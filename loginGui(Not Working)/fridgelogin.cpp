#include "fridgelogin.h"
#include "./ui_fridgelogin.h"

fridgeLogin::fridgeLogin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::fridgeLogin)
{
    ui->setupUi(this);
}

fridgeLogin::~fridgeLogin()
{
    delete ui;
}

void fridgeLogin::on_loginButton_clicked()
{
    //QString email = ui->email_input->text();
    //QString pass = ui->pass_input->text();

    //UserProfiles u;

    //vector<User> userList = u.getUsers();

    //for(int i = 0; i < userList.size(); i++)
    //{
    //    if(userList[i].getEmail() = email && userList[i].getPassword != pass)
    //    {

    //    }
    //}

}

