#include "include/coordinate_conversor.h"

namespace Toreo {
  CoordinateConversor::CoordinateConversor(double *latitude, double *longitude) :
    latitude_(latitude),
    longitude_(longitude)
  {}

  Visualizer::pointXY CoordinateConversor::GPS_to_XY(double latitude, double longitude){
    Visualizer::pointXY value = { 0.0, 0.0 };

    if(latitude_ && longitude_){
      latitude  *= toRADIANS;
      longitude *= toRADIANS;

      double latitudeRAD{*latitude_ * toRADIANS};
      double longitudeRAD{*longitude_ * toRADIANS};

      double A{cos(latitudeRAD)};
      double B{sin(latitudeRAD)};
      double C{cos(latitude)};
      double D{sin(latitude)};
      double E{cos(longitude - longitudeRAD)};

      double c{acos(B * D + A * C * E)};
      double k{c / sin(c)};

      value.x = k * C * sin(longitude - longitudeRAD) * 6378137.0;
      value.y = k * (A * D - B * C * E) * 6378137.0;

      if(value.x != value.x) value.x = 0.0;
      if(value.y != value.y) value.y = 0.0;
    }
    return value;
  }

  Visualizer::pointLL CoordinateConversor::XY_to_GPS(double x, double y){
    Visualizer::pointLL value = { 0.0, 0.0 };

    if(latitude_ && longitude_){
      x /= 6378137.0;
      y /= 6378137.0;

      double c{sqrt(x * x + y * y)};
      double latitudeRAD{*latitude_ * toRADIANS};
      double A{cos(latitudeRAD)};
      double B{sin(latitudeRAD)};
      double C{sin(c)};
      double D{cos(c)};

      value.latitude = asin(D * B + (y * C * A) / c) * toDEGREES;

      if(*latitude_ == 90.0)
        value.longitude = *longitude_ + atan(-x/y) * toDEGREES;
      else if(*latitude_ == -90.0)
        value.longitude = *longitude_ + atan(x/y) * toDEGREES;
      else
        value.longitude = *longitude_ + atan((x * C)/(c * A * D - y * B * C)) * toDEGREES;
    }
    return value;
  }

  double CoordinateConversor::distance(double start_latitude, double start_longitude,
                                       double end_latitude, double end_longitude){
    start_latitude  *= toRADIANS;
    start_longitude *= toRADIANS;
    end_latitude    *= toRADIANS;
    end_longitude   *= toRADIANS;

    double A{cos(start_latitude)};
    double B{sin(start_latitude)};
    double C{cos(end_latitude)};
    double D{sin(end_latitude)};
    double E{cos(end_longitude - start_longitude)};

    double c{acos(B * D + A * C * E)};
    double k{c / sin(c)};

    double x{k * C * sin(end_longitude - start_longitude) * 6378137.0};
    double y{k * (A * D - B * C * E) * 6378137.0};

    if(x != x) x = 0.0;
    if(y != y) y = 0.0;

    return double(sqrt(x * x + y * y));
  }

  Visualizer::pointXY CoordinateConversor::distances(double start_latitude, double start_longitude,
                                                     double end_latitude, double end_longitude){
    Visualizer::pointXY value = { 0.0, 0.0 };
    start_latitude  *= toRADIANS;
    start_longitude *= toRADIANS;
    end_latitude    *= toRADIANS;
    end_longitude   *= toRADIANS;

    double A{cos(start_latitude)};
    double B{sin(start_latitude)};
    double C{cos(end_latitude)};
    double D{sin(end_latitude)};
    double E{cos(end_longitude - start_longitude)};

    double c{acos(B * D + A * C * E)};
    double k{c / sin(c)};

    value.x = k * C * sin(end_longitude - start_longitude) * 6378137.0;
    value.y = k * (A * D - B * C * E) * 6378137.0;

    if(value.x != value.x) value.x = 0.0;
    if(value.y != value.y) value.y = 0.0;

    return value;
  }
}
