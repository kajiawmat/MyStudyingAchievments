#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->centralWidget->setLayout(ui->horizontalLayout_2);
    ui->saveJournal->setEnabled(false);
    ui->changeJournal->setEnabled(false);
    ui->menu_2->setEnabled(false);
    ui->menu_3->setEnabled(false);
    connect(ui->createJournal,SIGNAL(triggered(bool)),this,SLOT(on_menubar_createjournal_clicked()));
    connect(ui->saveJournal,SIGNAL(triggered(bool)),this,SLOT(on_menubar_savejournal_clicked()));
    connect(ui->loadJournal,SIGNAL(triggered(bool)),this,SLOT(on_menubar_loadjournal_clicked()));
    connect(ui->changeJournal,SIGNAL(triggered(bool)),this,SLOT(on_menubar_changejournal_clicked()));
    connect(ui->addSchoolBoy,SIGNAL(triggered(bool)),this,SLOT(on_menubar_addschoolboy_clicked()));
    connect(ui->delSchoolBoys,SIGNAL(triggered(bool)),this,SLOT(on_menubar_delschoolboy_clicked()));
    connect(ui->changeSchoolBoy,SIGNAL(triggered(bool)),this,SLOT(on_menubar_changeschoolboy_clicked()));
    //connect(ui->resSchoolBoys,SIGNAL(triggered(bool)),this,SLOT(on_menubar_resultschoolboy_clicked()));
    connect(ui->addSubject,SIGNAL(triggered(bool)),this,SLOT(on_menubar_addsubject_clicked()));
    connect(ui->delSubjects,SIGNAL(triggered(bool)),this,SLOT(on_menubar_delsubject_clicked()));
    //connect(ui->resSubject,SIGNAL(triggered(bool)),this,SLOT(on_menubar_resultsubject_clicked()));
    connect(ui->changeSubjectTimePeriod,SIGNAL(triggered(bool)),this,SLOT(on_menubar_changetimeperiod_clicked()));
    connect(ui->Help,SIGNAL(triggered(bool)),this,SLOT(on_menubar_help_clicked()));

    ui->scrollAreaWidgetContents->setLayout(ui->scroollLayout);
    ui->scroollLayout->setSpacing(0);
    this->setWindowTitle("Откройте журнал начальных классов");
    ui->labelState->setText("1/4 четверть");
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    CurrentPage--;
    ui->labelState->setText(QString::number(CurrentPage+1)+"/4 четверть");
    if(CurrentPage==0) ui->pushButton->setEnabled(false);
    else ui->pushButton->setEnabled(true);
    //ui->pushButton_2->setEnabled(true);
    emit changePage(CurrentPage);
}

void MainWindow::on_pushButton_2_clicked()
{
    CurrentPage++;
    if(CurrentPage>3) CurrentPage=3;
    ui->labelState->setText(QString::number(CurrentPage+1)+"/4 четверть");
    if(CurrentPage==3) ui->pushButton_2->setEnabled(false);
    ui->pushButton_2->setEnabled(true);
    ui->pushButton->setEnabled(true);
    emit changePage(CurrentPage);
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    delete ui->tabWidget->widget(index);
}

void MainWindow::on_menubar_loadjournal_clicked()
{
    QString dirName=QFileDialog::getExistingDirectory(0, "Открыть директорию", QDir::currentPath());
    if(!QFile(dirName+"/init.txt").exists())
    {
        qDebug("Это не журнал");
        return;
    }
    CurrentPath=dirName;
    QFileInfoList dirContent = QDir(dirName).entryInfoList(QStringList()<< "*",QDir::Dirs);
    while(!ui->scroollLayout->isEmpty()) delete ui->scroollLayout->itemAt(0);
    QFile *file=new QFile(dirName+"/init.txt");
    file->open(QIODevice::ReadOnly | QIODevice::Text);
    QStringList data=QString(file->readAll()).split("\n");
    file->close();
    Name=data[0];
    Teacher=data[1];
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<2;j++)
        {
            QuartersDates[i][j]=data[i*2+j+2];
        }
    }
    DataBase *db=new DataBase(CurrentPath);
    db->connectToDB();

    model = new QSqlTableModel;
    model->setTable("SchoolBoy");
    model->select();
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    SchoolBoysView=new QTableView();
    SchoolBoysView->setModel(model); //NoEdit in Window
    SchoolBoys.clear();
    for(int i=0;i<model->rowCount();i++)
    {
        SchoolBoys.append((model->data(model->index(i,0))).toString());
    }
    for(int i=2;i<dirContent.size();i++)
    {
        qDebug(dirContent[i].fileName().toUtf8());
        myPushButton* butt=new myPushButton(SchoolBoys,QuartersDates,CurrentPath,dirContent[i].fileName());
        connect(butt,SIGNAL(sentTable(MyTableWidget*,QString)),this,SLOT(GetTable(MyTableWidget*,QString)));
        butt->setMinimumHeight(30);
        ui->scroollLayout->addWidget(butt);
        Buttons.push_back(butt);
    }
    ui->saveJournal->setEnabled(true);
    ui->changeJournal->setEnabled(true);
    ui->menu_2->setEnabled(true);
    ui->menu_3->setEnabled(true);
    ui->changeSubjectTimePeriod->setEnabled(false);
    this->setWindowTitle("Журнал класса "+Name);
    while(ui->tabWidget->count()!=0)
    {
        ui->tabWidget->removeTab(0);
    }
    CurrentPage=0;
    ui->labelState->setText("1/4 четверть");
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
}

void MainWindow::on_menubar_savejournal_clicked()
{
    int n=QMessageBox::question(this,"Сохранение","Вы уверены, что хотите сохранить изменения?",QMessageBox::Yes | QMessageBox::No);
    if(n==QMessageBox::Yes)
    {
        for(int i=0;i<Buttons.size();i++)
        {
            Buttons[i]->WriteQuarterFile();
            Buttons[i]->WriteYearFile();
        }
        model->submitAll();
        for(int i=0;i<ui->tabWidget->count();i++)
        {
            if(ui->tabWidget->tabText(i)[ui->tabWidget->tabText(i).size()-1]=='*')
            {
                ui->tabWidget->setTabText(i,ui->tabWidget->tabText(i).remove(ui->tabWidget->tabText(i).size()-1,1));
            }
        }
    }
}

void MainWindow::on_menubar_changejournal_clicked()
{
    structJournalWindow *win=new structJournalWindow(Name,Teacher);
    win->setWindowTitle("Редактирование журнала");
    win->setModal(true);
    win->show();
    connect(win,SIGNAL(sentData(QString*)),this, SLOT(changeJournal(QString*)));
}

void MainWindow::on_menubar_createjournal_clicked()
{
    structJournalWindow *win=new structJournalWindow();
    win->setWindowTitle("Создание журнала");
    win->setModal(true);
    win->show();
    connect(win,SIGNAL(sentData(QString*)),this, SLOT(createJournal(QString*)));
}

void MainWindow::on_menubar_addschoolboy_clicked()
{
    addSchoolBoyWindow *win=new addSchoolBoyWindow();
    win->setWindowTitle("Добавление ученика");
    win->setModal(true);
    connect(win,SIGNAL(sentData(QString*)),this,SLOT(addSchoolBoy(QString*)));
    win->show();
}

void MainWindow::on_menubar_delschoolboy_clicked()
{
    delWindow *win=new delWindow(1,&SchoolBoys);
    win->setModal(true);
    win->setWindowTitle("Удаление учеников");
    connect(win,SIGNAL(sentData(QVector<int>)),this,SLOT(delSchoolBoy(QVector<int>)));
    win->show();
}

void MainWindow::on_menubar_changeschoolboy_clicked()
{
    schoolBoysWindow *win=new schoolBoysWindow(SchoolBoysView,model);
    win->setWindowTitle("Просмотр/Редактирование инормации об учениках");
    win->setModal(true);
    win->show();
}

void MainWindow::on_menubar_addsubject_clicked()
{
    addSubjectWindow *win=new addSubjectWindow();
    win->setModal(true);
    win->setWindowTitle("Добавление предмета");
    connect(win,SIGNAL(sentData(QString*)),this,SLOT(addSubject(QString*)));
    win->show();
    ui->changeSubjectTimePeriod->setEnabled(true);
}

void MainWindow::on_menubar_delsubject_clicked()
{
    QVector<QString> buts;
    for(int i=0;i<Buttons.size();i++) buts.push_back(Buttons[i]->text());
    delWindow *win=new delWindow(0,&buts);
    win->setWindowTitle("Удаление предметоа");
    win->setModal(true);
    connect(win,SIGNAL(sentData(QVector<int>)),this,SLOT(delSubject(QVector<int>)));
    win->show();
}

void MainWindow::on_menubar_changetimeperiod_clicked()
{
    QString cur="";
    QVector<QString> Sub;
    for(int i=0;i<Buttons.size();i++) Sub.push_back(Buttons[i]->text());
    if(ui->tabWidget->count()!=0) cur=ui->tabWidget->tabText(ui->tabWidget->currentIndex());
    changeTimePeriodWindow *win=new changeTimePeriodWindow(Sub,cur);
    win->setModal(true);
    win->setWindowTitle("Изменение даты на промежутке");
    win->show();
}

void MainWindow::on_menubar_help_clicked()
{
    helpWindow *help=new helpWindow("://Help/index.html");
    help->setWindowTitle("Помощь");
    help->show();
}

void MainWindow::createJournal(QString* str)
{
    QStringList data=str->split("\n");
    QDir().mkdir(data[0]);
    QFile file(data[0]+"/init.txt");
    file.open(QIODevice::WriteOnly);
    file.write(str->toUtf8());
    file.close();
    db=new DataBase(data[0]);
    db->connectToDB();

    model = new QSqlTableModel;
    model->setTable("SchoolBoy");
    model->select();
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    SchoolBoysView=new QTableView();
    SchoolBoysView->setModel(model); //NoEdit in Window

    Name=data[0];
    Teacher=data[1];
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<2;j++)
        {
            QuartersDates[i][j]=data[i*2+j+2];
        }
    }

    ui->saveJournal->setEnabled(true);
    ui->changeJournal->setEnabled(true);
    ui->menu_2->setEnabled(true);
    ui->menu_3->setEnabled(true);
    ui->changeSubjectTimePeriod->setEnabled(false);
    this->setWindowTitle("Журнал класса "+Name);

    while(ui->tabWidget->count()!=0)
    {
        ui->tabWidget->removeTab(0);
    }
    CurrentPage=0;
}

void MainWindow::changeJournal(QString *str)
{
    QStringList Data=str->split("\n");
    Name=Data[0];
    Teacher=Data[1];
    for(int k=0;k<4;k++)
    {
        if(QDate::fromString(QuartersDates[k][0],"dd.MM.yyyy")<QDate::fromString(Data[k*2+2],"dd.MM.yyyy"))
            for(int i=0;i<Buttons.size();i++) Buttons[i]->DeleteColumns(QuartersDates[k][0],Data[k*2+2],k);
        if(QDate::fromString(QuartersDates[k][0],"dd.MM.yyyy")>QDate::fromString(Data[k*2+2],"dd.MM.yyyy"))
            for(int i=0;i<Buttons.size();i++) Buttons[i]->InsertColumns(QuartersDates[k][0],Data[k*2+2],k);
        if(QDate::fromString(QuartersDates[k][1],"dd.MM.yyyy")<QDate::fromString(Data[k*2+3],"dd.MM.yyyy"))
            for(int i=0;i<Buttons.size();i++) Buttons[i]->InsertColumns(QuartersDates[k][1],Data[k*2+3],k);
        if(QDate::fromString(QuartersDates[k][1],"dd.MM.yyyy")>QDate::fromString(Data[k*2+3],"dd.MM.yyyy"))
            for(int i=0;i<Buttons.size();i++) Buttons[i]->DeleteColumns(QuartersDates[k][1],Data[k*2+3],k);
    }
    for(int k=0;k<4;k++)
    {
        for(int i=0;i<2;i++) QuartersDates[k][i]=Data[k*2+i+2];
    }
    this->setWindowTitle("Журнал класса "+Name);
}

void MainWindow::addSchoolBoy(QString *str)
{
    QStringList data=str->split("\n");
    int id=SetSchoolBoy(data[0],0,SchoolBoys.size());
    for(int i=0;i<Buttons.size();i++)
    {
        qDebug("No");
        Buttons[i]->InsertRow(id,data[0]);
    }
    qDebug("No");
    SchoolBoys.insert(id,data[0]);
    model->insertRow(id);
    qDebug("No");
    for(int i=0;i<model->columnCount();i++)
    {
        if(i<data.size()) model->setData(model->index(id,i),data[i]);
        else model->setData(model->index(id,i),"");
    }
    model->submitAll();
}

void MainWindow::delSchoolBoy(QVector<int> nums)
{
    for(int i=nums.size()-1;i>=0;i--)
    {
        for(int j=0;j<Buttons.size();j++)
        {
            Buttons[j]->DeleteRow(nums[i]);
        }
        model->removeRow(nums[i]);
        SchoolBoys.removeAt(nums[i]);
    }
    model->submitAll();
}

void MainWindow::addSubject(QString *str)
{
    CreateSubjectFile(*str);
    QString name=str->split("\n")[0];
    myPushButton *button=new myPushButton(SchoolBoys,QuartersDates,CurrentPath,name);
    ui->scroollLayout->addWidget(button);
    connect(button,SIGNAL(sentTable(MyTableWidget*,QString)),this,SLOT(GetTable(MyTableWidget*,QString)));
    Buttons.push_back(button);
}

void MainWindow::delSubject(QVector<int> nums)
{
    QString name;
    for(int i=nums.size()-1;i>=0;i--)
    {
        name=Buttons[nums[i]]->text();
        qDebug(name.toUtf8());
        for(int j=0;j<ui->tabWidget->count();j++)
        {
            if(name==ui->tabWidget->tabText(j) || (name+"*")==ui->tabWidget->tabText(j))
            {
                ui->tabWidget->removeTab(j);
                break;
            }
        }
        QLayoutItem *item=ui->scroollLayout->takeAt(nums[i]);
        delete item->widget();
        delete item;
        QDir dir(CurrentPath+"/"+name);
        dir.removeRecursively();
        Buttons.removeAt(nums[i]);
    }
}

QStringList MainWindow::GetDate(QDate first, QDate last, int times[])
{
    QStringList dates;
    int day;
    for(QDate currentDate=first;currentDate<=last;currentDate=currentDate.addDays(1))
    {
        day=currentDate.dayOfWeek();
        if(day==7) continue;
        for(int i=0;i<times[day];i++)
        {
            dates.push_back(currentDate.toString("dd.MM.yyyy")+";");
        }
    }
    return dates;
}

int MainWindow::SetSchoolBoy(QString Name, int L, int R)
{
    int M=0;
    while(L<R)
    {
        if(R==(L+1) && Name<SchoolBoys[M]) return M-1;
        M=(L+R)/2;
        if(Name<SchoolBoys[M]) L=M;
        else if(Name>SchoolBoys[M]) R=M;
        else return M;
    }
    return M;
}


void MainWindow::CreateSubjectFile(QString str)
{
    QStringList text=str.split("\n");
    QDir dir;
    dir.mkdir(CurrentPath+"/"+text[0]);
    QFile *markFile=new QFile(CurrentPath+"/"+text[0]+"/Quarter.csv");
    markFile->open(QIODevice::WriteOnly);
    QString Data="";
    QStringList dates;
    for(int i=1;i<7;i++) Data+=text[i]+";";
    Data+="\n";
    int times[7];
    for(int i=1;i<7;i++) times[i]=text[i].toInt();
    for(int k=0;k<4;k++)
    {
        dates+=GetDate(QDate::fromString(QuartersDates[k][0],"dd.MM.yyyy"),
                QDate::fromString(QuartersDates[k][1],"dd.MM.yyyy"),
                times);
    }
    QString *Dotes=new QString(dates.size(),';');
    Data+=dates.join("");
    for(int i=0;i<SchoolBoys.size();i++)
    {
        Data+="\n"+*Dotes;
    }
    markFile->write(Data.toUtf8());
    markFile->close();
    QFile *yearFile=new QFile(CurrentPath+"/"+text[0]+"/Year.csv");
    yearFile->open(QIODevice::WriteOnly);
    QString *Dotes2=new QString(7,';'),Data2="";
    for(int i=0;i<SchoolBoys.size();i++)
    {
        Data2+=*Dotes2+"\n";
    }
    yearFile->write(Data2.toUtf8());
    yearFile->close();
}

void MainWindow::GetTable(MyTableWidget *table, QString text)
{
    for(int i=0;i<ui->tabWidget->count();i++)
    {
        if(ui->tabWidget->tabText(i)==text || ui->tabWidget->tabText(i)==text+"*") return;
    }
    ui->tabWidget->addTab(table,text);
    ui->labelState->setText(QString::number(CurrentPage+1)+"/4 четверть");
    connect(this,SIGNAL(changePage(int)),table,SLOT(SetPage(int)));
    if(CurrentPage!=0) ui->pushButton->setEnabled(true);
    if(CurrentPage!=3) ui->pushButton_2->setEnabled(true);
}

void MainWindow::ChangeTable()
{
    if(ui->tabWidget->tabText(ui->tabWidget->currentIndex())[ui->tabWidget->tabText(ui->tabWidget->currentIndex()).size()-1]!='*')
    {
        ui->tabWidget->setTabText(ui->tabWidget->currentIndex(),ui->tabWidget->tabText(ui->tabWidget->currentIndex())+"*");
    }

}

void MainWindow::CloseTab()
{
    QString name=ui->tabWidget->tabText(ui->tabWidget->currentIndex());
    if(name[name.size()-1]=='*')
    {
        int n=QMessageBox::question(this,"Сохранение","Вы уверены, что хотите сохранить изменения?",QMessageBox::Yes | QMessageBox::No);
        if(n==QMessageBox::Yes)
        {
            for(int i=0;i<Buttons.size();i++)
            {
                if((Buttons[i]->text()+"*")==name)
                {
                    Buttons[i]->WriteQuarterFile();
                    Buttons[i]->WriteYearFile();
                    ui->tabWidget->removeTab(i);
                    break;
                }
            }
        }
    }
    if(ui->tabWidget->count()==0)
    {
        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
    }
}
