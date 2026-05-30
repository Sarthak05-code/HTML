#include <iostream>
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
            cout << "Add Password Selected: \n";
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