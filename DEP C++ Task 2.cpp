#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

class Contact {
    string name, phone_number, cnic;
public:
    Contact(string n = "", string p = "", string c = "") : name(n), phone_number(p), cnic(c) {}
    string getName() const { return name; }
    string getPhoneNumber() const { return phone_number; }
    string getCnic() const { return cnic; }
    void display() const { 
        cout << "Name: " << name << endl; 
        cout << "Phone Number: " << phone_number << endl;
    }

    friend ostream& operator<<(ostream& os, const Contact& contact) {
        os << contact.name << ',' << contact.phone_number << ',' << contact.cnic;
        return os;
    }

    friend istream& operator>>(istream& is, Contact& contact) {
        getline(is, contact.name, ',');
        getline(is, contact.phone_number, ',');
        getline(is, contact.cnic);
        return is;
    }
};

void addContact(vector<Contact>& contacts) {
    string name, phone_number, cnic;
    cout << "Enter Name: "; cin >> name;
    cout << "Enter Phone Number: "; cin >> phone_number;
    cout << "Enter CNIC: "; cin >> cnic;
    contacts.emplace_back(name, phone_number, cnic);
}

void viewContacts(const vector<Contact>& contacts) {
    if (contacts.empty()) {
        cout << "No contacts to display." << endl;
    } else {
        for (const auto& contact : contacts) {
            contact.display();
            cout << "-----------------------" << endl;
        }
    }
}

void deleteContact(vector<Contact>& contacts) {
    string name;
    cout << "Enter the name of the contact to delete: "; cin >> name;
    auto it = remove_if(contacts.begin(), contacts.end(),
                        [&name](const Contact& contact) { return contact.getName() == name; });
    if (it != contacts.end()) contacts.erase(it, contacts.end());
    else cout << "Contact not found." << endl;
}

void saveContactsToFile(const vector<Contact>& contacts, const string& filename) {
    ofstream file(filename);
    if (!file) {
        cout << "Error opening file for writing." << endl;
        return;
    }
    for (const auto& contact : contacts) {
        file << contact << endl;
    }
    file.close();
}

void loadContactsFromFile(vector<Contact>& contacts, const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Error opening file for reading." << endl;
        return;
    }
    contacts.clear();
    Contact contact;
    while (file >> contact) {
        contacts.push_back(contact);
    }
    file.close();
}

void showMenu() {
    cout << "\n**************************************" << endl;
    cout << "*      WELCOME TO CONTACT MANAGER    *" << endl;
    cout << "*------------------------------------*" << endl;
    cout << "* 1. Add New Contact                *" << endl;
    cout << "* 2. View All Contacts              *" << endl;
    cout << "* 3. Delete a Contact               *" << endl;
    cout << "* 4. Save Contacts to File          *" << endl;
    cout << "* 5. Load Contacts from File        *" << endl;
    cout << "* 6. Exit                           *" << endl;
    cout << "*------------------------------------*" << endl;
    cout << "* Please select an option:          *" << endl;
    cout << "**************************************" << endl;
}

int main() {
    vector<Contact> contacts;
    string filename = "contacts.txt";
    int choice;
    
    loadContactsFromFile(contacts, filename);

    do {
        showMenu(); cin >> choice;
        switch (choice) {
            case 1: addContact(contacts); break;
            case 2: viewContacts(contacts); break;
            case 3: deleteContact(contacts); break;
            case 4: saveContactsToFile(contacts, filename); cout << "Contacts saved to file." << endl; break;
            case 5: loadContactsFromFile(contacts, filename); cout << "Contacts loaded from file." << endl; break;
            case 6: cout << "Exiting program." << endl; break;
            default: cout << "Invalid choice. Please enter a number between 1 and 6." << endl;
        }
    } while (choice != 6);

    saveContactsToFile(contacts, filename);

    return 0;
}

