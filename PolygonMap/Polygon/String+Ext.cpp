//
//  String+Ext.cpp
//  PolygonMap
//
//  Created by Kevin Vallejo on 4/26/19.
//  Copyright © 2019 Vallejo. All rights reserved.
//

#include <stdio.h>
#include "String+Ext.h"

/* ---------------------------------
 
 ---------------------------------*/
namespace String {

    std::vector<std::string> split(const std::string& str, const std::string stop) {

        std::vector<std::string> values;
    
        auto start  = str.find_first_not_of(stop, 0);
        auto pos    = str.find_first_of(stop, start);

        while (std::string::npos != pos || std::string::npos != start) {

            //value found append to array
            values.push_back(str.substr(start, pos - start));

            // update pos
            start   = str.find_first_not_of(stop, pos);
            pos     = str.find_first_of(stop, start);
        }

        return values;
    }
   
}
