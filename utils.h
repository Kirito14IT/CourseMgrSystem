#pragma once

#include "data_structures.h"

// ���ߺ�������
int login();
void clearInputBuffer();
void pressEnterToContinue();
void removeFromStudentEnrollList(Student* student, int courseId);
void removeFromTeacherCourseList(Teacher* teacher, int courseId);

