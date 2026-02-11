#include "User.h"

User::User() : m_id(0), m_username(""), m_password(""), m_email(""), 
               m_role(""), m_fullName(""), m_phone("")
{
    m_createdAt = QDateTime::currentDateTime();
}

User::User(int id, const QString &username, const QString &password,
           const QString &email, const QString &role,
           const QString &fullName, const QString &phone,
           const QDateTime &createdAt)
    : m_id(id), m_username(username), m_password(password),
      m_email(email), m_role(role), m_fullName(fullName),
      m_phone(phone), m_createdAt(createdAt)
{
}