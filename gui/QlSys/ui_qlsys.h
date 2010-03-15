/********************************************************************************
** Form generated from reading ui file 'qlsys.ui'
**
** Created: Mon Mar 15 14:09:34 2010
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
#include <QtGui/QFormLayout>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QlSysClass
{
public:
    QAction *actionOpen;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QGroupBox *Group1;
    QVBoxLayout *verticalLayout;
    QSpinBox *spinIteration;
    QPushButton *btnRender;
    QPushButton *btnRendClose;
    QFrame *line;
    QGroupBox *Group2;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *chkAutorender;
    QCheckBox *chkLineMode;
    QCheckBox *chkRound;
    QSlider *sldRot;
    QFrame *line_2;
    QGroupBox *formGroupBox;
    QVBoxLayout *verticalLayout_4;
    QPushButton *btnRendPov;
    QPushButton *btnPov;
    QPushButton *btnPovSet;
    QGroupBox *groupBox;
    QFormLayout *formLayout_3;
    QLabel *label_2;
    QLineEdit *txtStrlen;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *txtTria;
    QLineEdit *txtCyl;
    QLabel *label_5;
    QLineEdit *txtFilename;
    QGroupBox *groupBox_2;
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *label_6;
    QLabel *label_7;
    QLineEdit *txtIttime;
    QLineEdit *txtCalctime;
    QLineEdit *txtRendertime;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QlSysClass)
    {
        if (QlSysClass->objectName().isEmpty())
            QlSysClass->setObjectName(QString::fromUtf8("QlSysClass"));
        QlSysClass->resize(551, 519);
        QIcon icon;
        icon.addPixmap(QPixmap(QString::fromUtf8("res/icon.png")), QIcon::Normal, QIcon::Off);
        QlSysClass->setWindowIcon(icon);
        actionOpen = new QAction(QlSysClass);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        centralWidget = new QWidget(QlSysClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_3 = new QVBoxLayout(centralWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setMargin(11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        Group1 = new QGroupBox(centralWidget);
        Group1->setObjectName(QString::fromUtf8("Group1"));
        verticalLayout = new QVBoxLayout(Group1);
        verticalLayout->setSpacing(6);
        verticalLayout->setMargin(11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        spinIteration = new QSpinBox(Group1);
        spinIteration->setObjectName(QString::fromUtf8("spinIteration"));
        spinIteration->setMinimumSize(QSize(100, 0));
        spinIteration->setLayoutDirection(Qt::LeftToRight);
        spinIteration->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        spinIteration->setMaximum(200);

        verticalLayout->addWidget(spinIteration);

        btnRender = new QPushButton(Group1);
        btnRender->setObjectName(QString::fromUtf8("btnRender"));

        verticalLayout->addWidget(btnRender);

        btnRendClose = new QPushButton(Group1);
        btnRendClose->setObjectName(QString::fromUtf8("btnRendClose"));

        verticalLayout->addWidget(btnRendClose);


        horizontalLayout->addWidget(Group1);

        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);

        Group2 = new QGroupBox(centralWidget);
        Group2->setObjectName(QString::fromUtf8("Group2"));
        verticalLayout_2 = new QVBoxLayout(Group2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setMargin(11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        chkAutorender = new QCheckBox(Group2);
        chkAutorender->setObjectName(QString::fromUtf8("chkAutorender"));

        verticalLayout_2->addWidget(chkAutorender);

        chkLineMode = new QCheckBox(Group2);
        chkLineMode->setObjectName(QString::fromUtf8("chkLineMode"));

        verticalLayout_2->addWidget(chkLineMode);

        chkRound = new QCheckBox(Group2);
        chkRound->setObjectName(QString::fromUtf8("chkRound"));

        verticalLayout_2->addWidget(chkRound);

        sldRot = new QSlider(Group2);
        sldRot->setObjectName(QString::fromUtf8("sldRot"));
        sldRot->setMaximum(359);
        sldRot->setOrientation(Qt::Horizontal);
        sldRot->setTickPosition(QSlider::TicksAbove);
        sldRot->setTickInterval(30);

        verticalLayout_2->addWidget(sldRot);


        horizontalLayout->addWidget(Group2);

        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_2);

        formGroupBox = new QGroupBox(centralWidget);
        formGroupBox->setObjectName(QString::fromUtf8("formGroupBox"));
        verticalLayout_4 = new QVBoxLayout(formGroupBox);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setMargin(11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        btnRendPov = new QPushButton(formGroupBox);
        btnRendPov->setObjectName(QString::fromUtf8("btnRendPov"));

        verticalLayout_4->addWidget(btnRendPov);

        btnPov = new QPushButton(formGroupBox);
        btnPov->setObjectName(QString::fromUtf8("btnPov"));

        verticalLayout_4->addWidget(btnPov);

        btnPovSet = new QPushButton(formGroupBox);
        btnPovSet->setObjectName(QString::fromUtf8("btnPovSet"));

        verticalLayout_4->addWidget(btnPovSet);


        horizontalLayout->addWidget(formGroupBox);


        verticalLayout_3->addLayout(horizontalLayout);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        formLayout_3 = new QFormLayout(groupBox);
        formLayout_3->setSpacing(6);
        formLayout_3->setMargin(11);
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        formLayout_3->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, label_2);

        txtStrlen = new QLineEdit(groupBox);
        txtStrlen->setObjectName(QString::fromUtf8("txtStrlen"));
        txtStrlen->setReadOnly(true);

        formLayout_3->setWidget(1, QFormLayout::FieldRole, txtStrlen);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout_3->setWidget(2, QFormLayout::LabelRole, label_3);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout_3->setWidget(3, QFormLayout::LabelRole, label_4);

        txtTria = new QLineEdit(groupBox);
        txtTria->setObjectName(QString::fromUtf8("txtTria"));
        txtTria->setReadOnly(true);

        formLayout_3->setWidget(2, QFormLayout::FieldRole, txtTria);

        txtCyl = new QLineEdit(groupBox);
        txtCyl->setObjectName(QString::fromUtf8("txtCyl"));
        txtCyl->setReadOnly(true);

        formLayout_3->setWidget(3, QFormLayout::FieldRole, txtCyl);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, label_5);

        txtFilename = new QLineEdit(groupBox);
        txtFilename->setObjectName(QString::fromUtf8("txtFilename"));
        txtFilename->setReadOnly(true);

        formLayout_3->setWidget(0, QFormLayout::FieldRole, txtFilename);


        verticalLayout_3->addWidget(groupBox);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        formLayout = new QFormLayout(groupBox_2);
        formLayout->setSpacing(6);
        formLayout->setMargin(11);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_6);

        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_7);

        txtIttime = new QLineEdit(groupBox_2);
        txtIttime->setObjectName(QString::fromUtf8("txtIttime"));

        formLayout->setWidget(0, QFormLayout::FieldRole, txtIttime);

        txtCalctime = new QLineEdit(groupBox_2);
        txtCalctime->setObjectName(QString::fromUtf8("txtCalctime"));

        formLayout->setWidget(1, QFormLayout::FieldRole, txtCalctime);

        txtRendertime = new QLineEdit(groupBox_2);
        txtRendertime->setObjectName(QString::fromUtf8("txtRendertime"));

        formLayout->setWidget(2, QFormLayout::FieldRole, txtRendertime);


        verticalLayout_3->addWidget(groupBox_2);

        QlSysClass->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(QlSysClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QlSysClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QlSysClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QlSysClass->setStatusBar(statusBar);

        mainToolBar->addAction(actionOpen);

        retranslateUi(QlSysClass);

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
        Group1->setTitle(QApplication::translate("QlSysClass", "Iterations:", 0, QApplication::UnicodeUTF8));
        btnRender->setText(QApplication::translate("QlSysClass", "&Render", 0, QApplication::UnicodeUTF8));
        btnRendClose->setText(QApplication::translate("QlSysClass", "&Close Render", 0, QApplication::UnicodeUTF8));
        Group2->setTitle(QApplication::translate("QlSysClass", "Render Options:", 0, QApplication::UnicodeUTF8));
        chkAutorender->setText(QApplication::translate("QlSysClass", "A&uto Render", 0, QApplication::UnicodeUTF8));
        chkLineMode->setText(QApplication::translate("QlSysClass", "Draw simple &lines", 0, QApplication::UnicodeUTF8));
        chkRound->setText(QApplication::translate("QlSysClass", "R&ound Cilinders", 0, QApplication::UnicodeUTF8));
        formGroupBox->setTitle(QApplication::translate("QlSysClass", "POVRay:", 0, QApplication::UnicodeUTF8));
        btnRendPov->setText(QApplication::translate("QlSysClass", "Render in PO&VRay", 0, QApplication::UnicodeUTF8));
        btnPov->setText(QApplication::translate("QlSysClass", "Export to &POV", 0, QApplication::UnicodeUTF8));
        btnPovSet->setText(QApplication::translate("QlSysClass", "POVRay &Settings", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("QlSysClass", "Info:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("QlSysClass", "String Length:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("QlSysClass", "# Triangles:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("QlSysClass", "# Cylinders:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("QlSysClass", "File:", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("QlSysClass", "Timers:", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("QlSysClass", "Iterating:", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("QlSysClass", "Calculating geometry:", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("QlSysClass", "OpenGL Rendering:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QlSysClass: public Ui_QlSysClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QLSYS_H
