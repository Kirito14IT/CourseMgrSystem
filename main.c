#include "data_structures.h"
#include "admin.h"
#include "teacher.h"
#include "student.h"
#include "utils.h"

// 全局变量定义
Admin adminArray[100];
Teacher teacherArray[900];
int adminCount = 1;
int teacherCount = 0;
int currentAdminId = 0;
int currentTeacherId = 100;
int currentStudentId = 1000;
int currentCourseId = 1;
int currentMaterialId = 1;


BPlusTreeNode* studentRoot = NULL;
BPlusTreeNode* courseRoot = NULL;
EnrollRecord* enrollHead = NULL;
TeachRecord* teachHead = NULL;

void initializeDefaultAdmin() {
    adminArray[0].adminId = 0;
    strcpy(adminArray[0].password, "0");
    strcpy(adminArray[0].name, "系统管理员");
    adminCount = 1;
}

void showMainMenu() {
    printf("\n=== 计算机专业课程管理系统 ===\n");
    printf("1. 用户登录\n");
    printf("0. 退出系统\n");
    printf("请选择操作: ");
}

int main() {
    // 初始化默认管理员
    initializeDefaultAdmin();

    printf("欢迎使用计算机专业课程管理系统！\n");
    printf("默认管理员账号: ID=0, 密码=0\n");

    int choice;

    while (1) {
        showMainMenu();
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
        case 1: {
            int userId = login();
            if (userId != -1) {
                // 根据用户ID范围判断用户类型
                if (userId >= 0 && userId <= 99) {
                    // 管理员
                    adminMenu(userId);
                }
                else if (userId >= 100 && userId <= 999) {
                    // 教师
                    teacherMenu(userId);
                }
                else if (userId >= 1000) {
                    // 学生
                    studentMenu(userId);
                }
            }
            break;
        }
        case 0:
            printf("感谢使用课程管理系统！再见！\n");

            // 清理B+树内存
            destroyBPlusTree(studentRoot);
            destroyBPlusTree(courseRoot);

            // 清理链表内存
            EnrollRecord* enrollCurrent = enrollHead;
            while (enrollCurrent != NULL) {
                EnrollRecord* temp = enrollCurrent;
                enrollCurrent = enrollCurrent->next;
                free(temp);
            }

            TeachRecord* teachCurrent = teachHead;
            while (teachCurrent != NULL) {
                TeachRecord* temp = teachCurrent;
                teachCurrent = teachCurrent->next;
                free(temp);
            }

            return 0;
        default:
            printf("无效选择，请重试！\n");
        }

        pressEnterToContinue();
    }

    return 0;
}
