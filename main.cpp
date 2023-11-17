#include "databaseParsers.cpp"
#include "refrigeratorMenu.cpp"

int main()
{
    // Back-End
    UserProfiles userList("masterUsers.csv"); // loads database for ALL users

    vector<string> fridges = {"None"};
    vector<string> allergies = {"Tomatoes"};
    
    userList.deleteUser("chickens@gmail.com");

    userList.addUser("chickens@gmail.com", "chickens123", "Chicken Man", fridges, allergies);

    userList.displayUsers();

    
    // specified fridge associated users implementation database

    // specified fridge items in fridge 

    // user class and their info database


    // Front-End
    // displayMenu();
    // selectChoices();



    userList.saveToFile(); // always save to file to update databases

    return 0;
}