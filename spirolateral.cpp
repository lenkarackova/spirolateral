#include "spirolateral.h"

Spirolateral::Spirolateral(int segment_nr, int angle)
{
    setSegmentNumber(segment_nr);
    setAngle(angle);
    generate();
}

QPolygonF& Spirolateral::getPolygon()
{
    return polygon;
}

void Spirolateral::setAngle(int angle)
{
    this->angle = 180 - angle;
    generate();
}

void Spirolateral::setSegmentNumber(int segment_nr)
{
    this->segment_nr = segment_nr;
    generate();
}

void Spirolateral::setReverseTurns(QString str)
{
    reverse_turns.clear();
    QRegExp rx("(\\ |\\,|\\;)"); // accepts values separated by space, comma or semicolon
    QStringList str_list = str.split(rx);
    int turn_nr;

    for(QString str: str_list)
    {
        turn_nr = str.toInt();
        if (turn_nr > 0 && turn_nr <= segment_nr)
        {
            reverse_turns.push_back(turn_nr);
        }
    }

    generate();
}

void Spirolateral::generate()
{
    polygon.clear();
    closed = false;

    qreal x = init_x;
    qreal y = init_y;

    double distance;
    int cycle_nr = 0;
    int angle_multiplier = 0;
    int angle_deg;
    double angle_rad;

    polygon << QPointF(init_x,init_y);

    for (;cycle_nr < max_cycles; cycle_nr++)
    {
        distance = segment_lenght;

        for (int i = 0; i < segment_nr; i++)
        {
            if (reverse_turns.contains(i+1))
            {
                angle_multiplier--;
            }
            else
            {
                angle_multiplier++;
            }

            angle_deg = (angle_multiplier * angle) % 360;
            angle_rad = angle_deg * (M_PI/180);

            x += distance * cos(angle_rad);
            y += distance * sin(angle_rad);

            distance += segment_lenght;

            polygon << QPointF(x,y);
        }

        // check if spirolateral got closed
        if((floor(100*x+0.5))/100 == init_x && (floor(100*y+0.5))/100 == init_y)
        {
            closed = true;
            break;
        }
    }

    // unclosed spirolateral, keep only first n cycles
    if (!closed)
    {
        polygon.resize(max_unclosed_cycles * segment_nr + 1);
    }

    normalize();
}

bool Spirolateral::isClosed()
{
    return closed;
}

void Spirolateral::normalize()
{
    QRectF rect = polygon.boundingRect();
    polygon.translate(-rect.x(), -rect.y());
}
