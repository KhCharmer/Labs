#include "visibilitygraph.h"

VisibilityGraph::VisibilityGraph(std::vector<Polygon> polys)
{

    std::vector<std::pair<Point, Point>> temp_edges;
    std::vector<Point> all_poins;
    for (int i = 0; i < polys.size(); i++)
    {
        std::vector<Point> temp_points = polys[i].GetPoints();
        for (int j = 0; j < temp_points.size() - 1; j++)
        {
            all_poins.push_back(temp_points[j]);
            temp_edges.push_back({temp_points[j], temp_points[j + 1]});
        }
        temp_edges.push_back({temp_points[temp_points.size() - 1], temp_points[0]});
    }
    for (int i = 0; i < all_poins.size(); i++)
    {
        for (int j = 0; j < all_poins.size(); j++)
        {
            if (i != j)
            {
                bool crossed = false;
                for (int k = 0; k < temp_edges.size(); k++)
                    if (LinesCross(all_poins[i], all_poins[j], temp_edges[k].first, temp_edges[k].second))
                    {
                        crossed = true;
                        break;
                    }
                if (!crossed)
                    edges.push_back({all_poins[i], all_poins[j]});
            }
        }
    }
}

std::vector<std::pair<Point, Point>> VisibilityGraph::getEdges()
{
    return edges;
}

void VisibilityGraph::PrintEdges()
{
    for (int i = 0; i < edges.size(); i++)
    {
        std::cout << edges[i].first.first << " " << edges[i].first.second << " " << edges[i].second.first << " " << edges[i].second.second << std::endl;
    }
}
