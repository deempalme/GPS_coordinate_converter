#include "torero/coordinate_conversor.h"

namespace Toreo {
  template<typename T>
  CoordinateConversor<T>::CoordinateConversor(double *latitude, double *longitude) :
    latitude_(latitude),
    longitude_(longitude),
    null_(static_cast<T>(0.0)),
    to_radians_(0.01745329252),
    to_degrees_(57.2957795131),
    earth_radius_(6378137.0)
  {}

  template<typename T>
  Visualizer::pointXY<T> CoordinateConversor<T>::GPS_to_origin(){
    Visualizer::pointXY<T> value = { null_, null_ };

    if(latitude_ && longitude_){
      const double latitudeRAD{*latitude_ * to_radians_};
      const double longitudeRAD{*longitude_ * to_radians_};

      const double C{std::cos(latitudeRAD)};
      const double D{std::sin(latitudeRAD)};
      const double E{std::cos(longitudeRAD)};

      const double c{std::acos(C * E)};
      const double k{c / std::sin(c)};

      value.x = static_cast<T>(k * C * E * earth_radius_);
      value.y = static_cast<T>(k * D * earth_radius_);

      if(value.x != value.x) value.x = null_;
      if(value.y != value.y) value.y = null_;
    }
    return value;
  }

  template<typename T>
  Visualizer::pointXY<T> CoordinateConversor<T>::GPS_to_XY(double latitude, double longitude){
    Visualizer::pointXY<T> value = { null_, null_ };

    if(latitude_ && longitude_){
      latitude  *= to_radians_;
      longitude *= to_radians_;

      const double latitudeRAD{*latitude_ * to_radians_};
      const double longitudeRAD{*longitude_ * to_radians_};

      const double A{std::cos(latitudeRAD)};
      const double B{std::sin(latitudeRAD)};
      const double C{std::cos(latitude)};
      const double D{std::sin(latitude)};
      const double E{std::cos(longitude - longitudeRAD)};

      const double c{std::acos(B * D + A * C * E)};
      const double k{c / std::sin(c)};

      value.x = static_cast<T>(k * C * std::sin(longitude - longitudeRAD) * earth_radius_);
      value.y = static_cast<T>(k * (A * D - B * C * E) * earth_radius_);

      if(value.x != value.x) value.x = null_;
      if(value.y != value.y) value.y = null_;
    }
    return value;
  }

  template<typename T>
  Visualizer::pointLL CoordinateConversor<T>::XY_to_GPS(T x, T y){
    Visualizer::pointLL value = { 0.0, 0.0 };

    if(latitude_ && longitude_){
      const double x2{static_cast<double>(x)/earth_radius_};
      const double y2{static_cast<double>(y)/earth_radius_};

      const double c{std::sqrt(x2 * x2 + y2 * y2)};
      const double latitudeRAD{*latitude_ * to_radians_};
      const double A{std::cos(latitudeRAD)};
      const double B{std::sin(latitudeRAD)};
      const double C{std::sin(c)};
      const double D{std::cos(c)};

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
  T CoordinateConversor<T>::distance(double start_latitude, double start_longitude,
                                     double end_latitude,   double end_longitude){
    start_latitude  *= to_radians_;
    start_longitude *= to_radians_;
    end_latitude    *= to_radians_;
    end_longitude   *= to_radians_;

    const double A{std::cos(start_latitude)};
    const double B{std::sin(start_latitude)};
    const double C{std::cos(end_latitude)};
    const double D{std::sin(end_latitude)};
    const double E{std::cos(end_longitude - start_longitude)};

    const double c{std::acos(B * D + A * C * E)};
    const double k{c / std::sin(c)};

    T x{static_cast<T>(k * C * std::sin(end_longitude - start_longitude) * earth_radius_)};
    T y{static_cast<T>(k * (A * D - B * C * E) * earth_radius_)};

    if(x != x) x = null_;
    if(y != y) y = null_;

    return T(std::sqrt(x * x + y * y));
  }

  template<typename T>
  Visualizer::pointXY<T> CoordinateConversor<T>::distances(double start_latitude,
                                                           double start_longitude,
                                                           double end_latitude,
                                                           double end_longitude){
    Visualizer::pointXY<T> value = { null_, null_ };
    start_latitude  *= to_radians_;
    start_longitude *= to_radians_;
    end_latitude    *= to_radians_;
    end_longitude   *= to_radians_;

    const double A{std::cos(start_latitude)};
    const double B{std::sin(start_latitude)};
    const double C{std::cos(end_latitude)};
    const double D{std::sin(end_latitude)};
    const double E{std::cos(end_longitude - start_longitude)};

    const double c{std::acos(B * D + A * C * E)};
    const double k{c / std::sin(c)};

    value.x = static_cast<T>(k * C * std::sin(end_longitude - start_longitude) * earth_radius_);
    value.y = static_cast<T>(k * (A * D - B * C * E) * earth_radius_);

    if(value.x != value.x) value.x = null_;
    if(value.y != value.y) value.y = null_;

    return value;
  }

  template class CoordinateConversor<float>;
  template class CoordinateConversor<double>;
  template class CoordinateConversor<long double>;
}
