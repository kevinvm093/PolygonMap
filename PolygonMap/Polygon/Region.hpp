//
//  Region.hpp
//  PolygonMap
//
//  Created by Kevin Vallejo on 4/23/19.
//  Copyright © 2019 Vallejo. All rights reserved.
//

#ifndef Region_hpp
#define Region_hpp

#include "Coordinates.hpp"

enum RegionType {rUnknown, rPolygon};
typedef std::vector<Coordinates> CoordinatesArray;

/* ---------------------------------
 
 ---------------------------------*/
class Region {
    
protected:
    
    Region() {}
    virtual ~Region() {}
    
public:
    
    virtual RegionType type() = 0;
};
#endif /* Region_hpp */
