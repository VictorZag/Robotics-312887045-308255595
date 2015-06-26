/* 
 * File:   Parameters.cpp
 * Author: colman
 * 
 * Created on June 26, 2015, 6:30 AM
 */

#include "Parameters.h"



Parameters::Parameters(char* p_filePath) {
    s_mapStringValues["map"] = map;
    s_mapStringValues["startLocation"] = startLocation;
    s_mapStringValues["goal"] = goal;
    s_mapStringValues["robotSize"] = robotSize;
    s_mapStringValues["MapResolutionCM"] = MapResolutionCM;
    s_mapStringValues["GridResolutionCM"] = GridResolutionCM;
    
    ifstream myfile(p_filePath);
    string line, propery;
        int startPos = 0;                
    int spacePos = 0;
    
    while (getline(myfile, line))
    {
        unsigned pos = line.find(':');
        if (pos != string::npos)
        {
            propery = line.substr(0, pos);
            switch (s_mapStringValues[propery])
            {
                case (map):
                    _mapFile = line.substr( pos + 1);
                    break;
                    
                case (robotSize):
                    startPos = 0;      
                    spacePos = 0;
                    while (spacePos = 0)
                        startPos = spacePos + 1;
                        spacePos = line.find(' ');
                    _robotSize = max((float)(atof(line.substr(startPos, spacePos - 1).c_str())),
                                        (float)atof(line.substr( spacePos + 1).c_str())) ;
                    break;
                case (MapResolutionCM):
                    _mapResolutionCM = (float)(atof(line.substr( pos + 1).c_str()));
                    break;
                    
                case (GridResolutionCM):
                    _gridResolutionCM = (float)(atof(line.substr( pos + 1).c_str()));
                    break;
                default:
                    break;
                    
            }
        }
    }
    }



Parameters::Parameters(const Parameters& orig) {
}

Parameters::~Parameters() {
}

string Parameters::GetMapFilePath(){return _mapFile;}
float Parameters::GetStartLocationX(){return _startLocationX;}
float Parameters::GetStartLocationY(){return _startLocationY;}
float Parameters::GetStartAngle(){return _startAngle;}
float Parameters::GetGoalLocationX(){return _goalLocationX;}
float Parameters::GetGoalLocationY(){return _goalLocationY;}
float Parameters::GetRobotSize(){return _robotSize;}
float Parameters::GetMapResolutionCM(){return _mapResolutionCM;}
float Parameters::GetGridResolutionCM(){return _gridResolutionCM;}


