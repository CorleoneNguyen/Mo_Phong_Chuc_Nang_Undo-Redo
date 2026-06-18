#include "UndoRedoSystem.h"

HistoryLog::HistoryLog() {
    head = nullptr;
    tail = nullptr;
    current = nullptr;
}

HistoryLog::~HistoryLog() {
    // Giải phóng danh sách liên kết đôi khi hủy đối tượng
    DLLNode* cur = head;
    while (cur != nullptr) {
        DLLNode* nextNode = cur->next;
        delete cur;
        cur = nextNode;
    }
}

DLLNode* HistoryLog::getCurrent() { return current; }
void HistoryLog::setCurrent(DLLNode* node) { current = node; }
DLLNode* HistoryLog::getHead() { return head; }

// ====
// TODO
// ===+

void HistoryLog::addLog(Action act) {
    // 1. Cấp phát một DLLNode mới chứa cấu trúc dữ liệu 'act'.
    // 2. Nếu danh sách rỗng (head == nullptr): Gán cả head, tail và current bằng node mới này.
    // 3. Nếu danh sách đã có phần tử: Thêm node mới vào sau 'tail', cập nhật liên kết đôi (prev/next) giữa tail cũ và node mới, sau đó chuyển 'tail' và 'current' sang node mới.
    // 4. ĐỪNG QUÊN: Thêm node mới này vào Hash Table 'idIndex' theo cấu trúc: idIndex[act.id] = newNode để hỗ trợ tra cứu O(1).
}

void HistoryLog::clearFuture(DLLNode* node) {
    // Hàm này dùng để xóa các hành động thuộc "tương lai" khi người dùng thực hiện hành động mới sau khi đã Undo.
    // 1. Xác định vị trí bắt đầu xóa (toDelete):
    //    - Nếu node truyền vào là nullptr (đã Undo hết về trước cả hành động đầu tiên): Cần xóa sạch toàn bộ log từ 'head'. Đặt head = tail = nullptr.
    //    - Ngược lại: Nhánh tương lai sẽ bắt đầu từ node->next. Ngắt kết nối bằng cách đặt node->next = nullptr và cập nhật tail = node.
    // 2. Chạy vòng lặp giải phóng bộ nhớ (delete) các node từ vị trí 'toDelete' cho đến hết danh sách.
    // 3. LƯU Ý: Trong vòng lặp, trước khi delete node nào thì phải xóa ID của node đó khỏi Hash Table 'idIndex' bằng hàm: idIndex.erase(id).
}

void HistoryLog::displayHistory() {
    // 1. Nếu nhật ký trống (head == nullptr), in thông báo ra màn hình.
    // 2. Tạo một con trỏ chạy duyệt từ 'head' đến cuối danh sách.
    // 3. In thông tin của từng node (id, name, timestamp).
    // 4. ĐẶC BIỆT: Kiểm tra xem node đang duyệt có trùng với con trỏ 'current' không. Nếu trùng thì in thêm chữ "(Hien tai)" ở bên cạnh để người dùng biết mình đang đứng ở bước nào.
}

DLLNode* HistoryLog::findById(string id) {
    // Sử dụng Hash Table 'idIndex' để tìm kiếm nhanh node có ID tương ứng.
    // Dùng hàm idIndex.find(id). Nếu tìm thấy thì trả về con trỏ DLLNode*, ngược lại trả về nullptr.
    // Yêu cầu bắt buộc đạt độ phức tạp O(1).
    return nullptr;
}