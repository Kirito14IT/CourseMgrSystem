//admin.h
#pragma once
#include "data_structures.h"
#include "student.h"
// ����Ա���ܺ�������
void adminMenu(int adminId);
void initializeSystem();
void addCourseInfo();
void deleteCourseInfo();
void modifyCourseInfo();
void browseCourseInfo();

void statisticsMenu();
void statisticsCourseCapacityCallback(void* data);
void statisticsCourseCapacity();
void statisticsCreditsCallback(void* data);
void statisticsCreditsDistribution();

void queryMenu();
void queryCoursesByIdRange();
void queryCoursesByTeacherName();

// ��������
bool addTeacherToCourse(int teacherId, int courseId);

