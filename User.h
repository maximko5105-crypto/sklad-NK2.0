#ifndef USER_H
#define USER_H

#include <QString>
#include <QDateTime>

class User
{
public:
    User();
    User(int id, const QString &username, const QString &password,
         const QString &email, const QString &role,
         const QString &fullName, const QString &phone = "",
         const QDateTime &createdAt = QDateTime::currentDateTime());
    
    int id() const { return m_id; }
    QString username() const { return m_username; }
    QString password() const { return m_password; }
    QString email() const { return m_email; }
    QString role() const { return m_role; }
    QString fullName() const { return m_fullName; }
    QString phone() const { return m_phone; }
    QDateTime createdAt() const { return m_createdAt; }
    
    bool isAdmin() const { return m_role == "admin"; }
    bool isManager() const { return m_role == "manager"; }
    bool isWorker() const { return m_role == "worker"; }
    
    void setId(int id) { m_id = id; }
    void setUsername(const QString &username) { m_username = username; }
    void setPassword(const QString &password) { m_password = password; }
    void setEmail(const QString &email) { m_email = email; }
    void setRole(const QString &role) { m_role = role; }
    void setFullName(const QString &fullName) { m_fullName = fullName; }
    void setPhone(const QString &phone) { m_phone = phone; }
    void setCreatedAt(const QDateTime &createdAt) { m_createdAt = createdAt; }
    
private:
    int m_id;
    QString m_username;
    QString m_password;
    QString m_email;
    QString m_role;
    QString m_fullName;
    QString m_phone;
    QDateTime m_createdAt;
};

#endif // USER_H