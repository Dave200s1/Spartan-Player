#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtMultimedia>
#include <QVideoWidget>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void setStation(int index);
    void play_function();
    void pause_function();
    void stop_function();
    void full_screen_function();


private slots:
    void on_actionOpen_triggered();

    void on_actionsmall_screen_triggered();

    void on_actionplayVideo_triggered();

    void on_actionpauseVideo_triggered();

    void on_actionfullScreen_triggered();

    void on_actionAbout_triggered();


    void on_actionTrueFullScreen_triggered();

private:
    Ui::MainWindow *ui;
    QMediaPlayer* player;
    QVideoWidget* vw;
    QAudioOutput* audio;
};
#endif // MAINWINDOW_H
