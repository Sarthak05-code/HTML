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

    file << website << " | " << username << " | " << password << endl;

    file.close();

    cout << "Password has been saved Successfully. \n";
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
            cout <<"View Password Selected: \n";
            break;
        
        case 3: 
            cout <<"Password Search Selected: \n";
            break;
        
        case  4:
            cout << "Exiting program: \n";
            break;
        default:
            cout << "Invalid Choice: \n";
        }
    }while(choice != 4);

    return 0;
}