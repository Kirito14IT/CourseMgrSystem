//bplus_tree.h
#pragma once

#include "data_structures.h"

#define BPLUS_TREE_ORDER 3 // B+树关键字的个数，阶数为最大关键字个数加1

// B+树操作函数声明
BPlusTreeNode* createBPlusTreeNode(bool isLeaf);
BPlusTreeNode* insertBPlusTree(BPlusTreeNode* root, int key, void* data);
void* searchBPlusTree(BPlusTreeNode* root, int key);
BPlusTreeNode* deleteBPlusTree(BPlusTreeNode* root, int key);
void traverseBPlusTree(BPlusTreeNode* root, void (*visit)(void* data));
void destroyBPlusTree(BPlusTreeNode* root);

// 便捷查找函数
Student* searchStudentById(int studentId);
Course* searchCourseById(int courseId);

// 调试函数声明（可选）
void printBPlusTree(BPlusTreeNode* root, int level);
int getBPlusTreeHeight(BPlusTreeNode* root);


