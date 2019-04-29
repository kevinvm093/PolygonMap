//
//  String+Ext.h
//  PolygonMap
//
//  Created by Kevin Vallejo on 4/23/19.
//  Copyright © 2019 Vallejo. All rights reserved.
//

#ifndef String_Ext_h
#define String_Ext_h

#include <string>
#include <vector>

namespace String {
    
    // splits a string seperated by a ","
    std::vector<std::string> split(const std::string& str, const std::string stop = " ");
}
#endif /* String_Ext_h */
