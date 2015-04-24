// Authors: Cade Haley, Mitch Block
// Date: Apr. 19, 2015
// Description: A text-based game that makes use of graphs to control the map

#include "GameGraph.h"
#include <iostream>
#include <queue>

using namespace std;

GameGraph::GameGraph()
{
    //ctor
}

GameGraph::~GameGraph()
{
    //dtor
}

/*
    void addArea(string name);
    Method adds an area to the graph, using the string passed in as the name.
    ex. addArea("Forest")
    Pre-conditions: instance of graph
    Post-conditions: area added to graph
*/
void GameGraph::addArea(std::string name)
{
    bool found = false;
    for (int i = 0; i < areas.size(); i++) //search collection of areas to see if area has already been added
    {
        if(areas[i].title == name)
        {
            found = true;
            std::cout << areas[i].title << " found." << std::endl;
        }
    }
    if(found == false) //add the new area to vector
    {
        room newRoom;
        newRoom.title = name;
        areas.push_back(newRoom);

    }
}

/*
    void addPathToArea(string startingArea, string endingArea)
    Method connects two areas with an edge
    ex. addPathToArea("Forest", "Mountains")
    Pre-conditions: at least two different areas, an instance of the graph
    Post-conditions: both areas added to the other's adjRoom vector
*/
void GameGraph::addPathToArea(std::string beginningArea, std::string endingArea)
{
    for(int i = 0; i < areas.size(); i++)
    {
        if(areas[i].title == beginningArea) //if beginning area is found
        {
            for(int j = 0; j < areas.size(); j++)
            {
                if(areas[j].title == endingArea && i != j) //if ending area is found, add path between the two areas
                {
                    adjRoom aR;
                    aR.r = &areas[j];
                    areas[i].adj.push_back(aR);
                    //another area for edge in other direction
                    adjRoom aR2;
                    aR2.r = &areas[i];
                    areas[j].adj.push_back(aR2);
                }
            }
        }
    }
}

/*
    void lookAtMap (room *currentLocation)
    Method prints to the screen the contents of the current area's adjRoom vector
    ex. lookAtMap(*forest)
    Pre-conditions: an instance of the graph, player's location
    Post-conditions: all adjacent areas printed to screen
*/
void GameGraph::lookAtMap(room *currentLocation)
{
    for (int i = 0; i < currentLocation->adj.size(); i++)
    {
        std::cout << currentLocation->adj[i].r->title << std::endl;
    }
}

/*
    routeToLocation shortestRouteToDestination(string startingArea, string endLocation)
    Method calculates the shortest unweighted distance between the starting area and end location
    ex. shortestRouteToDestination("Forest", "Graveyard")
    Pre-conditions: instance of graph, at least two different areas
    Post-conditions: return shortest path between starting area and end location
*/
routeToLocation GameGraph::shortestRouteToDestination(std::string startArea, std::string endLocation)
{
    room areaCheck;
    for (int i = 0; i < areas.size(); i++) //loop through areas, setting visited to false
    {
        areas[i].visited = false;
        if (areas[i].title == startArea)
        {
            areaCheck = areas[i];
        }
    }
    areaCheck.visited = true;
    routeToLocation currentPath;
    currentPath.distance = 0;
    currentPath.path.push_back(areaCheck);
    std::queue<routeToLocation> pathQueue; //set up queue to store paths taken
    pathQueue.push(currentPath);
    while (!pathQueue.empty())
    {
        currentPath = pathQueue.front(); //look at current path taken
        pathQueue.pop();
        room roomCheck = currentPath.path.back();
        for (int i = 0; i < roomCheck.adj.size(); i++) //look at all adjacent areas to last area in current path
        {
            if (roomCheck.adj[i].r->visited == false)
            {
                routeToLocation newRoute;
                newRoute.path = currentPath.path;
                newRoute.distance = currentPath.distance;
                newRoute.path.push_back(*roomCheck.adj[i].r); //add area to path
                newRoute.distance++;
                if (roomCheck.adj[i].r->title == endLocation) //return once destination found
                {
                    return newRoute;
                }
                else
                {
                    pathQueue.push(newRoute); //add new path to queue
                }
            }
        }
    }
    return currentPath;
}
