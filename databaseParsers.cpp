#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>

#include "refrigeratorClasses.cpp"

using namespace std;

class User
{
public:
    User(const string& email, const string& password, const string& name, 
         vector<string> associatedFridges, vector<string> associatedAllergies) : email(email),
         password(password), name(name), associatedFridges(associatedFridges), 
         associatedAllergies(associatedAllergies)
    {
        // should be empty, Users can only be created when all values are filled
    }

    void setEmail(const string& newEmail)
    {
        email = newEmail;
    }

    void setPassword(const string& newPassword)
    {
        password = newPassword;
    }

    string getEmail() const
    {
        return email;
    }

    string getPassword() const
    {
        return password;
    }

    string getName() const
    {
        return name;
    }

    vector<string> getFridges() const
    {
        return associatedFridges;
    }

    vector<string> getAllergies() const
    {
        return associatedAllergies;
    }

    void addFridges(const string& newFridge)
    {
        associatedFridges.push_back(newFridge);
    }
    
    void deleteFridge(const string& fridge)
    {
        auto it = find(associatedFridges.begin(), associatedFridges.end(), fridge);

        if (it != associatedFridges.end())
        {
            associatedFridges.erase(it);
        }
        else
        {
            cout << "Fridge not found." << endl;
        }
    }

    void addAllergy(const string& newAllergy)
    {
        associatedAllergies.push_back(newAllergy);
    }
    
    void deleteAllergy(const string& allergy)
    {
        auto it = find(associatedAllergies.begin(), associatedAllergies.end(), allergy);

        if (it != associatedAllergies.end())
        {
            associatedAllergies.erase(it);
        }
        else
        {
            cout << "Allergy not found." << endl;
        }
    }

private:
    string email;
    string password;
    string name;

    vector<string> associatedFridges;
    vector<string> associatedAllergies;
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

    // vector<Section> sections;
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

    // vector<section> sections; //This will hold all of the different sections of the fridge
    vector<User> users;
    // vector<Item> items;
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

            // saves associated fridges to user
            string fridgeList;
            vector<string> associatedFridges;
            getline(data, fridgeList, ',');

            stringstream listOfFridges(fridgeList);
            string fridge;
            while(getline(listOfFridges, fridge, '-'))
            {
                associatedFridges.push_back(fridge);
            }
            
            // saves associated allergies to user
            string allergyList;
            vector<string> associatedAllergies;
            getline(data, allergyList, ',');

            stringstream listOfAllergies(allergyList);
            string allergy;
            while(getline(listOfAllergies, allergy, '-'))
            {
                associatedAllergies.push_back(allergy);
            }

            createUser(email, password, name, associatedFridges, associatedAllergies);
        }

        file.close();
    }

    // should only be used inside this class
    void createUser(const string& email, const string& password, const string& name, 
                    vector<string> associatedFridges, vector<string> associatedAllergies)
    {
        listOfUsers.push_back(User(email, password, name, associatedFridges, associatedAllergies));
    }

    void addUser(const string& email, const string& password, const string& name, 
                    vector<string> associatedFridges, vector<string> associatedAllergies)
    {
        for (const auto& user : listOfUsers)
        {
            if (email == user.getEmail())
            {
                cout << email << " is already associated with another user" << endl;
                return;
            }
        }

        listOfUsers.push_back(User(email, password, name, associatedFridges, associatedAllergies));
        cout << email << " has been added!" << endl;
    }

    void displayUsers() const
    {
        cout << "---------------------------------------------------"<< endl;
        cout << "| Name                 | Email" << endl;
        cout << "---------------------------------------------------" << endl;

        for (const auto& user : listOfUsers)
        {
            cout << "| " << setw(20) << left << user.getEmail()
                << " | " << setw(28) << left << user.getName() << endl;
        }

        cout << "-----------------------------------------------------------------------------" << endl;
    }

    void displayUser(const string& email) const
    {
        for (const auto& user : listOfUsers)
        {
            if (user.getEmail() == email)
            {
                cout << "Name: " << user.getName()
                     << " | Email: " << user.getEmail() << endl;
                return;
            }
        }

        cout << email << " does not exist, please create an account." << endl;
    }

    void changePassword(const string& email, const string& newPassword)
    {
        for (auto& user : listOfUsers)
        {
            if (user.getEmail() == email)
            {
                user.setPassword(newPassword);
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
            if (user.getEmail() == email)
            {
                user.setEmail(newEmail);
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
            if (it->getEmail() == email)
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
            file << user.getEmail() << "," << user.getPassword() << "," << user.getName();
            
            file << "," << user.getFridges()[0];
            for (size_t i = 1; i < user.getFridges().size(); i++)
            {
                file << "-" << user.getFridges()[i];
            }

            file << "," << user.getAllergies()[0];
            for (size_t i = 1; i < user.getAllergies().size(); i++)
            {
                file << "-" << user.getAllergies()[i];
            }

            file << "\n";
        }
        file.close();
        
        // cout << "Saved to " << filename << endl;
    }

private:
    string filename;
    vector<User> listOfUsers;
};

