#ifndef PLAYWIDGET_H
#define PLAYWIDGET_H

#include "nikolaevgame.h"
#include <QtWidgets>

class PlayWidget : public QWidget
{
    Q_OBJECT
public:
    PlayWidget(NikolaevGame *scene) : QWidget(0)
    {
        QHBoxLayout *qhbl=new QHBoxLayout();
        QPushButton *start_button=new QPushButton("&start");
        QPushButton *stop_button=new QPushButton("&stop");

        qhbl->addWidget(start_button);
        qhbl->addWidget(stop_button);

        connect(start_button,SIGNAL(clicked(bool)),scene,SLOT(startPlay()));
        connect(stop_button,SIGNAL(clicked(bool)),scene,SLOT(stopPlay()));
        setLayout(qhbl);
    }
};

#endif // PLAYWIDGET_H
