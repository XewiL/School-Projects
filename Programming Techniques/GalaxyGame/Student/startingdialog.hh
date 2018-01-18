#ifndef STARTINGDIALOG_HH
#define STARTINGDIALOG_HH

#include <QDialog>

namespace Ui {
class startingdialog;
}

class startingdialog : public QDialog
{
    Q_OBJECT

public:
    explicit startingdialog(QWidget *parent = 0);
    ~startingdialog();

    int exec();

public slots:
    void finalPoints(int points);

signals:
    void sendData(int ships);

private:
    Ui::startingdialog *ui;
};

#endif // STARTINGDIALOG_HH
