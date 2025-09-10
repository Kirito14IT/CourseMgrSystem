#pragma once
#include "data_structures.h"

// ��ʦ���ܺ�������
void teacherMenu(int teacherId);
void addCourseMaterial(int teacherId);
void modifyCourseMaterial(int teacherId);
void deleteCourseMaterial(int teacherId);
void addStudentGrade(int teacherId);
void modifyStudentGrade(int teacherId);
void teacherQueryMenu(int teacherId);
GradeStats statisticsCourseGrades(int teacherId, int courseId);

// ��������
bool isTeacherOfCourse(int teacherId, int courseId);
Material* findMaterial(int courseId, int materialId);
