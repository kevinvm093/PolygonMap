//
//  XMLParser.cpp
//  PolygonMap
//
//  Created by Kevin Vallejo on 4/26/19.
//  Copyright © 2019 Vallejo. All rights reserved.
//

#include "XMLParser.hpp"

#include <map>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <iostream>


/* ---------------------------------
XMLReader::XMLReader(...)
 -----------------------------------
 Opens XML document
 ---------------------------------*/
XMLReader::XMLReader(std::string XMLPath) {
    
    XMLFile.open(XMLPath, std::ios::in|std::ios::binary);
    
    if (!XMLFile.is_open()) {
        
        open = false;
        std::cout << "Error in opening XML." << std::endl;
        return;
    }
    open = true;
}
/* ---------------------------------
XMLReader::readXML(...)
 ----------------------------------
 a. create Buffer
    a.1 initialize buffer with size of XML file
 b. read in the data from XML file and copy it to buffer
 c. using rapidXML library create a xml_document and parse the XML buffer
 d. extract the information from xml_doc begining with its first node.
 ---------------------------------*/
bool XMLReader::readXML() {
    
    std::cout << "Loading data from file..." << std::endl;
    
    char* buffer        = NULL;
    size_t bufferSize   = getSize();
    buffer              = new char[bufferSize];
    memset(buffer, 0, bufferSize);
    
    XMLFile.read(buffer, bufferSize);
    
    rapidxml::xml_document<> doc;
    doc.parse<0>(buffer);
    
    parseXML(doc.first_node());
    std::cout << "Finished extracting XML data" << std::endl;
    return true;
}
/* ---------------------------------
 getSize()
 -----------------------------------
 gets size of the XML file to be used when intializing
 the buffer size.
 ---------------------------------*/
size_t XMLReader::getSize() {
    
    XMLFile.seekg(0, std::ios::end);
    size_t size = (size_t)XMLFile.tellg() + 1;
    XMLFile.seekg(0, std::ios::beg);
    
    return size;
}

/* ---------------------------------
 rapidxml::xml_node<char> * XMLReader::parseXML(...)
 -----------------------------------
 a. for every parent passed through, traverse through each of their children.
    a.1 if child is of type data, it is not needed to go any deeper.
        a.1.1 pop current path from stack.
        a.1.2 terminate current recursive function
                and continue with their parents's next sibling.
 
    a.2 set path to child equal to path of parent
    a.3 append current child's name to path
    a.4 push current path to pathStack
    a.5 save value stored inside child (if any).
    a.6 traverse deeper into current child's nodes (children)
 
 b. call finishNode once each sibling has been visted.
 c. pop last visted sibling's path from stack and terminate current recursive func.
 ---------------------------------*/
void  XMLReader::parseXML(rapidxml::xml_node<> *parentNode) {
    
    for (auto child = parentNode->first_node(); child; child = child->next_sibling()) {
        
        //base case
        if (child->type() == rapidxml::node_data) {
            
            pathStack.pop();
            return;
        }
        
        if (!pathStack.empty()) {
            
            // sets path to parent
            path = pathStack.top();
            path.append(".");
        }
        
        // childs path
        path.append(child->name());
        pathStack.push(path);
        
        if (child->value() != NULL)
            saveData(child->value());
        
        // traverse childs children
        parseXML(child);
    }
    
    finishNode();
    
    // pop path to last sibling visited.
    if (!pathStack.empty()) {
        
        path = pathStack.top();
        pathStack.pop();
    }
    return;
}

/* ---------------------------------
 parsePath(...)
 -----------------------------------
 finds if current path is equal to
 destination passed through param.
 ---------------------------------*/
bool XMLReader::parsePath(std::string dest) {
    
    size_t pos = path.rfind(dest);
    
    if (pos == std::string::npos)
        return false;
    
    if ((path.length() - pos) == dest.length())
        return true;
    
    return false;
}

/* ---------------------------------
 XMLReader::saveData(...)
 ----------------------------------
 a. if parsed path leads to folder
    a.1 initialize a new folder
 
 b. if parsed path leads to placemark
    b.1 save current current countys name
 
 c. if parsed path leads to polygon
    c.1 create a new region if curRegion is NULL
 
 d. if parsed path leads to coords
    d.1 create a new polygon
    d.2 parse coordniates
    d.3 seperate by sub regions
    d.5 add sub regions to polygon
 ---------------------------------*/
void XMLReader::saveData(char *data){
    
    if (parsePath(loc.newFolder)) {
        
        curFolder           = XMLFolder(data);
        
    } else if (parsePath(loc.placemark)) {
      
        curData             = data;
        
    } else if (parsePath(loc.polygon) || parsePath(loc.multiPoly)){
        
        if (curRegion.get() == NULL) {
            
            auto polygon    = std::make_shared<Polygon>();
            curRegion       = std::dynamic_pointer_cast<Region, Polygon>(polygon);
        }
    } else if (parsePath(loc.coordinates)) {
        
        if (curRegion.get() == NULL) {
            
            std::cout << "Bugs!" << std::endl;
            return;
        }
        auto polygon        = std::dynamic_pointer_cast<Polygon, Region>(curRegion);
        
        auto coordStrings   = String::split(data);
        std::vector<Coordinates> coords;
        
        for(auto cs : coordStrings)
            coords.push_back(Coordinates(cs));
        
        SubRegion subReg(coords);
        polygon->subRegions().push_back(subReg);
    }
}
/* ---------------------------------
 XMLReader::finishNode()
 -----------------------------------
 
 ---------------------------------*/
void XMLReader::finishNode() {
    
    if (parsePath(loc.folder)){
        
        // Save the current folder
        std::cout << "Folder done." << std::endl;
        folders.push_back(curFolder);
    }
    else if (parsePath(loc.polygon) || parsePath(loc.multiPoly)){
        
        // Save the current geometry to a new placemark
        XMLData placemark(curData);
        placemark.setRegion(curRegion);
        
        curFolder.getData().push_back(placemark);
        std::cout << "finished:" << curData << std::endl;
        // Clear the current geometry
        curRegion.reset();
    }
    
}


