//
//  Coordinates.hpp
//  PolygonMap
//
//  Created by Kevin Vallejo on 4/23/19.
//  Copyright © 2019 Vallejo. All rights reserved.
//

#ifndef Coordinates_hpp
#define Coordinates_hpp

#include <string>
#include <vector>
#include "String+Ext.h"
#include "ConstKeys.hpp"

/* ---------------------------------
 Coordinates
 -----------------------------------
 Object that contains the x & y coords
 ---------------------------------*/
class Coordinates {
    
    double lon, lat, hgt;
    
public:
    
    /* ---------------------------------
     Constructors
     ---------------------------------*/
    Coordinates():lon(0),lat(0),hgt(0){ }
    Coordinates(double lon, double lat)
        :lon(lon),lat(lat),hgt(0){ };
    Coordinates(std::string coordinates);
    
    /* ---------------------------------
     Getters
     ---------------------------------*/
    double getLon() {return lon;}
    double getLat() {return lat;}
    double getHgt() {return hgt;}
    
};



#endif /* Coordinates_hpp */
