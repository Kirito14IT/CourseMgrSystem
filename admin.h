#pragma once
#include "data_structures.h"

// ����Ա���ܺ�������
void adminMenu(int adminId);
void initializeSystem();
void addCourseInfo();
void deleteCourseInfo();
void modifyCourseInfo();
void browseCourseInfo();
void statisticsMenu();
void queryMenu();

// ��������
bool addTeacherToCourse(int teacherId, int courseId);

