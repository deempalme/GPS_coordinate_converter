#ifndef RAMROD_GPS_COORDINATE_CONVERSOR_TYPES_H
#define RAMROD_GPS_COORDINATE_CONVERSOR_TYPES_H

#ifndef RR_P_XY_LL
#define RR_P_XY_LL
namespace ramrod {
  template<typename T>
  union point_xy{
    struct{
      T x; // Position in meters at the X axis (Longitude axis)
      T y; // Position in meters at the Y axis (Latitude axis)
    };
    T data[2] = { 0, 0 };
  };

  template<typename T>
  union point_ll{
    struct{
      T latitude;  // Latitude coordinate in degrees
      T longitude; // Longitude coordinate in degrees
    };
    T data[2] = { 0, 0 };
  };
} // namespace ramrod
#endif

#endif // RAMROD_GPS_COORDINATE_CONVERSOR_TYPES_H
