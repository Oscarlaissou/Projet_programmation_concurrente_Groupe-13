#ifndef CLIENTCONTROLLER_H
#define CLIENTCONTROLLER_H

#include <QObject>
#include <QGraphicsScene>
#include <QList>
#include <QRandomGenerator>
#include <QMessageBox>
#include "Client.h"
#include "TableController.h"

#include "Table.h" // Inclure Table pour son utilisation

// Déclaration avant utilisation
class TableController;

class ClientController : public QObject {
    Q_OBJECT

public:
    explicit ClientController(QObject *parent = nullptr);
    void setScene(QGraphicsScene *scene);
    Client* addClient(int id, int x, int y);  // Ajouter un client avec une taille de groupe aléatoire
    void moveClient(int id, int x, int y);   // Déplacer un client
    void removeAllClients();
    QList<Client*> getClients() const;       // Obtenir la liste des clients

    void setTableController(TableController *tableController); // Définir le contrôleur des tables
    void assignTableToClient(Client *client);                  // Assigner une table à un client
    void moveClientToAssignedTable(int id);

private:
    QGraphicsScene *scene;                  // Scène graphique
    QList<Client*> clients;                 // Liste des clients
    TableController *tableController;       // Référence au contrôleur de tables

    int generateRandomGroupSize() const;    // Générer une taille aléatoire pour le groupe
};

#endif // CLIENTCONTROLLER_H
