//
// Created by ��Դ�� on 2021/6/21.
//

#ifndef SMS_TREE_STUDENT_H
#define SMS_TREE_STUDENT_H

#include <list>
#include <unistd.h>

struct stu {//student message ѧ�ţ��������Ա����䣬���ᣬרҵ
    char sno[20];
    int pos;//ƫ����
    char name[20];
    char sex[4];
    int age;
    char region[20];
    char pro[20];
    //char addcount;//���ӵ��ֶθ���
    //char *message;//����
};


typedef struct course {//�γ���Ϣ
    char cno[20];
    char cname[20];
    double credit;
    int time;
} courseNode;

typedef struct score {//�ɼ���Ϣ
    char sno[20];
    char cno[20];
    double grade;
} scoreNode;


class findgrade {//STL����corse�Ƿ���
public:
    findgrade(char *sno, char *cno) {
        this->sno = sno;
        this->cno = cno;
    }

    bool operator()(scoreNode &sc) {
        return strcmp(sc.cno, cno) == 0 and strcmp(sc.sno, sno) == 0;
    }

private:
    char *sno, *cno;
};

struct comnode_sc {
    bool operator()(scoreNode &a, scoreNode &b) {//�Ƚ���
        int ret = strcmp(a.sno, b.sno);
        if (ret == 0) {
            ret = strcmp(a.cno, b.cno);
        }
        return ret < 0;
    }
};

class student {
public:
    void insert(scoreNode node);//����sc

    double find(char *sno, char *cno);//����

    void delete_sc(char *sno, char *cno);//ɾ��

    void update(char *sno, char *cno, double grade);//����

    void sort_c() {//����
        list1.sort(comnode_sc());
    }

    void writetofile();//д���ļ�

    void readintolist();//���뵽list

    void print_list();//���sc(sno,cno,grade) ������

private:
    std::list<scoreNode> list1;
};
#endif //SMS_TREE_STUDENT_H
