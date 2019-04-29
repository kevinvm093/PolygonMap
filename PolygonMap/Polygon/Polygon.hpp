//
//  Polygon.hpp
//  PolygonMap
//
//  Created by Kevin Vallejo on 4/23/19.
//  Copyright © 2019 Vallejo. All rights reserved.
//

#ifndef Polygon_hpp
#define Polygon_hpp

#include "SubRegion.hpp"

typedef std::vector<SubRegion> SRegionArray;

/* ---------------------------------
 Polygon
 -----------------------------------
 Child object that contains sub regions
 for a specific region.
 ---------------------------------*/
class Polygon : public Region {
    
    SRegionArray regions;

    void setRegions(SRegionArray regions)
    {this->regions = regions;}
    
public:
    
    Polygon() {}

    Polygon(SRegionArray regions)
    { setRegions(regions); }
    
    RegionType type() { return rPolygon; }
    
    SRegionArray& subRegions() { return regions; }
    
};
#endif /* Polygon_hpp */
