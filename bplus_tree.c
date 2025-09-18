//bplus_tree.c
#include "bplus_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 //B+树节点创建
BPlusTreeNode* createBPlusTreeNode(bool isLeaf) {
    BPlusTreeNode* node = (BPlusTreeNode*)malloc(sizeof(BPlusTreeNode));
    if (!node) {
        printf("内存分配失败!\n");
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

// 查找合适的子节点位置
// 临时修复版本 - 适应现有B+树结构
int findChildIndex(BPlusTreeNode* node, int key) {
    int i = 0;
    while (i < node->keyCount && key > node->keys[i]) {
        i++;
    }

    // 特殊处理：如果key等于某个内部键，应该到包含该键的子树
    if (i < node->keyCount && key == node->keys[i]) {
        return i + 1;  // 向右偏移一位
    }

    return i;
}


// 分裂内部节点
BPlusTreeNode* splitInternalNode(BPlusTreeNode* node, int* midKey) {
    int mid = BPLUS_TREE_ORDER / 2;
    BPlusTreeNode* newNode = createBPlusTreeNode(false);

    *midKey = node->keys[mid];

    // 复制后半部分的键和子节点
    for (int i = mid + 1; i < node->keyCount; i++) {
        newNode->keys[i - mid - 1] = node->keys[i];
        newNode->children[i - mid - 1] = node->children[i];
    }
    newNode->children[node->keyCount - mid - 1] = node->children[node->keyCount];

    newNode->keyCount = node->keyCount - mid - 1;
    node->keyCount = mid;

    return newNode;
}

// 分裂叶子节点
BPlusTreeNode* splitLeafNode(BPlusTreeNode* node) {
    int mid = (BPLUS_TREE_ORDER + 1) / 2;
    BPlusTreeNode* newNode = createBPlusTreeNode(true);

    // 复制后半部分的数据
    for (int i = mid; i < node->keyCount; i++) {
        newNode->keys[i - mid] = node->keys[i];
        newNode->data[i - mid] = node->data[i];
    }

    newNode->keyCount = node->keyCount - mid;
    node->keyCount = mid;

    // 链接叶子节点
    newNode->next = node->next;
    node->next = newNode;

    return newNode;
}

// 在节点中插入键值对
void insertInNode(BPlusTreeNode* node, int key, void* data, BPlusTreeNode* child) {
    int i = node->keyCount;

    // 找到插入位置
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

// 递归插入函数
BPlusTreeNode* insertRecursive(BPlusTreeNode* node, int key, void* data, int* promotedKey, BPlusTreeNode** promotedChild) {
    *promotedChild = NULL;

    if (node->isLeaf) {
        // 检查是否已存在相同键
        for (int i = 0; i < node->keyCount; i++) {
            if (node->keys[i] == key) {
                // 更新数据
                node->data[i] = data;
                return node;
            }
        }

        // 插入到叶子节点
        if (node->keyCount < BPLUS_TREE_ORDER) {
            insertInNode(node, key, data, NULL);
            return node;
        }
        else {
            // 需要分裂叶子节点
            insertInNode(node, key, data, NULL);
            BPlusTreeNode* newLeaf = splitLeafNode(node);
            *promotedKey = newLeaf->keys[0];
            *promotedChild = newLeaf;
            return node;
        }
    }
    else {
        // 内部节点
        int childIndex = findChildIndex(node, key);
        int childPromotedKey;
        BPlusTreeNode* childPromotedChild;

        node->children[childIndex] = insertRecursive(node->children[childIndex], key, data, &childPromotedKey, &childPromotedChild);

        if (childPromotedChild != NULL) {
            // 子节点分裂了，需要在当前节点插入提升的键
            if (node->keyCount < BPLUS_TREE_ORDER) {
                insertInNode(node, childPromotedKey, NULL, childPromotedChild);
                return node;
            }
            else {
                // 当前节点也需要分裂
                insertInNode(node, childPromotedKey, NULL, childPromotedChild);
                BPlusTreeNode* newInternal = splitInternalNode(node, promotedKey);
                *promotedChild = newInternal;
                return node;
            }
        }
        return node;
    }
}

// B+树插入
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
//    // 如果根节点分裂了，创建新的根节点
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

 //B+树插入 - 添加数据验证
BPlusTreeNode* insertBPlusTree(BPlusTreeNode* root, int key, void* data) {
    if (data == NULL) {
        printf("错误：尝试插入空数据指针\n");
        return root;
    }

    printf("插入B+树 - 键值: %d, 数据地址: %p\n", key, data);

    if (root == NULL) {
        root = createBPlusTreeNode(true);
        if (root == NULL) {
            printf("错误：创建根节点失败\n");
            return NULL;
        }
        root->keys[0] = key;
        root->data[0] = data;
        root->keyCount = 1;

        printf("创建新根节点，地址: %p\n", (void*)root);
        return root;
    }

    int promotedKey;
    BPlusTreeNode* promotedChild;

    root = insertRecursive(root, key, data, &promotedKey, &promotedChild);

    // 如果根节点分裂了，创建新的根节点
    if (promotedChild != NULL) {
        BPlusTreeNode* newRoot = createBPlusTreeNode(false);
        if (newRoot == NULL) {
            printf("错误：创建新根节点失败\n");
            return root;
        }
        newRoot->keys[0] = promotedKey;
        newRoot->children[0] = root;
        newRoot->children[1] = promotedChild;
        newRoot->keyCount = 1;
        printf("根节点分裂，新根节点地址: %p\n", (void*)newRoot);
        return newRoot;
    }

    return root;
}


// B+树查找
void* searchBPlusTree(BPlusTreeNode* root, int key) {
    if (root == NULL) {
        return NULL;
    }

    BPlusTreeNode* current = root;

    // 遍历到叶子节点
    while (!current->isLeaf) {
        int childIndex = findChildIndex(current, key);
        current = current->children[childIndex];
    }

    // 在叶子节点中查找
    for (int i = 0; i < current->keyCount; i++) {
        if (current->keys[i] == key) {
            return current->data[i];
        }
    }

    return NULL;
}

// 找到叶子节点中键的位置
int findKeyInLeaf(BPlusTreeNode* leaf, int key) {
    for (int i = 0; i < leaf->keyCount; i++) {
        if (leaf->keys[i] == key) {
            return i;
        }
    }
    return -1;
}

// 从节点中删除指定位置的键
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

// 删除递归函数（简化版本）
BPlusTreeNode* deleteRecursive(BPlusTreeNode* node, int key) {
    if (node == NULL) {
        return NULL;
    }

    if (node->isLeaf) {
        // 在叶子节点中删除
        int keyIndex = findKeyInLeaf(node, key);
        if (keyIndex != -1) {
            removeFromNode(node, keyIndex);
        }
        return node;
    }
    else {
        // 内部节点 - 找到对应的子节点
        int childIndex = findChildIndex(node, key);
        node->children[childIndex] = deleteRecursive(node->children[childIndex], key);
        return node;
    }
}

// B+树删除
BPlusTreeNode* deleteBPlusTree(BPlusTreeNode* root, int key) {
    if (root == NULL) {
        return NULL;
    }

    root = deleteRecursive(root, key);

    // 如果根节点是内部节点且只有一个子节点，则将子节点提升为根节点
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

// 遍历B+树（只遍历叶子节点）
void traverseBPlusTree(BPlusTreeNode* root, void (*visit)(void* data)) {
    if (root == NULL || visit == NULL) {
        return;
    }

    // 找到最左边的叶子节点
    BPlusTreeNode* current = root;
    while (!current->isLeaf) {
        current = current->children[0];
    }

    // 沿着叶子节点链表遍历
    while (current != NULL) {
        for (int i = 0; i < current->keyCount; i++) {
            visit(current->data[i]);
        }
        current = current->next;
    }
}

// 销毁B+树
void destroyBPlusTree(BPlusTreeNode* root) {
    if (root == NULL) {
        printf("尝试释放空节点\n");
        return;
    }
    printf("释放节点: %p, 键数: %d, 是否叶子: %d\n",
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



// 便捷查找函数实现
Student* searchStudentById(int studentId) {
    return (Student*)searchBPlusTree(studentRoot, studentId);
}

Course* searchCourseById(int courseId) {
    return (Course*)searchBPlusTree(courseRoot, courseId);
}


// 打印B+树结构（调试用）
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

// 获取B+树高度
int getBPlusTreeHeight(BPlusTreeNode* root) {
    if (root == NULL) return 0;

    if (root->isLeaf) return 1;

    return 1 + getBPlusTreeHeight(root->children[0]);
}

