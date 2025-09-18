//admin.h
#pragma once
#include "data_structures.h"
#include "student.h"
// 管理员功能函数声明
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

// 辅助函数
bool addTeacherToCourse(int teacherId, int courseId);

