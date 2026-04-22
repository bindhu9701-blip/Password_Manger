#include "Passwords.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
Credential getCredential(char *username)
{
    Credential details;
    printf("Website Name: ");
    scanf("%s", details.site);
    printf("Username in %s: ", details.site);
    scanf("%s", details.id);
    printf("Password in %s: ", details.site);
    scanf("%s", details.pwd);
    return details;
}
Credential details;
int checkCredential(char *username, Credential details)
{
    char *file = malloc(MAX);
    GetUserFile(username, file);
    FILE *fptr = fopen(file, "r");
    char *site = malloc(MAX);
    char *id = malloc(MAX);
    char *pwd = malloc(MAX);
    int notfound = 1;
    while (fscanf(fptr, "%s%s%s", site, id, pwd) == 3)
    {
        if (!strcmp(site, details.site) && !strcmp(id, details.id))
            notfound = 0;
    }
    fclose(fptr);
    free(id);
    free(pwd);
    free(site);
    free(file);
    return notfound;
}
void addCredential(char *username, char *key)
{
    char *file = malloc(MAX);
    GetUserFile(username, file);
    FILE *fptr = fopen(file, "a");
    printf("Enter the details to add :\n");
    details = getCredential(username);
    if (checkCredential(username, details))
    {
        int len = strlen(details.pwd);
        unsigned char data[MAX];
        memcpy(data, details.pwd, len);
        char hex[MAX * 2];
        EncryptDecrypt((unsigned char *)data, len, (unsigned char *)key, strlen(key));
        bytesToHex(data, len, hex);
        fprintf(fptr, "%s %s %s\n", details.site, details.id, hex);
        printf("Successfully added :)\n");
        fclose(fptr);
        CreateBackup(username);
    }
    else
    {
        printf("Given Username and Website were already present\n");
        fclose(fptr);
    }
    free(file);
}
void viewCredential(char *username, char *key)
{
    char *file = malloc(MAX);
    GetUserFile(username, file);
    FILE *fptr = fopen(file, "r");
    char *site = malloc(MAX);
    char *id = malloc(MAX);
    char *pwd = malloc(MAX);
    if (fptr == NULL)
    {
        printf("NO CREDENTIALS ARE PRESENT\n");
        free(file);
        free(site);
        free(id);
        free(pwd);
        return;
    }
    while (fptr != NULL && fscanf(fptr, "%s%s%s", site, id, pwd) == 3)
    {
        unsigned char data[MAX];
        char hex[MAX * 2];
        strcpy(hex, pwd);
        int len = hexToBytes(pwd, data);
        data[len] = '\0';
        EncryptDecrypt((unsigned char *)data, len, (unsigned char *)key, strlen(key));
        printf("\n+---------------+\n");
        printf("\nWebsite: %s\nUsername: %s\nPassword: %s\n", site, id, data);
        printf("\n+---------------+\n");
    }
    free(file);
    free(site);
    free(id);
    free(pwd);
    fclose(fptr);
}
int searchCredential(char *username, char *key)
{
    char *file = malloc(MAX);
    GetUserFile(username, file);
    FILE *fptr = fopen(file, "r");
    char *line = malloc(400);
    char *website = malloc(MAX);
    char *id = malloc(MAX);
    char *pwd = malloc(MAX);
    printf("Enter the website name for credentials: ");
    char *search = malloc(MAX);
    scanf("%s", search);
    int found = 0;
    while (fscanf(fptr, "%s%s%s", website, id, pwd) == 3)
    {
        if (strcmp(website, search) == 0)
        {
            unsigned char data[MAX];
            char hex[MAX * 2];
            strcpy(hex, pwd);
            int len = hexToBytes(pwd, data);
            data[len] = '\0';
            EncryptDecrypt((unsigned char *)data, len, (unsigned char *)key, strlen(key));
            printf("\nFound!!\n+---------------+\nWebsite: %s \nUsername: %s \nPassword: %s\n+---------------+\n", website, id, data);
            found = 1;
        }
    }
    free(file);
    fclose(fptr);
    free(line);
    free(id);
    free(pwd);
    free(website);
    free(search);
    return found;
}
void updateCredential(char *username, char *key)
{
    printf("Enter the details to get updated:\n");
    printf("Website: ");
    scanf("%s", details.site);
    printf("Username: ");
    scanf("%s", details.id);
    printf("New Password: ");
    scanf("%s", details.pwd);
    char *file = malloc(MAX);
    GetUserFile(username, file);
    FILE *fptr = fopen(file, "r");
    FILE *ftmp = fopen("temp.csv", "w+");
    char *website = malloc(MAX);
    char *id = malloc(MAX);
    char *pwd = malloc(MAX);
    int found = 0;
    while (fscanf(fptr, "%s%s%s", website, id, pwd) == 3)
    {
        if (!strcmp(website, details.site) && !strcmp(id, details.id))
        {
            int len = strlen(details.pwd);
            unsigned char data[MAX];
            memcpy(data, details.pwd, len);
            char hex[MAX * 2];
            EncryptDecrypt((unsigned char *)data, len, (unsigned char *)key, strlen(key));
            bytesToHex(data, len, hex);
            fprintf(ftmp, "%s %s %s\n", website, id, hex);
            found = 1;
        }
        else
        {
            fprintf(ftmp, "%s %s %s\n", website, id, pwd);
        }
    }
    free(website);
    free(id);
    free(pwd);
    fclose(ftmp);
    fclose(fptr);
    if (remove(file) != 0)
    {
        perror("Error in the removing the file");
    }
    rename("temp.csv", file);
    free(file);
    CreateBackup(username);
}
void deleteCredential(char *username)
{
    printf("Enter the details to be deleted:\n");
    printf("Website: ");
    scanf("%s", details.site);
    printf("Username: ");
    scanf("%s", details.id);
    char *file = malloc(MAX);
    GetUserFile(username, file);
    FILE *fptr = fopen(file, "r");
    FILE *ftmp = fopen("temp.csv", "w+");
    char *website = malloc(MAX);
    char *id = malloc(MAX);
    char *pwd = malloc(MAX);
    int found = 0;
    while (fscanf(fptr, "%s%s%s", website, id, pwd) == 3)
    {
        if (!strcmp(website, details.site) && !strcmp(id, details.id))
        {
            found = 1;
        }
        else
        {
            fprintf(ftmp, "%s %s %s\n", website, id, pwd);
        }
    }
    free(website);
    free(id);
    free(pwd);
    fclose(ftmp);
    fclose(fptr);
    remove(file);
    rename("temp.csv", file);
    free(file);
    CreateBackup(username);
}
