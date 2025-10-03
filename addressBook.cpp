#include <iostream>
#include <string>

struct Contact {
    std::string name;
    std::string phone;
    int age;
};

Contact contacts[10]; //array max size
int contactCount = 0;

void addContact(Contact contacts[], int& count){
    if (count >= 10) {
        std::cout << "Address book is full.\n";
        return;
    }

    Contact newContact; //object

    std::cout << "Enter name: ";
    std::cin >> newContact.name;

    std::cout << "Enter phone: ";
    std::cin >> newContact.phone;

    std::cout << "Enter age: ";
    std::cin >> newContact.age;

    contacts[count++] = newContact;
    std::cout << "Contact added. \n";
}

void deleteContact(Contact contacts[], int& count, const std::string& name) {
    for (int i = 0; i < count; ++i) {
        if (contacts[i].name == name) {
            for (int j = i; j < count - 1; ++j) {
                contacts[j] = contacts[j + 1]; //shifts contacts
            }
            count--;
            std::cout << "Contact Deleted.\n";
            return;
        }
    }
    std::cout << "Contact not found.\n";
}

void listContacts(const Contact contacts[], int count) {
    for (int i = 0; i < count; ++i) {
        std::cout << "Name: " << contacts[i].name
            << "\n Phone: " << contacts[i].phone
            << "\n Age: " << contacts[i].age << std::endl;
    }
}

void searchByName(const Contact contacts[], int count, std::string& name) {
    for (int i = 0; i < count; ++i) {
        if (contacts[i].name == name) {   
            std::cout << "Name: " << contacts[i].name
            << "\n Phone: " << contacts[i].phone
            << "\n Age: " << contacts[i].age << std::endl;
            return;
        }
    }
    std::cout << "Contact not found.\n";
}

int main() {
    Contact contacts[10]; 
    int count = 0;
    int choice;

    do {
        std::cout << "\nMenu:\n"
             << "1. Add contact\n"
             << "2. Delete contact\n"
             << "3. List contacts\n"
             << "4. Search by name\n"
             << "0. Exit\nChoice: ";
        std::cin >> choice;
        std::cout << std::endl;

        if (choice == 1) addContact(contacts, count);
        else if (choice == 2) {
            std::string name;
            std::cout << "Enter name to delete: ";
            std::cin >> name;
            deleteContact(contacts, count, name);
        }
        else if (choice == 3) listContacts(contacts, count);
        else if (choice == 4) {
            std::string name;
            std::cout << "Enter name to search: ";
            std::cin >> name;
            searchByName(contacts, count, name);
        }
    } while (choice != 0);

    return 0;
}