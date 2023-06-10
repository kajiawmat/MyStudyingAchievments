#ifndef DOCWINDOWNIKOLAEV_H
#define DOCWINDOWNIKOLAEV_H

#include<QTextEdit>

class DocWindowNikolaev: public QTextEdit
{
    Q_OBJECT
private:
    QString m_strFileName;
public:
    DocWindowNikolaev(QWidget *pwgt=0);
signals:
    void changeWindowTitle(const QString&);

public slots:
    void slotLoad();
    void slotSave();
    void slotSaveAs();
    void setColor();
};

#endif // DOCWINDOWNIKOLAEV_H
