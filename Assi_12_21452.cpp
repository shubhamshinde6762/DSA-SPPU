#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Record
{
    int key;
    string data;
};

class DirectAccessFile
{
private:
    string filename;

public:
    DirectAccessFile(const string &fname) : filename(fname) {}

    void addRecord(const Record &record)
    {
        ofstream file(filename, ios::binary | ios::app);
        if (!file)
        {
            cerr << "Error opening file." << endl;
            return;
        }

        file.write(reinterpret_cast<const char *>(&record), sizeof(Record));
        cout << "Record added successfully." << endl;

        file.close();
    }

    void deleteRecord(int key)
    {
        ifstream inFile(filename, ios::binary);
        ofstream outFile("temp.bin", ios::binary);

        if (!inFile || !outFile)
        {
            cerr << "Error opening file." << endl;
            return;
        }

        bool found = false;
        Record record;
        while (inFile.read(reinterpret_cast<char *>(&record), sizeof(Record)))
        {
            if (record.key != key)
            {
                outFile.write(reinterpret_cast<const char *>(&record), sizeof(Record));
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
            rename("temp.bin", filename.c_str());
            cout << "Record deleted successfully." << endl;
        }
        else
        {
            cout << "Record not found." << endl;
        }
    }

    void displayAllRecords()
    {
        ifstream file(filename, ios::binary);
        if (!file)
        {
            cerr << "Error opening file." << endl;
            return;
        }

        Record record;
        while (file.read(reinterpret_cast<char *>(&record), sizeof(Record)))
        {
            cout << "Key: " << record.key << ", Data: " << record.data << endl;
        }

        file.close();
    }
};

int main()
{
    DirectAccessFile directAccessFile("direct_access_file.bin");

    int choice;
    do
    {
        cout << "\nMenu:\n";
        cout << "1. Add record\n";
        cout << "2. Delete record\n";
        cout << "3. Display all records\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            Record newRecord;
            cout << "Enter key: ";
            cin >> newRecord.key;
            cin.ignore();
            cout << "Enter data: ";
            getline(cin, newRecord.data);
            directAccessFile.addRecord(newRecord);
            break;
        }
        case 2:
        {
            int key;
            cout << "Enter the key of the record to delete: ";
            cin >> key;
            directAccessFile.deleteRecord(key);
            break;
        }
        case 3:
            cout << "Displaying all records:\n";
            directAccessFile.displayAllRecords();
            break;
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
