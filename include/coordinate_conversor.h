#ifndef TORERO_COORDINATE_CONVERSOR_H
#define TORERO_COORDINATE_CONVERSOR_H

#include <cmath>

#ifndef C_C_S
#define C_C_S
namespace Visualizer {
  template<typename T>
  union pointXY{
    struct{
      T x; // Position in meters at the X axis (Longitude axis)
      T y; // Position in meters at the Y axis (Latitude axis)
    };
    T data[2];
  };

  template<typename T>
  union pointLL{
    struct{
      T latitude;  // Latitude coordinate in degrees
      T longitude; // Longitude coordinate in degrees
    };
    T data[2];
  };
}
#endif

namespace Toreo {
  template<typename T>
  class CoordinateConversor
  {
  public:
    /***
     * ### Constructor
     * 
     * This will construct this class, if you have an object which is constantly moving
     * you could use its coordinates *(latitude and longitude)* as the parameters in the
     * constructor so, when you call `GPS_to_XY()` or `XY_to_GPS()`, the object's latitude
     * and longitude will be taken as the origin. This does not affect `distance()` or
     * `distances()`
     *
     * **Arguments**
     * {T*} latitude = Latitude coordinate of the movable object.
     * {T*} longitude = Longitude coordinate of the movable object.
     *
     */
    CoordinateConversor(T *latitude = nullptr, T *longitude = nullptr) :
      latitude_(latitude),
      longitude_(longitude),
      null_(static_cast<T>(0.0)),
      ninety_(static_cast<T>(90.0)),
      to_radians_(static_cast<T>(0.01745329252)),
      to_degrees_(static_cast<T>(57.2957795131)),
      earth_radius_(static_cast<T>(6378137.0))
    {}
    /***
     * ### Converting from GPS coordinates to X and Y distances
     *
     * This function converts GPS **degree** coordinates to distance in meters from the
     * **GPS position** to the **Object position** *(he object's position is the origin)*
     * which was defined in the constructor.
     *
     * Mathematical formulas are as follows:
     *  * `x = longitude_to_meters - Object_longitude_to_meters`
     *  * `y = latitude_to_meters - Object_latitude_to_meters`
     *
     * **Arguments**
     * {T} latitude = Latitude coordinate to measure.
     * {T} longitude = Longitude coordinate to measure.
     *
     * **Errors**
     * This will always return x = 0 and y = 0 if the *latitude and *longitude were not
     * defined in the constructor.
     *
     */
    Visualizer::pointXY<T> GPS_to_XY(T latitude, T longitude){
      Visualizer::pointXY<T> value = { null_, null_ };

      if(latitude_ && longitude_){
        latitude  *= to_radians_;
        longitude *= to_radians_;

        T latitudeRAD{*latitude_ * to_radians_};
        T longitudeRAD{*longitude_ * to_radians_};

        T A{std::cos(latitudeRAD)};
        T B{std::sin(latitudeRAD)};
        T C{std::cos(latitude)};
        T D{std::sin(latitude)};
        T E{std::cos(longitude - longitudeRAD)};

        T c{std::acos(B * D + A * C * E)};
        T k{c / std::sin(c)};

        value.x = k * C * std::sin(longitude - longitudeRAD) * earth_radius_;
        value.y = k * (A * D - B * C * E) * earth_radius_;

        if(value.x != value.x) value.x = null_;
        if(value.y != value.y) value.y = null_;
      }
      return value;
    }
    /***
     * ### Converting from X and Y position to GPS coordinates
     * 
     * This function converts **X** and **Y** position *(in meters)* into GPS **degree**
     * coordinates. The X and Y distances must be relative to the Object, the **X axis**
     * is a line pointing east and the **Y axis** is a line pointing towards north and center
     * at the Object position (defined at the constructor).
     *
     * Mathematical formulas are as follows:
     *  * `latitude = to_GPS_coordinate(Object_latitude_to_meters + y)`
     *  * `longitude = to_GPS_coordinate(Object_longitude_to_meters + x)`
     *
     * **Arguments**
     * {T} x = Position X to measure relative to the object defined at the constructor.
     * {T} y = Position Y to measure relative to the object defined at the constructor.
     *
     * **Errors**
     * This will always return `latitude = 0` and `longitude = 0` if the *latitude* and *longitude* were not
     * defined in the constructor.
     *
     */
    Visualizer::pointLL<T> XY_to_GPS(T x, T y){
      Visualizer::pointLL<T> value = { null_, null_ };

      if(latitude_ && longitude_){
        x /= earth_radius_;
        y /= earth_radius_;

        T c{std::sqrt(x * x + y * y)};
        T latitudeRAD{*latitude_ * to_radians_};
        T A{std::cos(latitudeRAD)};
        T B{std::sin(latitudeRAD)};
        T C{std::sin(c)};
        T D{std::cos(c)};

        value.latitude = std::asin(D * B + (y * C * A) / c) * to_degrees_;

        if(*latitude_ >= ninety_)
          value.longitude = *longitude_ + std::atan(-x/y) * to_degrees_;
        else if(*latitude_ <= -ninety_)
          value.longitude = *longitude_ + std::atan(x/y) * to_degrees_;
        else
          value.longitude = *longitude_ + std::atan((x * C)/(c * A * D - y * B * C)) * to_degrees_;
      }
      return value;
    }
    /***
     * ### Calculating the distance between two GPS coordinates
     * 
     * This function calculates the **distance** between two GPS points, you must define the
     * **start point** *(latitude, longitude)* and **end point** *(latitude, longitude)*.
     *
     * **Arguments**
     * {T} start_latitude = Latitude of point 1.
     * {T} start_longitude = Longitude of point 1.
     * {T} end_latitude = Latitude of point 2.
     * {T} end_longitude = Longitude of point 2.
     *
     * **Errors**
     * This will return strange values if you do not introduces proper GPS coordinates.
     *
     */
    T distance(T start_latitude, T start_longitude,
               T end_latitude, T end_longitude){
      start_latitude  *= to_radians_;
      start_longitude *= to_radians_;
      end_latitude    *= to_radians_;
      end_longitude   *= to_radians_;

      T A{std::cos(start_latitude)};
      T B{std::sin(start_latitude)};
      T C{std::cos(end_latitude)};
      T D{std::sin(end_latitude)};
      T E{std::cos(end_longitude - start_longitude)};

      T c{std::acos(B * D + A * C * E)};
      T k{c / std::sin(c)};

      T x{k * C * std::sin(end_longitude - start_longitude) * earth_radius_};
      T y{k * (A * D - B * C * E) * earth_radius_};

      if(x != x) x = null_;
      if(y != y) y = null_;

      return T(std::sqrt(x * x + y * y));
    }
    /***
     * ### Calculating the distance X and Y between two GPS coordinates
     *
     * This function calculates the **distance X** and **Y** between two GPS points, you
     * must define a **start point** *(latitude, longitude)* and **end point** *(latitude,
     * longitude)*.
     *
     * **Arguments**
     * {T} start_latitude = latitude of point 1
     * {T} start_longitude = longitude of point 1
     * {T} end_latitude = latitude of point 2
     * {T} end_longitude = longitude of point 2
     *
     * **Errors**
     * This will return strange values if you do not introduces proper GPS coordinates.
     *
     */
    Visualizer::pointXY<T> distances(T start_latitude, T start_longitude,
                                     T end_latitude, T end_longitude){
      Visualizer::pointXY<T> value = { null_, null_ };
      start_latitude  *= to_radians_;
      start_longitude *= to_radians_;
      end_latitude    *= to_radians_;
      end_longitude   *= to_radians_;

      T A{std::cos(start_latitude)};
      T B{std::sin(start_latitude)};
      T C{std::cos(end_latitude)};
      T D{std::sin(end_latitude)};
      T E{std::cos(end_longitude - start_longitude)};

      T c{std::acos(B * D + A * C * E)};
      T k{c / std::sin(c)};

      value.x = k * C * std::sin(end_longitude - start_longitude) * earth_radius_;
      value.y = k * (A * D - B * C * E) * earth_radius_;

      if(value.x != value.x) value.x = null_;
      if(value.y != value.y) value.y = null_;

      return value;
    }

  private:
    T *latitude_, *longitude_;
    T null_, ninety_;
    T to_radians_, earth_radius_, to_degrees_;
  };

  typedef CoordinateConversor<float> CoordinateConversorFloat;
  typedef CoordinateConversor<double> CoordinateConversorDouble;
  typedef CoordinateConversor<long double> CoordinateConversorLong;
}

#endif // TORERO_COORDINATE_CONVERSOR_H
