#pragma once
#include "data_structures.h"

// 管理员功能函数声明
void adminMenu(int adminId);
void initializeSystem();
void addCourseInfo();
void deleteCourseInfo();
void modifyCourseInfo();
void browseCourseInfo();
void statisticsMenu();
void queryMenu();

// 辅助函数
bool addTeacherToCourse(int teacherId, int courseId);

