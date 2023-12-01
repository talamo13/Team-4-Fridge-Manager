#include <iostream>

#include "databaseParsers.cpp"
#include "refrigeratorMenu.cpp"

using namespace std;

int main()
{
    // Back-End
    UserProfiles userList; // loads database for ALL users
    ItemsDatabase savedItems; // loads database for saved items

    FridgesDatabase fridges;

    Fridge kitchenMasterTest = fridges.getFridges()[0]; // 71360 volume total
    Section sectionTest;
    
    string addedItemName = "Shellfish";
    Item addedItem(addedItemName, 2, 3, 3, 20);

    string sectionName = "Middle Shelf";

    kitchenMasterTest.addItem(addedItem, sectionName);

    kitchenMasterTest.removeItem(addedItemName, sectionName);

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