#ifndef PLOTWINDOW_H
#define PLOTWINDOW_H

#include <QMainWindow>
#include "qcustomplot/qcustomplot.h"
#include <map>
#include <iostream>

namespace Ui {
class PlotWindow;
using Point = std::pair<double, double>;
}

class PlotWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlotWindow(QWidget *parent = 0);
    ~PlotWindow();
    void addLine(double x1, double y1, double x2, double y2, QString, bool, QColor);
    void addPolygon(const QVector<std::pair<double, double>> &poly);

private slots:
    void on_plotInput_clicked(QMouseEvent *);
    void update_visibilityCheck(const QString &);
    void on_inputBegin_clicked();
    void on_inputEnd_clicked();
    void on_visibilityCheck_toggled(bool checked);

    void on_inputClear_clicked();

    void on_inputFreeze_clicked();

    void on_inputQuery_clicked();

    void on_inputRandom_clicked();

private:
    std::pair<double, double> start, finish;
    std::map<QString, QVector<QCPItemLine*>> taggedLines;
    std::map<QString, bool> taggedState;
    Ui::PlotWindow *ui;
    QCPGraph *points, *query;
    QVector<std::pair<Ui::Point, Ui::Point>> vg;
    QVector<std::pair<Ui::Point, Ui::Point>> path;
    QVector<QVector<std::pair<double, double>>> polygons;
    QVector<std::pair<double, double>> buffer;
    enum class Mode { None, Input, Start, Finish } mode;

    void addTaggedLine(QString, QCPItemLine*, bool);
    void removeLinesByTag(QString);
    void showTaggedLines(QString tag, bool show);
};

#endif // PLOTWINDOW_H
