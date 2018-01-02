#include "coordinate_conversor.h"

#include <iostream>
#include <iomanip>

int main(int argc, char *argv[]){
  // ------------------------------------------------------------------------------------ //
  // ---------------------------- GPS COORDINATE CONVERSOR ------------------------------ //
  // ------------------------------------------------------------------------------------ //
  // Defining the map center (which you could move inside your code at any moment)
  double map_center_latitude{0.0};
  double map_center_longitude{0.0};

  // Creating our GPS coordinate conversor object
  Toreo::CoordinateConversor<float> conversor(&map_center_latitude, &map_center_longitude);

  // -------------------------------------------------------------------------------
  // Converting from coordinates to meters (relative to the map center)
  Visualizer::pointXY<float> point_1;
  point_1 = conversor.GPS_to_XY(50.774987, 6.085083);
  // Printing the values
  std::cout << std::setprecision(2) << std::fixed
            << "X: " << point_1.x << "m \n"
            << "Y: " << point_1.y << "m"
            << std::endl;

  // -------------------------------------------------------------------------------
  // Changing the map center location
  map_center_latitude = 50.0;
  map_center_longitude = 6.0;

  // -------------------------------------------------------------------------------
  // Converting from meters to coordinates (relative to the map center)
  Visualizer::pointLL point_2{conversor.XY_to_GPS(1000.0f, 2000.0f)};
  // Printing the values
  std::cout << std::setprecision(9) << std::fixed
            << "Latitude: " << point_2.latitude << "° \n"
            << "Longitude: " << point_2.longitude << "°"
            << std::endl;

  // -------------------------------------------------------------------------------
  // Setting the points A and B
  double start_latitude = 50.774987;
  double start_longitude{6.085083};
  double end_latitude{51.774987};
  double end_longitude = 7.085083;
  // Calculating the distance from point A to B
  float distance{conversor.distance(start_latitude, start_longitude,
                                    end_latitude, end_longitude)};
  // Printing the values
  std::cout << std::setprecision(2) << std::fixed
            << "Distance: " << distance << "m"
            << std::endl;


  // -------------------------------------------------------------------------------
  // Calculating the distance from point A to B
  Visualizer::pointXY<float> distances{conversor.distances(start_latitude, start_longitude,
                                                           51.774987, 7.085083)};
  // Printing the values
  std::cout << std::setprecision(2) << std::fixed
            << "Distance in X: " << distances.x << "m \n"
            << "Distance in Y: " << distances.y << "m"
            << std::endl;

  return 0;
}
