#include "QrDisplayDialog.h"
#include "ui_QrDisplayDialog.h"
#include "../utils/QrGenerator.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QClipboard>
#include <QApplication>
#include <QStandardPaths>
#include <QSettings>
#include <QDateTime>

QrDisplayDialog::QrDisplayDialog(const QPixmap& qrCode, const QString& title, 
                               const QString& data, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::QrDisplayDialog)
    , m_qrCode(qrCode)
    , m_data(data)
{
    ui->setupUi(this);
    
    setWindowTitle(title);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    
    setupUi();
    setupConnections();
    loadSettings();
}

QrDisplayDialog::~QrDisplayDialog()
{
    saveSettings();
    delete ui;
}

void QrDisplayDialog::setupUi()
{
    // Устанавливаем изображение
    ui->qrLabel->setPixmap(m_qrCode);
    ui->qrLabel->setScaledContents(false);
    ui->qrLabel->setAlignment(Qt::AlignCenter);
    
    // Настройка информации
    if (!m_data.isEmpty()) {
        ui->dataTextEdit->setPlainText(m_data);
        ui->dataTextEdit->setVisible(true);
        ui->dataLabel->setVisible(true);
    } else {
        ui->dataTextEdit->setVisible(false);
        ui->dataLabel->setVisible(false);
    }
    
    // Настройка имени файла
    m_defaultFileName = "qr_code_" + 
                       QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");
    ui->fileNameEdit->setText(m_defaultFileName + ".png");
    
    // Настройка форматов
    ui->formatCombo->addItem("PNG (*.png)", "PNG");
    ui->formatCombo->addItem("JPEG (*.jpg)", "JPEG");
    ui->formatCombo->addItem("BMP (*.bmp)", "BMP");
    
    // Настройка размеров
    ui->sizeSlider->setRange(100, 800);
    ui->sizeSlider->setValue(400);
    ui->sizeLabel->setText("Размер: 400x400");
}

void QrDisplayDialog::setupConnections()
{
    connect(ui->saveButton, &QPushButton::clicked, this, &QrDisplayDialog::onSaveButtonClicked);
    connect(ui->printButton, &QPushButton::clicked, this, &QrDisplayDialog::onPrintButtonClicked);
    connect(ui->copyButton, &QPushButton::clicked, this, &QrDisplayDialog::onCopyButtonClicked);
    connect(ui->emailButton, &QPushButton::clicked, this, &QrDisplayDialog::onEmailButtonClicked);
    connect(ui->generateButton, &QPushButton::clicked, this, &QrDisplayDialog::onGenerateAnotherClicked);
    connect(ui->closeButton, &QPushButton::clicked, this, &QDialog::accept);
    
    connect(ui->fileNameEdit, &QLineEdit::textChanged, this, &QrDisplayDialog::updateSavePath);
    connect(ui->formatCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &QrDisplayDialog::onFormatChanged);
    connect(ui->sizeSlider, &QSlider::valueChanged, this, &QrDisplayDialog::onSizeChanged);
}

void QrDisplayDialog::onSaveButtonClicked()
{
    QString selectedFilter;
    QString fileName = ui->fileNameEdit->text();
    
    if (fileName.isEmpty()) {
        fileName = m_defaultFileName + ".png";
        ui->fileNameEdit->setText(fileName);
    }
    
    QString filePath = QFileDialog::getSaveFileName(
        this,
        "Сохранить QR-код",
        QDir::homePath() + "/" + fileName,
        "Изображения (*.png *.jpg *.jpeg *.bmp);;Все файлы (*.*)",
        &selectedFilter
    );
    
    if (!filePath.isEmpty()) {
        if (saveImage(filePath)) {
            QMessageBox::information(this, "Успех", 
                "QR-код успешно сохранен в файл:\n" + filePath);
        } else {
            QMessageBox::warning(this, "Ошибка", 
                "Не удалось сохранить файл. Проверьте права доступа.");
        }
    }
}

void QrDisplayDialog::onPrintButtonClicked()
{
    if (!printImage()) {
        QMessageBox::warning(this, "Ошибка", 
            "Не удалось выполнить печать. Проверьте подключение принтера.");
    }
}

void QrDisplayDialog::onCopyButtonClicked()
{
    copyToClipboard();
    QMessageBox::information(this, "Успех", 
        "QR-код скопирован в буфер обмена. Теперь его можно вставить в графический редактор.");
}

void QrDisplayDialog::onEmailButtonClicked()
{
    QMessageBox::information(this, "Информация", 
        "Функция отправки по email будет реализована в следующей версии.\n"
        "Сохраните QR-код и прикрепите его к письму вручную.");
}

void QrDisplayDialog::onGenerateAnotherClicked()
{
    // Перегенерировать QR-код с новыми параметрами
    int newSize = ui->sizeSlider->value();
    QPixmap scaledCode = m_qrCode.scaled(newSize, newSize, 
                                        Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->qrLabel->setPixmap(scaledCode);
}

bool QrDisplayDialog::saveImage(const QString& filePath)
{
    QString format = "PNG";
    
    if (filePath.endsWith(".jpg", Qt::CaseInsensitive) || 
        filePath.endsWith(".jpeg", Qt::CaseInsensitive)) {
        format = "JPG";
    } else if (filePath.endsWith(".bmp", Qt::CaseInsensitive)) {
        format = "BMP";
    }
    
    // Масштабируем изображение если нужно
    QPixmap savePixmap = ui->qrLabel->pixmap(Qt::ReturnByValue);
    
    return savePixmap.save(filePath, format.toUtf8().constData(), 100);
}

bool QrDisplayDialog::printImage()
{
    QPrinter printer(QPrinter::HighResolution);
    printer.setPageSize(QPrinter::A4);
    printer.setPageOrientation(QPageLayout::Portrait);
    printer.setColorMode(QPrinter::Color);
    
    QPrintDialog printDialog(&printer, this);
    if (printDialog.exec() == QDialog::Accepted) {
        QPainter painter(&printer);
        
        // Получаем текущее изображение
        QPixmap pixmap = ui->qrLabel->pixmap(Qt::ReturnByValue);
        
        // Рассчитываем размеры для печати
        QRect pageRect = printer.pageRect(QPrinter::DevicePixel);
        QRect printRect = pageRect.adjusted(50, 50, -50, -100);
        
        // Масштабируем изображение
        QPixmap scaledPixmap = pixmap.scaled(printRect.size(), 
                                            Qt::KeepAspectRatio, 
                                            Qt::SmoothTransformation);
        
        // Центрируем
        int x = printRect.left() + (printRect.width() - scaledPixmap.width()) / 2;
        int y = printRect.top() + (printRect.height() - scaledPixmap.height()) / 2;
        
        // Рисуем QR-код
        painter.drawPixmap(x, y, scaledPixmap);
        
        // Добавляем заголовок
        painter.setFont(QFont("Arial", 14, QFont::Bold));
        painter.drawText(pageRect.left(), 30, pageRect.width(), 30, 
                        Qt::AlignCenter, windowTitle());
        
        // Добавляем информацию о данных
        if (!m_data.isEmpty()) {
            painter.setFont(QFont("Arial", 10));
            painter.drawText(pageRect.left(), y + scaledPixmap.height() + 20, 
                           pageRect.width(), 50, Qt::AlignCenter, 
                           "Данные: " + m_data.left(100) + 
                           (m_data.length() > 100 ? "..." : ""));
        }
        
        // Добавляем дату и время
        painter.setFont(QFont("Arial", 8));
        painter.drawText(pageRect.left(), pageRect.bottom() - 30, 
                        pageRect.width(), 30, Qt::AlignCenter,
                        "Сгенерировано: " + 
                        QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm"));
        
        painter.end();
        return true;
    }
    
    return false;
}

void QrDisplayDialog::copyToClipboard()
{
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setPixmap(ui->qrLabel->pixmap(Qt::ReturnByValue));
}

void QrDisplayDialog::updateSavePath()
{
    QString fileName = ui->fileNameEdit->text();
    QString format = ui->formatCombo->currentData().toString().toLower();
    
    if (!fileName.isEmpty() && !fileName.contains('.')) {
        fileName += "." + format;
        ui->fileNameEdit->setText(fileName);
    }
}

void QrDisplayDialog::onFormatChanged(int index)
{
    Q_UNUSED(index);
    QString fileName = ui->fileNameEdit->text();
    QString newExt = "." + ui->formatCombo->currentData().toString().toLower();
    
    if (!fileName.isEmpty()) {
        // Заменяем расширение
        int dotIndex = fileName.lastIndexOf('.');
        if (dotIndex > 0) {
            fileName = fileName.left(dotIndex) + newExt;
        } else {
            fileName += newExt;
        }
        ui->fileNameEdit->setText(fileName);
    }
}

void QrDisplayDialog::onSizeChanged(int value)
{
    ui->sizeLabel->setText(QString("Размер: %1x%1").arg(value));
    
    // Автоматически обновляем изображение при изменении размера
    if (ui->autoUpdateCheck->isChecked()) {
        onGenerateAnotherClicked();
    }
}

void QrDisplayDialog::loadSettings()
{
    QSettings settings("WarehouseHK", "QRGenerator");
    
    ui->formatCombo->setCurrentIndex(settings.value("format", 0).toInt());
    ui->sizeSlider->setValue(settings.value("size", 400).toInt());
    ui->autoUpdateCheck->setChecked(settings.value("autoUpdate", true).toBool());
    
    restoreGeometry(settings.value("geometry").toByteArray());
}

void QrDisplayDialog::saveSettings()
{
    QSettings settings("WarehouseHK", "QRGenerator");
    
    settings.setValue("format", ui->formatCombo->currentIndex());
    settings.setValue("size", ui->sizeSlider->value());
    settings.setValue("autoUpdate", ui->autoUpdateCheck->isChecked());
    settings.setValue("geometry", saveGeometry());
}

void QrDisplayDialog::closeEvent(QCloseEvent *event)
{
    saveSettings();
    QDialog::closeEvent(event);
}

void QrDisplayDialog::setSaveEnabled(bool enabled)
{
    ui->saveButton->setEnabled(enabled);
}

void QrDisplayDialog::setPrintEnabled(bool enabled)
{
    ui->printButton->setEnabled(enabled);
}

void QrDisplayDialog::setCopyEnabled(bool enabled)
{
    ui->copyButton->setEnabled(enabled);
}