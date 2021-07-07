//
// Created by ��Դ�� on 2021/6/26.
//

#include "files.h"

stuNode *files_student::readfile(tree *t) {
    FILE *fp;
    int stuAmount;
    stu *s = (struct stu *) malloc(sizeof(struct stu));
    stuNode *new_node;
    if ((fp = fopen("student.txt", "r")) == nullptr)   //�ж��Ƿ���ļ�
    {
        if ((fp = fopen("student.txt", "w")) == nullptr) {
            printf("student.txt ��Ϣ����ʧ��,�˳�����!\n");
            exit(0);
        }
    }
    fseek(fp, 0, SEEK_END);   //�ļ�λ��ָ���ƶ����ļ�ĩβ��
    if (ftell(fp) > 0) //�ļ���Ϊ�ա�
    {
        rewind(fp);  //�ļ�λ��ָ���ƶ����ļ���ʼλ�á�
        for (stuAmount = 0; !feof(fp) && fread(s, sizeof(struct stu), 1, fp); stuAmount++) {//�ļ�����
            s->pos = (int) (stuAmount * sizeof(struct stu));
            *pos_extends = s->pos;
            new_node = t->createStuNode(s);
//            printf("sno:%s,pos:%d\n", s->sno, s->pos);
            root = t->insert(root, new_node);
        }
        printf("��ȡ��%d��ѧ����Ϣ\n", stuAmount);
    }
    free(s);
    fflush(fp);
//    fsync(fileno(fp));
    _commit(_fileno(fp));//��ȡ�ļ���������ǿ��дӲ��
    fclose(fp);
    return root;
}


void files_student::findfromfile(int count, char *message) {//����Ѱ���ļ���Ϣ������sno���ٴ��ݸ�find
    FILE *fp;
    if ((fp = fopen("student.txt", "r")) == nullptr) {
        return;
    }
    int stuAmount;
    stu *s = (struct stu *) malloc(sizeof(struct stu));
    fseek(fp, 0, SEEK_END);   //�ļ�λ��ָ���ƶ����ļ�ĩβ��
    if (ftell(fp) > 0) //�ļ���Ϊ�ա�
    {
        rewind(fp);  //�ļ�λ��ָ���ƶ����ļ���ʼλ�á�
        char *find;
        for (stuAmount = 0; !feof(fp) && fread(s, sizeof(struct stu), 1, fp);) {//��Ϣ��ȡ
            if (strstr(s->sno, message) or strstr(s->name, message) or strstr(s->sex, message) or
                (s->age == atoi(message)) or strstr(s->region, message) or strstr(s->pro, message)) {
                printf("ѧ�ţ�%s ѧ��������%s �Ա�%s ���䣺%d ������%s רҵ��%s\n",
                       s->sno, s->name, s->sex, s->age, s->region, s->pro);
                stuAmount++;
            }
            if (count != 0 && stuAmount > count) {
                break;
            }
        }
    }
    printf("��ȡ��%d��ѧ����Ϣ\n", stuAmount);
    free(s);
    fflush(fp);
//    fsync(fileno(fp));
    _commit(_fileno(fp));//��ȡ�ļ���������ǿ��дӲ��
    fclose(fp);
}

void files_student::pos_stuNode(stuNode *s) {
    if (s->lchild != nullptr) {
        pos_stuNode(s->lchild);
    }
    s->student->pos -= sizeof(struct stu);
    if (s->rchild != nullptr) {
        pos_stuNode(s->rchild);
    }
}

int files_student::deletetofile(tree *t, char *sno, stuNode *root) {
    FILE *fp;
    int pos;
    this->root = root;
    stuNode *sno_exists = t->find(root, sno);
    if (sno_exists == nullptr) {
        printf("δ���ҵ���ѧ����Ϣ��\n");
        return 0;
    }

    pos = sno_exists->student->pos;
    char *front = (char *) malloc(sizeof(char) * pos);
    if ((fp = fopen("student.txt", "r")) == nullptr) {
        printf("�ļ������쳣��\n");
        return 0;
    }
    fseek(fp, 0, SEEK_END); //�ļ�λ��ָ���ƶ����ļ�����λ��
    unsigned int backlen = ftell(fp) - pos - sizeof(struct stu);
    char *back = (char *) malloc(sizeof(char) * backlen);
    fseek(fp, 0, SEEK_SET);
    fread(front, pos, 1, fp);//front buf
    //��ȡ���ý�㴦
    fseek(fp, sizeof(struct stu), SEEK_CUR);//ƫ��һ��ѧ������
    fread(back, backlen, 1, fp);//��ȡ��ɾ�����ĺ�����Ϣ
    fflush(fp);
//    fsync(fileno(fp));
    _commit(_fileno(fp));//��ȡ�ļ���������ǿ��дӲ��
    fclose(fp);

    if ((fp = fopen("student.txt", "w")) == nullptr) {//�����ļ�
        printf("�ļ������쳣��\n");
        return 0;
    }
    fseek(fp, 0, SEEK_SET);
    fwrite(front, pos, 1, fp);
    fwrite(back, backlen, 1, fp);

    //���ӽ��ƫ���޸�
    pos_stuNode(sno_exists);
    free(front);
    free(back);
    fflush(fp);
//    fsync(fileno(fp));
    _commit(_fileno(fp));//��ȡ�ļ���������ǿ��дӲ��
    fclose(fp);
    return 1;
}
