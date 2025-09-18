//teacher.h
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
void queryStudentsByGradeRange(int teacherId);
void queryMaterialUsage(int teacherId);

GradeStats statisticsCourseGrades(int teacherId, int courseId);

// ��������
bool isTeacherOfCourse(int teacherId, int courseId);
Material* findMaterial(int courseId, int materialId);

//����γ�ѧϰ����
void outputCourseMaterials(int teacherId);

