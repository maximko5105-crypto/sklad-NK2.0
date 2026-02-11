#ifndef REQUEST_H
#define REQUEST_H

#include <QObject>
#include <QString>
#include <QDateTime>
#include <QVariantMap>

class Request : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString requestNumber READ requestNumber WRITE setRequestNumber NOTIFY requestNumberChanged)
    Q_PROPERTY(int userId READ userId WRITE setUserId NOTIFY userIdChanged)
    Q_PROPERTY(int productId READ productId WRITE setProductId NOTIFY productIdChanged)
    Q_PROPERTY(int quantity READ quantity WRITE setQuantity NOTIFY quantityChanged)
    Q_PROPERTY(QString type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QString status READ status WRITE setStatus NOTIFY statusChanged)
    Q_PROPERTY(QString priority READ priority WRITE setPriority NOTIFY priorityChanged)
    Q_PROPERTY(QString comments READ comments WRITE setComments NOTIFY commentsChanged)
    Q_PROPERTY(QDateTime createdAt READ createdAt WRITE setCreatedAt NOTIFY createdAtChanged)
    Q_PROPERTY(QDateTime updatedAt READ updatedAt WRITE setUpdatedAt NOTIFY updatedAtChanged)
    Q_PROPERTY(QDateTime completedAt READ completedAt WRITE setCompletedAt NOTIFY completedAtChanged)

public:
    explicit Request(QObject *parent = nullptr);
    Request(int id, const QString &requestNumber, int userId, int productId,
           int quantity, const QString &type, const QString &status,
           const QString &priority, const QString &comments,
           const QDateTime &createdAt, const QDateTime &updatedAt,
           const QDateTime &completedAt, QObject *parent = nullptr);
    
    // Getters
    int id() const;
    QString requestNumber() const;
    int userId() const;
    int productId() const;
    int quantity() const;
    QString type() const;
    QString status() const;
    QString priority() const;
    QString comments() const;
    QDateTime createdAt() const;
    QDateTime updatedAt() const;
    QDateTime completedAt() const;
    
    // Setters
    void setId(int id);
    void setRequestNumber(const QString &requestNumber);
    void setUserId(int userId);
    void setProductId(int productId);
    void setQuantity(int quantity);
    void setType(const QString &type);
    void setStatus(const QString &status);
    void setPriority(const QString &priority);
    void setComments(const QString &comments);
    void setCreatedAt(const QDateTime &createdAt);
    void setUpdatedAt(const QDateTime &updatedAt);
    void setCompletedAt(const QDateTime &completedAt);
    
    // Вспомогательные методы
    bool isIncoming() const;
    bool isOutgoing() const;
    bool isPending() const;
    bool isApproved() const;
    bool isCompleted() const;
    bool isRejected() const;
    QString toString() const;
    QVariantMap toVariantMap() const;
    static Request* fromVariantMap(const QVariantMap &data);
    
    // Статические методы преобразования
    static QString typeToString(const QString &type);
    static QString statusToString(const QString &status);
    static QString priorityToString(const QString &priority);

signals:
    void idChanged();
    void requestNumberChanged();
    void userIdChanged();
    void productIdChanged();
    void quantityChanged();
    void typeChanged();
    void statusChanged();
    void priorityChanged();
    void commentsChanged();
    void createdAtChanged();
    void updatedAtChanged();
    void completedAtChanged();

private:
    int m_id = 0;
    QString m_requestNumber;
    int m_userId = 0;
    int m_productId = 0;
    int m_quantity = 0;
    QString m_type;
    QString m_status;
    QString m_priority;
    QString m_comments;
    QDateTime m_createdAt;
    QDateTime m_updatedAt;
    QDateTime m_completedAt;
};

#endif // REQUEST_H