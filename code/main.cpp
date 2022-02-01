#include "school.h"
#include "login.h"

using namespace std;

int main()
{
    int a, choice, found = 0;
    char ans;
    login();
    do
    {
        system("cls");
        cout << "1. ---- Enter Data\n";
        cout << "2. ---- Display All Data\n";
        cout << "3. ---- Search And Modify Data\n";
        cout << "4. ---- Delete All Data\n";
        cout << "Enter Your Choice = ";
        cin >> choice;
        system("cls");
        switch (choice)
        {
        case 1:
        {
            insert();
            break;
        }
        case 2:
        {
            displayall();
            break;
        }
        case 3:
        {
            modify();
            break;
        }
        case 4:
        {
            char ch;
            cout << "Are You Sure You Want to delete all data (Y/N) = ";
            cin >> ch;
            if (ch == 'Y' || ch == 'y')
            {
                remove("school.txt");
                cout << "\nAll Data Deleted\n";
            }
            break;
        }
        default:
            cout << "Invalid Choice\n";
            break;
        }
        cout << "\nDo You Want to cotinue (Y/N) = ";
        cin >> ans;
    } while (ans == 'Y' || ans == 'y');
    return 0;
}
