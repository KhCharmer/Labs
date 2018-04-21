#ifndef POLYGON_H
#define POLYGON_H

#include <vector>;
#include <exception>;
#include <iostream>

using Point = std::pair<double, double>;

enum Position {Inner, Outer, Crossing, NonIntersecting};

bool ValidPolygon(std::vector<Point> & points);
bool LinesCross(Point, Point, Point, Point);

class Polygon
{
    std::vector<Point> points;
public:
    Polygon(std::vector<Point> points);
    Position CheckPosition(Polygon & with);
    std::vector<Point> GetPoints();
};

#endif // POLYGON_H
