#include "utils.h"
#include "bplus_tree.h"  // �������
int login() {
    int id;
    char password[20];

    printf("=== �γ̹���ϵͳ��¼ ===\n");
    printf("�������û�ID: ");
    scanf("%d", &id);
    clearInputBuffer();

    printf("����������: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    // ����Ա��¼��֤
    if (id >= 0 && id <= 99) {
        for (int i = 0; i < adminCount; i++) {
            if (adminArray[i].adminId == id && strcmp(adminArray[i].password, password) == 0) {
                printf("����Ա��¼�ɹ�����ӭ��%s\n", adminArray[i].name);
                return id;
            }
        }
    }
    // ��ʦ��¼��֤
    else if (id >= 100 && id <= 999) {
        for (int i = 0; i < teacherCount; i++) {
            if (teacherArray[i].teacherId == id && strcmp(teacherArray[i].password, password) == 0) {
                printf("��ʦ��¼�ɹ�����ӭ��%s\n", teacherArray[i].name);
                return id;
            }
        }
    }
    // ѧ����¼��֤
    else if (id >= 1000) {
        Student* student = searchStudentById(id);
        if (student != NULL && strcmp(student->password, password) == 0) {
            printf("ѧ����¼�ɹ�����ӭ��%s\n", student->name);
            return id;
        }
    }

    printf("��¼ʧ�ܣ��û�ID���������\n");
    return -1;
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pressEnterToContinue() {
    printf("���س�������...");
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
