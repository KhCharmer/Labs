#include "shortestpath.h"
#include <vector>
#include <queue>
#include <map>
#include <cmath>

double euclidDist(Point a, Point b)
{
    double x = a.first - b.first;
    double y = a.second - b.second;
    return sqrt(x*x + y*y);
}

std::vector<std::vector<std::pair<int, double>>>
    edgesToG(const std::vector<std::pair<Point, Point>> &edges
             , std::map<Point, int> &pointId)
{
     // TODO: fix it, very bad idea of using map with double
    int id = 0;
    for (const auto &edge: edges)
    {
        if (pointId.find(edge.first) == pointId.end())
        {
            pointId[edge.first] = id;
            ++id;
        }
        if (pointId.find(edge.second) == pointId.end())
        {
            pointId[edge.second] = id;
            ++id;
        }
    }
    std::vector<std::vector<std::pair<int, double>>> g(id);
    for (const auto &edge: edges)
    {
        Point a = edge.first, b = edge.second;
        double dist = euclidDist(a, b);
        int aId = pointId[a], bId = pointId[b];
        g[aId].push_back(std::make_pair(bId, dist));
        g[bId].push_back(std::make_pair(aId, dist));
    }
    return g;
}

std::vector<std::pair<Point, Point>>
    shortestPath(const std::vector<std::pair<Point, Point>> &edges, Point start, Point finish)
{
    std::map<Point, int> pointId;
    std::vector<std::vector<std::pair<int, double>>>
            g = edgesToG(edges, pointId);
    int n = g.size();
    int s = pointId[start];
    int f = pointId[finish];
    std::vector<double> d (n, INFINITY),  p (n);
    d[s] = 0;
    p[s] = s;
    std::priority_queue<std::pair<double, int>> q;
    q.push (std::make_pair (0, s));
    while (!q.empty()) {
        int v = q.top().second;
        double cur_d = -q.top().first;
        q.pop();
        if (cur_d > d[v])  continue;

        for (size_t j=0; j < g[v].size(); ++j) {
            int to = g[v][j].first;
            double len = g[v][j].second;
            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                p[to] = v;
                q.push (std::make_pair (-d[to], to));
            }
        }
    }

    std::vector<Point> idToPoint(n);
    for (const auto &p: pointId)
        idToPoint[p.second] = p.first;

    std::vector<std::pair<Point, Point>> res;
    int curr = f, prev = p[f];
    while (curr != s)
    {
        res.push_back(std::make_pair(idToPoint[prev], idToPoint[curr]));
        int temp = curr;
        curr = prev;
        prev = p[temp];
    }
    return res;
}
