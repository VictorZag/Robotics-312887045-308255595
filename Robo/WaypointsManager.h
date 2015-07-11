/* 
 * File:   WaypointsManager.h
 * Author: colman
 *
 * Created on June 26, 2015, 2:52 AM
 */

#ifndef WAYPOINTSMANAGER_H
#define	WAYPOINTSMANAGER_H

#include "PathPlanner.h"

class WaypointsManager {
public:
    WaypointsManager(GridNode* end, int startX, int startY);
    WaypointsManager(const WaypointsManager& orig);
    virtual ~WaypointsManager();
    Location getWaypoint();
    Location getPrevWaypoint();
    void remWaypoint();
private:
    vector<Location> _waypoints;
};

#endif	/* WAYPOINTSMANAGER_H */

