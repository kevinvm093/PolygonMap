//
//  Helpers.hpp
//  PolygonMap
//
//  Created by Kevin Vallejo on 4/28/19.
//  Copyright © 2019 Vallejo. All rights reserved.
//

#ifndef Helpers_hpp
#define Helpers_hpp

#include <stdio.h>
#include <sstream>
#include <iomanip>
#include "Polygon/Coordinates.hpp"

/* ---------------------------------
 Helper
 ----------------------------------
 Object that parses coordinates 
 ---------------------------------*/
struct Helper {
    
    std::string formatDouble(double x);
    std::string getCoords(Coordinates coords);
    std::string getCoords(std::vector<Coordinates> coords);
};

#endif /* Helpers_hpp */
