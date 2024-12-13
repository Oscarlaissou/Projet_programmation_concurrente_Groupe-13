#ifndef TABLECONTROLLER_H
#define TABLECONTROLLER_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

#include "Table.h"

class TableController : public QObject {
    Q_OBJECT

public:
    explicit TableController(QObject *parent = nullptr);
    void setScene(QGraphicsScene *scene);
    void setupTables(); // Organiser les tables automatiquement
    void addTable(const QString &imagePath, int x, int y, int width, int height, int capacity);

    // Méthodes supplémentaires (optionnel)
    QList<Table*> getTables() const; // Accéder à toutes les tables
    Table* getTableAt(int index) const; // Obtenir une table par index



private:
    QGraphicsScene *scene;
    QList<Table*> tables; // Liste des objets Table
};

#endif // TABLECONTROLLER_H
