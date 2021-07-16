<p align="center"><img src="images/logo.png" align="center" alt="GPS Conversor"></p>  

___

#### Table of Contents
   [1.1 Azimuthal equidistant map projection definition](#A)  
   &nbsp; &nbsp; [1.1.1 Understanding Latitude and Longiutde](#A1)  
   [1.2 Installation](#B)  
   [1.3 Public members](#C)  
   &nbsp; &nbsp; [1.3.1 Constructor](#C)  
   &nbsp; &nbsp; [1.3.2 Reseting the map's center](#rtmc)  
   &nbsp; &nbsp; [1.3.3 Getting the map's center](#gtmc)  
   &nbsp; &nbsp; [1.3.4 Calculating the distance from map's center to the map's origin](#ctdfmcttmo)  
   &nbsp; &nbsp; [1.3.5 Calculating the distance from a given GPS coordinates to the map's origin](#ctdfaggcttmo)  
   &nbsp; &nbsp; [1.3.6 Converting from GPS coordinates to X and Y distances](#C2)  
   &nbsp; &nbsp; [1.3.7 Converting from X and Y position to GPS coordinates](#C3)  
   &nbsp; &nbsp; [1.3.8 Calculating the distance between two GPS coordinates](#C4)  
   &nbsp; &nbsp; [1.3.9 Calculating the distance X and Y between two GPS coordinates](#C5)  
   &nbsp; &nbsp; [1.3.10 Changing the earth radius](#C6)  
   &nbsp; &nbsp; [1.3.11 Converting from radians to degrees and vice versa](#C7)  
   [1.4 Type definition](#D)  
   [1.5 Getting started](#E)  

___
<a name="A"></a><br/>  

## 1.1 Azimuthal equidistant map projection

The azimuthal equidistant projection is an azimuthal map projection. It has the useful properties that all points on the map are at proportionally correct distances from the center point, and that all points on the map are at the correct azimuth (direction) from the center point. A useful application for this type of projection is a polar projection which shows all meridians (lines of longitude) as straight, with distances from the pole represented correctly. The flag of the United Nations contains an example of a polar azimuthal equidistant projection. [\[wiki\]](https://www.wikiwand.com/en/Azimuthal_equidistant_projection)

You can see an interactive map [here](http://rogerallen.github.io/webgl/2014/01/27/azimuthal-equidistant-projection/), use the mouse to move center of the map projection.

<a name="A1"></a>  
### 1.1.1 Understanding Latitude and Longiutde

<p align="center">
   <img src="images/latitude-longitude.png" alt="Latitude-Longitude"/>
</p>  

**Latitude** and **Longitude** are imaginary lines that separate the globe in sections; **latitude** are horizontal lines and separate the circunference *vertically*, they represent values in the **Y axis**. **Longitude** in the other hand are vertical lines and separate the circunference *horizontally*, they represent values in **X axis**. The **origin** of **XY** and **Lat-Long** coodinate systems are located where the *Ecuator* and *Greenwich (prime meridian)* lines intersect.
<br/><br/>

___
<a name="B"></a><br/>  

## 1.2 Installation

This library does not require any additional libray, you only need to add the files to your **project's** folder and add the following lines to your **CMakeLists.txt**:
```Cmake
# Tripe points (...) represent possible content that may 
# already exist in your CMakeLists.txt
...
# Replace <gps_conversor_folder_path> with the actual folder path
add_subdirectory(<gps_conversor_folder_path>)

# Replace <project_name> with the actual project name
target_include_directories(<project_name>
  ${COORDINATE_INCLUDE_DIRS}
)
...
# Replace <project_name> with the actual project name
target_link_libraries(<project_name>
  ...
  ${COORDINATE_LIBRARIES}
  ...
)
...
```
And add the next `include` line into your code:
```c++
#include "ramrod/gps/coordinate_conversor.h"
```
<br/>

___
<a name="C"></a><br/>  

## 1.3 Public members

### 1.3.1 Constructor

You could define a different map's center by specifying pointers for `latitude` and `longitude` so, when you call `gps_to_xy()` or `xy_to_gps()`, the distances are properly calculated from that center, by default is (0°, 0°). This does not affect `distance()` or `distances()`. **NOTE:** _the map's center is different to the origin, the later is always located in the coordinates (0°, 0°). The former represents the center position of the azimuthal projection and it can change at your will._
```c++
ramrod::gps::coordinate_conversor<T>(const T *latitude = nullptr,
                                     const T *longitude = nullptr);
```

 &nbsp; **Parameters**

| Type | Name | Description |
| --- | --- | --- |
| `const T*` | **latitude** | Latitude coordinate of the map's center. |
| `const T*` | **longitude** | Longitude coordinate of the map's center. |
<br/>

---
<a name="rtmc"></a><br/>

### 1.3.2 Reseting the map's center

This function will change the variable's pointer used to define the map center (_center position of the azimuthal projection_) so, when you call `gps_to_xy()` or `xy_to_gps()`, the distances are properly calculated from that center. This does not affect `distance()` or `distances()`
```c++
bool center(const T *latitude, const T *longitude);
```

 &nbsp; **Parameters**

| Type | Name | Description |
| --- | --- | --- |
| `const T*` | **latitude** | Latitude coordinate of the map's center. |
| `const T*` | **longitude** | Longitude coordinate of the map's center. |
<br/>

 &nbsp; **Returns**

 | Type | Description |
 | --- | --- |
 | `bool` | `false` if latitude or longitude are `nullptr`. |
<br/>

---
<a name="gtmc"></a><br/>

### 1.3.3 Getting the map's center

Call this function to get the map's center coordinates (_center of the azimuthal projection_)
```c++
ramrod::point_ll<T> center();
```

 &nbsp; **Returns**

 | Type | Description |
 | --- | --- |
 | `ramrod::point_ll<T>` | GPS coordinates of the map's center. |
<br/>

___
<a name="ctdfmcttmo"></a><br>  

### 1.3.4 Calculating the distance from map's center to the map's origin

This function calculates the distance from the **map's center** (_center of azimuthal projection_) to the **map's origin** (*latitude* and *longitude* equal to 0° and 0°). The map's center is defined at the `constructor` or in `center(const T*, const T*)` functions.
```c++
ramrod::point_xy<T> gps_to_origin();
```

 &nbsp; **Returns**

 | Type | Description |
 | --- | --- |
 | `ramrod::point_xy<T>` | Distance in meters on **X** and **Y** axes relative to the **map's origin** (*latitude* and *longitude* equal to to 0° and 0°). (see [Types](#D) for more information about the `struct`). |
<br>

___
<a name="ctdfaggcttmo"></a><br>  

### 1.3.5 Calculating the distance from a given GPS coordinates to the map's origin

This function calculates the distance from the **given GPS coordinates** to the **map's origin** (*latitude* and *longitude* equal to 0° and 0°).
```c++
ramrod::point_xy<T> gps_to_origin(const T latitude, const T longitude);
```

 &nbsp; **Returns**

 | Type | Description |
 | --- | --- |
 | `ramrod::point_xy<T>` | Distance in meters on **X** and **Y** axes relative to the **map's origin** (*latitude* and *longitude* equal to 0° and 0°). (see [Types](#D) for more information about the `struct`). |
<br>

___
<a name="C2"></a><br/>  

### 1.3.6 Converting from GPS coordinates to X and Y distances

This function converts GPS **degree** coordinates to distance in meters from the **GPS position** to the **map's center** which was defined in the `constructor` or in `center(const T*, const T*)`.
```c++
ramrod::point_xy<T> gps_to_xy(T latitude, T longitude);
```

 &nbsp; **Parameters**

| Type | Name | Description |
| --- | --- | --- |
| `T` | **latitude** | Latitude coordinate to convert. |
| `T` | **longitude** | Longitude coordinate to convert. |

 &nbsp; **Returns**

 | Type | Description |
 | --- | --- |
 | `ramrod::point_xy<T>` | Distance in meters with coordinates **X** and **Y** relative to the map's center defined at the constructor. (see [Types](#D) for more information about the `struct`). |

<br/>

___
<a name="C3"></a><br/>  

### 1.3.7 Converting from X and Y position to GPS coordinates

This function converts **X** and **Y** position *(in meters)* into GPS **degree** coordinates. The X and Y distances must be relative to the map's center (not the map's origin), the **X axis** is a line pointing east and the **Y axis** is a line pointing towards north and map's center defined at the `constructor` or in `center(const T*, const T*)`.
```c++
ramrod::point_ll<T> xy_to_gps(T x, T y);
```

 &nbsp; **Parameters**

| Type | Name | Description |
| --- | --- | --- |
| `T` | **x** | Distance **X** relative to the map's center |
| `T` | **y** | Distance **Y** relative to the map's center |

 &nbsp; **Returns**

 | Type | Description |
 | --- | --- |
 | `ramrod::point_ll<T>` | Coordinates **latitude** and **longitude**. (see [Types](#D) for more information about the `struct`). |
 
<br/>

___
<a name="C4"></a><br/>  

### 1.3.8 Calculating the distance between two GPS coordinates

This function calculates the **distance** between two GPS points, you must define the **start point** *(latitude, longitude)* and **end point** *(latitude, longitude)*.
```c++
T distance(T start_latitude, T start_longitude,
           T end_latitude, T end_longitude);
```

 &nbsp; **Parameters**

| Type | Name | Description |
| --- | --- | --- |
| `T` | **start_latitude** | Latitude of point 1. |
| `T` | **start_longitude** | Longitude of point 1. |
| `T` | **end_latitude** | Latitude of point 2. |
| `T` | **end_longitude** | Longitude of point 2. |

 &nbsp; **Returns**

 | Type | Description |
 | --- | --- |
 | `T` | Distance in meters from *start point* to *end point*. |
 
<br/>

___
<a name="C5"></a><br/>  

### 1.3.9 Calculating the distance X and Y between two GPS coordinates

This function calculates the **distance X** and **Y** between two GPS points, you must define a **start point** *(latitude, longitude)* and **end point** *(latitude, longitude)*.
```c++
ramrod::point_xy<T> distances(T start_latitude, T start_longitude,
                              T end_latitude, T end_longitude);
```

 &nbsp; **Parameters**

| Type | Name | Description |
| --- | --- | --- |
| `T` | **start_latitude** | Latitude of point 1. |
| `T` | **start_longitude** | Longitude of point 1. |
| `T` | **end_latitude** | Latitude of point 2. |
| `T` | **end_longitude** | Longitude of point 2. |

 &nbsp; **Returns**
 
 | Type | Description |
 | --- | --- |
 | `ramrod::point_xy<T>` | Distance in meters from *start point* to *end point* separated in **vector components**. (see [Types](#D) for more information about the `struct`). |
 
 <br/>

___
<a name="C6"></a><br/>  

### 1.3.10 Changing the earth radius

This function changes the default value of the earth radius (which is **6,378,137.0 meters**) for a value you could manually define. It is only recommended if you want more precision.
```c++
bool earth_radius(const T new_earth_radius);
```

 &nbsp; **Parameters**

| Type | Name | Description |
| --- | --- | --- |
| `T` | **new_earth_radius** | New earth radius in meters. |

 &nbsp; **Returns**
 
 | Type | Description |
 | --- | --- |
 | `bool` | `false` if the value is lesser or equal to zero. |
 
 <br/>

___
<a name="C7"></a><br/>  

### 1.3.11 Converting from radians to degrees and vice versa

This function converts radians into degrees or the other way around:
```c++
// Converting from radians to degrees
T to_degrees(const T radians);
// Converting from degrees to radians
T to_radians(const T degrees);
```

 &nbsp; **Parameters**

| Type | Name | Description |
| --- | --- | --- |
| `T` | **radians** | Angle in radians. |
| `T` | **degrees** | Angle in degrees. |

 &nbsp; **Returns**
 
 | Type | Description |
 | --- | --- |
 | `T` | _(first funtion)_ Value converted into degrees. |
 | `T` | _(second function)_ Value converted into radians. |
 
 <br/>
 
 ___
<a name="D"></a><br/>
 
 ## 1.4 Type Definitions
 
There is two different types of **structures**:

```c++
namespace ramrod {
  // Position in meters
  template<typename T>
  union point_xy{
    struct{
      T x; // Position in meters at the X axis (Longitude axis)
      T y; // Position in meters at the Y axis (Latitude axis)
    };
    T data[2];
  };
  
  // Position in degrees
  template<typename T>
  union point_ll{
    struct{
      T latitude;  // Latitude coordinate in degrees
      T longitude; // Longitude coordinate in degrees
    };
    T data[2];
  };
}
```

You could directly **choose a type** for the coordinate conversor using the following type definitions:

```c++
namespace torero {
  typedef coordinate_conversor<float> coordinate_conversor_float;
  typedef coordinate_conversor<double> coordinate_conversor_double;
  typedef coordinate_conversor<long double> coordinate_conversor_long;
}
```

Example:

```c++
// You could use this:
float map_center_latitude{0.0f};
float map_center_longitude{0.0f};
ramrod::gps::coordinate_conversor_float gps_conversor(&map_center_latitude,
                                                      &map_center_longitude);

// Instead of this:
float map_center_latitude{0.0f};
float map_center_longitude{0.0f};
ramrod::gps::coordinate_conversor<float> gps_conversor(&map_center_latitude,
                                                       &map_center_longitude);
```

<br/>

___
<a name="E"></a><br/>

## 1.5 Getting started

The use of the coordinate conversor is really easy, here is an example in how to use the library.

```c++
#include "ramrod/gps/coordinate_conversor.h"

#include <iostream>  // for std::cout, std::endl, std::fixed
#include <iomanip>   // for std::setprecision

int main(int argc, char *argv[]){
  // ------------------------------------------------------------------------------------ //
  // ---------------------------- GPS COORDINATE CONVERSOR ------------------------------ //
  // ------------------------------------------------------------------------------------ //
  // Defining the map center (which you could move inside your code at any moment)
  float map_center_latitude{0.0f};
  float map_center_longitude{0.0f};

  // Creating our GPS coordinate conversor object
  ramrod::gps::coordinate_conversor<float> conversor(&map_center_latitude,
                                                     &map_center_longitude);

  // -------------------------------------------------------------------------------
  // Converting from coordinates to meters (relative to the map center)
  ramrod::point_xy<float> point_1 = conversor.gps_to_xy(50.774987f, 6.085083f);
  // Printing the values
  std::cout << std::setprecision(2) << std::fixed
            << "X: " << point_1.x << "m \n"
            << "Y: " << point_1.y << "m"
            << std::endl;

  // -------------------------------------------------------------------------------
  // Changing the map's center location (center of the azimuthal projection)
  map_center_latitude = 50.0f;
  map_center_longitude = 6.0f;

  // -------------------------------------------------------------------------------
  // Converting from meters to coordinates (relative to the map's center)
  ramrod::point_ll<float> point_2 = conversor.xy_to_gps(1000.0f, 2000.0f);
  // Printing the values
  std::cout << std::setprecision(7)
            << "Latitude: " << point_2.latitude << "° \n"
            << "Longitude: " << point_2.longitude << "°"
            << std::endl;

  // -------------------------------------------------------------------------------
  // Setting the points A and B
  float A_latitude = 50.774987f;
  float A_longitude{6.085083f};
  float B_latitude{51.774987f};
  float B_longitude = 7.085083f;
  // Calculating the distance from point A to B
  float distance{conversor.distance(A_latitude, A_longitude,
                                    B_latitude, B_longitude)};
  // Printing the values
  std::cout << std::setprecision(2)
            << "Distance: " << distance << "m"
            << std::endl;


  // -------------------------------------------------------------------------------
  // Calculating the distance from point A to B
  ramrod::point_xy<float> distances = conversor.distances(A_latitude, A_longitude,
                                                          B_latitude, B_longitude);
  // Printing the values
  std::cout << "Distance in X: " << distances.x << "m \n"
            << "Distance in Y: " << distances.y << "m"
            << std::endl;

  return 0;
}
```
