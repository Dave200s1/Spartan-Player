#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QDebug>
#include <QKeyEvent>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->start_btn->setIcon(QIcon(":/icon/img/icons/play-button.png"));
    ui->pause_btn->setIcon(QIcon(":/icon/img/icons/pause.png"));
    ui->control_stop_btn->setIcon(QIcon(":/icon/img/icons/stop.png"));
    ui->Full_Screen_btn->setIcon(QIcon(":/icon/img/icons/24px_maximize(1).png"));

    QPixmap pix_volume(":/icon/img/icons/24px_wave-sound.png");
    ui->volume_label->setPixmap(pix_volume);

    connect(ui->Volume_dial,&QDial::valueChanged,this,&MainWindow::setStation);
    connect(ui->pause_btn,&QPushButton::clicked,this,&MainWindow::pause_function);
    connect(ui->start_btn,&QPushButton::clicked,this,&MainWindow::play_function);
    connect(ui->control_stop_btn,&QPushButton::clicked,this,&MainWindow::stop_function);
    connect(ui->Full_Screen_btn,&QPushButton::clicked,this,&MainWindow::full_screen_function);



    player = new QMediaPlayer(this);
    vw = new QVideoWidget(this);
    player->setVideoOutput(vw);

    audio = new QAudioOutput;
    player->setAudioOutput(audio);

    //Connecting the slider to the Video
    connect(player,&QMediaPlayer::durationChanged,ui->horizontalSlider,&QSlider::setMaximum);
    connect(player,&QMediaPlayer::positionChanged,ui->horizontalSlider,&QSlider::setValue);
    connect(ui->horizontalSlider,&QSlider::sliderMoved,player,&QMediaPlayer::setPosition);



    //Adjusting Position and Size
    vw->setFixedSize(700,300);
    vw->move(0,40);
    vw->setMaximumSize(1400,600);


}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setStation(int index)
{
    audio->setVolume(index);
    ui->lcdNumber->display(index);
}



//Select a mp4 file
void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,"Open a File","","Video File(*.*)");
    //on_actionOpen_triggered();
    player->setSource(QUrl::fromLocalFile(filename));
    play_function();
    ui->lcdNumber->display(30);
}

void MainWindow::play_function()
{
    player->play();
    audio->setVolume(30);
}

void MainWindow::pause_function()
{
    player->pause();
}

void MainWindow::stop_function()
{
    player->stop();
}

void MainWindow::full_screen_function()
{
    qDebug()<<"going full-screen";
    //vw->setFullScreen(true);
    showMaximized();
    bool FullScreen = true;
    if(FullScreen == true)
    {
        vw->setFixedSize(1400,600);

        vw->move(0,40);

    }
}

void MainWindow::on_actionsmall_screen_triggered()
{
    qDebug()<<"going small-screen";
    showNormal();
    vw->setFullScreen(false);
    vw->setFixedSize(700,300);
    vw->move(0,40);
}






void MainWindow::on_actionplayVideo_triggered()
{
    player->play();
    audio->setVolume(30);
}


void MainWindow::on_actionpauseVideo_triggered()
{
    player->pause();
}


void MainWindow::on_actionfullScreen_triggered()
{
    qDebug()<<"going full-screen";
    //vw->setFullScreen(true);
    showMaximized();
    bool FullScreen = true;
    if(FullScreen == true)
    {
        vw->setFixedSize(1400,600);

        vw->move(0,40);

    }
}

