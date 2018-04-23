#include "controller.h"
#include "Geometry/polygon.h"
#include "Geometry/visibilitygraph.h"
#include "Geometry/shortestpath.h"

Polygon Controller::uiPolyToModel(const QVector<std::pair<double, double>> &uiPoly)
{
    std::vector<Point> points;
    for (const auto &p: uiPoly)
    {
        points.push_back(p);
    }
    return Polygon(points);
}

QVector<std::pair<Ui::Point, Ui::Point>> Controller::modelEdgeToUi(const std::vector<std::pair<Point, Point>> &modelEdges)
{
    QVector<std::pair<Ui::Point, Ui::Point>> uiEdges;
    for (const auto &e: modelEdges)
    {
        uiEdges.push_back(e);
    }
    return uiEdges;
}

QVector<std::pair<Ui::Point, Ui::Point>>
        Controller::calcVisibilityGraph(QVector<QVector<std::pair<double, double>>> &polygons)
{
    // transforming data input from View to Model representation
    std::vector<Polygon> model;
    for (auto const &polygon: polygons)
    {
         model.push_back(uiPolyToModel(polygon));
    }
    VisibilityGraph vg(model);
    // transforming Model data back to View representation
    std::vector<std::pair<Point, Point>> vgEdges = vg.getEdges();
    return modelEdgeToUi(vgEdges);
}

QVector<std::pair<Ui::Point, Ui::Point>>
    Controller::calcShortestPath(QVector<QVector<std::pair<double, double>>> &polygons
                                 , QVector<std::pair<Ui::Point, Ui::Point>> &vg
                                 , Ui::Point start, Ui::Point finish)
{
    // transforming data input from View to Model representation
    std::vector<std::pair<Point, Point>> model;
    for (auto const &polygon: polygons)
    {
        std::vector<std::pair<Point, Point>> edges = uiPolyToModel(polygon).GetEdges();
        model.insert(model.end(), edges.begin(), edges.end());
    }
    // TODO: workaround, fix it!
    auto vec = vg.toStdVector();
    model.insert(model.end(), vec.begin(), vec.end());
    return QVector<std::pair<Ui::Point, Ui::Point>>
        ::fromStdVector(shortestPath(model, start, finish));
}
