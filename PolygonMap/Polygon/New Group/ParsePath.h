//
//  ParsePath.h
//  
//
//  Created by Kevin Vallejo on 4/26/19.
//

#ifndef ParsePath_h
#define ParsePath_h
#include <string>

/* ---------------------------------
 ParsePath
 -----------------------------------
 Object that contains tags in the KML
 file.
 ---------------------------------*/

struct ParsePath {
    
    const std::string folder       = "Folder";
    const std::string newFolder    = "Folder.name";
    const std::string placemark    = "Placemark.name";
    const std::string polygon      = "Placemark.Polygon";
    const std::string multiPoly    = "Placemark.MultiGeometry.Polygon";
    const std::string coordinates  = "Polygon.outerBoundaryIs.LinearRing.coordinates";
    const std::string simpleData   = "Placemark.ExtendedData.SchemaData.SimpleData";

};

/* ---------------------------------
 StyleTags
 -----------------------------------
 Object that contains tags in the KML
 file.
 ---------------------------------*/
struct StyleTags {
    
   
    const std::string color = "ff0000ff";
    const std::string fill  = "0";
    std::vector<std::string> tags = {"Style","LineStyle",
                                    "color","PolyStyle","fill"};
};

/* ---------------------------------
 FilePath
 -----------------------------------
 Object that contains in/output file
 destinations on MY computer.
 ---------------------------------*/
struct FilePath {
    
    const std::string inputFile = "/Users/kevinvallejo/Desktop/Objective C/PolygonMap/PolygonMap/statecounties.kml";
    
    const std::string outputFile = "/Users/kevinvallejo/Desktop/Objective C/PolygonMap/PolygonMap/output.kml";

};
#endif /* ParsePath_h */
