//bplus_tree.c
#include "bplus_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 //B+���ڵ㴴��
BPlusTreeNode* createBPlusTreeNode(bool isLeaf) {
    BPlusTreeNode* node = (BPlusTreeNode*)malloc(sizeof(BPlusTreeNode));
    if (!node) {
        printf("�ڴ����ʧ��!\n");
        return NULL;
    }

    node->keys = (int*)malloc(sizeof(int) * BPLUS_TREE_ORDER);
    node->data = (void**)malloc(sizeof(void*) * BPLUS_TREE_ORDER);

    if (!isLeaf) {
        node->children = (BPlusTreeNode**)malloc(sizeof(BPlusTreeNode*) * (BPLUS_TREE_ORDER + 1));
        node->next = NULL;
    }
    else {
        node->children = NULL;
        node->next = NULL;
    }

    node->keyCount = 0;
    node->isLeaf = isLeaf;

    return node;
}

// ���Һ��ʵ��ӽڵ�λ��
// ��ʱ�޸��汾 - ��Ӧ����B+���ṹ
int findChildIndex(BPlusTreeNode* node, int key) {
    int i = 0;
    while (i < node->keyCount && key > node->keys[i]) {
        i++;
    }

    // ���⴦�����key����ĳ���ڲ�����Ӧ�õ������ü�������
    if (i < node->keyCount && key == node->keys[i]) {
        return i + 1;  // ����ƫ��һλ
    }

    return i;
}


// �����ڲ��ڵ�
BPlusTreeNode* splitInternalNode(BPlusTreeNode* node, int* midKey) {
    int mid = BPLUS_TREE_ORDER / 2;
    BPlusTreeNode* newNode = createBPlusTreeNode(false);

    *midKey = node->keys[mid];

    // ���ƺ�벿�ֵļ����ӽڵ�
    for (int i = mid + 1; i < node->keyCount; i++) {
        newNode->keys[i - mid - 1] = node->keys[i];
        newNode->children[i - mid - 1] = node->children[i];
    }
    newNode->children[node->keyCount - mid - 1] = node->children[node->keyCount];

    newNode->keyCount = node->keyCount - mid - 1;
    node->keyCount = mid;

    return newNode;
}

// ����Ҷ�ӽڵ�
BPlusTreeNode* splitLeafNode(BPlusTreeNode* node) {
    int mid = (BPLUS_TREE_ORDER + 1) / 2;
    BPlusTreeNode* newNode = createBPlusTreeNode(true);

    // ���ƺ�벿�ֵ�����
    for (int i = mid; i < node->keyCount; i++) {
        newNode->keys[i - mid] = node->keys[i];
        newNode->data[i - mid] = node->data[i];
    }

    newNode->keyCount = node->keyCount - mid;
    node->keyCount = mid;

    // ����Ҷ�ӽڵ�
    newNode->next = node->next;
    node->next = newNode;

    return newNode;
}

// �ڽڵ��в����ֵ��
void insertInNode(BPlusTreeNode* node, int key, void* data, BPlusTreeNode* child) {
    int i = node->keyCount;

    // �ҵ�����λ��
    while (i > 0 && key < node->keys[i - 1]) {
        node->keys[i] = node->keys[i - 1];
        if (node->isLeaf) {
            node->data[i] = node->data[i - 1];
        }
        else {
            node->children[i + 1] = node->children[i];
        }
        i--;
    }

    node->keys[i] = key;
    if (node->isLeaf) {
        node->data[i] = data;
    }
    else {
        node->children[i + 1] = child;
    }
    node->keyCount++;
}

// �ݹ���뺯��
BPlusTreeNode* insertRecursive(BPlusTreeNode* node, int key, void* data, int* promotedKey, BPlusTreeNode** promotedChild) {
    *promotedChild = NULL;

    if (node->isLeaf) {
        // ����Ƿ��Ѵ�����ͬ��
        for (int i = 0; i < node->keyCount; i++) {
            if (node->keys[i] == key) {
                // ��������
                node->data[i] = data;
                return node;
            }
        }

        // ���뵽Ҷ�ӽڵ�
        if (node->keyCount < BPLUS_TREE_ORDER) {
            insertInNode(node, key, data, NULL);
            return node;
        }
        else {
            // ��Ҫ����Ҷ�ӽڵ�
            insertInNode(node, key, data, NULL);
            BPlusTreeNode* newLeaf = splitLeafNode(node);
            *promotedKey = newLeaf->keys[0];
            *promotedChild = newLeaf;
            return node;
        }
    }
    else {
        // �ڲ��ڵ�
        int childIndex = findChildIndex(node, key);
        int childPromotedKey;
        BPlusTreeNode* childPromotedChild;

        node->children[childIndex] = insertRecursive(node->children[childIndex], key, data, &childPromotedKey, &childPromotedChild);

        if (childPromotedChild != NULL) {
            // �ӽڵ�����ˣ���Ҫ�ڵ�ǰ�ڵ���������ļ�
            if (node->keyCount < BPLUS_TREE_ORDER) {
                insertInNode(node, childPromotedKey, NULL, childPromotedChild);
                return node;
            }
            else {
                // ��ǰ�ڵ�Ҳ��Ҫ����
                insertInNode(node, childPromotedKey, NULL, childPromotedChild);
                BPlusTreeNode* newInternal = splitInternalNode(node, promotedKey);
                *promotedChild = newInternal;
                return node;
            }
        }
        return node;
    }
}

// B+������
//BPlusTreeNode* insertBPlusTree(BPlusTreeNode* root, int key, void* data) {
//    if (root == NULL) {
//        root = createBPlusTreeNode(true);
//        root->keys[0] = key;
//        root->data[0] = data;
//        root->keyCount = 1;
//        return root;
//    }
//
//    int promotedKey;
//    BPlusTreeNode* promotedChild;
//
//    root = insertRecursive(root, key, data, &promotedKey, &promotedChild);
//
//    // ������ڵ�����ˣ������µĸ��ڵ�
//    if (promotedChild != NULL) {
//        BPlusTreeNode* newRoot = createBPlusTreeNode(false);
//        newRoot->keys[0] = promotedKey;
//        newRoot->children[0] = root;
//        newRoot->children[1] = promotedChild;
//        newRoot->keyCount = 1;
//        return newRoot;
//    }
//
//    return root;
//}

 //B+������ - ���������֤
BPlusTreeNode* insertBPlusTree(BPlusTreeNode* root, int key, void* data) {
    if (data == NULL) {
        printf("���󣺳��Բ��������ָ��\n");
        return root;
    }

    printf("����B+�� - ��ֵ: %d, ���ݵ�ַ: %p\n", key, data);

    if (root == NULL) {
        root = createBPlusTreeNode(true);
        if (root == NULL) {
            printf("���󣺴������ڵ�ʧ��\n");
            return NULL;
        }
        root->keys[0] = key;
        root->data[0] = data;
        root->keyCount = 1;

        printf("�����¸��ڵ㣬��ַ: %p\n", (void*)root);
        return root;
    }

    int promotedKey;
    BPlusTreeNode* promotedChild;

    root = insertRecursive(root, key, data, &promotedKey, &promotedChild);

    // ������ڵ�����ˣ������µĸ��ڵ�
    if (promotedChild != NULL) {
        BPlusTreeNode* newRoot = createBPlusTreeNode(false);
        if (newRoot == NULL) {
            printf("���󣺴����¸��ڵ�ʧ��\n");
            return root;
        }
        newRoot->keys[0] = promotedKey;
        newRoot->children[0] = root;
        newRoot->children[1] = promotedChild;
        newRoot->keyCount = 1;
        printf("���ڵ���ѣ��¸��ڵ��ַ: %p\n", (void*)newRoot);
        return newRoot;
    }

    return root;
}


// B+������
void* searchBPlusTree(BPlusTreeNode* root, int key) {
    if (root == NULL) {
        return NULL;
    }

    BPlusTreeNode* current = root;

    // ������Ҷ�ӽڵ�
    while (!current->isLeaf) {
        int childIndex = findChildIndex(current, key);
        current = current->children[childIndex];
    }

    // ��Ҷ�ӽڵ��в���
    for (int i = 0; i < current->keyCount; i++) {
        if (current->keys[i] == key) {
            return current->data[i];
        }
    }

    return NULL;
}

// �ҵ�Ҷ�ӽڵ��м���λ��
int findKeyInLeaf(BPlusTreeNode* leaf, int key) {
    for (int i = 0; i < leaf->keyCount; i++) {
        if (leaf->keys[i] == key) {
            return i;
        }
    }
    return -1;
}

// �ӽڵ���ɾ��ָ��λ�õļ�
void removeFromNode(BPlusTreeNode* node, int index) {
    for (int i = index; i < node->keyCount - 1; i++) {
        node->keys[i] = node->keys[i + 1];
        if (node->isLeaf) {
            node->data[i] = node->data[i + 1];
        }
        else {
            node->children[i + 1] = node->children[i + 2];
        }
    }
    node->keyCount--;
}

// ɾ���ݹ麯�����򻯰汾��
BPlusTreeNode* deleteRecursive(BPlusTreeNode* node, int key) {
    if (node == NULL) {
        return NULL;
    }

    if (node->isLeaf) {
        // ��Ҷ�ӽڵ���ɾ��
        int keyIndex = findKeyInLeaf(node, key);
        if (keyIndex != -1) {
            removeFromNode(node, keyIndex);
        }
        return node;
    }
    else {
        // �ڲ��ڵ� - �ҵ���Ӧ���ӽڵ�
        int childIndex = findChildIndex(node, key);
        node->children[childIndex] = deleteRecursive(node->children[childIndex], key);
        return node;
    }
}

// B+��ɾ��
BPlusTreeNode* deleteBPlusTree(BPlusTreeNode* root, int key) {
    if (root == NULL) {
        return NULL;
    }

    root = deleteRecursive(root, key);

    // ������ڵ����ڲ��ڵ���ֻ��һ���ӽڵ㣬���ӽڵ�����Ϊ���ڵ�
    if (!root->isLeaf && root->keyCount == 0) {
        BPlusTreeNode* newRoot = root->children[0];
        free(root->keys);
        free(root->data);
        free(root->children);
        free(root);
        return newRoot;
    }

    return root;
}

// ����B+����ֻ����Ҷ�ӽڵ㣩
void traverseBPlusTree(BPlusTreeNode* root, void (*visit)(void* data)) {
    if (root == NULL || visit == NULL) {
        return;
    }

    // �ҵ�����ߵ�Ҷ�ӽڵ�
    BPlusTreeNode* current = root;
    while (!current->isLeaf) {
        current = current->children[0];
    }

    // ����Ҷ�ӽڵ��������
    while (current != NULL) {
        for (int i = 0; i < current->keyCount; i++) {
            visit(current->data[i]);
        }
        current = current->next;
    }
}

// ����B+��
void destroyBPlusTree(BPlusTreeNode* root) {
    if (root == NULL) {
        printf("�����ͷſսڵ�\n");
        return;
    }
    printf("�ͷŽڵ�: %p, ����: %d, �Ƿ�Ҷ��: %d\n",
        root, root->keyCount, root->isLeaf);

    if (!root->isLeaf) {
        for (int i = 0; i <= root->keyCount; i++) {
            destroyBPlusTree(root->children[i]);
        }
        if(root->children!=NULL)free(root->children);
    }

    //if(root->keys!=NULL)free(root->keys);
    //if (root->data != NULL)free(root->data);
    if (root != NULL)free(root);
}



// ��ݲ��Һ���ʵ��
Student* searchStudentById(int studentId) {
    return (Student*)searchBPlusTree(studentRoot, studentId);
}

Course* searchCourseById(int courseId) {
    return (Course*)searchBPlusTree(courseRoot, courseId);
}


// ��ӡB+���ṹ�������ã�
void printBPlusTree(BPlusTreeNode* root, int level) {
    if (root == NULL) return;

    for (int i = 0; i < level; i++) {
        printf("  ");
    }

    printf("Level %d: ", level);
    for (int i = 0; i < root->keyCount; i++) {
        printf("%d ", root->keys[i]);
    }
    printf("(%s)\n", root->isLeaf ? "Leaf" : "Internal");

    if (!root->isLeaf) {
        for (int i = 0; i <= root->keyCount; i++) {
            printBPlusTree(root->children[i], level + 1);
        }
    }
}

// ��ȡB+���߶�
int getBPlusTreeHeight(BPlusTreeNode* root) {
    if (root == NULL) return 0;

    if (root->isLeaf) return 1;

    return 1 + getBPlusTreeHeight(root->children[0]);
}

