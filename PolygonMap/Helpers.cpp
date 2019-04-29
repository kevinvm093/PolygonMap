//
//  Helpers.cpp
//  PolygonMap
//
//  Created by Kevin Vallejo on 4/28/19.
//  Copyright © 2019 Vallejo. All rights reserved.
//

#include "Helpers.hpp"
#include <string>

/* ---------------------------------
 
 ---------------------------------*/
std::string Helper::getCoords(Coordinates coord) {
    
    std::string coordString;
    coordString = formatDouble(coord.getLon());
    coordString.append(",");
    coordString.append(formatDouble(coord.getLat()));
    
    if (coord.getHgt() != 0.0) {
        
        coordString.append(",");
        coordString.append(formatDouble(coord.getHgt()));
    }
    return coordString;
}

/* ---------------------------------
 
 ---------------------------------*/
std::string Helper::getCoords(std::vector<Coordinates> coords) {
    
    std::string coordList;
    coordList.reserve(coords.size() * (40)); 
    
    for (auto coord : coords) {
        
        if (!coordList.empty())
            coordList.append(" ");
        
        coordList.append(getCoords(coord));
    }
    return coordList;
}

/* ---------------------------------
 
 ---------------------------------*/
std::string Helper::formatDouble(double x) {
    
    std::stringstream s;
    const int maxDigits = 1 + std::numeric_limits<double>::digits10;
    s << std::setprecision(maxDigits) << x;
    return s.str();
}


