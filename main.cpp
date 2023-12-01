#include <iostream>

#include "databaseParsers.cpp"
#include "refrigeratorMenu.cpp"
#include "login.cpp"

using namespace std;

// Function declaration(s)
void addItemToFridge(UserProfiles&, Fridge&, Item&, Section&);

int main()
{
    // Back-End
    UserProfiles userList; // loads database for ALL users

    // check login here first

    loginChoices();


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