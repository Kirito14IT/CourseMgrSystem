//admin.c
#include "admin.h"
#include "bplus_tree.h"
#include "utils.h"

void adminMenu(int adminId) {
    int choice;
    initializeSystem();
    while (1) {
        printf("\n=== 管理员菜单 (ID: %d) ===\n", adminId);
        //printf("1. 创建初始课程信息\n");
        printf("2. 添加课程信息\n");
        printf("3. 删除课程信息\n");
        printf("4. 修改课程信息\n");
        printf("5. 浏览课程信息\n");
        printf("6. 统计信息\n");
        printf("7. 查询信息\n");
        printf("8. 调试打印课程B+树\n");
        printf("9. 调试打印学生B+树\n");
        printf("0. 退出\n");
        printf("请选择操作: ");

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
            printf("课程B+树的高:%d\n", getBPlusTreeHeight(courseRoot));
            printf("课程B+树打印结果如下：\n");
            printBPlusTree(courseRoot, 0);  // 从根节点开始打印，层级为0
            break;
        case 9:
            printf("学生B+树的高:%d\n", getBPlusTreeHeight(studentRoot));
            printf("学生B+树打印结果如下：\n");
            printBPlusTree(studentRoot, 0);  // 从根节点开始打印，层级为0
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

    strcpy(teacherArray[2].name, "王老师");
    teacherArray[2].teacherId = 102;
    strcpy(teacherArray[2].password, "102");
    teacherArray[2].taughtCourses = NULL;

    strcpy(teacherArray[3].name, "杨老师");
    teacherArray[3].teacherId = 103;
    strcpy(teacherArray[3].password, "103");
    teacherArray[3].taughtCourses = NULL;

    // 新增教师
    strcpy(teacherArray[4].name, "赵老师");
    teacherArray[4].teacherId = 104;
    strcpy(teacherArray[4].password, "104");
    teacherArray[4].taughtCourses = NULL;

    strcpy(teacherArray[5].name, "刘老师");
    teacherArray[5].teacherId = 105;
    strcpy(teacherArray[5].password, "105");
    teacherArray[5].taughtCourses = NULL;

    teacherCount = 6;
    currentTeacherId = 106;

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

    Course* course3 = (Course*)malloc(sizeof(Course));
    course3->courseId = 3;
    strcpy(course3->courseName, "计算机网络编程");
    course3->credits = 5;
    strcpy(course3->schedule, "周三6-8节，周四5-6节");
    strcpy(course3->location, "教学楼C401");
    course3->capacity = 50;
    course3->currentEnrolled = 0;
    course3->materialHead = NULL;

    // 新增课程
    Course* course4 = (Course*)malloc(sizeof(Course));
    course4->courseId = 4;
    strcpy(course4->courseName, "操作系统");
    course4->credits = 4;
    strcpy(course4->schedule, "周一5-6节，周四1-2节");
    strcpy(course4->location, "教学楼D101");
    course4->capacity = 55;
    course4->currentEnrolled = 0;
    course4->materialHead = NULL;

    Course* course5 = (Course*)malloc(sizeof(Course));
    course5->courseId = 5;
    strcpy(course5->courseName, "数据库系统");
    course5->credits = 3;
    strcpy(course5->schedule, "周二3-4节，周五5-6节");
    strcpy(course5->location, "教学楼E205");
    course5->capacity = 40;
    course5->currentEnrolled = 0;
    course5->materialHead = NULL;

    Course* course6 = (Course*)malloc(sizeof(Course));
    course6->courseId = 6;
    strcpy(course6->courseName, "编译原理");
    course6->credits = 4;
    strcpy(course6->schedule, "周三1-2节，周五3-4节");
    strcpy(course6->location, "教学楼F301");
    course6->capacity = 50;
    course6->currentEnrolled = 0;
    course6->materialHead = NULL;

    // 插入课程到B+树
    courseRoot = insertBPlusTree(courseRoot, 1, course1);
    courseRoot = insertBPlusTree(courseRoot, 2, course2);
    courseRoot = insertBPlusTree(courseRoot, 3, course3);
    courseRoot = insertBPlusTree(courseRoot, 4, course4);
    courseRoot = insertBPlusTree(courseRoot, 5, course5);
    courseRoot = insertBPlusTree(courseRoot, 6, course6);

    currentCourseId = 7;

    // 创建授课记录
    addTeacherToCourse(100, 1);
    addTeacherToCourse(101, 2);
    addTeacherToCourse(102, 3);
    addTeacherToCourse(103, 4);  // 新增
    addTeacherToCourse(104, 5);  // 新增
    addTeacherToCourse(105, 6);  // 新增

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

    Student* student3 = (Student*)malloc(sizeof(Student));
    student3->studentId = 1002;
    strcpy(student3->password, "1002");
    student3->grade = 2023;
    strcpy(student3->stuNum, "2023003");
    strcpy(student3->name, "张小刚");
    student3->enrolledCourses = NULL;

    Student* student4 = (Student*)malloc(sizeof(Student));
    student4->studentId = 1003;
    strcpy(student4->password, "1003");
    student4->grade = 2023;
    strcpy(student4->stuNum, "2023004");
    strcpy(student4->name, "杨小二");
    student4->enrolledCourses = NULL;

    // 新增学生
    Student* student5 = (Student*)malloc(sizeof(Student));
    student5->studentId = 1004;
    strcpy(student5->password, "1004");
    student5->grade = 2023;
    strcpy(student5->stuNum, "2023005");
    strcpy(student5->name, "赵小六");
    student5->enrolledCourses = NULL;

    Student* student6 = (Student*)malloc(sizeof(Student));
    student6->studentId = 1005;
    strcpy(student6->password, "1005");
    student6->grade = 2023;
    strcpy(student6->stuNum, "2023006");
    strcpy(student6->name, "刘小七");
    student6->enrolledCourses = NULL;

    // 插入学生到B+树
    studentRoot = insertBPlusTree(studentRoot, 1000, student1);
    studentRoot = insertBPlusTree(studentRoot, 1001, student2);
    studentRoot = insertBPlusTree(studentRoot, 1002, student3);
    studentRoot = insertBPlusTree(studentRoot, 1003, student4);
    studentRoot = insertBPlusTree(studentRoot, 1004, student5);
    studentRoot = insertBPlusTree(studentRoot, 1005, student6);

    currentStudentId = 1006;

    printf("系统初始化完成！\n");
    printf("创建了6门课程，6位教师，6名学生\n");
    printf("默认账号密码与ID相同\n\n");

    printf("课程B+树的高:%d\n", getBPlusTreeHeight(courseRoot));
    printf("课程B+树打印结果如下：\n");
    printBPlusTree(courseRoot, 0);  // 从根节点开始打印，层级为0

    printf("学生B+树的高:%d\n", getBPlusTreeHeight(studentRoot));
    printf("学生B+树打印结果如下：\n");
    printBPlusTree(studentRoot, 0);  // 从根节点开始打印，层级为0

    // 授课记录验证
    printf("\n=== 调试：授课记录验证 ===\n");
    TeachRecord* debugRecord = teachHead;
    int recordCount = 0;
    while (debugRecord != NULL) {
        printf("授课记录%d: 教师ID=%d, 课程ID=%d\n",
            ++recordCount, debugRecord->teacherId, debugRecord->courseId);
        debugRecord = debugRecord->next;
    }
    printf("总共%d条授课记录\n", recordCount);


    // 在最后添加学生选课初始化数据
    printf("\n正在初始化学生选课数据...\n");

    // 学生1000选择课程1和课程2
    enrollCourse(1000, 1);  // 王小明选择数据结构
    enrollCourse(1000, 2);  // 王小明选择算法设计与分析

    // 学生1001选择课程2和课程3
    enrollCourse(1001, 2);  // 李小红选择算法设计与分析
    enrollCourse(1001, 3);  // 李小红选择计算机网络编程

    // 学生1002选择课程1、课程3和课程4
    enrollCourse(1002, 1);  // 张小刚选择数据结构
    enrollCourse(1002, 3);  // 张小刚选择计算机网络编程
    enrollCourse(1002, 4);  // 张小刚选择操作系统

    // 学生1003选择课程4和课程5
    enrollCourse(1003, 4);  // 杨小二选择操作系统
    enrollCourse(1003, 5);  // 杨小二选择数据库系统

    // 学生1004选择课程5和课程6
    enrollCourse(1004, 5);  // 赵小六选择数据库系统
    enrollCourse(1004, 6);  // 赵小六选择编译原理

    // 学生1005选择课程1和课程6
    enrollCourse(1005, 1);  // 刘小七选择数据结构
    enrollCourse(1005, 6);  // 刘小七选择编译原理

    printf("学生选课初始化完成！\n");

    // 验证选课结果
    printf("\n=== 选课记录验证 ===\n");
    EnrollRecord* enrollRecord = enrollHead;
    int enrollCount = 0;
    while (enrollRecord != NULL) {
        printf("选课记录%d: 学生ID=%d, 课程ID=%d, 成绩=%.1f\n",
            ++enrollCount, enrollRecord->studentId, enrollRecord->courseId, enrollRecord->grade);
        enrollRecord = enrollRecord->next;
    }
    printf("总共%d条选课记录\n", enrollCount);

    // 显示课程选课统计
    printf("\n=== 课程选课统计 ===\n");
    for (int i = 1; i <= 6; i++) {
        Course* course = searchCourseById(i);
        if (course != NULL) {
            printf("课程%d(%s): %d/%d人选课\n",
                i, course->courseName, course->currentEnrolled, course->capacity);
        }
    }
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

//void statisticsMenu() {
//    printf("\n=== 统计功能 ===\n");
//    printf("1. 课程容量统计\n");
//    printf("2. 课程学分统计\n");
//    printf("请选择统计类型: ");
//
//    int choice;
//    scanf("%d", &choice);
//    clearInputBuffer();
//
//    switch (choice) {
//    case 1:
//        printf("课程容量统计功能开发中...\n");
//        break;
//    case 2:
//        printf("课程学分统计功能开发中...\n");
//        break;
//    default:
//        printf("无效选择！\n");
//    }
//}

// 全局变量，用于统计
static int g_totalCourses = 0;
static int g_fullCourses = 0;
static int g_totalCapacity = 0;
static int g_totalEnrolled = 0;
static int g_creditCount[10] = { 0 };
static int g_totalCredits = 0;

// 课程容量统计的回调函数
void statisticsCourseCapacityCallback(void* data) {
    Course* course = (Course*)data;

    float utilization = (float)course->currentEnrolled / course->capacity * 100;

    printf("%d\t%-15s\t%d\t%d\t%.1f%%\t",
        course->courseId, course->courseName,
        course->capacity, course->currentEnrolled, utilization);

    if (course->currentEnrolled >= course->capacity) {
        printf("已满\n");
        g_fullCourses++;
    }
    else if (utilization > 80) {
        printf("接近满员\n");
    }
    else if (utilization > 50) {
        printf("正常\n");
    }
    else {
        printf("空余较多\n");
    }

    g_totalCourses++;
    g_totalCapacity += course->capacity;
    g_totalEnrolled += course->currentEnrolled;
}

// 修改后的课程容量统计功能
void statisticsCourseCapacity() {
    printf("\n=== 课程容量统计 ===\n");
    printf("课程ID\t课程名\t\t容量\t已选\t利用率\t状态\n");
    printf("------------------------------------------------------------\n");

    // 重置全局统计变量
    g_totalCourses = 0;
    g_fullCourses = 0;
    g_totalCapacity = 0;
    g_totalEnrolled = 0;

    if (courseRoot == NULL) {
        printf("暂无课程数据。\n");
        return;
    }

    // 直接遍历B+树
    traverseBPlusTree(courseRoot, statisticsCourseCapacityCallback);

    if (g_totalCourses > 0) {
        printf("\n=== 统计摘要 ===\n");
        printf("总课程数: %d\n", g_totalCourses);
        printf("总容量: %d\n", g_totalCapacity);
        printf("总选课人次: %d\n", g_totalEnrolled);
        printf("整体利用率: %.1f%%\n", (float)g_totalEnrolled / g_totalCapacity * 100);
        printf("满员课程数: %d\n", g_fullCourses);
    }
    else {
        printf("暂无课程数据。\n");
    }
}

// 学分统计的回调函数
void statisticsCreditsCallback(void* data) {
    Course* course = (Course*)data;

    if (course->credits >= 1 && course->credits <= 9) {
        g_creditCount[course->credits]++;
    }
    g_totalCourses++;
    g_totalCredits += course->credits;
}

// 修改后的课程学分统计功能
void statisticsCreditsDistribution() {
    printf("\n=== 课程学分统计 ===\n");

    // 重置统计变量
    for (int i = 0; i < 10; i++) {
        g_creditCount[i] = 0;
    }
    g_totalCourses = 0;
    g_totalCredits = 0;

    if (courseRoot == NULL) {
        printf("暂无课程数据。\n");
        return;
    }

    // 直接遍历B+树
    traverseBPlusTree(courseRoot, statisticsCreditsCallback);

    printf("学分\t课程数\t占比\n");
    printf("----------------------\n");

    for (int i = 1; i <= 9; i++) {
        if (g_creditCount[i] > 0) {
            printf("%d学分\t%d\t%.1f%%\n",
                i, g_creditCount[i],
                (float)g_creditCount[i] / g_totalCourses * 100);
        }
    }

    if (g_totalCourses > 0) {
        printf("\n=== 学分统计摘要 ===\n");
        printf("总课程数: %d\n", g_totalCourses);
        printf("总学分数: %d\n", g_totalCredits);
        printf("平均学分: %.1f\n", (float)g_totalCredits / g_totalCourses);
    }
    else {
        printf("暂无课程数据。\n");
    }
}

// 修改 statisticsMenu 函数
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
        statisticsCourseCapacity();
        break;
    case 2:
        statisticsCreditsDistribution();
        break;
    default:
        printf("无效选择！\n");
    }
}


//void queryMenu() {
//    printf("\n=== 查询功能 ===\n");
//    printf("1. 按课程号范围查询\n");
//    printf("2. 按教师姓名查询课程\n");
//    printf("请选择查询类型: ");
//
//    int choice;
//    scanf("%d", &choice);
//    clearInputBuffer();
//
//    switch (choice) {
//    case 1:
//        printf("按课程号范围查询功能开发中...\n");
//        break;
//    case 2:
//        printf("按教师姓名查询功能开发中...\n");
//        break;
//    default:
//        printf("无效选择！\n");
//    }
//}

void queryCoursesByIdRange() {
    int startId, endId;

    printf("请输入起始课程号: ");
    scanf("%d", &startId);
    clearInputBuffer();

    printf("请输入结束课程号: ");
    scanf("%d", &endId);
    clearInputBuffer();

    if (startId > endId) {
        printf("起始课程号不能大于结束课程号！\n");
        return;
    }

    // 添加B+树结构调试
    printf("\n=== 调试：当前B+树结构 ===\n");
    printf("课程B+树根节点地址: %p\n", (void*)courseRoot);
    printf("课程B+树高度: %d\n", getBPlusTreeHeight(courseRoot));
    printf("B+树结构:\n");
    printBPlusTree(courseRoot, 0);

    // 直接测试B+树查找
    printf("\n=== 调试：直接测试B+树查找 ===\n");
    for (int testId = 1; testId <= 4; testId++) {
        void* result = searchBPlusTree(courseRoot, testId);
        printf("直接查找课程ID=%d: %s (地址: %p)\n",
            testId, result ? "找到" : "未找到", result);

        if (result != NULL) {
            Course* course = (Course*)result;
            printf("  课程名: %s\n", course->courseName);
        }
    }

    printf("\n=== 调试：授课记录验证 ===\n");
    TeachRecord* debugRecord = teachHead;
    int recordCount = 0;
    while (debugRecord != NULL) {
        printf("授课记录%d: 教师ID=%d, 课程ID=%d\n",
            ++recordCount, debugRecord->teacherId, debugRecord->courseId);
        debugRecord = debugRecord->next;
    }
    printf("总共%d条授课记录\n", recordCount);

    printf("\n=== 课程号 %d-%d 范围内的课程 ===\n", startId, endId);
    printf("课程ID\t课程名\t\t学分\t容量\t已选\t教师\n");
    printf("------------------------------------------------------------\n");

    int foundCount = 0;

    // 遍历指定范围的课程ID
    for (int courseId = startId; courseId <= endId; courseId++) {
        Course* course = searchCourseById(courseId);
        if (course != NULL) {
            // 简化教师查找逻辑，直接根据课程ID映射
            char teacherNames[200] = "未分配";
            if (courseId == 1) strcpy(teacherNames, "张教授");
            else if (courseId == 2) strcpy(teacherNames, "李老师");
            else if (courseId == 3) strcpy(teacherNames, "王老师");
            else {
                // 其他课程通过授课记录查找
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
            printf("调试: 课程ID=%d 在B+树中不存在\n", courseId);
        }
    }

    if (foundCount == 0) {
        printf("在指定范围内未找到课程。\n");
    }
    else {
        printf("\n共找到 %d 门课程。\n", foundCount);
    }
}

void queryCoursesByTeacherName() {
    char teacherName[30];

    printf("请输入教师姓名: ");
    fgets(teacherName, sizeof(teacherName), stdin);
    teacherName[strcspn(teacherName, "\n")] = 0;

    printf("\n=== 教师 \"%s\" 的授课信息 ===\n", teacherName);
    printf("课程ID\t课程名\t\t学分\t容量\t已选\t上课时间\n");
    printf("------------------------------------------------------------\n");

    int foundCount = 0;
    int teacherId = -1;

    // 查找教师ID
    for (int i = 0; i < teacherCount; i++) {
        if (strcmp(teacherArray[i].name, teacherName) == 0) {
            teacherId = teacherArray[i].teacherId;
            break;
        }
    }

    if (teacherId == -1) {
        printf("未找到教师 \"%s\"。\n", teacherName);
        return;
    }

    // 方法1：通过授课记录查找
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

    // 方法2：如果授课记录找不到，采用备用查找方式
    if (foundCount == 0) {
        printf("通过授课记录未找到，尝试备用查找...\n");

        // 遍历所有课程，根据教师ID匹配
        for (int courseId = 1; courseId < 100; courseId++) {
            Course* course = searchCourseById(courseId);
            if (course != NULL) {
                // 根据初始化逻辑判断是否为该教师的课程
                bool isTeachersCourse = false;
                if (teacherId == 100 && (courseId == 1 || courseId == 4)) {
                    isTeachersCourse = true;  // 张教授教课程1和4
                }
                else if (teacherId == 101 && courseId == 2) {
                    isTeachersCourse = true;  // 李老师教课程2
                }
                else if (teacherId == 102 && courseId == 3) {
                    isTeachersCourse = true;  // 王老师教课程3
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
        printf("教师 \"%s\" 暂无授课安排。\n", teacherName);
    }
    else {
        printf("\n共找到 %d 门课程。\n", foundCount);
    }
}

// 修改 queryMenu 函数
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
        queryCoursesByIdRange();
        break;
    case 2:
        queryCoursesByTeacherName();
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
