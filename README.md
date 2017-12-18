![GPS Conversor](images/logo.png)<br/>
This is a GPS Coordinates converter that uses using Azimuthal equidistant projection.

___

#### Table of Contents
   [1.1 Azimuthal equidistant map projection definition](#A)  
   [1.2 Installation](#B)  
   [1.3 Public members](#C)  
   &nbsp; &nbsp; [1.3.1 Constructor](#C1)  
   &nbsp; &nbsp; [1.3.2 Converting from GPS coordinates to X and Y distances](#C2)  
   &nbsp; &nbsp; [1.3.3 Converting from X and Y position to GPS coordinates](#C3)  
   &nbsp; &nbsp; [1.3.4 Calculating the distance between two GPS coordinates](#C4)  
   &nbsp; &nbsp; [1.3.5 Calculating the distance X and Y between two GPS coordinates](#C5)  
   [1.4 Type definition](#D)  
   [1.5 Getting started](#E)  

___
<a name="A"/>  

## 1.1 Azimuthal equidistant map projection

The azimuthal equidistant map projection creates a map that puts points equidistant from the map's center in a circle surrounding it. It has the useful properties that all points on the map are at proportionately correct distances from the center point, and that all points on the map are at the correct azimuth (direction) from the center point. The most famous example is the flag of the United Nations which centers at the north pole. It is an interesting and complex projection that in the past was mainly used to create line drawings. Now, it can be done in realtime on a GPU in your web browser.

You can see an interactive map [here](http://rogerallen.github.io/webgl/2014/01/27/azimuthal-equidistant-projection/), use the mouse to move center of the map projection.
<br/><br/>

___
<a name="B"/>  

## 1.2 Installation

This library does not require any additional libray, you only need to add the files to your **project's** folder and add the following lines to your **CMakeLists.txt**:
```Cmake
# Tripe points (...) represent possible content that may 
# already exist in your CMakeLists.txt
...
# Replace <gps_conversor_folder_path> with the actual folder path
add_subdirectory(<gps_conversor_folder_path>)
include_directories(${COORDINATE_DIRS})
...
# Replace <project_name> with the actual project name
target_link_libraries(<project_name>
  ...
  ${COORDINATE_LIB}
  ...
)
...
```
<br/>

___
<a name="C"/><a name="C1"/>  

## 1.3 Public members

### 1.3.1 Constructor

This will construct this class, if you have an object which is constantly moving you could use its coordinates *(latitude and longitude)* as the parameters in the constructor so, when you call `GPS_to_XY()` or `XY_to_GPS()`, the object's latitude and longitude will be taken as the origin. This does not affect `distance()` or `distances()`
```c++
CoordinateConversor(double *latitude = nullptr, double *longitude = nullptr);
```

 &nbsp; **Arguments**

| Type | Name | Description |
| --- | --- | --- |
| [`double*`] | **latitude** | Latitude coordinate of the movable object. |
| [`double*`] | **longitude** | Longitude coordinate of the movable object. |
<br/>

___
<a name="C2"/>  

### 1.3.2 Converting from GPS coordinates to X and Y distances

This function converts GPS **degree** coordinates to distance in meters from the **GPS position** to the **Object position** *(he object's position is the origin)* which was defined in the constructor.
```c++
Visualizer::pointXY GPS_to_XY(double latitude, double longitude);
```

**Mathematical formulas** are as follows:
 * `x = longitude_to_meters - Object_longitude_to_meters`
 * `y = latitude_to_meters - Object_latitude_to_meters`

 &nbsp; **Arguments**

| Type | Name | Description |
| --- | --- | --- |
| [`double`] | **latitude** | Latitude coordinate to measure. |
| [`double`] | **longitude** | Longitude coordinate to measure. |

 &nbsp; **Returns**<br/>
 &nbsp; &nbsp; [`Visualizer::pointXY`] &nbsp; | &nbsp; Position in meters with coordinates **X** and **Y** relative to the map's center defined at the constructor. (see [Types](#type-definition) for more information about the `struct`).

 &nbsp; **Errors**<br />
 &nbsp; &nbsp; This will always return x = 0 and y = 0 if the *latitude* and *longitude* were not defined in the constructor.
 
<br/>

___
<a name="C3"/>  

### 1.3.3 Converting from X and Y position to GPS coordinates

This function converts **X** and **Y** position *(in meters)* into GPS **degree** coordinates. The X and Y distances must be relative to the Object, the **X axis** is a line pointing east and the **Y axis** is a line pointing towards north and center at the Object position (defined at the constructor).
```c++
Visualizer::pointLL XY_to_GPS(double x, double y);
```

**Mathematical formulas** are as follows:
 * `latitude = to_GPS_coordinate(Object_latitude_to_meters + y)`
 * `longitude = to_GPS_coordinate(Object_longitude_to_meters + x)`

 &nbsp; **Arguments**

| Type | Name | Description |
| --- | --- | --- |
| [`double`] | **x** | Position **X** to measure relative to the object defined at the constructor. |
| [`double`] | **y** | Position **Y** to measure relative to the object defined at the constructor. |

 &nbsp; **Returns**<br/>
 &nbsp; &nbsp; [`Visualizer::pointLL`] &nbsp; | &nbsp; Coordinates **latitude** and **longitude**. (see [Types](#type-definition) for more information about the `struct`).

 &nbsp; **Errors**<br />
 &nbsp; &nbsp; This will always return `latitude = 0` and `longitude = 0` if the *latitude* and *longitude* were not defined in the constructor.
 
<br/>

___
<a name="C4"/>  

### 1.3.4 Calculating the distance between two GPS coordinates

This function calculates the **distance** between two GPS points, you must define the **start point** *(latitude, longitude)* and **end point** *(latitude, longitude)*.
```c++
double distance(double start_latitude, double start_longitude,
                double end_latitude, double end_longitude);
```

 &nbsp; **Arguments**

| Type | Name | Description |
| --- | --- | --- |
| [`double`] | **start_latitude** | Latitude of point 1. |
| [`double`] | **start_longitude** | Longitude of point 1. |
| [`double`] | **end_latitude** | Latitude of point 2. |
| [`double`] | **end_longitude** | Longitude of point 2. |

 &nbsp; **Returns**<br/>
 &nbsp; &nbsp; [`double`] &nbsp; | &nbsp; Distance in meters from *start point* to *end point*.

 &nbsp; **Errors**<br />
 &nbsp; &nbsp; This will return strange values if you do not introduces proper GPS coordinates.
 
<br/>

___
<a name="C5"/>  

### 1.3.5 Calculating the distance X and Y between two GPS coordinates

This function calculates the **distance X** and **Y** between two GPS points, you must define a **start point** *(latitude, longitude)* and **end point** *(latitude, longitude)*.
```c++
Visualizer::pointXY distances(double start_latitude, double start_longitude,
                              double end_latitude, double end_longitude);
```

 &nbsp; **Arguments**

| Type | Name | Description |
| --- | --- | --- |
| [`double`] | **start_latitude** | Latitude of point 1. |
| [`double`] | **start_longitude** | Longitude of point 1. |
| [`double`] | **end_latitude** | Latitude of point 2. |
| [`double`] | **end_longitude** | Longitude of point 2. |

 &nbsp; **Returns**<br/>
 &nbsp; &nbsp; [`Visualizer::pointXY`] &nbsp; | &nbsp; Distance in meters from *start point* to *end point* separated in **vector components**. (see [Types](#type-definition) for more information about the `struct`).

 &nbsp; **Errors**<br />
 &nbsp; &nbsp; This will return strange values if you do not introduces proper GPS coordinates.
 
 <br/>
 
 ___
<a name="D"/>
 
 ## 1.4 Type Definitions
 
There is two different types of **structures**:

```c++
namespace Visualizer {
  // Position in meters
  union pointXY{
    struct{
      double x; // Position in meters at the X axis (Longitude axis)
      double y; // Position in meters at the Y axis (Latitude axis)
    };
    double data[2];
  };
  
  // Position in degrees
  union pointLL{
    struct{
      double latitude;  // Latitude coordinate in degrees
      double longitude; // Longitude coordinate in degrees
    };
    double data[2];
  };
}
```
<br/>  
___
<a name="E"/>

## 1.5 Getting started
