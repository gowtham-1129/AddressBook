/*
Name        : N.GOWTHAM
Branch      : 26001_150
Project     : AddressBook
Description : The Address Book Management System is a simple application used to store and manage contact details efficiently. 
              This project allows users to add, search, edit, and delete contact information such as name, mobile number, and email address. 
*/
#include <stdio.h>
#include "contact.h"

int main() 
{
    int choice;
    AddressBook addressBook;
    addressBook.contactCount = 0;
    initialize(&addressBook); // Initialize the address book

    do 
    {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Save and Exit\n");		
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) 
        {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:          
                listContacts(&addressBook);
                break;
            case 6:
                printf("------------------------\n");
                printf("Saving and Exiting...\n");
                printf("------------------------\n");
                saveContactsToFile(&addressBook);
                break;
            default:
                printf("------------------------\n");
                printf("Invalid choice. Please try again.\n");
                printf("------------------------\n");
        }
    } while (choice != 6);
    
    return 0;
}
