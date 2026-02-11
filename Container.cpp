#include "Container.h"

Container::Container()
    : m_id(-1), m_capacity(0), m_currentLoad(0), m_productId(-1)
{
}

Container::Container(int id, const QString& code, const QString& name,
                     const QString& location, int capacity, int currentLoad,
                     const QString& status, int productId, const QString& qrCodePath)
    : m_id(id), m_code(code), m_name(name), m_location(location),
      m_capacity(capacity), m_currentLoad(currentLoad), m_status(status),
      m_productId(productId), m_qrCodePath(qrCodePath)
{
}

QString Container::toString() const
{
    return QString("Container[id=%1, code='%2', load=%3/%4]")
           .arg(m_id).arg(m_code).arg(m_currentLoad).arg(m_capacity);
}