#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>
#include <QDateTime>

class Product
{
public:
    Product();
    Product(int id, const QString& name, const QString& description,
            const QString& category, const QString& sku, const QString& barcode,
            int quantity, const QString& unit, double price, int minQuantity,
            const QString& location, const QString& qrCodePath = "",
            const QDateTime& createdAt = QDateTime(),
            const QDateTime& updatedAt = QDateTime());

    // Getters
    int id() const { return m_id; }
    QString name() const { return m_name; }
    QString description() const { return m_description; }
    QString category() const { return m_category; }
    QString sku() const { return m_sku; }
    QString barcode() const { return m_barcode; }
    int quantity() const { return m_quantity; }
    QString unit() const { return m_unit; }
    double price() const { return m_price; }
    int minQuantity() const { return m_minQuantity; }
    QString location() const { return m_location; }
    QString qrCodePath() const { return m_qrCodePath; }
    QDateTime createdAt() const { return m_createdAt; }
    QDateTime updatedAt() const { return m_updatedAt; }

    // Setters
    void setId(int id) { m_id = id; }
    void setName(const QString& name) { m_name = name; }
    void setDescription(const QString& description) { m_description = description; }
    void setCategory(const QString& category) { m_category = category; }
    void setSku(const QString& sku) { m_sku = sku; }
    void setBarcode(const QString& barcode) { m_barcode = barcode; }
    void setQuantity(int quantity) { m_quantity = quantity; }
    void setUnit(const QString& unit) { m_unit = unit; }
    void setPrice(double price) { m_price = price; }
    void setMinQuantity(int minQuantity) { m_minQuantity = minQuantity; }
    void setLocation(const QString& location) { m_location = location; }
    void setQrCodePath(const QString& path) { m_qrCodePath = path; }

    // Utility
    bool isLowStock() const { return m_minQuantity > 0 && m_quantity <= m_minQuantity; }
    double totalValue() const { return m_quantity * m_price; }
    QString toString() const;

private:
    int m_id;
    QString m_name;
    QString m_description;
    QString m_category;
    QString m_sku;
    QString m_barcode;
    int m_quantity;
    QString m_unit;
    double m_price;
    int m_minQuantity;
    QString m_location;
    QString m_qrCodePath;
    QDateTime m_createdAt;
    QDateTime m_updatedAt;
};

#endif // PRODUCT_H