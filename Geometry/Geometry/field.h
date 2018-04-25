#ifndef FIELD_H
#define FIELD_H

#include "polygon.h"

class Field
{
    std::vector<Polygon> inner_polygons;
    //Polygon outer_polygon;
    Point start, finish;
public:
    Field();
    bool AddPoly(Polygon);
    void AddPolyRand();
    static Field GenerateRandom(int polyNumber);
    bool SetOuterPoly(Polygon);
    void SetOuterPolyRand();
    std::vector<Polygon> GetInnerPolygons();
};
#endif // FIELD_H
