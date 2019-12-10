#include "ramrod/gps/coordinate_conversor.h"

#include <cmath>

namespace ramrod {
  namespace gps {
    template<typename T>
    coordinate_conversor<T>::coordinate_conversor(const T *latitude,
                                                  const T *longitude) :
      zero_{static_cast<T>(0.0)},
      latitude_{latitude == nullptr ? &zero_ : latitude},
      longitude_{longitude == nullptr ? &zero_ : longitude},
      ninety_{static_cast<T>(90.0)},
      to_radians_{static_cast<T>(0.01745329252)},
      to_degrees_{static_cast<T>(57.2957795131)},
      earth_radius_{static_cast<T>(6378137.0)}
    {}

    template<typename T>
    bool coordinate_conversor<T>::center(const T *latitude,
                                         const T *longitude){
      if(latitude == nullptr || longitude == nullptr) return false;
      latitude_ = latitude;
      longitude_ = longitude;
      return true;
    }

    template<typename T>
    ramrod::point_ll<T> coordinate_conversor<T>::center(){
      ramrod::point_ll<T> value;
      value.latitude = *latitude_;
      value.longitude = *longitude_;
      return value;
    }

    template<typename T>
    T coordinate_conversor<T>::distance(T start_latitude, T start_longitude,
                                        T end_latitude,   T end_longitude){
      start_latitude  *= to_radians_;
      start_longitude *= to_radians_;
      end_latitude    *= to_radians_;
      end_longitude   *= to_radians_;

      const T A{std::cos(start_latitude)};
      const T B{std::sin(start_latitude)};
      const T C{std::cos(end_latitude)};
      const T D{std::sin(end_latitude)};
      const T E{std::cos(end_longitude - start_longitude)};

      const T c{std::acos(B * D + A * C * E)};
      const T k{c / std::sin(c)};

      T x{k * C * std::sin(end_longitude - start_longitude) * earth_radius_};
      T y{k * (A * D - B * C * E) * earth_radius_};

      if(x != x) x = zero_;
      if(y != y) y = zero_;

      return static_cast<T>(std::sqrt(x * x + y * y));
    }

    template<typename T>
    ramrod::point_xy<T> coordinate_conversor<T>::distances(T start_latitude, T start_longitude,
                                                           T end_latitude, T end_longitude){
      ramrod::point_xy<T> value;
      start_latitude  *= to_radians_;
      start_longitude *= to_radians_;
      end_latitude    *= to_radians_;
      end_longitude   *= to_radians_;

      const T A{std::cos(start_latitude)};
      const T B{std::sin(start_latitude)};
      const T C{std::cos(end_latitude)};
      const T D{std::sin(end_latitude)};
      const T E{std::cos(end_longitude - start_longitude)};

      const T c{std::acos(B * D + A * C * E)};
      const T k{c / std::sin(c)};

      value.x = k * C * std::sin(end_longitude - start_longitude) * earth_radius_;
      value.y = k * (A * D - B * C * E) * earth_radius_;

      if(value.x != value.x) value.x = zero_;
      if(value.y != value.y) value.y = zero_;

      return value;
    }

    template<typename T>
    ramrod::point_xy<T> coordinate_conversor<T>::gps_to_origin(){
      ramrod::point_xy<T> value;

      const T latitudeRAD{*latitude_ * to_radians_};
      const T longitudeRAD{*longitude_ * to_radians_};

      const T C{std::cos(latitudeRAD)};
      const T D{std::sin(latitudeRAD)};
      const T E{std::cos(longitudeRAD)};

      const T c{std::acos(C * E)};
      const T k{c / std::sin(c)};

      value.x = k * C * E * earth_radius_;
      value.y = k * D * earth_radius_;

      if(value.x != value.x) value.x = zero_;
      if(value.y != value.y) value.y = zero_;

      return value;
    }

    template<typename T>
    ramrod::point_xy<T> coordinate_conversor<T>::gps_to_origin(const T latitude, const T longitude){
      ramrod::point_xy<T> value;

      const T latitudeRAD{latitude * to_radians_};
      const T longitudeRAD{longitude * to_radians_};

      const T C{std::cos(latitudeRAD)};
      const T D{std::sin(latitudeRAD)};
      const T E{std::cos(longitudeRAD)};

      const T c{std::acos(C * E)};
      const T k{c / std::sin(c)};

      value.x = k * C * E * earth_radius_;
      value.y = k * D * earth_radius_;

      if(value.x != value.x) value.x = zero_;
      if(value.y != value.y) value.y = zero_;

      return value;
    }

    template<typename T>
    ramrod::point_xy<T> coordinate_conversor<T>::gps_to_xy(T latitude, T longitude){
      ramrod::point_xy<T> value;

      latitude  *= to_radians_;
      longitude *= to_radians_;

      const T latitudeRAD{*latitude_ * to_radians_};
      const T longitudeRAD{*longitude_ * to_radians_};

      const T A{std::cos(latitudeRAD)};
      const T B{std::sin(latitudeRAD)};
      const T C{std::cos(latitude)};
      const T D{std::sin(latitude)};
      const T E{std::cos(longitude - longitudeRAD)};

      const T c{std::acos(B * D + A * C * E)};
      const T k{c / std::sin(c)};

      value.x = k * C * std::sin(longitude - longitudeRAD) * earth_radius_;
      value.y = k * (A * D - B * C * E) * earth_radius_;

      if(value.x != value.x) value.x = zero_;
      if(value.y != value.y) value.y = zero_;

      return value;
    }

    template<typename T>
    ramrod::point_ll<T> coordinate_conversor<T>::xy_to_gps(T x, T y){
      ramrod::point_ll<T> value;

      const T x2{x/earth_radius_};
      const T y2{y/earth_radius_};

      const T c{std::sqrt(x2 * x2 + y2 * y2)};
      const T latitudeRAD{*latitude_ * to_radians_};
      const T A{std::cos(latitudeRAD)};
      const T B{std::sin(latitudeRAD)};
      const T C{std::sin(c)};
      const T D{std::cos(c)};

      value.latitude = std::asin(D * B + (y2 * C * A) / c) * to_degrees_;

      if(*latitude_ >= ninety_)
        value.longitude = *longitude_ + std::atan(-x2/y2) * to_degrees_;
      else if(*latitude_ <= -ninety_)
        value.longitude = *longitude_ + std::atan(x2/y2) * to_degrees_;
      else
        value.longitude = *longitude_ + std::atan((x2 * C)/(c * A * D - y2 * B * C)) * to_degrees_;

      return value;
    }

    template class coordinate_conversor<float>;
    template class coordinate_conversor<double>;
    template class coordinate_conversor<long double>;
  } // namespace gps
} // namespace ramrod
