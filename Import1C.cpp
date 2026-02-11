#include "Import1C.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "../database/DatabaseManager.h"

Import1C::Import1C(QObject* parent) 
    : QObject(parent)
{
    // Конструктор теперь имеет явную реализацию
}

QString Import1C::lastError() const {
    return m_lastError;
}

bool Import1C::importFromCSV(const QString& filename) {
    QFile file(filename);
    
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        m_lastError = QString("Не удалось открыть файл: %1").arg(file.errorString());
        qCritical() << m_lastError;
        return false;
    }

    qDebug() << "Начинается импорт из файла:" << filename;
    emit progressChanged(0);

    QTextStream in(&file);
    // Пропускаем заголовок CSV (первую строку)
    if (!in.atEnd()) {
        in.readLine();
    }

    int lineNumber = 0;
    int importedCount = 0;

    while (!in.atEnd()) {
        QString line = in.readLine();
        lineNumber++;

        // Парсинг CSV строки (упрощенный)
        QStringList fields = line.split(';');
        if (fields.size() < 3) {
            qWarning() << "Строка" << lineNumber << "пропущена: недостаточно полей";
            continue;
        }

        // Создаем объект товара из данных CSV
        // Предполагаем формат: артикул;название;цена;количество
        Product product;
        product.article = fields.value(0).trimmed();
        product.name = fields.value(1).trimmed();
        product.price = fields.value(2).toDouble();
        product.quantity = fields.value(3).toInt();

        if (product.article.isEmpty() || product.name.isEmpty()) {
            qWarning() << "Строка" << lineNumber << "пропущена: некорректные данные";
            continue;
        }

        // Добавляем товар в базу данных
        if (DatabaseManager::instance().addProduct(product)) {
            importedCount++;
        }

        // Отправляем сигнал о прогрессе (каждые 10 строк)
        if (lineNumber % 10 == 0) {
            emit progressChanged((lineNumber * 100) / 1000); // Пример: 1000 строк всего
        }
    }

    file.close();
    
    m_lastError.clear();
    qDebug() << "Импорт завершен. Успешно импортировано:" << importedCount << "товаров";
    emit progressChanged(100);
    
    return importedCount > 0;
}