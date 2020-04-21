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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Setting
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    QPushButton *selectExample;
    QPushButton *createROI;
    QPushButton *saveRoi;
    QWidget *tab_3;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QRadioButton *radioButton_none;
    QRadioButton *radioButton_straightness;
    QRadioButton *radioButton_perpendicularity;
    QRadioButton *radioButton_parallelism;
    QRadioButton *radioButton_distance;
    QPushButton *selectObj;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_obj1;
    QLabel *label_obj2;
    QPushButton *confirmMission;
    QLabel *label_4;
    QTableWidget *missiontable;
    QLabel *label_3;
    QPushButton *savemission;
    QWidget *tab_2;
    QPushButton *doCalibration;
    QPushButton *saveCalib;
    QPushButton *selectCalib;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QPushButton *Exist;

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
        tabWidget = new QTabWidget(Setting);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 580, 891, 191));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        selectExample = new QPushButton(tab);
        selectExample->setObjectName(QString::fromUtf8("selectExample"));
        selectExample->setGeometry(QRect(20, 20, 191, 28));
        createROI = new QPushButton(tab);
        createROI->setObjectName(QString::fromUtf8("createROI"));
        createROI->setGeometry(QRect(20, 60, 181, 28));
        saveRoi = new QPushButton(tab);
        saveRoi->setObjectName(QString::fromUtf8("saveRoi"));
        saveRoi->setGeometry(QRect(50, 120, 109, 28));
        tabWidget->addTab(tab, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        verticalLayoutWidget = new QWidget(tab_3);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(20, 30, 91, 125));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        radioButton_none = new QRadioButton(verticalLayoutWidget);
        radioButton_none->setObjectName(QString::fromUtf8("radioButton_none"));

        verticalLayout->addWidget(radioButton_none);

        radioButton_straightness = new QRadioButton(verticalLayoutWidget);
        radioButton_straightness->setObjectName(QString::fromUtf8("radioButton_straightness"));

        verticalLayout->addWidget(radioButton_straightness);

        radioButton_perpendicularity = new QRadioButton(verticalLayoutWidget);
        radioButton_perpendicularity->setObjectName(QString::fromUtf8("radioButton_perpendicularity"));

        verticalLayout->addWidget(radioButton_perpendicularity);

        radioButton_parallelism = new QRadioButton(verticalLayoutWidget);
        radioButton_parallelism->setObjectName(QString::fromUtf8("radioButton_parallelism"));

        verticalLayout->addWidget(radioButton_parallelism);

        radioButton_distance = new QRadioButton(verticalLayoutWidget);
        radioButton_distance->setObjectName(QString::fromUtf8("radioButton_distance"));

        verticalLayout->addWidget(radioButton_distance);

        selectObj = new QPushButton(tab_3);
        selectObj->setObjectName(QString::fromUtf8("selectObj"));
        selectObj->setGeometry(QRect(170, 100, 121, 31));
        horizontalLayoutWidget = new QWidget(tab_3);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(120, 30, 259, 61));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_obj1 = new QLabel(horizontalLayoutWidget);
        label_obj1->setObjectName(QString::fromUtf8("label_obj1"));
        label_obj1->setTextFormat(Qt::PlainText);

        horizontalLayout->addWidget(label_obj1);

        label_obj2 = new QLabel(horizontalLayoutWidget);
        label_obj2->setObjectName(QString::fromUtf8("label_obj2"));
        label_obj2->setTextFormat(Qt::PlainText);
        label_obj2->setScaledContents(true);
        label_obj2->setMargin(0);

        horizontalLayout->addWidget(label_obj2);

        confirmMission = new QPushButton(horizontalLayoutWidget);
        confirmMission->setObjectName(QString::fromUtf8("confirmMission"));

        horizontalLayout->addWidget(confirmMission);

        label_4 = new QLabel(tab_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(160, 10, 72, 15));
        missiontable = new QTableWidget(tab_3);
        if (missiontable->columnCount() < 4)
            missiontable->setColumnCount(4);
        QFont font;
        font.setPointSize(10);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font);
        missiontable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font);
        missiontable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font);
        missiontable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setFont(font);
        missiontable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        missiontable->setObjectName(QString::fromUtf8("missiontable"));
        missiontable->setGeometry(QRect(380, 0, 360, 161));
        QFont font1;
        font1.setPointSize(11);
        missiontable->setFont(font1);
        missiontable->setLineWidth(0);
        missiontable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        missiontable->setSelectionBehavior(QAbstractItemView::SelectRows);
        missiontable->setRowCount(0);
        missiontable->setColumnCount(4);
        missiontable->horizontalHeader()->setDefaultSectionSize(90);
        missiontable->verticalHeader()->setVisible(false);
        label_3 = new QLabel(tab_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 10, 72, 15));
        savemission = new QPushButton(tab_3);
        savemission->setObjectName(QString::fromUtf8("savemission"));
        savemission->setGeometry(QRect(760, 20, 93, 28));
        tabWidget->addTab(tab_3, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        doCalibration = new QPushButton(tab_2);
        doCalibration->setObjectName(QString::fromUtf8("doCalibration"));
        doCalibration->setGeometry(QRect(40, 70, 131, 28));
        saveCalib = new QPushButton(tab_2);
        saveCalib->setObjectName(QString::fromUtf8("saveCalib"));
        saveCalib->setGeometry(QRect(52, 120, 121, 28));
        selectCalib = new QPushButton(tab_2);
        selectCalib->setObjectName(QString::fromUtf8("selectCalib"));
        selectCalib->setGeometry(QRect(40, 30, 141, 28));
        tabWidget->addTab(tab_2, QString());
        verticalLayoutWidget_2 = new QWidget(Setting);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(909, 640, 111, 80));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        Exist = new QPushButton(verticalLayoutWidget_2);
        Exist->setObjectName(QString::fromUtf8("Exist"));

        verticalLayout_2->addWidget(Exist);


        retranslateUi(Setting);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Setting);
    } // setupUi

    void retranslateUi(QWidget *Setting)
    {
        Setting->setWindowTitle(QApplication::translate("Setting", "Setting", nullptr));
        selectExample->setText(QApplication::translate("Setting", "\351\200\211\345\217\226\347\244\272\344\276\213\345\233\276\347\211\207", nullptr));
        createROI->setText(QApplication::translate("Setting", "\345\210\233\345\273\272ROI", nullptr));
        saveRoi->setText(QApplication::translate("Setting", "\344\277\235\345\255\230\350\256\276\347\275\256", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("Setting", "roi", nullptr));
        radioButton_none->setText(QApplication::translate("Setting", "\346\227\240", nullptr));
        radioButton_straightness->setText(QApplication::translate("Setting", "\347\233\264\347\272\277\345\272\246", nullptr));
        radioButton_perpendicularity->setText(QApplication::translate("Setting", "\345\236\202\347\233\264\345\272\246", nullptr));
        radioButton_parallelism->setText(QApplication::translate("Setting", "\345\271\263\350\241\214\345\272\246", nullptr));
        radioButton_distance->setText(QApplication::translate("Setting", "\350\267\235\347\246\273", nullptr));
        selectObj->setText(QApplication::translate("Setting", "\351\200\211\345\217\226\345\257\271\350\261\241", nullptr));
        label_obj1->setText(QApplication::translate("Setting", "\351\200\211\346\213\251\345\257\271\350\261\2411", nullptr));
        label_obj2->setText(QApplication::translate("Setting", "\351\200\211\346\213\251\345\257\271\350\261\2412", nullptr));
        confirmMission->setText(QApplication::translate("Setting", "\347\241\256\350\256\244\346\267\273\345\212\240\344\273\273\345\212\241", nullptr));
        label_4->setText(QApplication::translate("Setting", "\344\273\273\345\212\241\345\257\271\350\261\241", nullptr));
        QTableWidgetItem *___qtablewidgetitem = missiontable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("Setting", "\344\273\273\345\212\241ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = missiontable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("Setting", "\344\273\273\345\212\241\347\261\273\345\236\213", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = missiontable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("Setting", "\345\257\271\350\261\2411", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = missiontable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("Setting", "\345\257\271\350\261\2412", nullptr));
        label_3->setText(QApplication::translate("Setting", "\344\273\273\345\212\241\347\261\273\345\236\213", nullptr));
        savemission->setText(QApplication::translate("Setting", "\344\277\235\345\255\230", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("Setting", "\344\273\273\345\212\241", nullptr));
        doCalibration->setText(QApplication::translate("Setting", "\346\240\207\345\256\232", nullptr));
        saveCalib->setText(QApplication::translate("Setting", "\344\277\235\345\255\230\346\240\207\345\256\232\347\273\223\346\236\234", nullptr));
        selectCalib->setText(QApplication::translate("Setting", "\351\200\211\346\213\251\346\240\207\345\256\232\346\235\277\345\233\276\347\211\207", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("Setting", "\346\240\207\345\256\232", nullptr));
        Exist->setText(QApplication::translate("Setting", "\351\200\200\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Setting: public Ui_Setting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTING_H
