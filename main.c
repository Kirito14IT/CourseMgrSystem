#include "data_structures.h"
#include "admin.h"
#include "teacher.h"
#include "student.h"
#include "utils.h"
#include "bplus_tree.h"

// ȫ�ֱ�������
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
    strcpy(adminArray[0].name, "ϵͳ����Ա");
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
    system("cls");  // ������Windowsϵͳ
    // system("clear");  // Linux/Macϵͳ�������Ҫ�Ļ�

    printTitle("�����רҵ�γ̹���ϵͳ");
    printf("|\t\t\t\t\t\t|\n");
    printf("|\t��ѡ��������ݣ�\t\t\t|\n");
    printf("|\t\t\t\t\t\t|\n");
    printf("|\t[1] ����Ա��¼\t\t\t\t|\n");
    printf("|\t[2] ��ʦ��¼\t\t\t\t|\n");
    printf("|\t[3] ѧ����¼\t\t\t\t|\n");
    printf("|\t[0] �˳�ϵͳ\t\t\t\t|\n");
    printf("|\t\t\t\t\t\t|\n");
    printBorder();
    printf("����������ѡ�� (0-3): ");
}

void showWelcomeMessage() {
    printTitle("��ӭʹ�ÿγ̹���ϵͳ");
    printf("|\tϵͳ��ʼ�����\t\t\t\t|\n");
    printf("|\tĬ�Ϲ���Ա�˺�: 0\t\t\t|\n");
    printf("|\tĬ�Ϲ���Ա����: 0\t\t\t|\n");
    printf("|\t\t\t\t\t\t|\n");
    printBorder();
    printf("\n���س�������...");
    getchar();
}

void showLoginPrompt(const char* userType) {
    printf("\n");
    printf("+------------------+\n");
    printf("|   %s��¼����   |\n", userType);
    printf("+------------------+\n");
}

void showOperationResult(const char* message, int success) {
    printf("\n");
    if (success) {
        printf(">> �����ɹ�: %s\n", message);
    }
    else {
        printf(">> ����ʧ��: %s\n", message);
    }
    printf("\n");
}

void showErrorMessage(const char* error) {
    printf("\n");
    printf("*** ����: %s ***\n", error);
    printf("\n");
}

int main() {
    // ��ʼ��Ĭ�Ϲ���Ա
    initializeDefaultAdmin();

    // ��ʾ��ӭ��Ϣ
    showWelcomeMessage();

    int choice;
    int loginAttempts = 0;
    const int MAX_LOGIN_ATTEMPTS = 3;

    while (1) {
        showMainMenu();

        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            showErrorMessage("��������Ч������ѡ��");
            continue;
        }
        clearInputBuffer();

        switch (choice) {
        case 1: {
            showLoginPrompt("����Ա");
            int userId = login();
            if (userId != -1) {
                loginAttempts = 0;
                if (userId >= 0 && userId <= 99) {
                    adminMenu(userId);
                }
                else {
                    showErrorMessage("����ԱID��Χ���� (ӦΪ0-99)");
                }
            }
            else {
                loginAttempts++;
                if (loginAttempts >= MAX_LOGIN_ATTEMPTS) {
                    showErrorMessage("��¼ʧ�ܴ������࣬ϵͳ���˳�");
                    return 1;
                }
            }
            break;
        }
        case 2: {
            showLoginPrompt("��ʦ");
            int userId = login();
            if (userId != -1) {
                loginAttempts = 0;
                if (userId >= 100 && userId <= 999) {
                    teacherMenu(userId);
                }
                else {
                    showErrorMessage("��ʦID��Χ���� (ӦΪ100-999)");
                }
            }
            else {
                loginAttempts++;
                if (loginAttempts >= MAX_LOGIN_ATTEMPTS) {
                    showErrorMessage("��¼ʧ�ܴ������࣬ϵͳ���˳�");
                    return 1;
                }
            }
            break;
        }
        case 3: {
            showLoginPrompt("ѧ��");
            int userId = login();
            if (userId != -1) {
                loginAttempts = 0;
                if (userId >= 1000) {
                    studentMenu(userId);
                }
                else {
                    showErrorMessage("ѧ��ID��Χ���� (ӦΪ1000����)");
                }
            }
            else {
                loginAttempts++;
                if (loginAttempts >= MAX_LOGIN_ATTEMPTS) {
                    showErrorMessage("��¼ʧ�ܴ������࣬ϵͳ���˳�");
                    return 1;
                }
            }
            break;
        }
        case 0:
            printf("\n");
            printTitle("ϵͳ�˳�");
            printf("|\t��������ϵͳ��Դ...\t\t\t|\n");
            printf("|\t��лʹ�ÿγ̹���ϵͳ��\t\t\t|\n");
            printf("|\t�ټ���\t\t\t\t\t|\n");
            printBorder();

            // ����B+���ڴ�
            destroyBPlusTree(studentRoot);
            destroyBPlusTree(courseRoot);

            // ���������ڴ�
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
            showErrorMessage("��Чѡ��������0-3֮�������");
        }

        // ��������˳�����ͣһ�����û��������
        if (choice != 0) {
            printf("���س����������˵�...");
            getchar();
        }
    }

    return 0;
}
