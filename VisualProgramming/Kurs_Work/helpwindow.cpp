#include "helpwindow.h"
#include "ui_helpwindow.h"

helpWindow::helpWindow(QString Path, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::helpWindow)
{
    ui->setupUi(this);

    this->setMaximumSize(this->width(),this->height());
    this->setMinimumSize(this->width(),this->height());

    connect(ui->NextButton, SIGNAL(clicked()), ui->TextBrowser, SLOT(forward()));
    connect(ui->BackButton, SIGNAL(clicked()), ui->TextBrowser, SLOT(backward()));
    connect(ui->HomeButton, SIGNAL(clicked()), ui->TextBrowser, SLOT(home()));
    connect(ui->TextBrowser, SIGNAL(forwardAvailable(bool)), ui->NextButton, SLOT(setEnabled(bool)));
    connect(ui->TextBrowser, SIGNAL(backwardAvailable(bool)), ui->BackButton, SLOT(setEnabled(bool)));

    this->setLayout(ui->VerticalLayout);

    ui->TextBrowser->setSource(QUrl::fromLocalFile(Path));
}

helpWindow::~helpWindow()
{
    delete ui;
}
