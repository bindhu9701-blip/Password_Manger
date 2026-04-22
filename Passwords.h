#include <stdio.h>
#ifndef Passwords
#define Passwords
#define MAX 256
typedef struct Credential
{
    char site[MAX];
    char id[MAX];
    char pwd[MAX];
} Credential;
// user Sigin
int signup();
int login(char *username);
void Logout(char *username);

// if logged in then menu will take care from there
void usermenu(char *username, char *key);

// Manage credentials of each user
void addCredential(char *username, char *key);
void viewCredential(char *username, char *key);
void deleteCredential(char *username);
void updateCredential(char *username, char *key);
int searchCredential(char *username, char *key);

// Backup and safety check;
void GetUserFile(char *username, char *filename);
void CreateBackup(char *username);
void RestoreBackup(char *username);
int GenerateCheckSum(char *filename);
void CreateFolder();
int VerifyCheckSum(char *username);

// security
void hashPassword(const char *password, char output[65]);
void EncryptDecrypt(unsigned char *pwd, int len, unsigned char *key, int key_len);
void bytesToHex(unsigned char *data, int len, char *hex);
int hexToBytes(char *hex, unsigned char *data);

#endif
