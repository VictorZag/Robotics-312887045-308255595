/*
 * Robot.cpp
 *
 *  Created on: May 26, 2015
 *      Author: colman
 */

#include "Robot.h"
#define PI 3.14159265
#define RWX 40*550
#define RWY 20*380

Robot::Robot(char* p_filePath,string ip, int port) : _pc(ip, port), _pp(&_pc), _lp(&_pc) {
	// TODO Auto-generated constructor stub
        ConfigurationManager* cm = new ConfigurationManager(p_filePath);
        _pp.SetMotorEnable(true);
        _pp.SetOdometry(cm->GetStartLocationX()/550*40,-cm->GetStartLocationY()/380*20,dtor(cm->GetStartAngle()));
        std::cout << dtor(cm->GetStartAngle())<<"          " <<getYaw() << std::endl;
        for(int i = 0; i < 20 ; i++)
        {
            _pc.Read();
            std::cout << dtor(cm->GetStartAngle())<<"          " <<getYaw() << std::endl;
        }
        
        _pp.SetOdometry(cm->GetStartLocationX()/550*40,-cm->GetStartLocationY()/380*20,dtor(cm->GetStartAngle()));
        std::cout << dtor(cm->GetStartAngle())<<"          " <<getYaw() << std::endl;
        _lastX = getX();
	_lastY = getY();
	_lastYaw = getYaw();
}

Robot::~Robot() {
	// TODO Auto-generated destructor stub
}

void Robot::setSpeed(float linear, float angular)
{
	_pp.SetSpeed(linear, angular);
}

float Robot::getX()
{
	return _pp.GetXPos()/40*550 +9;
}

float Robot::getY()
{
	return _pp.GetYPos()/20*380;
}

float Robot::getYaw()
{
	return _pp.GetYaw();
}

float Robot::getOldYaw()
{
	return _lastYaw;
}

void Robot::setOldYaw(float yaw)
{
	_lastYaw = yaw;
}

float* Robot::getLaserScan()
{
	float *scan = new float[_lp.GetCount()];
	for (unsigned int i = 0; i < _lp.GetCount(); i++)
	{
		scan[i] = _lp[i];
	}
	return scan;
}

int Robot::deg_to_index(double deg)
{
    return (deg + 120) / 0.36;
}

void Robot::read()
{
    _pc.Read();
}
