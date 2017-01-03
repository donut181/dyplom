#ifndef EXTRASTAB_H
#define EXTRASTAB_H

#include <QWidget>
#include <Config.h>
#include <QLabel>
#include <QFormLayout>
#include <QLineEdit>
#include <QCheckBox>
#include <QHBoxLayout>

class ExtrasTab : public QWidget
{
    Q_OBJECT
public:
    explicit ExtrasTab(QString include,QString sim, QWidget *parent = 0);
    QString getValues();
    QString getIncludeField();
    bool isMultithreadOptionChecked();
    bool isSaveOptionChecked();
    QString getSaveString();
private:
    QMap<QString,QLineEdit*> m_fields_pointers;
    QCheckBox *m_multithreadOption;
    QCheckBox *m_saveOption;
    QLineEdit *m_saveLetterField;
    QLineEdit *m_includeField;

    QString m_sim;
signals:

public slots:
};

#endif // EXTRASTAB_H
