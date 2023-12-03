#include <iostream>

//#include "databaseParsers.cpp"
#include "refrigeratorMenu.cpp"
//#include "login.cpp"

using namespace std;

// Function declaration(s)
void addItemToFridge(UserProfiles&, Fridge&, Item&, Section&);

bool checkEmail(vector<User>& listOfUsers, string emailToCheck);

bool checkPass(vector<User>& listOfUsers, string email, string passCheck);

User& successfulLogin(vector<User>& listOfUsers, string emailChecked, string passChecked);

User& logIn(vector<User>& listOfUsers);

User& loginChoices();

int main()
{
    // Back-End
    UserProfiles userList; // loads database for ALL users

    // check login here first
    User loggedIn = loginChoices();
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

bool checkEmail(vector<User>& listOfUsers, string emailToCheck)
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

bool checkPass(vector<User>& listOfUsers, string email, string passCheck)
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

User& successfulLogin(vector<User>& listOfUsers, string emailChecked, string passChecked)//Should only run after credential verification
{
  for (auto& user : listOfUsers)
  {
    if((emailChecked == user.getEmail()) && (passChecked == user.getPassword()))
    {
      return user;
    }
  }
}

User& logIn(vector<User>& listOfUsers)
{
    string email, password;
    
    do{
        cout << "Enter email: "; 
        cin >> email;
        if(checkEmail(listOfUsers, email))
        {
          cout << "Incorrect email, please try again." << endl;
        }
    }while(checkEmail(listOfUsers, email));

    do{ 
      cout << "Enter password: ";
      cin >> password;
      if(checkPass(listOfUsers, email, password))
      {
        cout << "Incorrect password, please try again." << endl;
      }
      else
      {
        cout << "Login Successful." << endl;
        return successfulLogin(listOfUsers, email, password);
      }
    }while(checkPass(listOfUsers, email, password));
}

User& loginChoices()
{

    int choices;
    
    cout << "Select an option: \n"
         << "-------------------\n"
         << "1: Register for Fridge Manager\n"
         << "2: Login\n"
         << "Selection: "  << endl;

    cin >> choices;

    UserProfiles userList;
    vector<User> userVec = userList.getUsers();

    if (choices == 1) 
    {

        string name, email, password;
        
        cout << "Enter your full name: ";
        cin >> name;
        cout << "Enter email: ";
        cin >> email;

        if(checkEmail(userVec, email))
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
        vector<User> loggingIn = userList.getUsers();
        User loggedInUser = logIn(loggingIn);
        return loggedInUser;
    }
}

/***
 ***/

// Function for adding item to fridge
void addItemToFridge(UserProfiles& profiles, Fridge& fridge, Item& item, Section& section)
{
    if (item.getLength() > section.getLength() || item.getWidth() > section.getWidth() ||
    item.getHeight() > section.getHeight())
    {
        cout << item.getItemName() << " is too large for the " 
        << section.getSectionName() << ".\n";
        return;
    }

    for (const auto& user : profiles.getUsers())
    {
        for (const auto& allergy: user.getAllergies())
        {
            if (item.getItemName().find(allergy) != std::string::npos)
            {
                cout << "A user of this fridge is allergic to " << allergy
                << ".\n";
                return;
            }
        }
    }

    cout << item.getItemName() << " was successfully added to the " 
    << section.getSectionName() << ".\n";
    fridge.addItem(item, section.getSectionName());
}
