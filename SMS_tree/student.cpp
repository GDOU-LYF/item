//
// Created by ��Դ�� on 2021/6/21.
//

#include "student.h"
//
// Created by ��Դ�� on 2021/6/26.
//

#include "course.h"

void student::readintolist() {
    FILE *fp;
    if ((fp = fopen("grade.txt", "r")) == nullptr) {
        return;
    }
    fseek(fp, 0, SEEK_END);   //�ļ�λ��ָ���ƶ����ļ�ĩβ��
    if (ftell(fp) <= 0) {
        return;
    }
    rewind(fp);  //�ļ�λ��ָ���ƶ����ļ���ʼλ�á�
    scoreNode sc{};
    while (fscanf(fp, "%s\t%s\t%lf\r\n", sc.sno, sc.cno, &sc.grade) != -1) {
        list1.push_back(sc);
    }
}

void student::insert(scoreNode node) {
    if (find(node.sno, node.cno) == -1) {
        list1.push_back(node);
    } else {
        printf("�Ѿ����ڸ�ѧ���ÿγ̳ɼ���\n");
    }
}

double student::find(char *sno, char *cno) {
    std::list<scoreNode>::iterator it = std::find_if(list1.begin(), list1.end(), findgrade(sno, cno));

    if (it == list1.end()) {//������β=����β
        return -1;
    } else {
        return it->grade;
    }
}

void student::delete_sc(char *sno, char *cno) {
    std::list<scoreNode>::iterator it = std::find_if(list1.begin(), list1.end(), findgrade(sno, cno));
    if (it != list1.end()) {
        list1.erase(it);//�Ƴ����
    }
}

void student::update(char *sno, char *cno, double grade) {
    std::list<scoreNode>::iterator it = std::find_if(list1.begin(), list1.end(), findgrade(sno, cno));
    if (it != list1.end()) {//201611701209 �ߵ���ѧ��
        it->grade = grade;
    }
}

void student::writetofile() {
    std::list<scoreNode>::iterator it;
    FILE *fp;
    if ((fp = fopen("grade.txt", "w")) == nullptr) {
        printf("δ�ܶԳɼ���Ϣ�ļ�����\n");
        return;
    }
    for (it = list1.begin(); it != list1.end(); it++) {
        fprintf(fp, "%s\t%s\t%f\r\n", it->sno, it->cno, it->grade);
//        printf("write_Sc:%s\t%s\t%f\r", it->sno, it->cno, it->grade);
    }
    fflush(fp);
//    fsync(fileno(fp));
            _commit(_fileno(fp));//��ȡ�ļ���������ǿ��дӲ��
    fclose(fp);
}

void student::print_list() {
    std::list<scoreNode>::iterator it;
    if (list1.size() != 0) {
        printf("ѧ��\t�γ̺�\t�ɼ�\n");
        for (it = list1.begin(); it != list1.end(); it++) {
            printf("%s\t%s\t%.1f\n", it->sno, it->cno, it->grade);
        }
    }
}