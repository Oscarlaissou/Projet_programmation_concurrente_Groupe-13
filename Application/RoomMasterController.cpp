#include "RoomMasterController.h"
#include "TableController.h"
#include "ClientController.h"

#include <QMessageBox>
#include <QDebug>
#include <QGraphicsScene>

RoomMasterController::RoomMasterController(QObject *parent)
    : QObject(parent), scene(nullptr), roomMasterItem(nullptr)
{
}

void RoomMasterController::setScene(QGraphicsScene *scene)
{
    this->scene = scene;
}

void RoomMasterController::addRoomMaster(int x, int y)
{
    if (!scene) {
        qWarning() << "Erreur : la scène n'a pas été définie.";
        return;
    }

    if (!roomMasterItem) {
        // Création de l'élément graphique
        roomMasterItem = new QGraphicsEllipseItem(0, 0, 20, 20); // Cercle bleu
        roomMasterItem->setBrush(Qt::red);

        // Positionnement à partir des coordonnées spécifiées
        roomMasterItem->setPos(x, y);

        // Ajout à la scène
        scene->addItem(roomMasterItem);

        qDebug() << "Maître d'hôtel graphique ajouté à la position" << QPoint(x, y);
    }
}

QString RoomMasterController::askGroupSize() const {
    return roomMaster.askGroupSize();  // Appel de la méthode de RoomMaster
}

void RoomMasterController::removeRoomMaster()
{
    if (roomMasterItem) {
        scene->removeItem(roomMasterItem);
        delete roomMasterItem;
        roomMasterItem = nullptr;
        qDebug() << "Maître d'hôtel supprimé de la scène.";
    } else {
        qWarning() << "Erreur : RoomMaster n'a pas été trouvé dans la scène.";
    }
}




const RoomMaster& RoomMasterController::getRoomMaster() const
{
    return roomMaster;
}
