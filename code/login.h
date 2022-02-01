#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>

using namespace std;

// structure to collect data in form of id password and key
struct info
{
    char id[15], password[15], key[15];
};

/* function to check for validity of username and password for the conditions
1. Don't Use spaces
2. Minimum Number of Characters = 8
3. Use Atleast One Number
4. Use Atleast One UpperCase Character
5. Use Atleast One Special Character*/
int check(char id[], char pass[])
{
    info dat1;
    bool found = false;
    fstream fin("signupdet.txt", ios::in | ios::binary);
    fin.read((char *)&dat1, sizeof(dat1));
    while (!fin.eof())
    {
        if (!strcmp(dat1.id, id) && !strcmp(dat1.password, pass))
        {
            found = true;
            break;
        }
        fin.read((char *)&dat1, sizeof(dat1));
    }
    fin.close();
    if (found)
        return 1;
    bool err1 = false, err2 = false, err3 = false, err4 = false, err5 = true;
    if (strlen(pass) >= 8)
        err1 = true;
    for (int i = 0; i < strlen(pass); i++)
    {
        if (pass[i] >= 65 && pass[i] <= 90) // Uppercase
            err2 = true;
        else if (pass[i] >= 48 && pass[i] <= 57) // Digits
            err3 = true;
        else if ((pass[i] >= 33 && pass[i] <= 47) || (pass[i] >= 58 && pass[i] <= 64) || (pass[i] >= 91 && pass[i] <= 96)) // Special Characters
            err4 = true;
        else if (pass[i] == ' ') // Space
            err5 = false;
    }
    if (!err1 || !err2 || !err3 || !err4 || !err5)
        return 2;
    return 0;
}

/* function to register as a new user and store it in a file,
if a file is not created then it will create a new one */
void signup()
{
    info dat;
    int error;
tryagain:
    cout << "\nRules For Making ID and Password\n";
    cout << "1. Don't Use spaces\n";
    cout << "2. Minimum Number of Characters = 8\n";
    cout << "3. Use Atleast One Number\n";
    cout << "4. Use Atleast One UpperCase Character\n";
    cout << "5. Use Atleast One Special Character\n";
    cout << "6. Don't Forget the Key To Change The ID/Password\n\n";
    cout << "ID            :   ";
    cin.getline(dat.id, 15);
    cout << "Password      :   ";
    cin.getline(dat.password, 15);
    cout << "key           :   ";
    cin.getline(dat.key, 15);
    fstream fout("signupdet.txt", ios::out | ios::binary | ios::app);
    error = check(dat.id, dat.password);
    if (error == 1)
    {
        cout << "Username Already Exists\nTry Again\n";
        strcpy(dat.id, "");
        strcpy(dat.password, "");
        strcpy(dat.key, "");
        goto tryagain;
    }
    if (error == 2)
    {
        cout << "Password Doesn't Fulfill the requirements\nTry Again\n";
        strcpy(dat.id, "");
        strcpy(dat.password, "");
        strcpy(dat.key, "");
        goto tryagain;
    }
    fout.write((char *)&dat, sizeof(dat));
    fout.close();
    cout << "\nSign Up Succesful\n";
}

/* function to change the password or delete an account,
without the key neither action can be completed*/
void forgot()
{
    info dat, dat1;
    int ch, ch1;
    bool found = false;
re:
    cout << "Key           :   ";
    cin.getline(dat.key, 15);
    fstream fin("signupdet.txt", ios::in | ios::binary);
    fstream temp("temp.txt", ios::out | ios::binary);
    fin.read((char *)&dat1, sizeof(dat1));
    while (!fin.eof())
    {
        if (!strcmp(dat1.key, dat.key))
        {
            found = true;
            break;
        }
        else
        {
            temp.write((char *)&dat1, sizeof(dat1));
        }
        fin.read((char *)&dat1, sizeof(dat1));
    }
    fin.close();
    temp.close();
    remove("signupdet.txt");
    rename("temp.txt", "signupdet.txt");
    if (found == 1)
    {
        bool done = false;
        do
        {
            cout << "\n1. Edit Login ID/Password\n";
            cout << "2. Delete Credentials\n";
            cout << "Enter Your Choice = ";
            cin >> ch1;
            cin.ignore(256, '\n');
            if (ch1 == 1)
            {
                signup();
                done = true;
            }
            else if (ch1 == 2)
            {
                cout << "Credentials Deleted\n";
                done = true;
                exit(0);
            }
            else
            {
                cout << "Wrong Choice\n";
            }
        } while (!done);
    }
    else
    {
        cout << "\n****Wrong Key****\n";
        cout << "1. Retry\n";
        cout << "2. Exit\n";
        cout << "Enter Your Choice = ";
        cin >> ch;
        cin.ignore(256, '\n');
        switch (ch)
        {
        case 1:
            goto re;
            break;
        case 2:
            exit(0);
        default:
            cout << "Wrong Choice Exiting...";
            break;
        }
    }
}

/* function to log into using existing user id and password
they are checked by the file from the file created*/
void signin()
{
    info dat, dat1;
    int ch;
    bool found = false;
again:
    cout << "ID            :   ";
    cin.getline(dat.id, 15);
    cout << "Password      :   ";
    cin.getline(dat.password, 15);
    fstream fin("signupdet.txt", ios::in | ios::binary);
    fin.read((char *)&dat1, sizeof(dat1));
    while (!fin.eof())
    {
        if (!strcmp(dat1.id, dat.id) && !strcmp(dat1.password, dat.password))
        {
            found = true;
            break;
        }
        fin.read((char *)&dat1, sizeof(dat1));
    }
    fin.close();
    if (found == 1)
    {
        cout << "\nLogin Succesfull\n";
    }
    else
    {
        cout << "\n****Wrong ID or Password****\n";
        cout << "1. Retry\n";
        cout << "2. Forgot ID/Password\n";
        cout << "3. New User\n";
        cout << "4. Exit\n";
        cout << "Enter Your Choice = ";
        cin >> ch;
        cin.ignore(256, '\n');
        switch (ch)
        {
        case 1:
            goto again;
            break;
        case 2:
            forgot();
            break;
        case 3:
            signup();
            break;
        case 4:
            exit(0);
        default:
            cout << "Wrong Choice Exiting...";
            break;
        }
    }
}

/* function for main menu to select the option
to register, login, change id/password, delete account*/
void login()
{
    int ch;
    cout << "1. Sign up\n";
    cout << "2. Sign in/Log in\n";
    cout << "3. Forgot ID/Password\n";
    cout << "4. Delete Account\n";
    cout << "Enter Your Choice = ";
    cin >> ch;
    cin.ignore(256, '\n');
    switch (ch)
    {
    case 1:
    {
        signup();
        break;
    }
    case 2:
    {
        signin();
        break;
    }
    case 3:
    {
        forgot();
        break;
    }
    case 4:
    {
        forgot();
        break;
    }
    default:
        cout << "Wrong Choice Exiting...";
        break;
    }
}
