//
//  Bounds.cpp
//  PolygonMap
//
//  Created by Kevin Vallejo on 4/28/19.
//  Copyright © 2019 Vallejo. All rights reserved.
//

#include "Bounds.hpp"

/* ---------------------------------
 Constructor Bounds(...)
 ------------------------------------
 a. loop through each area/ring for county passed through the param.
 b. use the ring's coordniates to find the bounds of the enclosing polygon
    b.1. if data members are NULL initialize them with the current coordnates
    b.2 compare each coordinate with self and update if needed.
 ---------------------------------*/
Bounds::Bounds(subRegions& polyRings):
maxX(0.0), maxY(0.0), minX(0.0), minY(0.0) {
    
    for (auto area : polyRings) {
        
        for (auto coords : area.getArea()) {
            
            if (this->minX == 0 && this->minY == 0
                && this->maxX == 0 && this->maxX == 0) {
                
                // intialize data members
                this->maxX = coords.getLon();
                this->minX = coords.getLon();
                this->maxY = coords.getLat();
                this->minY = coords.getLat();
            }
            
            // compare current 'x' coord with self
            if (coords.getLon() > this->maxX)
                this->maxX = coords.getLon();
            else if (coords.getLon()  < this->minX)
                this->minX = coords.getLon();
            
            // compare current 'y' coord with self
            if (coords.getLat() > this->maxY)
                this->maxY = coords.getLat();
            else if (coords.getLat() < this->minY)
                this->minY = coords.getLat();
            
        }
    }
}

/* ---------------------------------
 Bounds::convertToPolygon()
 -----------------------------------
 a. using bounds initialize each vertex of polygon
 b. append vertices to array of coordinates
 c. Generate new polygon using coordinates
 d. return generated polygon
 ---------------------------------*/
std::shared_ptr<Polygon> Bounds::drawPolygon() {
    
    //vertices
    auto minXMinY = Coordinates(this->minX, this->minY);
    auto minXMaxY = Coordinates(this->minX, this->maxY);
    auto maxXmaxY = Coordinates(this->maxX, this->maxY);
    auto maxXminY = Coordinates(this->maxX, this->minY);
    
    std::vector<Coordinates> coords;
    coords.push_back(minXMinY);
    coords.push_back(minXMaxY);
    coords.push_back(maxXmaxY);
    coords.push_back(maxXminY);
    coords.push_back(minXMinY);
    
    subRegions pRings;
    pRings.push_back(SubRegion(coords));
    
    // new Polygon
    return std::make_shared<Polygon>(Polygon(pRings));
}





