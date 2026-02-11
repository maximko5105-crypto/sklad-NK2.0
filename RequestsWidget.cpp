#include "RequestsWidget.h"
#include "database/DatabaseManager.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QInputDialog>
#include <QDate>
#include <QDialog>
#include <QFormLayout>
#include <QSpinBox>
#include <QComboBox>
#include <QTextEdit>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QSqlQuery>

RequestsWidget::RequestsWidget(const User& user, QWidget *parent)
    : QWidget(parent), m_currentUser(user)
{
    setupUi();
    loadRequests();
}

void RequestsWidget::setupUi() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *toolbar = new QHBoxLayout();

    m_createButton = new QPushButton("Создать заявку", this);
    m_approveButton = new QPushButton("Утвердить", this);
    m_rejectButton = new QPushButton("Отклонить", this);
    m_completeButton = new QPushButton("Завершить", this);
    m_deleteButton = new QPushButton("Удалить", this);
    m_refreshButton = new QPushButton("Обновить", this);

    m_approveButton->setEnabled(false); 
    m_rejectButton->setEnabled(false);
    m_completeButton->setEnabled(false); 
    m_deleteButton->setEnabled(false);

    toolbar->addWidget(m_createButton); 
    toolbar->addWidget(m_approveButton);
    toolbar->addWidget(m_rejectButton); 
    toolbar->addWidget(m_completeButton);
    toolbar->addWidget(m_deleteButton); 
    toolbar->addWidget(m_refreshButton);
    mainLayout->addLayout(toolbar);

    // Фильтры
    QHBoxLayout *filterbar = new QHBoxLayout();
    m_typeFilter = new QComboBox(this);
    m_typeFilter->addItem("Все типы", ""); 
    m_typeFilter->addItem("Приход", "incoming"); 
    m_typeFilter->addItem("Расход", "outgoing");
    filterbar->addWidget(m_typeFilter);
    
    m_statusFilter = new QComboBox(this);
    m_statusFilter->addItem("Любой статус", ""); 
    m_statusFilter->addItem("В ожидании", "pending");
    m_statusFilter->addItem("Утверждено", "approved"); 
    m_statusFilter->addItem("Отклонено", "rejected"); 
    m_statusFilter->addItem("Завершено", "completed");
    filterbar->addWidget(m_statusFilter);
    
    m_priorityFilter = new QComboBox(this);
    m_priorityFilter->addItem("Любой приоритет", ""); 
    m_priorityFilter->addItem("Низкий", "low");
    m_priorityFilter->addItem("Средний", "medium"); 
    m_priorityFilter->addItem("Высокий", "high");
    filterbar->addWidget(m_priorityFilter);
    
    m_searchEdit = new QLineEdit(this); 
    m_searchEdit->setPlaceholderText("Поиск (номер, товар, пользователь)");
    filterbar->addWidget(m_searchEdit);
    
    m_dateFrom = new QDateEdit(QDate::currentDate().addDays(-30), this);
    m_dateTo = new QDateEdit(QDate::currentDate(), this);
    filterbar->addWidget(new QLabel("С:")); 
    filterbar->addWidget(m_dateFrom);
    filterbar->addWidget(new QLabel("По:")); 
    filterbar->addWidget(m_dateTo);
    mainLayout->addLayout(filterbar);

    m_table = new QTableWidget(this);
    m_table->setColumnCount(8);
    m_table->setHorizontalHeaderLabels({"ID","Номер","Товар","Тип","Кол-во","Статус","Пользователь","Дата"});
    m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_table->setSelectionMode(QAbstractItemView::SingleSelection);
    m_table->horizontalHeader()->setStretchLastSection(true);
    mainLayout->addWidget(m_table);

    m_statsLabel = new QLabel(this);
    mainLayout->addWidget(m_statsLabel);

    connect(m_createButton, &QPushButton::clicked, this, &RequestsWidget::onCreateRequest);
    connect(m_deleteButton, &QPushButton::clicked, this, &RequestsWidget::onDeleteRequest);
    connect(m_approveButton, &QPushButton::clicked, this, &RequestsWidget::onApproveRequest);
    connect(m_rejectButton, &QPushButton::clicked, this, &RequestsWidget::onRejectRequest);
    connect(m_completeButton, &QPushButton::clicked, this, &RequestsWidget::onCompleteRequest);
    connect(m_refreshButton, &QPushButton::clicked, this, &RequestsWidget::refresh);

    connect(m_typeFilter, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &RequestsWidget::onFilterChanged);
    connect(m_statusFilter, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &RequestsWidget::onFilterChanged);
    connect(m_priorityFilter, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &RequestsWidget::onFilterChanged);
    connect(m_searchEdit, &QLineEdit::textChanged, this, &RequestsWidget::onFilterChanged);
    connect(m_dateFrom, &QDateEdit::dateChanged, this, &RequestsWidget::onFilterChanged);
    connect(m_dateTo, &QDateEdit::dateChanged, this, &RequestsWidget::onFilterChanged);

    connect(m_table, &QTableWidget::itemSelectionChanged, this, &RequestsWidget::updateButtonsState);
    connect(m_table, &QTableWidget::cellDoubleClicked, this, &RequestsWidget::onTableDoubleClicked);
}

void RequestsWidget::refresh() { 
    loadRequests(); 
}

void RequestsWidget::loadRequests() {
    m_table->setRowCount(0);
    QSqlQuery q = DatabaseManager::instance().getAllRequests();

    int total=0, pending=0, approved=0, rejected=0, completed=0;

    while(q.next()) {
        QString type = q.value("type").toString();
        QString status = q.value("status").toString();
        QString priority = q.value("priority").toString();
        int prodId = q.value("product_id").toInt();
        int uid = q.value("user_id").toInt();
        QDateTime created = q.value("created_at").toDateTime();

        // фильтрация
        if (!m_typeFilter->currentData().toString().isEmpty() && 
            m_typeFilter->currentData().toString() != type) 
            continue;
        if (!m_statusFilter->currentData().toString().isEmpty() && 
            m_statusFilter->currentData().toString() != status) 
            continue;
        if (!m_priorityFilter->currentData().toString().isEmpty() && 
            m_priorityFilter->currentData().toString() != priority) 
            continue;
        if (created.date() < m_dateFrom->date() || created.date() > m_dateTo->date()) 
            continue;

        QString prodName = "";
        QSqlQuery pr = DatabaseManager::instance().getProductById(prodId); 
        if (pr.next()) 
            prodName = pr.value("name").toString();
        
        QString userName = "";
        QSqlQuery ur; 
        ur.prepare("SELECT username FROM users WHERE id=?"); 
        ur.addBindValue(uid); 
        if (ur.exec() && ur.next()) 
            userName = ur.value("username").toString();

        QString search = m_searchEdit->text().trimmed().toLower();
        if (!search.isEmpty()
            && !(q.value("request_number").toString().toLower().contains(search)
              || prodName.toLower().contains(search)
              || userName.toLower().contains(search))
        ) continue;

        // статистика
        ++total; 
        if(status=="pending") ++pending; 
        else if(status=="approved") ++approved;
        else if(status=="completed") ++completed; 
        else if(status=="rejected") ++rejected;

        int r = m_table->rowCount();
        m_table->insertRow(r);
        m_table->setItem(r,0,new QTableWidgetItem(q.value("id").toString()));
        m_table->setItem(r,1,new QTableWidgetItem(q.value("request_number").toString()));
        m_table->setItem(r,2,new QTableWidgetItem(prodName));
        m_table->setItem(r,3,new QTableWidgetItem(type=="incoming"?"Приход":"Расход"));
        m_table->setItem(r,4,new QTableWidgetItem(q.value("quantity").toString()));
        m_table->setItem(r,5,new QTableWidgetItem(status));
        m_table->setItem(r,6,new QTableWidgetItem(userName));
        m_table->setItem(r,7,new QTableWidgetItem(created.toString("dd.MM.yyyy hh:mm")));
    }
    
    m_statsLabel->setText(
        QString("Всего: %1 | Ожидание: %2 | Утверждено: %3 | Завершено: %4 | Отклонено: %5")
        .arg(total).arg(pending).arg(approved).arg(completed).arg(rejected)
    );
    m_table->resizeColumnsToContents();
}

void RequestsWidget::onCreateRequest() {
    QDialog dialog(this);
    dialog.setWindowTitle("Создание заявки");
    QFormLayout *form = new QFormLayout(&dialog);

    QComboBox *typeCombo = new QComboBox(&dialog); 
    typeCombo->addItem("Приход", "incoming"); 
    typeCombo->addItem("Расход", "outgoing");
    form->addRow("Тип:", typeCombo);
    
    QComboBox *prodCombo = new QComboBox(&dialog);
    QSqlQuery pr = DatabaseManager::instance().getAllProducts();
    while (pr.next()) 
        prodCombo->addItem(pr.value("name").toString(), pr.value("id").toInt());
    form->addRow("Товар:", prodCombo);
    
    QSpinBox *qtyBox = new QSpinBox(&dialog); 
    qtyBox->setMinimum(1); 
    qtyBox->setMaximum(10000);
    form->addRow("Количество:", qtyBox);
    
    QComboBox *prioCombo = new QComboBox(&dialog); 
    prioCombo->addItem("Низкий","low"); 
    prioCombo->addItem("Средний","medium"); 
    prioCombo->addItem("Высокий","high");
    form->addRow("Приоритет:", prioCombo);
    
    QTextEdit *comments = new QTextEdit(&dialog); 
    form->addRow("Комментарий:", comments);
    
    QHBoxLayout* hbox = new QHBoxLayout();
    QPushButton* btnOk = new QPushButton("Создать", &dialog);
    QPushButton* btnCancel = new QPushButton("Отмена", &dialog);
    hbox->addWidget(btnOk); 
    hbox->addWidget(btnCancel); 
    form->addRow(hbox);

    connect(btnOk, &QPushButton::clicked, &dialog, [&]{
        if (prodCombo->currentIndex() < 0) {
            QMessageBox::warning(&dialog, "Ошибка", "Выберите товар!");
            return;
        }
        
        QString reqNo = "REQ-" + QDateTime::currentDateTime().toString("yyyyMMddHHmmss");
        if (DatabaseManager::instance().addRequest(
            reqNo, m_currentUser.id(),
            prodCombo->currentData().toInt(),
            qtyBox->value(),
            typeCombo->currentData().toString(),
            "pending",
            prioCombo->currentData().toString(),
            comments->toPlainText()
        )) {
            dialog.accept();
        } else {
            QMessageBox::warning(&dialog,"Ошибка","Не удалось создать заявку");
        }
    });
    
    connect(btnCancel, &QPushButton::clicked, &dialog, &QDialog::reject);
    
    if (dialog.exec() == QDialog::Accepted) 
        loadRequests();
}

void RequestsWidget::onDeleteRequest() {
    int row = m_table->currentRow(); 
    if(row < 0) return;
    
    int id = m_table->item(row,0)->text().toInt();
    if (QMessageBox::question(this,"Удалить","Удалить заявку?",QMessageBox::Yes|QMessageBox::No) == QMessageBox::No) 
        return;
    
    QSqlQuery q; 
    q.prepare("DELETE FROM requests WHERE id=?"); 
    q.addBindValue(id);
    if (!q.exec()) 
        QMessageBox::warning(this,"Ошибка","Ошибка при удалении");
    
    loadRequests();
}

void RequestsWidget::onApproveRequest() {
    int row = m_table->currentRow(); 
    if(row < 0) return;
    
    int id = m_table->item(row,0)->text().toInt();
    if (DatabaseManager::instance().updateRequestStatus(id,"approved")) 
        loadRequests();
}

void RequestsWidget::onRejectRequest() {
    int row = m_table->currentRow(); 
    if(row < 0) return;
    
    int id = m_table->item(row,0)->text().toInt();
    if (DatabaseManager::instance().updateRequestStatus(id,"rejected")) 
        loadRequests();
}

void RequestsWidget::onCompleteRequest() {
    int row = m_table->currentRow(); 
    if(row < 0) return;
    
    int id = m_table->item(row,0)->text().toInt();
    if (DatabaseManager::instance().updateRequestStatus(id,"completed")) 
        loadRequests();
}

void RequestsWidget::onFilterChanged() { 
    loadRequests(); 
}

void RequestsWidget::updateButtonsState() {
    bool sel = m_table->currentRow() >= 0;
    m_deleteButton->setEnabled(sel);
    
    bool okstat = false, okcomp = false;
    if(sel) {
        QString st = m_table->item(m_table->currentRow(),5)->text();
        okstat = (st=="pending");
        okcomp = (st=="approved");
    }
    
    bool hasPermission = (m_currentUser.isAdmin() || m_currentUser.isManager());
    m_approveButton->setEnabled(okstat && hasPermission);
    m_rejectButton->setEnabled(okstat && hasPermission);
    m_completeButton->setEnabled(okcomp && hasPermission);
}

void RequestsWidget::onTableDoubleClicked(int row, int) {
    if(row < 0) return;
    
    int id = m_table->item(row,0)->text().toInt();
    QString info = "Заявка №" + m_table->item(row,1)->text()
        + "\nТовар: " + m_table->item(row,2)->text()
        + "\nТип: " + m_table->item(row,3)->text()
        + "\nКол-во: " + m_table->item(row,4)->text()
        + "\nСтатус: " + m_table->item(row,5)->text()
        + "\nПользователь: " + m_table->item(row,6)->text()
        + "\nДата: " + m_table->item(row,7)->text();
    
    QSqlQuery q; 
    q.prepare("SELECT comments FROM requests WHERE id=?"); 
    q.addBindValue(id); 
    if (q.exec() && q.next()) {
        QString comments = q.value(0).toString();
        if (!comments.isEmpty()) {
            info += "\nКомментарий:\n" + comments;
        }
    }
    
    QMessageBox::information(this,"Детали заявки",info);
}