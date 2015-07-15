/*
 * Robot.cpp
 *
 *  Created on: May 26, 2015
 *      Author: colman
 */

#include "Robot.h"
#define PI 3.14159265
#define RWX 38.2
#define RWY 39

Robot::Robot(char* p_filePath,string ip, int port) : _pc(ip, port), _pp(&_pc), _lp(&_pc) {
	// TODO Auto-generated constructor stub
        ConfigurationManager* cm = new ConfigurationManager(p_filePath);
        _pp.SetMotorEnable(true);
        _pp.SetOdometry(cm->GetStartLocationX()/RWX,-cm->GetStartLocationY()/RWY,dtor(cm->GetStartAngle()));
        std::cout << dtor(cm->GetStartAngle())<<"          " <<getYaw() << std::endl;
        for(int i = 0; i < 20 ; i++)
        {
            _pc.Read();
            std::cout << dtor(cm->GetStartAngle())<<"          " <<getYaw() << std::endl;
        }
        
        _pp.SetOdometry(cm->GetStartLocationX()/RWX,-cm->GetStartLocationY()/RWY,dtor(cm->GetStartAngle()));
        std::cout << dtor(cm->GetStartAngle())<<"          " <<getYaw() << std::endl;
        _lastX = _pp.GetXPos();
	_lastY = _pp.GetYPos();
	_lastYaw = _pp.GetYaw();
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
	return _pp.GetXPos();
}

float Robot::getY()
{
	return _pp.GetYPos();
}

float Robot::getYaw()
{
	return _pp.GetYaw();
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
