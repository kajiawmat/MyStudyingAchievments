#ifndef CREATORWIDGET_H
#define CREATORWIDGET_H

#include<QtWidgets>

#include<QImage>
#include<QLabel>
#include<QHBoxLayout>
#include<QPushButton>


class CreatorWidget: public QDialogButtonBox
{
    Q_OBJECT
public:
    CreatorWidget(QGraphicsScene *scene, int len=150):QDialogButtonBox(0)
    {
        int side=(5*len)/6;
        QImage Img;
        QString str[4]={"Ellipse","Car","Wall0","Wall1"};
        QPushButton *ql=new QPushButton();
        QPixmap pixEll(60,60);
        QPainter pixPaint(&pixEll);
        pixPaint.setRenderHint(QPainter::Antialiasing,true);
        pixPaint.setPen(QPen(Qt::white,4,Qt::SolidLine));
        pixPaint.setBrush(QBrush(Qt::white,Qt::SolidPattern));
        pixPaint.drawRect(QRect(0,0,60,60));
        pixPaint.setPen(QPen(Qt::black,4,Qt::SolidLine));
        pixPaint.setBrush(QBrush(Qt::black,Qt::Dense5Pattern));
        pixPaint.drawEllipse(QRect(5,5,50,50));
        pixPaint.end();
        ql->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
        ql->setIcon(QIcon(pixEll));
        ql->setIconSize(QSize(side,side));
        ql->setObjectName(QString::number(0));
        addButton(ql,QDialogButtonBox::ActionRole);
        for(int i=1;i<4;i++)
        {
            ql=new QPushButton();
            Img.load(str[i]+".png");
            if(Img.width()>side || Img.height()>side) Img=Img.scaled(side,side,Qt::KeepAspectRatio);
            ql->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
            ql->setIcon(QIcon(QPixmap::fromImage(Img)));
            ql->setIconSize(QSize(side,side));
            ql->setObjectName(QString::number(i));
            addButton(ql,QDialogButtonBox::ActionRole);
        }
        connect(this,SIGNAL(clicked(QAbstractButton*)),scene,SLOT(CreateFigure(QAbstractButton*)));
    }

};

#endif // CREATORWIDGET_H
