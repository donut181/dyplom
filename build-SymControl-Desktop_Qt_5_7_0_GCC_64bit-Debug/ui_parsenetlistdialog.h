/********************************************************************************
** Form generated from reading UI file 'parsenetlistdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARSENETLISTDIALOG_H
#define UI_PARSENETLISTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_parseNetlistDialog
{
public:
    QDialogButtonBox *buttonBox;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *tab_2;
    QWidget *tab_3;

    void setupUi(QDialog *parseNetlistDialog)
    {
        if (parseNetlistDialog->objectName().isEmpty())
            parseNetlistDialog->setObjectName(QStringLiteral("parseNetlistDialog"));
        parseNetlistDialog->resize(400, 300);
        buttonBox = new QDialogButtonBox(parseNetlistDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        tabWidget = new QTabWidget(parseNetlistDialog);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(40, 20, 221, 31));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        tabWidget->addTab(tab_3, QString());

        retranslateUi(parseNetlistDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), parseNetlistDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), parseNetlistDialog, SLOT(reject()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(parseNetlistDialog);
    } // setupUi

    void retranslateUi(QDialog *parseNetlistDialog)
    {
        parseNetlistDialog->setWindowTitle(QApplication::translate("parseNetlistDialog", "Dialog", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("parseNetlistDialog", "Tab 1", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("parseNetlistDialog", "Strona", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("parseNetlistDialog", "Strona", 0));
    } // retranslateUi

};

namespace Ui {
    class parseNetlistDialog: public Ui_parseNetlistDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARSENETLISTDIALOG_H
