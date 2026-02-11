#include "src/widgets/ReportsWidget.h"
#include "widgets/RequestsWidget.h"
#include "widgets/WarehouseWidget.h"
#include <QVBoxLayout>
#include <QLabel>

ReportsWidget::ReportsWidget(const User &currentUser, QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Модуль отчетов в разработке", this));
}

void ReportsWidget::refresh() {}

RequestsWidget::RequestsWidget(const User &currentUser, QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Модуль заявок в разработке", this));
}

void RequestsWidget::refresh() {}

WarehouseWidget::WarehouseWidget(const User &currentUser, QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Модуль склада в разработке", this));
}

void WarehouseWidget::refresh() {}