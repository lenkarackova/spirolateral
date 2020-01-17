#ifndef SPIROLATERAL_H
#define SPIROLATERAL_H

#include <QVector>
#include <cmath>
#include <QLine>
#include <QPolygonF>

class Spirolateral
{
public:
    Spirolateral(int segment_nr, int angle);
    QPolygonF& getPolygon();
    void setAngle(int angle);
    void setSegmentNumber(int segment_nr);
    void setReverseTurns(QString str);
    bool isClosed();

private:
    int segment_nr;
    int angle;
    bool closed;

    static const int segment_lenght = 10;
    static const int init_x = 0;
    static const int init_y = 0;
    static const int max_cycles = 1000;
    static const int max_unclosed_cycles = 7;

    QPolygonF polygon;
    QVector<int> reverse_turns;

    void generate();
    void normalize();
};

#endif // SPIROLATERAL_H
