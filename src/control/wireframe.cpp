#include "control/wireframe.h"
#include "ui/util/colors.h"

WireframeControl::WireframeControl(Node* node, QObject* parent)
    : Control(node, parent)
{
    // Nothing to do here
}

QPainterPath WireframeControl::shape(QMatrix4x4 m, QMatrix4x4 t) const
{
    QPainterPathStroker stroker;
    stroker.setWidth(4);
    QPainterPath path = stroker.createStroke(linePath(m, t));
    path.addPath(pointPath(m, t));
    return path;
}

QRectF WireframeControl::bounds(QMatrix4x4 m, QMatrix4x4 t) const
{
    QPainterPathStroker stroker;
    stroker.setWidth(20);
    QPainterPath path = stroker.createStroke(linePath(m, t));
    path.addPath(pointPath(m, t));
    return path.boundingRect();
}

void WireframeControl::paint(QMatrix4x4 m, QMatrix4x4 t,
                             bool highlight, QPainter* painter)
{
    if (glow)
    {
        painter->setBrush(Qt::NoBrush);
        painter->setPen(QPen(QColor(255, 255, 255, Colors::base02.red()), 20));
        painter->drawPath(linePath(m, t));
        painter->drawPath(pointPath(m, t));
    }

    setDefaultPen(highlight, painter);
    painter->drawPath(linePath(m, t));
    setDefaultBrush(highlight, painter);
    painter->drawPath(pointPath(m, t));
}

QPainterPath WireframeControl::linePath(QMatrix4x4 m, QMatrix4x4 t) const
{
    QPainterPath path;
    for (auto line : lines(m, t))
    {
        path.moveTo((m*line.front()).toPointF());
        for (auto pt : line)
            path.lineTo((m*pt).toPointF());
    }
    return path;
}

QPainterPath WireframeControl::pointPath(QMatrix4x4 m, QMatrix4x4 t) const
{
    QPainterPath path;
    for (auto ptr : points(m, t))
    {
        QPointF pt = (m*ptr.first).toPointF();
        float r = ptr.second;
        path.addEllipse(QRectF(pt.x() - r, pt.y() - r, 2*r, 2*r));
    }
    return path;
}
