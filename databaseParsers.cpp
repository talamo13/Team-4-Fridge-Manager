#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>

#include "refrigeratorClasses.cpp"

using namespace std;

// master database for users
class UserProfiles
{
public:
    UserProfiles(const string& filename) : filename(filename)
    {
        ifstream file(filename);

        if (file.is_open())
        {
            listOfUsers.clear();

            string line;

            while(getline(file, line))
            {
                stringstream data(line);
                string email, password, name;
                getline(data, email, ',');
                getline(data, password, ',');
                getline(data, name, ',');

                createUser(email, password, name);
            }

            file.close();
        }
        else
        {
            ofstream createFile(filename);
            createFile.close();
        }
    }

    void createUser(const string& email, const string& password, const string& name)
    {
        for (const auto& user : listOfUsers)
        {
            if (email == user.first.first)
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
    vector<pair<pair<string, string>, string>> listOfUsers;
};


// database for fridge and their values, users and their items connected to fridge
class Fridge
{
public:
    FridgeUsers(const string& filename) : fridgeName(filename)
    {
        ifstream file(filename);

        if (file.is_open())
        {
            listOfUsers.clear();

            string line;

            while(getline(file, line))
            {
                stringstream data(line);
                string email, password, name;
                getline(data, email, ',');
                getline(data, password, ',');
                getline(data, name, ',');

                createUser(email, password, name);
            }

            file.close();
        }
        else
        {
            ofstream createFile(filename);
            createFile.close();
        }
    }

private:
    string fridgeName;
    string volume;
    string 
};