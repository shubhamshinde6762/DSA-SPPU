#include <bits/stdc++.h>
using namespace std;

class Student
{
    int rollNo;
    char name[20];
    char division[20];
    char address[20];

public:
    Student() : rollNo(-1), name("-1"), division("-1"), address("-1") {}
    void getStudentDetails()
    {
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter division: ";
        cin >> division;
        cout << "Enter roll number: ";
        cin >> rollNo;
        cout << "Enter address: ";
        cin >> address;
    }
    void showStudentDetails()
    {
        cout << "Roll number: " << rollNo << endl;
        cout << "Name: " << name << endl;
        cout << "Address: " << address << endl;
        cout << "Division: " << division << endl;
    }
    friend class StudentDB;
};

class StudentDB
{
    Student s;

public:
    StudentDB()
    {
        ifstream obj;
        obj.open("hash.dat", ios::ate | ios::binary);

        if (obj.tellg() < 10 * sizeof(s))
        {
            ofstream obj2;
            obj2.open("temp.dat", ios::out | ios::binary);
            for (int i = 0; i < 10; i++)
                obj2.write(reinterpret_cast<char *>(&s), sizeof(s));
            obj2.close();
            obj.close();

            remove("hash.dat");
            rename("temp.dat", "hash.dat");
        }
        else
            obj.close();
    }

    int getHash(int roll)
    {
        return roll % 10;
    }

    int saveStudentData()
    {
        s.getStudentDetails();
        fstream obj;
        obj.open("hash.dat", ios::in | ios::out | ios::binary);

        if (!obj)
        {
            cout << "File open Error" << endl;
            return 0;
        }
        obj.seekp(sizeof(s) * getHash(s.rollNo), ios::beg);
        obj.write(reinterpret_cast<char *>(&s), sizeof(s));
        obj.close();
    }
    void displayStudentData()
    {
        ifstream obj;
        obj.open("hash.dat", ios::in | ios::binary);

        if (!obj)
        {
            cout << "File open Error" << endl;
            return;
        }

        obj.read(reinterpret_cast<char *>(&s), sizeof(s));
        while (!obj.eof())
        {
            s.showStudentDetails();
            obj.read(reinterpret_cast<char *>(&s), sizeof(s));
        }

        obj.close();
    }
    void searchStudentDetails(const int roll)
    {
        ifstream obj;
        obj.open("hash.dat", ios::in | ios::binary);

        obj.seekg(sizeof(s) * getHash(roll));
        if (!obj)
        {
            cout << "File open Error" << endl;
            return;
        }

        obj.read(reinterpret_cast<char *>(&s), sizeof(s));
        obj.close();
        if (s.rollNo != -1)
        {
            s.showStudentDetails();
            return;
        }

        cout << "Record Not Found" << endl;
    }
    void deleteStudentDetails(int roll)
    {
        fstream obj;
        obj.open("hash.dat", ios::in | ios::out | ios::binary);

        if (!obj)
        {
            cout << "File open Error" << endl;
            return;
        }

        int pos = getHash(roll) * sizeof(Student);
        obj.seekg(pos, ios::beg);

        Student temp;
        obj.read(reinterpret_cast<char *>(&temp), sizeof(Student));

        if (temp.rollNo == roll)
        {
            obj.seekp(pos, ios::beg);
            Student empty;
            obj.write(reinterpret_cast<char *>(&empty), sizeof(Student));
            cout << "Record deleted successfully." << endl;
        }
        else
            cout << "Record not found." << endl;

        obj.close();
    }
};

int main()
{
    int ch, ch1 = 1;
    StudentDB obj;
    string data;
    int roll;
    do
    {
        cout << "===============================" << endl;
        cout << "1-Add Student Data" << endl;
        cout << "2-Display all students" << endl;
        cout << "3-Search Student Data" << endl;
        cout << "4-Delete Student Data" << endl;
        cout << "5-Exit" << endl;
        cout << "===============================" << endl;
        cout << "Enter your choice" << endl;
        cin >> ch;

        switch (ch)
        {
        case 1:
            obj.saveStudentData();
            break;

        case 2:
            obj.displayStudentData();
            break;

        case 3:
            cout << "Enter the name : "
                 << " ";
            cin >> roll;
            cout << endl;
            obj.searchStudentDetails(roll);
            break;

        case 4:
            cout << "Enter the name : "
                 << " ";
            cin >> roll;
            cout << endl;
            obj.deleteStudentDetails(roll);
            break;
        case 5:
            cout << "Exiting..." << endl;
            exit(0);
            break;
        default:
            cout << "Enter a Valid Choice " << endl;
            break;
        }
    } while (ch1 == 1);

    return 0;
}