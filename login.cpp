/******************************************************************************

Basic User Login

*******************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "databaseParsers.cpp"

using namespace std;

bool checkEmail(vector<User>& listOfUsers, string emailToCheck)
{
    for (const auto& user : listOfUsers)
    {
        if (user.getEmail() == emailToCheck)
        {
            return false;
        }
    }
    return true;
}

User& logIn(vector<User>& listOfUsers)
{
    string email, password;
    
    while (true)
    {
        cout << "Enter email: "; 
        cin >> email;
        cout << "Enter password: ";
        cin >> password;
        
        for (auto& user : listOfUsers)
        {
            if ((email == user.getEmail()) && (password == user.getPassword()))
            {
                return user;
            }
        }

        cout << "Wrong email or password, please try again." << endl;
    }
}

void loginChoices()
{

    int choices;
    
    cout << "Select an option: \n"
         << "-------------------\n"
         << "1: Register for Fridge Manager\n"
         << "2: Login\n"
         << "Selection: "  << endl;

    cin >> choices;
    
    if (choices == 1) 
    {
        UserProfiles userList;

        string name, email, password;
        
        cout << "Enter your full name: ";
        cin >> name;
        cout << "Enter email: ";
        cin >> email;

        if(checkEmail(userList.getUsers(), email))
        {
            cout << "Create a password: ";
            cin >> password;

            vector<string> allergies;
            string allergy;
            cout << "Do you have any allergies? If so, type them line-by-line.\n"
                << "When you are done or you have no allergies, type None and click Enter";

            cin >> allergy;
            allergies.push_back(allergy);

            if (allergies[0] != "None")
            {
                while(allergy != "None")
                {
                    cin >> allergy;
                    allergies.push_back(allergy);
                }
            }

            ofstream file;
            file.open("mastersUsers.csv");
            file << email << "," << password << "," << name;
            
            if ((allergies[0] == "None") || (allergies.size() == 1)) 
            {
                file << allergies[0] << "\n";
            }
            else
            {
                file << allergies[0];

                for (size_t i = 1; i < allergies.size(); i++)
                {
                    file << "-" << allergies[i];
                }
                file << "\n";
            }
            
            cout << "\nAccount has been registered" << endl;

            file.close();
        }
        else
        {
            cout << "Email already in use. Please try again." << endl;
        }
        
        loginChoices();
    }
    else if (choices == 2)
    {
        User loggedInUser = logIn(userList.getUsers());

        if(!stat) {
            cout << "Incorrect password, try again"<<endl;
            system("PAUSE");
            return 0;
        }
        else {
            cout << "Login Successful!"<<endl;
            system("PAUSE");
            return 1;
        }
    }
}