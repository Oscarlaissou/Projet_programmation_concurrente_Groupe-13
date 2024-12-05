#ifndef TABLE_H
#define TABLE_H

#include <QObject>
#include <QLabel>
#include <QPixmap>

class Table : public QObject
{
    Q_OBJECT

public:
    explicit Table(const QString &imagePath, int x, int y, QWidget *parent = nullptr);
    QLabel* getLabel() const;

private:
    QLabel *tableLabel; // QLabel pour représenter l'image de la table
};

#endif // TABLE_H
