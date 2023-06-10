#include "nikolaevgame.h"
#include "infowidget.h"
#include "creatorwidget.h"
#include "playwidget.h"
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QPainter>
#include <QtWidgets>
#include <QImage>
#include <cmath>

QString names[4]={"Ellipse","Car","Wall0","Wall1"};
const int GameWidth=600;
const int GameHeigth=400;
const int InfoWidth=300;
const int InfoHeigth=GameHeigth;
const int CreatorWidth=GameWidth;
const int CreatorHeigth=200;
const int PlayWidth=InfoWidth;
const int PlayHeigth=CreatorHeigth;
const int WallWidth=40;
const int WallHeigth=40;
const int GameSceneWidth=GameWidth+InfoWidth;
const int GameSceneHeigth=GameHeigth+CreatorHeigth;
const int EllipseWidth=40;
const int EllipseHeigth=40;

int CarWidth;
int CarHeigth;

const double Min_Rand=-4;
const double Max_Rand=4;

QRandomGenerator *gen=new QRandomGenerator();

NikolaevGame::NikolaevGame(QObject *parent) : QGraphicsScene(parent)
{
    setSceneRect(QRectF(0,0,GameSceneWidth,GameSceneHeigth));
    QGraphicsItem *item;
    CreateWalls("Wall0",0,WallHeigth,GameWidth,GameHeigth-WallHeigth,WallWidth,WallHeigth);
    CreateWalls("Wall1",0,0,GameWidth,GameHeigth-WallHeigth,WallWidth,WallHeigth);

    CreatorWidget *cr=new CreatorWidget(this,CreatorWidth/4);
    cr->resize(CreatorWidth,CreatorHeigth);
    item=addWidget(cr);
    item->setPos(0,GameHeigth);

    InfoWidget *inf=new InfoWidget(this);
    inf->resize(InfoWidth,InfoHeigth);
    item=addWidget(inf);
    item->setPos(GameWidth,0);
    connect(inf,SIGNAL(ChangedData(QString)),this,SLOT(setData(QString)));

    PlayWidget *pl=new PlayWidget(this);
    pl->resize(PlayWidth,PlayHeigth);
    item=addWidget(pl);
    item->setPos(GameWidth,GameHeigth);

    Playing=new QTimer();
    connect(Playing,SIGNAL(timeout()),this,SLOT(moveBalls()));

    QPixmap car("Car.png");
    CarWidth=car.width();
    CarHeigth=car.height();

    //honk=new QSound("CarHonk.mp3");

}

void NikolaevGame::CreateFigure(QAbstractButton* push)
{
    int i=(push->objectName()).toInt();
    QGraphicsItem *item;
    switch (i) {
    case 0:
        item=addEllipse(QRectF(0,0,40,40),QPen(Qt::black,3,Qt::SolidLine),QBrush(Qt::black,Qt::Dense5Pattern));
        break;
    case 1:
        item=addPixmap(QPixmap("Car.png"));
        break;
    case 2:
        item=addPixmap(QPixmap("Wall0.png"));
        break;
    case 3:
        item=addPixmap(QPixmap("Wall1.png"));
        break;
    }
    item->setPos(GameWidth/2,GameHeigth/2);
    item->setFlags(QGraphicsItem::ItemIsSelectable|QGraphicsItem::ItemIsMovable);
    item->setData(0,names[i]);
    item->setData(1,GameWidth/2);
    item->setData(2,GameHeigth/2);
    if(i==0)
    {
        item->setData(3,(gen->generateDouble()*(Max_Rand-Min_Rand+1))+Min_Rand);
        item->setData(4,(gen->generateDouble()*(Max_Rand-Min_Rand+1))+Min_Rand);
        Balls.push_back(item);
    }
    connect(this,SIGNAL(selectionChanged()),SLOT(getData()));
}

void NikolaevGame::CreateWalls(QString name, int x, int y, int w, int h, int side_x, int side_y)
{
    QPixmap *wall=new QPixmap(name+".png");
    for(int i=0;i<=(w-side_x);i+=side_x)
    {
        AddWall(name,wall,x+i,y);
        AddWall(name,wall,x+i,y+h-side_y);
    }
    for(int i=1;i<=(h-side_y);i+=side_y)
    {
        AddWall(name,wall,x,y+i);
        AddWall(name,wall,x+w-side_x,y+i);
    }
}

void NikolaevGame::AddWall(QString name, QPixmap *wall, int x, int y)
{
    QGraphicsItem* item;
    item=addPixmap(*wall);
    item->setPos(x,y);
    item->setFlags(QGraphicsItem::ItemIsSelectable);
    item->setData(0,name);
    item->setData(1,x);
    item->setData(2,y);
    if(name==names[3]) item->setZValue(1);
    connect(this,SIGNAL(selectionChanged()),SLOT(getData()));
}

void NikolaevGame::getData()
{
    if(QGraphicsScene::selectedItems().isEmpty()) return;
    SelectedItem=QGraphicsScene::selectedItems().first();
    QString *Data=new QString(SelectedItem->data(0).toString()+"\n"+
                              SelectedItem->data(1).toString()+"\n"+
                              SelectedItem->data(2).toString());
    if(SelectedItem->data(0)=="Ellipse") Data->append(QString("\n"+SelectedItem->data(3).toString()+
                                                              "\n"+SelectedItem->data(4).toString()));
    emit sendData(*Data);
}

void NikolaevGame::setData(QString str)
{
    QStringList dataList=str.split("\n");
    for(int i=1;i<3;i++) SelectedItem->setData(i,dataList[i].toDouble());
    for(int i=3;i<dataList.size();i++) SelectedItem->setData(i,dataList[i].toDouble());
    SelectedItem->setPos(dataList[1].toDouble(),dataList[2].toDouble());
}

void NikolaevGame::moveBalls()
{
    QGraphicsItem* intersect;
    foreach(QGraphicsItem *item,Balls)
    {
        if(QGraphicsScene::collidingItems((item),Qt::ContainsItemShape).isEmpty())
        {
            QList<QGraphicsItem*> list=QGraphicsScene::collidingItems((item),Qt::IntersectsItemShape);
            if(list.isEmpty()!=true)
            {
                for(int i=0;i<list.size();i++)
                {
                    intersect=list[i];
                    if(intersect->data(0)!=names[3]) break;
                }
                if(intersect->data(0)!=names[3]) ChangeVectorSpeed(item,intersect);
            }
            item->setData(1,item->data(1).toDouble()+item->data(3).toDouble());
            item->setData(2,item->data(2).toDouble()+item->data(4).toDouble());
            item->setPos(item->data(1).toDouble(),
                         item->data(2).toDouble());
            if(item==SelectedItem) getData();
        }
    }
}

void NikolaevGame::ChangeVectorSpeed(QGraphicsItem *item, QGraphicsItem *intersect)
{
    double x0=item->data(1).toDouble();
    double y0=item->data(2).toDouble();
    double x1=intersect->data(1).toDouble();
    double y1=intersect->data(2).toDouble();
    double vx0=item->data(3).toDouble();
    double vy0=item->data(4).toDouble();
    if(intersect->data(0)==names[0])
    {
        double dif_x=x0-x1,dif_y=y0-y1;
        double vx1=intersect->data(3).toDouble();
        double vy1=intersect->data(4).toDouble();
        item->setData(3,vx0-((vx0-vx1)*dif_x+(vy0-vy1)*dif_y)/(dif_x*dif_x+dif_y*dif_y)*dif_x);
        item->setData(4,vy0-((vx0-vx1)*dif_x+(vy0-vy1)*dif_y)/(dif_x*dif_x+dif_y*dif_y)*dif_y);
        intersect->setData(3,vx1+((vx0-vx1)*dif_x+(vy0-vy1)*dif_y)/(dif_x*dif_x+dif_y*dif_y)*dif_x);
        intersect->setData(4,vy1+((vx0-vx1)*dif_x+(vy0-vy1)*dif_y)/(dif_x*dif_x+dif_y*dif_y)*dif_y);
    }
    else if(intersect->data(0)!=names[1])
    {
        x0+=EllipseWidth/2;
        y0+=EllipseHeigth/2;
        if(x0>x1 && x0<x1+WallWidth)
        {
            item->setData(4,-vy0);
        }
        else if(y0>y1 && y0<y1+WallHeigth)
        {
            item->setData(3,-vx0);
        }
        else
        {
            item->setData(3,-vx0);
            item->setData(4,-vy0);
        }

    }
    else
    {
        x0+=EllipseWidth/2;
        y0+=EllipseHeigth/2;
        if(x0>x1 && x0<x1+CarWidth)
        {
            item->setData(4,-vy0);
        }
        else if(y0>y1 && y0<y1+CarHeigth)
        {
            item->setData(3,-vx0);
        }
        else
        {
            item->setData(3,-vx0);
            item->setData(4,-vy0);
        }
    }
   /* else if(intersect->data(0)!=names[3])
    {
        item->setData(3,0);
        item->setData(4,0);
    }*/
}

void NikolaevGame::startPlay()
{
    Playing->start(20);
}

void NikolaevGame::stopPlay()
{
    Playing->stop();
}

void NikolaevGame::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseReleaseEvent(event);
    if(SelectedItem!=NULL)
    {
        SelectedItem->setData(1,SelectedItem->pos().rx());
        SelectedItem->setData(2,SelectedItem->pos().ry());
    }
    getData();
}

void NikolaevGame::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);
    if(SelectedItem!=NULL)
    {
        SelectedItem->setData(1,SelectedItem->pos().rx());
        SelectedItem->setData(2,SelectedItem->pos().ry());
    }
    getData();
}

void NikolaevGame::keyPressEvent(QKeyEvent *event)
{
    QGraphicsScene::keyPressEvent(event);
    if(event->key()==Qt::Key_Delete)
    {
        delete SelectedItem;
    }
    switch (event->key())
    {
    case Qt::Key_Delete:
        removeItem(SelectedItem);
        break;
    case Qt::Key_P:
        startPlay();
        break;
    case Qt::Key_S:
        stopPlay();
        break;
    default:
        break;
    }
    getData();
}
