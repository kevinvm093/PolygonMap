//
//  XMLFolder.hpp
//  PolygonMap
//
//  Created by Kevin Vallejo on 4/24/19.
//  Copyright © 2019 Vallejo. All rights reserved.
//

#ifndef XMLFolder_hpp
#define XMLFolder_hpp

#include <string>
#include <vector>
#include <stdio.h>
#include "XMLData.hpp"

/* ---------------------------------
 XMLFolder
 -----------------------------------
 object that contains the name and data
 stored for the folders inside the kml document.
 ---------------------------------*/
class XMLFolder {
    
    std::string name;
    std::vector<XMLData> data;
    
public:
    
    XMLFolder(){};
    XMLFolder(std::string name):name(name){}
    
    std::string getName() {return name;}
    std::vector<XMLData>& getData() {return data;}
    
};
#endif /* XMLFolder_hpp */
