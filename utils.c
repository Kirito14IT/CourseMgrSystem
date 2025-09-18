//utils.c
#include "utils.h"
#include "bplus_tree.h"  // 添加这行
int login() {
    int id;
    char password[20];

    printf("请输入用户ID: ");
    if (scanf("%d", &id) != 1) {
        clearInputBuffer();
        printf("*** 错误: 请输入有效的数字ID ***\n");
        return -1;
    }
    clearInputBuffer();

    printf("请输入密码: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    // 管理员登录验证
    if (id >= 0 && id <= 99) {
        for (int i = 0; i < adminCount; i++) {
            if (adminArray[i].adminId == id && strcmp(adminArray[i].password, password) == 0) {
                printf("\n>> 管理员登录成功！欢迎您，%s <<\n", adminArray[i].name);
                return id;
            }
        }
    }
    // 教师登录验证
    else if (id >= 100 && id <= 999) {
        for (int i = 0; i < teacherCount; i++) {
            if (teacherArray[i].teacherId == id && strcmp(teacherArray[i].password, password) == 0) {
                printf("\n>> 教师登录成功！欢迎您，%s <<\n", teacherArray[i].name);
                return id;
            }
        }
    }
    // 学生登录验证
    else if (id >= 1000) {
        Student* student = searchStudentById(id);
        if (student != NULL && strcmp(student->password, password) == 0) {
            printf("\n>> 学生登录成功！欢迎您，%s <<\n", student->name);
            return id;
        }
    }

    printf("\n*** 登录失败！用户ID或密码错误 ***\n");
    return -1;
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pressEnterToContinue() {
    printf("按回车键继续...");
    getchar();
}

void removeFromStudentEnrollList(Student* student, int courseId) {
    if (student == NULL) return;

    EnrollNode* current = student->enrolledCourses;
    EnrollNode* prev = NULL;

    while (current != NULL) {
        if (current->courseId == courseId) {
            if (prev == NULL) {
                student->enrolledCourses = current->next;
            }
            else {
                prev->next = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

void removeFromTeacherCourseList(Teacher* teacher, int courseId) {
    if (teacher == NULL) return;

    CourseNode* current = teacher->taughtCourses;
    CourseNode* prev = NULL;

    while (current != NULL) {
        if (current->courseId == courseId) {
            if (prev == NULL) {
                teacher->taughtCourses = current->next;
            }
            else {
                prev->next = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}
