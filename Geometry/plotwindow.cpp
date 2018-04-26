#include "plotwindow.h"
#include "ui_plotwindow.h"
#include "qcustomplot/qcustomplot.h"
#include "Controller/controller.h"
#include <vector>
#include <iostream>
#include <cfloat>

PlotWindow::PlotWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlotWindow)
{
    ui->setupUi(this);
    mode = Mode::None;

    double PLOT_X_BEG = -10;
    double PLOT_X_END = 10;
    double PLOT_Y_BEG = 10;
    double PLOT_Y_END = -10;

    ui->plot->addGraph();
    ui->plot->xAxis->setRange(PLOT_X_BEG, PLOT_X_END);
    ui->plot->yAxis->setRange(PLOT_Y_BEG, PLOT_Y_END);

    points = new QCPGraph(ui->plot->xAxis, ui->plot->yAxis);
    points->setAdaptiveSampling(false);
    points->removeFromLegend();
    points->setLineStyle(QCPGraph::lsNone);
    points->setScatterStyle(QCPScatterStyle::ssCircle);
    points->setPen(QPen(QBrush(Qt::red),2));

    query = new QCPGraph(ui->plot->xAxis, ui->plot->yAxis);
    query->setAdaptiveSampling(false);
    query->removeFromLegend();
    query->setLineStyle(QCPGraph::lsNone);
    query->setScatterStyle(QCPScatterStyle::ssCircle);
    query->setPen(QPen(QBrush(Qt::green),2));

    ui->plot->replot();
    connect(ui->plot, SIGNAL(mouseRelease(QMouseEvent*))
            , this, SLOT(on_plotInput_clicked(QMouseEvent*)));
    connect(ui->visibilityList, SIGNAL(currentTextChanged(const QString &))
            , this, SLOT(update_visibilityCheck(const QString &)));
}

PlotWindow::~PlotWindow()
{
    delete ui;
}



void PlotWindow::showTaggedLines(QString tag, bool show)
{
    if (taggedState[tag] != show)
    {
        for (int i = 0; i < taggedLines[tag].size(); ++i)
            taggedLines[tag][i]->setVisible(show);
    }
}

void PlotWindow::removeLinesByTag(QString tag)
{
    if (this->taggedLines.find(tag) == this->taggedLines.end())
        return;
    auto &lines = this->taggedLines[tag];
    for (int i = 0; i < lines.size(); ++i)
        delete lines[i];
    lines.clear();
}

void PlotWindow::addTaggedLine(QString tag, QCPItemLine *line, bool show)
{
    if (taggedLines.find(tag) == taggedLines.end())
    {
        this->ui->visibilityList->setEnabled(true);
        this->ui->visibilityCheck->setEnabled(true);
        taggedState[tag] = show;
        this->ui->visibilityList->addItem(tag);
    }
    taggedLines[tag].push_back(line);
}

void PlotWindow::addLine(double x1, double y1, double x2, double y2, QString tag="", bool show=true, QColor color=Qt::red)
{
    QCPItemLine *line = new QCPItemLine(this->ui->plot);
    line->setPen(QPen(QBrush(color), 2));
    line->start->setCoords(x1, y1);
    line->end->setCoords(x2, y2);
    line->setVisible(show);
    if (tag != "") addTaggedLine(tag, line, show);
}

void PlotWindow::addPolygon(const QVector<std::pair<double, double>> &poly)
{
    int n = poly.size();
    for (int i = 0; i < n - 1; ++i)
    {
        double x1 = poly[i].first, y1 = poly[i].second, x2 = poly[i + 1].first, y2 = poly[i + 1].second;
        points->addData(x1, y1);
        this->addLine(x1, y1, x2, y2, "polygon");
    }
    points->addData(poly[n - 1].first, poly[n - 1].second);
    this->addLine(poly[n - 1].first, poly[n - 1].second, poly[0].first, poly[0].second, "polygon");
}

void PlotWindow::on_plotInput_clicked(QMouseEvent *event)
{
    double x = this->ui->plot->xAxis->pixelToCoord(event->pos().x());
    double y = this->ui->plot->yAxis->pixelToCoord(event->pos().y());
    std::pair<double, double> p = std::make_pair(x, y);

    if (this->mode == Mode::Input)
        this->buffer.push_back(p);
    else if (this->mode == Mode::Start)
    {
        query->data()->clear();
        removeLinesByTag("shortest path");
        removeLinesByTag("query-visibility graph");
        this->start = p;
        query->addData(x, y);
        this->ui->inputQuery->setEnabled(false);
        this->ui->plot->replot();
        this->mode = Mode::Finish;
    }
    else if (this->mode == Mode::Finish)
    {
        this->finish = p;
        query->addData(x, y);
        this->ui->inputQuery->setEnabled(true);
        additionalVg.clear();
        this->path = Controller::calcShortestPath(this->polygons, this->start, this->finish, additionalVg);
        for (const auto &edge: additionalVg)
        {
            Ui::Point p1 = edge.first, p2 = edge.second;
            this->addLine(p1.first, p1.second, p2.first, p2.second, "query-visibility graph", false, Qt::blue);
        }
        for (const auto &edge: this->path)
        {
            Ui::Point p1 = edge.first, p2 = edge.second;
            this->addLine(p1.first, p1.second, p2.first, p2.second, "shortest path", true, Qt::green);
        }
        this->ui->plot->replot();
        this->mode = Mode::None;
    }

    std::cerr << x << " " << y << std::endl;
}

void PlotWindow::update_visibilityCheck(const QString &tag)
{
    if (taggedState.find(tag) != taggedState.end())
        this->ui->visibilityCheck->setChecked(taggedState[tag]);
}

void PlotWindow::on_inputBegin_clicked()
{
    if (this->mode == Mode::None)
    {
        this->buffer.clear();
        ui->inputBegin->setEnabled(false);
        ui->inputEnd->setEnabled(true);
        this->mode = Mode::Input;
        ui->infoLabel->setText("Polygon input mode");
        ui->plot->replot();
    }
}

void PlotWindow::on_inputEnd_clicked()
{
    if (this->mode == Mode::Input && Controller::PolygonIsOkay(this->buffer, this->polygons))
    {
        this->polygons.push_back(this->buffer);
        this->addPolygon(this->buffer);
        this->buffer.clear();
        ui->inputBegin->setEnabled(true);
        ui->inputEnd->setEnabled(false);
        this->mode = Mode::None;
        ui->infoLabel->setText("");
        ui->plot->replot();
    }
    else if (!Controller::PolygonIsOkay(this->buffer, this->polygons))
    {
        ui->infoLabel->setText("New polygon invalid (cross existed).");
    }
}

void PlotWindow::on_visibilityCheck_toggled(bool checked)
{
    QString tag = this->ui->visibilityList->currentText();
    this->showTaggedLines(tag, checked);
    this->taggedState[tag] = checked;
    ui->plot->replot();
}

void PlotWindow::on_inputClear_clicked()
{
    this->polygons.clear();
    this->points->data()->clear();
    for (const auto& p: this->taggedLines)
        removeLinesByTag(p.first);
    this->taggedLines.clear();
    this->ui->visibilityList->clear();
    this->ui->visibilityList->setEnabled(false);

    this->taggedState.clear();
    this->ui->visibilityCheck->setEnabled(false);

    this->ui->inputFreeze->setEnabled(true);
    this->ui->inputQuery->setEnabled(false);

    query->data()->clear();

    this->ui->plot->replot();
}

void PlotWindow::on_inputFreeze_clicked()
{
    this->ui->inputFreeze->setEnabled(false);
    this->ui->inputQuery->setEnabled(true);
    vg = Controller::calcVisibilityGraph(this->polygons);
    for (const auto &edge: vg)
    {
        Ui::Point p1 = edge.first, p2 = edge.second;
        this->addLine(p1.first, p1.second, p2.first, p2.second, "visibility graph", false, Qt::blue);
    }
}

void PlotWindow::on_inputQuery_clicked()
{
    this->mode = Mode::Start;
}

void PlotWindow::on_inputRandom_clicked()
{
    auto temp_polygons = Controller::getRandomField(ui->polyNumber->value());
    std::cerr << "! "<< temp_polygons.size() << " ! ";
    for (int i = 0; i < temp_polygons[0].size(); i++)
    {
        std::cerr << "x: " << temp_polygons[0][i].first << " y: " << temp_polygons[0][i].second << std::endl;
    }
    for (QVector<std::pair<double, double>> poly : temp_polygons)
    {
        this->addPolygon(poly);
        this->polygons.push_back(poly);
    }
    ui->plot->replot();
}

void PlotWindow::on_polyNumber_valueChanged(int arg1)
{
    if (arg1 < 1)
    {
        ui->infoLabel->setText("Too small number of polygons");
        ui->inputRandom->setEnabled(false);
    }
    else if (arg1 < 101)
    {
        ui->infoLabel->setText("Random generation is possible");
        ui->inputRandom->setEnabled(true);
    }
    else
    {
        ui->infoLabel->setText("Too many polygons!");
        ui->inputRandom->setEnabled(false);
    }
}


void PlotWindow::on_polyNumber_editingFinished()
{
    if (ui->polyNumber->value() < 1)
    {
        ui->infoLabel->setText("Too small number of polygons");
        ui->inputRandom->setEnabled(false);
    }
    else if (ui->polyNumber->value() < 101)
    {
        ui->infoLabel->setText("Random generation is possible");
        ui->inputRandom->setEnabled(true);
    }
    else
    {
        ui->infoLabel->setText("Too many polygons!");
        ui->inputRandom->setEnabled(false);
    }
}
