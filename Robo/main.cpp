/*
 * Main.cpp
 *
 *  Created on: May 26, 2015
 *      Author: colman
 */

#include <libplayerc++/playerc++.h>
#include <iostream>
#include <unistd.h>
#include "Robot.h"
#include "lodepng.h"
#include "Map.h"
#include "PathPlanner.h"
#include "WaypointsManager.h"
#include "MoveForward.h"
#include "Turn.h"
#include "Particle.h"
#include "LocalizationManager.h"
#include "Manager.h"

#define PI 3.14159265
#define RWX 38.2
#define RWY 39

using namespace PlayerCc;
using namespace std;


int main()
{
    Map m((char*)"parameters.txt");
    PathPlanner p(m);
    WaypointsManager wm(p.getGoalNode(),m.gridFromPix(m.getStartLocationX()),m.gridFromPix(m.getStartLocationY()));
    Robot* robot = new Robot((char*)"parameters.txt","localhost", 6665);
    
    MoveForward* mf = new MoveForward(robot);
    Turn* tu=new Turn(robot);
    tu->setAngle(0.1);
    float dy,dx,deg;
    LocalizationManager *locM = new LocalizationManager(&m,robot,&wm);
    while(wm.getWaypointCount() > 1)
    {
        robot->read();
        dy=m.pixFromGrid(wm.getPrevWaypoint().y)-m.pixFromGrid(wm.getWaypoint().y);
        dx=m.pixFromGrid(wm.getPrevWaypoint().x)-m.pixFromGrid(wm.getWaypoint().x);
        if(dy<=0)
        {
            if(dx< 0)
            {
                deg = - abs(atan(dy/dx)) ;
            }
            else
            {
                deg = -PI - abs(atan(dy/dx)) ;
            }
        }
        else
        {
            if(dx<=0)
            {
                deg = abs(atan(dy/dx)) ;
            }
            else
            {
                deg = PI - abs(atan(dy/dx)) ;
            }
        }
        deg += 0.05;
        if ((deg - robot->getYaw() <= PI && deg - robot->getYaw() >= 0)|| deg - robot->getYaw() < -PI)
        {
            tu->setAngle(0.1);
        }
        else
        {
            tu->setAngle(-0.1);
        }
        std::cout << deg << std::endl;
        tu->action();
        while (abs(deg - robot->getYaw()) > 0.01)
        {
            robot->read();
            std::cout << " 1 " <<robot->getYaw() << std::endl;
            std::cout << " 2 " <<deg  << std::endl;
        }
        robot->setSpeed(0,0);
        sleep(1);
        mf->action();
        float o,n;

        n=m.calculateDis(robot->getX(),robot->getY(),m.pixFromGrid(wm.getWaypoint().x),-m.pixFromGrid(wm.getWaypoint().y));
        o=n;
        //            while (m.calculateDis(robot->getX(),robot->getY(),m.pixFromGrid(wm.getWaypoint().x)/RWX,-m.pixFromGrid(wm.getWaypoint().y)/RWY) > 0.1)
        while(n<=o)
        {
            o=n;
            robot->read();
            robot->read();
            robot->read();
            robot->read();
            robot->read();

//                if(abs(robot->getY() + m.pixFromGrid(wm.getWaypoint().y)/RWY) <=0.8)
//                {
//                    std::cout << "HERE!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
//                }
                n=m.calculateDis(robot->getX(),robot->getY(),m.pixFromGrid(wm.getWaypoint().x)/RWX,-m.pixFromGrid(wm.getWaypoint().y)/RWY);
                std::cout << " to x " <<m.pixFromGrid(wm.getWaypoint().x)/RWX << " to y "<< -m.pixFromGrid(wm.getWaypoint().y)/RWY <<std::endl;
                std::cout << " now x " <<robot->getX() << " now y "<< robot->getY() << " dis " << m.calculateDis(robot->getX(),robot->getY(),m.pixFromGrid(wm.getWaypoint().x)/RWX,-m.pixFromGrid(wm.getWaypoint().y)/RWY) <<std::endl;
            }
            robot->setSpeed(0,0);
            float dx = (m.pixFromGrid(wm.getWaypoint().x) - m.pixFromGrid(wm.getPrevWaypoint().x))/RWX;
            float dy = (m.pixFromGrid(wm.getWaypoint().y) - m.pixFromGrid(wm.getPrevWaypoint().y))/RWY;
            float dyaw = robot->getYaw() - robot->getOldYaw();
            robot->read();
            locM->Update(dx,dy,dyaw,robot->getLaserScan());
            robot->setOldYaw(robot->getYaw());
            wm.remWaypoint();
        }
        robot->setSpeed(0,0);
        
//        float dx = (m.pixFromGrid(wm.getWaypoint().x) - m.pixFromGrid(wm.getPrevWaypoint().x))/RWX;
//        float dy = (m.pixFromGrid(wm.getWaypoint().y) - m.pixFromGrid(wm.getPrevWaypoint().y))/RWY;
//        float dyaw = robot->getYaw() - robot->getOldYaw();
//        locM->Update(dx,dy,dyaw,robot->getLaserScan());
//        robot->setOldYaw(robot->getYaw());
        wm.remWaypoint();
    }
        return 0;
//        Map m((char*)"parameters.txt");
//        PathPlanner p(m);
//        WaypointsManager wm(p.getGoalNode(),m.gridFromPix(m.getStartLocationX()),m.gridFromPix(m.getStartLocationY()));
//        Robot* robot = new Robot((char*)"parameters.txt","localhost", 6665);
////	Position2dProxy pp(&pc,0);
////	//SonarProxy sp(&pc,0);
////	IrProxy sp(&pc,0);
//
////	pp.SetMotorEnable(true);
//       
//        
//        MoveForward* mf = new MoveForward(robot);
//        Turn* tu=new Turn(robot);
//        tu->setAngle(0.1);
//        float dy,dx,deg;
//        LocalizationManager *locM = new LocalizationManager(&m,robot,&wm);
//        while(wm.getWaypointCount() > 1)
//        {
//            robot->read();
//            dy=m.pixFromGrid(wm.getPrevWaypoint().y)-m.pixFromGrid(wm.getWaypoint().y);
//            dx=m.pixFromGrid(wm.getPrevWaypoint().x)-m.pixFromGrid(wm.getWaypoint().x);
//            deg=180 - (atan (dy/dx) * 180 / PI);
//            std::cout << deg << std::endl;
//            tu->action();
//            while (abs(deg * PI / 180 - robot->getYaw()+0.08) > 0.01)
//            {
//                robot->read();
//                std::cout << " 1 " <<robot->getYaw() << std::endl;
//                std::cout << " 2 " <<(deg * PI / 180) << std::endl;
//            }
//            robot->setSpeed(0,0);
//            sleep(1);
//            mf->action();
//            float o,n;
//            
//            n=m.calculateDis(robot->getX(),robot->getY(),m.pixFromGrid(wm.getWaypoint().x)/RWX,-m.pixFromGrid(wm.getWaypoint().y)/RWY);
//            o=n;
//            //            while (m.calculateDis(robot->getX(),robot->getY(),m.pixFromGrid(wm.getWaypoint().x)/RWX,-m.pixFromGrid(wm.getWaypoint().y)/RWY) > 0.1)
//            while(m.calculateDis(robot->getX(),robot->getY(),m.pixFromGrid(wm.getWaypoint().x)/RWX,-m.pixFromGrid(wm.getWaypoint().y)/RWY) > 0.5)
//            {
//                if(o<n)
//                    break;
//                o=n;
//                robot->read();
//                
////                if(abs(robot->getY() + m.pixFromGrid(wm.getWaypoint().y)/RWY) <=0.8)
////                {
////                    std::cout << "HERE!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
////                }
//                n=m.calculateDis(robot->getX(),robot->getY(),m.pixFromGrid(wm.getWaypoint().x)/RWX,-m.pixFromGrid(wm.getWaypoint().y)/RWY);
//                std::cout << " to x " <<m.pixFromGrid(wm.getWaypoint().x)/RWX << " to y "<< -m.pixFromGrid(wm.getWaypoint().y)/RWY <<std::endl;
//                std::cout << " now x " <<robot->getX() << " now y "<< robot->getY() << " dis " << m.calculateDis(robot->getX(),robot->getY(),m.pixFromGrid(wm.getWaypoint().x)/RWX,-m.pixFromGrid(wm.getWaypoint().y)/RWY) <<std::endl;
//            }
//            robot->setSpeed(0,0);
//            float dx = (m.pixFromGrid(wm.getWaypoint().x) - m.pixFromGrid(wm.getPrevWaypoint().x))/RWX;
//            float dy = (m.pixFromGrid(wm.getWaypoint().y) - m.pixFromGrid(wm.getPrevWaypoint().y))/RWY;
//            float dyaw = robot->getYaw() - robot->getOldYaw();
//            locM->Update(dx,dy,dyaw,robot->getLaserScan());
//            robot->setOldYaw(robot->getYaw());
//            wm.remWaypoint();
//        }
//	return 0;
}




