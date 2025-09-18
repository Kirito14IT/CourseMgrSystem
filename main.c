#include "data_structures.h"
#include "admin.h"
#include "teacher.h"
#include "student.h"
#include "utils.h"
#include "bplus_tree.h"

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

void printBorder() {
    printf("========================================================\n");
}

void printTitle(const char* title) {
    int len = strlen(title);
    int padding = (50 - len) / 2;

    printBorder();
    printf("|");
    for (int i = 0; i < padding; i++) printf(" ");
    printf("%s", title);
    for (int i = 0; i < (50 - len - padding); i++) printf(" ");
    printf("|\n");
    printBorder();
}

void showMainMenu() {
    system("cls");  // 清屏，Windows系统
    // system("clear");  // Linux/Mac系统，如果需要的话

    printTitle("计算机专业课程管理系统");
    printf("|\t\t\t\t\t\t|\n");
    printf("|\t请选择您的身份：\t\t\t|\n");
    printf("|\t\t\t\t\t\t|\n");
    printf("|\t[1] 管理员登录\t\t\t\t|\n");
    printf("|\t[2] 教师登录\t\t\t\t|\n");
    printf("|\t[3] 学生登录\t\t\t\t|\n");
    printf("|\t[0] 退出系统\t\t\t\t|\n");
    printf("|\t\t\t\t\t\t|\n");
    printBorder();
    printf("请输入您的选择 (0-3): ");
}

void showWelcomeMessage() {
    printTitle("欢迎使用课程管理系统");
    printf("|\t系统初始化完成\t\t\t\t|\n");
    printf("|\t默认管理员账号: 0\t\t\t|\n");
    printf("|\t默认管理员密码: 0\t\t\t|\n");
    printf("|\t\t\t\t\t\t|\n");
    printBorder();
    printf("\n按回车键继续...");
    getchar();
}

void showLoginPrompt(const char* userType) {
    printf("\n");
    printf("+------------------+\n");
    printf("|   %s登录界面   |\n", userType);
    printf("+------------------+\n");
}

void showOperationResult(const char* message, int success) {
    printf("\n");
    if (success) {
        printf(">> 操作成功: %s\n", message);
    }
    else {
        printf(">> 操作失败: %s\n", message);
    }
    printf("\n");
}

void showErrorMessage(const char* error) {
    printf("\n");
    printf("*** 错误: %s ***\n", error);
    printf("\n");
}

int main() {
    // 初始化默认管理员
    initializeDefaultAdmin();

    // 显示欢迎信息
    showWelcomeMessage();

    int choice;
    int loginAttempts = 0;
    const int MAX_LOGIN_ATTEMPTS = 3;

    while (1) {
        showMainMenu();

        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            showErrorMessage("请输入有效的数字选项");
            continue;
        }
        clearInputBuffer();

        switch (choice) {
        case 1: {
            showLoginPrompt("管理员");
            int userId = login();
            if (userId != -1) {
                loginAttempts = 0;
                if (userId >= 0 && userId <= 99) {
                    adminMenu(userId);
                }
                else {
                    showErrorMessage("管理员ID范围错误 (应为0-99)");
                }
            }
            else {
                loginAttempts++;
                if (loginAttempts >= MAX_LOGIN_ATTEMPTS) {
                    showErrorMessage("登录失败次数过多，系统将退出");
                    return 1;
                }
            }
            break;
        }
        case 2: {
            showLoginPrompt("教师");
            int userId = login();
            if (userId != -1) {
                loginAttempts = 0;
                if (userId >= 100 && userId <= 999) {
                    teacherMenu(userId);
                }
                else {
                    showErrorMessage("教师ID范围错误 (应为100-999)");
                }
            }
            else {
                loginAttempts++;
                if (loginAttempts >= MAX_LOGIN_ATTEMPTS) {
                    showErrorMessage("登录失败次数过多，系统将退出");
                    return 1;
                }
            }
            break;
        }
        case 3: {
            showLoginPrompt("学生");
            int userId = login();
            if (userId != -1) {
                loginAttempts = 0;
                if (userId >= 1000) {
                    studentMenu(userId);
                }
                else {
                    showErrorMessage("学生ID范围错误 (应为1000以上)");
                }
            }
            else {
                loginAttempts++;
                if (loginAttempts >= MAX_LOGIN_ATTEMPTS) {
                    showErrorMessage("登录失败次数过多，系统将退出");
                    return 1;
                }
            }
            break;
        }
        case 0:
            printf("\n");
            printTitle("系统退出");
            printf("|\t正在清理系统资源...\t\t\t|\n");
            printf("|\t感谢使用课程管理系统！\t\t\t|\n");
            printf("|\t再见！\t\t\t\t\t|\n");
            printBorder();

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
            showErrorMessage("无效选择，请输入0-3之间的数字");
        }

        // 如果不是退出，暂停一下让用户看到结果
        if (choice != 0) {
            printf("按回车键返回主菜单...");
            getchar();
        }
    }

    return 0;
}
