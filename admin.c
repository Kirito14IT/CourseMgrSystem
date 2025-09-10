#include "admin.h"
#include "bplus_tree.h"
#include "utils.h"

void adminMenu(int adminId) {
    int choice;

    while (1) {
        printf("\n=== ����Ա�˵� (ID: %d) ===\n", adminId);
        printf("1. ������ʼ�γ���Ϣ\n");
        printf("2. ��ӿγ���Ϣ\n");
        printf("3. ɾ���γ���Ϣ\n");
        printf("4. �޸Ŀγ���Ϣ\n");
        printf("5. ����γ���Ϣ\n");
        printf("6. ͳ����Ϣ\n");
        printf("7. ��ѯ��Ϣ\n");
        printf("0. �˳�\n");
        printf("��ѡ�����: ");

        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
        case 1:
            initializeSystem();
            break;
        case 2:
            addCourseInfo();
            break;
        case 3:
            deleteCourseInfo();
            break;
        case 4:
            modifyCourseInfo();
            break;
        case 5:
            browseCourseInfo();
            break;
        case 6:
            statisticsMenu();
            break;
        case 7:
            queryMenu();
            break;
        case 0:
            return;
        default:
            printf("��Чѡ�������ԣ�\n");
        }

        pressEnterToContinue();
    }
}

void initializeSystem() {
    printf("���ڳ�ʼ��ϵͳ...\n");

    // ��ʼ����ʦ����
    strcpy(teacherArray[0].name, "�Ž���");
    teacherArray[0].teacherId = 100;
    strcpy(teacherArray[0].password, "100");
    teacherArray[0].taughtCourses = NULL;

    strcpy(teacherArray[1].name, "����ʦ");
    teacherArray[1].teacherId = 101;
    strcpy(teacherArray[1].password, "101");
    teacherArray[1].taughtCourses = NULL;

    teacherCount = 2;
    currentTeacherId = 102;

    // ����ʾ���γ�
    Course* course1 = (Course*)malloc(sizeof(Course));
    course1->courseId = 1;
    strcpy(course1->courseName, "���ݽṹ");
    course1->credits = 4;
    strcpy(course1->schedule, "��һ3-4�ڣ�����5-6��");
    strcpy(course1->location, "��ѧ¥A301");
    course1->capacity = 60;
    course1->currentEnrolled = 0;
    course1->materialHead = NULL;

    Course* course2 = (Course*)malloc(sizeof(Course));
    course2->courseId = 2;
    strcpy(course2->courseName, "�㷨��������");
    course2->credits = 3;
    strcpy(course2->schedule, "�ܶ�1-2�ڣ�����3-4��");
    strcpy(course2->location, "��ѧ¥B201");
    course2->capacity = 45;
    course2->currentEnrolled = 0;
    course2->materialHead = NULL;

    // ����γ̵�B+��������ֻ��ģ�⣩
    courseRoot = insertBPlusTree(courseRoot, 1, course1);
    courseRoot = insertBPlusTree(courseRoot, 2, course2);

    // �����ڿμ�¼
    addTeacherToCourse(100, 1);
    addTeacherToCourse(101, 2);

    // ����ʾ��ѧ��
    Student* student1 = (Student*)malloc(sizeof(Student));
    student1->studentId = 1000;
    strcpy(student1->password, "1000");
    student1->grade = 2023;
    strcpy(student1->stuNum, "2023001");
    strcpy(student1->name, "��С��");
    student1->enrolledCourses = NULL;

    Student* student2 = (Student*)malloc(sizeof(Student));
    student2->studentId = 1001;
    strcpy(student2->password, "1001");
    student2->grade = 2023;
    strcpy(student2->stuNum, "2023002");
    strcpy(student2->name, "��С��");
    student2->enrolledCourses = NULL;

    // ����ѧ����B+��������ֻ��ģ�⣩
    studentRoot = insertBPlusTree(studentRoot, 1000, student1);
    studentRoot = insertBPlusTree(studentRoot, 1001, student2);

    currentCourseId = 3;
    currentStudentId = 1002;

    printf("ϵͳ��ʼ����ɣ�\n");
    printf("������2�ſγ̣�2λ��ʦ��2��ѧ��\n");
    printf("Ĭ���˺�������ID��ͬ\n");
}

void addCourseInfo() {
    Course* newCourse = (Course*)malloc(sizeof(Course));
    int teacherId;

    newCourse->courseId = currentCourseId++;

    printf("������γ���: ");
    fgets(newCourse->courseName, sizeof(newCourse->courseName), stdin);
    newCourse->courseName[strcspn(newCourse->courseName, "\n")] = 0;

    printf("������ѧ��: ");
    scanf("%d", &newCourse->credits);
    clearInputBuffer();

    printf("�������Ͽ�ʱ��: ");
    fgets(newCourse->schedule, sizeof(newCourse->schedule), stdin);
    newCourse->schedule[strcspn(newCourse->schedule, "\n")] = 0;

    printf("�������Ͽεص�: ");
    fgets(newCourse->location, sizeof(newCourse->location), stdin);
    newCourse->location[strcspn(newCourse->location, "\n")] = 0;

    printf("������γ�����: ");
    scanf("%d", &newCourse->capacity);
    clearInputBuffer();

    newCourse->currentEnrolled = 0;
    newCourse->materialHead = NULL;

    printf("�������ڿν�ʦID: ");
    scanf("%d", &teacherId);
    clearInputBuffer();

    // ��֤��ʦ����
    bool teacherExists = false;
    for (int i = 0; i < teacherCount; i++) {
        if (teacherArray[i].teacherId == teacherId) {
            teacherExists = true;
            break;
        }
    }

    if (!teacherExists) {
        printf("��ʦID�����ڣ�\n");
        free(newCourse);
        return;
    }

    // ����γ̵�B+��
    courseRoot = insertBPlusTree(courseRoot, newCourse->courseId, newCourse);

    // ����ڿμ�¼
    addTeacherToCourse(teacherId, newCourse->courseId);

    printf("�γ���ӳɹ����γ�ID: %d\n", newCourse->courseId);
}

void deleteCourseInfo() {
    int courseId;
    printf("������Ҫɾ���Ŀγ�ID: ");
    scanf("%d", &courseId);
    clearInputBuffer();

    Course* course = searchCourseById(courseId);
    if (course == NULL) {
        printf("�γ̲����ڣ�\n");
        return;
    }

    // ɾ��ѡ�μ�¼
    EnrollRecord* enrollCurrent = enrollHead;
    EnrollRecord* enrollPrev = NULL;

    while (enrollCurrent != NULL) {
        if (enrollCurrent->courseId == courseId) {
            Student* student = searchStudentById(enrollCurrent->studentId);
            if (student != NULL) {
                removeFromStudentEnrollList(student, courseId);
            }

            if (enrollPrev == NULL) {
                enrollHead = enrollCurrent->next;
            }
            else {
                enrollPrev->next = enrollCurrent->next;
            }

            EnrollRecord* temp = enrollCurrent;
            enrollCurrent = enrollCurrent->next;
            free(temp);
        }
        else {
            enrollPrev = enrollCurrent;
            enrollCurrent = enrollCurrent->next;
        }
    }

    // ɾ���ڿμ�¼
    TeachRecord* teachCurrent = teachHead;
    TeachRecord* teachPrev = NULL;

    while (teachCurrent != NULL) {
        if (teachCurrent->courseId == courseId) {
            for (int i = 0; i < teacherCount; i++) {
                if (teacherArray[i].teacherId == teachCurrent->teacherId) {
                    removeFromTeacherCourseList(&teacherArray[i], courseId);
                    break;
                }
            }

            if (teachPrev == NULL) {
                teachHead = teachCurrent->next;
            }
            else {
                teachPrev->next = teachCurrent->next;
            }

            TeachRecord* temp = teachCurrent;
            teachCurrent = teachCurrent->next;
            free(temp);
        }
        else {
            teachPrev = teachCurrent;
            teachCurrent = teachCurrent->next;
        }
    }

    // ɾ��ѧϰ����
    Material* material = course->materialHead;
    while (material != NULL) {
        Material* temp = material;
        material = material->next;
        free(temp);
    }

    // ��B+��ɾ���γ�
    courseRoot = deleteBPlusTree(courseRoot, courseId);
    free(course);

    printf("�γ�ɾ���ɹ���\n");
}

void modifyCourseInfo() {
    int courseId, choice;
    printf("������Ҫ�޸ĵĿγ�ID: ");
    scanf("%d", &courseId);
    clearInputBuffer();

    Course* course = searchCourseById(courseId);
    if (course == NULL) {
        printf("�γ̲����ڣ�\n");
        return;
    }

    printf("��ǰ�γ���Ϣ��\n");
    printf("�γ���: %s\n", course->courseName);
    printf("ѧ��: %d\n", course->credits);
    printf("�Ͽ�ʱ��: %s\n", course->schedule);
    printf("�Ͽεص�: %s\n", course->location);

    printf("\n��ѡ��Ҫ�޸ĵ���Ŀ��\n");
    printf("1. �γ���\n2. ѧ��\n3. �Ͽ�ʱ��\n4. �Ͽεص�\n");
    printf("��ѡ��: ");
    scanf("%d", &choice);
    clearInputBuffer();

    switch (choice) {
    case 1:
        printf("�������¿γ���: ");
        fgets(course->courseName, sizeof(course->courseName), stdin);
        course->courseName[strcspn(course->courseName, "\n")] = 0;
        break;
    case 2:
        printf("��������ѧ��: ");
        scanf("%d", &course->credits);
        clearInputBuffer();
        break;
    case 3:
        printf("���������Ͽ�ʱ��: ");
        fgets(course->schedule, sizeof(course->schedule), stdin);
        course->schedule[strcspn(course->schedule, "\n")] = 0;
        break;
    case 4:
        printf("���������Ͽεص�: ");
        fgets(course->location, sizeof(course->location), stdin);
        course->location[strcspn(course->location, "\n")] = 0;
        break;
    default:
        printf("��Чѡ��\n");
        return;
    }

    printf("�γ���Ϣ�޸ĳɹ���\n");
}

// �γ���Ϣ��ӡ����
void printCourseInfo(void* data) {
    Course* course = (Course*)data;
    printf("%d\t%-15s\t%d\t%d\t%d\t%-20s\t%s\n",
        course->courseId, course->courseName, course->credits,
        course->capacity, course->currentEnrolled,
        course->schedule, course->location);
}

void browseCourseInfo() {
    printf("\n=== ���пγ���Ϣ ===\n");
    printf("�γ�ID\t�γ���\t\tѧ��\t����\t��ѡ\t�Ͽ�ʱ��\t\t�Ͽεص�\n");
    printf("------------------------------------------------------------------------\n");

    if (courseRoot == NULL) {
        printf("���޿γ���Ϣ��\n");
        return;
    }

    traverseBPlusTree(courseRoot, printCourseInfo);
}

void statisticsMenu() {
    printf("\n=== ͳ�ƹ��� ===\n");
    printf("1. �γ�����ͳ��\n");
    printf("2. �γ�ѧ��ͳ��\n");
    printf("��ѡ��ͳ������: ");

    int choice;
    scanf("%d", &choice);
    clearInputBuffer();

    switch (choice) {
    case 1:
        printf("�γ�����ͳ�ƹ��ܿ�����...\n");
        break;
    case 2:
        printf("�γ�ѧ��ͳ�ƹ��ܿ�����...\n");
        break;
    default:
        printf("��Чѡ��\n");
    }
}

void queryMenu() {
    printf("\n=== ��ѯ���� ===\n");
    printf("1. ���γ̺ŷ�Χ��ѯ\n");
    printf("2. ����ʦ������ѯ�γ�\n");
    printf("��ѡ���ѯ����: ");

    int choice;
    scanf("%d", &choice);
    clearInputBuffer();

    switch (choice) {
    case 1:
        printf("���γ̺ŷ�Χ��ѯ���ܿ�����...\n");
        break;
    case 2:
        printf("����ʦ������ѯ���ܿ�����...\n");
        break;
    default:
        printf("��Чѡ��\n");
    }
}

bool addTeacherToCourse(int teacherId, int courseId) {
    // ��ӵ��ڿμ�¼����
    TeachRecord* newRecord = (TeachRecord*)malloc(sizeof(TeachRecord));
    newRecord->teacherId = teacherId;
    newRecord->courseId = courseId;
    newRecord->next = teachHead;
    teachHead = newRecord;

    // ��ӵ���ʦ�����ڿ�����
    for (int i = 0; i < teacherCount; i++) {
        if (teacherArray[i].teacherId == teacherId) {
            CourseNode* newNode = (CourseNode*)malloc(sizeof(CourseNode));
            newNode->courseId = courseId;
            newNode->next = teacherArray[i].taughtCourses;
            teacherArray[i].taughtCourses = newNode;
            return true;
        }
    }

    return false;
}
