#pragma once

#include "data_structures.h"

#define BPLUS_TREE_ORDER 4

// B+��������������
BPlusTreeNode* createBPlusTreeNode(bool isLeaf);
BPlusTreeNode* insertBPlusTree(BPlusTreeNode* root, int key, void* data);
void* searchBPlusTree(BPlusTreeNode* root, int key);
BPlusTreeNode* deleteBPlusTree(BPlusTreeNode* root, int key);
void traverseBPlusTree(BPlusTreeNode* root, void (*visit)(void* data));
void destroyBPlusTree(BPlusTreeNode* root);

// ��ݲ��Һ���
Student* searchStudentById(int studentId);
Course* searchCourseById(int courseId);

// ���Ժ�����������ѡ��
void printBPlusTree(BPlusTreeNode* root, int level);
int getBPlusTreeHeight(BPlusTreeNode* root);
