#include <iostream>

#include "databaseParsers.cpp"
#include "refrigeratorMenu.cpp"

using namespace std;

// Function declaration(s)
void addItemToFridge(UserProfiles&, Fridge&, Item&, Section&);

int main()
{
    // Back-End
    UserProfiles userList; // loads database for ALL users
    ItemsDatabase savedItems; // loads database for saved items

    FridgesDatabase fridges;

    Fridge kitchenMasterTest = fridges.getFridges()[0]; // 71360 volume total
    
    Section sectionTest = kitchenMasterTest.getSections()[7];

    // TEST CASES FOR ADDING ITEMS
    Item normalItem("normal", 1, 1, 2, 500); // Item 1: normal, no problem
    Item allergicItem("Shellfish", 1, 2, 3, 400); // Item 2: a user is allergic
    Item bigItem("nuclear bomb", 2000, 4000, 2, 3); // Item 3: item is too big
    Item allergicBigItem("Shellfish that is nuclear", 2000, 4000, 2, 3); // Item 4: has allergy name 
    Item allergicSmallItem("Shellfish that is sooo big", 1, 1, 1, 2); // Item 5: has allergy name

    addItemToFridge(userList, kitchenMasterTest, normalItem, sectionTest);
    addItemToFridge(userList, kitchenMasterTest, allergicItem, sectionTest);
    addItemToFridge(userList, kitchenMasterTest, bigItem, sectionTest);
    addItemToFridge(userList, kitchenMasterTest, allergicBigItem, sectionTest);
    addItemToFridge(userList, kitchenMasterTest, allergicSmallItem, sectionTest);

    // sectionTest = kitchenMasterTest.getSections()[7];
    
    // cout << "-----Default-----      " << kitchenMasterTest.getSections()[7].getUsedVolume() << endl;
    // for (const auto& item : kitchenMasterTest.getSections()[7].getItems())
    // {
    //     cout << item.getItemName() << endl;
    // }
    // cout << endl;
    
    // kitchenMasterTest.addItem(addedItem, sectionName);
    // cout << "Item added.\n" << endl ;
    


    // cout << "-----After Add-----      " << kitchenMasterTest.getSections()[7].getUsedVolume() << endl;
    // for (const auto& item : kitchenMasterTest.getSections()[7].getItems())
    // {
    //     cout << item.getItemName() << endl;
    // }
    // cout << endl;



    // kitchenMasterTest.removeItem("Shellfish", sectionName);
    // cout << "Item removed.\n" << endl ;

    // cout << "-----After Remove-----" << endl;
    // for (const auto& item : kitchenMasterTest.getSections()[7].getItems())
    // {
    //     cout << item.getItemName() << endl;
    // }
    // cout << endl;


    // for (const auto& user : userList.getUsers())
    // {
    //     for (const auto& allergy: user.getAllergies())
    //     {
    //         if (addedItem.getItemName() == allergy)
    //         {
    //             kitchenMasterTest.removeItem(addedItem.getItemName(), sectionName);
    //             cout << "A user of this fridge is allergic to this item.\n";
    //         }
    //     }
    // }

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
                fridge.removeItem(item.getItemName(), section.getSectionName());
                return;
            }
        }
    }

    cout << item.getItemName() << " was successfully added to the " 
    << section.getSectionName() << ".\n";
}