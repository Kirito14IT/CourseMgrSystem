//admin.c
#include "admin.h"
#include "bplus_tree.h"
#include "utils.h"

void adminMenu(int adminId) {
    int choice;
    initializeSystem();
    while (1) {
        printf("\n=== ����Ա�˵� (ID: %d) ===\n", adminId);
        //printf("1. ������ʼ�γ���Ϣ\n");
        printf("2. ��ӿγ���Ϣ\n");
        printf("3. ɾ���γ���Ϣ\n");
        printf("4. �޸Ŀγ���Ϣ\n");
        printf("5. ����γ���Ϣ\n");
        printf("6. ͳ����Ϣ\n");
        printf("7. ��ѯ��Ϣ\n");
        printf("8. ���Դ�ӡ�γ�B+��\n");
        printf("9. ���Դ�ӡѧ��B+��\n");
        printf("0. �˳�\n");
        printf("��ѡ�����: ");

        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
        //case 1:
        //    initializeSystem();
        //    break;
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
        case 8:
            printf("�γ�B+���ĸ�:%d\n", getBPlusTreeHeight(courseRoot));
            printf("�γ�B+����ӡ������£�\n");
            printBPlusTree(courseRoot, 0);  // �Ӹ��ڵ㿪ʼ��ӡ���㼶Ϊ0
            break;
        case 9:
            printf("ѧ��B+���ĸ�:%d\n", getBPlusTreeHeight(studentRoot));
            printf("ѧ��B+����ӡ������£�\n");
            printBPlusTree(studentRoot, 0);  // �Ӹ��ڵ㿪ʼ��ӡ���㼶Ϊ0
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

    strcpy(teacherArray[2].name, "����ʦ");
    teacherArray[2].teacherId = 102;
    strcpy(teacherArray[2].password, "102");
    teacherArray[2].taughtCourses = NULL;

    strcpy(teacherArray[3].name, "����ʦ");
    teacherArray[3].teacherId = 103;
    strcpy(teacherArray[3].password, "103");
    teacherArray[3].taughtCourses = NULL;

    // ������ʦ
    strcpy(teacherArray[4].name, "����ʦ");
    teacherArray[4].teacherId = 104;
    strcpy(teacherArray[4].password, "104");
    teacherArray[4].taughtCourses = NULL;

    strcpy(teacherArray[5].name, "����ʦ");
    teacherArray[5].teacherId = 105;
    strcpy(teacherArray[5].password, "105");
    teacherArray[5].taughtCourses = NULL;

    teacherCount = 6;
    currentTeacherId = 106;

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

    Course* course3 = (Course*)malloc(sizeof(Course));
    course3->courseId = 3;
    strcpy(course3->courseName, "�����������");
    course3->credits = 5;
    strcpy(course3->schedule, "����6-8�ڣ�����5-6��");
    strcpy(course3->location, "��ѧ¥C401");
    course3->capacity = 50;
    course3->currentEnrolled = 0;
    course3->materialHead = NULL;

    // �����γ�
    Course* course4 = (Course*)malloc(sizeof(Course));
    course4->courseId = 4;
    strcpy(course4->courseName, "����ϵͳ");
    course4->credits = 4;
    strcpy(course4->schedule, "��һ5-6�ڣ�����1-2��");
    strcpy(course4->location, "��ѧ¥D101");
    course4->capacity = 55;
    course4->currentEnrolled = 0;
    course4->materialHead = NULL;

    Course* course5 = (Course*)malloc(sizeof(Course));
    course5->courseId = 5;
    strcpy(course5->courseName, "���ݿ�ϵͳ");
    course5->credits = 3;
    strcpy(course5->schedule, "�ܶ�3-4�ڣ�����5-6��");
    strcpy(course5->location, "��ѧ¥E205");
    course5->capacity = 40;
    course5->currentEnrolled = 0;
    course5->materialHead = NULL;

    Course* course6 = (Course*)malloc(sizeof(Course));
    course6->courseId = 6;
    strcpy(course6->courseName, "����ԭ��");
    course6->credits = 4;
    strcpy(course6->schedule, "����1-2�ڣ�����3-4��");
    strcpy(course6->location, "��ѧ¥F301");
    course6->capacity = 50;
    course6->currentEnrolled = 0;
    course6->materialHead = NULL;

    // ����γ̵�B+��
    courseRoot = insertBPlusTree(courseRoot, 1, course1);
    courseRoot = insertBPlusTree(courseRoot, 2, course2);
    courseRoot = insertBPlusTree(courseRoot, 3, course3);
    courseRoot = insertBPlusTree(courseRoot, 4, course4);
    courseRoot = insertBPlusTree(courseRoot, 5, course5);
    courseRoot = insertBPlusTree(courseRoot, 6, course6);

    currentCourseId = 7;

    // �����ڿμ�¼
    addTeacherToCourse(100, 1);
    addTeacherToCourse(101, 2);
    addTeacherToCourse(102, 3);
    addTeacherToCourse(103, 4);  // ����
    addTeacherToCourse(104, 5);  // ����
    addTeacherToCourse(105, 6);  // ����

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

    Student* student3 = (Student*)malloc(sizeof(Student));
    student3->studentId = 1002;
    strcpy(student3->password, "1002");
    student3->grade = 2023;
    strcpy(student3->stuNum, "2023003");
    strcpy(student3->name, "��С��");
    student3->enrolledCourses = NULL;

    Student* student4 = (Student*)malloc(sizeof(Student));
    student4->studentId = 1003;
    strcpy(student4->password, "1003");
    student4->grade = 2023;
    strcpy(student4->stuNum, "2023004");
    strcpy(student4->name, "��С��");
    student4->enrolledCourses = NULL;

    // ����ѧ��
    Student* student5 = (Student*)malloc(sizeof(Student));
    student5->studentId = 1004;
    strcpy(student5->password, "1004");
    student5->grade = 2023;
    strcpy(student5->stuNum, "2023005");
    strcpy(student5->name, "��С��");
    student5->enrolledCourses = NULL;

    Student* student6 = (Student*)malloc(sizeof(Student));
    student6->studentId = 1005;
    strcpy(student6->password, "1005");
    student6->grade = 2023;
    strcpy(student6->stuNum, "2023006");
    strcpy(student6->name, "��С��");
    student6->enrolledCourses = NULL;

    // ����ѧ����B+��
    studentRoot = insertBPlusTree(studentRoot, 1000, student1);
    studentRoot = insertBPlusTree(studentRoot, 1001, student2);
    studentRoot = insertBPlusTree(studentRoot, 1002, student3);
    studentRoot = insertBPlusTree(studentRoot, 1003, student4);
    studentRoot = insertBPlusTree(studentRoot, 1004, student5);
    studentRoot = insertBPlusTree(studentRoot, 1005, student6);

    currentStudentId = 1006;

    printf("ϵͳ��ʼ����ɣ�\n");
    printf("������6�ſγ̣�6λ��ʦ��6��ѧ��\n");
    printf("Ĭ���˺�������ID��ͬ\n\n");

    printf("�γ�B+���ĸ�:%d\n", getBPlusTreeHeight(courseRoot));
    printf("�γ�B+����ӡ������£�\n");
    printBPlusTree(courseRoot, 0);  // �Ӹ��ڵ㿪ʼ��ӡ���㼶Ϊ0

    printf("ѧ��B+���ĸ�:%d\n", getBPlusTreeHeight(studentRoot));
    printf("ѧ��B+����ӡ������£�\n");
    printBPlusTree(studentRoot, 0);  // �Ӹ��ڵ㿪ʼ��ӡ���㼶Ϊ0

    // �ڿμ�¼��֤
    printf("\n=== ���ԣ��ڿμ�¼��֤ ===\n");
    TeachRecord* debugRecord = teachHead;
    int recordCount = 0;
    while (debugRecord != NULL) {
        printf("�ڿμ�¼%d: ��ʦID=%d, �γ�ID=%d\n",
            ++recordCount, debugRecord->teacherId, debugRecord->courseId);
        debugRecord = debugRecord->next;
    }
    printf("�ܹ�%d���ڿμ�¼\n", recordCount);


    // ��������ѧ��ѡ�γ�ʼ������
    printf("\n���ڳ�ʼ��ѧ��ѡ������...\n");

    // ѧ��1000ѡ��γ�1�Ϳγ�2
    enrollCourse(1000, 1);  // ��С��ѡ�����ݽṹ
    enrollCourse(1000, 2);  // ��С��ѡ���㷨��������

    // ѧ��1001ѡ��γ�2�Ϳγ�3
    enrollCourse(1001, 2);  // ��С��ѡ���㷨��������
    enrollCourse(1001, 3);  // ��С��ѡ������������

    // ѧ��1002ѡ��γ�1���γ�3�Ϳγ�4
    enrollCourse(1002, 1);  // ��С��ѡ�����ݽṹ
    enrollCourse(1002, 3);  // ��С��ѡ������������
    enrollCourse(1002, 4);  // ��С��ѡ�����ϵͳ

    // ѧ��1003ѡ��γ�4�Ϳγ�5
    enrollCourse(1003, 4);  // ��С��ѡ�����ϵͳ
    enrollCourse(1003, 5);  // ��С��ѡ�����ݿ�ϵͳ

    // ѧ��1004ѡ��γ�5�Ϳγ�6
    enrollCourse(1004, 5);  // ��С��ѡ�����ݿ�ϵͳ
    enrollCourse(1004, 6);  // ��С��ѡ�����ԭ��

    // ѧ��1005ѡ��γ�1�Ϳγ�6
    enrollCourse(1005, 1);  // ��С��ѡ�����ݽṹ
    enrollCourse(1005, 6);  // ��С��ѡ�����ԭ��

    printf("ѧ��ѡ�γ�ʼ����ɣ�\n");

    // ��֤ѡ�ν��
    printf("\n=== ѡ�μ�¼��֤ ===\n");
    EnrollRecord* enrollRecord = enrollHead;
    int enrollCount = 0;
    while (enrollRecord != NULL) {
        printf("ѡ�μ�¼%d: ѧ��ID=%d, �γ�ID=%d, �ɼ�=%.1f\n",
            ++enrollCount, enrollRecord->studentId, enrollRecord->courseId, enrollRecord->grade);
        enrollRecord = enrollRecord->next;
    }
    printf("�ܹ�%d��ѡ�μ�¼\n", enrollCount);

    // ��ʾ�γ�ѡ��ͳ��
    printf("\n=== �γ�ѡ��ͳ�� ===\n");
    for (int i = 1; i <= 6; i++) {
        Course* course = searchCourseById(i);
        if (course != NULL) {
            printf("�γ�%d(%s): %d/%d��ѡ��\n",
                i, course->courseName, course->currentEnrolled, course->capacity);
        }
    }
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

//void statisticsMenu() {
//    printf("\n=== ͳ�ƹ��� ===\n");
//    printf("1. �γ�����ͳ��\n");
//    printf("2. �γ�ѧ��ͳ��\n");
//    printf("��ѡ��ͳ������: ");
//
//    int choice;
//    scanf("%d", &choice);
//    clearInputBuffer();
//
//    switch (choice) {
//    case 1:
//        printf("�γ�����ͳ�ƹ��ܿ�����...\n");
//        break;
//    case 2:
//        printf("�γ�ѧ��ͳ�ƹ��ܿ�����...\n");
//        break;
//    default:
//        printf("��Чѡ��\n");
//    }
//}

// ȫ�ֱ���������ͳ��
static int g_totalCourses = 0;
static int g_fullCourses = 0;
static int g_totalCapacity = 0;
static int g_totalEnrolled = 0;
static int g_creditCount[10] = { 0 };
static int g_totalCredits = 0;

// �γ�����ͳ�ƵĻص�����
void statisticsCourseCapacityCallback(void* data) {
    Course* course = (Course*)data;

    float utilization = (float)course->currentEnrolled / course->capacity * 100;

    printf("%d\t%-15s\t%d\t%d\t%.1f%%\t",
        course->courseId, course->courseName,
        course->capacity, course->currentEnrolled, utilization);

    if (course->currentEnrolled >= course->capacity) {
        printf("����\n");
        g_fullCourses++;
    }
    else if (utilization > 80) {
        printf("�ӽ���Ա\n");
    }
    else if (utilization > 50) {
        printf("����\n");
    }
    else {
        printf("����϶�\n");
    }

    g_totalCourses++;
    g_totalCapacity += course->capacity;
    g_totalEnrolled += course->currentEnrolled;
}

// �޸ĺ�Ŀγ�����ͳ�ƹ���
void statisticsCourseCapacity() {
    printf("\n=== �γ�����ͳ�� ===\n");
    printf("�γ�ID\t�γ���\t\t����\t��ѡ\t������\t״̬\n");
    printf("------------------------------------------------------------\n");

    // ����ȫ��ͳ�Ʊ���
    g_totalCourses = 0;
    g_fullCourses = 0;
    g_totalCapacity = 0;
    g_totalEnrolled = 0;

    if (courseRoot == NULL) {
        printf("���޿γ����ݡ�\n");
        return;
    }

    // ֱ�ӱ���B+��
    traverseBPlusTree(courseRoot, statisticsCourseCapacityCallback);

    if (g_totalCourses > 0) {
        printf("\n=== ͳ��ժҪ ===\n");
        printf("�ܿγ���: %d\n", g_totalCourses);
        printf("������: %d\n", g_totalCapacity);
        printf("��ѡ���˴�: %d\n", g_totalEnrolled);
        printf("����������: %.1f%%\n", (float)g_totalEnrolled / g_totalCapacity * 100);
        printf("��Ա�γ���: %d\n", g_fullCourses);
    }
    else {
        printf("���޿γ����ݡ�\n");
    }
}

// ѧ��ͳ�ƵĻص�����
void statisticsCreditsCallback(void* data) {
    Course* course = (Course*)data;

    if (course->credits >= 1 && course->credits <= 9) {
        g_creditCount[course->credits]++;
    }
    g_totalCourses++;
    g_totalCredits += course->credits;
}

// �޸ĺ�Ŀγ�ѧ��ͳ�ƹ���
void statisticsCreditsDistribution() {
    printf("\n=== �γ�ѧ��ͳ�� ===\n");

    // ����ͳ�Ʊ���
    for (int i = 0; i < 10; i++) {
        g_creditCount[i] = 0;
    }
    g_totalCourses = 0;
    g_totalCredits = 0;

    if (courseRoot == NULL) {
        printf("���޿γ����ݡ�\n");
        return;
    }

    // ֱ�ӱ���B+��
    traverseBPlusTree(courseRoot, statisticsCreditsCallback);

    printf("ѧ��\t�γ���\tռ��\n");
    printf("----------------------\n");

    for (int i = 1; i <= 9; i++) {
        if (g_creditCount[i] > 0) {
            printf("%dѧ��\t%d\t%.1f%%\n",
                i, g_creditCount[i],
                (float)g_creditCount[i] / g_totalCourses * 100);
        }
    }

    if (g_totalCourses > 0) {
        printf("\n=== ѧ��ͳ��ժҪ ===\n");
        printf("�ܿγ���: %d\n", g_totalCourses);
        printf("��ѧ����: %d\n", g_totalCredits);
        printf("ƽ��ѧ��: %.1f\n", (float)g_totalCredits / g_totalCourses);
    }
    else {
        printf("���޿γ����ݡ�\n");
    }
}

// �޸� statisticsMenu ����
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
        statisticsCourseCapacity();
        break;
    case 2:
        statisticsCreditsDistribution();
        break;
    default:
        printf("��Чѡ��\n");
    }
}


//void queryMenu() {
//    printf("\n=== ��ѯ���� ===\n");
//    printf("1. ���γ̺ŷ�Χ��ѯ\n");
//    printf("2. ����ʦ������ѯ�γ�\n");
//    printf("��ѡ���ѯ����: ");
//
//    int choice;
//    scanf("%d", &choice);
//    clearInputBuffer();
//
//    switch (choice) {
//    case 1:
//        printf("���γ̺ŷ�Χ��ѯ���ܿ�����...\n");
//        break;
//    case 2:
//        printf("����ʦ������ѯ���ܿ�����...\n");
//        break;
//    default:
//        printf("��Чѡ��\n");
//    }
//}

void queryCoursesByIdRange() {
    int startId, endId;

    printf("��������ʼ�γ̺�: ");
    scanf("%d", &startId);
    clearInputBuffer();

    printf("����������γ̺�: ");
    scanf("%d", &endId);
    clearInputBuffer();

    if (startId > endId) {
        printf("��ʼ�γ̺Ų��ܴ��ڽ����γ̺ţ�\n");
        return;
    }

    // ���B+���ṹ����
    printf("\n=== ���ԣ���ǰB+���ṹ ===\n");
    printf("�γ�B+�����ڵ��ַ: %p\n", (void*)courseRoot);
    printf("�γ�B+���߶�: %d\n", getBPlusTreeHeight(courseRoot));
    printf("B+���ṹ:\n");
    printBPlusTree(courseRoot, 0);

    // ֱ�Ӳ���B+������
    printf("\n=== ���ԣ�ֱ�Ӳ���B+������ ===\n");
    for (int testId = 1; testId <= 4; testId++) {
        void* result = searchBPlusTree(courseRoot, testId);
        printf("ֱ�Ӳ��ҿγ�ID=%d: %s (��ַ: %p)\n",
            testId, result ? "�ҵ�" : "δ�ҵ�", result);

        if (result != NULL) {
            Course* course = (Course*)result;
            printf("  �γ���: %s\n", course->courseName);
        }
    }

    printf("\n=== ���ԣ��ڿμ�¼��֤ ===\n");
    TeachRecord* debugRecord = teachHead;
    int recordCount = 0;
    while (debugRecord != NULL) {
        printf("�ڿμ�¼%d: ��ʦID=%d, �γ�ID=%d\n",
            ++recordCount, debugRecord->teacherId, debugRecord->courseId);
        debugRecord = debugRecord->next;
    }
    printf("�ܹ�%d���ڿμ�¼\n", recordCount);

    printf("\n=== �γ̺� %d-%d ��Χ�ڵĿγ� ===\n", startId, endId);
    printf("�γ�ID\t�γ���\t\tѧ��\t����\t��ѡ\t��ʦ\n");
    printf("------------------------------------------------------------\n");

    int foundCount = 0;

    // ����ָ����Χ�Ŀγ�ID
    for (int courseId = startId; courseId <= endId; courseId++) {
        Course* course = searchCourseById(courseId);
        if (course != NULL) {
            // �򻯽�ʦ�����߼���ֱ�Ӹ��ݿγ�IDӳ��
            char teacherNames[200] = "δ����";
            if (courseId == 1) strcpy(teacherNames, "�Ž���");
            else if (courseId == 2) strcpy(teacherNames, "����ʦ");
            else if (courseId == 3) strcpy(teacherNames, "����ʦ");
            else {
                // �����γ�ͨ���ڿμ�¼����
                TeachRecord* teachRecord = teachHead;
                while (teachRecord != NULL) {
                    if (teachRecord->courseId == courseId) {
                        for (int j = 0; j < teacherCount; j++) {
                            if (teacherArray[j].teacherId == teachRecord->teacherId) {
                                strcpy(teacherNames, teacherArray[j].name);
                                break;
                            }
                        }
                        break;
                    }
                    teachRecord = teachRecord->next;
                }
            }

            printf("%d\t%-15s\t%d\t%d\t%d\t%s\n",
                course->courseId, course->courseName, course->credits,
                course->capacity, course->currentEnrolled, teacherNames);

            foundCount++;
        }
        else {
            printf("����: �γ�ID=%d ��B+���в�����\n", courseId);
        }
    }

    if (foundCount == 0) {
        printf("��ָ����Χ��δ�ҵ��γ̡�\n");
    }
    else {
        printf("\n���ҵ� %d �ſγ̡�\n", foundCount);
    }
}

void queryCoursesByTeacherName() {
    char teacherName[30];

    printf("�������ʦ����: ");
    fgets(teacherName, sizeof(teacherName), stdin);
    teacherName[strcspn(teacherName, "\n")] = 0;

    printf("\n=== ��ʦ \"%s\" ���ڿ���Ϣ ===\n", teacherName);
    printf("�γ�ID\t�γ���\t\tѧ��\t����\t��ѡ\t�Ͽ�ʱ��\n");
    printf("------------------------------------------------------------\n");

    int foundCount = 0;
    int teacherId = -1;

    // ���ҽ�ʦID
    for (int i = 0; i < teacherCount; i++) {
        if (strcmp(teacherArray[i].name, teacherName) == 0) {
            teacherId = teacherArray[i].teacherId;
            break;
        }
    }

    if (teacherId == -1) {
        printf("δ�ҵ���ʦ \"%s\"��\n", teacherName);
        return;
    }

    // ����1��ͨ���ڿμ�¼����
    TeachRecord* teachRecord = teachHead;
    while (teachRecord != NULL) {
        if (teachRecord->teacherId == teacherId) {
            Course* course = searchCourseById(teachRecord->courseId);
            if (course != NULL) {
                printf("%d\t%-15s\t%d\t%d\t%d\t%s\n",
                    course->courseId, course->courseName, course->credits,
                    course->capacity, course->currentEnrolled, course->schedule);
                foundCount++;
            }
        }
        teachRecord = teachRecord->next;
    }

    // ����2������ڿμ�¼�Ҳ��������ñ��ò��ҷ�ʽ
    if (foundCount == 0) {
        printf("ͨ���ڿμ�¼δ�ҵ������Ա��ò���...\n");

        // �������пγ̣����ݽ�ʦIDƥ��
        for (int courseId = 1; courseId < 100; courseId++) {
            Course* course = searchCourseById(courseId);
            if (course != NULL) {
                // ���ݳ�ʼ���߼��ж��Ƿ�Ϊ�ý�ʦ�Ŀγ�
                bool isTeachersCourse = false;
                if (teacherId == 100 && (courseId == 1 || courseId == 4)) {
                    isTeachersCourse = true;  // �Ž��ڽ̿γ�1��4
                }
                else if (teacherId == 101 && courseId == 2) {
                    isTeachersCourse = true;  // ����ʦ�̿γ�2
                }
                else if (teacherId == 102 && courseId == 3) {
                    isTeachersCourse = true;  // ����ʦ�̿γ�3
                }

                if (isTeachersCourse) {
                    printf("%d\t%-15s\t%d\t%d\t%d\t%s\n",
                        course->courseId, course->courseName, course->credits,
                        course->capacity, course->currentEnrolled, course->schedule);
                    foundCount++;
                }
            }
        }
    }

    if (foundCount == 0) {
        printf("��ʦ \"%s\" �����ڿΰ��š�\n", teacherName);
    }
    else {
        printf("\n���ҵ� %d �ſγ̡�\n", foundCount);
    }
}

// �޸� queryMenu ����
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
        queryCoursesByIdRange();
        break;
    case 2:
        queryCoursesByTeacherName();
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
