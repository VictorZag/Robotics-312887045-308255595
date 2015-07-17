/* 
 * File:   PathPlanner.cpp
 * Author: colman
 * 
 * Created on June 26, 2015, 2:50 AM
 */

#include "PathPlanner.h"

PathPlanner::PathPlanner(Map m) {
    _goalNode = aStar(m.getGrid(), m.geGridResolution(), m.gridFromPix(m.getStartLocationX()), m.gridFromPix(m.getStartLocationY()), m.gridFromPix(m.getGoalLocationX()), m.gridFromPix(m.getGoalLocationY()));
    painPath(m, _goalNode);
}

PathPlanner::PathPlanner(const PathPlanner& orig) {
}

PathPlanner::~PathPlanner() {
}

float PathPlanner::heuristic_cost_estimate(Location cur, Location goal)
{
    float dx = cur.x-goal.x;
    float dy = cur.y-goal.y;
    return sqrt(dx * dx + dy * dy);
}
int PathPlanner::minGScoreL(vector<GridNode*> open)
{
    float minG=open[0]->g_score;
    int minI=0;
    for(int i = 1; i < open.size(); i++)
    {
        if(open[i]->g_score < minG)
        {
            minI = i;
            minG = open[i]->g_score;
        }
    }
    return minI;
}
int PathPlanner::getNodeByL(vector<GridNode*> open,unsigned int nx, unsigned int ny)
{
    for(int i = 1; i < open.size(); i++)
    {
        if(open[i]->place.x == nx && open[i]->place.y == ny)
        {
            return i;
        }
    }
}
GridNode* PathPlanner::aStar(vector< vector<int> > grid, float gridResolution, float startX, float startY, float goalX, float goalY)
{
    Location goal;
    goal.x=goalX;
    goal.y=goalY;
    unsigned int rows = grid.size();
    unsigned int cols = grid[0].size();
    int wallStatus[rows][cols];
    float gCheck[rows][cols];
    for (unsigned int r=0; r<rows; r++)
    {
        for (unsigned int c=0; c<cols; c++)
        {
            if (grid[r][c] == 1)
            {
                wallStatus[r][c] = 1;
                for (int i=max((unsigned int)0,r-1); i<=min(r+1,rows-1); i++)
                {
                    for (int j=max((unsigned int)0,c-1); j<=min(c+1,cols-1); j++)
                    {
                        if (grid[i][j] == 0)
                        {
                            wallStatus[i][j] = 2;
                        }
                    }
                }
            }
            else if (wallStatus[r][c] != 2)
            {
                wallStatus[r][c] = 0;
            }
            gCheck[r][c] = -1;
        }
    }
    GridNode* startNode = new GridNode;;
    startNode->place.x=startX;
    startNode->place.y=startY;
    startNode->t_score=0;
    startNode->g_score=heuristic_cost_estimate(startNode->place,goal);
    gCheck[(int)startY][(int)startX] = startNode->g_score;
    vector<GridNode*> openSet;
    openSet.push_back(startNode);
    while(!openSet.empty())
    {
        int minGLocation = minGScoreL(openSet);
        GridNode* current = openSet[minGLocation];
        openSet.erase(openSet.begin()+minGLocation);
        wallStatus[current->place.y][current->place.x]=1;
        for (unsigned int neighborY=std::max((unsigned int)0,current->place.y-1);neighborY<=std::min(current->place.y+1,rows-1);neighborY++)
        {
            for (unsigned int neighborX=std::max((unsigned int)0,current->place.x-1);neighborX<=std::min(current->place.x+1,cols-1);neighborX++)
            {
                if(wallStatus[neighborY][neighborX] != 1)
                {
                    GridNode* neighbor = new GridNode;
                    neighbor->parent=current;
                    neighbor->place.x=neighborX;
                    neighbor->place.y=neighborY;
                    if(neighborX == goalX && neighborY == goalY)
                    {
                        return neighbor;
                    }
                    neighbor->t_score=current->t_score;
                    if(neighborX==current->place.x || neighborY==current->place.y)
                    {
                        neighbor->t_score+=gridResolution;
                    }
                    else
                    {
                        neighbor->t_score+=sqrt(gridResolution*gridResolution*2);
                    }
                    if (wallStatus[neighborY][neighborX] == 2)
                    {
                        neighbor->t_score+=gridResolution;
                    }
                    neighbor->g_score=neighbor->t_score+heuristic_cost_estimate(neighbor->place,goal);
                    if(gCheck[neighborY][neighborX] == -1)
                    {
                        gCheck[neighborY][neighborX] = neighbor->g_score;
                        openSet.push_back(neighbor);
                    }
                    else if (neighbor->g_score < gCheck[neighborX][neighborY])
                    {
                        gCheck[neighborY][neighborX] = neighbor->g_score;
                        int existingNodeI = getNodeByL(openSet,neighborX,neighborY);
                        openSet[existingNodeI]->t_score = neighbor->t_score;
                        openSet[existingNodeI]->g_score = neighbor->g_score;
                        openSet[existingNodeI]->parent = neighbor->parent;
                                
                    }
                }
            }
        }
        
        
    }
    return startNode;
}
void PathPlanner::painPath(Map m, GridNode* gn)
{
    vector<unsigned char> newImage = m.getImage();
    float gridResPix = m.getGridResolutionPix();
    float targetX = m.gridFromPix(m.getStartLocationX());
    float targetY = m.gridFromPix(m.getStartLocationY());
    while (gn->place.x!=targetX || gn->place.y!=targetY)
    {
        for (int i =gn->place.y*gridResPix; i<(gn->place.y+1)*gridResPix;i++)
            {
                for (int j =gn->place.x*gridResPix; j<(gn->place.x+1)*gridResPix;j++)
                {
                    int pix = ((i*m.getWidth())+j)*4;
                    newImage[pix]=0;
                    newImage[pix+1]=0;
                    newImage[pix+2]=255;
                    newImage[pix+3]=255;
                }
            }
        gn = gn->parent;
    }
    for (int i =gn->place.y*gridResPix; i<(gn->place.y+1)*gridResPix;i++)
    {
        for (int j =gn->place.x*gridResPix; j<(gn->place.x+1)*gridResPix;j++)
        {
            int pix = ((i*m.getWidth())+j)*4;
            newImage[pix]=0;
            newImage[pix+1]=0;
            newImage[pix+2]=255;
            newImage[pix+3]=255;
        }
    }
    for (int i =348; i<352;i++)
    {
        for (int j =390; j<394;j++)
        {
            int pix = ((i*m.getWidth())+j)*4;
            newImage[pix]=0;
            newImage[pix+1]=255;
            newImage[pix+2]=0;
            newImage[pix+3]=255;
        }
    }
    m.saveImage("MapWithPath.png",newImage,m.getWidth(),m.getHeight());
}

GridNode* PathPlanner::getGoalNode()
{
    return _goalNode;
}
