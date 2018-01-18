#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QWidget>

namespace Ui {
class Mainwindow;
}

class Mainwindow : public QWidget
{
    Q_OBJECT

public:
    explicit Mainwindow(QWidget *parent = 0);
    ~Mainwindow();

public slots:
    void clear_button_clicked();
    void kmh2miles(int kmh);

private:
    Ui::Mainwindow *ui;
};

#endif // MAINWINDOW_HH
