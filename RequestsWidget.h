#ifndef REQUESTSWIDGET_H
#define REQUESTSWIDGET_H

#include "models/User.h"
#include <QWidget>

// Предварительные объявления классов Qt
class QComboBox;
class QDateEdit;
class QPushButton;
class QTableWidget;
class QLineEdit;
class QLabel;

class RequestsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RequestsWidget(const User &currentUser, QWidget *parent = nullptr);
    void refresh();

private slots:
    void onCreateRequest();
    void onDeleteRequest();
    void onApproveRequest();
    void onRejectRequest();
    void onCompleteRequest();
    void onFilterChanged();
    void updateButtonsState();
    void onTableDoubleClicked(int row, int column);

private:
    void setupUi();
    void loadRequests();

    // Данные
    User m_currentUser;

    // UI элементы
    QPushButton *m_createButton;
    QPushButton *m_approveButton;
    QPushButton *m_rejectButton;
    QPushButton *m_completeButton;
    QPushButton *m_deleteButton;
    QPushButton *m_refreshButton;
    
    QComboBox *m_typeFilter;
    QComboBox *m_statusFilter;
    QComboBox *m_priorityFilter;
    QLineEdit *m_searchEdit;
    QDateEdit *m_dateFrom;
    QDateEdit *m_dateTo;
    
    QTableWidget *m_table;
    QLabel *m_statsLabel;
};

#endif // REQUESTSWIDGET_H