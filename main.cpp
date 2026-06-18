#include "UndoRedoSystem.h"
#include <iostream>

using namespace std;

void showMenu() {
    // =================================================================
    // TODO: HIỂN THỊ MENU CHƯƠNG TRÌNH
    // =================================================================
    // In ra màn hình danh sách các lựa chọn cho người dùng (từ 0 đến 7):
    // 1. Nhập hành động mới (Execute Action)
    // 2. Quay lại bước trước (Undo)
    // 3. Làm lại bước vừa xóa (Redo)
    // 4. Xem toàn bộ nhật ký lịch sử (View History)
    // 5. Nhảy tới một hành động bất kỳ (Jump to ID)
    // 6. Nạp dữ liệu mẫu từ file Demodata.txt
    // 7. Đánh giá hiệu suất (TestData_small/medium/large.txt)
    // 0. Thoát chương trình
}

int main() {
    UndoRedoManager manager;
    int choice;
    string inputStr;

    while (true) {
        // =================================================================
        // TODO: XỬ LÝ LỰA CHỌN CỦA NGƯỜI DÙNG (SWITCH CASE)
        // =================================================================
        // 1. Gọi hàm showMenu() để hiển thị danh sách lựa chọn.
        // 2. Nhận biến 'choice' từ bàn phím (cin >> choice) và xóa bộ nhớ đệm (cin.ignore()).
        // 3. Sử dụng cấu trúc switch(choice) để gọi các hàm tương ứng từ đối tượng 'manager':
        //    - Case 1: Yêu cầu nhập tên hành động (getline) rồi gọi manager.executeNewAction(inputStr).
        //    - Case 2: Gọi manager.undoOneStep().
        //    - Case 3: Gọi manager.redoOneStep().
        //    - Case 4: Gọi manager.viewHistory().
        //    - Case 5: Yêu cầu nhập ID mục tiêu rồi gọi manager.jumpToID(inputStr).
        //    - Case 6: Gọi manager.loadFromFile("DemoData_Nhom2.txt").
        //    - Case 7: Gọi manager.runPerformanceTest().
        //    - Case 0: In chữ "Tam biet!" và kết thúc chương trình (return 0).
        //    - Default: Thông báo lựa chọn không hợp lệ nếu người dùng nhập sai số.

        break; // Vòng lặp tạm thời để tránh treo máy khi chưa viết code, xóa dòng này khi cài đặt.
    }
    return 0;
}