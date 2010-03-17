/********************************************************************************
** Form generated from reading ui file 'qlsys.ui'
**
** Created: Wed Mar 17 15:23:01 2010
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_QLSYS_H
#define UI_QLSYS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QFormLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QlSysClass
{
public:
    QAction *actionOpen;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_11;
    QSpinBox *spinIteration;
    QTabWidget *tabWidget;
    QWidget *tab;
    QFormLayout *formLayout_2;
    QLabel *label_5;
    QLineEdit *txtFilename;
    QLabel *label_2;
    QLineEdit *txtStrlen;
    QLabel *label_3;
    QLineEdit *txtTria;
    QLabel *label_4;
    QLineEdit *txtCyl;
    QWidget *tab_2;
    QFormLayout *formLayout_3;
    QLabel *label;
    QLineEdit *txtIttime;
    QLabel *label_6;
    QLineEdit *txtCalctime;
    QLabel *label_7;
    QLineEdit *txtRendertime;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *comboBox;
    QPushButton *btnRender;
    QPushButton *btnRendClose;
    QSpacerItem *horizontalSpacer;
    QCheckBox *chkAutorender;
    QCheckBox *chkLineMode;
    QCheckBox *chkRound;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_8;
    QSlider *sldRotY;
    QPushButton *btnRotY;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_9;
    QSlider *sldRotZ;
    QPushButton *btnRotZ;
    QSpacerItem *verticalSpacer_2;
    QWidget *tab_4;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *btnRendPov;
    QPushButton *btnPov;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_10;
    QLineEdit *txtPovSettings;
    QSpacerItem *verticalSpacer;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QlSysClass)
    {
        if (QlSysClass->objectName().isEmpty())
            QlSysClass->setObjectName(QString::fromUtf8("QlSysClass"));
        QlSysClass->resize(350, 353);
        QIcon icon;
        icon.addPixmap(QPixmap(QString::fromUtf8("res/icon.png")), QIcon::Normal, QIcon::Off);
        QlSysClass->setWindowIcon(icon);
        actionOpen = new QAction(QlSysClass);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        centralWidget = new QWidget(QlSysClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setMargin(11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout->addWidget(label_11);

        spinIteration = new QSpinBox(centralWidget);
        spinIteration->setObjectName(QString::fromUtf8("spinIteration"));
        spinIteration->setMinimumSize(QSize(100, 0));
        spinIteration->setLayoutDirection(Qt::LeftToRight);
        spinIteration->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        spinIteration->setMaximum(200);

        horizontalLayout->addWidget(spinIteration);


        verticalLayout->addLayout(horizontalLayout);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        formLayout_2 = new QFormLayout(tab);
        formLayout_2->setSpacing(6);
        formLayout_2->setMargin(11);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        label_5 = new QLabel(tab);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_5);

        txtFilename = new QLineEdit(tab);
        txtFilename->setObjectName(QString::fromUtf8("txtFilename"));
        txtFilename->setReadOnly(true);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, txtFilename);

        label_2 = new QLabel(tab);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_2);

        txtStrlen = new QLineEdit(tab);
        txtStrlen->setObjectName(QString::fromUtf8("txtStrlen"));
        txtStrlen->setReadOnly(true);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, txtStrlen);

        label_3 = new QLabel(tab);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_3);

        txtTria = new QLineEdit(tab);
        txtTria->setObjectName(QString::fromUtf8("txtTria"));
        txtTria->setReadOnly(true);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, txtTria);

        label_4 = new QLabel(tab);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, label_4);

        txtCyl = new QLineEdit(tab);
        txtCyl->setObjectName(QString::fromUtf8("txtCyl"));
        txtCyl->setReadOnly(true);

        formLayout_2->setWidget(3, QFormLayout::FieldRole, txtCyl);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        formLayout_3 = new QFormLayout(tab_2);
        formLayout_3->setSpacing(6);
        formLayout_3->setMargin(11);
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        label = new QLabel(tab_2);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, label);

        txtIttime = new QLineEdit(tab_2);
        txtIttime->setObjectName(QString::fromUtf8("txtIttime"));

        formLayout_3->setWidget(0, QFormLayout::FieldRole, txtIttime);

        label_6 = new QLabel(tab_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, label_6);

        txtCalctime = new QLineEdit(tab_2);
        txtCalctime->setObjectName(QString::fromUtf8("txtCalctime"));

        formLayout_3->setWidget(1, QFormLayout::FieldRole, txtCalctime);

        label_7 = new QLabel(tab_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout_3->setWidget(2, QFormLayout::LabelRole, label_7);

        txtRendertime = new QLineEdit(tab_2);
        txtRendertime->setObjectName(QString::fromUtf8("txtRendertime"));

        formLayout_3->setWidget(2, QFormLayout::FieldRole, txtRendertime);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        verticalLayout_3 = new QVBoxLayout(tab_3);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setMargin(11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        comboBox = new QComboBox(tab_3);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout_2->addWidget(comboBox);

        btnRender = new QPushButton(tab_3);
        btnRender->setObjectName(QString::fromUtf8("btnRender"));

        horizontalLayout_2->addWidget(btnRender);

        btnRendClose = new QPushButton(tab_3);
        btnRendClose->setObjectName(QString::fromUtf8("btnRendClose"));

        horizontalLayout_2->addWidget(btnRendClose);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout_3->addLayout(horizontalLayout_2);

        chkAutorender = new QCheckBox(tab_3);
        chkAutorender->setObjectName(QString::fromUtf8("chkAutorender"));

        verticalLayout_3->addWidget(chkAutorender);

        chkLineMode = new QCheckBox(tab_3);
        chkLineMode->setObjectName(QString::fromUtf8("chkLineMode"));

        verticalLayout_3->addWidget(chkLineMode);

        chkRound = new QCheckBox(tab_3);
        chkRound->setObjectName(QString::fromUtf8("chkRound"));

        verticalLayout_3->addWidget(chkRound);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_8 = new QLabel(tab_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_3->addWidget(label_8);

        sldRotY = new QSlider(tab_3);
        sldRotY->setObjectName(QString::fromUtf8("sldRotY"));
        sldRotY->setMaximum(359);
        sldRotY->setOrientation(Qt::Horizontal);
        sldRotY->setTickPosition(QSlider::TicksAbove);
        sldRotY->setTickInterval(30);

        horizontalLayout_3->addWidget(sldRotY);

        btnRotY = new QPushButton(tab_3);
        btnRotY->setObjectName(QString::fromUtf8("btnRotY"));

        horizontalLayout_3->addWidget(btnRotY);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_9 = new QLabel(tab_3);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_4->addWidget(label_9);

        sldRotZ = new QSlider(tab_3);
        sldRotZ->setObjectName(QString::fromUtf8("sldRotZ"));
        sldRotZ->setMaximum(359);
        sldRotZ->setOrientation(Qt::Horizontal);
        sldRotZ->setTickPosition(QSlider::TicksAbove);
        sldRotZ->setTickInterval(30);

        horizontalLayout_4->addWidget(sldRotZ);

        btnRotZ = new QPushButton(tab_3);
        btnRotZ->setObjectName(QString::fromUtf8("btnRotZ"));

        horizontalLayout_4->addWidget(btnRotZ);


        verticalLayout_3->addLayout(horizontalLayout_4);

        verticalSpacer_2 = new QSpacerItem(20, 101, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        verticalLayout_2 = new QVBoxLayout(tab_4);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setMargin(11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        btnRendPov = new QPushButton(tab_4);
        btnRendPov->setObjectName(QString::fromUtf8("btnRendPov"));

        horizontalLayout_6->addWidget(btnRendPov);

        btnPov = new QPushButton(tab_4);
        btnPov->setObjectName(QString::fromUtf8("btnPov"));

        horizontalLayout_6->addWidget(btnPov);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_10 = new QLabel(tab_4);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_5->addWidget(label_10);

        txtPovSettings = new QLineEdit(tab_4);
        txtPovSettings->setObjectName(QString::fromUtf8("txtPovSettings"));

        horizontalLayout_5->addWidget(txtPovSettings);


        verticalLayout_2->addLayout(horizontalLayout_5);

        verticalSpacer = new QSpacerItem(20, 123, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        tabWidget->addTab(tab_4, QString());

        verticalLayout->addWidget(tabWidget);

        QlSysClass->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(QlSysClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QlSysClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QlSysClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QlSysClass->setStatusBar(statusBar);

        mainToolBar->addAction(actionOpen);

        retranslateUi(QlSysClass);

        tabWidget->setCurrentIndex(3);
        comboBox->setCurrentIndex(5);


        QMetaObject::connectSlotsByName(QlSysClass);
    } // setupUi

    void retranslateUi(QMainWindow *QlSysClass)
    {
        QlSysClass->setWindowTitle(QApplication::translate("QlSysClass", "QlSys", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("QlSysClass", "Open", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionOpen->setToolTip(QApplication::translate("QlSysClass", "Open file", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionOpen->setShortcut(QApplication::translate("QlSysClass", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("QlSysClass", "Iterations:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("QlSysClass", "File:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("QlSysClass", "String Length:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("QlSysClass", "# Triangles:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("QlSysClass", "# Cylinders:", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("QlSysClass", "&Info", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("QlSysClass", "Iterating:", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("QlSysClass", "Calculating geometry:", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("QlSysClass", "OpenGL Rendering:", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("QlSysClass", "&Timers", 0, QApplication::UnicodeUTF8));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("QlSysClass", "160x120", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QlSysClass", "176x144", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QlSysClass", "320x240", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QlSysClass", "400x300", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QlSysClass", "640x480", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QlSysClass", "800x600", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QlSysClass", "1024x768", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QlSysClass", "1280x1024", 0, QApplication::UnicodeUTF8)
        );
        btnRender->setText(QApplication::translate("QlSysClass", "&Render", 0, QApplication::UnicodeUTF8));
        btnRendClose->setText(QApplication::translate("QlSysClass", "&Close Render", 0, QApplication::UnicodeUTF8));
        chkAutorender->setText(QApplication::translate("QlSysClass", "A&uto Render", 0, QApplication::UnicodeUTF8));
        chkLineMode->setText(QApplication::translate("QlSysClass", "Draw simple &lines", 0, QApplication::UnicodeUTF8));
        chkRound->setText(QApplication::translate("QlSysClass", "R&ound Cilinders", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("QlSysClass", "Y-Axis:", 0, QApplication::UnicodeUTF8));
        btnRotY->setText(QApplication::translate("QlSysClass", "Rotate", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("QlSysClass", "Z-Axis:", 0, QApplication::UnicodeUTF8));
        btnRotZ->setText(QApplication::translate("QlSysClass", "Rotate", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("QlSysClass", "&OpenGL", 0, QApplication::UnicodeUTF8));
        btnRendPov->setText(QApplication::translate("QlSysClass", "Render in PO&VRay", 0, QApplication::UnicodeUTF8));
        btnPov->setText(QApplication::translate("QlSysClass", "Export to &POV", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("QlSysClass", "Options:", 0, QApplication::UnicodeUTF8));
        txtPovSettings->setText(QApplication::translate("QlSysClass", "+W800 +H600 +Q11 +A0.1", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("QlSysClass", "&PovRay", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QlSysClass: public Ui_QlSysClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QLSYS_H
