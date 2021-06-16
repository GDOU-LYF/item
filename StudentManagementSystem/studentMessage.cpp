//
// Created by SoneS on 2021/6/16.
//

#include "studentMessage.h"

studentMessage::studentMessage() {
    first = NULL;
    last = NULL;
}

void studentMessage::add() {
    Student *t = new Student;
    Student *p = first;
    t->in_Student();
    while (p) {
        if (p->ID == t->ID) {
            std::cout << "\nѧ�����������ѧ���ɼ��Ѿ����ڣ�(�����޸ģ�����ɾ��������¼��)" << std::endl;
            return;
        }
        p = p->next;
    }
    if (first == NULL) {
        first = last = t;

    } else {
        last->next = t;
        last = t;
    }
}

void studentMessage::searchId() {
    std::string a;
    std::cout << "\n������Ҫ���ҵ�ѧ����ѧ��:";
    std::cin >> a;
    Student *t = first;
    while (t) {
        if (t->ID == a) {
            break;
        }
        t = t->next;
    }
    if (!t) {
        std::cout << "\nδ�ҵ�Ҫ����ѧ����" << std::endl;
        return;
    }
    std::cout << "\n���ҳɹ���" << std::endl;
    std::cout << " ѧ��     ����     ��ѧ     Ӣ��     C++     �ܳɼ�" << std::endl;
    t->display();
}

void studentMessage::searchName() {
    std::string a;
    std::cout << "\n������Ҫ���ҵ�ѧ��������:";
    std::cin >> a;
    Student *t = first;
    while (t) {
        if (t->name == a) {
            break;
        }
        t = t->next;
    }
    if (!t) {
        std::cout << "\nδ�ҵ�Ҫ����ѧ����" << std::endl;
        return;
    }
    std::cout << "\n���ҳɹ���" << std::endl;
    std::cout << " ѧ��     ����     ��ѧ     Ӣ��     C++     �ܳɼ�" << std::endl;
    t->display();
}

void studentMessage::del() {
    std::string a;
    std::cout << "\n������Ҫɾ����ѧ����ѧ��: ";
    std::cin >> a;
    Student *t = first;
    Student *p = nullptr;
    while (t) {
        if (t->ID == a) {
            break;
        }
        p = t;
        t = t->next;
    }
    if (!t) {
        std::cout << "\nδ�ҵ�Ҫɾ��ѧ����" << std::endl;
        return;
    }
    if (!p) {
        first = first->next;
        std::cout << "\n�ɹ�ɾ��ѧ��" << a << std::endl;
        delete t;
    } else {
        p->next = t->next;
        std::cout << "�ɹ�ɾ��ѧ��" << a << std::endl;
        delete t;
    }


}

void studentMessage::read() {
    std::ifstream file;

    file.open("afile.dat", std::ios::in);

    if (!file.is_open()) {
        std::cout << "�ļ���ʧ��" << '\n';
        return;
    }
    char buf[1024] = {0};
    while (file.getline(buf, sizeof(buf))) {
        std::cout << buf << std::endl;
    }
    file.close();
}


void studentMessage::showAll() {
    std::cout << "---------------------�ɼ��б�----------------------" << std::endl;
    std::cout << " ѧ��    ����     ��ѧ     Ӣ��     Cpp     �ܳɼ�" << std::endl;
    Student *t = first;
    while (t) {
        t->display();
        t = t->next;
    }
}


void studentMessage::clear() {
    int x;
    std::cout << "ȷ��Ҫ���������Ϣ��������1��2 (1:ȷ�� 2:ȡ��) : ";
    std::cin >> x;
    if (x == 2) {
        std::cout << "\nȡ�����\n" << std::endl;
        return;
    }
    Student *t = first;
    Student *p;
    while (t) {
        p = t;
        t = t->next;
        delete p;
    }
    std::cout << "\n��ճɹ���\n";
    std::cout << "�˳��ɹ���\n";
}

void studentMessage::change() {
    std::string a;
    int b;
    int c;
    std::cout << "\n������Ҫ���ҵ�ѧ����ѧ��:";
    std::cin >> a;
    Student *t = first;
    while (t) {
        if (t->ID == a) {
            break;
        }
        t = t->next;
    }
    if (!t) {
        std::cout << "\nδ�ҵ�Ҫ����ѧ����" << std::endl;
        return;
    }
    std::cout << "\n����Ҫ�޸���һ���ɼ���(1.��ѧ��2.Ӣ�3.C++)" << std::endl;
    std::cin >> b;
    std::cout << "\n�޸ĵĳɼ�Ϊ��" << std::endl;
    std::cin >> c;
    switch (b) {
        case 1:
            t->score[1] = c;
            break;
        case 2:
            t->score[2] = c;
            break;
        case 3:
            t->score[3] = c;
            break;
    }
}