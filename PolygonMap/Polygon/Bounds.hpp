//
//  Bounds.hpp
//  PolygonMap
//
//  Created by Kevin Vallejo on 4/28/19.
//  Copyright © 2019 Vallejo. All rights reserved.
//

#ifndef Bounds_hpp
#define Bounds_hpp

#include <stdio.h>
#include "Bounds.hpp"
#include "Polygon.hpp"

// typedef for cleaner / easier to read code
typedef std::vector<SubRegion>      subRegions;
typedef std::shared_ptr<Polygon>    Polygon_sp;
typedef std::shared_ptr<Region>     Region_sp;

class Bounds {
    
    Polygon_sp  poly;
    
    double  minX, minY,
            maxX, maxY;
    
    /* ---------------------------------
     Bounds
     -----------------------------------
     Object that calculates and holds X & Y
     coordnimates of Polygons
     ---------------------------------*/
    
public:
    
    Bounds(subRegions& polyRings);
    
    Polygon_sp drawPolygon(); // generates polygons vertices
    
    double getMaxX() {return maxX;}
    double getMaxY() {return maxY;}
    double getMinX() {return minX;}
    double getMinY() {return minY;}
    
};

#endif /* Bounds_hpp */
