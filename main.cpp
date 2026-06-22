#include "UndoRedoSystem.h"
#include <iostream>

using namespace std;

void showMenu() {
    cout << "\n======= MENU DIEU KHIEN CHUONG TRINH =======\n";
    cout << "1. Nhap hanh dong moi (Execute Action)\n";
    cout << "2. Quay lai buoc truoc (Undo)\n";
    cout << "3. Lam lai buoc vua xoa (Redo)\n";
    cout << "4. Xem toan bo nhat ky lich su (View History)\n";
    cout << "5. Nhay toi mot hanh dong bat ky (Jump to ID)\n";
    cout << "6. Nap du lieu mau tu file DemoData_Nhom2\n";
    cout << "7. Danh gia hieu suat (TestData_Nhom2_small/medium/large.txt)\n";
    cout << "0. Thoat chuong trinh\n";
    cout << "============================================\n";
    cout << "Nhap lua chon cua ban: ";
}

int main() {
    UndoRedoManager manager;
    int choice;
    string inputStr;

    while (true) {
        showMenu();
        cin >> choice;
        cin.ignore(); // Bo qua ky tu enter con sot lai trong buffer

        switch (choice) {
        case 1:
            cout << "Nhap ten hanh dong/thao tac: ";
            getline(cin, inputStr);
            manager.executeNewAction(inputStr);
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
            cout << "Nhap ID muc tieu muon nhay den (Vi du: 3): ";
            cin >> inputStr;
            manager.jumpToID(inputStr);
            break;
        case 6:
            manager.loadFromFile("DemoData_Nhom2.txt");
            break;
        case 7:
            manager.runPerformanceTest();
            break;
        case 0:
            cout << "Tam biet!\n";
            return 0;
        default:
            cout << "Lua chon khong hop le! Vui long chon lai.\n";
        }
    }
    return 0;
}
