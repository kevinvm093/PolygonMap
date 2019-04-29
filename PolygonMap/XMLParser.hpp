//
//  XMLParser.hpp
//  PolygonMap
//
//  Created by Kevin Vallejo on 4/26/19.
//  Copyright © 2019 Vallejo. All rights reserved.
//

#ifndef XMLParser_hpp
#define XMLParser_hpp

#include <map>
#include <stack>
#include <vector>
#include <stdio.h>
#include <fstream>
#include "Polygon/Polygon.hpp"
#include "rapidxml/rapidxml.hpp"
#include "Polygon/New Group/ParsePath.h"
#include "Polygon/New Group/XMLFolder.hpp"

/* ---------------------------------
 XMLReader
 -----------------------------------
 object that reads in a KML document
 using the rapidXML library and stores
 the data into memory.
 ---------------------------------*/

class XMLReader {
 
    bool                        open;
    
    ParsePath                   loc; // kml tags for cleaner code.
    XMLFolder                   curFolder;
    
    std::string                 path; // path to current child node
    std::string                 curData; //current countys name
    std::ifstream               XMLFile;
    
    std::vector<XMLFolder>      folders;
    std::shared_ptr<Region>     curRegion;
    std::stack<std::string>     pathStack; // keeps track of traversal depth
    
    /* ---------------------------------
     Private member functions
     ---------------------------------*/
    
    size_t getSize();
    void finishNode();
    void saveData(char* data);
    bool parsePath(std::string);
    void parseXML(rapidxml::xml_node<> *parentNode);
    
public:
    
    XMLReader(){};
    XMLReader(std::string XMLPath);
    
    /* ---------------------------------
     
     ---------------------------------*/
    
    bool isOpen() {return open;};
    
    // recursive function that reads in the kml data and stores it into memory.
    bool readXML();
    std::vector<XMLFolder>& getFolders() {return folders;}
};
#endif /* XMLParser_hpp */
