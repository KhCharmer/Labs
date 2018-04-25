#include "controller.h"
#include "Geometry/polygon.h"
#include "Geometry/field.h"
#include "Geometry/visibilitygraph.h"
#include "Geometry/shortestpath.h"

VisibilityGraph Controller::vg;

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
    Controller::vg = VisibilityGraph(model);
    // transforming Model data back to View representation
    std::vector<std::pair<Point, Point>> vgEdges = Controller::vg.getEdges();
    return modelEdgeToUi(vgEdges);
}

QVector<std::pair<Ui::Point, Ui::Point>>
    Controller::calcShortestPath(QVector<QVector<std::pair<double, double>>> &polygons
                                 , Ui::Point start, Ui::Point finish
                                 , QVector<std::pair<Ui::Point, Ui::Point>> &additionalVg)
{
    // transforming data input from View to Model representation
    std::vector<std::pair<Point, Point>> model;
    for (auto const &polygon: polygons)
    {
        std::vector<std::pair<Point, Point>> edges = uiPolyToModel(polygon).GetEdges();
        model.insert(model.end(), edges.begin(), edges.end());
    }
    // TODO: workaround, fix it!
    VisibilityGraph temp = vg;

    auto newVgEdges = QVector<std::pair<Ui::Point, Ui::Point>>::fromStdVector(temp.addPoint(start, -1));
    additionalVg += newVgEdges;
    newVgEdges = QVector<std::pair<Ui::Point, Ui::Point>>::fromStdVector(temp.addPoint(finish, -1));
    additionalVg += newVgEdges;

    auto vec = temp.getEdges();
    model.insert(model.end(), vec.begin(), vec.end());
    auto path = shortestPath(model, start, finish);
    vg = temp;
    return QVector<std::pair<Ui::Point, Ui::Point>>::fromStdVector(path);
}

QVector<QVector<std::pair<double, double>>>
    Controller::getRandomField(int polyNumber)
{
    QVector<QVector<Ui::Point>> result;
    Field field = Field::GenerateRandom(polyNumber);
    std::vector<Polygon> polys = field.GetInnerPolygons();
    for (int i = 0; i < polys.size(); i++)
    {
        result.push_back(QVector<Ui::Point>::fromStdVector(polys[i].GetPoints()));
    }
    return result;
}
