#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QList>
#include <QLabel>
#include <QTimer>
#include "TableController.h"
#include "StaffController.h"
#include "KitchenController.h"
#include "chefdecuisine.h"
#include "chefdepatisserie.h"
#include "plongeur.h"
#include "chefdepartie.h"
#include "commis1.h"
#include "commis2.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
     void startChefAnimation(QWidget *rightPanel);
    void startChefpatisserie(QWidget *rightPanel);
     void startplongeur(QWidget *rightPanel);
    void startchefpartie(QWidget *rightPanel);
     void startcommis1(QWidget *rightPanel);
      void startcommis2(QWidget *rightPanel);
     bool isSimulationRunning = false;

private slots:
    void start_simulation(); // Démarre la simulation
    void pause_simulation();
private:
    Ui::MainWindow *ui;
    QSqlDatabase db; // Connexion à la base de données
    QList<QLabel *> staffLabels; // Liste pour gérer les personnages
    QTimer *simulationTimer; // Timer pour animer les personnages
    TableController *tableController;
    StaffController *staffController;
    KitchenController *kitchenController;
    chefdecuisine *chefCuisine;
    chefdepatisserie *chefPatisserie;


    void setupTables();
    void setupKitchen();
    void connectToDatabase();
};

#endif // MAINWINDOW_H
