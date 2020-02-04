/********************************************************************************
** Form generated from reading UI file 'Setting.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTING_H
#define UI_SETTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Setting
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *New;
    QPushButton *Edit;
    QPushButton *Save;
    QPushButton *Exist;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *createRect;
    QPushButton *getRect;

    void setupUi(QWidget *Setting)
    {
        if (Setting->objectName().isEmpty())
            Setting->setObjectName(QString::fromUtf8("Setting"));
        Setting->resize(1024, 768);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Setting->sizePolicy().hasHeightForWidth());
        Setting->setSizePolicy(sizePolicy);
        verticalLayoutWidget = new QWidget(Setting);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 610, 111, 135));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        New = new QPushButton(verticalLayoutWidget);
        New->setObjectName(QString::fromUtf8("New"));

        verticalLayout->addWidget(New);

        Edit = new QPushButton(verticalLayoutWidget);
        Edit->setObjectName(QString::fromUtf8("Edit"));

        verticalLayout->addWidget(Edit);

        Save = new QPushButton(verticalLayoutWidget);
        Save->setObjectName(QString::fromUtf8("Save"));

        verticalLayout->addWidget(Save);

        Exist = new QPushButton(verticalLayoutWidget);
        Exist->setObjectName(QString::fromUtf8("Exist"));

        verticalLayout->addWidget(Exist);

        horizontalLayoutWidget = new QWidget(Setting);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(220, 660, 321, 61));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        createRect = new QPushButton(horizontalLayoutWidget);
        createRect->setObjectName(QString::fromUtf8("createRect"));

        horizontalLayout->addWidget(createRect);

        getRect = new QPushButton(horizontalLayoutWidget);
        getRect->setObjectName(QString::fromUtf8("getRect"));

        horizontalLayout->addWidget(getRect);


        retranslateUi(Setting);

        QMetaObject::connectSlotsByName(Setting);
    } // setupUi

    void retranslateUi(QWidget *Setting)
    {
        Setting->setWindowTitle(QApplication::translate("Setting", "Setting", nullptr));
        New->setText(QApplication::translate("Setting", "\346\226\260\345\273\272\351\205\215\347\275\256", nullptr));
        Edit->setText(QApplication::translate("Setting", "\347\274\226\350\276\221\345\267\262\346\234\211\351\205\215\347\275\256", nullptr));
        Save->setText(QApplication::translate("Setting", "\344\277\235\345\255\230\345\275\223\345\211\215\351\205\215\347\275\256", nullptr));
        Exist->setText(QApplication::translate("Setting", "\351\200\200\345\207\272", nullptr));
        createRect->setText(QApplication::translate("Setting", "\345\210\233\345\273\272\347\237\251\345\275\242", nullptr));
        getRect->setText(QApplication::translate("Setting", "\350\216\267\345\217\226\347\237\251\345\275\242\345\235\220\346\240\207", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Setting: public Ui_Setting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTING_H
