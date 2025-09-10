#include "teacher.h"
#include "bplus_tree.h"
#include "utils.h"

void teacherMenu(int teacherId) {
    int choice;

    while (1) {
        printf("\n=== 教师菜单 (ID: %d) ===\n", teacherId);
        printf("1. 添加课程学习资料\n");
        printf("2. 修改课程学习资料\n");
        printf("3. 删除课程学习资料\n");
        printf("4. 添加学生成绩\n");
        printf("5. 修改学生成绩\n");
        printf("6. 查询课程信息\n");
        printf("7. 统计课程成绩\n");
        printf("0. 退出\n");
        printf("请选择操作: ");

        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
        case 1:
            addCourseMaterial(teacherId);
            break;
        case 2:
            modifyCourseMaterial(teacherId);
            break;
        case 3:
            deleteCourseMaterial(teacherId);
            break;
        case 4:
            addStudentGrade(teacherId);
            break;
        case 5:
            modifyStudentGrade(teacherId);
            break;
        case 6:
            teacherQueryMenu(teacherId);
            break;
        case 7: {
            int courseId;
            printf("请输入课程ID: ");
            scanf("%d", &courseId);
            clearInputBuffer();

            GradeStats stats = statisticsCourseGrades(teacherId, courseId);
            printf("成绩统计结果:\n");
            printf("90分以上: %d人\n", stats.above90);
            printf("60-90分: %d人\n", stats.between60_90);
            printf("60分以下: %d人\n", stats.below60);
            printf("总人数: %d人\n", stats.totalStudents);
            break;
        }
        case 0:
            return;
        default:
            printf("无效选择，请重试！\n");
        }

        pressEnterToContinue();
    }
}

void addCourseMaterial(int teacherId) {
    int courseId;
    char materialName[100];

    printf("请输入课程ID: ");
    scanf("%d", &courseId);
    clearInputBuffer();

    if (!isTeacherOfCourse(teacherId, courseId)) {
        printf("您不是该课程的授课教师！\n");
        return;
    }

    Course* course = searchCourseById(courseId);
    if (course == NULL) {
        printf("课程不存在！\n");
        return;
    }

    printf("请输入学习资料名称: ");
    fgets(materialName, sizeof(materialName), stdin);
    materialName[strcspn(materialName, "\n")] = 0;

    Material* newMaterial = (Material*)malloc(sizeof(Material));
    newMaterial->materialId = currentMaterialId++;
    strcpy(newMaterial->materialName, materialName);
    newMaterial->next = course->materialHead;
    course->materialHead = newMaterial;

    printf("学习资料添加成功！资料ID: %d\n", newMaterial->materialId);
}

void modifyCourseMaterial(int teacherId) {
    int courseId, materialId;
    char newName[100];

    printf("请输入课程ID: ");
    scanf("%d", &courseId);
    clearInputBuffer();

    if (!isTeacherOfCourse(teacherId, courseId)) {
        printf("您不是该课程的授课教师！\n");
        return;
    }

    printf("请输入资料ID: ");
    scanf("%d", &materialId);
    clearInputBuffer();

    Material* material = findMaterial(courseId, materialId);
    if (material == NULL) {
        printf("学习资料不存在！\n");
        return;
    }

    printf("当前资料名称: %s\n", material->materialName);
    printf("请输入新的资料名称: ");
    fgets(newName, sizeof(newName), stdin);
    newName[strcspn(newName, "\n")] = 0;

    strcpy(material->materialName, newName);
    printf("学习资料修改成功！\n");
}

void deleteCourseMaterial(int teacherId) {
    int courseId, materialId;

    printf("请输入课程ID: ");
    scanf("%d", &courseId);
    clearInputBuffer();

    if (!isTeacherOfCourse(teacherId, courseId)) {
        printf("您不是该课程的授课教师！\n");
        return;
    }

    Course* course = searchCourseById(courseId);
    if (course == NULL) {
        printf("课程不存在！\n");
        return;
    }

    printf("请输入要删除的资料ID: ");
    scanf("%d", &materialId);
    clearInputBuffer();

    Material* current = course->materialHead;
    Material* prev = NULL;

    while (current != NULL) {
        if (current->materialId == materialId) {
            if (prev == NULL) {
                course->materialHead = current->next;
            }
            else {
                prev->next = current->next;
            }
            free(current);
            printf("学习资料删除成功！\n");
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("学习资料不存在！\n");
}

void addStudentGrade(int teacherId) {
    int courseId, studentId;
    float grade;

    printf("请输入课程ID: ");
    scanf("%d", &courseId);
    clearInputBuffer();

    if (!isTeacherOfCourse(teacherId, courseId)) {
        printf("您不是该课程的授课教师！\n");
        return;
    }

    printf("请输入学生ID: ");
    scanf("%d", &studentId);
    clearInputBuffer();

    printf("请输入成绩: ");
    scanf("%f", &grade);
    clearInputBuffer();

    if (grade < 0 || grade > 100) {
        printf("成绩应在0-100之间！\n");
        return;
    }

    // 查找选课记录
    EnrollRecord* current = enrollHead;
    while (current != NULL) {
        if (current->studentId == studentId && current->courseId == courseId) {
            if (current->grade >= 0) {
                printf("该学生成绩已存在，请使用修改功能！\n");
                return;
            }
            current->grade = grade;

            // 同步更新学生个人选课记录的成绩
            Student* student = searchStudentById(studentId);
            if (student != NULL) {
                EnrollNode* enrollNode = student->enrolledCourses;
                while (enrollNode != NULL) {
                    if (enrollNode->courseId == courseId) {
                        enrollNode->grade = grade;
                        break;
                    }
                    enrollNode = enrollNode->next;
                }
            }

            printf("成绩添加成功！\n");
            return;
        }
        current = current->next;
    }

    printf("未找到该学生的选课记录！\n");
}

void modifyStudentGrade(int teacherId) {
    int courseId, studentId;
    float newGrade;

    printf("请输入课程ID: ");
    scanf("%d", &courseId);
    clearInputBuffer();

    if (!isTeacherOfCourse(teacherId, courseId)) {
        printf("您不是该课程的授课教师！\n");
        return;
    }

    printf("请输入学生ID: ");
    scanf("%d", &studentId);
    clearInputBuffer();

    // 查找选课记录
    EnrollRecord* current = enrollHead;
    while (current != NULL) {
        if (current->studentId == studentId && current->courseId == courseId) {
            if (current->grade < 0) {
                printf("该学生尚未录入成绩，请使用添加功能！\n");
                return;
            }

            printf("当前成绩: %.2f\n", current->grade);
            printf("请输入新成绩: ");
            scanf("%f", &newGrade);
            clearInputBuffer();

            if (newGrade < 0 || newGrade > 100) {
                printf("成绩应在0-100之间！\n");
                return;
            }

            current->grade = newGrade;

            // 同步更新学生个人选课记录的成绩
            Student* student = searchStudentById(studentId);
            if (student != NULL) {
                EnrollNode* enrollNode = student->enrolledCourses;
                while (enrollNode != NULL) {
                    if (enrollNode->courseId == courseId) {
                        enrollNode->grade = newGrade;
                        break;
                    }
                    enrollNode = enrollNode->next;
                }
            }

            printf("成绩修改成功！\n");
            return;
        }
        current = current->next;
    }

    printf("未找到该学生的选课记录！\n");
}

void teacherQueryMenu(int teacherId) {
    printf("\n=== 查询功能 ===\n");
    printf("1. 按成绩范围查询学生\n");
    printf("2. 查询学习资料使用情况\n");
    printf("请选择查询类型: ");

    int choice;
    scanf("%d", &choice);
    clearInputBuffer();

    switch (choice) {
    case 1:
        printf("按成绩范围查询学生功能开发中...\n");
        break;
    case 2:
        printf("查询学习资料使用情况功能开发中...\n");
        break;
    default:
        printf("无效选择！\n");
    }
}

GradeStats statisticsCourseGrades(int teacherId, int courseId) {
    GradeStats stats = { 0, 0, 0, 0 };

    if (!isTeacherOfCourse(teacherId, courseId)) {
        printf("您不是该课程的授课教师！\n");
        return stats;
    }

    Course* course = searchCourseById(courseId);
    if (course == NULL) {
        printf("课程不存在！\n");
        return stats;
    }

    // 统计该课程成绩
    EnrollRecord* current = enrollHead;
    while (current != NULL) {
        if (current->courseId == courseId && current->grade >= 0) {
            stats.totalStudents++;
            if (current->grade >= 90) {
                stats.above90++;
            }
            else if (current->grade >= 60) {
                stats.between60_90++;
            }
            else {
                stats.below60++;
            }
        }
        current = current->next;
    }

    return stats;
}

bool isTeacherOfCourse(int teacherId, int courseId) {
    for (int i = 0; i < teacherCount; i++) {
        if (teacherArray[i].teacherId == teacherId) {
            CourseNode* current = teacherArray[i].taughtCourses;
            while (current != NULL) {
                if (current->courseId == courseId) {
                    return true;
                }
                current = current->next;
            }
            break;
        }
    }
    return false;
}

Material* findMaterial(int courseId, int materialId) {
    Course* course = searchCourseById(courseId);
    if (course == NULL) {
        return NULL;
    }

    Material* current = course->materialHead;
    while (current != NULL) {
        if (current->materialId == materialId) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}
