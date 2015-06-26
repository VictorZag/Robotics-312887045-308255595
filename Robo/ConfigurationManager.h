/* 
 * File:   ConfigurationManager.h
 * Author: colman
 *
 * Created on June 26, 2015, 2:53 AM
 */

#ifndef CONFIGURATIONMANAGER_H
#define	CONFIGURATIONMANAGER_H
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <sstream>

using namespace std;


class ConfigurationManager {
public:
    ConfigurationManager(char* p_filePath);
    ConfigurationManager(const ConfigurationManager& orig);
    virtual ~ConfigurationManager();
    
    string GetMapFilePath();
    float GetStartLocationX();
    float GetStartLocationY();
    float GetStartAngle();
    float GetGoalLocationX();
    float GetGoalLocationY();
    float GetRobotSize();
    float GetMapResolutionCM();
    float GetGridResolutionCM();
private:
    
    string _mapFile;
    float _startLocationX, _startLocationY, _startAngle;
    float _goalLocationX, _goalLocationY;
    float _robotSize,_mapResolutionCM,_gridResolutionCM;
    
        // Value-Defintions of the different String values
    enum StringValue { map,
                        startLocation,
                        goal,
                        robotSize,
                        MapResolutionCM,
                        GridResolutionCM };
                          
    // Map to associate the strings with the enum values
    std::map<std::string, StringValue> s_mapStringValues;

};

#endif	/* CONFIGURATIONMANAGER_H */

