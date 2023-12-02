/******************************************************************************

Basic User Login

*******************************************************************************/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool logIn(){
    string userName, password, user, pass;
    
    cout << "Enter username: "; 
    cin >> userName;
    cout << "Enter password: ";
    cin >> password;
    
    ifstream read(userName + ".txt");
    getline(read, user);
    getline(read,pass);
    
    if(user == userName && pass == password) {
        return true;
    }
    else {
        return false;
    }
}

int main()
{
    int choices;
    
    cout << "Select an option: "<<endl;
    cout << "-------------------"<<endl;
    cout << "1: Register for Fridge Manager"<<endl;
    cout << "2: Login"<<endl;
    cout << "Your choice: "<<endl;
    cin >> choices;
    
    if (choices == 1) {
        string userName, password;
        
        cout << "New Username:";
        cin >> userName;
        cout << "Password: ";
        cin >> password;
        
        ofstream file;
        file.open(userName + ".txt");
        file << userName << endl << password;
        file.close();
        
        main();
    }
    
    else if (choices == 2){
        bool stat = logIn();
        if(!stat) {
            cout << "Incorrect password, try again"<<endl;
            system("PAUSE");
            return 0;
        }
        else {
            cout << "Login Successful!"<<endl;
            system("PAUSE");
            return 1;
        }
    }
}