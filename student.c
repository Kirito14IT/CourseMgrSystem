//student.c
#include "student.h"
#include "bplus_tree.h"
#include "utils.h"

void studentMenu(int studentId) {
    int choice;

    while (1) {
        printf("\n=== ѧ���˵� (ID: %d) ===\n", studentId);
        printf("1. ѡ��\n");
        printf("2. ��ѯ���˿γ���Ϣ\n");
        printf("0. �˳�\n");
        printf("��ѡ�����: ");

        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
        case 1: {
            int courseId;
            printf("������Ҫѡ��Ŀγ�ID: ");
            scanf("%d", &courseId);
            clearInputBuffer();
            enrollCourse(studentId, courseId);
            break;
        }
        case 2:
            queryStudentCourses(studentId);
            break;
        case 0:
            return;
        default:
            printf("��Чѡ�������ԣ�\n");
        }

        pressEnterToContinue();
    }
}

bool enrollCourse(int studentId, int courseId) {
    // ���γ��Ƿ����
    Course* course = searchCourseById(courseId);
    if (course == NULL) {
        printf("�γ̲����ڣ�\n");
        return false;
    }

    // ���γ�����
    if (course->currentEnrolled >= course->capacity) {
        printf("�γ���������ǰ����: %d/%d\n", course->currentEnrolled, course->capacity);
        return false;
    }

    // ���ѧ���Ƿ����
    Student* student = searchStudentById(studentId);
    if (student == NULL) {
        printf("ѧ�������ڣ�\n");
        return false;
    }

    // ����Ƿ���ѡ��ÿγ�
    EnrollNode* current = student->enrolledCourses;
    while (current != NULL) {
        if (current->courseId == courseId) {
            printf("����ѡ��ÿγ̣�\n");
            return false;
        }
        current = current->next;
    }

    // ��ӵ�ѡ�μ�¼��
    EnrollRecord* newRecord = (EnrollRecord*)malloc(sizeof(EnrollRecord));
    newRecord->studentId = studentId;
    newRecord->courseId = courseId;
    newRecord->grade = -1;  // δ¼��ɼ�
    newRecord->next = enrollHead;
    enrollHead = newRecord;

    // ��ӵ�ѧ������ѡ������
    EnrollNode* newEnroll = (EnrollNode*)malloc(sizeof(EnrollNode));
    newEnroll->courseId = courseId;
    newEnroll->grade = -1;
    newEnroll->next = student->enrolledCourses;
    student->enrolledCourses = newEnroll;

    // ���¿γ�ѡ������
    course->currentEnrolled++;

    printf("ѡ�γɹ����γ�: %s\n", course->courseName);
    return true;
}

void queryStudentCourses(int studentId) {
    Student* student = searchStudentById(studentId);
    if (student == NULL) {
        printf("ѧ�������ڣ�\n");
        return;
    }

    printf("\n=== %s ��ѡ����Ϣ ===\n", student->name);
    printf("�γ�ID\t�γ���\t\tѧ��\t�ɼ�\t\t�ڿ�ʱ��\t\t�ص�\n");
    printf("------------------------------------------------------------------------\n");

    EnrollNode* current = student->enrolledCourses;
    int courseCount = 0;
    int totalCredits = 0;

    while (current != NULL) {
        Course* course = searchCourseById(current->courseId);
        if (course != NULL) {
            printf("%d\t%-15s\t%d\t", course->courseId, course->courseName, course->credits);

            if (current->grade >= 0) {
                printf("%.2f\t\t", current->grade);
            }
            else {
                printf("δ¼��\t\t");
            }

            printf("%-20s\t%s\n", course->schedule, course->location);

            courseCount++;
            totalCredits += course->credits;
        }
        current = current->next;
    }

    if (courseCount == 0) {
        printf("����ѡ�μ�¼��\n");
    }
    else {
        printf("\n�ܹ�ѡ�� %d �ſγ̣���ѧ��: %d\n", courseCount, totalCredits);
    }
}
