//
// Created by ��Դ�� on 2021/6/26.
//

#include "course.h"

void courses::readintolist() {
    FILE *fp;
    if ((fp = fopen("course.txt", "r")) == nullptr) {
        return;
    }
    fseek(fp, 0, SEEK_END);   //�ļ�λ��ָ���ƶ����ļ�ĩβ��
    if (ftell(fp) <= 0) {
        return;
    }
    rewind(fp);  //�ļ�λ��ָ���ƶ����ļ���ʼλ�á�
    courseNode c{};
    while (fscanf(fp, "%s\t%s\t%lf\t%d\r\n", c.cno, c.cname, &c.credit, &c.time) != -1) {
        list1.push_back(c);
    }
}

void courses::insert(courseNode node) {
    if (find(node.cno) != nullptr) {
        printf("�ÿγ���Ϣ�Ѵ��ڣ�\n");
    } else {
        list1.push_back(node);
    }
}

void courses::insert() {
    courseNode c{};
    printf("����γ̺� �γ����� ѧ�� ѧʱ���ÿո�ָ:");
    scanf("%s %s %lf %d", c.cno, c.cname, &c.credit, &c.time);
    if (find(c.cno) != nullptr) {
        printf("�ÿγ���Ϣ�Ѵ��ڣ�\n");
    } else {
        list1.push_back(c);
    }
}

courseNode *courses::find(char *cno) {
    if (cno == nullptr) {
        return nullptr;
    }
    std::list<courseNode>::iterator it = std::find_if(list1.begin(), list1.end(), findcno(cno));
    courseNode *c = (courseNode *) malloc(sizeof(struct course));
    if (it == list1.end()) {//������β=����β
        return nullptr;
    } else {
        strcpy(c->cno, it->cno);
        strcpy(c->cname, it->cname);
        c->time = it->time;
        c->credit = it->credit;
        return c;
    }
}

void courses::delete_c(char *cno) {
    std::list<courseNode>::iterator it = std::find_if(list1.begin(), list1.end(), findcno(cno));
    if (it != list1.end()) {
        list1.erase(it);//�Ƴ����
    }
}

void courses::update(char *cno) {
    std::list<courseNode>::iterator it = std::find_if(list1.begin(), list1.end(), findcno(cno));
    char s[20];
    if (it != list1.end()) {
        printf("�����µĿγ����� ѧ�� ѧʱ���ÿո�ָ:");
        scanf("%s", s);
        if (s[0] != 0) {
            strcpy(it->cname, s);
        }
        scanf("%s", s);
        if (s[0] != 0) {
            it->credit = atof(s);
        }
        scanf("%s", s);
        if (s[0] != 0) {
            it->time = atoi(s);
        }
    }
}

void courses::print_list() {
    std::list<courseNode>::iterator it;
    if (list1.size() != 0) {
        printf("�γ̺�\t\t�γ�����\t\t\tѧ��\t\tѧʱ\n");
        for (it = list1.begin(); it != list1.end(); it++) {
            printf("%s\t%-20s\t%5.1f%5d\n", it->cno, it->cname, it->credit, it->time);
        }
    }
}

void courses::writetofile() {
    std::list<courseNode>::iterator it;
    FILE *fp;
    if ((fp = fopen("course.txt", "w")) == nullptr) {
        printf("δ�ܶԿγ���Ϣ�ļ�����\n");
        return;
    }
    for (it = list1.begin(); it != list1.end(); it++) {
        fprintf(fp, "%s\t%s\t%f\t%d\r\n", it->cno, it->cname, it->credit, it->time);
    }
    fflush(fp);
//    fsync(fileno(fp));
            _commit(_fileno(fp));//��ȡ�ļ���������ǿ��дӲ��
    fclose(fp);
}