#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "user_account.h"
#include"system_init.h"
#include<stdio.h>
#include<stdlib.h>

bool userAccountFlag = false;

//���ݹ�ϣ��ʽ�õ��ַ����Ĺ�ϣֵ
int elf_hash(char* key) {
	int h = 0, g;
	while (*key) {
		h = (h << 4) + *key++;
		g = h & 0xf0000000;
		if (g)
			h ^= g >> 24;
		h &= ~g;
		return h % hashTableLen;
	}
}

//�������������˺��Ƿ���ڣ������ڣ��򷵻ؽ��ָ��
UserAccount* isAccounttExist(char* name, UserAccount* accountTable[]) {
	UserAccount* target = accountTable[elf_hash(name)];
	while (target != NULL) {
		if (strcmp(name, target->userName) == 0) return target;
		else target = target->next;
	}
	return NULL;
}

//����˻���Ϣ
void addUserAccount(UserAccount* accountTable[]) {
	char name[LenOfName];
	//��ȡ��Ϣ
	printf("Enter name: ");
	while(true) {
		scanf("%s", name);
		if (isAccounttExist(name,accountTable) == NULL) break;
		else printf("Duplicate name. Enter another name: ");
	}
	UserAccount* newNode = (UserAccount*)malloc(sizeof(UserAccount));
	if (newNode == NULL) {
		perror("Error in addUserAccount");
		system("pause");
		return;
	}
	newNode->next = NULL;
	strncpy(newNode->userName, name, LenOfName - 1);
	newNode->userName[LenOfName - 1] = '\0';
	printf("Enter passeword: ");
	scanf("%15s", newNode->userPassword);

	while (getchar() != '\n');
	while(strlen(newNode->userPassword < 6)) {
		puts("The password is too short, reenter your password (length between 6 and 15):");
		scanf("%15s", newNode->userPassword);
		while (getchar() != '\n');
	}

	printf("Set privilege(0-Administrator  1-User): ");
	while (true) {
		while (scanf("%d", &(newNode->privilege)) == 0) {
			while (getchar() != '\n');
			printf("Invalid input, please reset privilege: ");
		}
		while (getchar() != '\n');
		if (newNode->privilege == 0 || newNode->privilege == 1) break;
		else printf("Enter 0 or 1: ");
	}
	int pos = elf_hash(name);
	if (accountTable[pos] == NULL)	accountTable[pos] = newNode;
	else {
		UserAccount* tmp = accountTable[pos];
		while (tmp->next != NULL) tmp = tmp->next;
		tmp->next = newNode;
	}
	userAccountFlag = true;
	puts("Successfully saved.");
	system("pause");
	system("cls");
}

//�����˻���Ϣ���˻������ɸ���
void updateUserAccount(UserAccount* accountTable[]) {
	char name[LenOfName];
	printf("Enter the name of account: ");
	scanf("%15s", name);
	while (getchar() != '\n');
	UserAccount* target = isAccounttExist(name,accountTable);
	if (target == NULL) {
		puts("There is no account with name %s", name);
		return;
	}
	else {
		puts("Enter new password(Enter 0 when you don't want to change it): ");
		scanf("%15s", name);
		while (getchar() != '\n');

		if (strcmp(name, "0") != 0) {
			strcpy(target->userPassword, name);
		}

		while (strlen(name) < 6) {
			puts("The password is too short, reenter your password (length between 6 and 15):");
			scanf("%15s", name);
			if (strcmp(name, "0") != 0) {
				strcpy(target->userPassword, name);
			}
			else break;
			while (getchar() != '\n');
		}
		while (getchar() != '\n');

		printf("Enter new privilege: ");
		while (true) {
			while (scanf("%d", &target->privilege) == 0) {
				while (getchar() != '\n');
				printf("Invalid input, please reset privilege: ");
			}
			while (getchar() != '\n');
			if (target->privilege == 0 || target->privilege == 1)
				break;
			else printf("Enter 0 or 1: ");
		}
		userAccountFlag = true;
	}
	system("pause");
}

//ɾ���˻���Ϣ
void deleteUserAccount(UserAccount* accountTable[]) {
	char name[LenOfName];
	printf("Enter Account name: ");
	scanf("%15s", name);
	while (getchar() != '\n');
	int pos = elf_hash(name);
	if (accountTable[pos] == NULL) {
		puts("There is no account with name %s", name);
		return;
	}
	else if (strcmp(accountTable[pos]->userName, name) == 0) {
		printf("%-15s %-15s ", accountTable[pos]->userName, accountTable[pos]->userPassword);
		switch (accountTable[pos]->privilege) {
		case 0:
			printf("Privolege: Administrator\n");
			break;
		case 1:
			printf("Privolege: User\n");
			break;
		default:
			printf("Privolege: Unknown\n");
			break;
		}
		free(accountTable[pos]);
		accountTable[pos] = NULL;
		userAccountFlag = true;
		puts("Successfully deleted.");
		system("pause");
		system("cls");
		return;
	}
	else {
		UserAccount* cur = accountTable[pos];
		while (cur->next != NULL) {
			if (strcmp(name, cur->next->userName) == 0) {
				UserAccount* tmp = cur->next;

				printf("%-15s %-15s ", tmp->userName, tmp->userPassword);
				switch (tmp->privilege) {
				case 0:
					printf("Privolege: Administrator\n");
					break;
				case 1:
					printf("Privolege: User\n");
					break;
				default:
					printf("Privolege: Unknown\n");
					break;
				}

				cur->next = tmp->next;
				free(tmp);
				userAccountFlag = true;
				puts("Successfully deleted.");
				system("pause");
				system("cls");
				return;
			}
			else cur = cur->next;
		}
	}
	puts("There is no account with name %s.", name);
	system("pause");
	system("cls");
}

//�����˻��������˻���Ϣ
void searchUserAccount(UserAccount* accountTable[]) {
	char name[LenOfName];
	printf("Enter the name of account: ");
	scanf("%15s", name);
	while (getchar() != '\n');
	UserAccount* target = isAccounttExist(name,accountTable);
	if (target == NULL) {
		puts("There is no account with name %s", name);
		return;
	}
	else {
		printf("User Name: %-16s\tPassword: %-16s\t",target->userName,target->userPassword);
		if (target->privilege == 0) {
			puts("Privilege: Administrator");
		}
		else if (target->privilege == 1) {
			puts("Privilege: User");
		}
		else puts("Privilege: Unknown");
	}
	system("pause");
}

//�������д���˻���Ϣ�Ŀռ�
void destroyAccountTable(UserAccount* accountTable[]) {
	for (int i = 0; i < hashTableLen; i++) {
		while (accountTable[i] != NULL) {
			UserAccount* tmp = accountTable;
			accountTable[i] = tmp->next;
			free(tmp);
		}
	}
}