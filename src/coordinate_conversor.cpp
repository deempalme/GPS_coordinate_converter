#include "torero/coordinate_conversor.h"

namespace Toreo {
  template<typename T>
  CoordinateConversor<T>::CoordinateConversor(T *latitude, T *longitude) :
    latitude_(latitude),
    longitude_(longitude),
    null_(static_cast<T>(0.0)),
    to_radians_(static_cast<T>(0.01745329252)),
    to_degrees_(static_cast<T>(57.2957795131)),
    earth_radius_(static_cast<T>(6378137.0))
  {}

  template<typename T>
  Visualizer::pointXY<T> CoordinateConversor<T>::GPS_to_origin(){
    Visualizer::pointXY<T> value = { null_, null_ };

    if(latitude_ && longitude_){
      const T latitudeRAD{*latitude_ * to_radians_};
      const T longitudeRAD{*longitude_ * to_radians_};

      const T C{std::cos(latitudeRAD)};
      const T D{std::sin(latitudeRAD)};
      const T E{std::cos(longitudeRAD)};

      const T c{std::acos(C * E)};
      const T k{c / std::sin(c)};

      value.x = k * C * E * earth_radius_;
      value.y = k * D * earth_radius_;

      if(value.x != value.x) value.x = null_;
      if(value.y != value.y) value.y = null_;
    }
    return value;
  }

  template<typename T>
  Visualizer::pointXY<T> CoordinateConversor<T>::GPS_to_XY(T latitude, T longitude){
    Visualizer::pointXY<T> value = { null_, null_ };

    if(latitude_ && longitude_){
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

      if(value.x != value.x) value.x = null_;
      if(value.y != value.y) value.y = null_;
    }
    return value;
  }

  template<typename T>
  Visualizer::pointLL<T> CoordinateConversor<T>::XY_to_GPS(T x, T y){
    Visualizer::pointLL<T> value = { 0.0, 0.0 };

    if(latitude_ && longitude_){
      const T x2{x/earth_radius_};
      const T y2{y/earth_radius_};

      const T c{std::sqrt(x2 * x2 + y2 * y2)};
      const T latitudeRAD{*latitude_ * to_radians_};
      const T A{std::cos(latitudeRAD)};
      const T B{std::sin(latitudeRAD)};
      const T C{std::sin(c)};
      const T D{std::cos(c)};

      value.latitude = std::asin(D * B + (y2 * C * A) / c) * to_degrees_;

      if(*latitude_ >= 90.0)
        value.longitude = *longitude_ + std::atan(-x2/y2) * to_degrees_;
      else if(*latitude_ <= -90.0)
        value.longitude = *longitude_ + std::atan(x2/y2) * to_degrees_;
      else
        value.longitude = *longitude_ + std::atan((x2 * C)/(c * A * D - y2 * B * C)) * to_degrees_;
    }
    return value;
  }

  template<typename T>
  T CoordinateConversor<T>::distance(T start_latitude, T start_longitude,
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

    if(x != x) x = null_;
    if(y != y) y = null_;

    return T(std::sqrt(x * x + y * y));
  }

  template<typename T>
  Visualizer::pointXY<T> CoordinateConversor<T>::distances(T start_latitude,
                                                           T start_longitude,
                                                           T end_latitude,
                                                           T end_longitude){
    Visualizer::pointXY<T> value = { null_, null_ };
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

    if(value.x != value.x) value.x = null_;
    if(value.y != value.y) value.y = null_;

    return value;
  }

  template class CoordinateConversor<float>;
  template class CoordinateConversor<double>;
  template class CoordinateConversor<long double>;
}
