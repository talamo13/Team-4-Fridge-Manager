#include <iostream>
#include <vector>

using namespace std;





class Item 
{
public:
    void setName();
    void setVolume(); // This will ask the user for the items measurements (l,w,h)
    void setExpiration();

    string getName();
    string getExpiration();
    double getVolume();

private:
    string name;
    string expiration;
    double volume;

    // Allows for Fridge object to access private members in 'Item' class
    friend class Fridge;
};

