#include <iostream>
#include <fstream>
using namespace std;

void showMenu()
{
    cout << "\n -----Password Manager--------\n";
    cout << "1.  Add Passoword : \n";
    cout << "2. View Password: \n";
    cout << "3. Search Password: \n";
    cout << "4. Exit \n";
    cout << "Enter your choice: ";

}


void addPassword()
{
    string website , username , password;
    cout << "Enter your Website: ";
    cin >> website;

    cout << "Enter your username: ";
    cin >> username;


    cout << "Enter your password: ";
    cin >> password;

    ofstream file("password.txt" , ios::app);

    file << website << "|" << username << "|" << password << endl;

    file.close();

    cout << "Password has been saved Successfully. \n";
}


void viewPassword()
{
    ifstream file("password.txt");
    if(!file)
    {
        cout << "File can't be found and no password has been saved yet: \n";
        return;
    }

    string line;

    cout << "\n===== Saved Password ======\n";

    while (getline(file , line))
    {
        int pos1 = line.find('|');
        int pos2 = line.rfind('|');

        string website = line.substr(0 , pos1);
        string username = line.substr(pos1 + 1 , pos2 - pos1 - 1);
        string password = line.substr(pos2 + 1);

        cout << "------------------------\n";
        cout << "Website : " << website << endl;
        cout << "Username : " << username << endl;
        cout << "Password : " << password << endl;

    }

    file.close();
}

void searchPassword()
{
    string searchKey;
    cout << "Enter the website to search : ";
    cin >> searchKey;

    ifstream file("password.txt");
    if(!file)
    {
        cout << "The file doesnt exist and no data is present: \n";
        return;
    }

    string line;
    bool found = false;

    while(getline(file , line))
    {
        int pos1 = line.find('|');
        int pos2 = line.rfind('|');

        string website = line.substr(0 , pos1);
        string username = line.substr(pos1 + 1 , pos2 - pos1 - 1);
        string password = line.substr(pos2 + 1);

        if(website == searchKey)
        {
            cout << "=========Match Found==========\n";
            cout << "Website : " << website << endl;
            cout << "Username : " << username << endl;
            cout << "Password : " << password << endl;
            found = true;
            break;

        } 
    }
    file.close();
    if(!found)
    {
        cout << "No password  was found: \n";
    }

}


void deletePassword()
{
    string searchKey;

    cout << "Enter the website to delete: ";
}


int main()
{
    int choice;

    do 
    {
        showMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            addPassword();
            break;
        
        case 2: 
            viewPassword();
            break;
        
        case 3: 
            searchPassword();
            break;
        
        case  4:
            cout << "Exiting program: \n";
            break;
        default:
            cout << "Invalid Choice: \n";
            break;
        }
    }while(choice != 4);

    return 0;
}