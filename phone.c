#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
//field
typedef struct
{
    char fname[100];
    char fnumbers[100];
    int isField;
} field;
//contacts details
typedef struct
{
    field fields;
    char firstname[100];
    char middlename[100];
    char lastname[100];
    char company[100];
    char phone[100];
    char email[100];
    char address[100];
    char birthday[100];
    char website[100];
    char note[100];
    int favourite;
} contact;
// Menu of first view
void menu();
void favouritescontact(contact *contacts, int *count);
void allcontact(contact *contacts, int *count);
void searchcontact(contact contacts[], int *count);
contact addcontact(contact contacts[], int *count);
// Menu of contact detail
int contactdetails(contact contacts[], int *choices, int *count2);
void contactdetailsmenu(contact contacts[], int choice, int *count2);
contact addfavourite(contact *contacts, int *count2);
contact contactupdate(contact contacts[], int *count);
void delete (contact *contacts, int *choices, int *count2);
void addfield(contact *contacts, int choices, int *count2);
//Check input function
char checkinputphone(char *phone);
char checkinputbirthday(char *birthday);
int CheckName(char *name);
bool isValidEmailAddress(char *EmailAddress);
// Get string from struct function
void geta();
//File
int WriteFile(contact *contacts, int count);
int ReadFile(contact *contacts, int *count);
int main(int argCount, char **args)
{
    system("cls");
    fflush(stdin);
    contact contacts[250];
    int count = 0;
    int choice;
    ReadFile(contacts, &count);
    do
    {
        menu();
        scanf("%d", &choice);
        while (choice < 1 || choice > 5)
        {
            printf("Try again : ");
            scanf("%d", &choice);
        }
        switch (choice)
        {
        case 1:
            searchcontact(contacts, &count);
            break;
        case 2:
            addcontact(&contacts[count], &count);
            count = count + 1;
            WriteFile(contacts, count);
            break;
        case 3:
            favouritescontact(contacts, &count);
            break;
        case 4:
            allcontact(contacts, &count);
            break;
        case 5:
            exit(0);
            break;
        }
    } while (choice != 5);
    return 0;
}
void menu() //Get Menu For Main()
{
    system("cls");
    printf("========================================\n");
    printf("\n --- VTC ACADEMY CONTACT MANAGEMENT --- \n");
    printf("\n========================================\n");
    printf("1 . Search Contact\n");
    printf("2 . Add Contact\n");
    printf("3 . Favourites Contact\n");
    printf("4 . All Contact\n");
    printf("5 . Exit Application\n");
    printf("========================================\n");
    printf("Your Choice : ");
}
contact addcontact(contact contacts[], int *count) //Function 1 : Add contact
{
    system("cls");
    ReadFile(contacts, count);
    fflush(stdin);
    printf("=======================================\n");
    printf("           CREATE NEW CONTACT          \n");
    printf("=======================================\n");
    printf("first name : ");
    geta(contacts->firstname, 100);
    while (CheckName(contacts->firstname) == 1)
    {
        printf("Invalid name, re-enter : ");
        geta(contacts->firstname, 100);
    }
    printf("middle name : ");
    geta(contacts->middlename, 100);
    while (CheckName(contacts->middlename) == 1)
    {
        printf("Invalid name, re-enter : ");
        geta(contacts->middlename, 100);
    }
    printf("last name : ");
    geta(contacts->lastname, 100);
    while (CheckName(contacts->lastname) == 1)
    {
        printf("Invalid name, re-enter : ");
        geta(contacts->lastname, 100);
    }
    printf("company : ");
    geta(contacts->company, 100);
    printf("phone : ");
    geta(contacts->phone, 100);
    while (CheckName(contacts->phone) == 0)
    {
        printf("Invalid phone, re-enter : ");
        geta(contacts->phone, 100);
    }
    printf("email : ");
    geta(contacts->email, 100);
    while (!isValidEmailAddress(contacts->email))
    {
        printf("Invalid Email, re-enter : ");
        geta(contacts->email, 100);
    }
    printf("address : ");
    geta(contacts->address, 100);
    printf("birthday : ");
    geta(contacts->birthday, 100);
    while (CheckName(contacts->birthday) == 0)
    {
        printf("Invalid phone, re-enter : ");
        geta(contacts->birthday, 100);
    }
    printf("website : ");
    geta(contacts->website, 100);
    printf("note : ");
    geta(contacts->note, 100);
    printf("========================\n");
    printf("Create contact complete\n");
    printf("========================\n");
    printf("Press any key to continue\n");
    getchar();
    return *contacts;
}
void searchcontact(contact contacts[], int *count) //Function 2 : Search contact
{
    ReadFile(contacts, count);
    system("cls");
    fflush(stdin);
    int count_search = 0;
    char name[100];
    int i, choice, save[100];
    if (*count == 0) // check count from file
    {
        printf("Contacts not exists\n");
        printf("Press any key to continue\n");
        getchar();
    }
    else
    {
        printf("Input to search : ");
        gets(name);
        printf("+----------------------------------------------------------------+\n");
        printf("|   %-5s|  %-53s|\n", "No", "Full Name");
        printf("+----------------------------------------------------------------+\n");
        for (i = 0; i < *count; i++)
        {
            if (strcmp(name, contacts[i].firstname) == 0 || strcmp(name, contacts[i].lastname) == 0)
            {
                save[count_search + 1] = i;
                for (int i = 0; i < *count; i++)
                {
                    int NO = i + 1;
                    int lengthname = strlen(contacts[i].firstname) + strlen(contacts[i].lastname);
                    int length = 52 - lengthname;
                    printf("|   %-5d|  %s %s", NO, contacts[i].firstname, contacts[i].lastname);
                    //Display Space;
                    for (int j = 0; j < length; j++)
                    {
                        printf(" ");
                    }
                    printf("|\n");
                }
                count_search++;
            }
        }
        if (count_search == 0)
        {
            printf("Contact not exists!");
            printf("Press any key to continue...");
            fflush(stdin);
            getchar();
        }
        else
        {
            printf("+----------------------------------------------------------------+\n");
            printf("\nINPUT CONTACT NO TO VIEW DETALLS OR INPUT 0  TO BACK MAIN MENU: ");
            fflush(stdin);
            scanf("%d", &choice);
            while (choice < 0 || choice > *count)
            {
                printf("Try again : ");
                fflush(stdin);
                scanf("%d", &choice);
            }
        }
        if (choice != 0)
        {
            system("cls");
            contactdetailsmenu(contacts, save[choice], count);
        }
    }
}

void geta(char *str, int length) // Get string
{
    fseek(stdin, 0, SEEK_END);
    fflush(stdin);
    fgets(str, length, stdin);
    str[strlen(str) - 1] = '\0';
    fseek(stdin, 0, SEEK_END);
    fflush(stdin);
}
void favouritescontact(contact contacts[], int *count) //Function 3 : Favourite
{
    ReadFile(contacts, count);
    system("cls");
    fflush(stdin);
    int i, choice;
    int how = 0;
    int save[100];
    printf("==============================================\n");
    printf("                 FAVOURITE CONTACTS                  \n");
    printf("==============================================\n");
    printf("+----------------------------------------------------------------+\n");
    printf("|   %-5s|  %-53s|\n", "No", "Full Name");
    printf("+----------------------------------------------------------------+\n");
    for (i = 0; i < *count; i++)
    {
        if (contacts[i].favourite == 1) //fv = 1(exists) , fv = 0(!exists)
        {
            int NO = i + 1;
            int lengthname = strlen(contacts[i].firstname) + strlen(contacts[i].lastname);
            int length = 52 - lengthname;
            printf("|   %-5d|  %s %s", NO, contacts[i].firstname, contacts[i].lastname);
            //Display Space;
            for (int j = 0; j < length; j++)
            {
                printf(" ");
            }
            printf("|\n");
            save[how + 1] = i;
            how++;
        }
    }
    if (how == 0)
    {
        printf("No contacts favourite\n");
        printf("Press any key to continue...");
        fflush(stdin);
        getchar();
    }
    else
    {
        printf("+----------------------------------------------------------------+\n");
        printf("\nINPUT CONTACT NO TO VIEW DETALLS OR INPUT 0  TO BACK MAIN MENU: ");
        fflush(stdin);
        scanf("%d", &choice);
        while (choice < 0 || choice > *count)
        {
            printf("Try again : ");
            fflush(stdin);
            scanf("%d", &choice);
        }
    }
    if (choice != 0)
    {
        system("cls");
        contactdetailsmenu(contacts, save[choice], count);
    }
}
void allcontact(contact contacts[], int *count) //Function 4 : All contact
{
    ReadFile(contacts, count);
    system("cls");
    fflush(stdin);
    int choice, i;
    int how = 0;
    printf("==============================================\n");
    printf("                 ALL CONTACT                  \n");
    printf("==============================================\n");
    printf("+----------------------------------------------------------------+\n");
    printf("|   %-5s|  %-53s|\n", "No", "Full Name");
    printf("+----------------------------------------------------------------+\n");
    for (i = 0; i < *count; i++)
    {
        int NO = i + 1;
        int lengthname = strlen(contacts[i].firstname) + strlen(contacts[i].lastname);
        int length = 52 - lengthname;
        printf("|   %-5d|  %s %s", NO, contacts[i].firstname, contacts[i].lastname);
        //Display Space;
        for (int j = 0; j < length; j++)
        {
            printf(" ");
        }
        printf("|\n");
        how = 1;
    }
    if (how == 0)
    {
        printf("No contact not exists\n");
        printf("Press any key to continue...");
        fflush(stdin);
        getchar();
    }
    else
    {
        printf("+----------------------------------------------------------------+\n");
        printf("\nINPUT CONTACT NO TO VIEW DETALLS OR INPUT 0  TO BACK MAIN MENU: ");
        fflush(stdin);
        scanf("%d", &choice);
        while (choice < 0 || choice > *count)
        {
            printf("Try again : ");
            fflush(stdin);
            scanf("%d", &choice);
        }
    }
    if (choice != 0)
    {
        system("cls");
        contactdetailsmenu(contacts, choice - 1, count);
    }
}
void contactdetailsmenu(contact contacts[], int choice, int *count2) //Get Detail from contact
{
    ReadFile(contacts, count2);
    int i = choice;
    printf("=======================================\n");
    printf("            Contact Details            \n");
    printf("=======================================\n");
    printf("Firstname : %s\n", contacts[i].firstname);
    printf("Middlename : %s\n", contacts[i].middlename);
    printf("Lastname : %s\n", contacts[i].lastname);
    printf("Company : %s\n", contacts[i].company);
    printf("Phone : %s\n", contacts[i].phone);
    printf("Email : %s\n", contacts[i].email);
    printf("Address : %s\n", contacts[i].address);
    printf("Birthday : %s\n", contacts[i].birthday);
    printf("Website : %s\n", contacts[i].website);
    printf("Note : %s\n", contacts[i].note);
    if (contacts[i].fields.isField == 1)
    {
        printf("%s : ", contacts[i].fields.fname);
        printf("%s\n", contacts[i].fields.fnumbers);
    }
    contactdetails(contacts, &choice, count2);
}
int contactdetails(contact contacts[], int *choices, int *count2) //Main of detail work
{
    ReadFile(contacts, count2);
    int choice;
    if (contacts[*choices].favourite == 0) // Menu if fv = 0(!exists)
    {
        printf("=======================================\n");
        printf("1.Add to Favourites\n");
        printf("2.Update\n");
        printf("3.Delete\n");
        printf("4.Addfield\n");
        printf("5.Back to menu\n");
    }
    else if (contacts[*choices].favourite == 1) // Menu if fv = 1(exists)
    {
        printf("=======================================\n");
        printf("1.Delete Favourites\n");
        printf("2.Update\n");
        printf("3.Delete\n");
        printf("4.Addfield\n");
        printf("5.Back to menu\n");
    }
    printf("=======================================\n");
    printf("Your choice : ");
    fflush(stdin);
    scanf("%d", &choice);
    while (choice < 1 || choice > 5)
    {
        printf("Try again : ");
        fflush(stdin);
        scanf("%d", &choice);
    }
    switch (choice)
    {
    case 1:
        addfavourite(contacts, choices);
        break;
    case 2:
        contactupdate(contacts, count2);
        break;
    case 3:
        delete (contacts, choices, count2);
        break;
    case 4:
        addfield(contacts, *choices, count2);
        break;
    case 5:
        return choice;
        break;
    }
}
contact addfavourite(contact *contacts, int *count2) // Function 1 : Favourite
{
    ReadFile(contacts, count2);
    if (contacts[*count2].favourite == 0)
    {
        contacts[*count2].favourite = 1;
        printf("\nAdd Favourites Compelte!\nPress Enter Key To Continue...");
        fflush(stdin);
        getchar();
    }
    else
    {
        contacts[*count2].favourite = 0;
        printf("\nDelete Favourites Compelte!\nPress Enter Key To Continue...");
        fflush(stdin);
        getchar();
    }
    return *contacts;
}
contact contactupdate(contact contacts[], int *count) // Function 2 : Update Field
{
    ReadFile(contacts, count);
    int choice;
    system("cls");
    fflush(stdin);
    printf("Which type do you want to update(only default) ?\n1. FirstName\t2. MiddleName\t3. LastName\t4. Company\n5. Phone\t6. Email\t7. Address\t8. Birthday\n9. Website\t10. Note\t11. Exit\n Your Choice : ");
    scanf("%d", &choice);
    while (choice < 1 || choice > 11)
    {
        printf("Try again : ");
        scanf("%d", &choice);
    }
    switch (choice)
    {
    case 1:
        system("cls");
        printf("New first name : ");
        geta(contacts->firstname, 100);
        while (CheckName(contacts->firstname) == 1)
        {
            printf("Invalid name, re-enter : ");
            geta(contacts->firstname, 100);
        }
        printf("Update Complete!\nPress any key to continue...");
        getchar();
        break;
    case 2:
        system("cls");
        printf("New middle name : ");
        geta(contacts->middlename, 100);
        while (CheckName(contacts->middlename) == 1)
        {
            printf("Invalid name, re-enter : ");
            geta(contacts->middlename, 100);
        }
        printf("Update Complete!\nPress any key to continue...");
        getchar();
        break;
    case 3:
        system("cls");
        printf("New last name : ");
        geta(contacts->lastname, 100);
        while (CheckName(contacts->lastname) == 1)
        {
            printf("Invalid name, re-enter : ");
            geta(contacts->lastname, 100);
        }
        printf("Update Complete!\nPress any key to continue...");
        getchar();
        break;
    case 4:
        system("cls");
        printf("New company : ");
        geta(contacts->company, 100);
        printf("Update Complete!\nPress any key to continue...");
        getchar();
        break;
    case 5:
        system("cls");
        printf("New phone : ");
        geta(contacts->phone, 100);
        while (CheckName(contacts->phone) == 0)
        {
            printf("Invalid name, re-enter : ");
            geta(contacts->phone, 100);
        }
        printf("Update Complete!\nPress any key to continue...");
        getchar();
        break;
    case 6:
        system("cls");
        printf("New email : ");
        geta(contacts->email, 100);
        while (!isValidEmailAddress(contacts->email))
        {
            printf("Invalid Email, re-enter : ");
            geta(contacts->email, 100);
        }
        printf("Update Complete!\nPress any key to continue...");
        getchar();
        break;
    case 7:
        system("cls");
        printf("New address : ");
        geta(contacts->address, 100);
        printf("Update Complete!\nPress any key to continue...");
        getchar();
        break;
    case 8:
        system("cls");
        printf("New birthday : ");
        geta(contacts->birthday, 100);
        while (CheckName(contacts->birthday) == 0)
        {
            printf("Invalid name, re-enter : ");
            geta(contacts->birthday, 100);
        }
        printf("Update Complete!\nPress any key to continue...");
        getchar();
        break;
    case 9:
        system("cls");
        printf("New website : ");
        geta(contacts->website, 100);
        printf("Update Complete!\nPress any key to continue...");
        getchar();
        break;
    case 10:
        system("cls"); 
        printf("New note : ");
        geta(contacts->note, 100);
        printf("Update Complete!\nPress any key to continue...");
        getchar();
        break;
    case 11:
        break;
    }
    WriteFile(contacts, *count);
    return *contacts;
}
void delete (contact *contacts, int *choices, int *count2) // Function 3 : Delete Field
{
    ReadFile(contacts, count2);
    int i, j;
    for (i = *choices; i < *count2 - 1; i++)
    {
        contacts[i] = contacts[i + 1];
    }
    *count2 = *count2 - 1;
    WriteFile(contacts, *count2);
    printf("Delete completed\n");
    printf("Press any key to continue\n");
    getchar();
}
void addfield(contact *contacts, int choices, int *count2) // Function 4 : Add Field
{
    ReadFile(contacts, count2);
    int checkIsfield = 0;
    if (contacts[choices].fields.isField == 0)
    {
        system("cls");
        printf("Field name : ");
        geta(contacts[choices].fields.fname, 100);
        printf("Field numbers : ");
        geta(contacts[choices].fields.fnumbers, 100);
        contacts[choices].fields.isField = 1;
        checkIsfield = 1;
    }
    else
    {
        contacts[choices].fields.isField = 0;
        checkIsfield = 0;
    }
    if (checkIsfield == 0)
    {
        printf("Delete Field Complete\n");
    }
    else if (checkIsfield == 1)
    {
        printf("Add Field Complete\n");
    }
    WriteFile(contacts, *count2);
    printf("Press any key to continue");
    fflush(stdin);
    getchar();
}
int WriteFile(contact *contacts, int count) // Write File
{
    FILE *file;
    int filesave = 0;
    // File = .txt, "wb" is create or if !exists->create
    file = fopen("contacts.txt", "wb");
    if (file != NULL)
    {
        //Write the number of contact to file
        fwrite(&count, sizeof(int), 1, file);
        //Save the contact to file
        fwrite(contacts, sizeof(contact), count, file);
        fclose(file);
        filesave = 1;
    }
    return filesave;
}
int ReadFile(contact *contacts, int *count) // Read File
{
    FILE *file;
    int fileread = 0;
    file = fopen("contacts.txt", "rb");
    if (file != NULL)
    {
        //Read the number of contact from file
        fread(count, sizeof(int), 1, file);
        if (count > 0)
        {
            //Read contact from file then save back to contact
            fread(contacts, sizeof(contact), *count, file);
            fileread = 1;
        }
        fclose(file);
    }
    return fileread;
}
char checkinputphone(char *phone)
{
    int check = 0, check2;
    do
    {
        check = 0;
        check2 = strlen(phone);
        if (phone[0] < 48 && phone[0] != 43 || phone[0] > 57)
        {
            printf("Invalid phone number!\nPhone: ");
            geta(phone, 100);
            check = 1;
        }
        else
        {
            for (int i = 1; i < check2; i++)
            {
                if (phone[i] < 48 || phone[i] > 57)
                {
                    printf("Invalid phone number!\nPhone: ");
                    geta(phone, 100);
                    check = 1;
                    break;
                }
            }
        }
    } while (check == 1);
    return *phone;
}
char checkinputbirthday(char *birthday)
{
    int check = 0, check2;
    do
    {
        check = 0;
        check2 = strlen(birthday);
        if (birthday[0] < 48 && birthday[0] != 43 || birthday[0] > 57)
        {
            printf("Invalid Birthday!\nPhone: ");
            geta(birthday, 100);
            check = 1;
        }
        else
        {
            for (int i = 1; i < check2; i++)
            {
                if (birthday[i] < 48 || birthday[i] > 57)
                {
                    printf("Invalid Birthday!\nPhone: ");
                    geta(birthday, 100);
                    check = 1;
                    break;
                }
            }
        }
    } while (check == 1);
    return *birthday;
}
int CheckName(char *name)
{
    int correct = 0;
    for (int i = 0; i < strlen(name); i++)
    {
        for (int j = 48; j <= 57; j++)
        {
            if (name[i] == j)
                correct = 1;
        }
    }
    return correct;
}
bool isValidEmailAddress(char *EmailAddress)
{
    if (!EmailAddress) // If cannot read the Email Address...
        return 0;
    int AtOffset = -1;
    int DotOffset = -1;
    int Length = strlen(EmailAddress); // Length = StringLength (strlen) of EmailAddress
    for (int i = 0; i < Length; i++)
    {
        if (EmailAddress[i] == '@') // If one of the characters is @, store it's position in AtOffset
            AtOffset = (int)i;
        else if (EmailAddress[i] == '.') // Same, but with the dot
            DotOffset = (int)i;
    }
    if (AtOffset == -1 || DotOffset == -1) // If cannot find a Dot or a @
        return 0;
    if (AtOffset > DotOffset) // If the @ is after the Dot
        return 0;
    return !(DotOffset >= ((int)Length - 1)); //Chech there is some other letters after the Dot
}
