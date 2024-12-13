#include "ClientController.h"
#include "TableController.h"

#include <QDebug>

ClientController::ClientController(QObject *parent)
    : QObject(parent), scene(nullptr) {}

void ClientController::setScene(QGraphicsScene *scene) {
    this->scene = scene;
}

Client* ClientController::addClient(int id, int x, int y) {
    if (!scene) {
        qWarning() << "Erreur : la scène n'a pas été définie.";
        return nullptr;
    }

    // Générer une taille aléatoire pour le groupe de clients
    int groupSize = generateRandomGroupSize();

    // Créer une nouvelle instance de Client avec la taille du groupe
    Client *client = new Client(id, groupSize, x, y, this);
    clients.append(client);

    // Ajouter le point représentant le client à la scène
    scene->addItem(client->getGraphicsItem());

    qDebug() << "Client ajouté : ID =" << id << "Taille du groupe =" << groupSize
             << "Position =" << x << "," << y;

    return client;
}

void ClientController::moveClient(int id, int x, int y) {
    for (Client *client : clients) {
        if (client->getId() == id) {
            client->moveTo(x, y);
            qDebug() << "Client déplacé : ID =" << id << "Nouvelle position =" << x << "," << y;
            return;
        }
    }

    qWarning() << "Erreur : Aucun client trouvé avec l'ID" << id;
}

void ClientController::removeAllClients()
{
    for (Client *client : clients) {
        if (client->getGraphicsItem()) {
            scene->removeItem(client->getGraphicsItem()); // Supprime de la scène
        }
        delete client; // Libère la mémoire
    }
    clients.clear(); // Vide la liste des clients
}



QList<Client*> ClientController::getClients() const {
    return clients;
}

int ClientController::generateRandomGroupSize() const {
    return QRandomGenerator::global()->bounded(1, 11); // Génère un nombre entre 1 et 10
}

void ClientController::setTableController(TableController* tablecontroller) {
    tableController = tablecontroller;
}


void ClientController::assignTableToClient(Client* client) {
    if (!client) {
        qWarning() << "Erreur : Client nul";
        return;
    }

    if (!tableController) {
        qWarning() << "Erreur : TableController non défini.";
        return;
    }

    int groupSize = client->getGroupSize();
    Table* availableTable = nullptr;

    // Récupérer les tables depuis le TableController
    QList<Table*> tables = tableController->getTables();

    // Chercher une table libre qui peut accueillir le groupe
    for (Table* table : tables) {
        if (!table->isOccupied() && table->getCapacity() >= groupSize) {
            availableTable = table;
            break;
        }
    }
    if (availableTable) {
        // Assigner la table au client
        client->assignTable(availableTable);

        availableTable->setOccupied(true);

        // Afficher un message pour le maître d'hôtel
        QString message = QString("Aller à la table (%1,%2)")
                              .arg(availableTable->getGraphicsItem()->pos().x())
                              .arg(availableTable->getGraphicsItem()->pos().y());
        QMessageBox::information(nullptr, "Table Assignée", message);
    } else {
        // Si aucune table n'est disponible
        QMessageBox::warning(nullptr, "Aucune table disponible", "Attendez qu'une table soit libre.");
    }
}

void ClientController::moveClientToAssignedTable(int clientId)
{
    for (Client *client : clients) {
        if (client->getId() == clientId) {
            Table *table = client->getAssignedTable();
            if (table) {
                QPointF tablePosition = table->getGraphicsItem()->pos();
                client->moveTo(tablePosition.x(), tablePosition.y());
                qDebug() << "Client ID =" << clientId << " déplacé vers la table.";
            }
            return;
        }
    }
    qWarning() << "Aucun client trouvé avec l'ID" << clientId;
}
