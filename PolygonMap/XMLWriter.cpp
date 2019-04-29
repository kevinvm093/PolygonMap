//
//  XMLWriter.cpp
//  PolygonMap
//
//  Created by Kevin Vallejo on 4/28/19.
//  Copyright © 2019 Vallejo. All rights reserved.
//

#include "XMLWriter.hpp"
#include <iostream>


XMLWriter::XMLWriter(std::string filename) {
    
    newFile.open(filename, std::ios::out);
    
    if (!newFile.is_open()) {
        std::cout << "cant open new file" << std::endl;
        return;
    }
}

/* ---------------------------------
 
 ---------------------------------*/
void XMLWriter::write() {
    
    auto rootNode           = doc.allocate_node(rapidxml::node_element, "kml");
    auto XMLRootNodeAttr    = doc.allocate_attribute("xmlns", "http://www.opengis.net/kml/2.2");
    auto XMLReaderument     = doc.allocate_node(rapidxml::node_element, "Document");
    
    doc.append_node(rootNode);
    rootNode->append_attribute(XMLRootNodeAttr);
    rootNode->append_node(XMLReaderument);
    
    //folders
    for(auto folder : folders) {
        
        auto XMLFolder      = doc.allocate_node(rapidxml::node_element, "Folder");
        XMLReaderument->append_node(XMLFolder);
        
        auto name           = doc.allocate_string(folder.getName().c_str());
        auto XMLFolderName  = doc.allocate_node(rapidxml::node_element, "name", name);
        XMLFolder->append_node(XMLFolderName);
        
        //regions
        for(auto data : folder.getData()) {
            
            auto XMLPlcmrk  = doc.allocate_node(rapidxml::node_element, "Placemark");
            XMLFolder->append_node(XMLPlcmrk);
            
            auto regionName = doc.allocate_string(data.name().c_str());
            auto plcmrkName = doc.allocate_node(rapidxml::node_element, "name", regionName);
            
            XMLPlcmrk->append_node(plcmrkName);
            
            writeStyleTags(XMLPlcmrk);
            
            Region_sp reg = data.region();
            
            if (reg->type() == rPolygon) {
                
                auto polygon = std::dynamic_pointer_cast<Polygon, Region>(reg);
                writePolygon(XMLPlcmrk, polygon);
            }
        }
    }
    
    newFile << "<?xml version=\"1.0\" encoding=\"utf-8\" ?>" << std::endl;
    std::cout << doc << std::endl;
    newFile << doc;
    
    std::cout << "Finished." << std::endl;
    
}

/* ---------------------------------
 
 ---------------------------------*/
void XMLWriter::writeStyleTags(rapidxml::xml_node<> *data) {
    
//    for(auto tag : styleTags.tags) {
//
//        rapidxml::xml_node<>* style;
//
//        if (tag == "color")
//            style   = doc.allocate_node(rapidxml::node_element,
//                                      tag.c_str(),styleTags.color.c_str());
//
//         else if (tag == "fill")
//            style   = doc.allocate_node(rapidxml::node_element,
//                                      tag.c_str(),styleTags.fill.c_str());
//         else
//            style   = doc.allocate_node(rapidxml::node_element, tag.c_str());
//
//        std::cout << tag.c_str() << std::endl;
//        data->append_node(style);
//    }
    auto XMLStyle = doc.allocate_node(rapidxml::node_element, "Style");
    data->append_node(XMLStyle);
    
    rapidxml::xml_node<>* XMLLineStyle = doc.allocate_node(rapidxml::node_element, "LineStyle");
    XMLStyle->append_node(XMLLineStyle);
    rapidxml::xml_node<>* XMLLineStyleColor = doc.allocate_node(rapidxml::node_element, "color", "ff0000ff");
    XMLLineStyle->append_node(XMLLineStyleColor);
    
    rapidxml::xml_node<>* XMLPolyStyle = doc.allocate_node(rapidxml::node_element, "PolyStyle");
    XMLStyle->append_node(XMLPolyStyle);
    rapidxml::xml_node<>* XMLPolyStyleFill = doc.allocate_node(rapidxml::node_element, "fill", "0");
    XMLPolyStyle->append_node(XMLPolyStyleFill);
    
}

/* ---------------------------------
 
 ---------------------------------*/
void XMLWriter::writePolygon(rapidxml::xml_node<> *curNode,
                             std::shared_ptr<Polygon> polygon) {
    
    if (polygon.get() == NULL)
        return;
    
    rapidxml::xml_node<>* XMLRegionNode = NULL;
    
    if (polygon->subRegions().size() == 1)
        XMLRegionNode           = curNode;
    
     else if (polygon->subRegions().size() > 1) {
        
        auto XMLMultiGeometry   = doc.allocate_node(rapidxml::node_element, "MultiGeometry");
        curNode->append_node(XMLMultiGeometry);

        XMLRegionNode           = XMLMultiGeometry;
         
    } else
        std::cout << "there are no sub regions inside polygon" << std::endl;
    
    for(auto sb : polygon->subRegions()) {
        
        auto newPoly        = doc.allocate_node(rapidxml::node_element, "Polygon");
        XMLRegionNode->append_node(newPoly);
        
        //outerBoundaryIs.LinearRing.coordinates
        auto outerBoundary  = doc.allocate_node(rapidxml::node_element, "outerBoundaryIs");
        newPoly->append_node(outerBoundary);
        
        auto linearRing     = doc.allocate_node(rapidxml::node_element, "LinearRing");
        outerBoundary->append_node(linearRing);
        
        char * coordString  = doc.allocate_string(helper.getCoords(sb.getArea()).c_str());
        auto xmlCoords      = doc.allocate_node(rapidxml::node_element, "coordinates", coordString);
        linearRing->append_node(xmlCoords);
        
    }
    
}
