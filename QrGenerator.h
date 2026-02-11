#ifndef QRGENERATOR_H
#define QRGENERATOR_H

#include <QPixmap>
#include <QString>

class QrGenerator
{
public:
    QrGenerator();
    
    QPixmap generateProductQR(int productId, const QString& name, const QString& sku, 
                             int quantity, const QString& location, int size = 400);
    
    QPixmap generateContainerQR(int containerId, const QString& code, 
                               const QString& name, const QString& location, int size = 400);
    
    bool saveQRToFile(const QPixmap& qrCode, const QString& filePath);
    
    QString getProductQRPath(int productId, const QString& productName);
    QString getContainerQRPath(int containerId, const QString& containerCode);
    
private:
    QPixmap generateQR(const QString& data, int size);
    QString sanitizeFilename(const QString& filename);
};

#endif // QRGENERATOR_H