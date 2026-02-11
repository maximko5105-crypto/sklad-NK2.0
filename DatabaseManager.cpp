#include "DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>      // ← ОБЯЗАТЕЛЬНО
#include <QVariant>
#include <QDebug>

DatabaseManager::DatabaseManager(QObject* parent) : QObject(parent)
{
    m_databasePath = QDir::currentPath() + "/database/warehouse.db";
    
    QDir dir;
    dir.mkpath(QDir::currentPath() + "/database");
    dir.mkpath(QDir::currentPath() + "/qr_codes/products");
    dir.mkpath(QDir::currentPath() + "/qr_codes/containers");
}

DatabaseManager::~DatabaseManager()
{
    if (m_database.isOpen()) {
        m_database.close();
    }
}

DatabaseManager& DatabaseManager::instance()
{
    static DatabaseManager instance;
    return instance;
}

bool DatabaseManager::initializeDatabase()
{
    m_database = QSqlDatabase::addDatabase("QSQLITE");
    m_database.setDatabaseName(m_databasePath);
    
    if (!m_database.open()) {
        qCritical() << "Cannot open database:" << m_database.lastError().text();
        return false;
    }
    
    if (!createTables()) {
        qCritical() << "Failed to create tables";
        return false;
    }
    
    qDebug() << "Database initialized successfully at:" << m_databasePath;
    return true;
}

bool DatabaseManager::createTables()
{
    QSqlQuery query;
    
    // Таблица пользователей
    QString createUsers = QStringLiteral(
        "CREATE TABLE IF NOT EXISTS users ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    username TEXT UNIQUE NOT NULL,"
        "    password TEXT NOT NULL,"
        "    email TEXT UNIQUE,"
        "    role TEXT NOT NULL CHECK(role IN ('admin', 'manager', 'worker')),"
        "    full_name TEXT NOT NULL,"
        "    phone TEXT,"
        "    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP"
        ")"
    );
    
    if (!query.exec(createUsers)) {
        qCritical() << "Failed to create users table:" << query.lastError().text();
        return false;
    }
    
    // Таблица товаров
    QString createProducts = QStringLiteral(
        "CREATE TABLE IF NOT EXISTS products ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    name TEXT NOT NULL,"
        "    description TEXT,"
        "    category TEXT NOT NULL,"
        "    sku TEXT UNIQUE NOT NULL,"
        "    barcode TEXT UNIQUE,"
        "    quantity INTEGER NOT NULL DEFAULT 0,"
        "    unit TEXT NOT NULL,"
        "    price REAL NOT NULL,"
        "    min_quantity INTEGER DEFAULT 0,"
        "    location TEXT,"
        "    qr_code_path TEXT,"
        "    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,"
        "    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP"
        ")"
    );
    
    if (!query.exec(createProducts)) {
        qCritical() << "Failed to create products table:" << query.lastError().text();
        return false;
    }
    
    // Таблица контейнеров
    QString createContainers = QStringLiteral(
        "CREATE TABLE IF NOT EXISTS containers ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    code TEXT UNIQUE NOT NULL,"
        "    name TEXT NOT NULL,"
        "    location TEXT NOT NULL,"
        "    capacity INTEGER NOT NULL,"
        "    current_load INTEGER DEFAULT 0,"
        "    status TEXT NOT NULL CHECK(status IN ('empty', 'partial', 'full', 'reserved')),"
        "    qr_code_path TEXT,"
        "    product_id INTEGER,"
        "    FOREIGN KEY (product_id) REFERENCES products(id) ON DELETE SET NULL"
        ")"
    );
    
    if (!query.exec(createContainers)) {
        qCritical() << "Failed to create containers table:" << query.lastError().text();
        return false;
    }
    
    // Таблица заявок
    QString createRequests = QStringLiteral(
        "CREATE TABLE IF NOT EXISTS requests ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    request_number TEXT UNIQUE NOT NULL,"
        "    user_id INTEGER NOT NULL,"
        "    product_id INTEGER NOT NULL,"
        "    quantity INTEGER NOT NULL,"
        "    type TEXT NOT NULL CHECK(type IN ('incoming', 'outgoing')),"
        "    status TEXT NOT NULL CHECK(status IN ('pending', 'approved', 'rejected', 'completed')),"
        "    priority TEXT CHECK(priority IN ('low', 'medium', 'high')),"
        "    comments TEXT,"
        "    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,"
        "    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,"
        "    completed_at TIMESTAMP,"
        "    FOREIGN KEY (user_id) REFERENCES users(id),"
        "    FOREIGN KEY (product_id) REFERENCES products(id)"
        ")"
    );
    
    if (!query.exec(createRequests)) {
        qCritical() << "Failed to create requests table:" << query.lastError().text();
        return false;
    }
    
    // Создание индексов
    QStringList indexes;
    indexes << "CREATE INDEX IF NOT EXISTS idx_products_sku ON products(sku)"
            << "CREATE INDEX IF NOT EXISTS idx_products_category ON products(category)"
            << "CREATE INDEX IF NOT EXISTS idx_requests_status ON requests(status)"
            << "CREATE INDEX IF NOT EXISTS idx_requests_user_id ON requests(user_id)"
            << "CREATE INDEX IF NOT EXISTS idx_containers_status ON containers(status)";
    
    for (const QString& indexSql : indexes) {
        if (!query.exec(indexSql)) {
            qWarning() << "Failed to create index:" << query.lastError().text();
        }
    }
    
    // Вставка тестовых пользователей
    query.exec("SELECT COUNT(*) FROM users");
    if (query.next() && query.value(0).toInt() == 0) {
        QString insertUsers = 
            "INSERT INTO users (username, password, email, role, full_name, phone) VALUES "
            "('admin', 'admin123', 'admin@sklad.hk', 'admin', 'Администратор Системы', '+7 999 123 45 67'), "
            "('manager', 'manager123', 'manager@sklad.hk', 'manager', 'Менеджер Склада', '+7 999 123 45 68'), "
            "('worker', 'worker123', 'worker@sklad.hk', 'worker', 'Работник Склада', '+7 999 123 45 69')";
        
        if (!query.exec(insertUsers)) {
            qWarning() << "Failed to insert initial users:" << query.lastError().text();
        }
    }
    
    return true;
}

bool DatabaseManager::isDatabaseValid() const
{
    return m_database.isOpen();
}

QSqlQuery DatabaseManager::getUserByUsername(const QString& username)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE username = ?");
    query.addBindValue(username);
    query.exec();
    return query;
}

QSqlQuery DatabaseManager::getAllUsers()
{
    return QSqlQuery("SELECT * FROM users ORDER BY role, username");
}

bool DatabaseManager::addUser(const QString& username, const QString& password, const QString& email,
                             const QString& role, const QString& fullName, const QString& phone)
{
    QSqlQuery query;
    query.prepare(
        "INSERT INTO users (username, password, email, role, full_name, phone) "
        "VALUES (?, ?, ?, ?, ?, ?)"
    );
    query.addBindValue(username);
    query.addBindValue(password);
    query.addBindValue(email);
    query.addBindValue(role);
    query.addBindValue(fullName);
    query.addBindValue(phone);
    
    return query.exec();
}

QSqlQuery DatabaseManager::getAllProducts()
{
    return QSqlQuery("SELECT * FROM products ORDER BY name");
}

QSqlQuery DatabaseManager::getProductById(int id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM products WHERE id = ?");
    query.addBindValue(id);
    query.exec();
    return query;
}

QSqlQuery DatabaseManager::getProductBySku(const QString& sku)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM products WHERE sku = ?");
    query.addBindValue(sku);
    query.exec();
    return query;
}

bool DatabaseManager::addProduct(const QString& name, const QString& description, const QString& category,
                                const QString& sku, const QString& barcode, int quantity, const QString& unit,
                                double price, int minQuantity, const QString& location)
{
    QSqlQuery query;
    query.prepare(
        "INSERT INTO products (name, description, category, sku, barcode, quantity, unit, price, min_quantity, location) "
        "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)"
    );
    query.addBindValue(name);
    query.addBindValue(description);
    query.addBindValue(category);
    query.addBindValue(sku);
    query.addBindValue(barcode);
    query.addBindValue(quantity);
    query.addBindValue(unit);
    query.addBindValue(price);
    query.addBindValue(minQuantity);
    query.addBindValue(location);
    
    return query.exec();
}

bool DatabaseManager::updateProduct(int id, int quantity)
{
    QSqlQuery query;
    query.prepare("UPDATE products SET quantity = ?, updated_at = CURRENT_TIMESTAMP WHERE id = ?");
    query.addBindValue(quantity);
    query.addBindValue(id);
    return query.exec();
}

bool DatabaseManager::updateProductQrPath(int id, const QString& qrPath)
{
    QSqlQuery query;
    query.prepare("UPDATE products SET qr_code_path = ? WHERE id = ?");
    query.addBindValue(qrPath);
    query.addBindValue(id);
    return query.exec();
}

QSqlQuery DatabaseManager::getAllContainers()
{
    return QSqlQuery("SELECT * FROM containers ORDER BY code");
}

QSqlQuery DatabaseManager::getContainerById(int id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM containers WHERE id = ?");
    query.addBindValue(id);
    query.exec();
    return query;
}

bool DatabaseManager::addContainer(const QString& code, const QString& name, const QString& location,
                                  int capacity, int currentLoad, const QString& status, int productId)
{
    QSqlQuery query;
    query.prepare(
        "INSERT INTO containers (code, name, location, capacity, current_load, status, product_id) "
        "VALUES (?, ?, ?, ?, ?, ?, ?)"
    );
    query.addBindValue(code);
    query.addBindValue(name);
    query.addBindValue(location);
    query.addBindValue(capacity);
    query.addBindValue(currentLoad);
    query.addBindValue(status);
    query.addBindValue(productId > 0 ? productId : QVariant());
    
    return query.exec();
}

bool DatabaseManager::updateContainer(int id, int currentLoad, const QString& status, int productId)
{
    QSqlQuery query;
    query.prepare("UPDATE containers SET current_load = ?, status = ?, product_id = ? WHERE id = ?");
    query.addBindValue(currentLoad);
    query.addBindValue(status);
    query.addBindValue(productId > 0 ? productId : QVariant());
    query.addBindValue(id);
    return query.exec();
}

bool DatabaseManager::updateContainerQrPath(int id, const QString& qrPath)
{
    QSqlQuery query;
    query.prepare("UPDATE containers SET qr_code_path = ? WHERE id = ?");
    query.addBindValue(qrPath);
    query.addBindValue(id);
    return query.exec();
}

QSqlQuery DatabaseManager::getAllRequests()
{
    return QSqlQuery("SELECT * FROM requests ORDER BY created_at DESC");
}

QSqlQuery DatabaseManager::getRequestsByStatus(const QString& status)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM requests WHERE status = ? ORDER BY created_at DESC");
    query.addBindValue(status);
    query.exec();
    return query;
}

bool DatabaseManager::addRequest(const QString& requestNumber, int userId, int productId, int quantity,
                                const QString& type, const QString& status, const QString& priority,
                                const QString& comments)
{
    QSqlQuery query;
    query.prepare(
        "INSERT INTO requests (request_number, user_id, product_id, quantity, type, status, priority, comments) "
        "VALUES (?, ?, ?, ?, ?, ?, ?, ?)"
    );
    query.addBindValue(requestNumber);
    query.addBindValue(userId);
    query.addBindValue(productId);
    query.addBindValue(quantity);
    query.addBindValue(type);
    query.addBindValue(status);
    query.addBindValue(priority.isEmpty() ? QVariant() : priority);
    query.addBindValue(comments.isEmpty() ? QVariant() : comments);
    
    return query.exec();
}

bool DatabaseManager::updateRequestStatus(int id, const QString& status)
{
    QSqlQuery query;
    query.prepare("UPDATE requests SET status = ?, updated_at = CURRENT_TIMESTAMP WHERE id = ?");
    query.addBindValue(status);
    query.addBindValue(id);
    return query.exec();
}

bool DatabaseManager::addMovementRecord(int productId, int containerId, int quantityChange,
                                       int newQuantity, int requestId, int userId,
                                       const QString& movementType, const QString& notes)
{
    QSqlQuery query;
    query.prepare(
        "INSERT INTO movement_history (product_id, container_id, quantity_change, new_quantity, "
        "request_id, user_id, movement_type, notes) "
        "VALUES (?, ?, ?, ?, ?, ?, ?, ?)"
    );
    query.addBindValue(productId);
    query.addBindValue(containerId > 0 ? containerId : QVariant());
    query.addBindValue(quantityChange);
    query.addBindValue(newQuantity);
    query.addBindValue(requestId > 0 ? requestId : QVariant());
    query.addBindValue(userId);
    query.addBindValue(movementType);
    query.addBindValue(notes.isEmpty() ? QVariant() : notes);
    
    return query.exec();
}

QSqlQuery DatabaseManager::getMovementHistory(int productId, int limit)
{
    QSqlQuery query;
    if (productId > 0) {
        query.prepare(
            "SELECT mh.*, p.name as product_name, u.username as user_name "
            "FROM movement_history mh "
            "LEFT JOIN products p ON mh.product_id = p.id "
            "LEFT JOIN users u ON mh.user_id = u.id "
            "WHERE mh.product_id = ? "
            "ORDER BY mh.created_at DESC "
            "LIMIT ?"
        );
        query.addBindValue(productId);
    } else {
        query.prepare(
            "SELECT mh.*, p.name as product_name, u.username as user_name "
            "FROM movement_history mh "
            "LEFT JOIN products p ON mh.product_id = p.id "
            "LEFT JOIN users u ON mh.user_id = u.id "
            "ORDER BY mh.created_at DESC "
            "LIMIT ?"
        );
    }
    query.addBindValue(limit);
    query.exec();
    return query;
}