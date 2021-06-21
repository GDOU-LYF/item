#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdlib>

using namespace std;
/*���˵�
1.��ѯ(���������ѯ��ģ����ѯ��ͳ�������ѯ������������������ʾ���) 
2.���ѧ����Ϣ(ѧ�Ų��أ��ȶ�12��ѧ���ַ����Ա�������ȷ�ַ��ȶ�) 
3.ɾ��ѧ����Ϣ() 
4. ����ѧ����Ϣ
5.�˳� 
*/
//ѧ��	����	�Ա�	����	����	רҵ 
class Student {
public:
    char id[20];
    char name[20];
    char sex[8];
    char age[4];
    char pro[20];
    char major[20];
};

//�����ṹ 
class Index {
public:
    char key[20];//�ؼ���
    int pos;//ƫ��λ��
};

//������
struct tree {
    Index data;
    tree *left, *right;
};


//���� 
void createbitree(Index index, tree *&p) {
    if (!p) {        //�����Ϊ��
        p = new tree;
        p->data = index;
        p->left = NULL;
        p->right = NULL;
    } else if (strcmp(index.key, p->data.key) < 0) {
        //�²�����ѧ�űȸ����ѧ��С
        //�²�����ѧ�űȸ����ѧ��С
        createbitree(index, p->left);
    } else if (strcmp(index.key, p->data.key) > 0) {
        //�²�����ѧ�űȸ����ѧ��С��
        createbitree(index, p->right);
    } else {
        //����ͬѧ��
        cout << "error" << endl;
        exit(0);
    }
}

//������
Index createIndex(Student stu, Index elems, int indexcount) {
    memcpy(elems.key, stu.id, 20);//���ı��е�ѧ����Ϣ��ֵ�������еĹؼ���
    elems.pos = indexcount * 92;///����Ϣ��ƫ��λ�ø�ֵ�������е�ƫ����
    return elems;
}

//����������
Index InsertIndex(Student stu, Index elems) {
    fstream file("E:/mycode/student.txt");
    if (!file) {
        cout << "���ļ�ʧ��" << endl;
        exit(0);
    }
    file.seekg(0, ios::end);  //ָ�뵽β
    memcpy(elems.key, stu.id, 20);
    elems.pos = file.tellg();
    return elems;
}


//ɾ����������� 
void delIndex(tree *&t, char id[20]) {
    {
        tree *f, *q, *s, *p;
        p = t;
        f = NULL;
        //���ҹؼ���Ϊk�Ľ�㣬ͬʱ���˽���˫���ҳ���
        while (p && strcmp(id, p->data.key)) {
            f = p; //f��¼�����
            if (strcmp(id, p->data.key) < 0)
                p = p->left;
            else
                p = p->right;
        }
        if (!p)//�Ҳ�����ɾ�����ʱ����
            return;
        if (p->left == NULL) //��ɾ������������Ϊ��
        {
            if (f == NULL)//��ɾ�����Ϊ�����
                t = p->right;
            else if (f->left == p)//��ɾ���������˫�׽�����ڵ�
                f->left = p->right;
            else                //��ɾ���������˫�׽����ҽ��
                f->right = p->right;
            delete p;
        } else //��ɾ�������������
        {
            q = p;
            s = p->left;
            while (s->right) //�ڴ�ɾ�������������в��������½��,�����Ҵ�ɾ����������ǰ�����
            {
                q = s;
                s = s->right;
            }
            if (q == p)
                q->left = s->left;
            else
                q->right = s->left;
            // memcpy(p->data.key,s->data.key,20);
            p->data = s->data;
            delete s;
        }
    }
}

//�޸�ƫ��ֵ
tree *updateIndex(tree *&t, tree *c, int &pos, char id[20]) {
    if (t == 0) {
        cout << "return 0" << endl;
        return 0;
    }
    if (strcmp(id, t->data.key) < 0 && t->data.pos > pos) {
        c->data.pos = t->data.pos - 92;//ƫ��ֵ��ǰ�ƶ�һ��ѧ����Ϣ����
        updateIndex(t->left, c->left, pos, id);
    }

    if (strcmp(id, t->data.key) > 0 && t->data.pos > pos) {
        c->data.pos = t->data.pos - 92;//ƫ��ֵ��ǰ�ƶ�һ��ѧ����Ϣ����
        updateIndex(t->right, c->right, pos, id);
    }
    return c;
}

//�ؽ���,��ʱ��ռ� 
tree *updateIndex() {
    Student stu;
    tree *root;
    root = NULL;
    Index index;
    Index newindex;
    int count = 0;
    int indexcount = 0;
    fstream file("E:/mycode/student.txt");
    if (!file) {
        cout << "���ļ�ʧ��" << endl;
        exit(0);
    }
    file.seekg(0, ios::end);  //ָ�뵽β
    count = file.tellg() / sizeof(stu);
    file.seekg(0);//ָ��ص�ͷ

    for (int i = 0; i < count; i++) {
        file.read((char *) &stu, sizeof(stu));

        newindex = createIndex(stu, index, indexcount);
        indexcount++;
        createbitree(newindex, root);
    }
    return root;
    file.close();
}


void lookMenu() {
    //��ѯ�˵�
    cout << "	  ��ѡ���ܼ�1-5" << endl;
    cout << "	  1.��ѯ����" << endl;
    cout << "	  2.ѧ�Ų�ѯ" << endl;
    cout << "	  3.������ѯ" << endl;
    cout << "	  4.ģ����ѯ" << endl;
    cout << "	  5.����" << endl;
    cout << "    ------������ѡ��(1-5)------" << endl;
}

void conditionMenu() {
    //������ѯ�˵�
    cout << "1.����" << endl;
    cout << "2.�Ա�" << endl;
    cout << "3.����" << endl;
    cout << "4.����" << endl;
    cout << "5.רҵ" << endl;
    cout << "" << endl;
    cout << "" << endl;
}

//��������ѯ
void twocondition(int one, int two) {
    Student stu;
    int count;
    int flag = 0;
    int i;
    char id[20];
    char name[20];
    char sex[8];
    char age[4];
    char pro[20];
    char major[20];
    fstream file("E:/mycode/student.txt");
    if (!file) {
        cout << "���ļ�ʧ��" << endl;
        exit(0);
    }
    file.seekg(0, ios::end);  //ָ�뵽β

    count = file.tellg() / sizeof(stu);

    file.seekg(0);//ָ��ص�ͷ


    if (one == 2 && two == 5) {

        cout << "�������Ա�" << endl;
        cin >> sex;
        cout << "������רҵ" << endl;
        cin >> major;
        cout << "ѧ��" << "\t\t" << "����" << "\t" << " " << "�Ա�" << "\t" << "����" << "\t" << "����" << "\t\t" << "רҵ" << "\n";
        cout << "\n";

        for (i = 0; i < count; i++) {
            file.read((char *) &stu, sizeof(stu)); //��������ѯ ��ȫ�����ϲ������ʾ
            if (strcmp(sex, stu.sex) == 0 && strcmp(major, stu.major) == 0) {
                cout << stu.id << "\t";
                cout << stu.name << "\t" << " ";
                cout << stu.sex << "\t";
                cout << stu.age << "\t";
                cout << stu.pro << "\t";
                cout << stu.major << "\t";
                cout << "" << endl;
                flag++;
            }
        }
        cout << "\n";
        cout << "\n";
        cout << "\n";
        cout << "\t\t\t\t\t\t��¼��" << flag << " ��" << endl;
        file.close();
    } else if (one == 2 && two == 4) {

        cout << "�������Ա�" << endl;
        cin >> sex;
        cout << "�����뼮��" << endl;
        cin >> pro;
        cout << "ѧ��" << "\t\t" << "����" << "\t" << " " << "�Ա�" << "\t" << "����" << "\t" << "����" << "\t\t" << "רҵ" << "\n";
        cout << "\n";

        for (i = 0; i < count; i++) {
            file.read((char *) &stu, sizeof(stu));
            if (strcmp(sex, stu.sex) == 0 && strcmp(major, stu.major) == 0) {
                cout << stu.id << "\t";
                cout << stu.name << "\t" << " ";
                cout << stu.sex << "\t";
                cout << stu.age << "\t";
                cout << stu.pro << "\t";
                cout << stu.major << "\t";
                cout << "" << endl;
                flag++;
            }

        }
        cout << "\n";
        cout << "\n";
        cout << "\n";
        cout << "\t\t\t\t\t\t��¼��" << flag << " ��" << endl;
        file.close();
    } else {
        cout << "�ù�����δ����" << endl;
        cout << "" << endl;
    }


}

//����ѧ�� 
void search(char id[20], tree *&t, int &pos) {
//�ݹ���� 
    if (t == 0) {
        return;    //û�ҵ� �����˳��ݹ�
    }
    if (strcmp(id, t->data.key) < 0) {
        search(id, t->left, pos);
    } else if (strcmp(id, t->data.key) > 0) {
        search(id, t->right, pos);
    } else {
        pos = t->data.pos;//����ƫ��ֵ���Կ��ٶ�λ
        return;
    }


}

//ģ����ѯ
void find() {
    char text[20];
    system("cls");
    cout << "�������������" << endl;
    cin >> text;
    int length = 0;
    int i;
    int flag = 0;
    Student stu;
    for (i = 0; i <= 20; i++) {
        if (text[i]) {
            length++;
        } else {
            break;
        }
    }
    bool isNum = false;
    int carrybit;//ָ���ƶ���λ
    for (i = 0; i < length; i++) {
        if (text[i] >= '0' && text[i] <= '9') {//�ж��Ƿ�Ϊ����
            carrybit = 1;
            isNum = true;
        } else {
            carrybit = 2;
            isNum = false;
            break;
        }
    }
    bool isFind = false;
    char temp[length];
    cout << "\n";
    cout << "ѧ��" << "\t\t" << "����" << "\t" << " " << "�Ա�" << "\t" << "����" << "\t" << "����" << "\t\t" << "רҵ" << "\n";
    int count;
    cout << "\n";
    ifstream file("E:/mycode/student.txt");
    if (!file) {
        cout << "���ļ�ʧ��" << endl;
        exit(0);
    }
    file.seekg(0, ios::end);  //ָ�뵽β
    count = file.tellg() / 92;//����ѧ����¼��
    for (i = 0; i < count; i++) {    //ѭ����ȡ�����ı�����
        isFind = false;
        //j=0ʱΪ��ѯ���У�j=20Ϊ����ѧ��
        for (int j = 20; j < 92; j = j + carrybit) {
            file.seekg(i * 92);    //���ı�ͷ��ʼ�ƶ�һ��ѧ����Ϣ����
            file.seekg(j, ios::cur);//��ǰλ�ú���j����λ  ����������Ϊ���� carrybit=1
            //�Ǻ�����carrybit=2
            file.read((char *) &temp, length);//��ȡ�ı����������ݵĳ��ȵ���Ϣ
            if (temp[0] == text[0]) {    //�Ƚ������������ȡ���������Ƿ���ͬ
                for (int k = 0; k < length; k++) {
                    if (temp[k] == text[k]) {
                        isFind = true;
                    } else {
                        isFind = false;
                        break;
                    }
                }
                if (isFind == true) {
                    break;
                }
            }
        }
        //�ص�ͷ
        file.seekg(i * 92, ios::beg);
        if (isFind == true) {
            file.read((char *) &stu, 92);
            cout << stu.id << "\t";
            cout << stu.name << "\t" << " ";
            cout << stu.sex << "\t";
            cout << stu.age << "\t";
            cout << stu.pro << "\t";
            cout << stu.major << "";
            cout << "" << endl;
            flag++;//��¼��
        }
    }
    cout << "\n";
    cout << "\n";
    cout << "\n";
    cout << "\t\t\t\t\t\t��¼��" << flag << " ��" << endl;
    file.close();
}


//������
void print(tree *&t) {
    if (t) {

        print(t->left);
//	cout<<t->data<<" ";
        cout << t->data.key << endl;
        cout << t->data.pos << endl;
        print(t->right);
    }
}

int Menu() {
    //�˵�
    int n;//switch�ж�
    cout << "***************************************************" << endl;
    cout << "**********				***********" << endl;
    cout << "**********	ѧ����Ϣ����ϵͳ	***********" << endl;
    cout << "**********				***********" << endl;
    cout << "***************************************************" << endl;
    cout << "" << endl;
    cout << "	  ��ѡ���ܼ�1-5" << endl;
    cout << "	  1.��ѯѧ����Ϣ" << endl;
    cout << "	  2.���ѧ����Ϣ" << endl;
    cout << "	  3.ɾ��ѧ����Ϣ" << endl;
    cout << "	  4.����ѧ����Ϣ" << endl;
    cout << "	  5.�˳�" << endl;
    cout << "" << endl;
    cout << "    ------������ѡ��(1-5)------" << endl;
    cin >> n;
    if (!cin >> n) {
        cout << "�������" << endl; //�������ʹ����˳�
        cin.clear();//��������ǣ����´������������������������ɱ�����֮ǰ�Ĳ�ƥ�������
        cin.sync();//���cin�����������ݡ�
    } else {
        return n;
    }
}

//��ѯѧ����Ϣ
int look(tree *&t) {
    Student stu;
    int choose;
    int count = 0;
    while (true) {

        lookMenu();
        cin >> choose;
        if (!cin >> choose) {
            cout << "�������" << endl; //����
            cin.clear();//��������ǣ����´������������������������ɱ�����֮ǰ�Ĳ�ƥ�������
            cin.sync();//���cin�����������ݡ�
        }
        switch (choose) {
            case 1://��ѯ ����
            {
                fstream file("E:/mycode/student.txt");
                if (!file) {
                    cout << "���ļ�ʧ��" << endl;
                    exit(0);
                }
                system("cls");
                cout << "\n";
                cout << "ѧ��" << "\t\t" << "����" << "\t" << " " << "�Ա�" << "\t" << "����" << "\t" << "����" << "\t\t" << "רҵ"
                     << "\n";
                cout << "\n";
                file.seekg(0, ios::end);  //ָ�뵽β
                count = file.tellg() / sizeof(stu);    //���㳤��
                file.seekg(0);//ָ��ص�ͷ
                for (int i = 0; i < count; i++) {
                    file.read((char *) &stu, sizeof(stu));
                    cout << stu.id << "\t";
                    cout << stu.name << "\t" << " ";
                    cout << stu.sex << "\t";
                    cout << stu.age << "\t";
                    cout << stu.pro << "\t";
                    cout << stu.major << "";
                    cout << "" << endl;
                }
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\t\t\t\t\t\t��¼��" << count << " ��" << endl;
                file.close();
                cout << "" << endl;
                break;
            }
            case 2: {
                tree *p;
                fstream file("E:/mycode/student.txt");
                if (!file) {
                    cout << "���ļ�ʧ��" << endl;
                    exit(0);
                }
                int pos = -1;
                cout << "������ѧ��ѧ��" << endl;
                cin >> stu.id;
                search(stu.id, t, pos);
                file.seekg(pos);
                if (pos >= 0) {
                    system("cls");
                    cout << "ѧ��" << "\t\t" << "����" << "\t" << " " << "�Ա�" << "\t" << "����" << "\t" << "����" << "\t\t"
                         << "רҵ" << "\n";
                    cout << "\n";
                    file.read((char *) &stu, sizeof(stu));
                    cout << stu.id << "\t";
                    cout << stu.name << "\t" << " ";
                    cout << stu.sex << "\t";
                    cout << stu.age << "\t";
                    cout << stu.pro << "\t";
                    cout << stu.major << "\t";
                    cout << "" << endl;
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                } else {
                    system("cls");
                    cout << "�Ҳ�����ѧ����Ϣ" << endl;
                    cout << "" << endl;
                }
                file.close();
            }
                break;
            case 3://ģ����ѯ
            {
                int i;
                fstream file("E:/mycode/student.txt");
                if (!file) {
                    cout << "���ļ�ʧ��" << endl;
                    exit(0);
                }
                system("cls");
                conditionMenu();//�����˵�

                int flag = 0;
                char name[20];
                char sex[8];
                char age[4];
                char pro[20];
                char major[20];
                int con;
                int onecon;
                int twocon1;
                int twocon2;
                system("cls");
                cout << "��ѡ���ѯ��������" << endl;
                cin >> con;
                if (con == 2) {
                    conditionMenu();
                    cout << "��ѡ����������������ѯ" << endl;
                    cout << "�������һ���������" << endl;
                    cin >> twocon1;
                    cout << "������ڶ����������" << endl;
                    cin >> twocon2;
                    twocondition(twocon1, twocon2);
                } else if (con == 1) {
                    cout << "ģ����ѯ�������ѧ����ĵ�������ѯ��������ѡ��" << endl;
                    cout << "" << endl;
                    cout << "" << endl;
                } else {
                    cout << "�ù�����δ����" << endl;
                    cout << "" << endl;
                    cout << "" << endl;
                }


            }
                break;
            case 4:
                find();
                break;
            case 5://����
            {
                cout << "�Ƿ񷵻��ϼ��˵�?(y/n)" << endl;
                char x;
                cin >> x;
                if (x == 'y' || x == 'Y') {
                    system("cls");
                    return 0;
                } else if (x == 'n' || x == 'N') {
                    system("cls");
                    break;
                } else {
                    system("cls");
                    cout << "�������" << endl;

                }
                default:
                    cout << "�޴˹���" << endl;
                break;
            }
        }
    }
}


//���ѧ����Ϣ
void add(tree *&t) {
    Student stu;
    Index elems;
    Index newindex;
    int i;
    int pos = -1;
    int flag;
    int length;
    fstream file("E:/mycode/student.txt", ios::app);
    if (!file) {
        cout << "���ļ�ʧ��" << endl;
        exit(0);
    }
    memset(&stu, '\0', sizeof(stu));//�����뻺��
    cout << "������ѧ��ѧ��" << endl;
    do {
        flag = 0;
        length = 0;
        cin >> stu.id;
        for (i = 0; i < sizeof(stu.id); i++) {
            if (stu.id[i]) {
                length++;//��¼�������ݵĳ���
            } else {
                break;
            }
        }
        for (i = 0; i < length; i++) {//�ж��Ƿ�Ϊ����
            if ((stu.id[i] >= 'a' && stu.id[i] <= 'z') || (stu.id[i] >= 'A' && stu.id[i] <= 'Z')) {
                flag++;
            }
        }
        //�ж������Ƿ�Ϸ�
        if (length != 12 || flag > 0) {
            cout << "�����볤��Ϊ12������ѧ��" << endl;
            cin.clear();//��������ǣ����´������������������������ɱ�����֮ǰ�Ĳ�ƥ�������
            cin.sync();//���cin�����������ݡ�
        }
    } while (flag > 0 || length != 12 || pos > 0);

    search(stu.id, t, pos);
    if (pos >= 0) {
        cout << "��ѧ����Ϣ�Ѵ���" << endl;
        return;
    }
    cout << "������ѧ������" << endl;
    do {
        cin >> stu.name;
        length = 0;
        for (i = 0; i < 1000; i++) {
            if (stu.name[i]) {
                length++;
            } else {
                break;
            }
        }
        if (length > 20) {
            cout << "���ֹ���,����������" << endl;
            cin.clear();//��������ǣ����´������������������������ɱ�����֮ǰ�Ĳ�ƥ�������
            cin.sync();//���cin�����������ݡ�
        }
    } while (length > 20);

    cout << "������ѧ������" << endl;

    //����
    do {
        flag = 0;
        length = 0;
        cin >> stu.age;
        for (i = 0; i < sizeof(stu.age); i++) {
            if (stu.age[i]) {
                length++;
            } else {
                break;
            }
        }


        for (i = 0; i < length; i++) {
            if (stu.age[i] > '9' || stu.age[i] < '0') {
                flag++;
            }
        }
        //�ж������ں��ʵ�����
        if (strcmp(stu.age, "16") < 0 || strcmp(stu.age, "60") > 0) {
            flag++;
        }
        if (flag > 0 || length != 2) {
            cout << "�����������,����������ʵ������" << endl;
            cin.clear();//��������ǣ����´������������������������ɱ�����֮ǰ�Ĳ�ƥ�������
            cin.sync();//���cin�����������ݡ�
        }
    } while (flag > 0 || length != 2);


    cout << "������ѧ���Ա�" << endl;
    do {
        cin >> stu.sex;
        if (!strcmp(stu.sex, "��") || !strcmp(stu.sex, "Ů")) {//�ж��Ա������Ƿ�Ϸ�
            flag = 1;
        } else {
            cout << "�Ա��������,����������" << endl;
            flag = 0;
        }
        cin.clear();//��������ǣ����´������������������������ɱ�����֮ǰ�Ĳ�ƥ�������
        cin.sync();//���cin�����������ݡ�
    } while (flag == 0);


    cout << "������ѧ������" << endl;
    do {
        cin >> stu.pro;
        length = 0;
        for (i = 0; i < 1000; i++) {
            if (stu.pro[i]) {
                length++;
            } else {
                break;
            }
        }
        if (length > 20) {
            cout << "�����������,����������" << endl;
            cin.clear();//��������ǣ����´������������������������ɱ�����֮ǰ�Ĳ�ƥ�������
            cin.sync();//���cin�����������ݡ�
        }
    } while (length > 20);

    cout << "������ѧ��רҵ" << endl;
    do {
        cin >> stu.major;
        length = 0;
        for (i = 0; i < 1000; i++) {
            if (stu.major[i]) {
                length++;
            } else {
                break;
            }
        }
        if (length > 20) {
            cout << "רҵ���Ȳ��ó���20,����������" << endl;
            cin.clear();//��������ǣ����´������������������������ɱ�����֮ǰ�Ĳ�ƥ�������
            cin.sync();//���cin�����������ݡ�
        }
    } while (length > 20);


    file.write((char *) &stu, sizeof(stu));
    newindex = InsertIndex(stu, elems);
    createbitree(newindex, t);

    file.close();
    cout << "��ӳɹ�" << endl;

}

void del(tree *&t) {
    Student stu;
    tree *c;
    ifstream file("E:/mycode/student.txt");
    if (!file) {
        cout << "���ļ�ʧ��" << endl;
        exit(0);
    }
    //���ı������и��ǰ�벿��-��ɾ������-��벿��
    //��ǰ�벿��-��벿�� ����д���ı�
    cout << "������Ҫɾ����ѧ��" << endl;
    cin >> stu.id;
    int pos = -1;//��ʼ��ƫ��ֵ
    search(stu.id, t, pos);//��ѯѧ���Ƿ���� ���ı�ƫ��ֵ
    char front[pos];//���崢��ǰ�벿����Ϣ������
    if (pos >= 0) {//ѧ�Ŵ���
        file.seekg(0, ios::end); //ָ�뵽β
        unsigned int backlength = file.tellg() - pos - sizeof(stu);//�����벿���ı�����
        file.seekg(0, ios::beg);//ָ��ص�ͷ
        file.read((char *) &front, pos);
        char back[backlength];//���崢���벿����Ϣ������
        file.seekg(92, ios::cur);//�ƶ���ɾ��
        file.read((char *) &back, backlength);
        file.close();
        // ���ǰ�벿����Ϣ
        ofstream writefile("E:/mycode/student.txt", ios::ate);
        writefile.seekp(0);//ָ��ص�ͷ
        writefile.write((char *) &front, pos);
        writefile.close();
        //�ı�ĩ׷�Ӻ�벿����Ϣ
        ofstream bwritefile("E:/mycode/student.txt", ios::app);
        bwritefile.write((char *) &back, backlength);
        bwritefile.close();

        updateIndex(t, c, pos, stu.id);//�޸�ƫ��ֵ
        delIndex(t, stu.id);//ɾ�����

        cout << "ɾ���ɹ�" << endl;
    } else {
        //system("cls");
        cout << "�Ҳ�����ѧ����Ϣ" << endl;
    }
}

void update(tree *&t) {
    int i;
    int flag;
    int length;
    Student stu;
    int pos = -1;
    memset(&stu, '\0', sizeof(stu));//���建����ĻᲿ������
    fstream file("E:/mycode/student.txt");
    if (!file) {
        cout << "���ļ�ʧ��" << endl;
        exit(0);
    }
    cout << "������ѧ����ѧ��" << endl;
    cin >> stu.id;
    search(stu.id, t, pos);//��ѧ��
    file.seekp(pos); //��λ
    if (pos >= 0) {

        cout << "������Ҫ�޸ĵ�ѧ������" << endl;
        do {
            cin >> stu.name;
            length = 0;
            for (i = 0; i < 1000; i++) {
                if (stu.name[i]) {
                    length++;
                } else {
                    break;
                }
            }
            if (length > 20) {
                cout << "���ֹ���,����������" << endl;
                cin.clear();//��������ǣ����´������������������������ɱ�����֮ǰ�Ĳ�ƥ�������
                cin.sync();//���cin�����������ݡ�
            }
        } while (length > 20);


        cout << "������Ҫ�޸ĵ�ѧ������" << endl;
        do {
            flag = 0;
            length = 0;
            cin >> stu.age;
            for (i = 0; i < sizeof(stu.age); i++) {
                if (stu.age[i]) {
                    length++;//�����������ݵĳ��� �����ж��Ƿ񳬹�����������ַ����鳤��
                } else {
                    break;
                }
            }
            for (i = 0; i < length; i++) {//�ж����������Ƿ�Ϊ����
                if (stu.age[i] > '9' || stu.age[i] < '0') {
                    flag++;//��ʶ�� �ж����������Ƿ��������
                }
            }

            if (strcmp(stu.age, "16") < 0 || strcmp(stu.age, "60") > 0) {
                flag++;//��ʶ��  �ж��������Ƿ���ʵ�����
            }
            if (flag > 0 || length != 2) {
                cout << "�����������,����������ʵ������" << endl;
                cin.clear();//��������ǣ����´������������������������ɱ�����֮ǰ�Ĳ�ƥ�������
                cin.sync();//���cin�����������ݡ�
            }
        } while (flag > 0 || length != 2);


        cout << "������Ҫ�޸ĵ�ѧ���Ա�" << endl;
        do {
            cin >> stu.sex;
            if (!strcmp(stu.sex, "��") || !strcmp(stu.sex, "Ů")) {//�ж��Ա������Ƿ�Ϸ�
                flag = 1;
            } else {
                cout << "�Ա��������,����������" << endl;
                flag = 0;
            }
            cin.clear();//��������ǣ����´������������������������ɱ�����֮ǰ�Ĳ�ƥ�������
            cin.sync();//���cin�����������ݡ�
        } while (flag == 0);

        cout << "������Ҫ�޸ĵ�ѧ������" << endl;
        do {
            cin >> stu.pro;
            length = 0;
            for (i = 0; i < 1000; i++) {
                if (stu.pro[i]) {
                    length++;
                } else {
                    break;
                }
            }
            if (length > 20) {
                cout << "�����������,����������" << endl;
                cin.clear();//��������ǣ����´������������������������ɱ�����֮ǰ�Ĳ�ƥ�������
                cin.sync();//���cin�����������ݡ�
            }
        } while (length > 20);
        cout << "������Ҫ�޸ĵ�ѧ��רҵ" << endl;
        do {
            cin >> stu.major;
            length = 0;
            for (i = 0; i < 1000; i++) {


                if (stu.major[i]) {
                    length++;
                } else {
                    break;
                }
            }
            if (length > 20) {
                cout << "רҵ���Ȳ��ó���20,����������" << endl;
                cin.clear();//��������ǣ����´������������������������ɱ�����֮ǰ�Ĳ�ƥ�������
                cin.sync();//���cin�����������ݡ�
            }
        } while (length > 20);
        file.write((char *) &stu, sizeof(stu));
    } else {
        system("cls");
        cout << "�Ҳ�����ѧ����Ϣ" << endl;
        cout << "" << endl;
    }
    file.close();
}


int main() {
    tree *root;
    root = updateIndex(); //��������
    while (true) {
        switch (Menu()) {
            case 1:
                system("cls");//����
                look(root); //�����ѯѧ����Ϣѡ�����
                break;
            case 2:
                system("cls");
                add(root);//���ѧ����Ϣ
                break;
            case 3:
                system("cls");
                del(root);// ɾ��ѧ����Ϣ
                break;
            case 4:
                system("cls");
                update(root);//����ѧ����Ϣ
                break;
            case 5://�˳�ϵͳ
            {
                cout << "�Ƿ�ȷ���˳�ѧ����Ϣ����ϵͳ?(y/n)" << endl;
                char x;
                cin >> x;
                if (x == 'y' || x == 'Y') {
                    return 0;
                } else if (x == 'n' || x == 'N') {
                    system("cls");
                    break;
                } else {
                    cout << "�������" << endl;
                    break;
                }
            }
            default:
                cout << "�޴˹���" << endl;
                break;
        }
    }
    return 0;
}

