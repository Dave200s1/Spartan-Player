#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>

namespace Ui {
class About;
}

class About : public QDialog
{
    Q_OBJECT

public:
    explicit About(QWidget *parent = nullptr);
    ~About();

public slots:
    void closeAboutWindow();
private:
    Ui::About *ui;
};

#endif // ABOUT_H
