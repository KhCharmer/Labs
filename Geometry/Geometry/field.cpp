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

Field Field::GenerateRandom()
{
    Field result;
    double min_x = -2, min_y = -2, max_x = 2, max_y = 2;
    std::vector<bool> vacant(25, true);
    srand(time(NULL));
    int number_of_polys = rand() % 10 + 1;
    for (int i = 0; i < number_of_polys; i++)
    {
        int number_of_cell = rand() % 25;
        while (!vacant[number_of_cell])
            number_of_cell = (number_of_cell + 1) % 25;
        vacant[number_of_cell] = false;
        int number_of_vertices = rand() % 4 + 3;
        double min_poly_x = min_x + ((max_x - min_x) / 5) * (number_of_cell / 5);
        double max_poly_x = min_poly_x + ((max_x - min_x) / 5);
        double min_poly_y = min_y + ((max_y - min_y) / 5) * (number_of_cell % 5);
        double max_poly_y = min_poly_y + ((max_y - min_y) / 5);
        result.AddPoly(Polygon::GenerateRandom(number_of_vertices, min_poly_x, max_poly_x, min_poly_y, max_poly_y));
    }
    return result;
}
