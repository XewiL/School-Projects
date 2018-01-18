// Pääikkunan esittely.
// Lisätty luokkaan kolme jäsenfunktiota.

#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void reset_menu_clicked();
    void gender_clicked();
    void calculateBMI();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_HH
