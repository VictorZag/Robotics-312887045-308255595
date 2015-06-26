/* 
 * File:   ConfigurationManager.cpp
 * Author: colman
 * 
 * Created on June 26, 2015, 2:53 AM
 */

#include "ConfigurationManager.h"

ConfigurationManager::ConfigurationManager(char* p_filePath) {
    s_mapStringValues["map"] = map;
    s_mapStringValues["startLocation"] = startLocation;
    s_mapStringValues["goal"] = goal;
    s_mapStringValues["robotSize"] = robotSize;
    s_mapStringValues["MapResolutionCM"] = MapResolutionCM;
    s_mapStringValues["GridResolutionCM"] = GridResolutionCM;
    size_t endpos;
    ifstream myfile(p_filePath);
    string line, propery,temp;
    int found, counter = 0;
    float robotLentgh, robotWidth;
    stringstream ssLocation,ssGoal,ssrobotSize;
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
                    endpos = line.find_last_not_of("\r");
                    if( string::npos != endpos )
                    {
                        _mapFile = line.substr(pos + 1, endpos -3 );
                    }
                    break;
                case (startLocation):
                    counter = 0;
                    ssLocation << line;
                    while(std::getline(ssLocation, temp,' ')) {
                        
                        if(std::stringstream(temp)>>found)
                        {
                            if (counter == 0)
                                _startLocationX = (float)found;
                             if (counter == 1)
                                _startLocationY = (float)found;
                             if (counter == 2)
                                _startAngle = (float)found;
                            
                            counter++;
                        }
                    }
                        
                    break;
                    
                case (goal):
                    counter = 0;
                    ssGoal << line;
                    while(std::getline(ssGoal, temp,' ')) {
                        
                        if(std::stringstream(temp)>>found)
                        {
                            if (counter == 0)
                                _goalLocationX = (float)found;
                             if (counter == 1)
                                _goalLocationY = (float)found;
                            
                            counter++;
                        }
                    }
                    break;
                case (robotSize):
                    counter = 0;
                    ssrobotSize << line;
                    while(std::getline(ssrobotSize, temp,' ')) {
                        
                        if(std::stringstream(temp)>>found)
                        {
                            if (counter == 0)
                                robotLentgh = (float)found;
                             if (counter == 1)
                                robotWidth = (float)found;
                            counter++;
                        }
                    }

                    _robotSize = max(robotLentgh, robotWidth);
                    
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



ConfigurationManager::ConfigurationManager(const ConfigurationManager& orig) {
}

ConfigurationManager::~ConfigurationManager() {
}

string ConfigurationManager::GetMapFilePath(){return _mapFile;}
float ConfigurationManager::GetStartLocationX(){return _startLocationX;}
float ConfigurationManager::GetStartLocationY(){return _startLocationY;}
float ConfigurationManager::GetStartAngle(){return _startAngle;}
float ConfigurationManager::GetGoalLocationX(){return _goalLocationX;}
float ConfigurationManager::GetGoalLocationY(){return _goalLocationY;}
float ConfigurationManager::GetRobotSize(){return _robotSize;}
float ConfigurationManager::GetMapResolutionCM(){return _mapResolutionCM;}
float ConfigurationManager::GetGridResolutionCM(){return _gridResolutionCM;}

