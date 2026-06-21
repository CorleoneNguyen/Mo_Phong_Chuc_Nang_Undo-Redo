#include "UndoRedoSystem.h"
#include <iostream>
#include <limits>

using namespace std;

void showMenu() {
    cout << "\n=====================================\n";
    cout << "     MO PHONG CHUC NANG UNDO/REDO\n";
    cout << "=====================================\n";
    cout << "1. Nhap hanh dong moi\n";
    cout << "2. Undo (Quay lai buoc truoc)\n";
    cout << "3. Redo (Lam lai buoc vua Undo)\n";
    cout << "4. Xem lich su thao tac\n";
    cout << "5. Nhay toi mot ID bat ky\n";
    cout << "6. Nap du lieu mau tu file\n";
    cout << "7. Danh gia hieu suat\n";
    cout << "0. Thoat\n";
    cout << "=====================================\n";
    cout << "Nhap lua chon: ";
}

int main() {
    UndoRedoManager manager;
    int choice;
    string inputStr;

    while (true) {
        showMenu();

        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {

        case 1:
            cout << "Nhap ten hanh dong: ";
            getline(cin, inputStr);

            if (!inputStr.empty())
                manager.executeNewAction(inputStr);
            else
                cout << "Ten hanh dong khong duoc rong!\n";
            break;

        case 2:
            manager.undoOneStep();
            break;

        case 3:
            manager.redoOneStep();
            break;

        case 4:
            manager.viewHistory();
            break;

        case 5:
            cout << "Nhap ID can nhay toi: ";
            getline(cin, inputStr);

            if (!inputStr.empty())
                manager.jumpToID(inputStr);
            else
                cout << "ID khong hop le!\n";

            break;

        case 6:
        {
            int result = manager.loadFromFile("DemoData_Nhom2.txt");

            if (result >= 0)
                cout << "Da nap thanh cong " << result << " thao tac.\n";
            else
                cout << "Khong the mo file DemoData_Nhom2.txt\n";

            break;
        }

        case 7:
            manager.runPerformanceTest();
            break;

        case 0:
            cout << "\nTam biet!\n";
            return 0;

        default:
            cout << "Lua chon khong hop le!\n";
        }

        cout << "\nNhan Enter de tiep tuc...";
        cin.get();
    }

    return 0;
}
