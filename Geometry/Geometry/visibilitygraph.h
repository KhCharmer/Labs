#ifndef VISIBILITYGRAPH_H
#define VISIBILITYGRAPH_H

#include "polygon.h"
#include <vector>
#include <iostream>

class VisibilityGraph
{
private:
    std::vector<std::pair<Point, Point>> edges;
    std::vector<std::pair<Point, int>> all_points;
    std::vector<std::pair<Point, Point>> poly_edges;

    void addPoly(const Polygon &);

public:
    VisibilityGraph();
    VisibilityGraph(std::vector<Polygon>);
    std::vector<std::pair<Point, Point>> getEdges();
    void PrintEdges();
    std::vector<std::pair<Point, Point>> addPoint(Point, int);
};

#endif // VISIBILITYGRAPH_H
