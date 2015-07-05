/* 
 * File:   WaypointsManager.cpp
 * Author: colman
 * 
 * Created on June 26, 2015, 2:52 AM
 */

#include "WaypointsManager.h"

WaypointsManager::WaypointsManager(GridNode* end, int startX, int startY) {
    int oldXProgression, oldYProgression;
    int newXProgression, newYProgression;
    GridNode* prev = end;
    GridNode* curr = prev->parent;
    newXProgression = curr->place.x - prev->place.x;
    newYProgression = curr->place.y - prev->place.y;
    _waypoints.push_back(prev->place);
    while(curr->place.x != startX || curr->place.y != startY)
    {
        prev = curr;
        curr = curr->parent;
        oldXProgression = newXProgression;
        oldYProgression = newYProgression;
        newXProgression = curr->place.x - prev->place.x;
        newYProgression = curr->place.y - prev->place.y;
        if ((oldXProgression - newXProgression != 0) || (oldYProgression - newYProgression != 0))
        {
            _waypoints.push_back(prev->place);
        }
    }
    _waypoints.push_back(curr->place);
}

WaypointsManager::WaypointsManager(const WaypointsManager& orig) {
}

WaypointsManager::~WaypointsManager() {
}

