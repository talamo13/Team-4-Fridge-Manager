#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>

#include "refrigeratorClasses.cpp"

using namespace std;

class User
{
public:
    User(const string& email, const string& password, const string& name) : email(email),
         password(password), name(name)
    {

    }

    void setEmail();
    void setPassword();
    void setName();

    void getEmail();
    void getPassword();
    void getName();

private:
    vector<string> associatedFridges;
    string email;
    string password;
    string name;
    vector<string> allergies;
};

class Fridge
{
public:
    Fridge(const string& name, const double length, const double width, const double height, 
           double remainingCapacity, const double totalCapacity) : name(name), length(length),
           width(width), height(height), remainingCapacity(remainingCapacity),
           totalCapacity(totalCapacity)
    {

    }
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
    string name;
    double length;
    double width;
    double height;
    double remainingCapacity;
    double totalCapacity;

    vector<Section> sections;
    vector<User> users;
};

// creates ALL the fridges
// opens "../Databases/listOfFridges.csv"
class Fridges
{
public:
    Fridges()
    {
        ifstream file(filename);

        fridges.clear();

        string line;

        while(getline(file, line))
        {
            stringstream data(line);
            
            string name;
            getline(data, name, ',');

            string length, width, height, remainingCapacity, totalCapacity; 
            getline(data, length, ',');
            getline(data, width, ',');
            getline(data, height, ',');
            getline(data, remainingCapacity, ',');
            getline(data, totalCapacity, ',');

            double lengthDouble = stod(length);
            double widthDouble = stod(width);
            double heightDouble = stod(height);
            double remainingCapacityDouble = stod(remainingCapacity);
            double totalCapacityDouble = stod(totalCapacity);

            

            fridges.push_back(Fridge(name, lengthDouble, widthDouble, heightDouble, 
                   remainingCapacityDouble, totalCapacityDouble));
        }
    }

private:
    string filename = "../Databases/listOfFridges.csv";

    vector<Fridge> fridges;

    double usedCapacity;
    double totalCapacity;

    struct section; // This will be how we can store the different sizes of the sections of the fridge (l,w,d)
    vector<section> sections; //This will hold all of the different sections of the fridge
    vector<User> users;
    vector<Item> items;
    string username;
    string password;
};

// master database for users
// opens masterUsers.csv
class UserProfiles
{
public:
    UserProfiles(const string& filename) : filename(filename)
    {
        ifstream file(filename);

        listOfUsers.clear();

        string line;

        while(getline(file, line))
        {
            stringstream data(line);
            string email, password, name, fridges, allergies;
            getline(data, email, ',');
            getline(data, password, ',');
            getline(data, name, ',');

            string fridgeList;
            vector<string> associatedFridges;
            getline(data, fridgeList, ',');

            stringstream listOfFridges(fridgeList);
            string fridge;
            while(getline(listOfFridges, fridge, '-'))
            {
                associatedFridges.push_back(fridge);
            }

            createUser(email, password, name, associatedFridges);
        }

        file.close();
    }

    void createUser(const string& email, const string& password, const string& name, vector<string> associatedFridges)
    {
        for (const auto& user : listOfUsers)
        {
            if (email == user)
            {
                cout << email << " is already associated with another user" << endl;
                return;
            }
        }

        listOfUsers.push_back(make_pair(make_pair(email, password), name));
        cout << email << " has been added!" << endl;
    }
    
    /*
    "Email: " << user.first.first
    "Password: " << user.first.second
    "Name: " << user.second
    */

    void displayUsers() const
    {
        cout << "---------------------------------------------------"<< endl;
        cout << "| Name                 | Email" << endl;
        cout << "---------------------------------------------------" << endl;

        for (const auto& user : listOfUsers)
        {
            cout << "| " << setw(20) << left << user.second
                << " | " << setw(28) << left << user.first.first << endl;
        }

        cout << "-----------------------------------------------------------------------------" << endl;
    }

    void displayUser(const string& email) const
    {
        for (const auto& user : listOfUsers)
        {
            if (user.first.first == email)
            {
                cout << "Name: " << user.second
                     << " | Email: " << user.first.first << endl;
                return;
            }
        }

        cout << email << " does not exist, please create an account." << endl;
    }

    void changePassword(const string& email, const string& newPassword)
    {
        for (auto& user : listOfUsers)
        {
            if (user.first.first == email)
            {
                user.first.second = newPassword;
                cout << "Password successfully changed!" << endl;
                return;
            }
        }

        cout << email << " does not exist, please create an account." << endl;
    }

    void changeEmail(const string& email, const string& newEmail)
    {
        for (auto& user : listOfUsers)
        {
            if (user.first.first == email)
            {
                user.first.first = newEmail;
                cout << email << " has been updated to " << newEmail << "." << endl;
                return;
            }
        }

        cout << email << " does not exist, please create an account." << endl;
    }

    void deleteUser(const string& email)
    {
        for (auto it = listOfUsers.begin(); it != listOfUsers.end(); it++)
        {
            if (it->first.first == email)
            {
                it = listOfUsers.erase(it);
                cout << email << " has been removed." << endl;
                return;
            }
        }

        cout << email << " does not exist." << endl;
    }

    void saveToFile() const
    {
        ofstream file(filename);
        for (const auto& user : listOfUsers)
        {
            file << user.first.first << "," << user.first.second << "," << user.second << "\n";
        }
        file.close();
        
        // cout << "Saved to " << filename << endl;
    }

private:
    string filename;
    vector<User> listOfUsers;
};

