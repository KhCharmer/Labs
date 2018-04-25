#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QVector>
#include "Geometry/polygon.h"
#include "Geometry/visibilitygraph.h"

namespace Ui
{
    using Point = std::pair<double, double>;
}

class Controller {
private:
    static VisibilityGraph vg;
    static Polygon
        uiPolyToModel(const QVector<std::pair<double, double>> &uiPoly);
    static QVector<std::pair<Ui::Point, Ui::Point>>
        modelEdgeToUi(const std::vector<std::pair<Point, Point>> &modelEdges);
public:
    static QVector<std::pair<Ui::Point, Ui::Point>>
        calcVisibilityGraph(QVector<QVector<std::pair<double, double>>> &polygons);
    static QVector<std::pair<Ui::Point, Ui::Point>>
        calcShortestPath(QVector<QVector<std::pair<double, double>>> &polygons
                         , Ui::Point start, Ui::Point finish
                         , QVector<std::pair<Ui::Point, Ui::Point>> &additionalsVg);
    static QVector<QVector<Ui::Point>> getRandomField();
};
#endif // CONTROLLER_H
