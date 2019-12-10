#ifndef RAMROD_GPS_COORDINATE_CONVERSOR_H
#define RAMROD_GPS_COORDINATE_CONVERSOR_H

#include "ramrod/gps/types.h"

namespace ramrod {
  namespace gps {
    template<typename T>
    class coordinate_conversor
    {
    public:
      /***
       * ### Constructor
       * 
       * You could define a different map's center by specifying pointers for `latitude`
       * and `longitude` so, when you call `gps_to_xy()` or `xy_to_gps()`, the distances
       * are properly calculated from that center, by default is (0°, 0°). This does not
       * affect `distance()` or `distances()`
       *
       * @parameters
       * {const T*} latitude = Latitude coordinate of the map's center.
       * {const T*} longitude = Longitude coordinate of the map's center.
       *
       */
      coordinate_conversor(const T *latitude = nullptr, const T *longitude = nullptr);
      /***
       * ### Reseting the map's center
       *
       * This function will change the variable's pointer used to define the map center
       * so, when you call `gps_to_xy()` or `xy_to_gps()`, the distances are properly
       * calculated from that center. This does not affect `distance()` or `distances()`
       *
       * @parameters
       * {const T*} latitude = Latitude coordinate of the map's center.
       * {const T*} longitude = Longitude coordinate of the map's center.
       *
       * @returns
       * {bool} `false` if latitude or longitude are `nullptr`.
       *
       */
      bool center(const T *latitude, const T *longitude);
      /***
       * ### Getting the map's center
       *
       * Call this function to get the map's center coodinates
       *
       * @returns
       * {ramrod::point_ll<T>} GPS coordinates of the map's center.
       *
       */
      ramrod::point_ll<T> center();
      /***
       * ### Calculating the distance between two GPS coordinates
       *
       * This function calculates the **distance** between two GPS points, you must define the
       * **start point** *(latitude, longitude)* and **end point** *(latitude, longitude)*.
       *
       * @parameters
       * {T} start_latitude = Latitude of point 1.
       * {T} start_longitude = Longitude of point 1.
       * {T} end_latitude = Latitude of point 2.
       * {T} end_longitude = Longitude of point 2.
       *
       * @returns
       * {T} Distance in meters from *start point* to *end point*.
       *
       */
      T distance(T start_latitude, T start_longitude,
                 T end_latitude, T end_longitude);
      /***
       * ### Calculating the distance X and Y between two GPS coordinates
       *
       * This function calculates the **distance X** and **Y** between two GPS points, you
       * must define a **start point** *(latitude, longitude)* and **end point** *(latitude,
       * longitude)*.
       *
       * @parameters
       * {T} start_latitude = latitude of point 1
       * {T} start_longitude = longitude of point 1
       * {T} end_latitude = latitude of point 2
       * {T} end_longitude = longitude of point 2
       *
       * @returns
       * {ramrod::point_xy<T>} Distance in meters from *start point* to *end point*
       * separated in **vector components**. (see [Types](#D) for more information
       * about the `struct`).
       *
       */
      ramrod::point_xy<T> distances(T start_latitude, T start_longitude,
                                    T end_latitude, T end_longitude);
      /***
       * ### Calculating the distance from map's center to the map's origin
       *
       * This function calculates the distance from the **map's center** defined at the
       * **constructor** to the **map's origin** (*latitude* and *longitude* equal to *zero*).
       *
       * @returns
       * {ramrod::point_xy<T>} Position in meters on **X** and **Y** axes relative to the
       * **map's origin** (*latitude* and *longitude* equal to *zero*). (see [Types](#D)
       * for more information about the `struct`).
       *
       */
      ramrod::point_xy<T> gps_to_origin();
      /***
       * ### Calculating the distance from a give GPS coordinates to the map's origin
       *
       * This function calculates the distance from the **given GPS coordinates**
       * to the **map's origin** (*latitude* and *longitude* equal to *zero*).
       *
       * @returns
       * {ramrod::point_xy<T>} Position in meters on **X** and **Y** axes relative to the
       * **map's origin** (*latitude* and *longitude* equal to *zero*). (see [Types](#D)
       * for more information about the `struct`).
       *
       */
      ramrod::point_xy<T> gps_to_origin(const T latitude, const T longitude);
      /***
       * ### Converting from GPS coordinates to X and Y distances
       *
       * This function converts GPS **degree** coordinates to distance in meters from the
       * **GPS position** to the **map's center** which was defined in the constructor.
       *
       * @parameters
       * {T} latitude = Latitude coordinate to measure.
       * {T} longitude = Longitude coordinate to measure.
       *
       * @returns
       * {ramrod::point_xy<T>} Position in meters on **X** and **Y** axes relative to the
       * **map's center** defined at the constructor. (see [Types](#D) for more information
       * about the `struct`).
       *
       */
      ramrod::point_xy<T> gps_to_xy(T latitude, T longitude);
      /***
       * ### Converting from X and Y position to GPS coordinates
       * 
       * This function converts **X** and **Y** position *(in meters)* into GPS **degree**
       * coordinates. The X and Y distances must be relative to the map's center, the **X axis**
       * is a line pointing east and the **Y axis** is a line pointing towards north and map's
       * center (defined at the constructor).
       *
       * @parameters
       * {T} x = Position X to measure relative to the map's center defined at the constructor.
       * {T} y = Position Y to measure relative to the map's center defined at the constructor.
       *
       * @returns
       * {ramrod::point_ll<T>} Coordinates **latitude** and **longitude**. (see [Types](#D)
       * for more information about the `struct`).
       *
       */
      ramrod::point_ll<T> xy_to_gps(T x, T y);
    private:
      const T zero_;
      const T *latitude_, *longitude_;
      const T ninety_;
      const T to_radians_, to_degrees_, earth_radius_;
    };

    typedef coordinate_conversor<float> coordinate_conversor_float;
    typedef coordinate_conversor<double> coordinate_conversor_double;
    typedef coordinate_conversor<long double> coordinate_conversor_long;
  } // namespace gps
} // namespace ramrod

#endif // RAMROD_GPS_COORDINATE_CONVERSOR_H
