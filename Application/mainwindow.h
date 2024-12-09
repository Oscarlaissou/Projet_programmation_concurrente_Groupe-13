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
    void start_simulation(); // Démarre la simulation

private:
    Ui::MainWindow *ui;
    QSqlDatabase db; // Connexion à la base de données
    QList<QLabel *> staffLabels; // Liste pour gérer les personnages
    QTimer *simulationTimer; // Timer pour animer les personnages
    TableController *tableController;
    StaffController *staffController;
    KitchenController *kitchenController;


    void setupTables();
    void setupKitchen();
    void connectToDatabase();
};

#endif // MAINWINDOW_H
