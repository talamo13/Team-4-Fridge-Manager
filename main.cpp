#include "databaseParsers.cpp"
#include "refrigeratorMenu.cpp"

int main()
{
    // Back-End
    UserProfiles userList; // loads database for ALL users
    ItemsDatabase savedItems; // loads database for saved items

    FridgesDatabase fridges;

    Fridge kitchenMasterTest = fridges.getFridges()[0];
    
    for (const auto& section : kitchenMasterTest.getSections())
    {
        cout << section.getSectionName() << endl;
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