#include <iostream>
#include "databaseParsers.cpp"
using namespace std;

// Function definitions
void addItemToFridge(UserProfiles&, Fridge&, Item&, Section&);

// displayMenu
void displayMenu()
{
    cout << "\n**************************************************************\n"
    << "                          MAIN MENU\n"
    << "**************************************************************\n";
	cout << "\nSelect one of the following:\n"
		<< "    1: Add item\n"
		<< "    2: Show current items\n"
		<< "    3: Show expiration dates\n"
		<< "    4: Remaining space\n"
		<< "    5: Edit profile\n"
        << "    6: Check database\n"
		<< "    7: Log out\n";
}

// Function definition selectChoices
void selectChoices(UserProfiles& userList, ItemsDatabase& savedItems, 
FridgesDatabase& fridges, Fridge& kitchenMasterTest, Section& sectionTest)
{
    int choice = 0, sectionCounter = 0;
    kitchenMasterTest = fridges.getFridges()[0];
    Item normalItem("normal", 1, 1, 2, 500, "Unknown");

    while (choice != 7)
    {
        cout << "\nSelect an option: "; 
        cin >> choice; 

        switch (choice)
        {
            // Add an item
            case 1: 
            {
                bool noFoundSection = true;
                string givenSection, itemName, itemType;
                double itemLength, itemWidth, itemHeight; 
                while (noFoundSection)
                {
                    cout << "\nWhich section would you like to add to? Type its name: ";

                    for (const Section sections : username.sectionTests)
                    {
                        cout << sections.getSectionName() << endl;
                    }

                    cin >> givenSection;
                    for (const Section sections : username.sectionTests)
                    {
                        if (givenSection == sections.getSectionName())
                        {
                            sectionTest = kitchenMasterTest.getSections()[sectionCounter];
                            noFoundSection = false;
                            break;
                        }
                        sectionCounter++;
                    }
                }

                cout << "\nEnter the name of the food: ";
                cin >> itemName;
                cout << "\nEnter the item length: ";
                cin >> itemLength;
                cout << "\nEnter the item width: ";
                cin >> itemWidth;
                cout << "\nEnter the item height: ";
                cin >> itemHeight;
                cout << "\nEnter the item type: ";
                cin >> itemType;

                addItemToFridge(userList, kitchenMasterTest, normalItem, sectionTest);
                // Need to update section volume after adding. 
                userList.saveToFile();
                displayMenu();
                break;
            }

            // Show current items
            case 2:
            {
                cout << "\nTO IMPLEMENT user's current items and their info\n";
                displayMenu();
                break;
            }

            // Show expiration dates
            case 3:
            {
                cout << "\nTO IMPLEMENT all user's expiration date for food\n";
                displayMenu();
                break;
            }

            // Remaining space, includes requesting/giving space options
            case 4:
            {
                cout << "\nTO IMPLEMENT things like request/give space, see "
                << "remaining space.\n";

                displayMenu();
                break;
            }

            // Edit profile
            case 5:
            {
                cout << "\nTO IMPLEMENT profile function\n";
                
                displayMenu();
                break;
            }

            // Check database
            case 6:
            {
                // fridgeDatabase();
                displayMenu();
                break;
            }
            // Log out
            case 7:
            {
                cout << "\nYou have logged out.\n";
                break;
            }

            // User chooses an invalid option
            default:
            {
                displayMenu();
                cout << "\nPlease select an option between 1 and 6.\n";
                break;
            }
        }
    }
}

// Function definition displayDatabase
void fridgeDatabase()
{
    int databaseChoice = 0;

    // Display refrigerator options
    cout << "\n**************************************************************\n"
    << "                           DATABASE                           \n"                        
    << "**************************************************************\n";
    cout << "\nSelect one of the following:\n"
    << "    1: Display database\n"
    << "    2: Add item to database\n"
    << "    3: Go back\n"
    << "Selected: ";
    cin >> databaseChoice;

    // Database choices
    if (databaseChoice == 1)
    {
        cout << "\nTO IMPLEMENT vector of items, including 10 default ones\n";
    }

    else if (databaseChoice == 2)
    {
        cout << "\nTO IMPLEMENT adding item to database, including recent items\n";
    }

    else if (databaseChoice == 3)
    {
        // Leave blank
    }

    else 
    {
        cout << "\nPlease input a valid option: ";
    }

}

// Function definition addFridgeChoices
void addFridgeChoices()
{
    int addFridgeChoice = 0;
    string friendCode;

    // Display refrigerator options
    cout << "\n**************************************************************\n"
    << "                       ADD REFRIGERATOR                       \n"                     
    << "**************************************************************\n";
    cout << "\nSelect one of the following:\n"
    << "    1: Input dimensions\n"
    << "    2: Input code\n"
    << "    3: Go back\n"
    << "Selected: ";
    cin >> addFridgeChoice;

    if (addFridgeChoice == 1)
    {
        cout << "\nTO IMPLEMENT L X W X H\n";
    }

    else if (addFridgeChoice == 2)
    {
        cout << "\nEnter the code: ";
        cin >> friendCode; 
        cout << "\nTO IMPLEMENT CONTAINER OF FAKE FRIEND CODES\n";
    }

    else if (addFridgeChoice == 3)
    {
        // Leave blank
    }

    else 
    {
        cout << "\nPlease input a valid option: ";
    }
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