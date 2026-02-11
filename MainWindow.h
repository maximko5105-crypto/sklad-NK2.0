#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "models/User.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class WarehouseWidget;
class ReportsWidget;
class RequestsWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(const User& user, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onWarehouseButtonClicked();
    void onReportsButtonClicked();
    void onRequestsButtonClicked();
    void onUsersButtonClicked();
    void onSettingsButtonClicked();
    void onExitButtonClicked();

private:
    void setupUi();
    void setupMenuBar();
    void setupToolBar();
    void setupConnections();
    void applyUserPermissions();

    Ui::MainWindow *ui;
    User m_currentUser;
    
    WarehouseWidget *m_warehouseWidget;
    ReportsWidget *m_reportsWidget;
    RequestsWidget *m_requestsWidget;
};

#endif // MAINWINDOW_H