#ifndef INFOWIDGET_H
#define INFOWIDGET_H

#include "nikolaevgame.h"
#include<QtWidgets>
#include<QImage>

class InfoWidget : public QWidget
{
    Q_OBJECT
public:
    InfoWidget(NikolaevGame *scene):QWidget(0)
    {
        QVBoxLayout *qvbl=new QVBoxLayout();
        item_name=new QLabel("Выберите объект...");

        QLabel *x_posl=new QLabel("Позиция по x:");
        x_post=new QLineEdit();
        x_post->setEnabled(false);

        QLabel *y_posl=new QLabel("Позиция по y:");
        y_post=new QLineEdit();
        y_post->setEnabled(false);

        QLabel *x_spl=new QLabel("Скорость по x:");
        x_spt=new QLineEdit();
        x_spt->setEnabled(false);

        QLabel *y_spl=new QLabel("Скорость по y:");
        y_spt=new QLineEdit();
        y_spt->setEnabled(false);

        qvbl->addWidget(item_name);
        qvbl->addWidget(x_posl);
        qvbl->addWidget(x_post);
        qvbl->addWidget(y_posl);
        qvbl->addWidget(y_post);
        qvbl->addWidget(x_spl);
        qvbl->addWidget(x_spt);
        qvbl->addWidget(y_spl);
        qvbl->addWidget(y_spt);

        connect(x_post,SIGNAL(editingFinished()),this,SLOT(setData()));
        connect(y_post,SIGNAL(editingFinished()),this,SLOT(setData()));
        connect(x_spt,SIGNAL(editingFinished()),this,SLOT(setData()));
        connect(y_spt,SIGNAL(editingFinished()),this,SLOT(setData()));

        setLayout(qvbl);
        connect(scene,SIGNAL(sendData(QString)),this,SLOT(getData(QString)));
    }
private:
    QLabel *item_name;
    QLineEdit *x_post;
    QLineEdit *y_post;
    QLineEdit *x_spt;
    QLineEdit *y_spt;

signals:
    void ChangedData(QString data);

public slots:
    void getData(QString str)
    {
        QStringList dataList=str.split("\n");
        item_name->setText(dataList[0]);
        x_post->setText(dataList[1]);
        x_post->setEnabled(true);
        y_post->setText(dataList[2]);
        y_post->setEnabled(true);
        if(dataList.size()!=3)
        {
            x_spt->setText(dataList[3]);
            x_spt->setEnabled(true);
            y_spt->setText(dataList[4]);
            y_spt->setEnabled(true);
        }
        else
        {
            x_spt->clear();
            x_spt->setEnabled(false);
            y_spt->clear();
            y_spt->setEnabled(false);
        }
    }

    void setData()
    {
        QString *data=new QString(item_name->text()+
                                  "\n"+x_post->text()+
                                  "\n"+y_post->text());
        if(y_spt->isEnabled()) data->append(QString("\n"+x_spt->text()+
                                                    "\n"+y_spt->text()));
        emit ChangedData(*data);
    }
};

#endif // INFOWIDGET_H
