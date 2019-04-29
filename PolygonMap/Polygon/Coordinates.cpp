//
//  Coordinates.cpp
//  PolygonMap
//
//  Created by Kevin Vallejo on 4/23/19.
//  Copyright © 2019 Vallejo. All rights reserved.
//

#include "Coordinates.hpp"

Coordinates::Coordinates(std::string coordinates):
lon(0),lat(0),hgt(0){

    std::vector<std::string> coords = String::split(coordinates, ",");
    this->lon = std::stod(coords[LON]);
    
    if (coords.size() > LAT)
        this->lat = std::stod(coords[LAT]);
}

