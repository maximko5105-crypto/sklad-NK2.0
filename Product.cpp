#include "Product.h"

Product::Product()
    : m_id(-1), m_quantity(0), m_price(0.0), m_minQuantity(0)
{
}

Product::Product(int id, const QString& name, const QString& description,
                 const QString& category, const QString& sku, const QString& barcode,
                 int quantity, const QString& unit, double price, int minQuantity,
                 const QString& location, const QString& qrCodePath,
                 const QDateTime& createdAt, const QDateTime& updatedAt)
    : m_id(id), m_name(name), m_description(description), m_category(category),
      m_sku(sku), m_barcode(barcode), m_quantity(quantity), m_unit(unit),
      m_price(price), m_minQuantity(minQuantity), m_location(location),
      m_qrCodePath(qrCodePath), m_createdAt(createdAt), m_updatedAt(updatedAt)
{
}

QString Product::toString() const
{
    return QString("Product[id=%1, name='%2', sku='%3', qty=%4]")
           .arg(m_id).arg(m_name).arg(m_sku).arg(m_quantity);
}