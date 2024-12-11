#ifndef TABLECONTROLLER_H
#define TABLECONTROLLER_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

class TableController : public QObject {
    Q_OBJECT

public:
    explicit TableController(QObject *parent = nullptr);
    void setScene(QGraphicsScene *scene); // Définir la scène
    void addTable(const QString &imagePath, int x, int y); // Ajouter une table

private:
    QGraphicsScene *scene;
    QList<QGraphicsPixmapItem *> tables;
};

#endif // TABLECONTROLLER_H
