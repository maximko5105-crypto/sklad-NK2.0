#ifndef REPORTSWIDGET_H
#define REPORTSWIDGET_H

#include "models/User.h"
#include <QWidget>
#include <QComboBox>
#include <QDateEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QTreeWidget>
#include <QGroupBox>
#include <QCheckBox>
#include <QLabel>

class ReportsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ReportsWidget(const User &currentUser, QWidget *parent = nullptr);
    void refresh();

private slots:
    void onReportTypeChanged(int index);
    void onGenerateReport();
    void onExportReport();
    void onPrintReport();

private:
    void setupUi();
    void generateInventoryReport();
    void generateMovementReport();
    void generateLowStockReport();
    void generateContainerReport();
    void updateSummary();

    User m_currentUser;

    QComboBox *m_reportTypeCombo;
    QDateEdit *m_dateFromEdit;
    QDateEdit *m_dateToEdit;
    QPushButton *m_generateButton;
    QPushButton *m_exportButton;
    QPushButton *m_printButton;
    QTableWidget *m_reportTable;
    QTreeWidget *m_summaryTree;
};

#endif // REPORTSWIDGET_H
