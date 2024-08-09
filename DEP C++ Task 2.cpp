#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Contact {
    std::string name, phone_number;
public:
    Contact(std::string n, std::string p) : name(n), phone_number(p) {}
    std::string getName() const { return name; }
    void display() const { std::cout << "Name: " << name << ", Phone Number: " << phone_number << std::endl; }
};

void addContact(std::vector<Contact>& contacts) {
    std::string name, phone_number;
    std::cout << "Enter Name: "; std::cin >> name;
    std::cout << "Enter Phone Number: "; std::cin >> phone_number;
    contacts.emplace_back(name, phone_number);
}

void viewContacts(const std::vector<Contact>& contacts) {
    if (contacts.empty()) std::cout << "No contacts to display." << std::endl;
    else for (const auto& contact : contacts) contact.display();
}

void deleteContact(std::vector<Contact>& contacts) {
    std::string name;
    std::cout << "Enter the name of the contact to delete: "; std::cin >> name;
    auto it = std::remove_if(contacts.begin(), contacts.end(),
                             [&name](const Contact& contact) { return contact.getName() == name; });
    if (it != contacts.end()) contacts.erase(it, contacts.end());
    else std::cout << "Contact not found." << std::endl;
}

void showMenu() {
    std::cout << "1. Add Contact\n2. View Contacts\n3. Delete Contact\n4. Exit\nChoose an option: ";
}

int main() {
    std::vector<Contact> contacts;
    int choice;
    do {
        showMenu(); std::cin >> choice;
        if (choice == 1) addContact(contacts);
        else if (choice == 2) viewContacts(contacts);
        else if (choice == 3) deleteContact(contacts);
    } while (choice != 4);
    return 0;
}
