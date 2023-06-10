#ifndef SDIPROGRAM_H
#define SDIPROGRAM_H

#include <QMainWindow>
#include <QtWidgets>
#include "docwindownikolaev.h"

namespace Ui {
class SDIProgram;
}

class SDIProgram : public QMainWindow
{
    Q_OBJECT

public:
    SDIProgram(QWidget *pwgt=0):QMainWindow(pwgt)
    {
        QMenu *pmnuFile = new QMenu("&File");
        QMenu *pmnuHelp = new QMenu("&Help");
        DocWindowNikolaev *pdoc = new DocWindowNikolaev;
        pmnuFile->addAction("&Open...",pdoc,SLOT(slotLoad()),QKeySequence("CTRL+O"));
        pmnuFile->addAction("&Save...",pdoc,SLOT(slotSave()),QKeySequence("CTRL+S"));
        pmnuFile->addAction("&SaveAs...",pdoc,SLOT(slotSaveAs()),QKeySequence("CTRL+W"));
        pmnuFile->addAction("&Color",pdoc,SLOT(setColor()),QKeySequence("CTRL+P"));
        pmnuFile->addSeparator();
        pmnuFile->addAction("&Quit",qApp,SLOT(quit()),Qt::Key_Escape);
        pmnuHelp->addAction("&About...",this,SLOT(slotAbout()),Qt::Key_F1);
        menuBar()->addMenu(pmnuFile);
        menuBar()->addMenu(pmnuHelp);
        setCentralWidget(pdoc);
        connect(pdoc,SIGNAL(changeWindowTitle(const QString&)),SLOT(slotChangeWindowTitle(const QString&)));
        statusBar()->showMessage("Ready",2000);
    }

public slots:
        void slotAbout()
        {
            QMessageBox::about(this,"Лабораторная №3","Николаев Алексей ИП-012");
        }

        void slotChangeWindowTitle(const QString& str)
        {
            setWindowTitle(str);
        }
};

#endif // SDIPROGRAM_H
