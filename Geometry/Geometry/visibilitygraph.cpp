#include "visibilitygraph.h"

void VisibilityGraph::addPoly(const Polygon &poly)
{
    std::vector<Point> temp_points = poly.GetPoints();
    size_t n = temp_points.size();
    for (int j = 0; j < n - 1; j++)
    {
        poly_edges.push_back({temp_points[j], temp_points[j + 1]});
    }
    poly_edges.push_back({temp_points[n - 1], temp_points[0]});
}

VisibilityGraph::VisibilityGraph()
{}

VisibilityGraph::VisibilityGraph(std::vector<Polygon> polys)
{
    for (int i = 0; i < polys.size(); i++)
    {
        addPoly(polys[i]);
        std::vector<Point> points = polys[i].GetPoints();
        for (int j = 0; j < points.size(); ++j)
        {
            std::vector<std::pair<Point, Point>> newEdges = addPoint(points[j], i);
        }
    }
}

std::vector<std::pair<Point, Point>> VisibilityGraph::getEdges()
{
    return edges;
}


std::vector<std::pair<Point, Point>> VisibilityGraph::addPoint(Point p, int id=-1)
{
    std::vector<std::pair<Point, Point>> newEdges;
    for (int i = 0; i < all_points.size(); i++)
    {
        if (all_points[i].second == id && id != -1) continue;
        bool crossed = false;
        for (int k = 0; k < poly_edges.size(); k++)
            if (LinesCross(all_points[i].first, p, poly_edges[k].first, poly_edges[k].second))
            {
                crossed = true;
                break;
            }
        if (!crossed)
            newEdges.push_back({all_points[i].first, p});
    }
    all_points.push_back({p, id});
    edges.insert(edges.end(), newEdges.begin(), newEdges.end());
    return newEdges;
}

void VisibilityGraph::PrintEdges()
{
    for (int i = 0; i < edges.size(); i++)
    {
        std::cout << edges[i].first.first << " " << edges[i].first.second << " " << edges[i].second.first << " " << edges[i].second.second << std::endl;
    }
}
