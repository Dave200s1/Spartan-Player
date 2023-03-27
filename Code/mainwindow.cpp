#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QDebug>
#include <QKeyEvent>
#include <QTimer>
#include <QMessageBox>

#include"about.h"



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



    //track progress of Video
    QTimer *timer = new QTimer(this);
    connect(timer,&QTimer::timeout,[=]()
    {
        // Get the current position of the video and update the QLabel widget
           double currentPosition = player->position(); // Replace with your own method to get the current position of the video
           int minutes = static_cast<int>(currentPosition / 60000);
           double maxLenghtVideo = player->duration();
           int minutes_backwards = static_cast<int>(maxLenghtVideo/60000);
           ui->start_label->setText(QString("Current Position: %1 mins").arg(minutes));
           ui->end_lebel->setText(QString("%1mins").arg(minutes_backwards- minutes));
    });

    timer->start(1000); // Start the QTimer to update the QLabel widget every second
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
        MainWindow w;
        w.setFixedSize(2400,8000);
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


void MainWindow::on_actionAbout_triggered()
{
    About aboutWindow;
    aboutWindow.setModal(true);
    aboutWindow.exec();
}


void MainWindow::on_actionTrueFullScreen_triggered()
{
    //vw->fullScreenChanged(true);
    qDebug()<<"goind true-full-screen-mode!";
    int choice = QMessageBox::warning(this,"Going True-Full-Scren-Mode","You will not be able to switch back, are you sure ?",QMessageBox::Yes | QMessageBox::Cancel);
    if(choice==QMessageBox::Yes)
    {
        vw->setFullScreen(true);
        vw->showFullScreen();
    }else{

    }

}

