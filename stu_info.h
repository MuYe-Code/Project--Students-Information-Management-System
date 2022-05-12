#pragma once
#include"Global.h"

extern bool stuInfoFlag;

typedef struct stu_info {
	int stuId;
	char stuName[LenOfName];
	int courseId;
	double courseScore;
	struct stu_info* next;
}StuInfo;

void showStuInfo(const StuInfo* stu);
void searchAll(const StuInfo* list);
void searchByName(const StuInfo* listhead);
StuInfo* searchById(const StuInfo* listhead);
void addStuInfo(StuInfo** list);
void updateStuInfo(const StuInfo* listhead);
void deleteStuInfo(StuInfo** listhead);
void destroyStuInfoList(StuInfo* listhead);
