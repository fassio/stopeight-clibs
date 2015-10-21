#ifndef DPOINT_H
#define DPOINT_H

#include "legacy_global.h"

#include <QDebug>
#include <QPointF>
#include <QDataStream>
#include <cmath>

class LEGACYSHARED_EXPORT dpoint : public QPointF
{
public:
    dpoint();
    dpoint(const QPointF& point);

    QPointF rot;
    //float position;
    qreal position;

    /*inline dpoint &operator=(QPointF &p)  {
    this->rx()=p.x();
    this->ry()=p.y();
    this->height = 0;
    this->delta1 = QPointF();
    this->delta2 = QPointF();
    this->rot = QPointF();
    this->pressure = 0;
    return *this;
    }*/

};

LEGACYSHARED_EXPORT inline bool operator==(const dpoint &p1, const dpoint &p2)
{
    if (p1.position==p2.position){
        return true;
    } else {
        return false;
    }
}

LEGACYSHARED_EXPORT QDebug operator<<(QDebug dbg, const dpoint &dp);

LEGACYSHARED_EXPORT QDataStream &operator<<(QDataStream &out, const dpoint &dp);
LEGACYSHARED_EXPORT QDataStream &operator>>(QDataStream &in, dpoint &dp);

#endif // DPOINT_H
