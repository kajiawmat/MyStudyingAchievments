#include "helpform.h"
#include "ui_helpform.h"

HelpForm::HelpForm(QString Path, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HelpForm)
{
    ui->setupUi(this);

    this->setMaximumSize(this->width(),this->height());
    this->setMinimumSize(this->width(),this->height());

    connect(ui->NextButton, SIGNAL(clicked()), ui->TextBrowser, SLOT(forward()));
    connect(ui->BackButton, SIGNAL(clicked()), ui->TextBrowser, SLOT(backward()));
    connect(ui->HomeButton, SIGNAL(clicked()), ui->TextBrowser, SLOT(home()));
    connect(ui->TextBrowser, SIGNAL(forwardAvailable(bool)), ui->NextButton, SLOT(setEnabled(bool)));
    connect(ui->TextBrowser, SIGNAL(backwardAvailable(bool)), ui->BackButton, SLOT(setEnabled(bool)));
    ui->TextBrowser->setSource(QUrl::fromLocalFile(Path));
}

HelpForm::~HelpForm()
{
    delete ui;
}
