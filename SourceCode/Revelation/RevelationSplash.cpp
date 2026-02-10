#include "RevelationSplash.h"
#include "RevelationInterface.h"
#include <QLabel>

RevelationSplash::RevelationSplash(IRevelationInterface* intf, QWidget* parent)
    : m_interface(intf), QDialog(parent)
{
    ui.setupUi(this);

    Initialize();
}

RevelationSplash::~RevelationSplash()
{
}

void RevelationSplash::Initialize()
{
    InitWidget();
}

void RevelationSplash::InitWidget()
{
    this->setWindowFlag(Qt::SplashScreen);
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setWindowFlag(Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    auto iconPath = m_interface->GetResourcePath() / "image" / "icon.ico";
    if (std::filesystem::exists(iconPath))
    {
        auto    u8     = iconPath.u8string();
        QString u8Path = QString::fromUtf8(reinterpret_cast<const char*>(u8.c_str()), u8.size());
        QPixmap pixmap(u8Path);
        this->setWindowIcon(pixmap);
    }

    auto imagePath = m_interface->GetResourcePath() / "image" / "splash.png";
    if (std::filesystem::exists(imagePath))
    {
        QLabel* label  = new QLabel(ui.eSplashWidget);
        auto    u8     = imagePath.u8string();
        QString u8Path = QString::fromUtf8(reinterpret_cast<const char*>(u8.c_str()), u8.size());
        QPixmap pixmap(u8Path);
        label->setStyleSheet("background-color: transparent;");
        label->setPixmap(pixmap);
        label->resize(pixmap.size());
    }
    else
    {
        this->close();
    }
}
