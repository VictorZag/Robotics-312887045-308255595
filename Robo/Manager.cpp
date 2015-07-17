/* 
 * File:   Manager.cpp
 * Author: colman
 * 
 * Created on June 26, 2015, 2:58 AM
 */

#include "Manager.h"


Manager::Manager() {
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
        if(dy>0)
        {
            if(dx>0)
            {
                deg = atan(dy/dx) ;
            }
            else
            {
                deg = PI - atan(dy/dx) ;
            }
        }
        else
        {
            if(dx>0)
            {
                deg = -atan(dy/dx) ;
            }
            else
            {
                deg = PI + atan(dy/dx) ;
            }
        }
        if (deg - robot->getYaw() <= PI)
        {
            tu->setAngle(0.1);
        }
        else
        {
            tu->setAngle(-0.1);
        }
        std::cout << deg << std::endl;
        tu->action();
        while (abs(deg - robot->getYaw()+0.08) > 0.01)
        {
            robot->read();
            std::cout << " 1 " <<robot->getYaw() << std::endl;
            std::cout << " 2 " <<deg  << std::endl;
        }
        robot->setSpeed(0,0);
        sleep(1);
        mf->action();
        float o,n;

        n=m.calculateDis(robot->getX(),robot->getY(),m.pixFromGrid(wm.getWaypoint().x)/RWX,-m.pixFromGrid(wm.getWaypoint().y)/RWY);
        o=n;
        //            while (m.calculateDis(robot->getX(),robot->getY(),m.pixFromGrid(wm.getWaypoint().x)/RWX,-m.pixFromGrid(wm.getWaypoint().y)/RWY) > 0.1)
        while(m.calculateDis(robot->getX(),robot->getY(),m.pixFromGrid(wm.getWaypoint().x)/RWX,-m.pixFromGrid(wm.getWaypoint().y)/RWY) > 0.5)
        {
            if(o<n)
                break;
            o=n;
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
        locM->Update(dx,dy,dyaw,robot->getLaserScan());
        robot->setOldYaw(robot->getYaw());
        wm.remWaypoint();
    }
}

Manager::Manager(const Manager& orig) {
}

Manager::~Manager() {
}

