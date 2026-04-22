#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Passwords.h"
#include <sys/stat.h>
#include <errno.h>

void usermenu(char *username, char *key)
{

    int opt = 1;
    while (opt >0 && opt< 6)
    {
        opt=0;
        printf("1.add\n");
        printf("2.view\n");
        printf("3.search\n");
        printf("4.update\n");
        printf("5.delete\n");
        printf("6.logout\n");
        printf("Enter the option: ");
        scanf("%d", &opt);
        switch (opt)
        {
        case 1:
            addCredential(username, key);
            break;
        case 2:
            viewCredential(username, key);
            break;
        case 3:
            searchCredential(username, key);
            break;
        case 4:
            updateCredential(username, key);
            break;
        case 5:
            deleteCredential(username);
            break;
        case 6:
            printf("Successfully Logged Out!!");
            break;
        default:
            printf("Please select One from above X_X\n");
            break;
        }
    }
}
void GetUserFile(char *username, char *file)
{
    sprintf(file, "users_%s.csv", username);
}
void CreateBackup(char *username)
{
    char *file = malloc(MAX);
    char *backup = malloc(MAX);
    GetUserFile(username, file);
    sprintf(backup, "./backup/users_%s.bak", username);
    FILE *fptr1 = fopen(file, "r");
    FILE *fptr2 = fopen(backup, "w");
    if (fptr2 == NULL)
    {
        if (mkdir("backup", 0777) == 0)
        {
            printf("backup Folder gets successfully Created\n");
        }
    }
    fptr2 = fopen(backup, "w");
    int ch;
    while ((ch = fgetc(fptr1)) != EOF)
    {
        fputc(ch, fptr2);
    }
    free(file);
    free(backup);
    fclose(fptr1);
    fclose(fptr2);
}
void RestoreBackup(char *username)
{
    char *file = malloc(MAX);
    char *backup = malloc(MAX);
    sprintf(file, "users_%s.csv", username);
    sprintf(backup, "./backup/users_%s.bak", username);
    FILE *fptr2 = fopen(file, "w");
    FILE *fptr1 = fopen(backup, "r");
    int c;
    while ((c = fgetc(fptr1)) != EOF)
    {
        fputc(c, fptr2);
    }
    free(file);
    free(backup);
    fclose(fptr1);
    fclose(fptr2);
}
int GenerateCheckSum(char *filename)
{
    int c;
    int sum = 0;
    FILE *fptr = fopen(filename, "a");
    if (fptr != NULL)
    {
        while ((c = fgetc(fptr)) != EOF)
        {
            sum += c;
        }
        fclose(fptr);
        return sum;
    }
    if (fptr == NULL)
    {
        fclose(fptr);
        return -1;
    }
    return -1;
}
void CreateFolder()
{
    if (mkdir("backup", 0777) == -1)
    {
        if (errno != EEXIST)
            printf("Error in creating the backup folder");
    }
}
int VerifyCheckSum(char *username)
{
    char *file = malloc(MAX);
    char *backup = malloc(MAX);
    GetUserFile(username, file);
    sprintf(backup, "./backup/users_%s.bak", username);
    int currSum = GenerateCheckSum(file);
    int backupSum = GenerateCheckSum(backup);
    free(file);
    free(backup);
    if (currSum == -1)
        return 0;
    if (currSum == backupSum)
        return 1;
    else
        return 0;
}
