#ifndef ORDERCONTROLLER_H
#define ORDERCONTROLLER_H

#include <QObject>
#include <QSqlDatabase>
#include <QRandomGenerator>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QList>
#include <QString>
#include <QDebug>

class OrderController : public QObject {
    Q_OBJECT
public:
    explicit OrderController(QSqlDatabase db, QObject *parent = nullptr);
    QList<QString> getMenuItems();
    void placeOrderForClient(int clientId);

private:
    QSqlDatabase db;
    QList<QString> menuItems;
    bool insertOrderIntoDatabase(int clientId, const QString &menuItem, const QString &dateCommande, const QString &heureCommande, const QString &status);


    void loadMenuItems();
};

#endif // ORDERCONTROLLER_H
