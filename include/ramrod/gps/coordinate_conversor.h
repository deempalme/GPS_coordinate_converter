#ifndef RAMROD_GPS_COORDINATE_CONVERSOR_H
#define RAMROD_GPS_COORDINATE_CONVERSOR_H

#include "ramrod/gps/types.h"

namespace ramrod {
  namespace gps {
    template<typename T>
    class coordinate_conversor
    {
    public:
      /**
       * @brief Constructor
       * 
       * You could define a different map's center by specifying pointers for `latitude`
       * and `longitude` so, when you call `gps_to_xy()` or `xy_to_gps()`, the distances
       * are properly calculated from that center, by default is (0°, 0°). This does not
       * affect `distance()` or `distances()`
       *
       * @param latitude  Latitude coordinate of the map's center.
       * @param longitude Longitude coordinate of the map's center.
       *
       */
      coordinate_conversor(const T *latitude = nullptr, const T *longitude = nullptr);
      /**
       * @brief Reseting the map's center
       *
       * This function will change the variable's pointer used to define the map center
       * so, when you call `gps_to_xy()` or `xy_to_gps()`, the distances are properly
       * calculated from that center. This does not affect `distance()` or `distances()`
       *
       * @param latitude  Latitude coordinate of the map's center.
       * @param longitude Longitude coordinate of the map's center.
       *
       * @return `false` if latitude or longitude are `nullptr`.
       */
      bool center(const T *latitude, const T *longitude);
      /**
       * @brief Getting the map's center
       *
       * Call this function to get the map's center coodinates (which is not the map's origin)
       *
       * @return GPS coordinates of the map's center.
       */
      ramrod::point_ll<T> center();
      /**
       * @brief Calculating the distance between two GPS coordinates
       *
       * This function calculates the **distance** between two GPS points, you must define the
       * **start point** *(latitude, longitude)* and **end point** *(latitude, longitude)*.
       *
       * @param start_latitude  Latitude of point 1.
       * @param start_longitude Longitude of point 1.
       * @param end_latitude    Latitude of point 2.
       * @param end_longitude   Longitude of point 2.
       *
       * @return Distance in meters from *start point* to *end point*.
       */
      T distance(T start_latitude, T start_longitude,
                 T end_latitude, T end_longitude);
      /**
       * @brief Calculating the distance X and Y between two GPS coordinates
       *
       * This function calculates the **distance X** and **Y** between two GPS points, you
       * must define a **start point** *(latitude, longitude)* and **end point** *(latitude,
       * longitude)*.
       *
       * @param start_latitude  Latitude of point 1
       * @param start_longitude Longitude of point 1
       * @param end_latitude    Latitude of point 2
       * @param end_longitude   Longitude of point 2
       *
       * @return Distance in meters from *start point* to *end point*
       * separated in **vector components**. (see [Types](#D) for more information
       * about the `struct`).
       */
      ramrod::point_xy<T> distances(T start_latitude, T start_longitude,
                                    T end_latitude, T end_longitude);
      /**
       * @brief Defines a new value for eath radius
       *
       * The initial value is 6,378,137.0 meters
       *
       * @param new_earth_radius New earth radius in meters
       *
       * @return `false` if the value is negative
       */
      bool earth_radius(const T new_earth_radius);
      /**
       * @brief Calculating the distance from map's center to the map's origin
       *
       * This function calculates the distance from the **map's center** defined at the
       * **constructor** to the **map's origin** (*latitude* and *longitude* equal to *zero*).
       *
       * @return Distance in meters on **X** and **Y** axes relative to the
       * **map's origin** (*latitude* and *longitude* equal to *zero*). (see [Types](#D)
       * for more information about the `struct`).
       */
      ramrod::point_xy<T> gps_to_origin();
      /**
       * @brief Calculating the distance from a give GPS coordinates to the map's origin
       *
       * This function calculates the distance from the **given GPS coordinates**
       * to the **map's origin** (*latitude* and *longitude* equal to *zero*).
       *
       * @return Distance in meters on **X** and **Y** axes relative to the
       * **map's origin** (*latitude* and *longitude* equal to *zero*). (see [Types](#D)
       * for more information about the `struct`).
       */
      ramrod::point_xy<T> gps_to_origin(const T latitude, const T longitude);
      /**
       * @brief Converting from GPS coordinates to X and Y distances
       *
       * This function converts GPS **degree** coordinates to distance in meters from the
       * **GPS position** to the **map's center** which was defined in the constructor.
       *
       * @param latitude  Latitude coordinate to measure.
       * @param longitude Longitude coordinate to measure.
       *
       * @return Distance in meters on **X** and **Y** axes relative to the
       * **map's center** defined at the constructor. (see [Types](#D) for more information
       * about the `struct`).
       */
      ramrod::point_xy<T> gps_to_xy(T latitude, T longitude);
      /**
       * @brief Converting from X and Y position to GPS coordinates
       * 
       * This function converts **X** and **Y** position *(in meters)* into GPS **degree**
       * coordinates. The X and Y distances must be relative to the map's center, the **X axis**
       * is a line pointing east and the **Y axis** is a line pointing towards north and map's
       * center (defined at the constructor).
       *
       * @param x Distance X relative to the map's center defined at the constructor.
       * @param y Distance Y relative to the map's center defined at the constructor.
       *
       * @return Coordinates **latitude** and **longitude**. (see [Types](#D)
       * for more information about the `struct`).
       */
      ramrod::point_ll<T> xy_to_gps(T x, T y);

      // Utility functions:

      /**
       * @brief Converting radians into degrees
       * 
       * @param radians Value in radians
       * 
       * @return Converted value (in degrees)
       */
      T to_degrees(const T radians);
      /**
       * @brief Converting degrees into radians
       * 
       * @param degrees Value in degrees
       * 
       * @return Converted value (in radians)
       */
      T to_radians(const T degrees);
      
    private:
      const T zero_;
      const T *latitude_, *longitude_;
      T earth_radius_;
    };

    typedef coordinate_conversor<float> coordinate_conversor_float;
    typedef coordinate_conversor<double> coordinate_conversor_double;
    typedef coordinate_conversor<long double> coordinate_conversor_long;
  } // namespace gps
} // namespace ramrod

#endif // RAMROD_GPS_COORDINATE_CONVERSOR_H
