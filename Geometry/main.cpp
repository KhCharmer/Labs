#include <iostream>
#include <polygon.h>
#include <field.h>
#include <visibilitygraph.h>
#include <exception>
using namespace std;

int main()
{
    vector<Point> points;
    points.push_back({0,0});
    points.push_back({0,1});
    points.push_back({1,1});
    points.push_back({1,0});
    cout << ValidPolygon(points);
    Polygon p(points);
    Field field;
    field.AddPoly(p);
    VisibilityGraph vg(field.GetInnerPolygons());
    vg.PrintEdges();
    return 0;
}
