#pragma once

#include "data_structures.h"

// 工具函数声明
int login();
void clearInputBuffer();
void pressEnterToContinue();
void removeFromStudentEnrollList(Student* student, int courseId);
void removeFromTeacherCourseList(Teacher* teacher, int courseId);

