//
// Created by ��Դ�� on 2021/6/21.
//
#include "tree.h"


#define MAX(A, B) ((A)>(B)?(A):(B))


int tree::height(stuNode *root1) {//tree height
    if (root1 == nullptr) {
        return 0;
    }
    return (MAX(height(root1->lchild), height(root1->rchild))) + 1;
}

stuNode *tree::tree_node_LL(stuNode *root1) {
    stuNode *tmp;
    tmp = root1->lchild;
    root1->lchild = tmp->rchild;
    tmp->rchild = root1;

    tmp->height = height(tmp);
    root1->height = height(root1);

    return tmp;
}

stuNode *tree::tree_node_RR(stuNode *root1) {
    stuNode *tmp;
    tmp = root1->rchild;
    root1->rchild = tmp->lchild;
    tmp->lchild = root1;

    tmp->height = height(tmp);
    root1->height = height(root1);

    return tmp;
}

stuNode *tree::tree_node_LR(stuNode *root1) {//R->L
    root1->lchild = tree_node_RR(root1->lchild);
    root1 = tree_node_LL(root1);
    return root1;
}

stuNode *tree::tree_node_RL(stuNode *root1) {//L->R
    root1->rchild = tree_node_LL(root1->rchild);
    root1 = tree_node_RR(root1);
    return root1;
}

stuNode *tree::createStuNode(struct stu *student) {
    stuNode *node;
    stu *stu = (struct stu *) malloc(sizeof(struct stu));
    stu = (struct stu *) memcpy(stu, student, sizeof(struct stu));
    node = (stuNode *) (malloc(sizeof(stuNode)));
    if (node == nullptr) {
        printf("δ�����뵽���������\n");
        return nullptr;
    } else {
        node->rchild = nullptr;
        node->lchild = nullptr;
        node->student = stu;
    }
    return node;
}

stuNode *tree::insert(stuNode *root1, stuNode *stu) {
    int x;
    if (root1 == nullptr) {
        root1 = stu;
    } else {
        stuNode *e = find(root1, stu->student->sno);
        if (e != nullptr) {
            printf("��������ͬ��ѧ�ţ��ܾ����룡\n");
            return root1;
        } else {
            x = strcmp(stu->student->sno, root1->student->sno);
            //<0 ����Ԫ��С�ڸ����Ԫ��
            //>0 ����Ԫ�ش��ڸ����Ԫ��
            if (x < 0) {//Ԫ��С�ڸ����,�������
                root1->lchild = insert(root1->lchild, stu);

                if (height(root1->lchild) - height(root1->rchild) == 2) {//��ƽ��
                    if (x < 0) {//������ת
                        root1 = tree_node_LL(root1);
                    } else {//������ת
                        root1 = tree_node_LR(root1);
                    }
                }

            } else if (x > 0) {//Ԫ�ش��ڸ���㣬�����ұ�
                root1->rchild = insert(root1->rchild, stu);

                if (height(root1->rchild) - height(root1->lchild) == 2) {//��ƽ��
                    if (x > 0) {//������ת
                        root1 = tree_node_RR(root1);
                    } else {//������ת
                        root1 = tree_node_RL(root1);
                    }
                }
            }
        }
    }
    root1->height = height(root1);
    return root1;
}

stuNode *tree::insert(stuNode *root1, stuNode *stu, stuNode *e) {
    int x;
    if (root1 == nullptr) {
        root1 = stu;
    } else {
        if (e != nullptr) {
            printf("��������ͬ��ѧ�ţ��ܾ����룡\n");
            return root1;
        } else {
            x = strcmp(stu->student->sno, root1->student->sno);

            if (x < 0) {//Ԫ��С�ڸ����,�������
                root1->lchild = insert(root1->lchild, stu);

                if (height(root1->lchild) - height(root1->rchild) == 2) {//��ƽ��
                    if (x < 0) {//������ת
                        root1 = tree_node_LL(root1);
                    } else {//������ת
                        root1 = tree_node_LR(root1);
                    }
                }

            } else if (x > 0) {//Ԫ�ش��ڸ���㣬�����ұ�
                root1->rchild = insert(root1->rchild, stu);

                if (height(root1->rchild) - height(root1->lchild) == 2) {//��ƽ��
                    if (x > 0) {//������ת
                        root1 = tree_node_RR(root1);
                    } else {//������ת
                        root1 = tree_node_RL(root1);
                    }
                }
            }
        }
    }
    root1->height = height(root1);
    return root1;
}

stuNode *tree::find(stuNode *root1, char *sno) {//������ѯѧ����Ϣ
    if (root1 == nullptr) {
        return nullptr;
    }
    int x = strcmp(root1->student->sno, sno);//0 ��� ѧ�Ŵ� <0������ >0
    if (x > 0) {
        return find(root1->lchild, sno);
    } else if (x < 0) {
        return find(root1->rchild, sno);
    }
    return root1;
}

void tree::print_ALL(stuNode *root1, student *sc, courses *c) {
    if (root1 == nullptr) {
        return;
    }
    double grade;
    print_ALL(root1->lchild, sc, c);
    char **cnames = (char **) malloc(20 * sizeof(char *));
    char **cnos = c->getCnos(cnames);
    if (cnos != nullptr) {
        printf("ѧ�ţ�%s ѧ��������%s �Ա�%s ���䣺%d ������%s רҵ��%s",
               root1->student->sno, root1->student->name, root1->student->sex, root1->student->age,
               root1->student->region, root1->student->pro);
        for (int i = 0; cnos[i] != nullptr; i++) {
            grade = sc->find(root1->student->sno, cnos[i]);
            if (grade != -1) {
                printf(" %s:%.1f", cnames[i], grade);
            }
        }
    }
    printf("\n");
    free(cnos);
    free(cnames);
    print_ALL(root1->rchild, sc, c);
}

void tree::print(stuNode *root1) {
    if (root1 == nullptr) {
        return;
    }
    print(root1->lchild);
    printf("ѧ�ţ�%s ѧ��������%s �Ա�%s ���䣺%d ������%s רҵ��%s\n",
           root1->student->sno, root1->student->name, root1->student->sex, root1->student->age,
           root1->student->region, root1->student->pro);
    print(root1->rchild);
}

void tree::writeToFile(struct stu *stu) {
    FILE *fp;
    if ((fp = fopen("student.txt", "a")) != nullptr)//׷����Ϣ
    {
        if (fwrite(stu, sizeof(struct stu), 1, fp) != 1) {
            printf("д���ļ�����\n");
        }
        fflush(fp);
//        fsync(fileno(fp));
        _commit(_fileno(fp));//��ȡ�ļ���������ǿ��дӲ��
        fclose(fp);
    }
}

void tree::writeToFileALL(stuNode *root1) {
    FILE *fp;
    fp = fopen("student.txt", "w");
    fflush(fp);
//    fsync(fileno(fp));
    _commit(_fileno(fp));//��ȡ�ļ���������ǿ��дӲ��
    fclose(fp);
    print(root1, 1);
}

void tree::print(stuNode *root1, int writeTo) {
    if (root1 == nullptr) {
        return;
    }
    print(root1->lchild, writeTo);
    if (writeTo == 0) {
        printf("ѧ�ţ�%s,ѧ��������%s,�Ա�%s,���䣺%d��������%s��רҵ��%s ƫ����:%d\n",
               root1->student->sno, root1->student->name, root1->student->sex, root1->student->age,
               root1->student->region, root1->student->pro, root1->student->pos);
    } else {
        writeToFile(root1->student);
    }
    print(root1->rchild, writeTo);
}

stuNode *tree::remove(stuNode *root1, char *sno) {//ɾ��ѧ����Ϣ
    stuNode *tmp;

    if (root1 == nullptr) {
        return nullptr;
    }

    int x = strcmp(root1->student->sno, sno);//0 ��� ѧ�Ŵ� <0������ >0
    if (x == 0) {
        if (root1->lchild == nullptr && root1->rchild == nullptr) {
            free(root1->student);
            free(root1);
            return nullptr;
        } else if (root1->lchild != nullptr) {//�����������
            for (tmp = root1->lchild; tmp->rchild != nullptr; tmp = tmp->rchild);//��tmp����¼root�����������е����ұߵĽڵ㣨Ҳ�����������е����ֵ��
//            struct stu *swap =(struct stu *)malloc(sizeof(struct stu));
//            swap = (struct stu *) memcpy(swap, tmp->student, sizeof(struct stu));//�������
            struct stu *swap = tmp->student;
            tmp->student = root1->student;
            root1->student = swap;
            root1->lchild = remove(root1->lchild, sno);//�ݹ��ɾ�����ظ�����������ڵ�,�������������ݸ��½���
        } else {//���ֻ��������
            for (tmp = root1->rchild; tmp->lchild != nullptr; tmp = tmp->lchild);//��tmp����¼root���������е�����ߵĽڵ㣨Ҳ�����������е���Сֵ��
//            struct stu *swap =(struct stu *)malloc(sizeof(struct stu));
//            swap = (struct stu *) memcpy(swap, tmp->student, sizeof(struct stu));//�������
            struct stu *swap = tmp->student;
            tmp->student = root1->student;
            root1->student = swap;
            root1->rchild = remove(root1->lchild, sno);//�ݹ��ɾ�����ظ�����������ڵ�,�������������ݸ��½���
        }
    } else if (x > 0) {//���ɾ�������ݱ�����ڵ�ҪС������������ȥɾ���ڵ�
        root1->lchild = remove(root1->lchild, sno);
    } else if (x < 0) {//���ɾ�������ݱ�����ڵ�Ҫ����������ұ�ȥɾ��
        root1->rchild = remove(root1->rchild, sno);
    }

    //�����½ڵ���������ж��Ƿ���ֲ�ƽ��


    int h = height(root1->lchild) - height(root1->rchild);
    x = strcmp(root1->student->sno, sno);
    if (h == 2)//��ƽ��
    {
        //�����������ݱȸ��������ڵ������ҪС�������϶��ǲ��뵽root->lchild�����ȥ������������ƽ��

        if (x > 0)//����ƽ��
        {
            root1 = tree_node_LL(root1);
        } else//�������ǲ��뵽root->lchild���ұ�ȥ�����������Ҳ�ƽ��
        {
            root1 = tree_node_LR(root1);
        }
    } else if (h == -2)//�Ҳ�ƽ��
    {

        if (x <= 0)//���Ҳ�ƽ��
        {
            //printf("�����Ҳ�ƽ��\n");
            root1 = tree_node_RR(root1);
        } else//����ƽ��
        {
            root1 = tree_node_RL(root1);
        }
    }
    root1->height = height(root1);
    return root1;//�����ǰroot����ڵ㲻������ɾ���Ľڵ㣬���Ǳ�ԭ�ⲻ���ķ��س�ȥ
}

void tree::update(stuNode *root1, stu *stu, int isUpdate) {
    stuNode *find_node = find(root1, stu->sno);
    if (find_node == nullptr) {
        printf("����ѡ���ѧ����Ϣ�����ڣ�");
        return;
    }

    struct stu *s = find_node->student;
    strcpy(s->name, stu->name);
    strcpy(s->pro, stu->pro);
    strcpy(s->region, stu->region);
    s->age = stu->age;
    strcpy(s->sex, stu->sex);
    if (isUpdate) {
        int frontlen;
        FILE *fp;
        frontlen = find_node->student->pos;
        char *front = (char *) malloc(sizeof(char) * frontlen);
        if ((fp = fopen("student.txt", "r")) == nullptr) {
            printf("�ļ������쳣��\n");
            return;
        }
        fseek(fp, 0, SEEK_END); //�ļ�λ��ָ���ƶ����ļ�����λ��
        unsigned int backlen = ftell(fp) - frontlen - sizeof(struct stu);
        char *back = (char *) malloc(sizeof(char) * backlen);
        fseek(fp, 0, SEEK_SET);
        fread(front, frontlen, 1, fp);//front buf
        //��ȡ���ý�㴦
        fseek(fp, sizeof(struct stu), SEEK_CUR);//ƫ��һ��ѧ������
        fread(back, backlen, 1, fp);//��ȡҪ���½��ĺ�����Ϣ
        fflush(fp);
//        fsync(fileno(fp));
        _commit(_fileno(fp));//��ȡ�ļ���������ǿ��дӲ��
        fclose(fp);
        if (front[0] != 0 or back[0] != 0) {
            if ((fp = fopen("student.txt", "w")) == nullptr) {//�����ļ�
                printf("�ļ������쳣��\n");
                return;
            }
            fseek(fp, 0, SEEK_SET);

            fwrite(front, frontlen, 1, fp);
            fwrite(stu, sizeof(struct stu), 1, fp);
            fwrite(back, backlen, 1, fp);

            free(front);
            free(back);
            fflush(fp);
//            fsync(fileno(fp));
            _commit(_fileno(fp));//��ȡ�ļ���������ǿ��дӲ��
            fclose(fp);
        }
        return;
    }
}
