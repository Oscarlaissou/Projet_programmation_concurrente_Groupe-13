#include "OrderController.h"

OrderController::OrderController(QSqlDatabase db, QObject *parent)
    : QObject(parent), db(std::move(db))
{
    if (!this->db.isOpen()) {
        qDebug() << "La base de données n'est pas ouverte.";
    } else {
        qDebug() << "Connexion à la base de données établie.";
        loadMenuItems(); // Charger les éléments du menu à l'initialisation
    }
}

void OrderController::loadMenuItems() {
    if (!db.isOpen()) {
        qDebug() << "La base de données n'est pas ouverte.";
        return;
    }

    QSqlQuery query(db);
    if (!query.prepare("SELECT Titre FROM Recette")) {
        qDebug() << "Erreur lors de la préparation de la requête :" << query.lastError().text();
        return;
    }

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête :" << query.lastError().text();
        return;
    }

    while (query.next()) {
        QString itemName = query.value(0).toString();
        menuItems.append(itemName);
    }

    if (menuItems.isEmpty()) {
        qDebug() << "La liste des menus est vide.";
    } else {
        qDebug() << "Menu items récupérés :" << menuItems;
    }
}

QList<QString> OrderController::getMenuItems() {
    return menuItems;
}

void OrderController::placeOrderForClient(int clientId) {
    if (menuItems.isEmpty()) {
        qDebug() << "Impossible de passer une commande : la liste des menus est vide.";
        return;
    }

    // Sélection aléatoire d'un élément du menu
    int randomIndex = QRandomGenerator::global()->bounded(menuItems.size());
    QString chosenItem = menuItems[randomIndex];

    // Affichage d'une boîte de dialogue avec l'élément choisi
    QMessageBox::information(nullptr, "Commande du client",
                             QString("Le client %1 a choisi de consommer : %2")
                                 .arg(clientId).arg(chosenItem));

    // Insertion de la commande dans la base de données
    QString dateCommande = "2024-12-13 15:00:00"; // La date spécifiée
    QString heureCommande = "15:00"; // L'heure spécifiée
    QString status = "En attente"; // Le statut spécifié

    if (insertOrderIntoDatabase(clientId, chosenItem, dateCommande, heureCommande, status)) {
        qDebug() << "Commande insérée avec succès.";
    } else {
        qDebug() << "Erreur lors de l'insertion de la commande.";
    }
}

bool OrderController::insertOrderIntoDatabase(int clientId, const QString &menuItem, const QString &dateCommande, const QString &heureCommande, const QString &status) {
    if (!db.isOpen()) {
        qDebug() << "Erreur : La base de données n'est pas ouverte.";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("INSERT INTO Commande (Date_Commande, Status, Client_ID, Heure) VALUES (:dateCommande, :status, :clientId, :heure)");
    query.bindValue(":dateCommande", dateCommande);
    query.bindValue(":status", status);
    query.bindValue(":clientId", clientId);
    query.bindValue(":heure", heureCommande);

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'insertion de la commande :" << query.lastError().text();
        return false;
    }

    return true;
}
