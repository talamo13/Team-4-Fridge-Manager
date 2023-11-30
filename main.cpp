#include "databaseParsers.cpp"
#include "refrigeratorMenu.cpp"

int main()
{
    // Back-End
    UserProfiles userList; // loads database for ALL users
    ItemsDatabase savedItems; // loads database for saved items

    FridgesDatabase fridges;

    Fridge kitchenMasterTest = fridges.getFridges()[0];
    Section sectionTest;
    
    string addedItemName = "potato";
    Item addedItem(addedItemName, 2, 3, 3, 20);

    string sectionName = "Middle Shelf";
    
    
    // for (const auto& section : kitchenMasterTest.getSections())
    // {
    //     cout << section.getSectionName() << endl;
    // }

    sectionTest = kitchenMasterTest.getSections()[7];
    for (const auto& item : sectionTest.getItems())
    {
        cout << item.getItemName() << endl;
    }
    
    cout << "Before add:\n";
    kitchenMasterTest.addItem(addedItem, sectionTest);

    cout << "After add:\n";
    cout << kitchenMasterTest.getSections()[7].getItems().size();

    
    for (const auto& item : sectionTest.getItems())
    {
        cout << item.getItemName() << endl;
    }




    for (const auto& user : userList.getUsers())
    {
        for (const auto& allergy: user.getAllergies())
        {
            if (addedItem.getItemName() == allergy)
            {
                kitchenMasterTest.removeItem(addedItem.getItemName(), sectionName);
                cout << "A user of this fridge is allergic to this item.\n";
            }
        }
    }

    // specified fridge associated users implementation database

    // specified fridge items in fridge 

    // user class and their info database


    // Front-End
    // displayMenu();
    // selectChoices();



    userList.saveToFile(); // always save to file to update databases

    return 0;
}