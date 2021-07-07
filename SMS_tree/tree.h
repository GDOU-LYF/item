//
// Created by ��Դ�� on 2021/6/21.
//

#ifndef SMS_TREE_TREE_H
#define SMS_TREE_TREE_H

#include "student.h"
#include "course.h"
#include <cstdlib>
#include <cstdio>
#include <cstring>
//#include <io.h>
#include <unistd.h>

typedef struct stuNode {//student tree structure
    stu *student;
    stuNode *lchild, *rchild;
    int height;
} stuNode;

class tree {
public:
    int height(stuNode *root1);//��߶�

    stuNode *tree_node_LL(stuNode *root1);//����

    stuNode *tree_node_RR(stuNode *root1);//�ҵ���

    stuNode *tree_node_LR(stuNode *root1);//����˫��

    stuNode *tree_node_RL(stuNode *root1);//����˫��

    stuNode *createStuNode(struct stu *student);//����ѧ����Ϣ���

    stuNode *insert(stuNode *root1, stuNode *stu);//����

    stuNode *insert(stuNode *root1, stuNode *stu, stuNode *e);//override

    stuNode *find(stuNode *root1, char *sno);//����

    stuNode *remove(stuNode *root1, char *sno);//ɾ�����

    void update(stuNode *root1, stu *stu, int updateTofile);//����

    void print(stuNode *root1);//��������

    void print(stuNode *root1, int writeTofile);//�����д���ļ�

    void print_ALL(stuNode *root1, student *sc, courses *c);//���������Ϣ�������ɼ�

    void writeToFile(struct stu *stu);//ѧ����Ϣд���ļ�

    void writeToFileALL(stuNode *root1);//д�����н����Ϣ���ļ�

private:

};


#endif //SMS_TREE_TREE_H
