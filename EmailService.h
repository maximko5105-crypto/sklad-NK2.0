#ifndef EMAILSERVICE_H
#define EMAILSERVICE_H

#include <QObject>
#include <QString>
#include <QStringList>

class EmailService : public QObject
{
    Q_OBJECT

public:
    explicit EmailService(QObject *parent = nullptr);
    
    bool sendEmail(const QString& to, const QString& subject, 
                   const QString& body, const QStringList& attachments = QStringList());
    bool sendLowStockNotification(const QStringList& lowStockProducts);
    bool sendRequestNotification(int requestId, const QString& action);
    bool sendDailyReport(const QString& recipient);
    
    void setSmtpServer(const QString& server) { m_smtpServer = server; }
    void setSmtpPort(int port) { m_smtpPort = port; }
    void setUsername(const QString& username) { m_username = username; }
    void setPassword(const QString& password) { m_password = password; }
    void setUseSsl(bool use) { m_useSsl = use; }
    
    QString lastError() const { return m_lastError; }
    
    bool loadSettings();
    bool saveSettings();

private:
    QString m_smtpServer = "smtp.gmail.com";
    int m_smtpPort = 587;
    QString m_username = "";
    QString m_password = "";
    bool m_useSsl = true;
    QString m_lastError = "";
    
    bool validateEmail(const QString& email);
    QString createLowStockEmailBody(const QStringList& products);
    QString createRequestEmailBody(int requestId, const QString& action);
    QString createDailyReportBody();
};

#endif // EMAILSERVICE_H