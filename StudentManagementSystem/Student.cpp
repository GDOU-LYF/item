//
// Created by SoneS on 2021/6/16.
//

#include "Student.h"

Student::Student() {
    std::cout << "������ѧ��ѧ�� : ";
    std::cin >> ID;
    std::cout << "������ѧ������ : ";
    std::cin >> name;
    std::cout << "������ѧ������ѧ��Ӣ���C++�ɼ� : " << std::endl;
    int a, b, c;
    std::cin >> a;
    while (a < 0 || a > 100) {
        std::cout << "����ɼ���������������: " << std::endl;
        std::cin >> a;
    }
    std::cin >> b;
    while (b < 0 || b > 100) {
        std::cout << "����ɼ���������������: " << std::endl;
        std::cin >> b;
    }
    std::cin >> c;
    while (c < 0 || c > 100) {
        std::cout << "����ɼ���������������: " << std::endl;
        std::cin >> c;
    }
    score[1] = a;
    score[2] = b;
    score[3] = c;
    score[4] = a + b + c;
    next = nullptr;
}

std::string Student::getName() {
    return name;
}

std::string Student::getID() {
    return ID;
}

double Student::getMath() {
    return score[1];
}

double Student::getEnglish() {
    return score[2];
}

double Student::getCpp() {
    return score[3];
}

double Student::gettotal() {
    return score[4];
}

void Student::in_Student() {
    std::ofstream outfile;
    outfile.open("afile.dat", std::ios::app);
    outfile << "ѧ�ţ�" << std::setw(3) << ID << "   ";
    outfile << "���֣�" << std::setw(3) << name << "   ";
    outfile << "��ѧ��" << std::setw(3) << score[1] << "   ";
    outfile << "Ӣ�" << std::setw(3) << score[2] << "   ";
    outfile << "c++��" << std::setw(3) << score[3] << "   ";
    outfile << "�ܳɼ���" << std::setw(3) << score[4] << "   " << "\n";
    outfile.close();
}

void Student::display() {
    std::cout << " " << std::setw(3) << ID << "     " << std::setw(3) << name << "      ";
    for (int i = 1; i <= 4; i++) {
        std::cout << std::setw(3) << score[i] << "      ";
    }
    std::cout << std::endl;
}