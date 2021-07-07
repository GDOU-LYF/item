#include "tree.h"
#include "student.h"
#include "files.h"
#include <iostream>
#include <cstring>
#include "course.h"
//#include <io.h>
#include <unistd.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat"
#pragma ide diagnostic ignored "cert-err34-c"
stuNode *root = nullptr;
int pos_extends = 0;

int input_student(struct stu *stu) {
    int ret = 1;
    printf("��������ѧ����Ϣ��ѧ�� ���� �Ա� ���� ���� רҵ(�ÿո�ֿ�)\n");//����ѧ��Ϊ12λ���޶���
    scanf("%s %s %s %d %s %s",
          &stu->sno, &stu->name, &stu->sex, &stu->age, &stu->region, &stu->pro);

    int count = 0;
    for (int i = 0; stu->sno[i] != 0; i++) {//ѧ�źϷ��ԡ��ж��Ƿ�Ϊ���֣�12λ��ǰ4λ�Ƿ���ȷ���
        if ((stu->sno[i] >= '0' && stu->sno[i] <= '9')) {
            count += 1;
        }
    }
    if (count == 0) {
        printf("ѧ�Ų���Ϊ�գ�\n");
        ret = 0;
    } else if (count == 12) {
        if (stu->sno[0] > '2' or stu->sno[1] > '0' or stu->sno[2] > '2') {
            printf("ѧ�ŵ���ݳ���\n");
            ret = 0;
        }
    }

    if (strcmp(stu->sex, "��") != 0 and strcmp(stu->sex, "Ů") != 0) {
        printf("�Ա����\n");
        ret = 0;
    }
    if (stu->age < 0 or stu->age > 100) {
        printf("�������\n");
        ret = 0;
    }
    pos_extends += sizeof(struct stu);
    stu->pos = pos_extends;
    return ret;
}

void test_couse() {
    courses *c = new courses();
    c->readintolist();
//    c->insert();//19221101 �ߵ���ѧ�� 9.5 152
//    c->insert();//16522105 C++������� 4 64
//    printf("%p\n",c->find("�ߵ���ѧ��"));
//    printf("%p\n",c->find("16221301"));
//    c->print_list();
//    c->update("19221101");// �߼���ѧ 5 15
//    c->print_list();
//    c->sort_c();
//    c->print_list();
//    c->writetofile();

}

//
void test_sc() {
    student *sc = new student();
    sc->readintolist();
//    scoreNode scNode1{"201611701208", "19221101", 99};
//    scoreNode scNode2{"201611701209", "19221101", 100};
//    scoreNode scNode3{"201611301107", "16522105", 60};
//    scoreNode scNode4{"201611701201", "16522105", 85};
//    sc->insert(scNode1);
//    sc->insert(scNode2);
//    sc->insert(scNode3);
//    sc->insert(scNode4);
//
//    printf("sno:%s cno:%s grade:%.1f\n", "201611701201", "16522105", sc->find("201611701201", "16522105"));
//    printf("sno:%s cno:%s grade:%.1f\n", "201611701209", "19221101", sc->find("201611701209", "19221101"));
////    sc->delete_sc("201611701201", "16522105");
//    sc->update("201611701209", "19221101",70);
//    printf("sno:%s cno:%s grade:%.1f\n", "201611701209", "19221101", sc->find("201611701209", "19221101"));
    sc->print_list();
//    sc->writetofile();

//201611701209 �ߵ���ѧ��

}

void courseMenu(courses *c) {
    int choose;
    char cno[20];
    courseNode *cNode;
    while (1) {
        printf("****************��ӭ����γ̹���ϵͳ********************\n");
        printf("����������ѡ����Ӧ��ָ��\n");
        printf("1.��ӿγ���Ϣ\n");
        printf("2.���ҿγ���Ϣ\n");
        printf("3.ɾ���γ���Ϣ\n");
        printf("4.���¿γ���Ϣ\n");
        printf("5.��ӡ���пγ���Ϣ\n");
        printf("6.�˳��γ̹���ϵͳ\n");
        printf("*****************************************************\n");
        scanf("%d", &choose);
        switch (choose) {
            case 1:
                c->insert();
                break;
            case 2:
                printf("������γ̺Ż��߿γ�����:");
                scanf("%s", cno);
                cNode = c->find(cno);
                if (cNode == nullptr) {
                    printf("δ�ҵ���(%s)�γ���Ϣ��\n", cno);
                } else {
                    printf("%s\t%s\t%.1f\t%d\n", cNode->cno, cNode->cname, cNode->credit, cNode->time);
                }
                free(cNode);
                break;
            case 3:
                printf("������γ̺Ż��߿γ�����:");
                scanf("%s", cno);
                c->delete_c(cno);
                break;
            case 4:
                printf("������γ̺Ż��߿γ�����:");
                scanf("%s", cno);
                c->update(cno);
                break;
            case 5:
                c->print_list();
                break;
            case 6:
                c->writetofile();
                return;
                break;
        }
    }
}

void gradeMenu(tree *t, student *sc, courses *c) {
    int choose, flag;
    scoreNode scNode{};
    stuNode *sNode;
    courseNode *cNode;
    while (1) {
        printf("****************��ӭ����ɼ�����ϵͳ********************\n");
        printf("����������ѡ����Ӧ��ָ��\n");
        printf("1.�Ǽǳɼ�\n");
        printf("2.��ѯ�ɼ�\n");
        printf("3.�޸ĳɼ�\n");
        printf("4.ɾ���ɼ�\n");
        printf("5.��ӡ����ѧ���ɼ�\n");
        printf("6.�˳��γ̹���ϵͳ\n");
        printf("*****************************************************\n");
        scanf("%d", &choose);
        switch (choose) {
            case 1:
                printf("������ѧ�źͿγ̺�[�γ�����]���ÿո�ָ:");
                scanf("%s %s", &scNode.sno, &scNode.cno);
                sNode = t->find(root, scNode.sno);
                cNode = c->find(scNode.cno);
                if (sNode == nullptr or cNode == nullptr) {
                    printf("��ѧ�������ڻ��߿γ̲�����!\n");
                    break;
                }
                flag = 0;
                while (flag == 0) {
                    printf("������%sѧ����%s�γ̵Ŀ��Գɼ���", sNode->student->name, cNode->cname);
                    scanf("%lf", &scNode.grade);
                    if (scNode.grade < 0 or scNode.grade > 100) {
                        printf("�ɼ�����������������룡\n");
                    } else {
                        flag = 1;
                    }
                }
                strcpy(scNode.sno, sNode->student->sno);
                strcpy(scNode.cno, cNode->cno);
                sc->insert(scNode);
                break;
            case 2:
                printf("������ѧ�źͿγ̺�[�γ�����]���ÿո�ָ:");
                scanf("%s %s", &scNode.sno, &scNode.cno);

                sNode = t->find(root, scNode.sno);
                cNode = c->find(scNode.cno);
                if (sNode == nullptr or cNode == nullptr) {
                    printf("��ѧ�������ڻ��߿γ̲�����!\n");
                    break;
                } else {
                    printf("������%sѧ����%s�γ̵Ŀ��Գɼ�:%.1f��\n", sNode->student->name, cNode->cname,
                           sc->find(sNode->student->sno, cNode->cno));
                }
                break;
            case 3:
                printf("������ѧ�źͿγ̺�[�γ�����]���ÿո�ָ:");
                scanf("%s %s", &scNode.sno, &scNode.cno);

                sNode = t->find(root, scNode.sno);
                cNode = c->find(scNode.cno);
                if (sNode == nullptr or cNode == nullptr) {
                    printf("��ѧ�������ڻ��߿γ̲�����!\n");
                    break;
                } else {
                    printf("������%sѧ����%s�γ̵��¿��Գɼ���", sNode->student->name, cNode->cname);
                    scanf("%lf", &scNode.grade);
                    sc->update(sNode->student->sno, cNode->cno, scNode.grade);
                }
                break;
            case 4:
                printf("������ѧ�źͿγ̺�[�γ�����]���ÿո�ָ:");
                scanf("%s %s", &scNode.sno, &scNode.cno);

                sNode = t->find(root, scNode.sno);
                cNode = c->find(scNode.cno);//201611701209 19221101
                if (sNode == nullptr or cNode == nullptr) {
                    printf("��ѧ�������ڻ��߿γ̲�����!\n");
                    break;
                } else {
                    sc->delete_sc(sNode->student->sno, cNode->cno);
                }
                break;
            case 5://student.sno*sc*course
//                sc->print_list();
                t->print_ALL(root, sc, c);

                break;
            case 6:
                sc->writetofile();
                return;
        }
    }
}

int main() {
//    test_couse();
//    test_sc();
//    return 0;
    int choose;
    char sno[20];
    struct stu stu{};//����һ��ѧ���ṹ�����͵�������������ѧ������
    stuNode *find_node, *new_node;
    tree *t = new tree();
    courses *c = new courses();
    student *sc = new student();
    auto *fs = new files_student(root, &pos_extends);

    root = fs->readfile(t);//��ȡѧ����Ϣ�ļ�����
    c->readintolist();//�γ���Ϣ
    sc->readintolist();//�ɼ���Ϣ
    while (1) {
        printf("****************��ӭ����ѧ���ɼ�����ϵͳ************\n");
        printf("����������ѡ����Ӧ��ָ��\n");
        printf("1�����Ӳ���ѧ������Ϣ\n");
        printf("2������ѧ����Ϣ\n");
        printf("3��ģ������ѧ��\n");
        printf("4����ӡ����ѧ������Ϣ\n");
        printf("5��ɾ��ѧ������Ϣ\n");
        printf("6������ѧ������Ϣ\n");
        printf("7���༭�α���Ϣ\n");
        printf("8���༭�ɼ���Ϣ\n");
        printf("9���˳�ѧ����Ϣ����ϵͳ\n");
        printf("*****************************************************\n");

        scanf("%d", &choose);
        switch (choose) {
            case 1:
                if (input_student(&stu)) {//��ȡһ��ѧ����Ϣ
                    new_node = t->createStuNode(&stu);
                    if ((find_node = t->find(root, stu.sno)) == nullptr) {
                        t->writeToFile(&stu);
                    }
                    root = t->insert(root, new_node, find_node);
                }
                break;
            case 2:
                printf("������ѧ����ѧ��������ѧ����Ϣ\n");
                scanf("%s", &sno);

                find_node = t->find(root, sno);

                if (find_node == nullptr) {
                    printf("�Ҳ�����ѧ������Ϣ\n");
                    break;
                } else {
                    printf("ѧ�ţ�%s ѧ��������%s �Ա�%s ���䣺%d ������%s רҵ��%s\n",
                           find_node->student->sno, find_node->student->name, find_node->student->sex,
                           find_node->student->age, find_node->student->region,
                           find_node->student->pro);
                }
                break;
            case 3:
                printf("��������Ϣ��\n");
                char s[1024];
                scanf("%s", &s);
                fs->findfromfile(0, s);
                break;
            case 4:
                printf("���е�ѧ������ϢΪ\n");
                t->print(root);
                break;
            case 5:
                printf("������ѧ����ѧ����ɾ��ѧ����Ϣ\n");
                scanf("%s", &sno);
                if (fs->deletetofile(t, sno, root)) {
                    root = t->remove(root, sno);
                }
                break;
            case 6:
                printf("��������º��ѧ����Ϣ����ѧ����Ϊ�ؼ���\nѧ�� ���� �Ա� ���� ���� רҵ\n");
                scanf("%s %s %s %d %s %s",
                      &stu.sno, &stu.name, &stu.sex, &stu.age, &stu.region, &stu.pro);

                t->update(root, &stu, 1);
                break;
            case 7:
                courseMenu(c);
                break;
            case 8:
                gradeMenu(t, sc, c);
                break;
            case 9:
                t->writeToFileALL(root);
                c->writetofile();
                sc->writetofile();
                return 0;
        }
    }
}

#pragma clang diagnostic pop