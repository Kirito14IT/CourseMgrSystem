#include "admin.h"
#include "bplus_tree.h"
#include "utils.h"

void adminMenu(int adminId) {
    int choice;

    while (1) {
        printf("\n=== 管理员菜单 (ID: %d) ===\n", adminId);
        printf("1. 创建初始课程信息\n");
        printf("2. 添加课程信息\n");
        printf("3. 删除课程信息\n");
        printf("4. 修改课程信息\n");
        printf("5. 浏览课程信息\n");
        printf("6. 统计信息\n");
        printf("7. 查询信息\n");
        printf("0. 退出\n");
        printf("请选择操作: ");

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
            printf("无效选择，请重试！\n");
        }

        pressEnterToContinue();
    }
}

void initializeSystem() {
    printf("正在初始化系统...\n");

    // 初始化教师数据
    strcpy(teacherArray[0].name, "张教授");
    teacherArray[0].teacherId = 100;
    strcpy(teacherArray[0].password, "100");
    teacherArray[0].taughtCourses = NULL;

    strcpy(teacherArray[1].name, "李老师");
    teacherArray[1].teacherId = 101;
    strcpy(teacherArray[1].password, "101");
    teacherArray[1].taughtCourses = NULL;

    teacherCount = 2;
    currentTeacherId = 102;

    // 创建示例课程
    Course* course1 = (Course*)malloc(sizeof(Course));
    course1->courseId = 1;
    strcpy(course1->courseName, "数据结构");
    course1->credits = 4;
    strcpy(course1->schedule, "周一3-4节，周三5-6节");
    strcpy(course1->location, "教学楼A301");
    course1->capacity = 60;
    course1->currentEnrolled = 0;
    course1->materialHead = NULL;

    Course* course2 = (Course*)malloc(sizeof(Course));
    course2->courseId = 2;
    strcpy(course2->courseName, "算法设计与分析");
    course2->credits = 3;
    strcpy(course2->schedule, "周二1-2节，周四3-4节");
    strcpy(course2->location, "教学楼B201");
    course2->capacity = 45;
    course2->currentEnrolled = 0;
    course2->materialHead = NULL;

    // 插入课程到B+树（现在只是模拟）
    courseRoot = insertBPlusTree(courseRoot, 1, course1);
    courseRoot = insertBPlusTree(courseRoot, 2, course2);

    // 创建授课记录
    addTeacherToCourse(100, 1);
    addTeacherToCourse(101, 2);

    // 创建示例学生
    Student* student1 = (Student*)malloc(sizeof(Student));
    student1->studentId = 1000;
    strcpy(student1->password, "1000");
    student1->grade = 2023;
    strcpy(student1->stuNum, "2023001");
    strcpy(student1->name, "王小明");
    student1->enrolledCourses = NULL;

    Student* student2 = (Student*)malloc(sizeof(Student));
    student2->studentId = 1001;
    strcpy(student2->password, "1001");
    student2->grade = 2023;
    strcpy(student2->stuNum, "2023002");
    strcpy(student2->name, "李小红");
    student2->enrolledCourses = NULL;

    // 插入学生到B+树（现在只是模拟）
    studentRoot = insertBPlusTree(studentRoot, 1000, student1);
    studentRoot = insertBPlusTree(studentRoot, 1001, student2);

    currentCourseId = 3;
    currentStudentId = 1002;

    printf("系统初始化完成！\n");
    printf("创建了2门课程，2位教师，2名学生\n");
    printf("默认账号密码与ID相同\n");
}

void addCourseInfo() {
    Course* newCourse = (Course*)malloc(sizeof(Course));
    int teacherId;

    newCourse->courseId = currentCourseId++;

    printf("请输入课程名: ");
    fgets(newCourse->courseName, sizeof(newCourse->courseName), stdin);
    newCourse->courseName[strcspn(newCourse->courseName, "\n")] = 0;

    printf("请输入学分: ");
    scanf("%d", &newCourse->credits);
    clearInputBuffer();

    printf("请输入上课时间: ");
    fgets(newCourse->schedule, sizeof(newCourse->schedule), stdin);
    newCourse->schedule[strcspn(newCourse->schedule, "\n")] = 0;

    printf("请输入上课地点: ");
    fgets(newCourse->location, sizeof(newCourse->location), stdin);
    newCourse->location[strcspn(newCourse->location, "\n")] = 0;

    printf("请输入课程容量: ");
    scanf("%d", &newCourse->capacity);
    clearInputBuffer();

    newCourse->currentEnrolled = 0;
    newCourse->materialHead = NULL;

    printf("请输入授课教师ID: ");
    scanf("%d", &teacherId);
    clearInputBuffer();

    // 验证教师存在
    bool teacherExists = false;
    for (int i = 0; i < teacherCount; i++) {
        if (teacherArray[i].teacherId == teacherId) {
            teacherExists = true;
            break;
        }
    }

    if (!teacherExists) {
        printf("教师ID不存在！\n");
        free(newCourse);
        return;
    }

    // 插入课程到B+树
    courseRoot = insertBPlusTree(courseRoot, newCourse->courseId, newCourse);

    // 添加授课记录
    addTeacherToCourse(teacherId, newCourse->courseId);

    printf("课程添加成功！课程ID: %d\n", newCourse->courseId);
}

void deleteCourseInfo() {
    int courseId;
    printf("请输入要删除的课程ID: ");
    scanf("%d", &courseId);
    clearInputBuffer();

    Course* course = searchCourseById(courseId);
    if (course == NULL) {
        printf("课程不存在！\n");
        return;
    }

    // 删除选课记录
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

    // 删除授课记录
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

    // 删除学习资料
    Material* material = course->materialHead;
    while (material != NULL) {
        Material* temp = material;
        material = material->next;
        free(temp);
    }

    // 从B+树删除课程
    courseRoot = deleteBPlusTree(courseRoot, courseId);
    free(course);

    printf("课程删除成功！\n");
}

void modifyCourseInfo() {
    int courseId, choice;
    printf("请输入要修改的课程ID: ");
    scanf("%d", &courseId);
    clearInputBuffer();

    Course* course = searchCourseById(courseId);
    if (course == NULL) {
        printf("课程不存在！\n");
        return;
    }

    printf("当前课程信息：\n");
    printf("课程名: %s\n", course->courseName);
    printf("学分: %d\n", course->credits);
    printf("上课时间: %s\n", course->schedule);
    printf("上课地点: %s\n", course->location);

    printf("\n请选择要修改的项目：\n");
    printf("1. 课程名\n2. 学分\n3. 上课时间\n4. 上课地点\n");
    printf("请选择: ");
    scanf("%d", &choice);
    clearInputBuffer();

    switch (choice) {
    case 1:
        printf("请输入新课程名: ");
        fgets(course->courseName, sizeof(course->courseName), stdin);
        course->courseName[strcspn(course->courseName, "\n")] = 0;
        break;
    case 2:
        printf("请输入新学分: ");
        scanf("%d", &course->credits);
        clearInputBuffer();
        break;
    case 3:
        printf("请输入新上课时间: ");
        fgets(course->schedule, sizeof(course->schedule), stdin);
        course->schedule[strcspn(course->schedule, "\n")] = 0;
        break;
    case 4:
        printf("请输入新上课地点: ");
        fgets(course->location, sizeof(course->location), stdin);
        course->location[strcspn(course->location, "\n")] = 0;
        break;
    default:
        printf("无效选择！\n");
        return;
    }

    printf("课程信息修改成功！\n");
}

// 课程信息打印函数
void printCourseInfo(void* data) {
    Course* course = (Course*)data;
    printf("%d\t%-15s\t%d\t%d\t%d\t%-20s\t%s\n",
        course->courseId, course->courseName, course->credits,
        course->capacity, course->currentEnrolled,
        course->schedule, course->location);
}

void browseCourseInfo() {
    printf("\n=== 所有课程信息 ===\n");
    printf("课程ID\t课程名\t\t学分\t容量\t已选\t上课时间\t\t上课地点\n");
    printf("------------------------------------------------------------------------\n");

    if (courseRoot == NULL) {
        printf("暂无课程信息。\n");
        return;
    }

    traverseBPlusTree(courseRoot, printCourseInfo);
}

void statisticsMenu() {
    printf("\n=== 统计功能 ===\n");
    printf("1. 课程容量统计\n");
    printf("2. 课程学分统计\n");
    printf("请选择统计类型: ");

    int choice;
    scanf("%d", &choice);
    clearInputBuffer();

    switch (choice) {
    case 1:
        printf("课程容量统计功能开发中...\n");
        break;
    case 2:
        printf("课程学分统计功能开发中...\n");
        break;
    default:
        printf("无效选择！\n");
    }
}

void queryMenu() {
    printf("\n=== 查询功能 ===\n");
    printf("1. 按课程号范围查询\n");
    printf("2. 按教师姓名查询课程\n");
    printf("请选择查询类型: ");

    int choice;
    scanf("%d", &choice);
    clearInputBuffer();

    switch (choice) {
    case 1:
        printf("按课程号范围查询功能开发中...\n");
        break;
    case 2:
        printf("按教师姓名查询功能开发中...\n");
        break;
    default:
        printf("无效选择！\n");
    }
}

bool addTeacherToCourse(int teacherId, int courseId) {
    // 添加到授课记录链表
    TeachRecord* newRecord = (TeachRecord*)malloc(sizeof(TeachRecord));
    newRecord->teacherId = teacherId;
    newRecord->courseId = courseId;
    newRecord->next = teachHead;
    teachHead = newRecord;

    // 添加到教师个人授课链表
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
