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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Setting
{
public:
    QPushButton *saveSetting;
    QPushButton *Exist;
    QTabWidget *tabWidget;
    QWidget *tab;
    QPushButton *selectExample;
    QPushButton *createROI;
    QPushButton *getsb;
    QWidget *tab_3;
    QPushButton *newMission;
    QRadioButton *radioButton;
    QPushButton *confirmMission;
    QWidget *tab_2;
    QPushButton *doCalibration;

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
        saveSetting = new QPushButton(Setting);
        saveSetting->setObjectName(QString::fromUtf8("saveSetting"));
        saveSetting->setGeometry(QRect(660, 630, 271, 28));
        Exist = new QPushButton(Setting);
        Exist->setObjectName(QString::fromUtf8("Exist"));
        Exist->setGeometry(QRect(670, 680, 221, 28));
        tabWidget = new QTabWidget(Setting);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(80, 610, 541, 161));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        selectExample = new QPushButton(tab);
        selectExample->setObjectName(QString::fromUtf8("selectExample"));
        selectExample->setGeometry(QRect(20, 20, 191, 28));
        createROI = new QPushButton(tab);
        createROI->setObjectName(QString::fromUtf8("createROI"));
        createROI->setGeometry(QRect(20, 60, 181, 28));
        getsb = new QPushButton(tab);
        getsb->setObjectName(QString::fromUtf8("getsb"));
        getsb->setGeometry(QRect(310, 40, 181, 51));
        tabWidget->addTab(tab, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        newMission = new QPushButton(tab_3);
        newMission->setObjectName(QString::fromUtf8("newMission"));
        newMission->setGeometry(QRect(20, 10, 93, 28));
        radioButton = new QRadioButton(tab_3);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setGeometry(QRect(140, 40, 115, 19));
        confirmMission = new QPushButton(tab_3);
        confirmMission->setObjectName(QString::fromUtf8("confirmMission"));
        confirmMission->setGeometry(QRect(20, 60, 101, 28));
        tabWidget->addTab(tab_3, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        doCalibration = new QPushButton(tab_2);
        doCalibration->setObjectName(QString::fromUtf8("doCalibration"));
        doCalibration->setGeometry(QRect(80, 90, 271, 28));
        tabWidget->addTab(tab_2, QString());

        retranslateUi(Setting);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Setting);
    } // setupUi

    void retranslateUi(QWidget *Setting)
    {
        Setting->setWindowTitle(QApplication::translate("Setting", "Setting", nullptr));
        saveSetting->setText(QApplication::translate("Setting", "\344\277\235\345\255\230\350\256\276\347\275\256", nullptr));
        Exist->setText(QApplication::translate("Setting", "\351\200\200\345\207\272", nullptr));
        selectExample->setText(QApplication::translate("Setting", "\351\200\211\345\217\226\347\244\272\344\276\213\345\233\276\347\211\207", nullptr));
        createROI->setText(QApplication::translate("Setting", "\345\210\233\345\273\272ROI", nullptr));
        getsb->setText(QApplication::translate("Setting", "\350\216\267\345\217\226\350\242\253\351\200\211\346\213\251\347\237\251\345\275\242", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("Setting", "roi", nullptr));
        newMission->setText(QApplication::translate("Setting", "\346\226\260\345\273\272\344\273\273\345\212\241", nullptr));
        radioButton->setText(QApplication::translate("Setting", "RadioButton", nullptr));
        confirmMission->setText(QApplication::translate("Setting", "\347\241\256\350\256\244\346\267\273\345\212\240\344\273\273\345\212\241", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("Setting", "\344\273\273\345\212\241", nullptr));
        doCalibration->setText(QApplication::translate("Setting", "\346\240\207\345\256\232", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("Setting", "\346\240\207\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Setting: public Ui_Setting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTING_H
