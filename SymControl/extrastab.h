#ifndef EXTRASTAB_H
#define EXTRASTAB_H

#include <QWidget>
#include <Config.h>

class ExtrasTab : public QWidget
{
    Q_OBJECT
public:
    explicit ExtrasTab(QString include,QString sim, QWidget *parent = 0);

signals:

public slots:
};

#endif // EXTRASTAB_H
