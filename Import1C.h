#ifndef IMPORT1C_H
#define IMPORT1C_H

#include <QObject>
#include <QString>

class Import1C : public QObject
{
    Q_OBJECT

public:
    explicit Import1C(QObject* parent = nullptr);
    ~Import1C() = default;

    // Основной метод импорта
    bool importFromCSV(const QString& filename);

    // Получить текст последней ошибки
    QString lastError() const;

signals:
    // Сигнал для отображения прогресса
    void progressChanged(int percent);

private:
    QString m_lastError;
};

#endif // IMPORT1C_H