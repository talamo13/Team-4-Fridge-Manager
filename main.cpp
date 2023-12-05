#include <iostream>
#include <string>
#include <limits>

#include "refrigeratorMenu.cpp"

using namespace std;


int main()
{
    UserProfiles userList; // loads database for ALL users
    
    // check login here first
    User loggedIn;
    bool logged = false;
    
    ItemsDatabase savedItems; // loads database for saved items
    FridgesDatabase fridges(savedItems); // loads database for saved fridges
    Fridge kitchenMasterTest = fridges.getFridges()[0]; // 71360 volume total

    while(!logged)
    {
        loggedIn = loginChoices(userList.getUsers(), kitchenMasterTest);

        if(loggedIn.getName() != "")
        {
            logged = true;
        }
    }

    cout << "Logged in as: " << loggedIn.getName() << endl;

    // after login validation, load all databases

    // load user's sections
    vector<Section> userSections;
    for (auto& section : kitchenMasterTest.getSections())
    {
        if (section.getSectionOwner().getEmail() == loggedIn.getEmail())
        {
            userSections.push_back(section);
        }
    }

    selectChoices(userList, loggedIn, savedItems, fridges, kitchenMasterTest, userSections);

    userList.saveToFile(); // always save to file to update databases
    savedItems.saveToFile();
    fridges.saveToFile();

    return 0;
}
