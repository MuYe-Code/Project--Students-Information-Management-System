#pragma once
#include "stu_info.h"
#include "user_account.h"
#include "Global.h"

typedef struct initInfo {
	StuInfo* stuInfoList;
	char accountFileName[24];
	char infoFileName[24];
	UserAccount* accountTable[hashTableLen];
}InitInfo;

void loadData(InitInfo* allInfo);
int logIn(const UserAccount* accountTable[]);
void showMenue(int privilege, InitInfo* allInfo);
void showSearchMenue(int privilege, InitInfo* allInfo);
StuInfo* stuInfoInit(const char* filename);
void saveStuInfoList(const char* filename, const StuInfo* stuInfoList);
void userAccountInit(const char* filename, UserAccount* accountTable[]);
void saveUserAccountList(const char* filename, UserAccount* accountTable[]);
