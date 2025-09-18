//student.c
#include "student.h"
#include "bplus_tree.h"
#include "utils.h"

void studentMenu(int studentId) {
    int choice;

    while (1) {
        printf("\n=== 学生菜单 (ID: %d) ===\n", studentId);
        printf("1. 选课\n");
        printf("2. 查询个人课程信息\n");
        printf("0. 退出\n");
        printf("请选择操作: ");

        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
        case 1: {
            int courseId;
            printf("请输入要选择的课程ID: ");
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
            printf("无效选择，请重试！\n");
        }

        pressEnterToContinue();
    }
}

bool enrollCourse(int studentId, int courseId) {
    // 检查课程是否存在
    Course* course = searchCourseById(courseId);
    if (course == NULL) {
        printf("课程不存在！\n");
        return false;
    }

    // 检查课程容量
    if (course->currentEnrolled >= course->capacity) {
        printf("课程已满！当前容量: %d/%d\n", course->currentEnrolled, course->capacity);
        return false;
    }

    // 检查学生是否存在
    Student* student = searchStudentById(studentId);
    if (student == NULL) {
        printf("学生不存在！\n");
        return false;
    }

    // 检查是否已选择该课程
    EnrollNode* current = student->enrolledCourses;
    while (current != NULL) {
        if (current->courseId == courseId) {
            printf("您已选择该课程！\n");
            return false;
        }
        current = current->next;
    }

    // 添加到选课记录表
    EnrollRecord* newRecord = (EnrollRecord*)malloc(sizeof(EnrollRecord));
    newRecord->studentId = studentId;
    newRecord->courseId = courseId;
    newRecord->grade = -1;  // 未录入成绩
    newRecord->next = enrollHead;
    enrollHead = newRecord;

    // 添加到学生个人选课链表
    EnrollNode* newEnroll = (EnrollNode*)malloc(sizeof(EnrollNode));
    newEnroll->courseId = courseId;
    newEnroll->grade = -1;
    newEnroll->next = student->enrolledCourses;
    student->enrolledCourses = newEnroll;

    // 更新课程选课人数
    course->currentEnrolled++;

    printf("选课成功！课程: %s\n", course->courseName);
    return true;
}

void queryStudentCourses(int studentId) {
    Student* student = searchStudentById(studentId);
    if (student == NULL) {
        printf("学生不存在！\n");
        return;
    }

    printf("\n=== %s 的选课信息 ===\n", student->name);
    printf("课程ID\t课程名\t\t学分\t成绩\t\t授课时间\t\t地点\n");
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
                printf("未录入\t\t");
            }

            printf("%-20s\t%s\n", course->schedule, course->location);

            courseCount++;
            totalCredits += course->credits;
        }
        current = current->next;
    }

    if (courseCount == 0) {
        printf("暂无选课记录。\n");
    }
    else {
        printf("\n总共选择 %d 门课程，总学分: %d\n", courseCount, totalCredits);
    }
}
