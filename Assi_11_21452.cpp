#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Student
{
private:
    int rollNumber;
    string name;
    string division;
    string address;

public:
    Student(int roll, const string &n, const string &div, const string &addr)
        : rollNumber(roll), name(n), division(div), address(addr) {}

    int getRollNumber() const { return rollNumber; }
    string getName() const { return name; }
    string getDivision() const { return division; }
    string getAddress() const { return address; }

    void write(ofstream &file) const
    {
        file.write(reinterpret_cast<const char *>(this), sizeof(Student));
    }

    void read(ifstream &file)
    {
        file.read(reinterpret_cast<char *>(this), sizeof(Student));
    }
};

class StudentDatabase
{
private:
    string filename;

public:
    StudentDatabase(const string &fname) : filename(fname) {}

    void addStudentRecord(const Student &student)
    {
        ofstream file(filename, ios::app | ios::binary);
        if (!file)
        {
            cerr << "Error opening file." << endl;
            return;
        }

        student.write(file);
        cout << "Student record added successfully." << endl;

        file.close();
    }

    void deleteStudentRecord(int rollNumber)
    {
        ifstream inFile(filename, ios::binary);
        ofstream outFile("temp.dat", ios::binary);

        if (!inFile || !outFile)
        {
            cerr << "Error opening file." << endl;
            return;
        }

        bool found = false;
        Student student(0, "", "", "");
        while (!inFile.eof())
        {
            student.read(inFile);
            if (inFile.eof())
                break;

            if (student.getRollNumber() != rollNumber)
            {
                student.write(outFile);
            }
            else
            {
                found = true;
            }
        }

        inFile.close();
        outFile.close();

        if (found)
        {
            remove(filename.c_str());
            rename("temp.dat", filename.c_str());
            cout << "Student record deleted successfully." << endl;
        }
        else
        {
            cout << "Student record not found." << endl;
        }
    }

    void displayStudentRecord(int rollNumber)
    {
        ifstream file(filename, ios::binary);

        if (!file)
        {
            cerr << "Error opening file." << endl;
            return;
        }

        bool found = false;
        Student student(0, "", "", "");
        while (!file.eof())
        {
            student.read(file);
            if (file.eof())
                break;

            if (student.getRollNumber() == rollNumber)
            {
                found = true;
                cout << "Roll Number: " << student.getRollNumber() << endl;
                cout << "Name: " << student.getName() << endl;
                cout << "Division: " << student.getDivision() << endl;
                cout << "Address: " << student.getAddress() << endl;
                break;
            }
        }

        if (!found)
        {
            cout << "Student record not found." << endl;
        }

        file.close();
    }
};

int main()
{
    StudentDatabase database("student_records.dat");

    int choice;
    do
    {
        cout << "\nMenu:\n";
        cout << "1. Add student record\n";
        cout << "2. Delete student record\n";
        cout << "3. Display student record\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int roll;
            string name, div, addr;
            cout << "Enter roll number: ";
            cin >> roll;
            cin.ignore();
            cout << "Enter name: ";
            getline(cin, name);
            cout << "Enter division: ";
            getline(cin, div);
            cout << "Enter address: ";
            getline(cin, addr);
            Student newStudent(roll, name, div, addr);
            database.addStudentRecord(newStudent);
            break;
        }
        case 2:
        {
            int rollToDelete;
            cout << "Enter the roll number of the student to delete: ";
            cin >> rollToDelete;
            database.deleteStudentRecord(rollToDelete);
            break;
        }
        case 3:
        {
            int rollToDisplay;
            cout << "Enter the roll number of the student to display: ";
            cin >> rollToDisplay;
            database.displayStudentRecord(rollToDisplay);
            break;
        }
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
