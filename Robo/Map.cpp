/* 
 * File:   Map.cpp
 * Author: colman
 * 
 * Created on June 26, 2015, 2:50 AM
 */

#include "Map.h"

Map::Map(char* parameters) {
    ifstream myfile(parameters);
    string line;
    
    while (getline(myfile, line))
    {
        unsigned pos = line.find(':');
        if (pos != string::npos)
        {
            switch (line.substr(0, pos - 1))
            {
                case 'map':
                    _mapFile = line.substr( pos + 1);
                    break;
                    
                case 'robotSize' :
                    unsigned startPos = 0;                
                    unsigned spacePos = 0;
                    while (spacePos = 0)
                        startPos = spacePos + 1;
                        spacePos = line.find(' ');
                    _robotSize = max((float)atof(line.substr(startPos, spacePos - 1)), (float)atof(line.substr( spacePos + 1)));
                    break;
                    
                case 'MapResolutionCM':
                    _mapResolutionCM = (float)atof(line.substr( pos + 1));
                    break;
                    
                case 'GridResolutionCM':
                    _gridResolutionCM = (float)atof(line.substr( pos + 1));
                    break;
                    
                    
            }
        }
    }
}

Map::Map(const Map& orig) {
}

Map::~Map() {
}

