#define _CRT_SECURE_NO_WARNINGS
#include"stu_info.h"
#include"system_init.h"
#include"user_account.h"
#include<stdio.h>
#include<stdlib.h>



void main(void) {
	InitInfo* allInfo = (InitInfo*)calloc(1, sizeof(InitInfo));
	if (allInfo == NULL) {
		perror("Error in main");
		exit(EXIT_FAILURE);
	}
	loadData(allInfo);
	int privilege = logIn(allInfo->accountTable);
	showMenue(privilege, allInfo);
	return 0;
}
