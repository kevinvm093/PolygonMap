//
//  main.cpp
//  PolygonMap
//
//  Created by Kevin Vallejo on 4/23/19.
//  Copyright © 2019 Vallejo. All rights reserved.
//

#include <iostream>
#include "XMLParser.hpp"
#include "XMLWriter.hpp"
#include "Polygon/Bounds.hpp"

int main(int argc, const char * argv[]) {
   
    /* ---------------------------------
     a. open XML document
     b. read in data from file using rapidxml library
     c. calculate bounds for every county
     d. append new data to writer object
     d. create and write XML file using new data
     ---------------------------------*/
    
    FilePath file;
    auto doc = XMLReader(file.inputFile);
    
    if (doc.isOpen())
        doc.readXML();
    
    XMLFolder outputFolder("County Extents");
    
    for (auto folder : doc.getFolders()) {
        
        for (auto data : folder.getData()) {
            
            auto curData = data;
            auto curRegion = curData.region();
            
            if (curRegion->type() == rPolygon) {
                
                /* ---------------------------------
                 a. calculate bounds for current county
                 b. generate a new polygon using bounds
                 c. intialize a new placemark using county name and new polygon
                 d. insert the new placemark in the output XML structure
                 ---------------------------------*/
                
                Polygon_sp  polygon      = std::dynamic_pointer_cast
                <Polygon,Region>(curRegion);
                
                Bounds      bounds(polygon->subRegions());
                Polygon_sp  newPolygon   = bounds.drawPolygon();
                
                Region_sp newRegion  = std::dynamic_pointer_cast
                <Region, Polygon>(newPolygon);
                
                XMLData newPlacemark(curData.name());
                newPlacemark.setRegion(newRegion);
                
                outputFolder.getData().push_back(newPlacemark);
            }
        }
    }
    
    XMLWriter output(file.outputFile);
    output.getFolders().push_back(outputFolder);
    output.write();
    
    std::cout << "Press return." << std::endl;
    std::cin.get();
    return 0;
}

