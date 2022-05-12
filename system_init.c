#define _CRT_SECURE_NO_WARNINGS
#include"system_init.h"
#include"Global.h"
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

//系统初始化
void loadData(InitInfo* allInfo) {
	puts("读取文件名");
	FILE* fp = fopen("Configure.txt", "r");
	if (fp == NULL) {
		perror("Error in main");
		exit(EXIT_FAILURE);
	}
	fscanf(fp, "%s", allInfo->infoFileName);
	fscanf(fp, "%s", allInfo->accountFileName);
	fclose(fp);
	puts("读取文件名成功");
	puts("学生信息初始化");
	allInfo->stuInfoList = stuInfoInit(allInfo->infoFileName);
	puts("学生信息初始化成功");
	puts("账号信息初始化");
	userAccountInit(allInfo->accountFileName, allInfo->accountTable);
	puts("账号信息初始化成功");
	system("cls");
}

//登录模块，返回权限代码
int logIn(const UserAccount* accountTable[]) {
	char name[LenOfName];
	char password[LenOfName];
	while (true) {
		printf("Enter account name: \n");
		scanf("%15s", name);
		while (getchar() != '\n');
		printf("Enter password: \n");
		int i = 0;
		for (i = 0; i < LenOfName - 1; i++) {
			password[i] = _getch();
			if (password[i] == '\r') {
				password[i] = '\0';
				break;
			}
			if (password[i] == '\b') {
				printf("\b \b");
				i -= 2;
			}
			else putchar('*');
			
		}
		password[i] = '\0';
		system("cls");
		UserAccount* target = isAccounttExist(name, accountTable);
		if (target == NULL || strcmp(target->userPassword, password) != 0) {
			puts("Wrong Name Or Wrong Password.");
		}
		else return target->privilege;
	}
}

//显示菜单及命令执行函数
void showMenue(int privilege,InitInfo* allInfo) {
	while (true) {
		puts("*******************************************************************************************************************************************************************************************************************");
		puts("*                                                                                      Student Information Management System                                                                                      *");
		puts("*******************************************************************************************************************************************************************************************************************");
		puts("\n");
		if (privilege == 0) {
			puts("                                                                                      1. Search      student      information\n");
			puts("                                                                                      2. Add         student      information\n");
			puts("                                                                                      3. Update      student      information\n");
			puts("                                                                                      4. Delete      student      information\n");
			puts("                                                                                      5. Add           user         account\n");
			puts("                                                                                      6. Update        user         account\n");
			puts("                                                                                      7. Delete        user         account\n");
			puts("                                                                                      8. Search        user         account\n");
			puts("                                                                                      9. Exit\n");

			printf("\nEnter your selection: ");
			int selection = 0;
			scanf("%d", &selection  );
			switch (selection) {
			case 1:
				system("cls");
				showSearchMenue(privilege,allInfo);
				break;
			case 2:
				system("cls");
				addStuInfo(&(allInfo->stuInfoList));
				saveStuInfoList(allInfo->infoFileName, allInfo->stuInfoList);
				break;
			case 3:
				system("cls");
				updateStuInfo(allInfo->stuInfoList);
				saveStuInfoList(allInfo->infoFileName, allInfo->stuInfoList);
				break;
			case 4:
				system("cls");
				deleteStuInfo(&(allInfo->stuInfoList));
				saveStuInfoList(allInfo->infoFileName, allInfo->stuInfoList);
				break;
			case 5:
				system("cls");
				addUserAccount(allInfo->accountTable);
				saveUserAccountList(allInfo->accountFileName, allInfo->accountTable);
				break;
			case 6:
				system("cls");
				updateUserAccount(allInfo->accountTable);
				saveUserAccountList(allInfo->accountFileName, allInfo->accountTable);
				break;
			case 7:
				system("cls");
				deleteUserAccount(allInfo->accountTable);
				saveUserAccountList(allInfo->accountFileName, allInfo->accountTable);
				break;
			case 8:
				system("cls");
				searchUserAccount(allInfo->accountTable);
				break;
			case 9:
				exit(EXIT_SUCCESS);
				destroyStuInfoList(allInfo->stuInfoList);
				destroyAccountTable(allInfo->accountTable);
				break;
			default: {
				puts("Invalid Inputs!");
				system("pause");
			}
			}
			system("cls");
		}
		else {
			puts("                                                                                      1. Search      student      information\n");
			puts("                                                                                      9. Exit\n");

			printf("\nEnter your selection: ");
			int selection = 0;
			scanf("%d", &selection);
			switch (selection) {
			case 1:
				system("cls");
				showSearchMenue(privilege, allInfo);
				break;
			case 9:
				exit(EXIT_SUCCESS);
				break;
			default: {
				puts("Invalid Inputs!");
				system("pause");
			}
			}
			system("cls");
		}
	}
}

//搜索菜单
void showSearchMenue(int privilege, InitInfo* allInfo) {
	while (true) {
		if (privilege == 0) puts("0. Search All");
		puts("1. Search by name");
		puts("2. Search by id");
		puts("3. Return");

		printf("\nEnter your selection: ");
		int selection = 0;
		scanf("%d", &selection);
		switch (selection) {
		case 0:
			system("cls");
			if (privilege == 0)
				searchAll(allInfo->stuInfoList);
			else {
				puts("Invalid Inputs!");
				system("pause");
			}
			break;
		case 1:
			system("cls");
			searchByName(allInfo->stuInfoList);
			break;
		case 2:
			system("cls");
			searchById(allInfo->stuInfoList);
			break;
		case 3:
			return;
			break;
		default: {
			puts("Invalid Inputs!");
			system("pause");
		}
		}
		system("cls");
	}
}

//学生信息初始化
StuInfo* stuInfoInit(const char* filename) {
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		perror("Error in stuInfoInit");
		exit(EXIT_FAILURE);
	}
	StuInfo* head = NULL, * cur = head;
	int id = 0;
	while (fscanf(fp, "%d", &id) != EOF) {
		StuInfo* newNode = (StuInfo*)malloc(sizeof(StuInfo));
		if (newNode == NULL) {
			perror("Error in stuInfoInit");
			exit(EXIT_FAILURE);
		}
		if (head == NULL) {
			head = newNode;
			cur = newNode;
		}
		else cur->next = newNode;
		newNode->next = NULL;
		newNode->stuId = id;
		char tmp;
		while ((tmp = fgetc(fp)) == ' ' || tmp == '\t');
		newNode->stuName[0] = tmp;
		for (int i = 1; i < LenOfName - 1; i++) {
			newNode->stuName[i] = fgetc(fp);
			if (newNode->stuName[i] == ' '|| newNode->stuName[i] == '\t') {
				newNode->stuName[i] = '\0';
				break;
			}
		}
		fscanf(fp, "%d", &(newNode->courseId));
		fscanf(fp, "%lf", &(newNode->courseScore));
		while (fgetc(fp) != '\n');
	}
	fclose(fp);
	return head;
}

//将链表中数据存入文件
void saveStuInfoList(const char* filename, const StuInfo* stuInfoList) {
	if (!stuInfoFlag) return;

	FILE* fp = fopen(filename, "w");
	if (fp == NULL) {
		perror("Error in saveStuInfoList");
		return;
	}
	while (stuInfoList != NULL) {
		fprintf(fp,"%-15d %-15s %-8d %-8.2lf\n", stuInfoList->stuId, stuInfoList->stuName, stuInfoList->courseId, stuInfoList->courseScore);
		stuInfoList = stuInfoList->next;
	}
	stuInfoFlag = false;
	fclose(fp);
}

//账号信息初始化
void userAccountInit(const char* filename, UserAccount* accountTable[]) {
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		perror("Error in userAccountInit");
		exit(EXIT_FAILURE);
	}
	char name[LenOfName];
	while (fscanf(fp, "%15s", name) != EOF) {
		UserAccount* newNode = (UserAccount*)malloc(sizeof(UserAccount));
		if (newNode == NULL) {
			perror("Error in userAccountInit");
			exit(EXIT_FAILURE);
		}
		else {

			newNode->next = NULL;
			strcpy(newNode->userName, name);
			fscanf(fp, "%15s", newNode->userPassword);
			fscanf(fp, "%d", &(newNode->privilege));
			//while ((tmp= fgetc(fp) != '\n')&&tmp!=EOF);
			int pos = elf_hash(name);
			if (accountTable[pos] == NULL) {
				accountTable[pos] = newNode;
			}
			else {
				UserAccount* cur = accountTable[pos];
				while (cur->next != NULL) cur = cur->next;
				cur->next = newNode;
			}
		}
	}
	fclose(fp);
}

//将哈希表中的数据存入文件
void saveUserAccountList(const char* filename, UserAccount* accountTable[]) {
	if (userAccountFlag) {
		FILE* fp = fopen(filename, "w");
		if (fp == NULL) {
			perror("Error in saveUserAccountList");
			system("pause");
			return;
		}
		UserAccount* cur = NULL;
		for (int i = 0; i < hashTableLen; i++) {
			cur = accountTable[i];
			while (cur != NULL) {
				fprintf(fp,"%-15s %-15s %-8d\n", cur->userName, cur->userPassword, cur->privilege);
				cur = cur->next;
			}
		}
		userAccountFlag = false;
	}
}