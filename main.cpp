#include <iostream>
#include <string>
#include <limits>

//#include "databaseParsers.cpp"
#include "refrigeratorMenu.cpp"
//#include "login.cpp"

using namespace std;

// Function declaration(s)
bool checkEmail(vector<User>& listOfUsers, const string& emailToCheck);

bool checkPass(vector<User>& listOfUsers, const string& email, const string& passCheck);

User& successfulLogin(vector<User>& listOfUsers, const string& emailChecked, const string& passChecked);

User& loginChoices(vector<User>& userVec);

int main()
{
    // Back-End
    UserProfiles userList; // loads database for ALL users

    // check login here first
    User loggedIn;
    loggedIn = loginChoices(userList.getUsers());

    cout << "Logged in as: " << loggedIn.getName() << endl;

    

    //loginChoices();


    // after validated open all needed databases

    ItemsDatabase savedItems; // loads database for saved items

    FridgesDatabase fridges;

    Fridge kitchenMasterTest = fridges.getFridges()[0]; // 71360 volume total

    Section sectionTest;
    
    Item normalItem("normal", 1, 1, 2, 500, "Unknown"); // Item 1: normal, no problem
    Item allergicItem("Shellfish", 1, 2, 3, 400, "Fish"); // Item 2: a user is allergic
    Item bigItem("nuclear bomb", 2000, 4000, 2, 3, "Unknown"); // Item 3: item is too big
    Item allergicBigItem("Shellfish that is nuclear", 2000, 4000, 2, 3, "Fish"); // Item 4: has allergy name 
    Item allergicSmallItem("Shellfish that is sooo big", 1, 1, 1, 2, "Fish"); // Item 5: has allergy name

    addItemToFridge(userList, kitchenMasterTest, normalItem, sectionTest);
    addItemToFridge(userList, kitchenMasterTest, allergicItem, sectionTest);
    addItemToFridge(userList, kitchenMasterTest, bigItem, sectionTest);
    addItemToFridge(userList, kitchenMasterTest, allergicBigItem, sectionTest);
    addItemToFridge(userList, kitchenMasterTest, allergicSmallItem, sectionTest);
    
    for (const auto& i : kitchenMasterTest.getContents())
    {
        cout << i.getItemName() << " ";
    }

    // specified fridge associated users implementation database

    // specified fridge items in fridge 

    // user class and their info database


    // Front-End
    // displayMenu();
    // selectChoices();


    // fridges.saveToFile();
    userList.saveToFile(); // always save to file to update databases

    return 0;
}

/******************************************************************************

Basic User Login

*******************************************************************************/

bool checkEmail(vector<User>& listOfUsers, const string& emailToCheck)
{
    for (auto& user : listOfUsers)
    {
        if (user.getEmail() == emailToCheck)
        {
            return false;
        }
    }
    return true;
}

bool checkPass(vector<User>& listOfUsers, const string& email, const string& passCheck)
{
    for (const auto& user : listOfUsers)
    {
        if ((email == user.getEmail()) && (passCheck == user.getPassword()))
        {
            return false;
        }
    }
    return true;
}

User& successfulLogin(vector<User>& listOfUsers, const string& emailChecked, const string& passChecked)//Should only run after credential verification
{
    for (auto& user : listOfUsers)
    {
        if((emailChecked == user.getEmail()) && (passChecked == user.getPassword()))
        {
            return user;
        }
    }
}

User& loginChoices(vector<User>& userVec)
{
    int choices;
    
    cout << "Select an option: \n"
         << "-------------------\n"
         << "1: Register for Fridge Manager\n"
         << "2: Login\n"
         << "Selection: ";

    cin >> choices;

    if (choices == 1) 
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string name, email, password;
        
        cout << "Enter your full name: ";
        getline(cin, name);

        cout << "Enter email: ";
        cin >> email;

        if(checkEmail(userVec, email))
        {
            cout << "Create a password: ";
            cin >> password;

            vector<string> allergies;
            cout << "\nDo you have any allergies? If you don't type None and click Enter.\n"
                 << "If you do, type them line-by-line.\n"
                 << "When you are done, type Done and click Enter." << endl;
                
            string allergy;
            cin >> allergy;
            allergies.push_back(allergy);
            
            if (allergies[0] != "None")
            {
                while (allergy != "Done")
                {
                    cin >> allergy;
                    if (allergy != "Done")
                    {
                        allergies.push_back(allergy);
                    }
                }
            }

            ofstream file;
            file.open("masterUsers.csv", ios::app);
            file << email << "," << password << "," << name << ",";
            
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
            
            cout << "\nAccount has been registered.\n" << endl;
            
            userVec.push_back(User(email, password, name, allergies));

            file.close();
        }
        else
        {
            cout << "Email already in use. Please try again.\n" << endl;
        }
        
        loginChoices(userVec);
    }
    else if (choices == 2)
    {
        string email, password;
    
        do
        {
            cout << "Enter email: "; 
            cin >> email;

            if(checkEmail(userVec, email))
            {
                cout << "Incorrect email, please try again." << endl;
            }
        }
        while(checkEmail(userVec, email));

        do
        { 
            cout << "Enter password: ";
            cin >> password;

            if(checkPass(userVec, email, password))
            {
                cout << "Incorrect password, please try again." << endl;
            }
            else
            {
                cout << "Login Successful." << endl;

                for (auto& user : userVec)
                {
                    if((email == user.getEmail()) && (password == user.getPassword()))
                    {
                        return user;
                    }
                }
            }
        }
        while(checkPass(userVec, email, password));
    }

    static User defaultUser;
    return defaultUser;
}