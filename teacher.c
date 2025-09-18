//teacher.c
#include "teacher.h"
#include "bplus_tree.h"
#include "utils.h"

void teacherMenu(int teacherId) {
    int choice;

    while (1) {
        printf("\n=== ��ʦ�˵� (ID: %d) ===\n", teacherId);
        printf("1. ��ӿγ�ѧϰ����\n");
        printf("2. �޸Ŀγ�ѧϰ����\n");
        printf("3. ɾ���γ�ѧϰ����\n");
        printf("4. ���ѧ���ɼ�\n");
        printf("5. �޸�ѧ���ɼ�\n");
        printf("6. ��ѯ�γ���Ϣ\n");
        printf("7. ͳ�ƿγ̳ɼ�\n");
        printf("8. ����γ�ѧϰ����\n");
        printf("0. �˳�\n");
        printf("��ѡ�����: ");

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
            printf("������γ�ID: ");
            scanf("%d", &courseId);
            clearInputBuffer();

            GradeStats stats = statisticsCourseGrades(teacherId, courseId);
            printf("�ɼ�ͳ�ƽ��:\n");
            printf("90������: %d��\n", stats.above90);
            printf("60-90��: %d��\n", stats.between60_90);
            printf("60������: %d��\n", stats.below60);
            printf("������: %d��\n", stats.totalStudents);
            break;
        }
        case 8:
            outputCourseMaterials(teacherId);
            break;
        case 0:
            return;
        default:
            printf("��Чѡ�������ԣ�\n");
        }

        pressEnterToContinue();
    }
}

void addCourseMaterial(int teacherId) {
    int courseId;
    char materialName[100];

    printf("������γ�ID: ");
    scanf("%d", &courseId);
    clearInputBuffer();

    if (!isTeacherOfCourse(teacherId, courseId)) {
        printf("�����Ǹÿγ̵��ڿν�ʦ��\n");
        return;
    }

    Course* course = searchCourseById(courseId);
    if (course == NULL) {
        printf("�γ̲����ڣ�\n");
        return;
    }

    printf("������ѧϰ��������: ");
    fgets(materialName, sizeof(materialName), stdin);
    materialName[strcspn(materialName, "\n")] = 0;

    Material* newMaterial = (Material*)malloc(sizeof(Material));
    newMaterial->materialId = currentMaterialId++;
    strcpy(newMaterial->materialName, materialName);

    // ��materialId�������
    if (course->materialHead == NULL || course->materialHead->materialId > newMaterial->materialId) {
        // ���뵽����ͷ��
        newMaterial->next = course->materialHead;
        course->materialHead = newMaterial;
    }
    else {
        // �ҵ����ʵĲ���λ��
        Material* current = course->materialHead;
        Material* prev = NULL;

        while (current != NULL && current->materialId < newMaterial->materialId) {
            prev = current;
            current = current->next;
        }

        // ���뵽prev��current֮��
        newMaterial->next = current;
        prev->next = newMaterial;
    }

    printf("ѧϰ������ӳɹ�������ID: %d\n", newMaterial->materialId);
}

void modifyCourseMaterial(int teacherId) {
    int courseId, materialId;
    char newName[100];

    printf("������γ�ID: ");
    scanf("%d", &courseId);
    clearInputBuffer();

    if (!isTeacherOfCourse(teacherId, courseId)) {
        printf("�����Ǹÿγ̵��ڿν�ʦ��\n");
        return;
    }

    printf("����������ID: ");
    scanf("%d", &materialId);
    clearInputBuffer();

    Material* material = findMaterial(courseId, materialId);
    if (material == NULL) {
        printf("ѧϰ���ϲ����ڣ�\n");
        return;
    }

    printf("��ǰ��������: %s\n", material->materialName);
    printf("�������µ���������: ");
    fgets(newName, sizeof(newName), stdin);
    newName[strcspn(newName, "\n")] = 0;

    strcpy(material->materialName, newName);
    printf("ѧϰ�����޸ĳɹ���\n");
}

void deleteCourseMaterial(int teacherId) {
    int courseId, materialId;

    printf("������γ�ID: ");
    scanf("%d", &courseId);
    clearInputBuffer();

    if (!isTeacherOfCourse(teacherId, courseId)) {
        printf("�����Ǹÿγ̵��ڿν�ʦ��\n");
        return;
    }

    Course* course = searchCourseById(courseId);
    if (course == NULL) {
        printf("�γ̲����ڣ�\n");
        return;
    }

    printf("������Ҫɾ��������ID: ");
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
            printf("ѧϰ����ɾ���ɹ���\n");
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("ѧϰ���ϲ����ڣ�\n");
}

void addStudentGrade(int teacherId) {
    int courseId, studentId;
    float grade;

    printf("������γ�ID: ");
    scanf("%d", &courseId);
    clearInputBuffer();

    if (!isTeacherOfCourse(teacherId, courseId)) {
        printf("�����Ǹÿγ̵��ڿν�ʦ��\n");
        return;
    }

    printf("������ѧ��ID: ");
    scanf("%d", &studentId);
    clearInputBuffer();

    printf("������ɼ�: ");
    scanf("%f", &grade);
    clearInputBuffer();

    if (grade < 0 || grade > 100) {
        printf("�ɼ�Ӧ��0-100֮�䣡\n");
        return;
    }

    // ����ѡ�μ�¼
    EnrollRecord* current = enrollHead;
    while (current != NULL) {
        if (current->studentId == studentId && current->courseId == courseId) {
            if (current->grade >= 0) {
                printf("��ѧ���ɼ��Ѵ��ڣ���ʹ���޸Ĺ��ܣ�\n");
                return;
            }
            current->grade = grade;

            // ͬ������ѧ������ѡ�μ�¼�ĳɼ�
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

            printf("�ɼ���ӳɹ���\n");
            return;
        }
        current = current->next;
    }

    printf("δ�ҵ���ѧ����ѡ�μ�¼��\n");
}

void modifyStudentGrade(int teacherId) {
    int courseId, studentId;
    float newGrade;

    printf("������γ�ID: ");
    scanf("%d", &courseId);
    clearInputBuffer();

    if (!isTeacherOfCourse(teacherId, courseId)) {
        printf("�����Ǹÿγ̵��ڿν�ʦ��\n");
        return;
    }

    printf("������ѧ��ID: ");
    scanf("%d", &studentId);
    clearInputBuffer();

    // ����ѡ�μ�¼
    EnrollRecord* current = enrollHead;
    while (current != NULL) {
        if (current->studentId == studentId && current->courseId == courseId) {
            if (current->grade < 0) {
                printf("��ѧ����δ¼��ɼ�����ʹ����ӹ��ܣ�\n");
                return;
            }

            printf("��ǰ�ɼ�: %.2f\n", current->grade);
            printf("�������³ɼ�: ");
            scanf("%f", &newGrade);
            clearInputBuffer();

            if (newGrade < 0 || newGrade > 100) {
                printf("�ɼ�Ӧ��0-100֮�䣡\n");
                return;
            }

            current->grade = newGrade;

            // ͬ������ѧ������ѡ�μ�¼�ĳɼ�
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

            printf("�ɼ��޸ĳɹ���\n");
            return;
        }
        current = current->next;
    }

    printf("δ�ҵ���ѧ����ѡ�μ�¼��\n");
}

//void teacherQueryMenu(int teacherId) {
//    printf("\n=== ��ѯ���� ===\n");
//    printf("1. ���ɼ���Χ��ѯѧ��\n");
//    printf("2. ��ѯѧϰ����ʹ�����\n");
//    printf("��ѡ���ѯ����: ");
//
//    int choice;
//    scanf("%d", &choice);
//    clearInputBuffer();
//
//    switch (choice) {
//    case 1:
//        printf("���ɼ���Χ��ѯѧ�����ܿ�����...\n");
//        break;
//    case 2:
//        printf("��ѯѧϰ����ʹ��������ܿ�����...\n");
//        break;
//    default:
//        printf("��Чѡ��\n");
//    }
//}

// ���ɼ���Χ��ѯѧ��
void queryStudentsByGradeRange(int teacherId) {
    int courseId;
    float minGrade, maxGrade;

    printf("������γ�ID: ");
    scanf("%d", &courseId);
    clearInputBuffer();

    if (!isTeacherOfCourse(teacherId, courseId)) {
        printf("�����Ǹÿγ̵��ڿν�ʦ��\n");
        return;
    }

    printf("��������ͳɼ�: ");
    scanf("%f", &minGrade);
    clearInputBuffer();

    printf("��������߳ɼ�: ");
    scanf("%f", &maxGrade);
    clearInputBuffer();

    if (minGrade > maxGrade) {
        printf("��ͳɼ����ܴ�����߳ɼ���\n");
        return;
    }

    Course* course = searchCourseById(courseId);
    if (course == NULL) {
        printf("�γ̲����ڣ�\n");
        return;
    }

    printf("\n=== �γ�\"%s\"�ɼ���Χ %.1f-%.1f ��ѧ�� ===\n",
        course->courseName, minGrade, maxGrade);
    printf("ѧ��ID\tѧ������\t\tѧ��\t\t�ɼ�\n");
    printf("--------------------------------------------\n");

    int foundCount = 0;
    float totalGrade = 0;

    EnrollRecord* current = enrollHead;
    while (current != NULL) {
        if (current->courseId == courseId && current->grade >= 0 &&
            current->grade >= minGrade && current->grade <= maxGrade) {

            Student* student = searchStudentById(current->studentId);
            if (student != NULL) {
                printf("%d\t%-15s\t%s\t\t%.2f\n",
                    student->studentId, student->name,
                    student->stuNum, current->grade);
                foundCount++;
                totalGrade += current->grade;
            }
        }
        current = current->next;
    }

    if (foundCount == 0) {
        printf("��ָ���ɼ���Χ��δ�ҵ�ѧ����\n");
    }
    else {
        printf("\n=== ͳ����Ϣ ===\n");
        printf("����������ѧ����: %d\n", foundCount);
        printf("ƽ���ɼ�: %.2f\n", totalGrade / foundCount);
    }
}

// ��ѯѧϰ����ʹ�����
void queryMaterialUsage(int teacherId) {
    int courseId;

    printf("������γ�ID: ");
    scanf("%d", &courseId);
    clearInputBuffer();

    if (!isTeacherOfCourse(teacherId, courseId)) {
        printf("�����Ǹÿγ̵��ڿν�ʦ��\n");
        return;
    }

    Course* course = searchCourseById(courseId);
    if (course == NULL) {
        printf("�γ̲����ڣ�\n");
        return;
    }

    printf("\n=== �γ�\"%s\"ѧϰ����ʹ����� ===\n", course->courseName);
    printf("����ID\t��������\t\t\t״̬\n");
    printf("------------------------------------------------\n");

    Material* material = course->materialHead;
    int materialCount = 0;
    int totalNameLength = 0;

    while (material != NULL) {
        printf("%d\t%-30s\t����\n",
            material->materialId, material->materialName);
        materialCount++;
        totalNameLength += strlen(material->materialName);
        material = material->next;
    }

    if (materialCount == 0) {
        printf("�ÿγ�����ѧϰ���ϡ�\n");
    }
    else {
        printf("\n=== ����ͳ�Ƹſ� ===\n");
        printf("��������: %d ��\n", materialCount);
        printf("ƽ������������: %.1f �ַ�\n", (float)totalNameLength / materialCount);

        // ͳ��ѡ��ѧ����
        int enrolledStudents = 0;
        EnrollRecord* enrollRecord = enrollHead;
        while (enrollRecord != NULL) {
            if (enrollRecord->courseId == courseId) {
                enrolledStudents++;
            }
            enrollRecord = enrollRecord->next;
        }
        printf("ѡ��ѧ����: %d ��\n", enrolledStudents);
        printf("�˾�������: %.1f ��/��\n",
            enrolledStudents > 0 ? (float)materialCount / enrolledStudents : 0);
    }
}

// �޸� teacherQueryMenu ����
void teacherQueryMenu(int teacherId) {
    printf("\n=== ��ѯ���� ===\n");
    printf("1. ���ɼ���Χ��ѯѧ��\n");
    printf("2. ��ѯѧϰ����ʹ�����\n");
    printf("��ѡ���ѯ����: ");

    int choice;
    scanf("%d", &choice);
    clearInputBuffer();

    switch (choice) {
    case 1:
        queryStudentsByGradeRange(teacherId);
        break;
    case 2:
        queryMaterialUsage(teacherId);
        break;
    default:
        printf("��Чѡ��\n");
    }
}


GradeStats statisticsCourseGrades(int teacherId, int courseId) {
    GradeStats stats = { 0, 0, 0, 0 };

    if (!isTeacherOfCourse(teacherId, courseId)) {
        printf("�����Ǹÿγ̵��ڿν�ʦ��\n");
        return stats;
    }

    Course* course = searchCourseById(courseId);
    if (course == NULL) {
        printf("�γ̲����ڣ�\n");
        return stats;
    }

    // ͳ�Ƹÿγ̳ɼ�
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

void outputCourseMaterials(int teacherId) {
    int courseId;

    printf("������γ�ID: ");
    scanf("%d", &courseId);
    clearInputBuffer();

    if (!isTeacherOfCourse(teacherId, courseId)) {
        printf("�����Ǹÿγ̵��ڿν�ʦ��\n");
        return;
    }

    Course* course = searchCourseById(courseId);
    if (course == NULL) {
        printf("�γ̲����ڣ�\n");
        return;
    }

    printf("\n=== �γ�\"%s\"��ѧϰ���� ===\n", course->courseName);
    printf("����ID\t��������\n");
    printf("----------------------------------------\n");

    Material* current = course->materialHead;
    int count = 0;

    while (current != NULL) {
        printf("%d\t%s\n", current->materialId, current->materialName);
        current = current->next;
        count++;
    }

    if (count == 0) {
        printf("�ÿγ�����ѧϰ���ϡ�\n");
    }
    else {
        printf("----------------------------------------\n");
        printf("���� %d ��ѧϰ����\n", count);
    }
}

