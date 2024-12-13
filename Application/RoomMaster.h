#ifndef ROOMMASTER_H
#define ROOMMASTER_H

#include <QString>
#include <QPoint>

class RoomMaster {
public:
    RoomMaster();

    QPoint getPosition() const;
    QString askGroupSize() const;

private:
    QPoint position; // Position fixe (70, 60)
};

#endif // ROOMMASTER_H
