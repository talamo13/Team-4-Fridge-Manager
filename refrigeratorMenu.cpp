#include <iostream>
#include <algorithm>
#include <cmath> // for rounding
#include "databaseParsers.cpp"
using namespace std;

// Function definitions
void addItemToFridge(UserProfiles&, Fridge&, Item&, Section&, vector<Section>& userSections);

// displayMenu
void displayMenu()
{
    cout << "\n**************************************************************\n"
    << "                          MAIN MENU\n"
    << "**************************************************************\n";
	cout << "\nSelect one of the following:\n"
		<< "    1: Add item\n"
		<< "    2: Remove item\n"
		<< "    3: Show expiration dates\n"
		<< "    4: Show current items\n"
		<< "    5: View profile\n"
		<< "    6: Log out\n";
}

// Function definition selectChoices
void selectChoices(UserProfiles& userList, User& user, ItemsDatabase& savedItems, 
FridgesDatabase& fridges, Fridge& kitchenMasterTest, vector<Section> userSections)
{
    // Variables
    int choice = 0;
    vector<pair<pair<string, string>, int>> showExpirations;
    Section* selectedSection = &userSections[0];

    while (choice != 6)
    {
        cout << "\nSelect an option: "; 
        cin >> choice; 
        cin.ignore();
        
        switch (choice)
        {
            // Add an item
            case 1: 
            {
                // Variables
                bool noFoundSection = true, alreadyRegistered = false;
                string givenSection, itemName, itemType;
                double itemLength, itemWidth, itemHeight; 
                int itemExpiration = 0, sectionCounter = 0, registeredChoice = 3,
                addToDatabase = 0;
                
                while (noFoundSection)
                {
                    cout << "\nWhich section would you like to add to?\n"
                         << "-------Available Sections-------\n";

                    for (const auto& sections : userSections)
                    {
                        cout << sections.getSectionName() << endl;
                    }   

                    cout << "\nEnter section name: ";
                    getline(cin, givenSection);

                    for (size_t i = 0; i < userSections.size(); i++)
                    {
                        if ((givenSection == userSections[i].getSectionName()) && (userSections[i].getSectionOwner().getEmail() == user.getEmail()))
                        {
                            selectedSection = &userSections[i];
                            noFoundSection = false;
                            break;
                        }
                    }

                    if (noFoundSection)
                    {
                        cout << "\nThat is not a valid section. Try again.\n";
                    }         
                }

                // Account for space
                if (selectedSection->getRemainingVolume() <= 0)
                {
                    cout << "\nYou have no free space left. "
                    << "Please remove an item before adding a new one.";
                }
                else 
                {
                    cout << "\nEnter the name of the food: ";
                    getline(cin, itemName);
                    
                    // Check if item is already in database.
                    for (auto& item : savedItems.getListOfItems())
                    {
                        if (itemName == item.getItemName())
                        {
                            cout << "\nThere is a similar item already" 
                            << " registered in the database. Is the information the same?";

                            // Item information.
                            cout << "\nName: " << item.getItemName();
                            cout << "\nType: " << item.getItemType();
                            cout << "\nPhysical Dimensions (inches): " 
                            << item.getLength() << " x " << item.getWidth() << " x "
                            << item.getHeight();
                            cout << "\nDays until Expiration: " << item.getExpiration()
                                 << "\nType 1 if yes, and 2 if no.";
                            
                            do
                            {
                                cout << "\n\nChoice: ";
                                cin >> registeredChoice;
                            } while (registeredChoice != 1 && registeredChoice != 2);

                            if (registeredChoice == 1)
                            {
                                addItemToFridge(userList, kitchenMasterTest, item, *selectedSection, userSections);
                            }
                        }
                    }

                    if (registeredChoice == 2 || registeredChoice == 3)
                    {
                        cout << "\nEnter the item length: ";
                        cin >> itemLength;
                        cout << "\nEnter the item width: ";
                        cin >> itemWidth;
                        cout << "\nEnter the item height: ";
                        cin >> itemHeight;
                        cout << "\nEnter the item type: ";
                        cin >> itemType;
                        cout << "\nEnter how many days until the item expires: ";
                        cin >> itemExpiration;

                        Item givenItem(itemName, itemLength, itemWidth, itemHeight, itemExpiration, itemType);
                        addItemToFridge(userList, kitchenMasterTest, givenItem, *selectedSection, userSections); 

                        // Add item to database option.
                        cout << "\nWould you like to add this item to the database? Type 1 for yes and 2 for no: ";
                        do
                        {
                            cout << "\n\nChoice: ";
                            cin >> addToDatabase;
                        } while (addToDatabase != 1 && addToDatabase != 2);

                        if (addToDatabase == 1)
                        {
                            savedItems.addItem(givenItem);
                            cout << "\n" << itemName << " has been added to the database.";

                            ofstream fridgeFile("Fridges/KitchenMaster.csv");

                            for (auto& section : kitchenMasterTest.getSections())
                            {
                                fridgeFile << section.getSectionName() << ",";

                                if (section.getSectionOwner().getEmail() == "")
                                {
                                    fridgeFile << "None," << section.getLength() << "," << section.getWidth() << ","
                                                << section.getHeight();
                                }
                                else
                                {
                                    fridgeFile << section.getSectionOwner().getEmail() << "," 
                                                << section.getLength() << "," << section.getWidth() << ","
                                                << section.getHeight();
                                }
                                
                                if (section.getItems().size() == 0)
                                {
                                    fridgeFile << ",None";
                                }
                                else
                                {
                                    vector<Item> itemInSection = section.getItems();


                                    fridgeFile << "," << itemInSection[0].getItemName() 
                                                    << "~" << itemInSection[0].getLength()
                                                    << "~" << itemInSection[0].getWidth()
                                                    << "~" << itemInSection[0].getHeight()
                                                    << "~" << itemInSection[0].getExpiration()
                                                    << "~" << itemInSection[0].getItemType();

                                    for (size_t i = 1; i < itemInSection.size(); i++)
                                    {
                                        fridgeFile << "-" << itemInSection[i].getItemName() 
                                                    << "~" << itemInSection[i].getLength()
                                                    << "~" << itemInSection[i].getWidth()
                                                    << "~" << itemInSection[i].getHeight()
                                                    << "~" << itemInSection[i].getExpiration()
                                                    << "~" << itemInSection[i].getItemType();
                                        
                                    }
                                }
                                fridgeFile << "\n";
                            } 
                            
                            fridgeFile.close();
                        }
                        else
                        {
                            cout << "\n" << itemName << " will not be added to the database.";

                            ofstream fridgeFile("Fridges/KitchenMaster.csv");

                            for (auto& section : kitchenMasterTest.getSections())
                            {
                                fridgeFile << section.getSectionName() << ",";

                                if (section.getSectionOwner().getEmail() == "")
                                {
                                    fridgeFile << "None," << section.getLength() << "," << section.getWidth() << ","
                                                << section.getHeight();
                                }
                                else
                                {
                                    fridgeFile << section.getSectionOwner().getEmail() << "," 
                                                << section.getLength() << "," << section.getWidth() << ","
                                                << section.getHeight();
                                }
                                
                                if (section.getItems().size() == 0)
                                {
                                    fridgeFile << ",None";
                                }
                                else
                                {
                                    vector<Item> itemInSection = section.getItems();


                                    fridgeFile << "," << itemInSection[0].getItemName() 
                                                    << "~" << itemInSection[0].getLength()
                                                    << "~" << itemInSection[0].getWidth()
                                                    << "~" << itemInSection[0].getHeight()
                                                    << "~" << itemInSection[0].getExpiration()
                                                    << "~" << itemInSection[0].getItemType();

                                    for (size_t i = 1; i < itemInSection.size(); i++)
                                    {
                                        fridgeFile << "-" << itemInSection[i].getItemName() 
                                                    << "~" << itemInSection[i].getLength()
                                                    << "~" << itemInSection[i].getWidth()
                                                    << "~" << itemInSection[i].getHeight()
                                                    << "~" << itemInSection[i].getExpiration()
                                                    << "~" << itemInSection[i].getItemType();
                                        
                                    }
                                }
                                fridgeFile << "\n";
                            } 
                            
                            fridgeFile.close();
                        }
                    }
                }
                displayMenu();
                break;
            }

            // Remove an item.
            case 2:
            {
            // Variables
                bool noFoundSection = true, foundItem = false;
                string givenSection, itemName;
                int itemExpiration = 0, sectionCounter = 0, registeredChoice = 0;
                Item toRemove("placeholder", 0, 0, 0, 0, "placeholder");

                while (noFoundSection)
                {
                    cout << "\nWhich section would you like to remove from? \n";

                    for (const Section sections : userSections)
                    {
                        cout << sections.getSectionName() << endl;
                    }   

                    cout << "\nEnter its name: ";
                    getline(cin, givenSection);

                    for (size_t i = 0; i < userSections.size(); i++)
                    {
                        if (userSections[i].getSectionOwner().getEmail() == user.getEmail())
                        {
                            selectedSection = &userSections[i];
                            noFoundSection = false;
                            break;
                        }
                    }

                    if (noFoundSection)
                    {
                        cout << "\nThere is no section with that name. Try again.";
                    }         
                }

                while (!foundItem)
                {
                    // Display items
                    if (selectedSection->getItems().size() == 0)
                    {
                        cout << "\nThere are no items in this section."
                        << " Returning to menu.";
                        foundItem = true;
                    }
                    else 
                    {
                        cout << "\nAll items in this section: ";
                        for (auto& item : selectedSection->getItems())
                        {
                            cout << "\n\nName: " << item.getItemName();
                            cout << "\nType: " << item.getItemType();
                            cout << "\nPhysical Dimensions (inches): " 
                            << item.getLength() << " x " << item.getWidth() << " x "
                            << item.getHeight();
                            cout << "\nDays until Expiration: " << item.getExpiration();
                        }
                        
                        cout << "\nEnter the name of the food to remove: ";
                        getline(cin, itemName);

                        for (auto& item : selectedSection->getItems())
                        {
                            if (item.getItemName() == itemName)
                            {
                                // Item information.
                                cout << "\nName: " << item.getItemName();
                                cout << "\nType: " << item.getItemType();
                                cout << "\nPhysical Dimensions (inches): " 
                                << item.getLength() << " x " << item.getWidth() << " x "
                                << item.getHeight();
                                cout << "\nDays until Expiration: " << item.getExpiration();

                                toRemove = item;
                                foundItem = true;
                                break;
                            }
                        }

                        cout << "\n\nAre you sure you want to remove this item?"
                        << " Type 1 to confirm, and 2 to refuse.";
                        do
                        {
                            cout << "\nChoice: ";
                            cin >> registeredChoice;
                        } while (registeredChoice != 1 && registeredChoice != 2);
                    }

                    // Removing the item.
                    if (registeredChoice == 1)
                    {
                        cout << endl << toRemove.getItemName() << " has been removed.";

                        kitchenMasterTest.removeItem(itemName, selectedSection->getSectionName());

                        for (Section& findSection : userSections)
                        {
                            if (findSection.getSectionName() == selectedSection->getSectionName())
                            {
                                findSection.removeItem(toRemove);
                            }
                        }

                        ofstream fridgeFile("Fridges/KitchenMaster.csv");

                        for (auto& section : kitchenMasterTest.getSections())
                        {
                            fridgeFile << section.getSectionName() << ",";

                            if (section.getSectionOwner().getEmail() == "")
                            {
                                fridgeFile << "None," << section.getLength() << "," << section.getWidth() << ","
                                            << section.getHeight();
                            }
                            else
                            {
                                fridgeFile << section.getSectionOwner().getEmail() << "," 
                                            << section.getLength() << "," << section.getWidth() << ","
                                            << section.getHeight();
                            }
                            
                            if (section.getItems().size() == 0)
                            {
                                fridgeFile << ",None";
                            }
                            else
                            {
                                vector<Item> itemInSection = section.getItems();


                                fridgeFile << "," << itemInSection[0].getItemName() 
                                                << "~" << itemInSection[0].getLength()
                                                << "~" << itemInSection[0].getWidth()
                                                << "~" << itemInSection[0].getHeight()
                                                << "~" << itemInSection[0].getExpiration()
                                                << "~" << itemInSection[0].getItemType();

                                for (size_t i = 1; i < itemInSection.size(); i++)
                                {
                                    fridgeFile << "-" << itemInSection[i].getItemName() 
                                                << "~" << itemInSection[i].getLength()
                                                << "~" << itemInSection[i].getWidth()
                                                << "~" << itemInSection[i].getHeight()
                                                << "~" << itemInSection[i].getExpiration()
                                                << "~" << itemInSection[i].getItemType();
                                    
                                }
                            }
                            fridgeFile << "\n";
                        } 
                        
                        fridgeFile.close();
                    }
                    else
                    {
                        cout << "\nThe item will not be removed.";
                    }
                    
                }
                displayMenu();
                break;
            }

            // Show expiration dates.
            case 3:
            {
                // Variables
                string sectOwnerName, sectItemName;
                int sectItemExpiration = 0;

                // Bring all necessary information to vector
                for (auto& sections: kitchenMasterTest.getSections())
                {
                    sectOwnerName = sections.getSectionOwner().getName();
                    for (const auto& items : sections.getItems())
                    {
                        sectItemName = items.getItemName();
                        sectItemExpiration = items.getExpiration();
                        showExpirations.push_back(make_pair(make_pair(
                            sectOwnerName, sectItemName), sectItemExpiration));
                    }
                }

                // Sort by expiration
                sort(showExpirations.begin(), showExpirations.end(), 
                [](const auto& a, const auto& b) { return a.second < b.second; });

                // Print
                for (const auto& pairPart : showExpirations) 
                {
                    cout << "Item Owner: " << pairPart.first.first
                    << ", Item Name: " << pairPart.first.second
                    << ", Days until Expiration: " << pairPart.second << endl;
                }

                showExpirations.clear();
                displayMenu();
                break;
            }

            // Show current items
            case 4:
            {
                // Copied from itemsDatabase class
                cout << "-----------------------------------------------------------------------------------"<< endl;
                cout << "| Item                 | Volume               | Days to Expire         | Type" << endl;
                cout << "-----------------------------------------------------------------------------------" << endl;
                
                for (auto& section : userSections)
                {
                    for (auto& fridgeSection : kitchenMasterTest.getSections())
                    {
                        if (section.getSectionName() == fridgeSection.getSectionName())
                        {
                            for (const auto& item : fridgeSection.getItems())
                            {
                                if (fridgeSection.getItems().size() == 0)
                                {
                                    cout << "\nNo items in " << fridgeSection.getSectionName();
                                }
                                else
                                {
                                    cout << "| " << setw(20) << left << item.getItemName()
                                    << " | " << setw(20) << left << item.getItemVolume() 
                                    << " | " << setw(22) << left << item.getExpiration()
                                    << " | " << setw(20) << left << item.getItemType() << endl;
                                }
                            }
                        }
                    }
                }

                // for (auto& sections: userSections)
                // {
                //     for (const auto& items: sections.getItems())
                //     {
                //         if (sections.getItems().size() == 0)
                //         {
                //             cout << "\nNo items in " << sections.getSectionName();
                //         }
                //         else
                //         {
                //             cout << "| " << setw(20) << left << items.getItemName()
                //             << " | " << setw(20) << left << items.getItemVolume() 
                //             << " | " << setw(22) << left << items.getExpiration()
                //             << " | " << setw(20) << left << items.getItemType() << endl;
                //         }
                //     }
                // }

                displayMenu();
                break;
            }

            // View profile
            case 5:
            {
                double usedSectionSpace = 0;
                cout << "\nName: " << user.getName();
                cout << "\nEmail: " << user.getEmail();
                cout << "\nAllergies: ";
                for (const auto& allergy : user.getAllergies())
                {
                    cout << allergy << " ";
                }
                cout << "\nOwned Section(s): \n\t";
                for (const auto& section : userSections)
                {
                    cout << section.getSectionName() << ": "
                    << "\n\t\tLength: " << section.getLength() << " inches"
                    << "\n\t\tWidth: " << section.getWidth() << " inches"
                    << "\n\t\tHeight: " << section.getHeight() << " inches\n"
                    << round((section.getRemainingVolume()/section.getSectionVolume()) * 100)
                    << "\% space remaining.\n";
                    usedSectionSpace += section.getSectionVolume();
                }

                cout << "Used " << round((usedSectionSpace / kitchenMasterTest.getTotalCapacity()) * 100)
                << "\% of the total fridge space available.\n";

                displayMenu();
                break;
            }

            // Log out
            case 6:
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
void addItemToFridge(UserProfiles& profiles, Fridge& fridge, Item& item, Section& section, vector<Section>& userSections)
{
    if (item.getLength() > section.getLength() || item.getWidth() > section.getWidth() ||
    item.getHeight() > section.getHeight())
    {
        cout << item.getItemName() << " is too large for the " 
        << section.getSectionName() << ". Returning to menu.\n";
        return;
    }

    for (const auto& user : profiles.getUsers())
    {
        for (const auto& allergy: user.getAllergies())
        {
            if (item.getItemName().find(allergy) != string::npos)
            {
                cout << "A user of this fridge is allergic to " << allergy
                << ".\n";
                return;
            }
        }
    }

    for (auto& findSection : fridge.getSections())
    {
         if (findSection.getSectionName() == section.getSectionName())
        {
            findSection.addItem(item);
            cout << item.getItemName() << " was successfully added to the " 
                    << section.getSectionName() << ".\n";
        }
    }

    // section.addItem(item);
    // cout << item.getItemName() << " was successfully added to the " 
    //              << section.getSectionName() << ".\n";

    // for (auto& findSection : fridge.getSections())
    // {
    //     if (findSection.getSectionName() == section.getSectionName())
    //     {
    //         findSection.addItem(item);
    //         cout << item.getItemName() << " was successfully added to the " 
    //              << section.getSectionName() << ".\n";
    //     }
    // }

    // for (auto& section: fridge.getSections())
    // {
    //     cout << section.getSectionName() << ": ";
    //     for (auto& x : section.getItems())
    //     {
    //         cout << x.getItemName() << " ";
    //     }
    //     cout << endl;
    // }

    // update KitchenMaster.csv
    // ofstream fridgeFile("Fridges/KitchenMaster.csv");

    // for (auto& section : fridge.getSections())
    // {
    //     fridgeFile << section.getSectionName() << "," 
    //                        << section.getSectionOwner().getEmail() << "," 
    //                        << section.getLength() << "," << section.getWidth() << ","
    //                        << section.getHeight();


    //     if (section.getItems().size() == 0)
    //     {
    //         fridgeFile << ",None";
    //     }
    //     else
    //     {
    //         ItemsDatabase itemDatabase;
    //         vector<Item> savedItems = itemDatabase.getListOfItems();

    //         vector<Item> itemInSection = section.getItems();

    //         if (find(savedItems.begin(), savedItems.end(), itemInSection[0]) != savedItems.end())
    //         {
    //             fridgeFile << "," << itemInSection[0].getItemName();
    //         }
    //         else
    //         {
    //             fridgeFile << "," << itemInSection[0].getItemName() 
    //                         << "~" << itemInSection[0].getLength()
    //                         << "~" << itemInSection[0].getWidth()
    //                         << "~" << itemInSection[0].getHeight()
    //                         << "~" << itemInSection[0].getExpiration();
    //         }

    //         for (size_t i = 1; i < itemInSection.size(); i++)
    //         {
    //             if (find(savedItems.begin(), savedItems.end(), itemInSection[i]) != savedItems.end())
    //             {
    //                 fridgeFile << "-" << itemInSection[i].getItemName();
    //             }
    //             else
    //             {
    //                 fridgeFile << "-" << itemInSection[i].getItemName() 
    //                             << "~" << itemInSection[i].getLength()
    //                             << "~" << itemInSection[i].getWidth()
    //                             << "~" << itemInSection[i].getHeight()
    //                             << "~" << itemInSection[i].getExpiration();
    //             }
    //         }
    //     }
    //     fridgeFile << "\n";
    // }
    // fridgeFile.close();
}