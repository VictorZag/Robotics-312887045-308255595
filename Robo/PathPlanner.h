/* 
 * File:   PathPlanner.h
 * Author: colman
 *
 * Created on June 26, 2015, 2:50 AM
 */

#ifndef PATHPLANNER_H
#define	PATHPLANNER_H

#include "Map.h"

class Location
{
public:
    unsigned int x;
    unsigned int y;
};

class GridNode
{
public:
    Location place;
    float t_score;
    float g_score;
    GridNode* parent;
};

class PathPlanner {
public:
    PathPlanner(Map m);
    PathPlanner(const PathPlanner& orig);
    virtual ~PathPlanner();
    
    GridNode* getGoalNode();
private:
    GridNode* _goalNode;
    
    //returns how much distance from current location to goal location
    float heuristic_cost_estimate(Location cur, Location goal);
    //returns the position of the node with the smallest g score in open
    int minGScoreL(vector<GridNode*> open);
    //returns the position of the node witch located in a specific location
    int getNodeByL(vector<GridNode*> open,unsigned int nx, unsigned int ny);
    //returns the node of the goal (can be traces to beginning by parent)
    GridNode* aStar(vector< vector<int> > grid, float gridResolution, float startX, float startY, float goalX, float goalY);
    //creates a picture by the name of "MapWithPath.png" which is the map with the calculated path
    void painPath(Map m, GridNode* gn);
    
    
};

#endif	/* PATHPLANNER_H */

