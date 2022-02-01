#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

class student
{
private:
    long rollno;
    int standard;
    char sec, name[25];

public:
    void input()
    {
        cout << "Enter Roll Number Of Student = ";
        cin >> rollno;
        cout << "Enter Name Of Student = ";
        cin.ignore();
        cin.get(name, 25);
        cout << "Enter the Class Of Student = ";
        cin >> standard;
        cout << "Enter Section Of Student = ";
        cin >> sec;
    }

    void output()
    {
        cout << "Roll Number ------- " << rollno << endl;
        cout << "Name        ------- " << name << endl;
        cout << "Standard    ------- " << standard << endl;
        cout << "Section     ------- " << sec << endl;
    }

    int getroll()
    {
        return rollno;
    }

    student()
    {
        rollno = 0;
        strcpy(name, "None");
        sec = '0';
    }
};

void insert()
{
    fstream fout("school.txt", ios::out | ios::app | ios::binary);
    if (!fout)
    {
        cout << "file not found\n";
    }
    else
    {
        cout << "Entering Data\n";
        student s1;
        s1.input();
        fout.write((char *)&s1, sizeof(s1));
        fout.close();
    }
}

void displayall()
{
    fstream fin("school.txt", ios::in | ios::binary);
    if (!fin)
    {
        cout << "file not found\n";
    }
    else
    {
        student s;
        cout << "Displaying All Data\n";
        while (!fin.eof())
        {
            fin.read((char *)&s, sizeof(s));
            if (fin.eof())
            {
                break;
            }
            s.output();
        }
        fin.close();
    }
}

void modify()
{
    int x, ans1;
    student s2, s;
    char confirm = 'a';
    cout << "Enter Roll Number To modify = ";
    cin >> x;
    system("cls");
    fstream real("school.txt", ios::in | ios::binary);
    fstream temp("temp.txt", ios::out | ios::binary);
    real.read((char *)&s2, sizeof(s2));
    while (!real.eof())
    {
        if (s2.getroll() == x)
        {
            s2.output();
            cout << "\n\nAre you sure you want to Modify this data [Y/N] = ";
            cin >> confirm;
            system("cls");
            if (confirm != 'Y' && confirm != 'y')
            {
                temp.write((char *)&s2, sizeof(s2));
            }
        }
        else
        {
            temp.write((char *)&s2, sizeof(s2));
        }
        real.read((char *)&s2, sizeof(s2));
    }
    real.close();
    temp.close();
    remove("school.txt");
    rename("temp.txt", "school.txt");
    if (confirm == 'y' || confirm == 'Y')
    {
        cout << "1. Modify Data\n2. Delete Data\nEnter Your Choice = ";
        cin >> ans1;
        if (ans1 == 1)
        {
            fstream fio("school.txt", ios::out | ios::binary | ios::app);
            s.input();
            fio.write((char *)&s, sizeof(s));
            cout << "Data Modifying\n\nModified Data\n";
            s.output();
            fio.close();
        }
        else if (ans1 == 2)
        {
            cout << "\nDeletion Successful\n";
        }
    }
}
