#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "stu_info.h"
#include "system_init.h"
#include <stdlib.h>
#include <stdio.h>

bool stuInfoFlag = false;

//显示指定学生信息
void showStuInfo(const StuInfo* stu) {
	printf("%-16d%-16s", stu->stuId, stu->stuName);
	switch (stu->courseId) {
	case 0:
		printf("Chinese\t");
		break;
	case 1:
		printf("Japanese");
		break;
	case 2:
		printf("English\t");
		break;
	}
	printf("\t%.2lf\n", stu->courseScore);
}

//显示所有学生信息
void searchAll(const StuInfo* listhead) {
	if (listhead == NULL) {
		puts("No Student Infomation Exist!");
		return;
	}

	puts("StudentNumber\tStudentName\tCourse\t\tScore");
	while (listhead != NULL) {
		showStuInfo(listhead);
		listhead = listhead->next;
	}
	system("pause");
	system("cls");
}

//根据姓名查找并显示学生信息
void searchByName(const StuInfo* listhead) {
	char name[LenOfName];
	printf("Enter Student Name: ");
	scanf("%15s", name);

	while (listhead != NULL) {
		if (strcmp(listhead->stuName, name) == 0) {
			puts("StudentNumber\tStudentName\tCourse\t\tScore");
			showStuInfo(listhead);
			break;
		}
		else listhead = listhead->next;
	}
	if (listhead == NULL) {
		printf("There is no student named %s\n", name);
	}
	system("pause");
	system("cls");
}

//根据学号查找并显示学生信息
StuInfo* searchById(const StuInfo* listhead) {
	int id = -1;
	printf("Enter Student Number: ");
	scanf("%d", &id);

	while (listhead != NULL) {
		if (listhead->stuId == id) {
			puts("StudentNumber\tStudentName\tCourse\t\tScore");
			showStuInfo(listhead);
			break;
		}
		else listhead = listhead->next;
	}
	if (listhead == NULL) {
		printf("There is no student with student number %d\n", id);
	}
	system("pause");
	return listhead;
}

//添加学生信息
void addStuInfo(StuInfo** list) {
	StuInfo* newNode = (StuInfo*)malloc(sizeof(StuInfo));
	if (newNode == NULL) {
		perror("Error in addStuInfo");
		exit(EXIT_FAILURE);
	}
	/*输入学号*/
	printf("Enter Student Number: ");
	while (scanf("%d", &(newNode->stuId)) == 0) {
		while (getchar() != '\n');
		printf("Wrong Number, Reenter Student Number: ");
	}
	while (getchar() != '\n');
	/*检查链表是否为空且学号是否重复*/
	if (*list == NULL) {
		*list = newNode;
		*list = newNode;
		newNode->next = NULL;
	}
	else {
		StuInfo* cur = (*list);
		/*寻找插入位置*/
		if (cur->stuId > newNode->stuId) {
			newNode->next = cur;
			(*list) = newNode;
		}
		else {
			while ((cur->next != NULL) && (cur->next->stuId <= newNode->stuId)) {
				if (cur->next->stuId == newNode->stuId) {
					puts("Add Student Infomation Failed. Duplicate Student Numbers.");
					free(newNode);
					return;
				}
				else cur = cur->next;
			}

			if (cur->next == NULL) {
				cur->next = newNode;
				newNode->next = NULL;
			}
			else {
				newNode->next = cur->next;
				cur->next = newNode;
			}
		}
	}
	/*若学号不重复，读取其他信息*/
	printf("Enter Student Name: ");
	scanf("%15s", newNode->stuName);
	while (getchar() != '\n');
	printf("Enter Student Course Id(0-Chinese  1-Japanese  2-English): ");
	while (true) {
		scanf("%d", &(newNode->courseId));
		while (getchar() != '\n');
		if (newNode->courseId >= 0 || newNode->courseId<=2)
			break;
		else printf("Enter a number in [0,2]: ");
	} 
	printf("Enter Course Score: ");
	while (scanf("%lf", &(newNode->courseScore))== 0) {
		while (getchar() != '\n');
		printf("Wrong Score, Reenter Course Score: ");
	}
	while (getchar() != '\n');
	puts("Successfully saved.");
	stuInfoFlag = true;
	system("pause");
	system("cls");
}

//更新学生信息
void updateStuInfo(const StuInfo* listhead) {
	StuInfo* target = searchById(listhead);
	if (target != NULL) {
		showStuInfo(target);
		printf("Enter New Student Name: ");
		scanf("%15s", target->stuName);
		while (getchar() != '\n');
		printf("Enter New Student Course Id (0-Chinese  1-Japanese  2-English): ");
		while (scanf("%d", &target->courseId) == 0) {
			while (getchar() != '\n');
			printf("Wrong Course Id, Reenter Course Id: ");
		}
		while (getchar() != '\n');
		printf("Enter New Course Score: ");
		while (scanf("%lf", &target->courseScore) == 0) {
			while (getchar() != '\n');
			printf("Wrong Course Score, Reenter Course Score: ");
		}
		while (getchar() != '\n');
		puts("Successfully saved.");
	}
	stuInfoFlag = true;
	system("pause");
	system("cls");
}

//删除学生信息
void deleteStuInfo(StuInfo** listhead) {
	int id = -1;
	printf("Enter Student Number: ");
	while (scanf("%d", &id) == 0) {
		while (getchar() != '\n');
		printf("Wrong Number, Reenter Student Number: ");
	}
	while (getchar() != '\n');
	StuInfo* cur = *listhead;
	//空链表没有信息
	if (cur == NULL) {
		printf("There is no student with student number %d\n", id);
		return;
	}
	//头结点就是要删除的结点
	if (cur->stuId == id) {
		showStuInfo(cur);
		(*listhead) = cur->next;
		free(cur);
		puts("Successfully deleted.");
		stuInfoFlag = true;
		system("pause");
		system("cls");
		return;
	}
	while ((cur->next != NULL) && (cur->next->stuId <= id)) {
		if (cur->next->stuId == id) {
			StuInfo* tmp = cur->next;
			showStuInfo(tmp);
			printf("Sure you want to delete this informatin? (Y:yes  N:no): ");
			
			while (true) {
				char selection = getchar();
				while (getchar() != '\n');
				if (selection == 'Y' || selection == 'y') {
					cur->next = tmp->next;
					free(tmp);
					puts("Successfully deleted.");
					stuInfoFlag = true;
					break;
				}
				else if (selection == 'N' || selection == 'n') return;
				else printf("Enter Y for Yes and N for No: ");
			}
		}
		else cur = cur->next;
	}
	if(cur->next==NULL) printf("There is no student with student number %d\n", id);
	system("pause");
	system("cls");
}

void destroyStuInfoList(StuInfo* listhead) {
	while (listhead != NULL) {
		StuInfo* tmp = listhead;
		listhead = listhead->next;
		free(tmp);
	}
}
