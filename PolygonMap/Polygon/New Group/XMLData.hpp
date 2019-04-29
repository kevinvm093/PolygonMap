//
//  XMLData.hpp
//  PolygonMap
//
//  Created by Kevin Vallejo on 4/23/19.
//  Copyright © 2019 Vallejo. All rights reserved.
//

#ifndef XMLData_hpp
#define XMLData_hpp


#include "Region.hpp"

typedef std::shared_ptr<Region>  Region_sp;

/* ---------------------------------
 XMLData
 -----------------------------------
 Contains county name and the data for
 that region(county)
 ---------------------------------*/
class XMLData {
    
    //placemark
    Region_sp   region_ptr;
    std::string regionName;
    
public:
    
    XMLData() {}
    XMLData(std::string name) : regionName(name) { }
    
    std::string name() { return regionName;}
    Region_sp region() { return region_ptr;}
    
    void setRegion(Region_sp region) { this->region_ptr = region;}
    
};
#endif /* XMLData_hpp */
