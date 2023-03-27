#include "about.h"
#include "ui_about.h"
#include<QPixmap>

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    QPixmap pix_Logo(":/icon/img/icons/128_helmet.png");
    ui->LogoIcon->setPixmap(pix_Logo);
    connect(ui->close_btn,&QPushButton::clicked,this,&About::closeAboutWindow);
}

void About::closeAboutWindow()
{
    close();
}

About::~About()
{
    delete ui;
}
