#include "Student.h"
#include "studentMessage.h"

using namespace std;

void showMenu();

int main() {
    int h;
    studentMessage stuM = studentMessage();
    while (1) {
        showMenu();
        cout <<"������:";
        cout << "�����������Ӧ����� : ";
        cin >> h;
        cout << endl;
        switch (h) {
            case 1:
                stuM.showAll();
                break;
            case 2:
                stuM.add();
                break;
            case 3:
                stuM.searchId();
                break;
            case 4:
                stuM.searchName();
                break;
            case 5:
                stuM.del();
                break;
            case 6:
                stuM.clear();
                return 0;
            case 7:
                stuM.change();
                break;
            case 8:
                stuM.read();
                break;
            case 0:
                cout << "\n�˳��ɹ���";
                return 0;
            default:
                cout << "\n�������������������ȷ����š�" << endl;
        }
    }
}

void showMenu() {
    cout << "                               \n";
    cout << "===============================\n";
    cout << "      ѧ���ɼ�����ϵͳ\n\n";
    cout << "      1.��ʾ����ѧ���ɼ�\n";
    cout << "      2.�����Ϣ\n";
    cout << "      3.ѧ�Ų�ѯ��Ϣ\n";
    cout << "      4.���ֲ�ѯ��Ϣ\n";
    cout << "      5.ɾ����Ϣ\n";
    cout << "      6.���������Ϣ���˳�ϵͳ\n";
    cout << "      7.�޸���Ϣ\n";
    cout << "      8.��ȡ�ļ�\n";
    cout << "      0.�˳�ϵͳ\n";
    cout << "===============================\n";
    cout << "                               \n";
}