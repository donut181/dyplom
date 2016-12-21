/********************************************************************************
** Form generated from reading UI file 'parsedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARSEDIALOG_H
#define UI_PARSEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_ParseDialog
{
public:
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ParseDialog)
    {
        if (ParseDialog->objectName().isEmpty())
            ParseDialog->setObjectName(QStringLiteral("ParseDialog"));
        ParseDialog->resize(400, 300);
        buttonBox = new QDialogButtonBox(ParseDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(ParseDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ParseDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ParseDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ParseDialog);
    } // setupUi

    void retranslateUi(QDialog *ParseDialog)
    {
        ParseDialog->setWindowTitle(QApplication::translate("ParseDialog", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class ParseDialog: public Ui_ParseDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARSEDIALOG_H
