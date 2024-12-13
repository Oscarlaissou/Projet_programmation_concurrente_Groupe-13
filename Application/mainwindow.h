#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QList>
#include <QLabel>
#include <QTimer>
#include <QTime>

#include "viewwindow.h"
#include "TableController.h"
#include "KitchenController.h"
#include "chefdecuisine.h"
#include "chefdepatisserie.h"
#include "plongeur.h"
#include "chefdepartie.h"
#include "commis1.h"
#include "commis2.h"
#include "ClientController.h"
#include "RoomMasterController.h"
#include "OrderController.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Simulation management
    void start_simulation();
    void pause_simulation();
    void handleNewClient();

    // Kitchen animations
    void startChefAnimation(QWidget *rightPanel);
    void startChefpatisserie(QWidget *rightPanel);
    void startplongeur(QWidget *rightPanel);
    void startchefpartie(QWidget *rightPanel);
    void startcommis1(QWidget *rightPanel);
    void startcommis2(QWidget *rightPanel);

    bool isSimulationRunning = false;
    bool simulationStarted = false;

private slots:
    void onStartButtonClicked();       // Bouton Démarrer
    void onPauseButtonClicked();       // Bouton Pause
    void onStopButtonClicked();        // Bouton Stop
    void updateTimeDisplay();          // Mise à jour de l'affichage du temps
    void onDashboardButtonClicked();   // Bouton Dashboard (nouveau slot)

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;                   // Connexion à la base de données
    QList<QLabel *> staffLabels;       // Liste pour gérer les personnages

    QTimer *simulationTimer;           // Chronomètre pour la simulation
    QTimer *clientCreationTimer;
    QTimer *timer;                     // Timer pour le suivi du temps
    int elapsedSeconds;                // Temps écoulé en secondes

    // Controllers
    TableController *tableController;
    KitchenController *kitchenController;
    ClientController *clientController;
    RoomMasterController *roomMasterController;
    OrderController *orderController;

    // Kitchen staff
    chefdecuisine *chefCuisine;
    chefdepatisserie *chefPatisserie;

    // Views
    ViewWindow *viewWindow;

    // Methods
    void assignTableToClient(Client *client, TableController *tableController);
    void addClient();
    void removeAllClients();
    void moveClient();
    void setupTables();
    void setupKitchen();
    void connectToDatabase();
    void setupRoomMaster(); // Ajouter la configuration du RoomMaster
};

#endif // MAINWINDOW_H
