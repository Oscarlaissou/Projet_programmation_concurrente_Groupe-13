#include "KitchenController.h"
#include <QDebug>
#include <QPixmap>

KitchenController::KitchenController(QObject *parent)
    : QObject(parent), scene(nullptr) {}

void KitchenController::setScene(QGraphicsScene *scene) {
    this->scene = scene;
}



void KitchenController::addKitchenElement(const QString &imagePath, int x, int y) {
     QPixmap pixmap(imagePath);

    if (pixmap.isNull()) {
        qWarning() << "Erreur : Impossible de charger l'image" << imagePath;
        return;
    }



    // Appliquer une taille spécifique en fonction des mots-clés
    if (imagePath.contains("chambre_froide", Qt::CaseInsensitive)) {
        pixmap = pixmap.scaled(140, 140, Qt::KeepAspectRatio);
    } else if (imagePath.contains("cuisin", Qt::CaseInsensitive)) {
        pixmap = pixmap.scaled(200, 200, Qt::KeepAspectRatio);
    } else if (imagePath.contains("refri", Qt::CaseInsensitive)) {
        pixmap = pixmap.scaled(200, 200, Qt::KeepAspectRatio);
    }else if (imagePath.contains("comptoir", Qt::CaseInsensitive)) {
        pixmap = pixmap.scaled(200, 200, Qt::KeepAspectRatio);
    } else {
        // Taille par défaut pour les autres éléments
        pixmap = pixmap.scaled(100, 100, Qt::KeepAspectRatio);
    }

    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap);
    item->setPos(x, y);


    // Ajouter l'élément à la scène
    if (scene) {
        scene->addItem(item);
    }
}

QGraphicsPixmapItem* KitchenController::addCharacter(const QString& imagePath, int x, int y) {
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(QPixmap(imagePath));
    item->setPos(x, y);
    scene->addItem(item);
    return item;
}


//     kitchenItem->setPos(x, y);
//     scene->addItem(kitchenItem);
//     kitchenElements.append(kitchenItem);
//}
