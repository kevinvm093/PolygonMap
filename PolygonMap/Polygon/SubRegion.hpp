//
//  SubRegion.hpp
//  PolygonMap
//
//  Created by Kevin Vallejo on 4/23/19.
//  Copyright © 2019 Vallejo. All rights reserved.
//

#ifndef SubRegion_hpp
#define SubRegion_hpp


#include "Region.hpp"
#include <vector>

class SubRegion {
    
    CoordinatesArray area;
    
public:
    /* ---------------------------------
     Constructors
     ---------------------------------*/
    SubRegion(){}
    SubRegion(CoordinatesArray area) {setArea(area);}
    
    /* ---------------------------------
     Getters / Setters
     ---------------------------------*/
    CoordinatesArray& getArea() { return area;}
    void setArea(CoordinatesArray area) { this->area = area;}
    
    
};
#endif /* SubRegion_hpp */
