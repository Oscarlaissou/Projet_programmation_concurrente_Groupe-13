#ifndef KITCHENCONTROLLER_H
#define KITCHENCONTROLLER_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

class KitchenController : public QObject {
    Q_OBJECT

public:
    QGraphicsPixmapItem* addCharacter(const QString& imagePath, int x, int y);
    QVector<QPoint> getObjectPositions() const;
    explicit KitchenController(QObject *parent = nullptr);
    void setScene(QGraphicsScene *scene); // Définir la scène
    void addKitchenElement(const QString &imagePath, int x, int y); // Ajouter un élément

private:
    QGraphicsScene *scene;
    QList<QGraphicsPixmapItem *> kitchenElements;
};

#endif // KITCHENCONTROLLER_H
