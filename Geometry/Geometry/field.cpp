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

Field Field::GenerateRandom(int polyNumber)
{
    Field result;
    double min_x = -10, min_y = -10, max_x = 10, max_y = 10;
    std::vector<bool> vacant(100, true);
    srand(time(NULL));
    int number_of_polys = polyNumber % 101;
    for (int i = 0; i < number_of_polys; i++)
    {
        int number_of_cell = rand() % 100;
        while (!vacant[number_of_cell])
            number_of_cell = (number_of_cell + 1) % 100;
        vacant[number_of_cell] = false;
        int number_of_vertices = rand() % 4 + 3;
        double min_poly_x = min_x + ((max_x - min_x) / 10) * (number_of_cell / 10);
        double max_poly_x = min_poly_x + ((max_x - min_x) / 10);
        double min_poly_y = min_y + ((max_y - min_y) / 10) * (number_of_cell % 10);
        double max_poly_y = min_poly_y + ((max_y - min_y) / 10);
        result.AddPoly(Polygon::GenerateRandom(number_of_vertices, min_poly_x, max_poly_x, min_poly_y, max_poly_y));
    }
    return result;
}
