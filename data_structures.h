#pragma once

// ��ÿ���ļ���ͷ������д���,���Ա���һЩ������Ϣ
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// B+���ڵ�ṹ����������
typedef struct BPlusTreeNode {
    int* keys;
    void** data;
    struct BPlusTreeNode** children;
    struct BPlusTreeNode* next;
    int keyCount;
    bool isLeaf;
} BPlusTreeNode;

// ѧϰ���Ͻṹ��
typedef struct Material {
    int materialId;
    char materialName[100];
    struct Material* next;
} Material;

// ѧ������ѡ�νڵ�
typedef struct EnrollNode {
    int courseId;
    float grade;
    struct EnrollNode* next;
} EnrollNode;

// ��ʦ�����ڿνڵ�
typedef struct CourseNode {
    int courseId;
    struct CourseNode* next;
} CourseNode;

// ����Ա�ṹ��
typedef struct Admin {
    int adminId;        // 0-99
    char password[20];
    char name[30];
} Admin;

// ��ʦ�ṹ��
typedef struct Teacher {
    int teacherId;      // 100-999
    char password[20];
    char name[30];
    struct CourseNode* taughtCourses;  // �����ڿ�����
} Teacher;

// ѧ���ṹ��
typedef struct Student {
    int studentId;      // 1000+
    char password[20];
    int grade;
    char stuNum[20];
    char name[30];
    struct EnrollNode* enrolledCourses;  // ����ѡ������
} Student;

// �γ̽ṹ��
typedef struct Course {
    int courseId;
    char courseName[50];
    int credits;
    char schedule[100];
    char location[50];
    int capacity;           // �γ�����
    int currentEnrolled;    // ��ǰѡ������
    struct Material* materialHead;  // ѧϰ��������
} Course;

// ѡ�μ�¼
typedef struct EnrollRecord {
    int studentId;
    int courseId;
    float grade;        // �ɼ���-1��ʾδ¼��
    struct EnrollRecord* next;
} EnrollRecord;

// �ڿμ�¼
typedef struct TeachRecord {
    int teacherId;
    int courseId;
    struct TeachRecord* next;
} TeachRecord;

// �ɼ�ͳ�ƽṹ
typedef struct GradeStats {
    int above90;
    int between60_90;
    int below60;
    int totalStudents;
} GradeStats;

// ȫ�ֱ�������
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
