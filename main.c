#include "data_structures.h"
#include "admin.h"
#include "teacher.h"
#include "student.h"
#include "utils.h"

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

void showMainMenu() {
    printf("\n=== �����רҵ�γ̹���ϵͳ ===\n");
    printf("1. �û���¼\n");
    printf("0. �˳�ϵͳ\n");
    printf("��ѡ�����: ");
}

int main() {
    // ��ʼ��Ĭ�Ϲ���Ա
    initializeDefaultAdmin();

    printf("��ӭʹ�ü����רҵ�γ̹���ϵͳ��\n");
    printf("Ĭ�Ϲ���Ա�˺�: ID=0, ����=0\n");

    int choice;

    while (1) {
        showMainMenu();
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
        case 1: {
            int userId = login();
            if (userId != -1) {
                // �����û�ID��Χ�ж��û�����
                if (userId >= 0 && userId <= 99) {
                    // ����Ա
                    adminMenu(userId);
                }
                else if (userId >= 100 && userId <= 999) {
                    // ��ʦ
                    teacherMenu(userId);
                }
                else if (userId >= 1000) {
                    // ѧ��
                    studentMenu(userId);
                }
            }
            break;
        }
        case 0:
            printf("��лʹ�ÿγ̹���ϵͳ���ټ���\n");

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
            printf("��Чѡ�������ԣ�\n");
        }

        pressEnterToContinue();
    }

    return 0;
}
