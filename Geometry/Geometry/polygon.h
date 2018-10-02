#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <exception>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <stdio.h>
#include <algorithm>
#include <set>
#include <random>

using Point = std::pair<double, double>;

enum Position {Inner, Outer, Crossing, NonIntersecting};

bool ValidPolygon(std::vector<Point> & points);
bool LinesCross(Point, Point, Point, Point);

class Polygon
{
    std::vector<Point> points;
    std::vector<std::pair<Point, Point>> edges;
public:
    Polygon(std::vector<Point> points);
    Position CheckPosition(Polygon & with);
    std::vector<Point> GetPoints() const;
    std::vector<std::pair<Point, Point>> GetEdges() const;
    static Polygon GenerateRandom(int v_n, double min_x, double max_x, double min_y, double max_y);
    static bool IsPossibleToAdd(Polygon poly, std::vector<Polygon> & to);
};

#endif // POLYGON_H
