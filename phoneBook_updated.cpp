#include <iostream>
#include <iomanip>
#include <string>


using namespace std;

struct phoneBook
{
    string firstName, lastName, eMail, phoneNumbers[3], address;
};

struct Node
{
    phoneBook contact;
    Node* next;
};

class PhoneDirectory
{
private:
    Node* head;

public:
    PhoneDirectory() : head(nullptr) {}

    void addContacts(const phoneBook &newContact)
    {
        Node* newNode = new Node;
        newNode->contact = newContact;
        newNode->next = nullptr;

        if (head == nullptr)
        {
            head = newNode;
        }
        else
        {
            Node* temp = head;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = newNode;
        }

        cout << "Contact added in directory successfully!" << endl;
    }
    
    void displayContacts()
    {
        if (head == nullptr)
        {
            cout << "Your phone Directory is still empty.\nPlease add contacts first." << endl;
            cout << endl;
            return;
        }
        cout << "--------------------------------------" << endl;
        Node* temp = head;
        while (temp != nullptr)
        {
            const phoneBook &contact = temp->contact;
            cout << "Name: " << contact.firstName << " " << contact.lastName << endl;
            cout << "Phone Number: " << endl;
            for (int i = 0; i < 3; ++i)
            {
                cout << " - " << contact.phoneNumbers[i] << endl;
            }
            cout << "Email: " << contact.eMail << endl;
            cout << "Address: " << contact.address << endl;
            cout << "--------------------------------------" << endl;
            temp = temp->next;
        }
    }

    void searchContacts(const string &query)
    {
        bool found = false;
        cout << "Search Results: " << endl;
        cout << "--------------------------------------" << endl;
        Node* temp = head;
        while (temp != nullptr)
        {
            const phoneBook &contact = temp->contact;
            if (contact.firstName.find(query) != string::npos ||
                contact.lastName.find(query) != string::npos ||
                contact.phoneNumbers[0].find(query) != string::npos ||
                contact.phoneNumbers[1].find(query) != string::npos ||
                contact.phoneNumbers[2].find(query) != string::npos ||
                contact.eMail.find(query) != string::npos)
            {
                cout << "Name: " << contact.firstName << " " << contact.lastName << endl;
                cout << "Phone Number: " << endl;
                for (int i = 0; i < 3; ++i)
                {
                    if (!contact.phoneNumbers[i].empty())
                    {
                        cout << "- " << contact.phoneNumbers[i] << endl;
                    }
                }
                cout << "Email: " << contact.eMail << endl;
                cout << "Address: " << contact.address << endl;
                cout << "--------------------------------------" << endl;
                found = true;
            }
            temp = temp->next;
        }
        if (!found)
        {
            cout << "No matching contact Found, Please check spellings." << endl;
        }
    }

    void deleteContacts(const string &fullName)
    {
        Node* prev = nullptr;
        Node* curr = head;

        while (curr != nullptr)
        {
            if ((curr->contact.firstName + " " + curr->contact.lastName) == fullName)
            {
                if (prev == nullptr)
                {
                    head = curr->next;
                }
                else
                {
                    prev->next = curr->next;
                }
                delete curr;
                cout << "Contact Deleted Permanently!" << endl;
                return;
            }
            prev = curr;
            curr = curr->next;
        }

        cout << "Either contact is not present or Spelling mistake!" << endl;
    }

    void editContact(const string &fullName, const phoneBook &newContactInfo)
    {
        Node* temp = head;
        while (temp != nullptr)
        {
            if ((temp->contact.firstName + " " + temp->contact.lastName) == fullName)
            {
                temp->contact = newContactInfo;
                cout << "Contact Edited & Updated successfully!" << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Contact not found in Directory!" << endl;
    }

    ~PhoneDirectory()
    {
        Node* temp;
        while (head != nullptr)
        {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};

void printIntroduction()
{
    cout << endl;
    cout << endl;
    cout << "\"Phone Directory Application\"" << endl;
    cout << "Created By \"Maryam khan\"" << endl;
    cout << "\"BS CS\"" << endl;
    cout << "1174" << endl;
    cout << "IUB" << endl;
   
    cout << endl;
}

int main()
{
    PhoneDirectory directory;
    int choice;
    string firstName, lastName, searchQuery;
    phoneBook newContact;

    printIntroduction();

    cout << "Home of the Application" << endl;

    do
    {
        cout << "\nPhone Directory Menu:\n";
        cout << "1. Add Contact\n";
        cout << "2. Display Contacts\n";
        cout << "3. Search Contacts\n";
        cout << "4. Delete Contact\n";
        cout << "5. Edit Contact\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Enter First Name: ";
            cin >> newContact.firstName;
            cout << "Enter Last Name: ";
            cin >> newContact.lastName;
            cout << "Enter Mobile Number: ";
            cin >> newContact.phoneNumbers[0];
            cout << "Enter Home Number: ";
            cin >> newContact.phoneNumbers[1];
            cout << "Enter Work Number: ";
            cin >> newContact.phoneNumbers[2];
            cout << "Enter Email: ";
            cin >> newContact.eMail;
            cout << "Enter Home Address: ";
            cin >> newContact.address;
            directory.addContacts(newContact);
            break;
        case 2:
            directory.displayContacts();
            break;
        case 3:
            cout << "Enter Full Name or Contact Number: ";
            cin.ignore();
            cin >> searchQuery;
            directory.searchContacts(searchQuery);
            break;
        case 4:
            cout << "Enter Full Name of contact to delete: ";
            cin >> firstName >> lastName;
            directory.deleteContacts(firstName + " " + lastName);
            break;
        case 5:
            cout << "Enter full name of contact to edit: ";
            cin >> firstName >> lastName;
            cout << "Enter new First Name: ";
            cin >> newContact.firstName;
            cout << "Enter new Last Name: ";
            cin >> newContact.lastName;
            cout << "Enter new Mobile Number: ";
            cin >> newContact.phoneNumbers[0];
            cout << "Enter new Home Number: ";
            cin >> newContact.phoneNumbers[1];
            cout << "Enter new Work Number: ";
            cin >> newContact.phoneNumbers[2];
            cout << "Enter new Email: ";
            cin >> newContact.eMail;
            cout << "Enter new Address: ";
            cin >> newContact.address;
            directory.editContact(firstName + " " + lastName, newContact);
            break;
        case 6:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 6);

    return 0;
}
