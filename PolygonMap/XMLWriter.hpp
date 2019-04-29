//
//  XMLWriter.hpp
//  PolygonMap
//
//  Created by Kevin Vallejo on 4/28/19.
//  Copyright © 2019 Vallejo. All rights reserved.
//

#ifndef XMLWriter_hpp
#define XMLWriter_hpp

#include <stdio.h>
#include "XMLParser.hpp"
#include "Helpers.hpp"
#include "rapidxml/rapidxml_print.hpp"


class XMLWriter {
    
    Helper                      helper; // helper incharge of parsing coordinates
    StyleTags                   styleTags; //StyleTag constants
    std::ofstream               newFile; // new XML file to write data
    std::vector<XMLFolder>      folders; // folders of containing xmlData
    rapidxml::xml_document<>    doc; // rapidXML library
    
    
    /* ---------------------------------
     XMLWriter
     -----------------------------------
     Object that writes calculated bounds
     into a new XMLFile.
     ---------------------------------*/
    
    void writeStyleTags(rapidxml::xml_node<>* data);
    void writePolygon(rapidxml::xml_node<>* curNode, std::shared_ptr<Polygon> polygon);

public:
    
    XMLWriter(std::string filename);
    
    //writes data into file in XML format
    void write();
    std::vector<XMLFolder>& getFolders() {return folders;}
};

#endif /* XMLWriter_hpp */
