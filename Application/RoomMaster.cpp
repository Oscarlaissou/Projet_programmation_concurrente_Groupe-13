#include "RoomMaster.h"

RoomMaster::RoomMaster()
    : position(400, 60) // Position fixe
{
}

QPoint RoomMaster::getPosition() const {
    return position;
}

QString RoomMaster::askGroupSize() const {
    return "Combien êtes-vous ?";
}
