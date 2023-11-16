#include <iostream>
#include <vector>

using namespace std;

class Users
{
public:
    string email;
    string password;
    string name;

private:
};

class Fridge 
{
public:
    void putItem();
    void removeItem();
    void addSection();

    void setPassword();
    void setUsername();
    void setUser();
    void setSection();

    double getVolume();
    string getUsername();
    string getPassword();
    vector<string> getContents();
    vector<string> getUsers();
    vector<string> getSections();

private:
    struct section; // This will be how we can store the different sizes of the sections of the fridge (l,w,d)
    vector<section> sections; //This will hold all of the different sections of the fridge
    vector<string> users;
    vector<Item> items;
    string username;
    string password;
    string name;
    double volume;
};

class Item 
{
public:
    void setName();
    void setVolume(); // This will ask the user for the items measurements (l,w,d)
    void setExpiration();

    string getName();
    string getExpiration();
    double getVolume();

private:
    string name;
    string expiration;
    double volume;

    // Allows for Fridge object to access private members in 'Item' class
    friend class Fridge;
};

