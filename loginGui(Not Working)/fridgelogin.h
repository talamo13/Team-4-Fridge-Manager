#ifndef FRIDGELOGIN_H
#define FRIDGELOGIN_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class fridgeLogin; }
QT_END_NAMESPACE

class fridgeLogin : public QMainWindow
{
    Q_OBJECT

public:
    fridgeLogin(QWidget *parent = nullptr);
    ~fridgeLogin();

private slots:
    void on_pushButton_3_clicked();

    void on_loginButton_clicked();

private:
    Ui::fridgeLogin *ui;
};
#endif // FRIDGELOGIN_H
