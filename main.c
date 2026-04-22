#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include "Passwords.h"
#include <errno.h>

int main()
{
    int choice;
    char Username[MAX];
    CreateFolder();
    while (1)
    {
        printf("\n=====PASSWORD MANAGER=====\n");
        printf("1. SignUp \n2. Login\n3. Delete Account\n4. Exit\n");
        printf("ENTER CHOICE : ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            if (signup())
            {
            }
            else
                printf("----SignUp Failed!!----\n");
            break;
        case 2:
            char *key = malloc(MAX);
            if (login(Username))
            {
                printf("----Welcome %s---\n", Username);
                printf("Enter your masterkey O_O : ");
                scanf("%s", key);
                // Checking for Data is saftey
                if (!VerifyCheckSum(Username))
                {
                    printf("####Data Corrupted! Restoring From Backup..####\n");
                    RestoreBackup(Username);
                }
                usermenu(Username, key);
            }
            else
                printf("Invalid username or password!!\n");
            free(key);
            break;
        case 3:
            Logout(Username);
            break;
        case 4:
            printf("......Exiting.....\n");
            exit(0);
            break;
        default:
            printf("____Invalid choice ____\n");
            break;
        }
        if (choice < 1 || choice > 4)
            break;
    }
}