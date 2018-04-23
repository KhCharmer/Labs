#include "field.h"

Field::Field() {}

bool Field::AddPoly(Polygon p)
{
    for (int i = 0; i < inner_polygons.size(); i++)
    {
        if (p.CheckPosition(inner_polygons[i]) != NonIntersecting)
            return false;
    }
    inner_polygons.push_back(p);
    return true;
}

bool Field::SetOuterPoly(Polygon p)
{
    for (int i = 0; i < inner_polygons.size(); i++)
    {
        if (p.CheckPosition(inner_polygons[i]) != Outer)
            return false;
    }
    //outer_polygon = p;
    return true;
}

std::vector<Polygon> Field::GetInnerPolygons()
{
    return inner_polygons;
}
