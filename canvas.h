#ifndef CANVAS_H
#define CANVAS_H

#include <QtGui>
#include <QWidget>
#include <QColorDialog>
#include "spirolateral.h"

class Canvas : public QWidget
{
    Q_OBJECT
private:
    Spirolateral spirolateral;
    static const int padding = 20;
    QPolygonF polygon;
    QColor line_color;
    QColor background_color;
    QColor fill_color;
    bool use_fill;
    double line_width;

    void getSpirolateral();

public:
    explicit Canvas(QWidget *parent = nullptr);
    void paint(QPainter &painter);

public slots:
    //void setAntialiased(bool antialiased);
    void setAngle(int angle);
    void setSegmentNumber(int segment_nr);
    void setReverseTurns(QString str);
    void setLineColor();
    void setLineColor(QColor color);
    void setBackgroundColor();
    void setBackgroundColor(QColor color);
    void setFillColor();
    void setFillColor(QColor color);
    void setUseFill(int state);
    void setLineWidth(double width);

signals:
    void lineColorChanged(QColor color);
    void backgroundColorChanged(QColor color);
    void fillColorChanged(QColor color);

protected:
    void paintEvent(QPaintEvent *);

signals:
};

#endif // CANVAS_H
