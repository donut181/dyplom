/********************************************************************************
** Form generated from reading UI file 'createsimulatordialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATESIMULATORDIALOG_H
#define UI_CREATESIMULATORDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CreateSimulatorDialog
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *commandLabel;
    QLineEdit *commandLineEdit;
    QLabel *flag1Label;
    QLineEdit *flag1LineEdit;
    QLabel *flag2Label;
    QLineEdit *flag2LineEdit;

    void setupUi(QDialog *CreateSimulatorDialog)
    {
        if (CreateSimulatorDialog->objectName().isEmpty())
            CreateSimulatorDialog->setObjectName(QStringLiteral("CreateSimulatorDialog"));
        CreateSimulatorDialog->resize(383, 295);
        buttonBox = new QDialogButtonBox(CreateSimulatorDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        formLayoutWidget = new QWidget(CreateSimulatorDialog);
        formLayoutWidget->setObjectName(QStringLiteral("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(130, 80, 160, 83));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        commandLabel = new QLabel(formLayoutWidget);
        commandLabel->setObjectName(QStringLiteral("commandLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, commandLabel);

        commandLineEdit = new QLineEdit(formLayoutWidget);
        commandLineEdit->setObjectName(QStringLiteral("commandLineEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, commandLineEdit);

        flag1Label = new QLabel(formLayoutWidget);
        flag1Label->setObjectName(QStringLiteral("flag1Label"));

        formLayout->setWidget(1, QFormLayout::LabelRole, flag1Label);

        flag1LineEdit = new QLineEdit(formLayoutWidget);
        flag1LineEdit->setObjectName(QStringLiteral("flag1LineEdit"));

        formLayout->setWidget(1, QFormLayout::FieldRole, flag1LineEdit);

        flag2Label = new QLabel(formLayoutWidget);
        flag2Label->setObjectName(QStringLiteral("flag2Label"));

        formLayout->setWidget(2, QFormLayout::LabelRole, flag2Label);

        flag2LineEdit = new QLineEdit(formLayoutWidget);
        flag2LineEdit->setObjectName(QStringLiteral("flag2LineEdit"));

        formLayout->setWidget(2, QFormLayout::FieldRole, flag2LineEdit);


        retranslateUi(CreateSimulatorDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), CreateSimulatorDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), CreateSimulatorDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(CreateSimulatorDialog);
    } // setupUi

    void retranslateUi(QDialog *CreateSimulatorDialog)
    {
        CreateSimulatorDialog->setWindowTitle(QApplication::translate("CreateSimulatorDialog", "Dialog", 0));
        commandLabel->setText(QApplication::translate("CreateSimulatorDialog", "Command", 0));
        flag1Label->setText(QApplication::translate("CreateSimulatorDialog", "Flag 1", 0));
        flag2Label->setText(QApplication::translate("CreateSimulatorDialog", "Flag 2", 0));
    } // retranslateUi

};

namespace Ui {
    class CreateSimulatorDialog: public Ui_CreateSimulatorDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATESIMULATORDIALOG_H
