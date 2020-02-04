/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QLabel *label_2;
    QPushButton *ShangChuan;
    QGroupBox *DengLu;
    QLabel *label_16;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QComboBox *comboBox_2;
    QComboBox *comboBox_3;
    QComboBox *comboBox_4;
    QGroupBox *ShenFen;
    QWidget *formLayoutWidget_2;
    QFormLayout *formLayout_2;
    QLabel *label_17;
    QComboBox *comboBox;
    QLabel *label_18;
    QLineEdit *MiMa;
    QPushButton *DengLu_2;
    QLabel *label_19;
    QTabWidget *tabWidget;
    QWidget *TuXiang;
    QGraphicsView *graphicsView;
    QWidget *JiGuang;
    QLabel *label_21;
    QGroupBox *CaoZuo;
    QGroupBox *FuCan;
    QPushButton *FuWei;
    QPushButton *Setting;
    QGroupBox *KaiZanTing;
    QPushButton *KaiShi;
    QPushButton *ZanTing;
    QPushButton *TingZhi;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *ShouZi;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QPushButton *ChaKan;
    QPushButton *Import;
    QLabel *label_22;
    QGroupBox *groupBox_9;
    QLabel *label_25;
    QGroupBox *groupBox_10;
    QLabel *label_23;
    QGroupBox *groupBox_11;
    QLabel *label_24;
    QPushButton *Stop;
    QPushButton *Open;
    QPushButton *Reset;
    QTableView *Count_Bottom;
    QTableView *Count_Top;
    QTabWidget *Test_Inf_Tab;
    QWidget *Sys;
    QScrollArea *Sys_ScrollArea;
    QWidget *Sys_Widget;
    QTableView *Sys_Table;
    QWidget *Testing;
    QTableView *Test_Inf_Testing_Title_TableView;
    QScrollArea *Test_Inf_Testing_ScrollArea;
    QWidget *Test_Inf_Testing_Widget;
    QTableView *Test_Inf_Testing_TableView;
    QWidget *Failed;
    QScrollArea *Test_Inf_Failed_ScrollArea;
    QWidget *Test_Inf_Failed_Widget;
    QTableView *Test_Inf_Failed_TableView;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QString::fromUtf8("MainWindowClass"));
        MainWindowClass->resize(2099, 1080);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(90, 90, 90, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(135, 135, 135, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(112, 112, 112, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(45, 45, 45, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(60, 60, 60, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        QBrush brush6(QColor(136, 136, 136, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush6);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        QBrush brush7(QColor(0, 0, 0, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush7);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush4);
        QBrush brush8(QColor(255, 255, 220, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush7);
        QBrush brush9(QColor(255, 255, 255, 128));
        brush9.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush9);
#endif
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush7);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush7);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush9);
#endif
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush7);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush7);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush9);
#endif
        MainWindowClass->setPalette(palette);
        MainWindowClass->setAutoFillBackground(false);
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(130, 10, 221, 51));
        QPalette palette1;
        QBrush brush10(QColor(255, 0, 127, 255));
        brush10.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush10);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush10);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        label->setPalette(palette1);
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        font.setStyleStrategy(QFont::PreferAntialias);
        label->setFont(font);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(0, 0, 1920, 100));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::Button, brush);
        palette2.setBrush(QPalette::Active, QPalette::Base, brush);
        palette2.setBrush(QPalette::Active, QPalette::Window, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Window, brush);
        label_2->setPalette(palette2);
        label_2->setAutoFillBackground(false);
        label_2->setStyleSheet(QString::fromUtf8("background-color:rgb(255,255,255);\n"
"border-width: 3px;\n"
"border-style: solid;\n"
"border-color: rgb(0, 0, 0)"));
        label_2->setFrameShape(QFrame::Box);
        label_2->setFrameShadow(QFrame::Plain);
        label_2->setLineWidth(0);
        ShangChuan = new QPushButton(centralWidget);
        ShangChuan->setObjectName(QString::fromUtf8("ShangChuan"));
        ShangChuan->setGeometry(QRect(380, 370, 80, 35));
        QPalette palette3;
        QConicalGradient gradient(0.5, 0.522909, 179.9);
        gradient.setSpread(QGradient::PadSpread);
        gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush11(gradient);
        palette3.setBrush(QPalette::Active, QPalette::Button, brush11);
        QConicalGradient gradient1(0.5, 0.522909, 179.9);
        gradient1.setSpread(QGradient::PadSpread);
        gradient1.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient1.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient1.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush12(gradient1);
        palette3.setBrush(QPalette::Active, QPalette::Base, brush12);
        QConicalGradient gradient2(0.5, 0.522909, 179.9);
        gradient2.setSpread(QGradient::PadSpread);
        gradient2.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient2.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient2.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush13(gradient2);
        palette3.setBrush(QPalette::Active, QPalette::Window, brush13);
        QConicalGradient gradient3(0.5, 0.522909, 179.9);
        gradient3.setSpread(QGradient::PadSpread);
        gradient3.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient3.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient3.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush14(gradient3);
        palette3.setBrush(QPalette::Inactive, QPalette::Button, brush14);
        QConicalGradient gradient4(0.5, 0.522909, 179.9);
        gradient4.setSpread(QGradient::PadSpread);
        gradient4.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient4.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient4.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush15(gradient4);
        palette3.setBrush(QPalette::Inactive, QPalette::Base, brush15);
        QConicalGradient gradient5(0.5, 0.522909, 179.9);
        gradient5.setSpread(QGradient::PadSpread);
        gradient5.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient5.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient5.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush16(gradient5);
        palette3.setBrush(QPalette::Inactive, QPalette::Window, brush16);
        QConicalGradient gradient6(0.5, 0.522909, 179.9);
        gradient6.setSpread(QGradient::PadSpread);
        gradient6.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient6.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient6.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush17(gradient6);
        palette3.setBrush(QPalette::Disabled, QPalette::Button, brush17);
        QConicalGradient gradient7(0.5, 0.522909, 179.9);
        gradient7.setSpread(QGradient::PadSpread);
        gradient7.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient7.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient7.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush18(gradient7);
        palette3.setBrush(QPalette::Disabled, QPalette::Base, brush18);
        QConicalGradient gradient8(0.5, 0.522909, 179.9);
        gradient8.setSpread(QGradient::PadSpread);
        gradient8.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient8.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient8.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush19(gradient8);
        palette3.setBrush(QPalette::Disabled, QPalette::Window, brush19);
        ShangChuan->setPalette(palette3);
        QFont font1;
        font1.setFamily(QString::fromUtf8("\346\226\271\346\255\243\347\262\227\351\273\221\345\256\213\347\256\200\344\275\223"));
        font1.setPointSize(12);
        font1.setBold(false);
        font1.setWeight(50);
        ShangChuan->setFont(font1);
        ShangChuan->setAutoFillBackground(false);
        ShangChuan->setStyleSheet(QString::fromUtf8("QPushButton#ShangChuan{\n"
"background-color: qconicalgradient(cx:0.5, cy:0.522909, angle:179.9, stop:0.494318 rgba(134, 198, 233, 255), stop:0.5 rgba(175, 215, 234, 255));\n"
"border: 1px solid rgb(124, 124, 124);\n"
"border-radius:8px;\n"
"}\n"
"QPushButton#ShangChuan:hover{\n"
"background-color: qconicalgradient(cx:0.5, cy:0.522909, angle:179.9, stop:0.494318 rgba(181, 225, 250, 255), stop:0.5 rgba(222, 242, 251, 255));\n"
"  border-radius:8px;\n"
"  border: 1px solid #3C80B1;\n"
"}\n"
"QPushButton#ShangChuan:pressed{\n"
" background-color: qconicalgradient(cx:0.5, cy:0.522909, angle:179.9, stop:0.494318 rgba(214, 214, 214, 255), stop:0.5 rgba(236, 236, 236, 255));\n"
"  border-radius:8px;\n"
"  border: 1px solid #5F92B2;\n"
"}"));
        DengLu = new QGroupBox(centralWidget);
        DengLu->setObjectName(QString::fromUtf8("DengLu"));
        DengLu->setGeometry(QRect(300, 130, 250, 180));
        DengLu->setAutoFillBackground(false);
        DengLu->setStyleSheet(QString::fromUtf8("QGroupBox#DengLu{\n"
"border-image:url(:/VisionTest/Resources/Pictures/DengLu.jpg);\n"
"border: 0px solid;\n"
"}"));
        label_16 = new QLabel(DengLu);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(20, 10, 121, 31));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette4.setBrush(QPalette::Active, QPalette::Text, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette4.setBrush(QPalette::Active, QPalette::PlaceholderText, brush9);
#endif
        palette4.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Text, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette4.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush9);
#endif
        QBrush brush20(QColor(120, 120, 120, 255));
        brush20.setStyle(Qt::SolidPattern);
        palette4.setBrush(QPalette::Disabled, QPalette::WindowText, brush20);
        palette4.setBrush(QPalette::Disabled, QPalette::Text, brush20);
        QBrush brush21(QColor(0, 0, 0, 128));
        brush21.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette4.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush21);
#endif
        label_16->setPalette(palette4);
        QFont font2;
        font2.setFamily(QString::fromUtf8("\346\226\271\346\255\243\347\262\227\351\273\221\345\256\213\347\256\200\344\275\223"));
        font2.setPointSize(16);
        font2.setBold(false);
        font2.setWeight(50);
        label_16->setFont(font2);
        label_16->setAutoFillBackground(false);
        formLayoutWidget = new QWidget(DengLu);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(20, 50, 211, 121));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setSizeConstraint(QLayout::SetNoConstraint);
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout->setLabelAlignment(Qt::AlignCenter);
        formLayout->setHorizontalSpacing(10);
        formLayout->setVerticalSpacing(15);
        formLayout->setContentsMargins(0, 0, 0, 0);
        label_13 = new QLabel(formLayoutWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setFont(font1);

        formLayout->setWidget(0, QFormLayout::LabelRole, label_13);

        label_14 = new QLabel(formLayoutWidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setFont(font1);

        formLayout->setWidget(1, QFormLayout::LabelRole, label_14);

        label_15 = new QLabel(formLayoutWidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setFont(font1);

        formLayout->setWidget(2, QFormLayout::LabelRole, label_15);

        comboBox_2 = new QComboBox(formLayoutWidget);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\346\226\271\346\255\243\347\262\227\351\273\221\345\256\213\347\256\200\344\275\223"));
        font3.setPointSize(12);
        comboBox_2->setFont(font3);
        comboBox_2->setEditable(true);

        formLayout->setWidget(0, QFormLayout::FieldRole, comboBox_2);

        comboBox_3 = new QComboBox(formLayoutWidget);
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));
        comboBox_3->setFont(font3);
        comboBox_3->setEditable(true);

        formLayout->setWidget(1, QFormLayout::FieldRole, comboBox_3);

        comboBox_4 = new QComboBox(formLayoutWidget);
        comboBox_4->setObjectName(QString::fromUtf8("comboBox_4"));
        comboBox_4->setFont(font3);
        comboBox_4->setEditable(true);

        formLayout->setWidget(2, QFormLayout::FieldRole, comboBox_4);

        ShenFen = new QGroupBox(centralWidget);
        ShenFen->setObjectName(QString::fromUtf8("ShenFen"));
        ShenFen->setGeometry(QRect(1650, 130, 220, 180));
        ShenFen->setStyleSheet(QString::fromUtf8("QGroupBox#ShenFen{\n"
"border-image:url(:/VisionTest/Resources/Pictures/ShenFen.jpg);\n"
"border: 0px solid;\n"
"}"));
        formLayoutWidget_2 = new QWidget(ShenFen);
        formLayoutWidget_2->setObjectName(QString::fromUtf8("formLayoutWidget_2"));
        formLayoutWidget_2->setGeometry(QRect(14, 50, 201, 81));
        formLayout_2 = new QFormLayout(formLayoutWidget_2);
        formLayout_2->setSpacing(6);
        formLayout_2->setContentsMargins(11, 11, 11, 11);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setHorizontalSpacing(5);
        formLayout_2->setVerticalSpacing(10);
        formLayout_2->setContentsMargins(5, 5, 5, 5);
        label_17 = new QLabel(formLayoutWidget_2);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setFont(font1);

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_17);

        comboBox = new QComboBox(formLayoutWidget_2);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::WindowText, brush7);
        palette5.setBrush(QPalette::Active, QPalette::Text, brush7);
        QBrush brush22(QColor(0, 0, 0, 128));
        brush22.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette5.setBrush(QPalette::Active, QPalette::PlaceholderText, brush22);
#endif
        palette5.setBrush(QPalette::Inactive, QPalette::WindowText, brush7);
        palette5.setBrush(QPalette::Inactive, QPalette::Text, brush7);
        QBrush brush23(QColor(0, 0, 0, 128));
        brush23.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette5.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush23);
#endif
        palette5.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette5.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        QBrush brush24(QColor(0, 0, 0, 128));
        brush24.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette5.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush24);
#endif
        comboBox->setPalette(palette5);
        comboBox->setFont(font3);
        comboBox->setEditable(false);
        comboBox->setDuplicatesEnabled(false);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, comboBox);

        label_18 = new QLabel(formLayoutWidget_2);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setFont(font3);

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_18);

        MiMa = new QLineEdit(formLayoutWidget_2);
        MiMa->setObjectName(QString::fromUtf8("MiMa"));
        MiMa->setFont(font3);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, MiMa);

        DengLu_2 = new QPushButton(ShenFen);
        DengLu_2->setObjectName(QString::fromUtf8("DengLu_2"));
        DengLu_2->setGeometry(QRect(65, 130, 80, 35));
        QPalette palette6;
        QConicalGradient gradient9(0.5, 0.522909, 179.9);
        gradient9.setSpread(QGradient::PadSpread);
        gradient9.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient9.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient9.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush25(gradient9);
        palette6.setBrush(QPalette::Active, QPalette::Button, brush25);
        QConicalGradient gradient10(0.5, 0.522909, 179.9);
        gradient10.setSpread(QGradient::PadSpread);
        gradient10.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient10.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient10.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush26(gradient10);
        palette6.setBrush(QPalette::Active, QPalette::Base, brush26);
        QConicalGradient gradient11(0.5, 0.522909, 179.9);
        gradient11.setSpread(QGradient::PadSpread);
        gradient11.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient11.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient11.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush27(gradient11);
        palette6.setBrush(QPalette::Active, QPalette::Window, brush27);
        QConicalGradient gradient12(0.5, 0.522909, 179.9);
        gradient12.setSpread(QGradient::PadSpread);
        gradient12.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient12.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient12.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush28(gradient12);
        palette6.setBrush(QPalette::Inactive, QPalette::Button, brush28);
        QConicalGradient gradient13(0.5, 0.522909, 179.9);
        gradient13.setSpread(QGradient::PadSpread);
        gradient13.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient13.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient13.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush29(gradient13);
        palette6.setBrush(QPalette::Inactive, QPalette::Base, brush29);
        QConicalGradient gradient14(0.5, 0.522909, 179.9);
        gradient14.setSpread(QGradient::PadSpread);
        gradient14.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient14.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient14.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush30(gradient14);
        palette6.setBrush(QPalette::Inactive, QPalette::Window, brush30);
        QConicalGradient gradient15(0.5, 0.522909, 179.9);
        gradient15.setSpread(QGradient::PadSpread);
        gradient15.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient15.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient15.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush31(gradient15);
        palette6.setBrush(QPalette::Disabled, QPalette::Button, brush31);
        QConicalGradient gradient16(0.5, 0.522909, 179.9);
        gradient16.setSpread(QGradient::PadSpread);
        gradient16.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient16.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient16.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush32(gradient16);
        palette6.setBrush(QPalette::Disabled, QPalette::Base, brush32);
        QConicalGradient gradient17(0.5, 0.522909, 179.9);
        gradient17.setSpread(QGradient::PadSpread);
        gradient17.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient17.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient17.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush33(gradient17);
        palette6.setBrush(QPalette::Disabled, QPalette::Window, brush33);
        DengLu_2->setPalette(palette6);
        DengLu_2->setFont(font1);
        DengLu_2->setAutoFillBackground(false);
        DengLu_2->setStyleSheet(QString::fromUtf8("QPushButton#DengLu_2{\n"
"background-color: qconicalgradient(cx:0.5, cy:0.522909, angle:179.9, stop:0.494318 rgba(134, 198, 233, 255), stop:0.5 rgba(175, 215, 234, 255));\n"
"border: 1px solid rgb(124, 124, 124);\n"
"border-radius:8px;\n"
"}\n"
"QPushButton#DengLu_2:hover{\n"
"background-color: qconicalgradient(cx:0.5, cy:0.522909, angle:179.9, stop:0.494318 rgba(181, 225, 250, 255), stop:0.5 rgba(222, 242, 251, 255));\n"
"  border-radius:8px;\n"
"  border: 1px solid #3C80B1;\n"
"}\n"
"QPushButton#DengLu_2:pressed{\n"
" background-color: qconicalgradient(cx:0.5, cy:0.522909, angle:179.9, stop:0.494318 rgba(214, 214, 214, 255), stop:0.5 rgba(236, 236, 236, 255));\n"
"  border-radius:8px;\n"
"  border: 1px solid #5F92B2;\n"
"}"));
        label_19 = new QLabel(ShenFen);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(20, 8, 151, 31));
        QPalette palette7;
        palette7.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette7.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette7.setBrush(QPalette::Disabled, QPalette::WindowText, brush20);
        label_19->setPalette(palette7);
        QFont font4;
        font4.setPointSize(11);
        font4.setBold(true);
        font4.setWeight(75);
        label_19->setFont(font4);
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(600, 110, 970, 560));
        QPalette palette8;
        palette8.setBrush(QPalette::Active, QPalette::WindowText, brush7);
        palette8.setBrush(QPalette::Active, QPalette::Text, brush7);
        QBrush brush34(QColor(0, 0, 0, 128));
        brush34.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette8.setBrush(QPalette::Active, QPalette::PlaceholderText, brush34);
#endif
        palette8.setBrush(QPalette::Inactive, QPalette::WindowText, brush7);
        palette8.setBrush(QPalette::Inactive, QPalette::Text, brush7);
        QBrush brush35(QColor(0, 0, 0, 128));
        brush35.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette8.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush35);
#endif
        palette8.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette8.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        QBrush brush36(QColor(0, 0, 0, 128));
        brush36.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette8.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush36);
#endif
        tabWidget->setPalette(palette8);
        TuXiang = new QWidget();
        TuXiang->setObjectName(QString::fromUtf8("TuXiang"));
        graphicsView = new QGraphicsView(TuXiang);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(0, 0, 964, 535));
        graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        tabWidget->addTab(TuXiang, QString());
        JiGuang = new QWidget();
        JiGuang->setObjectName(QString::fromUtf8("JiGuang"));
        label_21 = new QLabel(JiGuang);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(40, 290, 72, 15));
        tabWidget->addTab(JiGuang, QString());
        CaoZuo = new QGroupBox(centralWidget);
        CaoZuo->setObjectName(QString::fromUtf8("CaoZuo"));
        CaoZuo->setGeometry(QRect(1650, 350, 220, 361));
        CaoZuo->setStyleSheet(QString::fromUtf8("QGroupBox#CaoZuo{\n"
"border-image:url(:/VisionTest/Resources/Pictures/CaoZuo.jpg);\n"
"border: 0px solid;\n"
"}"));
        FuCan = new QGroupBox(CaoZuo);
        FuCan->setObjectName(QString::fromUtf8("FuCan"));
        FuCan->setGeometry(QRect(50, 10, 111, 101));
        FuCan->setStyleSheet(QString::fromUtf8("QGroupBox#FuCan{\n"
"border: 0px solid;\n"
"}"));
        FuWei = new QPushButton(FuCan);
        FuWei->setObjectName(QString::fromUtf8("FuWei"));
        FuWei->setGeometry(QRect(0, 20, 110, 30));
        QPalette palette9;
        QConicalGradient gradient18(0.5, 0.522909, 179.9);
        gradient18.setSpread(QGradient::PadSpread);
        gradient18.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient18.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient18.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush37(gradient18);
        palette9.setBrush(QPalette::Active, QPalette::Button, brush37);
        QConicalGradient gradient19(0.5, 0.522909, 179.9);
        gradient19.setSpread(QGradient::PadSpread);
        gradient19.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient19.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient19.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush38(gradient19);
        palette9.setBrush(QPalette::Active, QPalette::Base, brush38);
        QConicalGradient gradient20(0.5, 0.522909, 179.9);
        gradient20.setSpread(QGradient::PadSpread);
        gradient20.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient20.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient20.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush39(gradient20);
        palette9.setBrush(QPalette::Active, QPalette::Window, brush39);
        QConicalGradient gradient21(0.5, 0.522909, 179.9);
        gradient21.setSpread(QGradient::PadSpread);
        gradient21.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient21.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient21.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush40(gradient21);
        palette9.setBrush(QPalette::Inactive, QPalette::Button, brush40);
        QConicalGradient gradient22(0.5, 0.522909, 179.9);
        gradient22.setSpread(QGradient::PadSpread);
        gradient22.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient22.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient22.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush41(gradient22);
        palette9.setBrush(QPalette::Inactive, QPalette::Base, brush41);
        QConicalGradient gradient23(0.5, 0.522909, 179.9);
        gradient23.setSpread(QGradient::PadSpread);
        gradient23.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient23.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient23.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush42(gradient23);
        palette9.setBrush(QPalette::Inactive, QPalette::Window, brush42);
        QConicalGradient gradient24(0.5, 0.522909, 179.9);
        gradient24.setSpread(QGradient::PadSpread);
        gradient24.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient24.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient24.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush43(gradient24);
        palette9.setBrush(QPalette::Disabled, QPalette::Button, brush43);
        QConicalGradient gradient25(0.5, 0.522909, 179.9);
        gradient25.setSpread(QGradient::PadSpread);
        gradient25.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient25.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient25.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush44(gradient25);
        palette9.setBrush(QPalette::Disabled, QPalette::Base, brush44);
        QConicalGradient gradient26(0.5, 0.522909, 179.9);
        gradient26.setSpread(QGradient::PadSpread);
        gradient26.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient26.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient26.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush45(gradient26);
        palette9.setBrush(QPalette::Disabled, QPalette::Window, brush45);
        FuWei->setPalette(palette9);
        FuWei->setFont(font1);
        FuWei->setAutoFillBackground(false);
        FuWei->setStyleSheet(QString::fromUtf8("QPushButton#FuWei{\n"
"background-color: qconicalgradient(cx:0.5, cy:0.522909, angle:179.9, stop:0.494318 rgba(134, 198, 233, 255), stop:0.5 rgba(175, 215, 234, 255));\n"
"border: 1px solid rgb(124, 124, 124);\n"
"border-radius:8px;\n"
"}\n"
"QPushButton#FuWei:hover{\n"
"background-color: qconicalgradient(cx:0.5, cy:0.522909, angle:179.9, stop:0.494318 rgba(181, 225, 250, 255), stop:0.5 rgba(222, 242, 251, 255));\n"
"  border-radius:8px;\n"
"  border: 1px solid #3C80B1;\n"
"}\n"
"QPushButton#FuWei:pressed{\n"
" background-color: qconicalgradient(cx:0.5, cy:0.522909, angle:179.9, stop:0.494318 rgba(214, 214, 214, 255), stop:0.5 rgba(236, 236, 236, 255));\n"
"  border-radius:8px;\n"
"  border: 1px solid #5F92B2;\n"
"}"));
        Setting = new QPushButton(FuCan);
        Setting->setObjectName(QString::fromUtf8("Setting"));
        Setting->setGeometry(QRect(0, 60, 110, 30));
        QPalette palette10;
        QConicalGradient gradient27(0.5, 0.522909, 179.9);
        gradient27.setSpread(QGradient::PadSpread);
        gradient27.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient27.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient27.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush46(gradient27);
        palette10.setBrush(QPalette::Active, QPalette::Button, brush46);
        QConicalGradient gradient28(0.5, 0.522909, 179.9);
        gradient28.setSpread(QGradient::PadSpread);
        gradient28.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient28.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient28.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush47(gradient28);
        palette10.setBrush(QPalette::Active, QPalette::Base, brush47);
        QConicalGradient gradient29(0.5, 0.522909, 179.9);
        gradient29.setSpread(QGradient::PadSpread);
        gradient29.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient29.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient29.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush48(gradient29);
        palette10.setBrush(QPalette::Active, QPalette::Window, brush48);
        QConicalGradient gradient30(0.5, 0.522909, 179.9);
        gradient30.setSpread(QGradient::PadSpread);
        gradient30.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient30.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient30.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush49(gradient30);
        palette10.setBrush(QPalette::Inactive, QPalette::Button, brush49);
        QConicalGradient gradient31(0.5, 0.522909, 179.9);
        gradient31.setSpread(QGradient::PadSpread);
        gradient31.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient31.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient31.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush50(gradient31);
        palette10.setBrush(QPalette::Inactive, QPalette::Base, brush50);
        QConicalGradient gradient32(0.5, 0.522909, 179.9);
        gradient32.setSpread(QGradient::PadSpread);
        gradient32.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient32.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient32.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush51(gradient32);
        palette10.setBrush(QPalette::Inactive, QPalette::Window, brush51);
        QConicalGradient gradient33(0.5, 0.522909, 179.9);
        gradient33.setSpread(QGradient::PadSpread);
        gradient33.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient33.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient33.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush52(gradient33);
        palette10.setBrush(QPalette::Disabled, QPalette::Button, brush52);
        QConicalGradient gradient34(0.5, 0.522909, 179.9);
        gradient34.setSpread(QGradient::PadSpread);
        gradient34.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient34.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient34.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush53(gradient34);
        palette10.setBrush(QPalette::Disabled, QPalette::Base, brush53);
        QConicalGradient gradient35(0.5, 0.522909, 179.9);
        gradient35.setSpread(QGradient::PadSpread);
        gradient35.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient35.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient35.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush54(gradient35);
        palette10.setBrush(QPalette::Disabled, QPalette::Window, brush54);
        Setting->setPalette(palette10);
        Setting->setFont(font1);
        Setting->setAutoFillBackground(false);
        Setting->setStyleSheet(QString::fromUtf8("QPushButton#Setting{\n"
"background-color: qconicalgradient(cx:0.5, cy:0.522909, angle:179.9, stop:0.494318 rgba(134, 198, 233, 255), stop:0.5 rgba(175, 215, 234, 255));\n"
"border: 1px solid rgb(124, 124, 124);\n"
"border-radius:8px;\n"
"}\n"
"QPushButton#Setting:hover{\n"
"background-color: qconicalgradient(cx:0.5, cy:0.522909, angle:179.9, stop:0.494318 rgba(181, 225, 250, 255), stop:0.5 rgba(222, 242, 251, 255));\n"
"  border-radius:8px;\n"
"  border: 1px solid #3C80B1;\n"
"}\n"
"QPushButton#Setting:pressed{\n"
" background-color: qconicalgradient(cx:0.5, cy:0.522909, angle:179.9, stop:0.494318 rgba(214, 214, 214, 255), stop:0.5 rgba(236, 236, 236, 255));\n"
"  border-radius:8px;\n"
"  border: 1px solid #5F92B2;\n"
"}"));
        KaiZanTing = new QGroupBox(CaoZuo);
        KaiZanTing->setObjectName(QString::fromUtf8("KaiZanTing"));
        KaiZanTing->setGeometry(QRect(110, 115, 71, 131));
        KaiZanTing->setStyleSheet(QString::fromUtf8("QGroupBox#KaiZanTing{\n"
"border: 0px solid;\n"
"}"));
        KaiShi = new QPushButton(KaiZanTing);
        KaiShi->setObjectName(QString::fromUtf8("KaiShi"));
        KaiShi->setGeometry(QRect(0, 10, 70, 30));
        QPalette palette11;
        QConicalGradient gradient36(0.5, 0.522909, 179.9);
        gradient36.setSpread(QGradient::PadSpread);
        gradient36.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient36.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient36.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush55(gradient36);
        palette11.setBrush(QPalette::Active, QPalette::Button, brush55);
        QConicalGradient gradient37(0.5, 0.522909, 179.9);
        gradient37.setSpread(QGradient::PadSpread);
        gradient37.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient37.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient37.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush56(gradient37);
        palette11.setBrush(QPalette::Active, QPalette::Base, brush56);
        QConicalGradient gradient38(0.5, 0.522909, 179.9);
        gradient38.setSpread(QGradient::PadSpread);
        gradient38.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient38.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient38.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush57(gradient38);
        palette11.setBrush(QPalette::Active, QPalette::Window, brush57);
        QConicalGradient gradient39(0.5, 0.522909, 179.9);
        gradient39.setSpread(QGradient::PadSpread);
        gradient39.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient39.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient39.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush58(gradient39);
        palette11.setBrush(QPalette::Inactive, QPalette::Button, brush58);
        QConicalGradient gradient40(0.5, 0.522909, 179.9);
        gradient40.setSpread(QGradient::PadSpread);
        gradient40.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient40.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient40.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush59(gradient40);
        palette11.setBrush(QPalette::Inactive, QPalette::Base, brush59);
        QConicalGradient gradient41(0.5, 0.522909, 179.9);
        gradient41.setSpread(QGradient::PadSpread);
        gradient41.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient41.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient41.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush60(gradient41);
        palette11.setBrush(QPalette::Inactive, QPalette::Window, brush60);
        QConicalGradient gradient42(0.5, 0.522909, 179.9);
        gradient42.setSpread(QGradient::PadSpread);
        gradient42.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient42.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient42.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush61(gradient42);
        palette11.setBrush(QPalette::Disabled, QPalette::Button, brush61);
        QConicalGradient gradient43(0.5, 0.522909, 179.9);
        gradient43.setSpread(QGradient::PadSpread);
        gradient43.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient43.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient43.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush62(gradient43);
        palette11.setBrush(QPalette::Disabled, QPalette::Base, brush62);
        QConicalGradient gradient44(0.5, 0.522909, 179.9);
        gradient44.setSpread(QGradient::PadSpread);
        gradient44.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient44.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient44.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush63(gradient44);
        palette11.setBrush(QPalette::Disabled, QPalette::Window, brush63);
        KaiShi->setPalette(palette11);
        KaiShi->setFont(font1);
        KaiShi->setAutoFillBackground(false);
        KaiShi->setStyleSheet(QString::fromUtf8("QPushButton#KaiShi{\n"
"background-color: qconicalgradient(cx:0.5, cy:0.522909, angle:179.9, stop:0.494318 rgba(134, 198, 233, 255), stop:0.5 rgba(175, 215, 234, 255));\n"
"border: 1px solid rgb(124, 124, 124);\n"
"border-radius:8px;\n"
"}\n"
"QPushButton#KaiShi:hover{\n"
"background-color: qconicalgradient(cx:0.5, cy:0.522909, angle:179.9, stop:0.494318 rgba(181, 225, 250, 255), stop:0.5 rgba(222, 242, 251, 255));\n"
"  border-radius:8px;\n"
"  border: 1px solid #3C80B1;\n"
"}\n"
"QPushButton#KaiShi:pressed{\n"
" background-color: qconicalgradient(cx:0.5, cy:0.522909, angle:179.9, stop:0.494318 rgba(214, 214, 214, 255), stop:0.5 rgba(236, 236, 236, 255));\n"
"  border-radius:8px;\n"
"  border: 1px solid #5F92B2;\n"
"}"));
        ZanTing = new QPushButton(KaiZanTing);
        ZanTing->setObjectName(QString::fromUtf8("ZanTing"));
        ZanTing->setGeometry(QRect(0, 50, 70, 30));
        QPalette palette12;
        QConicalGradient gradient45(0.5, 0.522909, 179.9);
        gradient45.setSpread(QGradient::PadSpread);
        gradient45.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient45.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient45.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush64(gradient45);
        palette12.setBrush(QPalette::Active, QPalette::Button, brush64);
        QConicalGradient gradient46(0.5, 0.522909, 179.9);
        gradient46.setSpread(QGradient::PadSpread);
        gradient46.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient46.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient46.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush65(gradient46);
        palette12.setBrush(QPalette::Active, QPalette::Base, brush65);
        QConicalGradient gradient47(0.5, 0.522909, 179.9);
        gradient47.setSpread(QGradient::PadSpread);
        gradient47.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient47.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient47.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush66(gradient47);
        palette12.setBrush(QPalette::Active, QPalette::Window, brush66);
        QConicalGradient gradient48(0.5, 0.522909, 179.9);
        gradient48.setSpread(QGradient::PadSpread);
        gradient48.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient48.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient48.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush67(gradient48);
        palette12.setBrush(QPalette::Inactive, QPalette::Button, brush67);
        QConicalGradient gradient49(0.5, 0.522909, 179.9);
        gradient49.setSpread(QGradient::PadSpread);
        gradient49.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient49.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient49.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush68(gradient49);
        palette12.setBrush(QPalette::Inactive, QPalette::Base, brush68);
        QConicalGradient gradient50(0.5, 0.522909, 179.9);
        gradient50.setSpread(QGradient::PadSpread);
        gradient50.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient50.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient50.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush69(gradient50);
        palette12.setBrush(QPalette::Inactive, QPalette::Window, brush69);
        QConicalGradient gradient51(0.5, 0.522909, 179.9);
        gradient51.setSpread(QGradient::PadSpread);
        gradient51.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient51.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient51.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush70(gradient51);
        palette12.setBrush(QPalette::Disabled, QPalette::Button, brush70);
        QConicalGradient gradient52(0.5, 0.522909, 179.9);
        gradient52.setSpread(QGradient::PadSpread);
        gradient52.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient52.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient52.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush71(gradient52);
        palette12.setBrush(QPalette::Disabled, QPalette::Base, brush71);
        QConicalGradient gradient53(0.5, 0.522909, 179.9);
        gradient53.setSpread(QGradient::PadSpread);
        gradient53.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient53.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient53.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush72(gradient53);
        palette12.setBrush(QPalette::Disabled, QPalette::Window, brush72);
        ZanTing->setPalette(palette12);
        ZanTing->setFont(font1);
        ZanTing->setAutoFillBackground(false);
        ZanTing->setStyleSheet(QString::fromUtf8("QPushButton#ZanTing{\n"
"background-color: qconicalgradient(cx:0.5, cy:0.522909, angle:179.9, stop:0.494318 rgba(134, 198, 233, 255), stop:0.5 rgba(175, 215, 234, 255));\n"
"border: 1px solid rgb(124, 124, 124);\n"
"border-radius:8px;\n"
"}\n"
"QPushButton#ZanTing:hover{\n"
"background-color: qconicalgradient(cx:0.5, cy:0.522909, angle:179.9, stop:0.494318 rgba(181, 225, 250, 255), stop:0.5 rgba(222, 242, 251, 255));\n"
"  border-radius:8px;\n"
"  border: 1px solid #3C80B1;\n"
"}\n"
"QPushButton#ZanTing:pressed{\n"
" background-color: qconicalgradient(cx:0.5, cy:0.522909, angle:179.9, stop:0.494318 rgba(214, 214, 214, 255), stop:0.5 rgba(236, 236, 236, 255));\n"
"  border-radius:8px;\n"
"  border: 1px solid #5F92B2;\n"
"}"));
        TingZhi = new QPushButton(KaiZanTing);
        TingZhi->setObjectName(QString::fromUtf8("TingZhi"));
        TingZhi->setGeometry(QRect(0, 90, 70, 30));
        QPalette palette13;
        QConicalGradient gradient54(0.5, 0.522909, 179.9);
        gradient54.setSpread(QGradient::PadSpread);
        gradient54.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient54.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient54.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush73(gradient54);
        palette13.setBrush(QPalette::Active, QPalette::Button, brush73);
        QConicalGradient gradient55(0.5, 0.522909, 179.9);
        gradient55.setSpread(QGradient::PadSpread);
        gradient55.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient55.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient55.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush74(gradient55);
        palette13.setBrush(QPalette::Active, QPalette::Base, brush74);
        QConicalGradient gradient56(0.5, 0.522909, 179.9);
        gradient56.setSpread(QGradient::PadSpread);
        gradient56.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient56.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient56.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush75(gradient56);
        palette13.setBrush(QPalette::Active, QPalette::Window, brush75);
        QConicalGradient gradient57(0.5, 0.522909, 179.9);
        gradient57.setSpread(QGradient::PadSpread);
        gradient57.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient57.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient57.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush76(gradient57);
        palette13.setBrush(QPalette::Inactive, QPalette::Button, brush76);
        QConicalGradient gradient58(0.5, 0.522909, 179.9);
        gradient58.setSpread(QGradient::PadSpread);
        gradient58.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient58.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient58.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush77(gradient58);
        palette13.setBrush(QPalette::Inactive, QPalette::Base, brush77);
        QConicalGradient gradient59(0.5, 0.522909, 179.9);
        gradient59.setSpread(QGradient::PadSpread);
        gradient59.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient59.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient59.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush78(gradient59);
        palette13.setBrush(QPalette::Inactive, QPalette::Window, brush78);
        QConicalGradient gradient60(0.5, 0.522909, 179.9);
        gradient60.setSpread(QGradient::PadSpread);
        gradient60.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient60.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient60.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush79(gradient60);
        palette13.setBrush(QPalette::Disabled, QPalette::Button, brush79);
        QConicalGradient gradient61(0.5, 0.522909, 179.9);
        gradient61.setSpread(QGradient::PadSpread);
        gradient61.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient61.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient61.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush80(gradient61);
        palette13.setBrush(QPalette::Disabled, QPalette::Base, brush80);
        QConicalGradient gradient62(0.5, 0.522909, 179.9);
        gradient62.setSpread(QGradient::PadSpread);
        gradient62.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient62.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient62.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush81(gradient62);
        palette13.setBrush(QPalette::Disabled, QPalette::Window, brush81);
        TingZhi->setPalette(palette13);
        TingZhi->setFont(font1);
        TingZhi->setAutoFillBackground(false);
        TingZhi->setStyleSheet(QString::fromUtf8("QPushButton#TingZhi{\n"
"background-color: qconicalgradient(cx:0.5, cy:0.522909, angle:179.9, stop:0.494318 rgba(134, 198, 233, 255), stop:0.5 rgba(175, 215, 234, 255));\n"
"border: 1px solid rgb(124, 124, 124);\n"
"border-radius:8px;\n"
"}\n"
"QPushButton#TingZhi:hover{\n"
"background-color: qconicalgradient(cx:0.5, cy:0.522909, angle:179.9, stop:0.494318 rgba(181, 225, 250, 255), stop:0.5 rgba(222, 242, 251, 255));\n"
"  border-radius:8px;\n"
"  border: 1px solid #3C80B1;\n"
"}\n"
"QPushButton#TingZhi:pressed{\n"
" background-color: qconicalgradient(cx:0.5, cy:0.522909, angle:179.9, stop:0.494318 rgba(214, 214, 214, 255), stop:0.5 rgba(236, 236, 236, 255));\n"
"  border-radius:8px;\n"
"  border: 1px solid #5F92B2;\n"
"}"));
        verticalLayoutWidget_3 = new QWidget(CaoZuo);
        verticalLayoutWidget_3->setObjectName(QString::fromUtf8("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(30, 140, 69, 80));
        ShouZi = new QVBoxLayout(verticalLayoutWidget_3);
        ShouZi->setSpacing(10);
        ShouZi->setContentsMargins(11, 11, 11, 11);
        ShouZi->setObjectName(QString::fromUtf8("ShouZi"));
        ShouZi->setContentsMargins(0, 0, 0, 0);
        radioButton = new QRadioButton(verticalLayoutWidget_3);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setFont(font3);

        ShouZi->addWidget(radioButton);

        radioButton_2 = new QRadioButton(verticalLayoutWidget_3);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));
        radioButton_2->setFont(font3);

        ShouZi->addWidget(radioButton_2);

        ChaKan = new QPushButton(CaoZuo);
        ChaKan->setObjectName(QString::fromUtf8("ChaKan"));
        ChaKan->setGeometry(QRect(35, 265, 150, 30));
        QPalette palette14;
        QConicalGradient gradient63(0.5, 0.522909, 179.9);
        gradient63.setSpread(QGradient::PadSpread);
        gradient63.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient63.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient63.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush82(gradient63);
        palette14.setBrush(QPalette::Active, QPalette::Button, brush82);
        QConicalGradient gradient64(0.5, 0.522909, 179.9);
        gradient64.setSpread(QGradient::PadSpread);
        gradient64.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient64.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient64.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush83(gradient64);
        palette14.setBrush(QPalette::Active, QPalette::Base, brush83);
        QConicalGradient gradient65(0.5, 0.522909, 179.9);
        gradient65.setSpread(QGradient::PadSpread);
        gradient65.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient65.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient65.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush84(gradient65);
        palette14.setBrush(QPalette::Active, QPalette::Window, brush84);
        QConicalGradient gradient66(0.5, 0.522909, 179.9);
        gradient66.setSpread(QGradient::PadSpread);
        gradient66.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient66.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient66.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush85(gradient66);
        palette14.setBrush(QPalette::Inactive, QPalette::Button, brush85);
        QConicalGradient gradient67(0.5, 0.522909, 179.9);
        gradient67.setSpread(QGradient::PadSpread);
        gradient67.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient67.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient67.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush86(gradient67);
        palette14.setBrush(QPalette::Inactive, QPalette::Base, brush86);
        QConicalGradient gradient68(0.5, 0.522909, 179.9);
        gradient68.setSpread(QGradient::PadSpread);
        gradient68.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient68.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient68.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush87(gradient68);
        palette14.setBrush(QPalette::Inactive, QPalette::Window, brush87);
        QConicalGradient gradient69(0.5, 0.522909, 179.9);
        gradient69.setSpread(QGradient::PadSpread);
        gradient69.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient69.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient69.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush88(gradient69);
        palette14.setBrush(QPalette::Disabled, QPalette::Button, brush88);
        QConicalGradient gradient70(0.5, 0.522909, 179.9);
        gradient70.setSpread(QGradient::PadSpread);
        gradient70.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient70.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient70.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush89(gradient70);
        palette14.setBrush(QPalette::Disabled, QPalette::Base, brush89);
        QConicalGradient gradient71(0.5, 0.522909, 179.9);
        gradient71.setSpread(QGradient::PadSpread);
        gradient71.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient71.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient71.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush90(gradient71);
        palette14.setBrush(QPalette::Disabled, QPalette::Window, brush90);
        ChaKan->setPalette(palette14);
        ChaKan->setFont(font1);
        ChaKan->setAutoFillBackground(false);
        ChaKan->setStyleSheet(QString::fromUtf8("QPushButton#ChaKan{\n"
"background-color: qconicalgradient(cx:0.5, cy:0.522909, angle:179.9, stop:0.494318 rgba(134, 198, 233, 255), stop:0.5 rgba(175, 215, 234, 255));\n"
"border: 1px solid rgb(124, 124, 124);\n"
"border-radius:8px;\n"
"}\n"
"QPushButton#ChaKan:hover{\n"
"background-color: qconicalgradient(cx:0.5, cy:0.522909, angle:179.9, stop:0.494318 rgba(181, 225, 250, 255), stop:0.5 rgba(222, 242, 251, 255));\n"
"  border-radius:8px;\n"
"  border: 1px solid #3C80B1;\n"
"}\n"
"QPushButton#ChaKan:pressed{\n"
" background-color: qconicalgradient(cx:0.5, cy:0.522909, angle:179.9, stop:0.494318 rgba(214, 214, 214, 255), stop:0.5 rgba(236, 236, 236, 255));\n"
"  border-radius:8px;\n"
"  border: 1px solid #5F92B2;\n"
"}"));
        Import = new QPushButton(CaoZuo);
        Import->setObjectName(QString::fromUtf8("Import"));
        Import->setGeometry(QRect(50, 310, 131, 31));
        label_22 = new QLabel(centralWidget);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setGeometry(QRect(700, 680, 461, 141));
        QFont font5;
        font5.setPointSize(18);
        font5.setBold(true);
        font5.setWeight(75);
        label_22->setFont(font5);
        label_22->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        groupBox_9 = new QGroupBox(centralWidget);
        groupBox_9->setObjectName(QString::fromUtf8("groupBox_9"));
        groupBox_9->setGeometry(QRect(1670, 20, 70, 70));
        groupBox_9->setStyleSheet(QString::fromUtf8("QGroupBox#groupBox_9{\n"
"background-image:url(:/VisionTest/Resources/Pictures/Deng_huang.png);\n"
"border: 0px solid;\n"
"}"));
        label_25 = new QLabel(groupBox_9);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setGeometry(QRect(16, 15, 51, 41));
        QPalette palette15;
        QBrush brush91(QColor(83, 83, 83, 255));
        brush91.setStyle(Qt::SolidPattern);
        palette15.setBrush(QPalette::Active, QPalette::WindowText, brush91);
        palette15.setBrush(QPalette::Active, QPalette::Text, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette15.setBrush(QPalette::Active, QPalette::PlaceholderText, brush9);
#endif
        palette15.setBrush(QPalette::Inactive, QPalette::WindowText, brush91);
        palette15.setBrush(QPalette::Inactive, QPalette::Text, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette15.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush9);
#endif
        palette15.setBrush(QPalette::Disabled, QPalette::WindowText, brush20);
        palette15.setBrush(QPalette::Disabled, QPalette::Text, brush20);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette15.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush21);
#endif
        label_25->setPalette(palette15);
        QFont font6;
        font6.setFamily(QString::fromUtf8("\346\226\271\346\255\243\347\262\227\351\273\221\345\256\213\347\256\200\344\275\223"));
        font6.setPointSize(14);
        font6.setBold(false);
        font6.setWeight(50);
        label_25->setFont(font6);
        groupBox_10 = new QGroupBox(centralWidget);
        groupBox_10->setObjectName(QString::fromUtf8("groupBox_10"));
        groupBox_10->setGeometry(QRect(1570, 20, 70, 70));
        groupBox_10->setStyleSheet(QString::fromUtf8("QGroupBox#groupBox_10{\n"
"background-image:url(:/VisionTest/Resources/Pictures/Deng_hong.png);\n"
"border: 0px solid;\n"
"}"));
        label_23 = new QLabel(groupBox_10);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(10, 15, 51, 41));
        QPalette palette16;
        palette16.setBrush(QPalette::Active, QPalette::WindowText, brush91);
        palette16.setBrush(QPalette::Active, QPalette::Text, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette16.setBrush(QPalette::Active, QPalette::PlaceholderText, brush9);
#endif
        palette16.setBrush(QPalette::Inactive, QPalette::WindowText, brush91);
        palette16.setBrush(QPalette::Inactive, QPalette::Text, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette16.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush9);
#endif
        palette16.setBrush(QPalette::Disabled, QPalette::WindowText, brush20);
        palette16.setBrush(QPalette::Disabled, QPalette::Text, brush20);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette16.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush21);
#endif
        label_23->setPalette(palette16);
        label_23->setFont(font6);
        groupBox_11 = new QGroupBox(centralWidget);
        groupBox_11->setObjectName(QString::fromUtf8("groupBox_11"));
        groupBox_11->setGeometry(QRect(1770, 20, 70, 70));
        groupBox_11->setStyleSheet(QString::fromUtf8("QGroupBox#groupBox_11{\n"
"background-image:url(:/VisionTest/Resources/Pictures/Deng_lv.png);\n"
"border: 0px solid;\n"
"}"));
        label_24 = new QLabel(groupBox_11);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(19, 15, 51, 41));
        QPalette palette17;
        palette17.setBrush(QPalette::Active, QPalette::WindowText, brush91);
        palette17.setBrush(QPalette::Active, QPalette::Text, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette17.setBrush(QPalette::Active, QPalette::PlaceholderText, brush9);
#endif
        palette17.setBrush(QPalette::Inactive, QPalette::WindowText, brush91);
        palette17.setBrush(QPalette::Inactive, QPalette::Text, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette17.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush9);
#endif
        palette17.setBrush(QPalette::Disabled, QPalette::WindowText, brush20);
        palette17.setBrush(QPalette::Disabled, QPalette::Text, brush20);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette17.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush21);
#endif
        label_24->setPalette(palette17);
        label_24->setFont(font6);
        Stop = new QPushButton(centralWidget);
        Stop->setObjectName(QString::fromUtf8("Stop"));
        Stop->setGeometry(QRect(90, 300, 80, 80));
        Stop->setStyleSheet(QString::fromUtf8("QPushButton#Stop{\n"
"background-image:url(:/VisionTest/Resources/Pictures/AnNiuHong.png);\n"
"border: 0 px ;\n"
"}\n"
"QPushButton#Stop:hover{\n"
"background-image:url(:/VisionTest/Resources/Pictures/AnNiuHong.png);\n"
"  border-radius:8px;\n"
"  border: 0px;\n"
"}\n"
"QPushButton#Stop:pressed{\n"
"background-image:url(:/VisionTest/Resources/Pictures/AnNiuHuiTing.png);\n"
"  border: 0px ;\n"
"}"));
        Open = new QPushButton(centralWidget);
        Open->setObjectName(QString::fromUtf8("Open"));
        Open->setGeometry(QRect(90, 200, 80, 80));
        Open->setStyleSheet(QString::fromUtf8("QPushButton#Open{\n"
"background-image:url(:/VisionTest/Resources/Pictures/AnNiu.png);\n"
"border: 0 px ;\n"
"}\n"
"QPushButton#Open:hover{\n"
"background-image:url(:/VisionTest/Resources/Pictures/AnNiu.png);\n"
"  border-radius:8px;\n"
"  border: 0px;\n"
"}\n"
"QPushButton#Open:pressed{\n"
"background-image:url(:/VisionTest/Resources/Pictures/AnNiu.png);\n"
"  border: 0px ;\n"
"}"));
        Reset = new QPushButton(centralWidget);
        Reset->setObjectName(QString::fromUtf8("Reset"));
        Reset->setGeometry(QRect(1340, 760, 110, 40));
        QPalette palette18;
        QConicalGradient gradient72(0.5, 0.522909, 179.9);
        gradient72.setSpread(QGradient::PadSpread);
        gradient72.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient72.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient72.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush92(gradient72);
        palette18.setBrush(QPalette::Active, QPalette::Button, brush92);
        QConicalGradient gradient73(0.5, 0.522909, 179.9);
        gradient73.setSpread(QGradient::PadSpread);
        gradient73.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient73.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient73.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush93(gradient73);
        palette18.setBrush(QPalette::Active, QPalette::Base, brush93);
        QConicalGradient gradient74(0.5, 0.522909, 179.9);
        gradient74.setSpread(QGradient::PadSpread);
        gradient74.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient74.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient74.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush94(gradient74);
        palette18.setBrush(QPalette::Active, QPalette::Window, brush94);
        QConicalGradient gradient75(0.5, 0.522909, 179.9);
        gradient75.setSpread(QGradient::PadSpread);
        gradient75.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient75.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient75.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush95(gradient75);
        palette18.setBrush(QPalette::Inactive, QPalette::Button, brush95);
        QConicalGradient gradient76(0.5, 0.522909, 179.9);
        gradient76.setSpread(QGradient::PadSpread);
        gradient76.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient76.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient76.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush96(gradient76);
        palette18.setBrush(QPalette::Inactive, QPalette::Base, brush96);
        QConicalGradient gradient77(0.5, 0.522909, 179.9);
        gradient77.setSpread(QGradient::PadSpread);
        gradient77.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient77.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient77.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush97(gradient77);
        palette18.setBrush(QPalette::Inactive, QPalette::Window, brush97);
        QConicalGradient gradient78(0.5, 0.522909, 179.9);
        gradient78.setSpread(QGradient::PadSpread);
        gradient78.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient78.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient78.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush98(gradient78);
        palette18.setBrush(QPalette::Disabled, QPalette::Button, brush98);
        QConicalGradient gradient79(0.5, 0.522909, 179.9);
        gradient79.setSpread(QGradient::PadSpread);
        gradient79.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient79.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient79.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush99(gradient79);
        palette18.setBrush(QPalette::Disabled, QPalette::Base, brush99);
        QConicalGradient gradient80(0.5, 0.522909, 179.9);
        gradient80.setSpread(QGradient::PadSpread);
        gradient80.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient80.setColorAt(0.494318, QColor(134, 198, 233, 255));
        gradient80.setColorAt(0.5, QColor(175, 215, 234, 255));
        QBrush brush100(gradient80);
        palette18.setBrush(QPalette::Disabled, QPalette::Window, brush100);
        Reset->setPalette(palette18);
        Reset->setFont(font1);
        Reset->setAutoFillBackground(false);
        Reset->setStyleSheet(QString::fromUtf8("QPushButton#Reset{\n"
"background-color: qconicalgradient(cx:0.5, cy:0.522909, angle:179.9, stop:0.494318 rgba(134, 198, 233, 255), stop:0.5 rgba(175, 215, 234, 255));\n"
"border: 1px solid rgb(124, 124, 124);\n"
"border-radius:8px;\n"
"}\n"
"QPushButton#Reset:hover{\n"
"background-color: qconicalgradient(cx:0.5, cy:0.522909, angle:179.9, stop:0.494318 rgba(181, 225, 250, 255), stop:0.5 rgba(222, 242, 251, 255));\n"
"  border-radius:8px;\n"
"  border: 1px solid #3C80B1;\n"
"}\n"
"QPushButton#Reset:pressed{\n"
" background-color: qconicalgradient(cx:0.5, cy:0.522909, angle:179.9, stop:0.494318 rgba(214, 214, 214, 255), stop:0.5 rgba(236, 236, 236, 255));\n"
"  border-radius:8px;\n"
"  border: 1px solid #5F92B2;\n"
"}"));
        Count_Bottom = new QTableView(centralWidget);
        Count_Bottom->setObjectName(QString::fromUtf8("Count_Bottom"));
        Count_Bottom->setGeometry(QRect(1470, 740, 400, 80));
        QFont font7;
        font7.setPointSize(11);
        Count_Bottom->setFont(font7);
        Count_Bottom->setStyleSheet(QString::fromUtf8("background-color:rgba(255, 255, 255,0);\n"
"		color:rgb(255,255,255);\n"
"		gridline-color: rgb(255, 255,255);\n"
"		border-radius:0px"));
        Count_Bottom->setLineWidth(0);
        Count_Bottom->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        Count_Bottom->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        Count_Bottom->setAutoScroll(false);
        Count_Bottom->setEditTriggers(QAbstractItemView::NoEditTriggers);
        Count_Bottom->setSelectionMode(QAbstractItemView::NoSelection);
        Count_Bottom->horizontalHeader()->setVisible(false);
        Count_Bottom->horizontalHeader()->setHighlightSections(false);
        Count_Bottom->verticalHeader()->setVisible(false);
        Count_Bottom->verticalHeader()->setDefaultSectionSize(40);
        Count_Top = new QTableView(centralWidget);
        Count_Top->setObjectName(QString::fromUtf8("Count_Top"));
        Count_Top->setGeometry(QRect(560, 60, 800, 40));
        QFont font8;
        font8.setPointSize(11);
        font8.setBold(false);
        font8.setWeight(50);
        Count_Top->setFont(font8);
        Count_Top->setStyleSheet(QString::fromUtf8("background-color:rgba(255, 255, 255,0);\n"
"		color:rgb(0,0,0);\n"
"		border-color:rgba(0,0,0,0);\n"
"		border-radius:0px;"));
        Count_Top->setLineWidth(0);
        Count_Top->setMidLineWidth(0);
        Count_Top->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        Count_Top->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        Count_Top->setEditTriggers(QAbstractItemView::NoEditTriggers);
        Count_Top->setSelectionMode(QAbstractItemView::NoSelection);
        Count_Top->setShowGrid(false);
        Count_Top->setGridStyle(Qt::NoPen);
        Count_Top->horizontalHeader()->setVisible(false);
        Count_Top->verticalHeader()->setVisible(false);
        Count_Top->verticalHeader()->setDefaultSectionSize(40);
        Test_Inf_Tab = new QTabWidget(centralWidget);
        Test_Inf_Tab->setObjectName(QString::fromUtf8("Test_Inf_Tab"));
        Test_Inf_Tab->setGeometry(QRect(50, 850, 1820, 201));
        Test_Inf_Tab->setStyleSheet(QString::fromUtf8("QTabBar::tab{\n"
"		height:20;\n"
"		width:90;\n"
"		background: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1,\n"
"			stop : 0 #808080, stop: 0.4 #858585,\n"
"			stop: 0.5 #3A3A3A, stop: 1.0 #505050);\n"
"		color:rgba(255,255,255,150);\n"
"		border: 1px solid #C4C4C3;\n"
"		border-bottom: 0px;\n"
"		border-radius:0px;\n"
"		}\n"
"		QTabBar::tab:hover{\n"
"	    background: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1,\n"
"			stop : 0 #fafafa, stop: 0.4 #f4f4f4,\n"
"			stop: 0.5 #e7e7e7, stop: 1.0 #fafafa);}\n"
"		QTabBar::tab:selected{\n"
"		color:rgba(0,0,255,150);\n"
"		background: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1,\n"
"		stop : 0 #9A9A9A, stop: 0.4 #9F9F9F,\n"
"		stop: 0.5 #5B5B5B, stop: 1.0 #6A6A6A);\n"
"	   }"));
        Sys = new QWidget();
        Sys->setObjectName(QString::fromUtf8("Sys"));
        Sys_ScrollArea = new QScrollArea(Sys);
        Sys_ScrollArea->setObjectName(QString::fromUtf8("Sys_ScrollArea"));
        Sys_ScrollArea->setGeometry(QRect(0, 0, 1820, 180));
        Sys_ScrollArea->setStyleSheet(QString::fromUtf8("background-color: rgb(50,50, 50);\n"
"		border-radius:0px;"));
        Sys_ScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        Sys_ScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        Sys_ScrollArea->setWidgetResizable(true);
        Sys_Widget = new QWidget();
        Sys_Widget->setObjectName(QString::fromUtf8("Sys_Widget"));
        Sys_Widget->setGeometry(QRect(0, 0, 1800, 300));
        Sys_Widget->setMinimumSize(QSize(1800, 300));
        Sys_Widget->setMaximumSize(QSize(16777215, 500));
        Sys_Table = new QTableView(Sys_Widget);
        Sys_Table->setObjectName(QString::fromUtf8("Sys_Table"));
        Sys_Table->setGeometry(QRect(0, 0, 1805, 240));
        Sys_Table->setFont(font7);
        Sys_Table->setStyleSheet(QString::fromUtf8("QTableView{\n"
"		background-color:rgba(255, 255, 255,0);\n"
"		color:rgb(255,255,255);\n"
"		gridline-color: rgb(255, 255,255);\n"
"		border-radius:0px;\n"
"		}"));
        Sys_Table->setLineWidth(0);
        Sys_Table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        Sys_Table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        Sys_Table->setEditTriggers(QAbstractItemView::NoEditTriggers);
        Sys_Table->setSelectionMode(QAbstractItemView::NoSelection);
        Sys_Table->horizontalHeader()->setVisible(false);
        Sys_Table->verticalHeader()->setVisible(false);
        Sys_Table->verticalHeader()->setDefaultSectionSize(30);
        Sys_Table->verticalHeader()->setMinimumSectionSize(15);
        Sys_ScrollArea->setWidget(Sys_Widget);
        Test_Inf_Tab->addTab(Sys, QString());
        Testing = new QWidget();
        Testing->setObjectName(QString::fromUtf8("Testing"));
        Test_Inf_Testing_Title_TableView = new QTableView(Testing);
        Test_Inf_Testing_Title_TableView->setObjectName(QString::fromUtf8("Test_Inf_Testing_Title_TableView"));
        Test_Inf_Testing_Title_TableView->setGeometry(QRect(0, 0, 1805, 30));
        Test_Inf_Testing_Title_TableView->setStyleSheet(QString::fromUtf8("border-radius:0px;\n"
"gridline - radius:0px;\n"
"background-color: rgb(50,50, 50);\n"
""));
        Test_Inf_Testing_Title_TableView->setLineWidth(0);
        Test_Inf_Testing_Title_TableView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        Test_Inf_Testing_Title_TableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        Test_Inf_Testing_Title_TableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        Test_Inf_Testing_Title_TableView->setSelectionMode(QAbstractItemView::NoSelection);
        Test_Inf_Testing_Title_TableView->horizontalHeader()->setVisible(false);
        Test_Inf_Testing_Title_TableView->horizontalHeader()->setHighlightSections(false);
        Test_Inf_Testing_Title_TableView->verticalHeader()->setVisible(false);
        Test_Inf_Testing_Title_TableView->verticalHeader()->setDefaultSectionSize(30);
        Test_Inf_Testing_Title_TableView->verticalHeader()->setHighlightSections(false);
        Test_Inf_Testing_ScrollArea = new QScrollArea(Testing);
        Test_Inf_Testing_ScrollArea->setObjectName(QString::fromUtf8("Test_Inf_Testing_ScrollArea"));
        Test_Inf_Testing_ScrollArea->setGeometry(QRect(0, 0, 1820, 180));
        Test_Inf_Testing_ScrollArea->setStyleSheet(QString::fromUtf8("background-color: rgb(50,50, 50);\n"
"		border-radius:0px;"));
        Test_Inf_Testing_ScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        Test_Inf_Testing_ScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        Test_Inf_Testing_ScrollArea->setWidgetResizable(true);
        Test_Inf_Testing_Widget = new QWidget();
        Test_Inf_Testing_Widget->setObjectName(QString::fromUtf8("Test_Inf_Testing_Widget"));
        Test_Inf_Testing_Widget->setGeometry(QRect(0, 0, 1820, 330));
        Test_Inf_Testing_Widget->setMinimumSize(QSize(1820, 330));
        Test_Inf_Testing_TableView = new QTableView(Test_Inf_Testing_Widget);
        Test_Inf_Testing_TableView->setObjectName(QString::fromUtf8("Test_Inf_Testing_TableView"));
        Test_Inf_Testing_TableView->setGeometry(QRect(0, 30, 1800, 300));
        Test_Inf_Testing_TableView->setStyleSheet(QString::fromUtf8("border-radius:0px;\n"
"		gridline - radius:0px;"));
        Test_Inf_Testing_TableView->setLineWidth(0);
        Test_Inf_Testing_TableView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        Test_Inf_Testing_TableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        Test_Inf_Testing_TableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        Test_Inf_Testing_TableView->setSelectionMode(QAbstractItemView::NoSelection);
        Test_Inf_Testing_TableView->setShowGrid(false);
        Test_Inf_Testing_TableView->horizontalHeader()->setVisible(false);
        Test_Inf_Testing_TableView->horizontalHeader()->setHighlightSections(false);
        Test_Inf_Testing_TableView->verticalHeader()->setVisible(false);
        Test_Inf_Testing_TableView->verticalHeader()->setDefaultSectionSize(30);
        Test_Inf_Testing_TableView->verticalHeader()->setHighlightSections(false);
        Test_Inf_Testing_TableView->verticalHeader()->setMinimumSectionSize(15);
        Test_Inf_Testing_ScrollArea->setWidget(Test_Inf_Testing_Widget);
        Test_Inf_Tab->addTab(Testing, QString());
        Test_Inf_Testing_ScrollArea->raise();
        Test_Inf_Testing_Title_TableView->raise();
        Failed = new QWidget();
        Failed->setObjectName(QString::fromUtf8("Failed"));
        Test_Inf_Failed_ScrollArea = new QScrollArea(Failed);
        Test_Inf_Failed_ScrollArea->setObjectName(QString::fromUtf8("Test_Inf_Failed_ScrollArea"));
        Test_Inf_Failed_ScrollArea->setGeometry(QRect(0, 0, 1820, 180));
        Test_Inf_Failed_ScrollArea->setStyleSheet(QString::fromUtf8("background-color: rgb(50,50, 50);\n"
"		border-radius:0px;"));
        Test_Inf_Failed_ScrollArea->setLineWidth(0);
        Test_Inf_Failed_ScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        Test_Inf_Failed_ScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        Test_Inf_Failed_ScrollArea->setWidgetResizable(true);
        Test_Inf_Failed_Widget = new QWidget();
        Test_Inf_Failed_Widget->setObjectName(QString::fromUtf8("Test_Inf_Failed_Widget"));
        Test_Inf_Failed_Widget->setGeometry(QRect(0, 0, 1850, 330));
        Test_Inf_Failed_Widget->setMinimumSize(QSize(1850, 330));
        Test_Inf_Failed_TableView = new QTableView(Test_Inf_Failed_Widget);
        Test_Inf_Failed_TableView->setObjectName(QString::fromUtf8("Test_Inf_Failed_TableView"));
        Test_Inf_Failed_TableView->setGeometry(QRect(0, 30, 1850, 300));
        Test_Inf_Failed_TableView->setStyleSheet(QString::fromUtf8("border-radius:0px;\n"
"		gridline - radius:0px;"));
        Test_Inf_Failed_TableView->setLineWidth(0);
        Test_Inf_Failed_TableView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        Test_Inf_Failed_TableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        Test_Inf_Failed_TableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        Test_Inf_Failed_TableView->setSelectionMode(QAbstractItemView::NoSelection);
        Test_Inf_Failed_TableView->setShowGrid(false);
        Test_Inf_Failed_TableView->horizontalHeader()->setVisible(false);
        Test_Inf_Failed_TableView->verticalHeader()->setVisible(false);
        Test_Inf_Failed_TableView->verticalHeader()->setDefaultSectionSize(30);
        Test_Inf_Failed_TableView->verticalHeader()->setHighlightSections(false);
        Test_Inf_Failed_ScrollArea->setWidget(Test_Inf_Failed_Widget);
        Test_Inf_Tab->addTab(Failed, QString());
        MainWindowClass->setCentralWidget(centralWidget);
        Test_Inf_Tab->raise();
        label_2->raise();
        label->raise();
        ShangChuan->raise();
        DengLu->raise();
        ShenFen->raise();
        tabWidget->raise();
        CaoZuo->raise();
        label_22->raise();
        groupBox_9->raise();
        groupBox_10->raise();
        groupBox_11->raise();
        Stop->raise();
        Open->raise();
        Reset->raise();
        Count_Bottom->raise();
        Count_Top->raise();

        retranslateUi(MainWindowClass);

        tabWidget->setCurrentIndex(0);
        Test_Inf_Tab->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "VisionTest", nullptr));
        label->setText(QApplication::translate("MainWindowClass", "XXX\347\224\265\346\261\240\346\243\200\346\265\213\347\263\273\347\273\237", nullptr));
        label_2->setText(QString());
        ShangChuan->setText(QApplication::translate("MainWindowClass", "\344\270\212\344\274\240", nullptr));
        DengLu->setTitle(QString());
        label_16->setText(QApplication::translate("MainWindowClass", "\346\223\215\344\275\234\345\221\230\347\231\273\351\231\206", nullptr));
        label_13->setText(QApplication::translate("MainWindowClass", "\347\217\255\345\210\253", nullptr));
        label_14->setText(QApplication::translate("MainWindowClass", "\347\253\231\345\210\253", nullptr));
        label_15->setText(QApplication::translate("MainWindowClass", "\347\272\277\345\210\253", nullptr));
        ShenFen->setTitle(QString());
        label_17->setText(QApplication::translate("MainWindowClass", "\350\272\253\344\273\275   ", nullptr));
        comboBox->setItemText(0, QApplication::translate("MainWindowClass", "\347\256\241\347\220\206\345\221\230", nullptr));
        comboBox->setItemText(1, QApplication::translate("MainWindowClass", "\346\223\215\344\275\234\345\221\230", nullptr));
        comboBox->setItemText(2, QApplication::translate("MainWindowClass", "\346\212\200\346\234\257\344\272\272\345\221\230", nullptr));

        comboBox->setCurrentText(QApplication::translate("MainWindowClass", "\347\256\241\347\220\206\345\221\230", nullptr));
        label_18->setText(QApplication::translate("MainWindowClass", "\345\257\206\347\240\201", nullptr));
        DengLu_2->setText(QApplication::translate("MainWindowClass", "\347\231\273\351\231\206", nullptr));
        label_19->setText(QApplication::translate("MainWindowClass", "\347\256\241\347\220\206\344\272\272\345\221\230\347\231\273\351\231\206", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(TuXiang), QApplication::translate("MainWindowClass", "\345\233\276\345\203\217", nullptr));
        label_21->setText(QApplication::translate("MainWindowClass", "\346\277\200\345\205\211", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(JiGuang), QApplication::translate("MainWindowClass", "\346\277\200\345\205\211", nullptr));
        CaoZuo->setTitle(QString());
        FuCan->setTitle(QString());
        FuWei->setText(QApplication::translate("MainWindowClass", "\345\244\215\344\275\215", nullptr));
        Setting->setText(QApplication::translate("MainWindowClass", "\350\256\276\347\275\256", nullptr));
        KaiZanTing->setTitle(QString());
        KaiShi->setText(QApplication::translate("MainWindowClass", "\345\274\200\345\247\213", nullptr));
        ZanTing->setText(QApplication::translate("MainWindowClass", "\346\232\202\345\201\234", nullptr));
        TingZhi->setText(QApplication::translate("MainWindowClass", "\345\201\234\346\255\242", nullptr));
        radioButton->setText(QApplication::translate("MainWindowClass", "\346\211\213\345\212\250", nullptr));
        radioButton_2->setText(QApplication::translate("MainWindowClass", "\350\207\252\345\212\250", nullptr));
        ChaKan->setText(QApplication::translate("MainWindowClass", "\346\237\245\347\234\213\346\211\200\346\234\211\345\217\202\346\225\260", nullptr));
        Import->setText(QApplication::translate("MainWindowClass", "\345\212\240\350\275\275ROI\345\217\202\346\225\260", nullptr));
        label_22->setText(QApplication::translate("MainWindowClass", "Warning:", nullptr));
        groupBox_9->setTitle(QString());
        label_25->setText(QApplication::translate("MainWindowClass", "Wait", nullptr));
        groupBox_10->setTitle(QString());
        label_23->setText(QApplication::translate("MainWindowClass", "Fault", nullptr));
        groupBox_11->setTitle(QString());
        label_24->setText(QApplication::translate("MainWindowClass", "Run", nullptr));
        Stop->setText(QString());
        Open->setText(QString());
        Reset->setText(QApplication::translate("MainWindowClass", "Reset", nullptr));
        Test_Inf_Tab->setTabText(Test_Inf_Tab->indexOf(Sys), QApplication::translate("MainWindowClass", "\347\263\273\347\273\237\347\212\266\346\200\201", nullptr));
        Test_Inf_Tab->setTabText(Test_Inf_Tab->indexOf(Testing), QApplication::translate("MainWindowClass", "\346\255\243\345\234\250\346\243\200\346\265\213", nullptr));
        Test_Inf_Tab->setTabText(Test_Inf_Tab->indexOf(Failed), QApplication::translate("MainWindowClass", "\346\243\200\346\265\213\346\234\252\351\200\232\350\277\207", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
