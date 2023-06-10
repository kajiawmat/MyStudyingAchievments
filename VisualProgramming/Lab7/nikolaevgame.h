#ifndef NIKOLAEVGAME_H
#define NIKOLAEVGAME_H

#include<QtWidgets>
#include<QGraphicsItem>
#include<QHBoxLayout>
#include<QTime>

class NikolaevGame : public QGraphicsScene
{
    Q_OBJECT
public:
    NikolaevGame(QObject *parent=0);

signals:
    void sendData(QString str);
public slots:
    void CreateFigure(QAbstractButton *push);
    void getData();
    void setData(QString str);
    void moveBalls();
    void startPlay();
    void stopPlay();
private:
    void CreateWalls(QString name, int x, int y, int w, int h, int side_x, int side_y);
    void AddWall(QString name, QPixmap *wall, int x, int y);
    void ChangeVectorSpeed(QGraphicsItem* item, QGraphicsItem* intersect);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    QTimer *Playing;
    QList<QGraphicsItem *> Balls;
    QGraphicsItem* SelectedItem;
};

#endif // NIKOLAEVGAME_H
