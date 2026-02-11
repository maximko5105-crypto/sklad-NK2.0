#include "EmailService.h"
#include <QDebug>

EmailService::EmailService(QObject *parent) : QObject(parent)
{
}

bool EmailService::sendEmail(const QString& to, const QString& subject, 
                             const QString& body, const QStringList& attachments)
{
    Q_UNUSED(attachments);
    
    // Простая реализация для тестирования
    qDebug() << "Отправка email:";
    qDebug() << "Кому:" << to;
    qDebug() << "Тема:" << subject;
    qDebug() << "Тело:" << body;
    
    m_lastError = "Email отправлен (демо-режим)";
    return true;
}

bool EmailService::sendLowStockNotification(const QStringList& lowStockProducts)
{
    if (lowStockProducts.isEmpty()) {
        return true;
    }
    
    QString subject = "Уведомление: товары с низким запасом";
    QString body = "<h2>Товары с низким запасом:</h2><ul>";
    
    for (const QString &product : lowStockProducts) {
        body += "<li>" + product + "</li>";
    }
    
    body += "</ul><p>Пожалуйста, пополните запасы.</p>";
    
    // Отправляем администратору
    return sendEmail("admin@sklad.hk", subject, body);
}

bool EmailService::sendRequestNotification(int requestId, const QString& action)
{
    QString subject = QString("Уведомление: заявка #%1 - %2").arg(requestId).arg(action);
    QString body = QString("<h2>Заявка #%1</h2><p>Статус: %2</p>").arg(requestId).arg(action);
    
    return sendEmail("manager@sklad.hk", subject, body);
}

bool EmailService::sendDailyReport(const QString& recipient)
{
    QString subject = "Ежедневный отчет по складу";
    QString body = "<h2>Ежедневный отчет</h2><p>Отчет находится в разработке.</p>";
    
    return sendEmail(recipient, subject, body);
}

bool EmailService::validateEmail(const QString& email)
{
    return email.contains('@') && email.contains('.');
}

QString EmailService::createLowStockEmailBody(const QStringList& products)
{
    QString body = "<h2>Товары с низким запасом:</h2><ul>";
    for (const QString &product : products) {
        body += "<li>" + product + "</li>";
    }
    body += "</ul>";
    return body;
}

QString EmailService::createRequestEmailBody(int requestId, const QString& action)
{
    return QString("<h2>Заявка #%1</h2><p>Действие: %2</p>").arg(requestId).arg(action);
}

QString EmailService::createDailyReportBody()
{
    return "<h2>Ежедневный отчет по складу</h2><p>Отчет генерируется автоматически.</p>";
}

bool EmailService::loadSettings()
{
    // Загрузка настроек из файла конфигурации
    return true;
}

bool EmailService::saveSettings()
{
    // Сохранение настроек в файл конфигурации
    return true;
}