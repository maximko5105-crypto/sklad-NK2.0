#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>

class DatabaseManager : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(DatabaseManager)

public:
    static DatabaseManager& instance();
    
    bool initializeDatabase();
    bool isDatabaseValid() const;
    
    // User operations
    QSqlQuery getUserByUsername(const QString& username);
    QSqlQuery getAllUsers();
    bool addUser(const QString& username, const QString& password, const QString& email,
                const QString& role, const QString& fullName, const QString& phone);
    
    // Product operations
    QSqlQuery getAllProducts();
    QSqlQuery getProductById(int id);
    QSqlQuery getProductBySku(const QString& sku);
    bool addProduct(const QString& name, const QString& description, const QString& category,
                   const QString& sku, const QString& barcode, int quantity, const QString& unit,
                   double price, int minQuantity, const QString& location);
    bool updateProduct(int id, int quantity);
    bool updateProductQrPath(int id, const QString& qrPath);
    
    // Container operations
    QSqlQuery getAllContainers();
    QSqlQuery getContainerById(int id);
    bool addContainer(const QString& code, const QString& name, const QString& location,
                     int capacity, int currentLoad, const QString& status, int productId = -1);
    bool updateContainer(int id, int currentLoad, const QString& status, int productId = -1);
    bool updateContainerQrPath(int id, const QString& qrPath);
    
    // Request operations
    QSqlQuery getAllRequests();
    QSqlQuery getRequestsByStatus(const QString& status);
    bool addRequest(const QString& requestNumber, int userId, int productId, int quantity,
                   const QString& type, const QString& status, const QString& priority,
                   const QString& comments);
    bool updateRequestStatus(int id, const QString& status);
    
    // Movement history
    bool addMovementRecord(int productId, int containerId, int quantityChange,
                          int newQuantity, int requestId, int userId,
                          const QString& movementType, const QString& notes = "");
    
    QSqlQuery getMovementHistory(int productId = -1, int limit = 100);

private:
    DatabaseManager(QObject* parent = nullptr);
    ~DatabaseManager();
    
    bool createTables();
    
    QSqlDatabase m_database;
    QString m_databasePath;
};

#endif // DATABASEMANAGER_H