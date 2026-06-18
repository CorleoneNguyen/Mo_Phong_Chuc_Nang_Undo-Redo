#include "UndoRedoSystem.h"
#include <ctime>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <chrono>

UndoRedoManager::UndoRedoManager() {
}

string UndoRedoManager::getCurrentTimeStr() {
    time_t now = time(0);

    tm ltm;
    localtime_s(&ltm, &now);
    stringstream ss;
    ss << setfill('0') << setw(2) << ltm.tm_hour << ":"
        << setw(2) << ltm.tm_min << ":"
        << setw(2) << ltm.tm_sec;
    return ss.str();
}

void UndoRedoManager::viewHistory() {
    log.displayHistory();
}

// ======
// TODO: 2 người
// =====

void UndoRedoManager::executeNewAction(string actionName, bool verbose) {
    // 1. Gọi hàm log.clearFuture(log.getCurrent()) để cắt bỏ toàn bộ nhánh tương lai bị thừa trước khi lưu hành động mới.
    // 2. Tính toán mã số ID tiếp theo (nextId): Lấy ID của node 'current' hiện tại ép sang kiểu số (stoi) rồi cộng thêm 1. Nếu current là nullptr thì ID bắt đầu từ 1.
    // 3. Khởi tạo một struct Action mới gồm: id tự tăng vừa tính, actionName, và chuỗi thời gian lấy từ hàm getCurrentTimeStr().
    // 4. Cập nhật các cấu trúc dữ liệu:
    //    - Thêm vào danh sách lịch sử: log.addLog(act)
    //    - Đẩy vào ngăn xếp undo: undoStack.push(act)
    //    - Xóa sạch ngăn xếp redo (vì chuỗi hành động mới đã làm mất hiệu lực các bước redo cũ): redoStack.clear()
    // 5. Nếu verbose == true, in thông báo thực hiện thành công ra màn hình.
}

void UndoRedoManager::undoOneStep() {
    // 1. Kiểm tra nếu undoStack rỗng thì in thông báo không thể Undo và dừng hàm.
    // 2. Lấy hành động ra khỏi undoStack (pop) và đẩy hành động đó vào redoStack (push).
    // 3. Cập nhật lại con trỏ lịch sử hệ thống: Di chuyển log.current lùi về phía trước một bước (log.setCurrent(current->prev)).
    // 4. In thông báo đã hoàn tác hành động thành công.
}

void UndoRedoManager::redoOneStep() {
    // 1. Kiểm tra nếu redoStack rỗng thì in thông báo không thể Redo và dừng hàm.
    // 2. Lấy hành động ra khỏi redoStack (pop) và đẩy ngược lại vào undoStack (push).
    // 3. Cập nhật lại con trỏ lịch sử hệ thống tiến lên một bước:
    //    - Nếu log.current đang là nullptr (đang đứng ở vị trí ban đầu chưa có gì), đặt current trỏ tới head (hành động đầu tiên).
    //    - Ngược lại, đặt current dịch tới node tiếp theo (current = current->next).
    // 4. In thông báo đã làm lại hành động thành công.
}

void UndoRedoManager::jumpToID(string targetId) {
    // 1. Sử dụng hàm log.findById(targetId) để tìm node đích. Nếu trả về nullptr thì in lỗi và dừng hàm.
    // 2. Thực hiện vòng lặp dịch chuyển con trỏ hiện tại (log.getCurrent()) cho tới khi nó bằng với targetNode:
    //    - Nếu log.getCurrent() == nullptr (đang ở vạch xuất phát): chỉ có thể tiến lên bằng cách gọi redoOneStep().
    //    - So sánh ID mục tiêu và ID hiện tại (LƯU Ý: Phải dùng stoi() để ép sang kiểu số nguyên rồi mới so sánh, không so sánh chuỗi).
    //    - Nếu ID mục tiêu < ID hiện tại: Gọi undoOneStep() để lùi lại.
    //    - Nếu ID mục tiêu > ID hiện tại: Gọi redoOneStep() để tiến lên.
    // 3. Kết thúc vòng lặp, in thông báo đã nhảy thành công tới ID mong muốn.
}

int UndoRedoManager::loadFromFile(string filename, bool verbose) {
    // 1. Mở file có tên 'filename' bằng ifstream. Nếu mở lỗi, in thông báo (nếu verbose = true) và trả về -1.
    // 2. Tạo một biến đếm count = 0 và một chuỗi tạm để đọc dữ liệu.
    // 3. Dùng vòng lặp dữ liệu đọc từng dòng từ file (getline). Với mỗi dòng không rỗng, gọi hàm executeNewAction(line, verbose) và tăng count.
    // 4. Đóng file và trả về số lượng hành động (count) đã nạp thành công.
    return 0;
}

void UndoRedoManager::runPerformanceTest() {
    // 1. Tạo một vector chứa danh sách 3 file: "TestData_Nhom2_small.txt", "TestData_Nhom2_medium.txt", "TestData_Nhom2_large.txt".
    // 2. In tiêu đề bảng hiển thị kết quả (File, Số dòng, Thời gian ms, Trung bình ms/thao tác).
    // 3. Chạy vòng lặp qua 3 file trên:
    //    - Sử dụng thư viện <chrono> lấy mốc thời gian bắt đầu (high_resolution_clock::now()).
    //    - Gọi hàm loadFromFile(file, false) để nạp dữ liệu (để verbose = false để tránh I/O màn hình làm sai lệch thời gian đo).
    //    - Lấy mốc thời gian kết thúc và tính số miligiây (ms) thực thi.
    //    - Tính toán thời gian trung bình cho mỗi thao tác (ms / count) và in kết quả ra định dạng bảng đẹp mắt, căn lề thẳng hàng.
}