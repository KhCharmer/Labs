#include "polygon.h"

bool PointBelongsToSeg(Point p, Point start, Point finish)
{
    bool point_belongs_to_line= (p.first - start.first) * (finish.second - start.second) ==
            (p.second - start.second) * (finish.first - start.first);
    bool point_belongs_to_borders = ((start.first - p.first) * (finish.first - p.first) <= 0) &&
            ((start.second - p.second) * (finish.second - p.second) <= 0);
    return point_belongs_to_borders && point_belongs_to_line;
}

int CheckSign(Point start, Point finish, Point p)
{
    return (p.first - start.first) * (finish.second - start.second) -
            (p.second - start.second) * (finish.first - start.first);
}

bool LinesCross(Point s1, Point f1, Point s2, Point f2)
{
    return (CheckSign(s1, f1, s2) * CheckSign(s1, f1, f2) < 0) &&
            (CheckSign(s2, f2, s1) * CheckSign(s2, f2, f1) < 0);
}

bool ValidPolygon(std::vector<Point> & points)
{
    if (points.size() < 3)
        return false;
    std::vector<std::pair<Point, Point>> segments;
    for (int i = 0; i < points.size() - 1; i++)
    {
        segments.push_back({points[i], points[i + 1]});
    }
    segments.push_back({points[points.size() - 1], points[0]});

    for (int i = 0; i < segments.size(); i++)
        for (int j = 0; j < segments.size(); j++)
            if ((i != j) && LinesCross(segments[i].first, segments[i].second, segments[j].first, segments[j].second))
                return false;
    return true;
}

Polygon::Polygon(std::vector<Point> ps)
{
    if (ValidPolygon(ps))
        points = ps;
    else
        std::cout << "Polygon is inavlid";
}

Position Polygon::CheckPosition(Polygon & with)
{
    return NonIntersecting;
}

std::vector<Point> Polygon::GetPoints()
{
    return points;
}
