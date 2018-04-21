#ifndef VISIBILITYGRAPH_H
#define VISIBILITYGRAPH_H

#include "polygon.h"
#include <vector>
#include <iostream>

class VisibilityGraph
{
std::vector<std::pair<Point, Point>> edges;
public:
    VisibilityGraph(std::vector<Polygon>);
    std::vector<std::pair<Point, Point>> getEdges();
    void PrintEdges();
};

#endif // VISIBILITYGRAPH_H
