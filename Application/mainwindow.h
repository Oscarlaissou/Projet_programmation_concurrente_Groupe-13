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
#include "StaffController.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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
    TableController *tableController;
    StaffController *staffController;
    ViewWindow *viewWindow;            // Pointeur vers ViewWindow

    // Gestion du temps pour le chronomètre
    QTimer *timer;                     // Timer pour le suivi du temps
    int elapsedSeconds;                // Temps écoulé en secondes

    void start_simulation();
    void setupTables();
    void connectToDatabase();
};

#endif // MAINWINDOW_H
