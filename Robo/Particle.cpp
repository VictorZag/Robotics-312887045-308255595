/* 
 * File:   Particle.cpp
 * Author: colman
 * 
 * Created on June 26, 2015, 2:52 AM
 */


#include "Particle.h"

Particle::Particle(float x, float y, float yaw, float belief, Map *map, Robot *robot, WaypointsManager *wayPoint) {
    this->_x = x;
    this->_y = y;
    this->_yaw = yaw;
    this->_belief = belief;
    this->_currMap = map;
    this->_robot = robot;
    this->_wayPoint = wayPoint;
    
}

Particle::Particle(const Particle& orig) {
}

Particle::~Particle() {
}

void Particle::Update(float deltaX, float deltaY, float deltaYaw)
{
    _x += deltaX;
    _y += deltaY;
    _yaw += deltaYaw;
    
    float predBelief = _belief * ProbByMove(abs(deltaX), abs(deltaY), deltaYaw);
    
    _belief = 1.5 * predBelief * ProbByMeasurement();
}

float Particle::ProbByMeasurement()
{
    // READ!!!
    _robot->read();
    float probResult = 0;
    float xObs, yObs;
    float robotYaw = _robot->getYaw();
    float robotX = _robot->getX();
    float robotY = _robot->getY();
    int minIndex = _robot->deg_to_index(MIN_ANGLE);
    int maxIndex = _robot->deg_to_index(MAX_ANGLE);
    bool stop = false;

    float *scan = _robot->getLaserScan();

    for (int i = minIndex; i <= maxIndex; i++)
    {
        /*    xrob – x position of the robot
              yrob – y position of the robot
              α – robot’s orientation
              β – angle of the sensor relative to the robot
              d – distance between the robot and the obstacle
              xobs – x position of the obstacle
              yobs – y position of the obstacle*/

          //xobs = xrob + d · cos(α + β)
          xObs = robotX + scan[i] * cos(robotYaw + (i * 0.36 - 120)*PI/180);
          //yobs = yrob + d · sin(α + β)        
          yObs = robotY + scan[i] * sin(robotYaw + (i * 0.36 - 120)*PI/180);

          // we have two points, now according to map extimate if we have obstacle
          // if so give high prob 
          // else give low prob

          // 4 Meter = 100pixels
          int angle = robotYaw + (i * 0.36 - 120)*PI/180;
          int length = LASER_RANGE;
          float gridResolution = _currMap->getGridResolutionPix();
          float roboX = _wayPoint->getWaypoint().x * gridResolution;
          float roboY = _wayPoint->getWaypoint().y *(-1.0f) * gridResolution;

          float xObsImage, yObsImage;

          xObsImage =  round(roboX + length * cos(angle));
          yObsImage =  round(roboY + -length * sin(angle));

          LocationF loc = Line(roboX, abs(roboY), xObsImage, abs(yObsImage));

          probResult += ((MAX_LASER_DIST - abs(loc.x - xObs))/(MAX_LASER_DIST * 2))/maxIndex;
          probResult += ((MAX_LASER_DIST - abs(loc.y - yObs))/(MAX_LASER_DIST * 2))/maxIndex;
    }
    return probResult;
}

LocationF Particle::Line(  float x1,  float y1,  float x2,  float y2)
{
  // Bresenham's line algorithm
  const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
  if(steep)
  {
    
    std::swap(x1, y1);
    std::swap(x2, y2);
  }
 
  if(x1 > x2)
  {
    std::swap(x1, x2);
    std::swap(y1, y2);
  }
 
  const float dx = x2 - x1;
  const float dy = fabs(y2 - y1);
 
  float error = dx / 2.0f;
  const int ystep = (y1 < y2) ? 1 : -1;
  int y = (int)y1;
 
  const int maxX = (int)x2;
  float width = _currMap->getWidth();
  LocationF l;
  for(int x=(int)x1; x<maxX; x++)
  {
    if(steep)
    {
        //SetPixel(y,x, color);        
        if (_currMap->getImage()[((x*width)+y)*4] == 0)
        {
            l.x = y;
            l.y = x;
            return l;
        }      
    }
    else
    {
         //SetPixel(x,y, color);
        if (_currMap->getImage()[((y*width)+x)*4] == 0)
        {
            l.x = x;
            l.y = y;
            return l;
        }
    }
 
    error -= dy;
    if(error < 0)
    {
        y += ystep;
        error += dx;
    }
  }
}

float Particle::ProbByMove(float deltaX, float deltaY, float deltaYaw)
{
    // As delta yaw is smaller so return Prob that close to 1
    // else return Prob that close to 0
    float prob = (PI - deltaYaw)/(3*PI);
    
    if (deltaX <= 145/RWX)
    {
        prob+= (145/RWX - deltaX)/(145/RWX * 3);
    }
    
    if (deltaY <= 125/RWY)
    {
        prob+= (125/RWY - deltaY)/(125/RWY * 3);
    }
    
    return prob;
}

float Particle::GetBelief() const
{
    return _belief;
}

float Particle::GetX() const{
    return _x;
}
float Particle::GetY() const{
    return _y;
}
float Particle::GetYaw() const{
    return _yaw;
}
float Particle::Getbelief() const{
    return _belief;
}
