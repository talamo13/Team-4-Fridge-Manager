#include "databaseParsers.cpp"

int main()
{
    Users userList("users.csv");

    userList.displayUser("chickens@gmail.com");

    userList.createUser("chickens@gmail.com", "chickens123", "Chicken Man");

    userList.changePassword("chickens@gmail.com", "asdfasdf");

    userList.saveToFile();

    userList.displayUsers();
}