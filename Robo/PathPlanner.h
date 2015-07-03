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
private:
    float heuristic_cost_estimate(Location start, Location goal);
    int minGScoreL(vector<GridNode*> open);
    int getNodeByL(vector<GridNode*> open,unsigned int nx, unsigned int ny);
    GridNode* aStar(vector< vector<int> > grid, float gridResolution, float startX, float startY, float goalX, float goalY);
    void painPath(Map m, GridNode* gn);
};

#endif	/* PATHPLANNER_H */

