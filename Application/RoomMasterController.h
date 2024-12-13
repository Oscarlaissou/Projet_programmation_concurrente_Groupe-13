#ifndef ROOMMASTERCONTROLLER_H
#define ROOMMASTERCONTROLLER_H
#include "ClientController.h"
#include "TableController.h"
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include "RoomMaster.h"

class RoomMasterController : public QObject
{
    Q_OBJECT

public:
    explicit RoomMasterController(QObject *parent = nullptr);
    void setScene(QGraphicsScene *scene);
    void addRoomMaster(int x, int y); // Méthode pour ajouter un RoomMaster à la scène
    void removeRoomMaster(); // Méthode pour supprimer le RoomMaster de la scène

     QString askGroupSize() const;

    const RoomMaster& getRoomMaster() const;

private:
    QGraphicsScene *scene = nullptr;
    QGraphicsEllipseItem *roomMasterItem = nullptr;
    RoomMaster roomMaster;
};

#endif // ROOMMASTERCONTROLLER_H
