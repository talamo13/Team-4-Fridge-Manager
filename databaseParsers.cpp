#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <filesystem>

// #include "refrigeratorClasses.cpp"

using namespace std;

class User
{
public:
    User() : email(""), password(""), name("")
    {
        
    }

    User(const User& other)
        : email(other.email), password(other.password), name(other.name),
          associatedAllergies(other.associatedAllergies) 
    {
        
    }

    User(const string& email, const string& password, const string& name, 
         vector<string> associatedAllergies) : email(email),
         password(password), name(name), associatedAllergies(associatedAllergies)
    {
        // should be empty, Users can only be created when all values are filled
    }

    void setEmail(const string& newEmail)
    {
        email = newEmail;
    }

    void setPassword(const string& newPassword)
    {
        password = newPassword;
    }

    string getEmail() const
    {
        return email;
    }

    string getPassword() const
    {
        return password;
    }

    string getName() const
    {
        return name;
    }

    vector<string> getAllergies() const
    {
        return associatedAllergies;
    }

    void addAllergy(const string& newAllergy)
    {
        associatedAllergies.push_back(newAllergy);
    }
    
    void deleteAllergy(const string& allergy)
    {
        auto it = find(associatedAllergies.begin(), associatedAllergies.end(), allergy);

        if (it != associatedAllergies.end())
        {
            associatedAllergies.erase(it);
        }
        else
        {
            cout << "Allergy not found." << endl;
        }
    }

private:
    string email;
    string password;
    string name;

    vector<string> associatedAllergies;
};

class Item
{
public:
    Item(const string& name, double length, double width, double height, 
    int expiration, const string& type) : 
         name(name), length(length), width(width), height(height), expiration(expiration),
         volume(length * width * height), type(type)
    {
        
    }

    void setItemName(const string& itemName)
    {
        name = itemName;
    }
    
    void setDimensions(double l, double w, double h)
    {
        length = l;
        width = w;
        height = h;

        volume = length * width * height;
    } 

    void setExpiration()
    {
        cout << "Enter days until expiration " << name << ": ";
        cin >> expiration;
    }

    string getItemName() const
    {
        return name;
    }

    string getItemType() const 
    {
        return type;
    }

    int getExpiration() const
    {
        return expiration;
    }

    double getLength() const
    {
        return length;
    }

    double getWidth() const
    {
        return width;
    }

    double getHeight() const
    {
        return height;
    }

    double getItemVolume() const
    {
        return volume;
    }

    bool operator==(const Item& other) const
    {
        return (name == other.name);
    }

private:
    string name;
    string type;

    double length;
    double width;
    double height;
    double volume;
    
    int expiration;
};

class Section
{
public:
    Section() : name(""), length(0), width(0), height(0)
    {

    }

    Section(const string& name, const User& owner, double length, double width, 
            double height, vector<Item>& items) : name(name), owner(owner), 
            length(length), width(width), height(height), items(items)
    {
        volume = 0;
        volume = length * width * height;


        usedVolume = 0;
        for (const auto& item : items)
        {
            usedVolume += item.getItemVolume();
        }
    }

    Section(const Section& other) : name(other.name), owner(other.owner),
          length(other.length), width(other.width), height(other.height),
          volume(other.volume), usedVolume(other.usedVolume), items(other.items) 
    {
        
    }

    void setSectionName(const string& sectionName)
    {
        name = sectionName;
    }

    void setSectionDimensions(double l, double w, double h)
    {
        length = l;
        width = w;
        height = h;

        volume = length * width * height;
    }
    
    void updateSectionVolume()
    {
        volume = 0;

        for (const auto& item : items)
        {
            volume += item.getItemVolume();
        }
    }

    void setSectionOwner(const User& sectionOwner)
    {
        owner = sectionOwner;
    }

    string getSectionName() const
    {
        return name;
    }

    User getSectionOwner() const
    {
        return owner;
    }

    double getSectionVolume() const
    {
        return volume;
    }

    double getLength() const
    {
        return length;
    }
    
    double getWidth() const
    {
        return width;
    }

    double getHeight() const
    {
        return height;
    }
    
    double getUsedVolume() const 
    {
        return usedVolume;
    }

    double getRemainingVolume() const
    {
        return volume - usedVolume;
    }

    vector<Item>& getItems()
    {
        return items;
    }

    void addItem(const Item& item)
    {
        usedVolume += item.getItemVolume();

        if (volume - usedVolume < 0)
        {
            cout << "Storage full, please remove an item." << endl;
            usedVolume -= item.getItemVolume();
        }
        else
        {
            items.push_back(item);
        }
    }

    void removeItem(const Item& itemToDelete)
    {
        auto it = find(items.begin(), items.end(), itemToDelete);

        if (it != items.end())
        {            
            items.erase(it);
            usedVolume -= itemToDelete.getItemVolume();
        }
        else
        {
            cout << "Item not found in the section." << endl;
        }
    }

private:
    string name;
    User owner;

    double length;
    double width;
    double height;
    double volume;

    double usedVolume;

    vector<Item> items;
};

class Fridge
{
public:
    // Fridge() : name(""), length(0.0), width(0.0), height(0.0),
    //            remainingCapacity(0.0), totalCapacity(0.0), sections(), users() {}
    
    Fridge(const string& name, const double length, const double width, const double height, 
           double remainingCapacity, const double totalCapacity, vector<Section>& sections) : 
           name(name), length(length), width(width), height(height),
           totalCapacity(length * width * height), sections(sections)
    {
        for (auto& section : sections)
        {
            users.push_back(section.getSectionOwner());
            
            for (auto& item : section.getItems())
            {
                usedCapacity += item.getItemVolume();
            }
        }
    }

    string getFridgeName() const
    {
        return name;
    }

    double getLength() const
    {
        return length;
    }
    
    double getWidth() const
    {
        return width;
    }

    double getHeight() const
    {
        return height;
    }

    double getUsedCapacity() const
    {
        return usedCapacity;
    }
    
    double getTotalCapacity() const
    {
        return totalCapacity;
    }

    void addItem(Item& item, const string& sectionName)
    {
        for (auto section : sections)
        {
            if (sectionName == section.getSectionName())
            {
                section.addItem(item);
                usedCapacity += item.getItemVolume();
                return;
            }
        }
        cout << "Section does not exist." << endl;
    }

    void removeItem(const string& itemName, const string& sectionName)
    {
        for (auto& section : sections)
        {
            if (sectionName == section.getSectionName())
            {
                for (auto& item : section.getItems())
                {
                    if (item.getItemName() == itemName)
                    {
                        section.removeItem(item); 

                        usedCapacity -= item.getItemVolume();
                        return;
                    }
                }
            }
        }
    }

    vector<Item> getContents() const
    {
        vector<Item> allItems;

        for (auto section : sections)
        {
            for (auto item : section.getItems())
            {
                allItems.push_back(item);
            }
        }

        return allItems;
    }

    vector<User>& getUsers()
    {
        return users;
    }

    vector<Section>& getSections()
    {
        return sections;
    }

private:
    string name;

    double length;
    double width;
    double height;
    double usedCapacity;
    double totalCapacity;

    vector<Section> sections;
    vector<User> users;
};

// master database for users
// opens masterUsers.csv
class UserProfiles
{
public:
    UserProfiles()
    {
        ifstream file(filename);

        listOfUsers.clear();

        string line;

        while(getline(file, line))
        {
            stringstream data(line);
            string email, password, name;
            getline(data, email, ',');
            getline(data, password, ',');
            getline(data, name, ',');
            
            // saves associated allergies to user
            string allergyList;
            vector<string> associatedAllergies;
            getline(data, allergyList, ',');

            stringstream listOfAllergies(allergyList);
            string allergy;
            while(getline(listOfAllergies, allergy, '-'))
            {
                associatedAllergies.push_back(allergy);
            }

            listOfUsers.push_back(User(email, password, name, associatedAllergies));
        }

        file.close();
    }

    void addUser(const string& email, const string& password, const string& name, 
                    vector<string> associatedAllergies)
    {
        for (const auto& user : listOfUsers)
        {
            if (email == user.getEmail())
            {
                cout << email << " is already associated with another user" << endl;
                return;
            }
        }

        listOfUsers.push_back(User(email, password, name, associatedAllergies));
        cout << email << " has been added!" << endl;
    }

    vector<User>& getUsers()
    {
        return listOfUsers;
    }

    void displayUsers() const
    {
        cout << "---------------------------------------------------"<< endl;
        cout << "| Name                 | Email" << endl;
        cout << "---------------------------------------------------" << endl;

        for (const auto& user : listOfUsers)
        {
            cout << "| " << setw(20) << left << user.getEmail()
                << " | " << setw(28) << left << user.getName() << endl;
        }

        cout << "-----------------------------------------------------------------------------" << endl;
    }

    void displayUser(const string& email) const
    {
        for (const auto& user : listOfUsers)
        {
            if (user.getEmail() == email)
            {
                cout << "Name: " << user.getName()
                     << " | Email: " << user.getEmail() 
                     << " | Allergies: ";
                
                for (auto allergy : user.getAllergies())
                {
                    cout << allergy << " ";
                }
                
                cout << endl;
                return;
            }
        }

        cout << email << " does not exist, please create an account." << endl;
    }

    void changePassword(const string& email, const string& newPassword)
    {
        for (auto& user : listOfUsers)
        {
            if (user.getEmail() == email)
            {
                user.setPassword(newPassword);
                cout << "Password successfully changed!" << endl;
                return;
            }
        }

        cout << email << " does not exist, please create an account." << endl;
    }

    void changeEmail(const string& email, const string& newEmail)
    {
        for (auto& user : listOfUsers)
        {
            if (user.getEmail() == email)
            {
                user.setEmail(newEmail);
                cout << email << " has been updated to " << newEmail << "." << endl;
                return;
            }
        }

        cout << email << " does not exist, please create an account." << endl;
    }

    void deleteUser(const string& email)
    {
        for (auto it = listOfUsers.begin(); it != listOfUsers.end(); it++)
        {
            if (it->getEmail() == email)
            {
                it = listOfUsers.erase(it);
                cout << email << " has been removed." << endl;
                return;
            }
        }

        cout << email << " does not exist." << endl;
    }

    void saveToFile() const
    {
        ofstream file(filename);
        for (const auto& user : listOfUsers)
        {
            file << user.getEmail() << "," << user.getPassword() << "," << user.getName();

            file << "," << user.getAllergies()[0];
            for (size_t i = 1; i < user.getAllergies().size(); i++)
            {
                file << "-" << user.getAllergies()[i];
            }

            file << "\n";
        }
        file.close();
        
        // cout << "Saved to " << filename << endl;
    }

private:
    string filename = "masterUsers.csv";
    vector<User> listOfUsers;
};

// database of items
// opens itemDatabase.csv
class ItemsDatabase
{
public:
    ItemsDatabase()
    {
        ifstream file(filename);

        listOfItems.clear();

        string line;

        while(getline(file, line))
        {
            stringstream data(line);
            string itemName, strLength, strWidth, strHeight, 
            strExpiration, itemType;
            getline(data, itemName, ',');
            getline(data, strLength, ',');
            getline(data, strWidth, ',');
            getline(data, strHeight, ',');
            getline(data, strExpiration, ',');
            getline(data, itemType, ',');

            double length = stod(strLength);
            double width = stod(strWidth);
            double height = stod(strHeight);
            int expiration = stoi(strExpiration);

            listOfItems.push_back(Item(itemName, length, width, height, expiration, itemType));
        }

        file.close();
    }

    vector<Item>& getListOfItems()
    {
        return listOfItems;
    }

    void addItem(Item& newItem)
    {
        listOfItems.push_back(newItem);
    }

    void displayItems() const
    {
        cout << "-----------------------------------------------------------------------------------"<< endl;
        cout << "| Item                 | Volume               | Days to Expire         | Type" << endl;
        cout << "-----------------------------------------------------------------------------------" << endl;

        for (const auto& item : listOfItems)
        {
            cout << "| " << setw(20) << left << item.getItemName()
                << " | " << setw(20) << left << item.getItemVolume() 
                << " | " << setw(22) << left << item.getExpiration()
                << " | " << setw(20) << left << item.getItemType() << endl;
        }

        cout << "---------------------------------------------------------------------------------" << endl;
    }

    void displayItem(const string& itemName) const
    {
        for (const auto& item : listOfItems)
        {
            if (item.getItemName() == itemName)
            {
                cout << "Item: " << item.getItemName()
                     << " | Volume: " << item.getItemVolume() 
                     << " | Days to Expire: " << item.getExpiration()
                     << " | Type: " << item.getItemType() << endl;
                return;
            }
        }

        cout << itemName << " does not exist, please add it to the database." << endl;
    }

    void saveToFile() const
    {
        ofstream file(filename);
        for (const auto& item : listOfItems)
        {
            file << item.getItemName() << "," << item.getLength() << "," << item.getWidth() 
                 << "," << item.getHeight() << "," << item.getExpiration()
                 << "," << item.getItemType() << "\n";
        }
        file.close();
    }

private:
    string filename = "itemDatabase.csv";
    vector<Item> listOfItems;
};

class FridgesDatabase
{
public:
    FridgesDatabase(ItemsDatabase& databaseOfItems) : databaseOfItems(databaseOfItems)
    {
        ifstream file(filename);

        listOfFridges.clear();

        UserProfiles savedUsers;

        string line;

        while(getline(file, line))
        {
            stringstream data(line);
            string fridgeName, strLength, strWidth, strHeight, 
                   strRemainingCapacity, strTotalCapacity;
            getline(data, fridgeName, ',');
            getline(data, strLength, ',');
            getline(data, strWidth, ',');
            getline(data, strHeight, ',');
            getline(data, strRemainingCapacity, ',');
            getline(data, strTotalCapacity, ',');

            double length = stod(strLength);
            double width = stod(strWidth);
            double height = stod(strHeight);
            double remainingCapacity = stod(strRemainingCapacity);
            double totalCapacity = stod(strTotalCapacity);

            // reads data from Fridge (possibly will allow multiple fridge creations)
            ifstream fridgeFile("Fridges/" + fridgeName + ".csv");

            string fridgeLine;
            
            vector<Section> associatedSections;
            associatedSections.clear();
            
            while(getline(fridgeFile, fridgeLine))
            {
                stringstream fridgeData(fridgeLine);
                string sectionName, sectionOwner, strSectionLength, strSectionWidth, 
                       strSectionHeight;
                getline(fridgeData, sectionName, ',');
                getline(fridgeData, sectionOwner, ',');
                getline(fridgeData, strSectionLength, ',');
                getline(fridgeData, strSectionWidth, ',');
                getline(fridgeData, strSectionHeight, ',');

                double sectionLength = stod(strSectionLength);
                double sectionWidth = stod(strSectionWidth);
                double sectionHeight = stod(strSectionHeight);

                string items;
                vector<string> addedItems;
                vector<Item> associatedItems;
                associatedItems.clear();
                getline(fridgeData, items, ',');

                stringstream listOfItems(items);
                string item;
                while(getline(listOfItems, item, '-'))
                {
                    for (const auto& existingItem : databaseOfItems.getListOfItems())
                    {
                        if(item == existingItem.getItemName())
                        {
                            associatedItems.push_back(existingItem);
                            addedItems.push_back(existingItem.getItemName());
                        }
                    }   
                    
                    if (item != "None")
                    {
                        auto it = find(addedItems.begin(), addedItems.end(), item);

                        if (it == addedItems.end())
                        {
                            stringstream itemNotDatabase(item);
                            string itemName, strItemLength, strItemWidth, strItemHeight, strItemExpiration, itemType;
                            getline(itemNotDatabase, itemName, '~');
                            getline(itemNotDatabase, strItemLength, '~');
                            getline(itemNotDatabase, strItemWidth, '~');
                            getline(itemNotDatabase, strItemHeight, '~');
                            getline(itemNotDatabase, strItemExpiration, '~');
                            getline(itemNotDatabase, itemType, '~');
                            
                            double itemLength = stod(strItemLength);
                            double itemWidth = stod(strItemWidth);
                            double itemHeight = stod(strItemHeight);
                            int itemExpiration = stoi(strItemExpiration);
                            
                            associatedItems.push_back(Item(itemName, itemLength, itemWidth, itemHeight, itemExpiration, itemType));
                        }
                    } 
                }
                
                User sectionUser;

                for (const auto& user : savedUsers.getUsers())
                {
                    if(sectionOwner == user.getEmail())
                    {
                        sectionUser = user;
                    }
                }

                associatedSections.push_back(Section(sectionName, sectionUser, sectionLength, sectionWidth, sectionHeight,
                        associatedItems));
            }
            listOfFridges.push_back(Fridge(fridgeName, length, width, height,
                                        remainingCapacity, totalCapacity, associatedSections));
            fridgeFile.close();
        }

        file.close();
    }

    vector<Fridge>& getFridges()
    {
        return listOfFridges;
    }

    void saveToFile()
    {
        ofstream file(filename);

        for (auto& fridge : listOfFridges)
        {
            file << fridge.getFridgeName() << "," << fridge.getLength() << "," 
                 << fridge.getWidth() << "," << fridge.getHeight() << "," 
                 << fridge.getUsedCapacity() << "," << fridge.getTotalCapacity() << "\n";

        }
        
        file.close();
    }

private:
    ItemsDatabase databaseOfItems;
    string filename = "listOfFridges.csv";
    vector<Fridge> listOfFridges;
};