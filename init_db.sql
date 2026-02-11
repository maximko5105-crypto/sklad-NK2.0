-- Таблица пользователей
CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT UNIQUE NOT NULL,
    password TEXT NOT NULL,
    email TEXT UNIQUE,
    role TEXT NOT NULL CHECK(role IN ('admin', 'manager', 'worker')),
    full_name TEXT NOT NULL,
    phone TEXT,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Таблица товаров
CREATE TABLE IF NOT EXISTS products (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL,
    description TEXT,
    category TEXT NOT NULL,
    sku TEXT UNIQUE NOT NULL,
    barcode TEXT UNIQUE,
    quantity INTEGER NOT NULL DEFAULT 0,
    unit TEXT NOT NULL,
    price REAL NOT NULL,
    min_quantity INTEGER DEFAULT 0,
    location TEXT,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Таблица контейнеров
CREATE TABLE IF NOT EXISTS containers (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    code TEXT UNIQUE NOT NULL,
    name TEXT NOT NULL,
    location TEXT NOT NULL,
    capacity INTEGER NOT NULL,
    current_load INTEGER DEFAULT 0,
    status TEXT NOT NULL CHECK(status IN ('empty', 'partial', 'full', 'reserved')),
    product_id INTEGER,
    FOREIGN KEY (product_id) REFERENCES products(id) ON DELETE SET NULL
);

-- Таблица заявок
CREATE TABLE IF NOT EXISTS requests (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    request_number TEXT UNIQUE NOT NULL,
    user_id INTEGER NOT NULL,
    product_id INTEGER NOT NULL,
    quantity INTEGER NOT NULL,
    type TEXT NOT NULL CHECK(type IN ('incoming', 'outgoing')),
    status TEXT NOT NULL CHECK(status IN ('pending', 'approved', 'rejected', 'completed')),
    priority TEXT CHECK(priority IN ('low', 'medium', 'high')),
    comments TEXT,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    completed_at TIMESTAMP,
    FOREIGN KEY (user_id) REFERENCES users(id),
    FOREIGN KEY (product_id) REFERENCES products(id)
);

-- Таблица истории движений
CREATE TABLE IF NOT EXISTS movement_history (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    product_id INTEGER NOT NULL,
    container_id INTEGER,
    quantity_change INTEGER NOT NULL,
    new_quantity INTEGER NOT NULL,
    request_id INTEGER,
    user_id INTEGER NOT NULL,
    movement_type TEXT NOT NULL CHECK(movement_type IN ('incoming', 'outgoing', 'adjustment', 'transfer')),
    notes TEXT,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (product_id) REFERENCES products(id),
    FOREIGN KEY (container_id) REFERENCES containers(id),
    FOREIGN KEY (request_id) REFERENCES requests(id),
    FOREIGN KEY (user_id) REFERENCES users(id)
);

-- Индексы для оптимизации
CREATE INDEX IF NOT EXISTS idx_products_sku ON products(sku);
CREATE INDEX IF NOT EXISTS idx_products_category ON products(category);
CREATE INDEX IF NOT EXISTS idx_requests_status ON requests(status);
CREATE INDEX IF NOT EXISTS idx_requests_user_id ON requests(user_id);
CREATE INDEX IF NOT EXISTS idx_containers_status ON containers(status);
CREATE INDEX IF NOT EXISTS idx_movement_history_product_id ON movement_history(product_id);
CREATE INDEX IF NOT EXISTS idx_movement_history_created_at ON movement_history(created_at);

-- Триггер для обновления updated_at
CREATE TRIGGER IF NOT EXISTS update_products_timestamp 
AFTER UPDATE ON products
BEGIN
    UPDATE products SET updated_at = CURRENT_TIMESTAMP WHERE id = NEW.id;
END;

CREATE TRIGGER IF NOT EXISTS update_requests_timestamp 
AFTER UPDATE ON requests
BEGIN
    UPDATE requests SET updated_at = CURRENT_TIMESTAMP WHERE id = NEW.id;
END;

-- Вставка тестовых данных (только если таблицы пустые)
INSERT OR IGNORE INTO users (username, password, email, role, full_name, phone) VALUES
('admin', 'admin123', 'admin@sklad.hk', 'admin', 'Администратор Системы', '+7 999 123 45 67'),
('manager', 'manager123', 'manager@sklad.hk', 'manager', 'Менеджер Склада', '+7 999 123 45 68'),
('worker', 'worker123', 'worker@sklad.hk', 'worker', 'Работник Склада', '+7 999 123 45 69');

