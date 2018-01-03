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

  union pointLL{
    struct{
      double latitude;  // Latitude coordinate in degrees
      double longitude; // Longitude coordinate in degrees
    };
    double data[2];
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
     * {double*} latitude = Latitude coordinate of the movable object.
     * {double*} longitude = Longitude coordinate of the movable object.
     *
     */
    CoordinateConversor(double *latitude = nullptr, double *longitude = nullptr);
    /***
     * ### Calculating the distance from movable object to the map's origin
     *
     * This function calculates the distance from the **movable object** defined at the
     * **constructor** to the **map's origin** (*latitude* and *longitude* equal to *zero*).
     *
     * **Returns**
     * {Visualizer::pointXY<T>} Position in meters on **X** and **Y** axes relative to the
     * **map's origin** (*latitude* and *longitude* equal to *zero*). (see [Types](#D)
     * for more information about the `struct`).
     *
     * **Errors**
     * This will always return x = 0 and y = 0 if the *latitude and *longitude were not
     * defined in the constructor.
     *
     */
    Visualizer::pointXY<T> GPS_to_origin();
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
     * {double} latitude = Latitude coordinate to measure.
     * {double} longitude = Longitude coordinate to measure.
     *
     * **Returns**
     * {Visualizer::pointXY<T>} Position in meters on **X** and **Y** axes relative to the
     * **map's center** defined at the constructor. (see [Types](#D) for more information
     * about the `struct`).
     *
     * **Errors**
     * This will always return x = 0 and y = 0 if the *latitude and *longitude were not
     * defined in the constructor.
     *
     */
    Visualizer::pointXY<T> GPS_to_XY(double latitude, double longitude);
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
     * **Returns**
     * {Visualizer::pointLL} Coordinates **latitude** and **longitude**. (see [Types](#D)
     * for more information about the `struct`).
     *
     * **Errors**
     * This will always return `latitude = 0` and `longitude = 0` if the *latitude* and *longitude* were not
     * defined in the constructor.
     *
     */
    Visualizer::pointLL XY_to_GPS(T x, T y);
    /***
     * ### Calculating the distance between two GPS coordinates
     * 
     * This function calculates the **distance** between two GPS points, you must define the
     * **start point** *(latitude, longitude)* and **end point** *(latitude, longitude)*.
     *
     * **Arguments**
     * {double} start_latitude = Latitude of point 1.
     * {double} start_longitude = Longitude of point 1.
     * {double} end_latitude = Latitude of point 2.
     * {double} end_longitude = Longitude of point 2.
     *
     * **Returns**
     * {T} Distance in meters from *start point* to *end point*.
     *
     * **Errors**
     * This will return strange values if you do not introduces proper GPS coordinates.
     *
     */
    T distance(double start_latitude, double start_longitude,
               double end_latitude, double end_longitude);
    /***
     * ### Calculating the distance X and Y between two GPS coordinates
     *
     * This function calculates the **distance X** and **Y** between two GPS points, you
     * must define a **start point** *(latitude, longitude)* and **end point** *(latitude,
     * longitude)*.
     *
     * **Arguments**
     * {double} start_latitude = latitude of point 1
     * {double} start_longitude = longitude of point 1
     * {double} end_latitude = latitude of point 2
     * {double} end_longitude = longitude of point 2
     *
     * **Returns**
     * {Visualizer::pointXY<T>} Distance in meters from *start point* to *end point*
     * separated in **vector components**. (see [Types](#D) for more information
     * about the `struct`).
     *
     * **Errors**
     * This will return strange values if you do not introduces proper GPS coordinates.
     *
     */
    Visualizer::pointXY<T> distances(double start_latitude, double start_longitude,
                                     double end_latitude, double end_longitude);
  private:
    double *latitude_, *longitude_;
    T null_;
    double to_radians_, earth_radius_, to_degrees_;
  };

  typedef CoordinateConversor<float> CoordinateConversorFloat;
  typedef CoordinateConversor<double> CoordinateConversorDouble;
  typedef CoordinateConversor<long double> CoordinateConversorLong;
}

#endif // TORERO_COORDINATE_CONVERSOR_H
