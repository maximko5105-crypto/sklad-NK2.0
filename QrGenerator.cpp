#include "QrGenerator.h"
#include <QPainter>
#include <QFile>
#include <QDir>
#include <QDateTime>
#include <QRegularExpression>
#include <QDebug>

QrGenerator::QrGenerator()
{
}

QPixmap QrGenerator::generateQR(const QString& data, int size)
{
    QPixmap pixmap(size, size);
    pixmap.fill(Qt::white);
    
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    
    // Рисуем рамку
    painter.setPen(QPen(QColor(25, 118, 210), 3));
    painter.setBrush(Qt::white);
    painter.drawRoundedRect(2, 2, size - 4, size - 4, 10, 10);
    
    // Рисуем заголовок QR-кода
    painter.setPen(QColor(25, 118, 210));
    painter.setFont(QFont("Arial", 14, QFont::Bold));
    painter.drawText(0, 30, size, 30, Qt::AlignCenter, "СКЛАД HK");
    
    // Рисуем данные
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 10));
    
    // Разделяем данные на строки
    QStringList lines = data.split('\n', Qt::SkipEmptyParts);
    
    // Рисуем строки
    int lineHeight = (size - 80) / (lines.size() + 1);
    int startY = 60;
    
    for (int i = 0; i < lines.size(); i++) {
        painter.drawText(10, startY + (i * lineHeight), size - 20, lineHeight, 
                        Qt::AlignCenter, lines[i]);
    }
    
    // Добавляем водяной знак
    painter.setFont(QFont("Arial", 8));
    painter.setPen(QColor(100, 100, 100, 128));
    painter.drawText(0, size - 20, size, 20, Qt::AlignCenter, 
                    QDateTime::currentDateTime().toString("dd.MM.yyyy"));
    
    return pixmap;
}

QPixmap QrGenerator::generateProductQR(int productId, const QString& name, const QString& sku,
                                      int quantity, const QString& location, int size)
{
    QString data = QString("ТОВАР\n"
                          "ID: %1\n"
                          "Название: %2\n"
                          "SKU: %3\n"
                          "Кол-во: %4\n"
                          "Место: %5\n"
                          "Дата: %6")
                   .arg(productId)
                   .arg(name.left(30))  // Ограничиваем длину названия
                   .arg(sku)
                   .arg(quantity)
                   .arg(location.left(20))  // Ограничиваем длину местоположения
                   .arg(QDateTime::currentDateTime().toString("dd.MM.yyyy"));
    
    return generateQR(data, size);
}

QPixmap QrGenerator::generateContainerQR(int containerId, const QString& code,
                                        const QString& name, const QString& location, int size)
{
    QString data = QString("КОНТЕЙНЕР\n"
                          "ID: %1\n"
                          "Код: %2\n"
                          "Название: %3\n"
                          "Место: %4\n"
                          "Дата: %5")
                   .arg(containerId)
                   .arg(code)
                   .arg(name.left(30))
                   .arg(location.left(20))
                   .arg(QDateTime::currentDateTime().toString("dd.MM.yyyy"));
    
    return generateQR(data, size);
}

bool QrGenerator::saveQRToFile(const QPixmap& qrCode, const QString& filePath)
{
    QDir dir = QFileInfo(filePath).absoluteDir();
    if (!dir.exists()) {
        if (!dir.mkpath(".")) {
            qWarning() << "Failed to create directory:" << dir.path();
            return false;
        }
    }
    
    // Сохраняем с высоким качеством
    return qrCode.save(filePath, "PNG", 100);
}

QString QrGenerator::getProductQRPath(int productId, const QString& productName)
{
    QString safeName = sanitizeFilename(productName);
    return QDir::currentPath() + 
           "/qr_codes/products/" + 
           QString("product_%1_%2.png").arg(productId).arg(safeName);
}

QString QrGenerator::getContainerQRPath(int containerId, const QString& containerCode)
{
    QString safeCode = sanitizeFilename(containerCode);
    return QDir::currentPath() + 
           "/qr_codes/containers/" + 
           QString("container_%1_%2.png").arg(containerId).arg(safeCode);
}

QString QrGenerator::sanitizeFilename(const QString& filename)
{
    QString result = filename;
    // Заменяем недопустимые символы на подчеркивания
    QRegularExpression invalidChars("[\\\\/:*?\"<>|]");
    result.replace(invalidChars, "_");
    // Ограничиваем длину
    if (result.length() > 50) {
        result = result.left(50);
    }
    return result;
}