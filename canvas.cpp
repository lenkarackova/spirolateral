#include "canvas.h"

Canvas::Canvas(QWidget *parent) : QWidget(parent), spirolateral(6,98)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    getSpirolateral();

    line_width = 1.0;
    background_color = Qt::black;
    use_fill = false;
    setLineColor(Qt::yellow);
}

void Canvas::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    paint(painter);
}

void Canvas::setAngle(int angle)
{
    spirolateral.setAngle(angle);
    getSpirolateral();
    update();
}

void Canvas::setSegmentNumber(int segment_nr)
{
    spirolateral.setSegmentNumber(segment_nr);
    getSpirolateral();
    update();
}

void Canvas::setReverseTurns(QString str)
{
    spirolateral.setReverseTurns(str);
    getSpirolateral();
    update();
}

void Canvas::setLineColor()
{
    QColor color = QColorDialog::getColor();
    if (!color.isValid())
        return;
    else
        setLineColor(color);
}

void Canvas::setLineColor(QColor color)
{
    line_color = color;
    emit lineColorChanged(color);
    update();
}

void Canvas::setBackgroundColor()
{
    QColor color = QColorDialog::getColor();
    if (!color.isValid())
        return;
    else
        setBackgroundColor(color);
}

void Canvas::setBackgroundColor(QColor color)
{
    background_color = color;
    emit backgroundColorChanged(color);
    update();
}

void Canvas::setLineWidth(double width)
{
    line_width = width;
    update();
}

void Canvas::setFillColor()
{
    QColor color = QColorDialog::getColor();
    if (!color.isValid())
        return;
    else
        setFillColor(color);
}

void Canvas::setFillColor(QColor color)
{
    fill_color = color;
    emit fillColorChanged(color);
    update();
}

void Canvas::setUseFill(int state)
{
    use_fill = (state == Qt::Unchecked) ? false : true;
    update();
}

void Canvas::getSpirolateral()
{
    polygon = spirolateral.getPolygon();
}

void Canvas::paint(QPainter &painter)
{
    qreal viewport_height = painter.viewport().height();
    qreal viewport_width = painter.viewport().width();
    qreal polygon_width = polygon.boundingRect().width();
    qreal polygon_height = polygon.boundingRect().height();
    qreal polygon_ratio = polygon_width/polygon_height;
    qreal viewport_ratio = viewport_width/viewport_height;

    qreal padding_top = padding;
    qreal padding_left = padding;

    qreal scale;
    if (polygon_ratio < viewport_ratio)
    {
        scale = (viewport_height-2*padding)/polygon_height;
        padding_left = (viewport_width-(scale*polygon_width))/2;
    }
    else
    {
        scale = (viewport_width-2*padding)/polygon_width;
        padding_top = (viewport_height-(scale*polygon_height))/2;
    }

    QTransform transform;
    transform.translate(padding_left,padding_top);
    transform.scale(scale,scale);

    if (line_width > 0)
    {
        QPen pen;
        pen.setWidthF(line_width);
        pen.setColor(line_color);
        pen.setJoinStyle(Qt::MiterJoin);
        painter.setPen(pen);
    }
    else
    {
        painter.setPen(Qt::NoPen);
    }

    if (use_fill)
    {
        QBrush brush(fill_color);
        painter.setBrush(brush);
    }

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillRect(rect(), QBrush(background_color));

    if (spirolateral.isClosed())
    {
        painter.drawPolygon(transform.map(polygon));
    }
    else
    {
        painter.drawPolyline(transform.map(polygon));
    }
}
