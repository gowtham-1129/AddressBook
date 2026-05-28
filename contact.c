#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"
//#include "populate.h"
//Function to validate name input
int name_validation(char name[])
{
    // Validation: name must be at least 3 characters
    int len=strlen(name);
    if(len<3)
    {
        printf("------------------------\n");
        printf("Enter the name is at least 3 charactar\n");
        printf("------------------------\n");
        return 0;
    }
    // Validation: only alphabets and space allowed
   int i=0;
   while(name[i]!='\0')
   {
        if(!isalpha((unsigned char)name[i]) && name[i] != ' ')
        {
            printf("------------------------\n");
            printf("Only alphabets allowed!!\n");
            printf("------------------------\n");
            return 0;
        }
        i++;
   } 
   return 1;
}
//Function to validate phone number
int phone_validation(AddressBook *addressBook,char phone[])
{
    int i=0,flag = 1;
    // Validation: phone number must be 10 digits
    int len = strlen(phone);
    if(len!=10)
    {
        printf("------------------------\n");
        printf("please enter the 10 digits of phone number!!!\n");
        printf("------------------------\n");
        return 0;
    }
    // Validation: phone number must be 10 digits
    if(phone[0] < '6' || phone[0] > '9')
    {
        printf("------------------------\n");
        printf("Phone number starting from 6 to 9 only!!!\n");
        printf("------------------------\n");
        return 0;
    }
    //Validation: all characters must be digits
    while(phone[i]!='\0')
    {
        if(!isdigit(phone[i]) )
        {
            printf("------------------------\n");
            printf("please enter the digit values!!!\n");
            printf("------------------------\n");
            return 0;
        }
        i++;
    }
    //Validation: check duplicate phone number
    for(int i=0;i < addressBook->contactCount;i++)
    {
        if(strcmp(addressBook->contacts[i].phone,phone)==0)
        {
            printf("------------------------\n");
            printf("This number is alredy saved!!!\n");
            printf("------------------------\n");
            return 0;
        }

    }
    return 1;
}
// Function to validate email
int email_validation(AddressBook *addressBook,char email[])
{
    // Validation: first character must be alphabet
    if(!isalpha(email[0]))
    {
        printf("------------------------\n");
        printf("Email must start with alphabet!!!\n");
        printf("------------------------\n");
        return 0;
    }
    // Validation: email must be lowercase
    for(int i=0;email[i]!='\0';i++)
    {
    if(isupper(email[i]))
    {
        printf("------------------------\n");
        printf("Email must be lowercase...\n");
        printf("------------------------\n");
        return 0;
    }
    }
    // Validation: count number of '@'
    int count=0;
    for(int i=0;email[i]!='\0';i++)
    {
        if(email[i]=='@')
        {
            count++;
        }
    }
    // Validation: only one '@' allowed
    if(count>1 || count<1)
    {
        printf("------------------------\n");
        printf("Email must contain exactly one '@'\n");
        printf("------------------------\n");
        return 0;
    }
    // Validation: characters must exist between '@' and '.com'
    char *at = strchr(email, '@');
    char *dot = strchr(email, '.');
    if (at + 1 == dot)
    {
        printf("------------------------\n");
        printf("No character between '@' and '.com'\n");
        printf("------------------------\n");
        return 0;
    }
    // Validation: no digits in domain part
    for(char *p=at+1;p<dot;p++){
        if(isdigit(*p))
        {
            printf("------------------------\n");
            printf("Invalid: Domain can not contain digits!\n");
            printf("------------------------\n");
            return 0;
        }
    }
    // Validation: must contain ".com"
    char *ptr=strstr(email,".com");
    if(ptr==NULL)
    {
        printf("------------------------\n");
        printf("Email must contain '.com'\n");
        printf("------------------------\n");
        return 0;
    }
    // Validation: ".com" must be at end
    if(strcmp(ptr,".com")!=0)
    {
        printf("------------------------\n");
        printf(".com must be contain end\n");
        printf("------------------------\n");
        return 0;
    }
    // Validation: check duplicate email
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(addressBook->contacts[i].email,email)==0)
        {
            printf("------------------------\n");
            printf("This Email_id is already saved!!!\n");
            printf("------------------------\n");
            return 0;
        }
    }
    return 1;
}
void listContacts(AddressBook *addressBook) 
{
    // Sort contacts based on the chosen criteria
    if(addressBook->contactCount==0)
    {
        printf("------------------------\n");
        printf("No contacts\n");
        printf("------------------------\n");
        return ;
    }
     printf("\n----- Contact List -----\n");
     printf("%-10s%-20s%-20s%-20s\n","serial","name","phone","Email");
     printf("------------------------\n");
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        printf("%-10d%-20s%-20s%-20s\n",i + 1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    printf("------------------------\n");
}
void initialize(AddressBook *addressBook)
{
    //initialize of the addressbook 
    addressBook->contactCount = 0;
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) 
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}
void createContact(AddressBook *addressBook)
{
    char name[50];
    char phone[20];
    char email[50];
	/* Define the logic to create a Contacts */
    //Name
   
    int success_name = 0,success_phone=0,success_email= 0,count_name=0,count_phone=0,count_email=0;
    while(count_name <3)
    {
    printf("Enter the name : \n");
    scanf(" %[^\n]",name);
    if(name_validation(name)) // Call name validation function
    {
      strcpy(addressBook->contacts[addressBook->contactCount].name,name);
      success_name = 1;
      break;
    }
    else
    {
        count_name++;
        if(count_name<3)
        {
            printf("------------------------\n");
            printf("Invalid Name!\n");
            printf("------------------------\n");
        }
    }
    }
    if(!success_name)
    {  
        printf("-----------------------------\n");
        printf("Failed: Maximum attempts reached for Name.\n");
        printf("-----------------------------\n");
        return;
    }
    // Loop until valid phone number is entered
    while(count_phone<3)
    {
    printf("Enter the mobile : \n");
    scanf(" %[^\n]",phone);
    if(phone_validation(addressBook,phone)) // Call phone validation
    {
      strcpy(addressBook->contacts[addressBook->contactCount].phone,phone);
      success_phone = 1;
      break;
    }
    else
    {
        count_phone++;
        if(count_phone<3)
        {
            printf("------------------------\n");
            printf("Invalid Phone Number!!\n");
            printf("------------------------\n");
        }
    }
    }
    if(!success_phone)
    {  
        printf("-----------------------------\n");
        printf("Failed: Maximum attempts reached for Phone Number.\n");
        printf("-----------------------------\n");
        return;
    }
    // Loop until valid email is entered
    while(count_email <3)
    {
        printf("Enter the Mail : \n");
        scanf(" %[^\n]",email);
        if(email_validation(addressBook,email)) // Call email validation
        {
            strcpy(addressBook->contacts[addressBook->contactCount].email,email);
            success_email = 1;
            break;
        }
        else
        {
            count_email++;
            if(count_email<3)
            {
                printf("------------------------\n");
                printf("Invalid Email, Try again!!\n");
                printf("------------------------\n");
            }
        }
    }
    if(!success_email)
    {  
        printf("-----------------------------\n");
        printf("You have exceeded 3 attempts!\n");
        printf("Contact creation failed.\n");
        printf("-----------------------------\n");
        return;
    }
    // Increase contact count after adding new contact
   addressBook->contactCount++;
    printf("------------------------\n");
    printf("Contact SuccessFully created!!!\n");
    printf("------------------------\n");
}
/* Function: searchContact
   Purpose : Search contact using name, phone or email */
void searchContact(AddressBook *addressBook) 
{
    // Define the logic for search 
    char name[50];
    char phone[20];
    char email[50];
    int option;
    int found=0;
    // Check if address book is empty
    if(addressBook->contactCount==0)
    {
        printf("------------------------\n");
        printf("Addressbook is empty");
        printf("------------------------\n");
        return;
    }
    // Display search options
    printf("------------------------\n");
    printf("Choose one option of serial number\n");
    printf("------------------------\n");
    printf("1.search by name\n");
    printf("2.search by phone_number\n");
    printf("3.serach by Email_id\n");
    scanf("%d",&option);
    getchar();
    // Compare based on selected option
    // search by name
    if(option==1)
    {
        printf("Enter the name : ");
        scanf(" %[^\n]",name);
        for(int i=0;i<addressBook->contactCount;i++)
        {
            if(strcmp(addressBook->contacts[i].name,name)==0)
            {
                if(found==0)
                {
                    printf("------------------------\n");
                    printf("contact found:\n");
                    printf("------------------------\n");
                    printf("%-20s%-20s%-20s\n","name","phone","Email");
                    printf("------------------------\n");
                }
                printf("%-20s%-20s%-20s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                found++;
            }
        }
    }
    // search by phone
    else if(option==2)
    {
        printf("Enter the phone : ");
        scanf(" %[^\n]",phone);
        for(int i=0;i<addressBook->contactCount;i++)
        {
            if(strcmp(addressBook->contacts[i].phone,phone)==0)
            {
                printf("------------------------\n");
                printf("contact found:\n");
                printf("------------------------\n");
                printf("%-20s%-20s%-20s\n","name","phone","Email");
                printf("%-20s%-20s%-20s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                found++;
                break;
            }
        }
    }
    // search by email
    else if(option==3)
    {
        printf("Enter the email : ");
        scanf(" %[^\n]",email);
        for(int i=0;i<addressBook->contactCount;i++)
        {
            if(strcmp(addressBook->contacts[i].email,email)==0)
            {
                printf("------------------------\n");
                printf("contact found:\n");
                printf("------------------------\n");
                printf("%-20s%-20s%-20s\n","name","phone","Email");
                printf("%-20s%-20s%-20s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                found++;
                break;
            }
        }
    }
    // Invalid Option
    else
    {
        printf("------------------------\n");
        printf("Invalid option!!\n");
        printf("------------------------\n");
        return;
    }
    // If no match found
    if(!found)
    {
        printf("------------------------\n");
        printf("Contact not found!!\n");
        printf("------------------------\n");
        return;
    }
}
/* Function: editContact
   Purpose : Modify existing contact details */
void editContact(AddressBook *addressBook)
{
	// Define the logic for Editcontact 
    char name_edit[100];
    char phone_edit[100];
    char email_edit[100];
    int index[100];
    int option;
    int number;
    int count=0;
    // Check if address book is empty
    if(addressBook->contactCount==0)
    {
        printf("------------------------\n");
        printf("Addressbook is empty");
        printf("------------------------\n");
        return;
    }
    printf("------------------------\n");
    printf("Choose one option of serial number\n");
    printf("------------------------\n");
    printf("1.search by name\n");
    printf("2.search by phone_number\n");
    printf("3.serach by Email_id\n");
    scanf("%d",&number);
    getchar();
    if(number==1)
    {
        printf("Enter name to search: \n");
        scanf(" %[^\n]",name_edit);
        for(int i=0;i<addressBook->contactCount;i++)
        {
        if(strcmp(addressBook->contacts[i].name,name_edit)==0)
            {
                if(count==0)
                {
                    printf("------------------------\n");
                    printf("contact found:\n");
                    printf("------------------------\n");
                    printf("%-20s%-20s%-20s\n","name","phone","Email");
                    printf("------------------------\n");
                }
                index[count]=i;
                printf("%-20s%-20s%-20s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                count++;
            }
        }
    }
    else if(number==2)
    {
        printf("Enter phone to search: \n");
        scanf(" %[^\n]",phone_edit);
        for(int i=0;i<addressBook->contactCount;i++)
        {
        if(strcmp(addressBook->contacts[i].phone,phone_edit)==0)
            {
                index[count]=i;
                printf("%-20s%-20s%-20s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                count++;
            }
        }
    }
    else if(number==3)
    {
        printf("Enter email to search: \n");
        scanf(" %[^\n]",email_edit);
        for(int i=0;i<addressBook->contactCount;i++)
        {
        if(strcmp(addressBook->contacts[i].email,email_edit)==0)
            {
                index[count]=i;
                printf("%-20s%-20s%-20s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                count++;
            }
        }
    }
    // Invalid Option
    else
    {
        printf("Invalid Option\n");
        return;
    }
    if(number>3)
    {
        printf("Invalid Option\n");
        return;
    }
    // If contact not found
    if(count==0)
    {
        printf("------------------------\n");
        printf("Contact not found!!\n");
        printf("------------------------\n");
        return;
    }
    if(count==1)
    {
        option=1;
    }
    else
    {
        printf("------------------------\n");
        printf("%d Contact found select 1 contact to edit\n",count);
        printf("------------------------\n");
        scanf("%d",&option);
    }
    if(option < 1 || option > count)
    {
        printf("------------------------\n");
        printf("Invalid choice\n");
        printf("------------------------\n");
        return;
    }
    int indexfound=index[option-1];
    int choose;
    int check=0;
    char name[50];
    char phone[20];
    char email[50];
    printf("------------------------\n");
    printf("Contact Found!!! Choose the option to edit : \n");
    printf("------------------------\n");
    printf("1.Edit by name\n");
    printf("2.Edit by phone_number\n");
    printf("3.Edit by Email_id\n");
    printf("Enter the serial number : \n");
    scanf("%d",&choose);
    getchar();
    // Update name
    if(choose==1)
    {
        for(int i=0;i<3;i++)
        {
            printf("Enter the name,you have only 3 attempts : \n");
            scanf(" %[^\n]",name);
            if(name_validation(name))
            {
                strcpy(addressBook->contacts[indexfound].name,name);
                printf("------------------------\n");
                printf("contact updated successfully!!\n");
                printf("------------------------\n");
                check=1;
                break;
            }
        }
        if(!check)
        {
            printf("------------------------\n");
            printf("Too many attempts, Try later!!!\n");
            printf("------------------------\n");
            return;
        }
    }
    // Update phone
    else if(choose==2)
    {
        for(int i=0;i<3;i++)
        {
            printf("Enter the phone,you have only 3 attempts : \n");
            scanf(" %[^\n]",phone);
            if(phone_validation(addressBook,phone))
            {
                strcpy(addressBook->contacts[indexfound].phone,phone);
                printf("------------------------\n");
                printf("contact updated successfully!!\n");
                printf("------------------------\n");
                check=1;
                break;
            }
        }
        if(!check)
        {
            printf("------------------------\n");
            printf("Too many attempts, Try later!!!\n");
            printf("------------------------\n");
            return;
        }
    }
    // Update email
    else if(choose==3)
    {
        for(int i=0;i<3;i++)
        {
            printf("Enter the email,you have only 3 attempts : \n");
            scanf(" %[^\n]",email);
            if(email_validation(addressBook,email))
            {
                strcpy(addressBook->contacts[indexfound].email,email);
                printf("------------------------\n");
                printf("contact updated successfully!!\n");
                printf("------------------------\n");
                check=1;
                break;
            }
        }
        if(!check)
        {
            printf("------------------------\n");
            printf("Too many attempts, Try later!!!\n");
            printf("------------------------\n");
            return;
        }
    }
    else
    {
        printf("------------------------\n");
        printf("Invalid choice!!!\n");
        printf("------------------------\n");
        return;
    }
}
/* Function: deleteContact
   Purpose : Remove a contact from address book */
void deleteContact(AddressBook *addressBook)
{
	// Define the logic for deletecontact 
    int option;
    int choose;
    char name[50];
    char phone[20];
    char email[50];
    int temp[100];
    int count=0;
    // Check if address book is empty
    if(addressBook->contactCount==0)
    {
        printf("-----------------------------\n");
        printf("Contacts Empty!!\n");
        printf("-----------------------------\n");
        return ;
    }
    printf("------------------------\n");
    printf("Choose the option to delete : \n");
    printf("------------------------\n");
    printf("1.delete by name\n");
    printf("2.delete by phone_number\n");
    printf("3.delete by Email_id\n");
    printf("Enter the serial number : \n");
    scanf("%d",&choose);
    getchar();
    // Get name to delete
        if(choose==1)
        {
        printf("Enter name to delete : \n");
        scanf(" %[^\n]",name);
        for(int i=0;i<addressBook->contactCount;i++)
        {
            if(strcmp(addressBook->contacts[i].name,name)==0)
            {
                if(count==0)
                {
                    printf("------------------------\n");
                    printf("contact found:\n");
                    printf("------------------------\n");
                    printf("%-10s%-20s%-20s%-20s\n","serial","name","phone","Email");
                    printf("------------------------\n");
                }
            temp[count]=i;
            printf("%-10d%-20s%-20s%-20s\n",i + 1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            count++;
            }
        }
    }
    // get to phone number delete
    else if(choose==2)
        {
        printf("Enter phone number to delete : \n");
        scanf(" %[^\n]",phone);
        for(int i=0;i<addressBook->contactCount;i++)
        {
            if(strcmp(addressBook->contacts[i].phone,phone)==0)
            {
                if(count==0)
                {
                    printf("------------------------\n");
                    printf("contact found:\n");
                    printf("------------------------\n");
                    printf("%-10s%-20s%-20s%-20s\n","serial","name","phone","Email");
                    printf("------------------------\n");
                }
            temp[count]=i;
            printf("%-10d%-20s%-20s%-20s\n",i + 1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            count++;
            }
        }
    }
    // get to email_id delete
    else if(choose==3)
        {
        printf("Enter Email_ID to delete : \n");
        scanf(" %[^\n]",email);
        for(int i=0;i<addressBook->contactCount;i++)
        {
            if(strcmp(addressBook->contacts[i].email,email)==0)
            {
                if(count==0)
                {
                    printf("------------------------\n");
                    printf("contact found:\n");
                    printf("------------------------\n");
                    printf("%-10s%-20s%-20s%-20s\n","serial","name","phone","Email");
                    printf("------------------------\n");
                }
            temp[count]=i;
            printf("%-10d%-20s%-20s%-20s\n",i + 1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            count++;
            }
        }
    }
    //Contact not found
    if(count==0)
    {
    printf("-----------------------------\n");
    printf("contact not found!!\n");
    printf("-----------------------------\n");
    return ;
    }
    if(count==1)
    {
        option=1;
    }
    //Check multiple contacts
    else
    {
        printf("%d Contact are found select 1 contact to delete\n",count);
        scanf("%d",&option);
    }
    //Check Invalid option
    if(option>count)
    {
        printf("-----------------------------\n");
        printf("Invalid option!!\n");
        printf("-----------------------------\n");
        return ;
    }
    //delete and replace opration
    int deleteindex=temp[option-1];
    for(int i=deleteindex;i<addressBook->contactCount-1;i++)
    {
        addressBook->contacts[i]=addressBook->contacts[i+1];
    }
    addressBook->contactCount--;
    printf("-----------------------------\n");
    printf("Contact Deleted Sucssfully!!\n");
    printf("-----------------------------\n");

}