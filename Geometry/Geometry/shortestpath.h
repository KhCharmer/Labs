#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H

#include "model.h"
#include <vector>

std::vector<std::pair<Point, Point>>
    shortestPath(const std::vector<std::pair<Point, Point>> &edges, Point s, Point f);

#endif // SHORTESTPATH_H
