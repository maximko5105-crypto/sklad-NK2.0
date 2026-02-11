#include <QApplication>
#include <QStyleFactory>
#include <QFile>
#include <QDir>
#include "gui/LoginDialog.h"
#include "gui/MainWindow.h"
#include "database/DatabaseManager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // Настройка стиля приложения
    app.setStyle(QStyleFactory::create("Fusion"));
    
    // Загрузка стилей
    QFile styleFile(":/styles/style.qss");
    if (styleFile.open(QIODevice::ReadOnly)) {
        QString styleSheet = QString::fromUtf8(styleFile.readAll());
        app.setStyleSheet(styleSheet);
        styleFile.close();
    }
    
    // Установка информации о приложении
    app.setApplicationName("Складская система HK");
    app.setOrganizationName("WarehouseHK");
    app.setApplicationVersion("2.0.0");
    
    // Создаем необходимые директории
    QDir dir;
    dir.mkpath(QDir::currentPath() + "/database");
    dir.mkpath(QDir::currentPath() + "/qr_codes/products");
    dir.mkpath(QDir::currentPath() + "/qr_codes/containers");
    
    // Инициализация базы данных
    if (!DatabaseManager::instance().initializeDatabase()) {
        qCritical("Failed to initialize database!");
        return 1;
    }
    
    // Показываем окно авторизации
    LoginDialog loginDialog;
    
    if (loginDialog.exec() == QDialog::Accepted) {
        // Получаем текущего пользователя
        User currentUser = loginDialog.getCurrentUser();
        
        // Создаем главное окно
        MainWindow mainWindow(currentUser);
        mainWindow.showMaximized();
        
        return app.exec();
    }
    
    return 0;
}