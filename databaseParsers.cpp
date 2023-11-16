#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class Users
{
public:
    Users(const string& filename) : filename(filename)
    {
        ifstream file(filename);

        if (file.is_open)
        {
            listOfUsers.clear();

            string line;

            while(getline(file, line))
            {
                stringstream data(line);
                string email, password, name;
                getline(ss, email, ",");
                getline(ss, password, ",");
                getline(ss, name, ",");

                addUser(email, password, name);
            }

            file.close()
        }
        else
        {
            ofstream createFile(filename);
            createFile.close();
        }
    }

    void createUser(const string& email, const string& password, const string& name)
    {
        listOfUsers.push_back(make_pair(make_pair(email, password), name));
    }
    
    /*
    "Email: " << user.first.first
    "Password: " << user.first.second
    "Name: " << user.second
    */

    void displayUsers() const
    {
        for (const auto& user : listOfUsers)
        {
            cout << "Name: " << user.second << "\t\t, "
                 << "Email: " << user.first.first << endl;
        }
    }

    pair<bool, string> displayUser(const string& email) const
    {
        for (const auto& user : listOfUsers)
        {
            if (user.first.first == email)
            {
                return {true, user.second}
            }
        }

        return (false, "")
    }

    bool changePassword(const string& email, const string& newPassword)
    {
        for (auto& user : listOfUsers)
        {
            if (user.first.first == email)
            {
                user.first.second = newPassword;
                return true;
            }
        }

        return false;
    }

    bool changeEmail(const string& email, const string& newEmail)
    {
        for (auto& user : listOfUsers)
        {
            if (user.first.first == email)
            {
                user.first.first = newEmail;
                return true;
            }
        }

        return false;
    }

    bool deleteUser(const string& email)
    {
        for (auto it = listOfUsers.begin(); it != listOfUsers.end(); it++)
        {
            if (it->first.first == email)
            {
                it = listOfUsers.erase(it);
                return true;
            }
        }

        return false;
    }

    void saveToFile() const
    {
        ofstream file(filename);

        if (file.is_open())
        {
            for (const auto& user : listOfUsers)
            {
                file << user.first.first << "," << user.first.second << "," << user.second << "\n";
            }
            file.close();
        }
    }

private:
    string filename;
    vector<pair<string, string>, string>> listOfUsers;
};