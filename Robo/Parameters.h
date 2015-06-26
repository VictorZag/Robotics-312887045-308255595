/* 
 * File:   Parameters.h
 * Author: colman
 *
 * Created on June 26, 2015, 6:30 AM
 */

#ifndef PARAMETERS_H
#define	PARAMETERS_H
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <map>

using namespace std;


class Parameters {
public:
    Parameters(char* p_filePath);
    Parameters(const Parameters& orig);
    virtual ~Parameters();
private:
    
    std::string _mapFile;
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

#endif	/* PARAMETERS_H */

