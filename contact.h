#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100
// Structure to store one contact
typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;
// Structure for Address Book
typedef struct {
    Contact contacts[100];
    int contactCount;
} AddressBook;
int name_validation(char name[]);
int phone_validation(AddressBook *addressBook,char phone[]);
int email_validation(AddressBook *addressBook,char email[]);
void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);
#endif
