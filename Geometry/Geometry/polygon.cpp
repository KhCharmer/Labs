#include "polygon.h"
#include <algorithm>

bool PointBelongsToSeg(Point p, Point start, Point finish)
{
    bool point_belongs_to_line= (p.first - start.first) * (finish.second - start.second) ==
            (p.second - start.second) * (finish.first - start.first);
    bool point_belongs_to_borders = ((start.first - p.first) * (finish.first - p.first) <= 0) &&
            ((start.second - p.second) * (finish.second - p.second) <= 0);
    return point_belongs_to_borders && point_belongs_to_line;
}

double CheckSign(Point start, Point finish, Point p)
{
    return (p.second - start.second) * (finish.first - start.first) -
            (p.first - start.first) * (finish.second - start.second);
}

template <typename T>
bool checkProjIntersect(T a, T b, T c, T d)
{
    if (a > b) std::swap(a, b);
    if (c > d) std::swap(c, d);
    return std::max(a, c) <= std::min(b, d);
}

bool checkBoxIntersect(Point s1, Point f1, Point s2, Point f2)
{
    return checkProjIntersect(s1.first, f1.first, s2.first, f2.first)
            && checkProjIntersect(s1.second, f1.second, s2.second, f2.second);
}



bool LinesCross(Point s1, Point f1, Point s2, Point f2)
{
    return (checkBoxIntersect(s1, f1, s2, f2) &&
            (CheckSign(s1, f1, s2) * CheckSign(s1, f1, f2) < 0) &&
            (CheckSign(s2, f2, s1) * CheckSign(s2, f2, f1) < 0));
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
    {
        points = ps;
        size_t n = ps.size();
        for (int i = 0; i < n - 1; ++i)
            edges.push_back(std::make_pair(ps[i], ps[i + 1]));
        edges.push_back(std::make_pair(ps[n - 1], ps[0]));
    }
    else
        std::cout << "Polygon is inavlid";
}

Position Polygon::CheckPosition(Polygon & with)
{
    return NonIntersecting;
}

std::vector<Point> Polygon::GetPoints() const
{
    return points;
}

std::vector<std::pair<Point, Point>> Polygon::GetEdges() const
{
    return edges;
}
