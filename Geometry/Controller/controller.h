#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QVector>
#include "Geometry/polygon.h"

namespace Ui
{
    using Point = std::pair<double, double>;
}

class Controller {
private:
    static Polygon
        uiPolyToModel(const QVector<std::pair<double, double>> &uiPoly);
    static QVector<std::pair<Ui::Point, Ui::Point>>
        modelEdgeToUi(const std::vector<std::pair<Point, Point>> &modelEdges);
public:
    static QVector<std::pair<Ui::Point, Ui::Point>>
        calcVisibilityGraph(QVector<QVector<std::pair<double, double>>> &polygons);
    static QVector<std::pair<Ui::Point, Ui::Point>>
        calcShortestPath(QVector<QVector<std::pair<double, double>>> &polygons
                                 , QVector<std::pair<Ui::Point, Ui::Point>> &vg
                                 , Ui::Point start, Ui::Point finish);
};
#endif // CONTROLLER_H
