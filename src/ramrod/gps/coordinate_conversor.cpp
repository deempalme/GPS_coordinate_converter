#include "ramrod/gps/coordinate_conversor.h"

#include <cmath>

namespace ramrod {
  namespace gps {
    template<typename T>
    coordinate_conversor<T>::coordinate_conversor(const T *latitude,
                                                  const T *longitude) :
      zero_{static_cast<T>(0)},
      latitude_{latitude == nullptr ? &zero_ : latitude},
      longitude_{longitude == nullptr ? &zero_ : longitude},
      earth_radius_{static_cast<T>(6378137.0)}
    {}

    template<typename T>
    bool coordinate_conversor<T>::center(const T *latitude, const T *longitude){
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
      start_latitude  = to_radians(start_latitude);
      start_longitude = to_radians(start_longitude);
      end_latitude    = to_radians(end_latitude);
      end_longitude   = to_radians(end_longitude);

      const T A{std::cos(start_latitude)};
      const T B{std::sin(start_latitude)};
      const T C{std::cos(end_latitude)};
      const T D{std::sin(end_latitude)};
      const T E{std::cos(end_longitude - start_longitude)};

      const T c{std::acos(B * D + A * C * E)};
      const T k{c / std::sin(c)};

      T x{k * C * std::sin(end_longitude - start_longitude) * earth_radius_};
      T y{k * (A * D - B * C * E) * earth_radius_};

      if(x != x) x = static_cast<T>(0);
      if(y != y) y = static_cast<T>(0);

      return static_cast<T>(std::sqrt(x * x + y * y));
    }

    template<typename T>
    ramrod::point_xy<T> coordinate_conversor<T>::distances(T start_latitude, T start_longitude,
                                                           T end_latitude, T end_longitude){
      ramrod::point_xy<T> value;
      start_latitude  = to_radians(start_latitude);
      start_longitude = to_radians(start_longitude);
      end_latitude    = to_radians(end_latitude);
      end_longitude   = to_radians(end_longitude);

      const T A{std::cos(start_latitude)};
      const T B{std::sin(start_latitude)};
      const T C{std::cos(end_latitude)};
      const T D{std::sin(end_latitude)};
      const T E{std::cos(end_longitude - start_longitude)};

      const T c{std::acos(B * D + A * C * E)};
      const T k{c / std::sin(c)};

      value.x = k * C * std::sin(end_longitude - start_longitude) * earth_radius_;
      value.y = k * (A * D - B * C * E) * earth_radius_;

      if(value.x != value.x) value.x = static_cast<T>(0);
      if(value.y != value.y) value.y = static_cast<T>(0);

      return value;
    }

    template<typename T>
    bool coordinate_conversor<T>::earth_radius(const T new_earth_radius){
      if(new_earth_radius <= 0) return false;
      earth_radius_ = new_earth_radius;
      return true;
    }

    template<typename T>
    ramrod::point_xy<T> coordinate_conversor<T>::gps_to_origin(){
      ramrod::point_xy<T> value;

      const T latitude_rad{to_radians(*latitude_)};
      const T longitude_rad{to_radians(*longitude_)};

      const T C{std::cos(latitude_rad)};
      const T D{std::sin(latitude_rad)};
      const T E{std::cos(longitude_rad)};

      const T c{std::acos(C * E)};
      const T k{c / std::sin(c)};

      value.x = k * C * E * earth_radius_;
      value.y = k * D * earth_radius_;

      if(value.x != value.x) value.x = static_cast<T>(0);
      if(value.y != value.y) value.y = static_cast<T>(0);

      return value;
    }

    template<typename T>
    ramrod::point_xy<T> coordinate_conversor<T>::gps_to_origin(const T latitude, const T longitude){
      ramrod::point_xy<T> value;

      const T latitude_rad{to_radians(latitude)};
      const T longitude_rad{to_radians(longitude)};

      const T C{std::cos(latitude_rad)};
      const T D{std::sin(latitude_rad)};
      const T E{std::cos(longitude_rad)};

      const T c{std::acos(C * E)};
      const T k{c / std::sin(c)};

      value.x = k * C * E * earth_radius_;
      value.y = k * D * earth_radius_;

      if(value.x != value.x) value.x = static_cast<T>(0);
      if(value.y != value.y) value.y = static_cast<T>(0);

      return value;
    }

    template<typename T>
    ramrod::point_xy<T> coordinate_conversor<T>::gps_to_xy(T latitude, T longitude){
      ramrod::point_xy<T> value;

      latitude  = to_radians(latitude);
      longitude = to_radians(longitude);

      const T latitude_rad{to_radians(*latitude_)};
      const T longitude_rad{to_radians(*longitude_)};

      const T A{std::cos(latitude_rad)};
      const T B{std::sin(latitude_rad)};
      const T C{std::cos(latitude)};
      const T D{std::sin(latitude)};
      const T E{std::cos(longitude - longitude_rad)};

      const T c{std::acos(B * D + A * C * E)};
      const T k{c / std::sin(c)};

      value.x = k * C * std::sin(longitude - longitude_rad) * earth_radius_;
      value.y = k * (A * D - B * C * E) * earth_radius_;

      if(value.x != value.x) value.x = static_cast<T>(0);
      if(value.y != value.y) value.y = static_cast<T>(0);

      return value;
    }

    template<typename T>
    ramrod::point_ll<T> coordinate_conversor<T>::xy_to_gps(T x, T y){
      ramrod::point_ll<T> value;

      const T x2{x/earth_radius_};
      const T y2{y/earth_radius_};

      const T c{std::sqrt(x2 * x2 + y2 * y2)};
      const T latitude_rad{to_radians(*latitude_)};
      const T A{std::cos(latitude_rad)};
      const T B{std::sin(latitude_rad)};
      const T C{std::sin(c)};
      const T D{std::cos(c)};

      value.latitude = to_degrees(std::asin(D * B + (y2 * C * A) / c));

      if(*latitude_ >= static_cast<T>(90))
        value.longitude = to_degrees(*longitude_ + std::atan(-x2/y2));
      else if(*latitude_ <= -static_cast<T>(90))
        value.longitude = to_degrees(*longitude_ + std::atan(x2/y2));
      else
        value.longitude = to_degrees(*longitude_ + std::atan((x2 * C)/(c * A * D - y2 * B * C)));

      return value;
    }

    template<typename T>
    T coordinate_conversor<T>::to_degrees(const T radians){
      return radians * static_cast<T>(57.2957795131);
    }

    template<typename T>
    T coordinate_conversor<T>::to_radians(const T degrees){
      return degrees * static_cast<T>(0.01745329252);
    }

    template class coordinate_conversor<float>;
    template class coordinate_conversor<double>;
    template class coordinate_conversor<long double>;
  } // namespace gps
} // namespace ramrod
