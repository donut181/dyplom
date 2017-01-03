#ifndef OPTIONSTAB_H
#define OPTIONSTAB_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QFormLayout>

class OptionsTab : public QWidget
{
    Q_OBJECT
public:
    explicit OptionsTab(QString options, QWidget *parent = 0);
    QString getValues();
private:
    QMap<QString,QLineEdit*> m_fields_pointers;
signals:

public slots:
};

#endif // OPTIONSTAB_H
