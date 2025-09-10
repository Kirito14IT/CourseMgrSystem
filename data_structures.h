#pragma once

// 在每个文件开头添加这行代码,可以避免一些警告信息
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// B+树节点结构（简化声明）
typedef struct BPlusTreeNode {
    int* keys;
    void** data;
    struct BPlusTreeNode** children;
    struct BPlusTreeNode* next;
    int keyCount;
    bool isLeaf;
} BPlusTreeNode;

// 学习资料结构体
typedef struct Material {
    int materialId;
    char materialName[100];
    struct Material* next;
} Material;

// 学生个人选课节点
typedef struct EnrollNode {
    int courseId;
    float grade;
    struct EnrollNode* next;
} EnrollNode;

// 教师个人授课节点
typedef struct CourseNode {
    int courseId;
    struct CourseNode* next;
} CourseNode;

// 管理员结构体
typedef struct Admin {
    int adminId;        // 0-99
    char password[20];
    char name[30];
} Admin;

// 教师结构体
typedef struct Teacher {
    int teacherId;      // 100-999
    char password[20];
    char name[30];
    struct CourseNode* taughtCourses;  // 个人授课链表
} Teacher;

// 学生结构体
typedef struct Student {
    int studentId;      // 1000+
    char password[20];
    int grade;
    char stuNum[20];
    char name[30];
    struct EnrollNode* enrolledCourses;  // 个人选课链表
} Student;

// 课程结构体
typedef struct Course {
    int courseId;
    char courseName[50];
    int credits;
    char schedule[100];
    char location[50];
    int capacity;           // 课程容量
    int currentEnrolled;    // 当前选课人数
    struct Material* materialHead;  // 学习资料链表
} Course;

// 选课记录
typedef struct EnrollRecord {
    int studentId;
    int courseId;
    float grade;        // 成绩，-1表示未录入
    struct EnrollRecord* next;
} EnrollRecord;

// 授课记录
typedef struct TeachRecord {
    int teacherId;
    int courseId;
    struct TeachRecord* next;
} TeachRecord;

// 成绩统计结构
typedef struct GradeStats {
    int above90;
    int between60_90;
    int below60;
    int totalStudents;
} GradeStats;

// 全局变量声明
extern Admin adminArray[100];
extern Teacher teacherArray[900];
extern int adminCount;
extern int teacherCount;
extern int currentAdminId;
extern int currentTeacherId;
extern int currentStudentId;
extern int currentCourseId;
extern int currentMaterialId;

extern BPlusTreeNode* studentRoot;
extern BPlusTreeNode* courseRoot;
extern EnrollRecord* enrollHead;
extern TeachRecord* teachHead;
