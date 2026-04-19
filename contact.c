#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include"validation.h"


void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;
    populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}
void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}
void createContact(AddressBook *addressBook)
{
/* Define the logic to create a Contacts */
    char name[50];
    char phone[15];
    char email[50];
    int res=0;
// ------------------------ add BY NAME ------------------------
do 
    {
        printf("Enter Name: ");
        scanf(" %[^\n]", name); // read the value from the user
        // call the function
        res = validateName(name);
        if (res == 0)
        printf("Invalid Name! Try again.\n"); // this is for the print the invalide after the function call
    } 
    while (res == 0);

    // ------------------------ add BY number ------------------------ 
while(1) //loop until a valid and unique mobile number is entered
{
    printf("Enter Mobile Number: ");
    scanf("%s", phone);
    if (!validateMobile(phone)) //check if number is 10 digits or not
    {
        printf("Invalid Mobile! Must be 10 digits.\n");
        continue; //ask again if invalid
    }

    
// DUPLICATE CHECK HERE
    int duplicate = 0; //flag to track if number already exists
    for (int i = 0; i < addressBook->contactCount; i++) // loop through all saved contacts
    {
        if (strcmp(addressBook->contacts[i].phone, phone) == 0) //compare entered number with exiting
        {
            duplicate = 1; //mark as duplicate
            break; //exit loop after finding duplicate
        }
    }
    if(duplicate) // if number already exists
    {
        printf("Duplicate Phone! Enter a different number.\n");
        continue; // ask again
    }
    break; //number is valid + unique → exit loop
}


// ------------------------ add BY email ------------------------
while(1) //repeat until a valid and unique email is entered
{
    printf("Enter email: ");
    scanf(" %s", email);  //read full email including spaces

    if (!validategmail(email)) // validate format:
    {
        printf("Invalid email!\n");
        continue; // ask again if invalid
    }
    
    // DUPLICATE CHECK HERE
    int duplicate = 0; //flag for checking if email already exists
    for (int i = 0; i < addressBook->contactCount; i++) //loop through all saved contacts
    {
        if (strcmp(addressBook->contacts[i].email, email) == 0) //compare with existing emails
        {
            duplicate = 1; //mark if duplicate found 
            break;        //stop checking further
        }
    }

    if (duplicate) //if email already exists
    {
        printf("\nDuplicate email! Enter a different email.\n");
        continue; // ask again
    }

    break;  // emailis valid and unique exit loop
}

// SAVE CONTACT
strcpy(addressBook->contacts[addressBook->contactCount].name, name);    // save name
strcpy(addressBook->contacts[addressBook->contactCount].phone, phone); // save phone
strcpy(addressBook->contacts[addressBook->contactCount].email, email);// save email

addressBook->contactCount++; //increase total contact count 

printf("\nContact saved successfully!\n"); //comfirmation message
}
void searchContact(AddressBook *addressBook) 
{
int choice;              // Stores user choice for search option
char temp[100];          // Temporary buffer to store input
int found;               // Flag to indicate contact found or not

printf("\n--- Search Contact ---\n");   // Search menu heading
printf("Search by:\n");                 // Menu options
printf("1. Name\n");
printf("2. Phone Number\n");
printf("3. Email\n");
printf("4. Exit\n");
printf("Enter your choice: ");          // Ask user choice
scanf("%d", &choice);                   // Read choice

switch (choice)
{
    // ------------------------ SEARCH BY NAME ------------------------
    case 1:
        found = 0;                      // Reset found flag

        do
        {
            printf("Enter Name: ");     // Ask for name
            scanf(" %[^\n]", temp);     // Read full name including spaces

            if (validateName(temp) == 0) // Validate name
                printf("Invalid Name! Try again.\n");

        } while (validateName(temp) == 0); // Repeat until valid name

        for (int i = 0; i < addressBook->contactCount; i++) // Loop through contacts
        {
            if (strcmp(addressBook->contacts[i].name, temp) == 0) // Compare names
            {
                printf("\nContact Found:\n");  // Display contact details
                printf("Name  : %s\n", addressBook->contacts[i].name);
                printf("Phone : %s\n", addressBook->contacts[i].phone);
                printf("Email : %s\n", addressBook->contacts[i].email);
                found = 1;              // Mark contact as found
                break;                  // Exit loop after match
            }
        }

        if (!found)                     // If no match found
        {
            printf("Contact Not Found!\n");
        }
        break;                          // Exit case 1

    // ------------------------ SEARCH BY PHONE ------------------------
    case 2:
        found = 0;                      // Reset found flag

        do
        {
            printf("Enter Phone Number: "); // Ask for phone number
            scanf("%s", temp);              // Read phone number

            if (validateMobile(temp) == 0)  // Validate phone number
                printf("Invalid Phone! Must be 10 digits.\n");

        } while (validateMobile(temp) == 0); // Repeat until valid phone

        for (int i = 0; i < addressBook->contactCount; i++) // Loop through contacts
        {
            if (strcmp(addressBook->contacts[i].phone, temp) == 0) // Compare phone
            {
                printf("\nContact Found:\n"); // Display contact details
                printf("Name  : %s\n", addressBook->contacts[i].name);
                printf("Phone : %s\n", addressBook->contacts[i].phone);
                printf("Email : %s\n", addressBook->contacts[i].email);
                found = 1;              // Mark contact as found
                break;                  // Exit loop after match
            }
        }

        if (!found)                     // If no match found
        {
            printf("Contact Not Found!\n");
        }
        break;                          // Exit case 2

    // ------------------------ SEARCH BY EMAIL ------------------------
    case 3:
        found = 0;                      // Reset found flag

        do
        {
            printf("Enter Email: ");    // Ask for email
            scanf("%s", temp);          // Read email

            if (validategmail(temp) == 0) // Validate email format
                printf("Invalid Email! Must contain @ and .com\n");

        } while (validategmail(temp) == 0); // Repeat until valid email

        for (int i = 0; i < addressBook->contactCount; i++) // Loop through contacts
        {
            if (strcmp(addressBook->contacts[i].email, temp) == 0) // Compare email
            {
                printf("\nContact Found:\n"); // Display contact details
                printf("Name  : %s\n", addressBook->contacts[i].name);
                printf("Phone : %s\n", addressBook->contacts[i].phone);
                printf("Email : %s\n", addressBook->contacts[i].email);
                found = 1;              // Mark contact as found
                break;                  // Exit loop after match
            }
        }

        if (!found)                     // If no match found
        {
            printf("Contact Not Found!\n");
        }
        break;                          // Exit case 3

    case 4:
        return;                         // Exit search menu

    default:
        printf("Invalid Choice! Try Again.\n"); // Handle invalid choice
}

}
void editContact(AddressBook *addressBook)
{
    // ------------------------ DEFINE VARIABLES ------------------------
int choice;                    // Stores user menu choice
char temp[100];                // Temporary buffer for search input
int found = 0;                 // Flag to check if contact is found
int index = -1;                // Stores index of contact to edit

// ------------------------ SEARCH MENU ------------------------
printf("\n--- Search Contact ---\n");
printf("Search by:\n");
printf("1. Name\n");
printf("2. Phone Number\n");
printf("3. Email\n");
printf("4. Exit\n");
printf("Enter your choice: ");
scanf("%d", &choice);          // Read user choice

switch (choice)
{
    // ------------------------ SEARCH BY NAME ------------------------
    case 1:
    {
        printf("Enter Name: ");
        scanf(" %[^\n]", temp);     // Read full name

        int matchIndexes[100];      // Store indexes of matched contacts
        int matchCount = 0;         // Count number of matches

        // Loop to find all matching names
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].name, temp) == 0)
            {
                matchIndexes[matchCount++] = i; // Save matched index
            }
        }

        // If no contact found
        if (matchCount == 0)
        {
            printf("Contact Not Found!\n");
            return;
        }

        // If only one contact found
        if (matchCount == 1)
        {
            index = matchIndexes[0]; // Select that contact
            found = 1;
        }
        else
        {
            // Multiple contacts found with same name
            printf("\nMultiple contacts found with name '%s':\n", temp);

            // Display phone and email for selection
            for (int i = 0; i < matchCount; i++)
            {
                int idx = matchIndexes[i];
                printf("%d. Phone: %s | Email: %s\n",
                       i + 1,
                       addressBook->contacts[idx].phone,
                       addressBook->contacts[idx].email);
            }

            int sel;   // User selection
            printf("Select which contact to edit (1-%d): ", matchCount);
            scanf("%d", &sel);

            // Validate selection
            if (sel < 1 || sel > matchCount)
            {
                printf("Invalid Selection!\n");
                return;
            }

            index = matchIndexes[sel - 1]; // Set selected contact index
            found = 1;
        }
    }
    break;

    // ------------------------ SEARCH BY PHONE ------------------------
    case 2:
        printf("Enter Phone Number: ");
        scanf("%s", temp);           // Read phone number

        // Search contact by phone
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].phone, temp) == 0)
            {
                found = 1;
                index = i;           // Store index
                break;
            }
        }
        break;

    // ------------------------ SEARCH BY EMAIL ------------------------
    case 3:
        printf("Enter Email: ");
        scanf("%s", temp);           // Read email

        // Search contact by email
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].email, temp) == 0)
            {
                found = 1;
                index = i;           // Store index
                break;
            }
        }
        break;

    case 4:
        return;                      // Exit edit contact

    default:
        printf("Invalid Choice!\n");
        return;
}

// If contact not found
if (!found)
{
    printf("Contact Not Found!\n");
    return;
}

// ------------------------ EDIT MENU ------------------------
printf("\nContact Found:\n");
printf("1. Edit Name\n");
printf("2. Edit Phone\n");
printf("3. Edit Email\n");
printf("4. Cancel\n");
printf("Enter your choice: ");
scanf("%d", &choice);               // Read edit option

char newValue[100];                 // Buffer for new data
int res;                            // Validation result

switch (choice)
{
    // ------------------------ EDIT NAME ------------------------
    case 1:
        do
        {
            printf("Enter New Name: ");
            scanf(" %[^\n]", newValue);  // Read new name

            res = validateName(newValue); // Validate name
            if (res == 0)
            {
                printf("Invalid Name! Try again.\n");
            }
        } while (res == 0);

        strcpy(addressBook->contacts[index].name, newValue); // Update name
        printf("Name Updated Successfully!\n");
        break;

    // ------------------------ EDIT PHONE ------------------------
    case 2:
        do
        {
            printf("Enter New Phone: ");
            scanf(" %[^\n]", newValue);  // Read new phone

            res = validateMobile(newValue); // Validate phone
            if (res == 0)
            {
                printf("Invalid Phone! Try again.\n");
                continue;
            }

            int duplicate = 0;          // Duplicate check flag

            // Check for duplicate phone
            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (i == index) continue;
                if (strcmp(addressBook->contacts[i].phone, newValue) == 0)
                {
                    duplicate = 1;
                    break;
                }
            }

            if (duplicate)
            {
                printf("Phone already exists! Enter a different number.\n");
                res = 0;
            }

        } while (res == 0);

        strcpy(addressBook->contacts[index].phone, newValue); // Update phone
        printf("Phone Updated Successfully!\n");
        break;

    // ------------------------ EDIT EMAIL ------------------------
    case 3:
        do
        {
            printf("Enter New Email: ");
            scanf(" %[^\n]", newValue);  // Read new email

            res = validategmail(newValue); // Validate email
            if (res == 0)
            {
                printf("Invalid Email! Try again.\n");
                continue;
            }

            int duplicate = 0;          // Duplicate check flag

            // Check for duplicate email
            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (i == index) continue;
                if (strcmp(addressBook->contacts[i].email, newValue) == 0)
                {
                    duplicate = 1;
                    break;
                }
            }

            if (duplicate)
            {
                printf("Email already exists! Enter a different email.\n");
                res = 0;
            }

        } while (res == 0);

        strcpy(addressBook->contacts[index].email, newValue); // Update email
        printf("Email Updated Successfully!\n");
        break;

    case 4:
        return;                         // Cancel editing

    default:
        printf("Invalid Choice!\n");    // Handle wrong option
    }
}
void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    int choice;
    char temp[100];
    int found = 0, index = -1;

    printf("\n Delete the contact \n");
    printf("1.By Name :\n");
    printf("2.By PH.NO :\n");
    printf("3.By Gmail ID :\n");
    printf("4.Exit\n");
    printf("Enter the choice : ");
    scanf("%d",&choice);

    switch(choice)
    {
         // ------------------------ DELETE BY NAME ------------------------
        case 1 :
         {
            printf("Enter Name: ");
            scanf(" %[^\n]", temp);

            int matchIndexes[100];
            int matchCount = 0;

            // Find all contacts with this name
            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(addressBook->contacts[i].name, temp) == 0)
                {
                    matchIndexes[matchCount] = i; // store index of matched contact
                    matchCount++;
                }
            }

            if (matchCount == 0)
            {
                printf("Contact Not Found!\n");
                return;
            }

            if (matchCount == 1)
            {
                index = matchIndexes[0]; // Direct delete if only 1 match
                found = 1;
                break;
            }

            // Multiple contacts found → ask user to select exact one
            printf("\nMultiple contacts found with name '%s':\n", temp);
            for (int i = 0; i < matchCount; i++)
            {
                int idx = matchIndexes[i];
                printf("%d. Phone: %s | Email: %s\n",
                       i + 1,
                       addressBook->contacts[idx].phone,
                       addressBook->contacts[idx].email);
            }

            int sel;
            printf("Enter which one to delete (1-%d): ", matchCount);
            scanf("%d", &sel);

            if (sel < 1 || sel > matchCount)
            {
                printf("Invalid Selection!\n");
                return;   //user selected wrong option
            }

            index = matchIndexes[sel - 1]; // select correct contact
            found = 1;
            break;
        }

        // ------------------------ DELETE BY PHONE ------------------------
        case 2:
            printf("Enter Phone Number: ");
            scanf("%s", temp);
            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(addressBook->contacts[i].phone, temp) == 0)
                {
                    found = 1;
                    index = i;  // save index of contact
                    break;
                }
            }
            break;

        // ------------------------ DELETE BY EMAIL ------------------------
        case 3:
            printf("Enter Email: ");
            scanf("%s", temp);
            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(addressBook->contacts[i].email, temp) == 0)
                {
                    found = 1;
                    index = i; //save index of matched contant
                    break;
                }
            }
            break;

        case 4:
            return; //exit delete menu

        default:
            printf("Invalid Choice!\n");
            return; 
    }

    if (!found)
    {
        printf("Contact Not Found!\n");
        return; //Nothing Matched
    }

    // ------------------------ SHOW CONTACT + CONFIRM ------------------------
    printf("\nContact Found:\n");
    printf("Name  : %s\n", addressBook->contacts[index].name);
    printf("Phone : %s\n", addressBook->contacts[index].phone);
    printf("Email : %s\n", addressBook->contacts[index].email);

    printf("\nAre you sure you want to delete this contact? (y/n): ");
    char confirm;
    scanf(" %c", &confirm);

    if (confirm != 'y' && confirm != 'Y')
    {
        printf("Delete Cancelled.\n");
        return; //user cancelled deletion
    }

    // ------------------------ DELETE (SHIFT LEFT) ------------------------
    for (int i = index; i < addressBook->contactCount - 1; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1]; // shift left
    }

    addressBook->contactCount--; //reduce total count

    printf("Contact Deleted Successfully!\n");
                
    }
void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    // Sort contacts based on the chosen criteria
    if(addressBook->contactCount == 0)
    {
        printf("NO CONTACT FOUND.\n");
        return;
    }
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        printf("%-20s %-15s %-30s\n",
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }
}

