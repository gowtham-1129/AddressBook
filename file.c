#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) 
{
    FILE *fp=fopen("contacts.csv","w");
    fprintf(fp,"# %d\n",addressBook->contactCount);
    for(int i=0;i<addressBook->contactCount;i++)
    {
        fprintf(fp,"%d. %s,%s,%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fp);
}

void loadContactsFromFile(AddressBook *addressBook) 
{
    FILE *fp=fopen("contacts.csv","r");
    if(fscanf(fp,"# %d\n",&addressBook->contactCount)!=1)
    {
        addressBook->contactCount=0;
    }
    for(int i=0;i<addressBook->contactCount;i++)
    {
        fscanf(fp,"%*d. %[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fp);
}