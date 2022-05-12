#pragma once
#include<stdbool.h>

#define hashTableLen 100
#define LenOfName 16

extern bool userAccountFlag;

//�û��������볤�Ⱦ�������15���ַ�
typedef struct user_account {
	char userName[LenOfName];
	char userPassword[LenOfName];
	int privilege;
	struct user_account* next;
}UserAccount;


int elf_hash(char* key);
UserAccount* isAccounttExist(char* name, UserAccount* accountTable[]);
void addUserAccount(UserAccount* accountTable[]);
void updateUserAccount(UserAccount* accountTable[]);
void deleteUserAccount(UserAccount* accountTable[]);
void searchUserAccount(const UserAccount* accountTable[]);
void destroyAccountTable(UserAccount* accountTable[]);
