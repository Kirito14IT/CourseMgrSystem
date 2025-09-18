//teacher.h
#pragma once
#include "data_structures.h"

// 教师功能函数声明
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

// 辅助函数
bool isTeacherOfCourse(int teacherId, int courseId);
Material* findMaterial(int courseId, int materialId);

//输出课程学习资料
void outputCourseMaterials(int teacherId);

