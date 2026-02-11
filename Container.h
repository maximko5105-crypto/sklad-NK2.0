#ifndef CONTAINER_H
#define CONTAINER_H

#include <QString>

class Container
{
public:
    Container();
    Container(int id, const QString& code, const QString& name,
              const QString& location, int capacity, int currentLoad,
              const QString& status, int productId = -1,
              const QString& qrCodePath = "");

    // Getters
    int id() const { return m_id; }
    QString code() const { return m_code; }
    QString name() const { return m_name; }
    QString location() const { return m_location; }
    int capacity() const { return m_capacity; }
    int currentLoad() const { return m_currentLoad; }
    QString status() const { return m_status; }
    int productId() const { return m_productId; }
    QString qrCodePath() const { return m_qrCodePath; }

    // Setters
    void setId(int id) { m_id = id; }
    void setCode(const QString& code) { m_code = code; }
    void setName(const QString& name) { m_name = name; }
    void setLocation(const QString& location) { m_location = location; }
    void setCapacity(int capacity) { m_capacity = capacity; }
    void setCurrentLoad(int currentLoad) { m_currentLoad = currentLoad; }
    void setStatus(const QString& status) { m_status = status; }
    void setProductId(int productId) { m_productId = productId; }
    void setQrCodePath(const QString& path) { m_qrCodePath = path; }

    // Utility
    double loadPercentage() const { return capacity() > 0 ? (currentLoad() * 100.0) / capacity() : 0.0; }
    bool isEmpty() const { return m_status == "empty"; }
    bool isFull() const { return m_status == "full"; }
    QString toString() const;

private:
    int m_id;
    QString m_code;
    QString m_name;
    QString m_location;
    int m_capacity;
    int m_currentLoad;
    QString m_status;
    int m_productId;
    QString m_qrCodePath;
};

#endif // CONTAINER_H