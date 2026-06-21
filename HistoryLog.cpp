#include "UndoRedoSystem.h"
#include <iostream>

using namespace std;

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

// =================================================================
// CÀI ĐẶT CÁC HÀM NHIỆM VỤ (ĐÃ LOẠI BỎ HASH TABLE)
// =================================================================

void HistoryLog::addLog(Action act) {
    // 1. Cấp phát một DLLNode mới chứa cấu trúc dữ liệu 'act'.
    DLLNode* newNode = new DLLNode(act); 

    // 2. Nếu danh sách rỗng (head == nullptr): Gán cả head, tail và current bằng node mới này.
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
        current = newNode;
    } 
    // 3. Nếu danh sách đã có phần tử: Thêm node mới vào sau 'tail', cập nhật liên kết đôi (prev/next) 
    // giữa tail cũ và node mới, sau đó chuyển 'tail' và 'current' sang node mới.
    else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
        current = newNode;
    }
    // 4. LƯU Ý: Đã bỏ hoàn toàn phần thêm vào Hash Table idIndex theo yêu cầu.
}

void HistoryLog::clearFuture(DLLNode* node) {
    // Hàm này dùng để xóa các hành động thuộc "tương lai" khi người dùng thực hiện hành động mới sau khi đã Undo.
    DLLNode* toDelete = nullptr;

    // 1. Xác định vị trí bắt đầu xóa (toDelete):
    //    - Nếu node truyền vào là nullptr (đã Undo hết về trước cả hành động đầu tiên): Cần xóa sạch toàn bộ log từ 'head'. Đặt head = tail = nullptr.
    if (node == nullptr) {
        toDelete = head;
        head = nullptr;
        tail = nullptr;
        current = nullptr;
    } 
    //    - Ngược lại: Nhánh tương lai sẽ bắt đầu từ node->next. Ngắt kết nối bằng cách đặt node->next = nullptr và cập nhật tail = node.
    else {
        toDelete = node->next;
        node->next = nullptr;
        tail = node;
    }

    // 2. Chạy vòng lặp giải phóng bộ nhớ (delete) các node từ vị trí 'toDelete' cho đến hết danh sách.
    while (toDelete != nullptr) {
        DLLNode* temp = toDelete;
        toDelete = toDelete->next;
        delete temp; // Giải phóng vùng nhớ RAM từng nút tương lai
    }
    // 3. LƯU Ý: Đã bỏ phần xóa ID khỏi Hash Table idIndex.erase(id).
}

void HistoryLog::displayHistory() {
    // 1. Nếu nhật ký trống (head == nullptr), in thông báo ra màn hình.
    if (head == nullptr) {
        cout << "[Thong bao] Nhat ky lich su hien tai dang trong!" << endl;
        return;
    }

    // 2. Tạo một con trỏ chạy duyệt từ 'head' đến cuối danh sách.
    DLLNode* cur = head;

    // 3. In thông tin của từng node (id, name, timestamp).
    while (cur != nullptr) {
        cout << "[" << cur->data.id << "] " << cur->data.name << " (" << cur->data.timestamp << ")";
        
        // 4. ĐẶC BIỆT: Kiểm tra xem node đang duyệt có trùng với con trỏ 'current' không. 
        // Nếu trùng thì in thêm chữ "(Hien tai)" ở bên cạnh.
        if (cur == current) {
            cout << " (Hien tai)";
        }
        cout << endl;
        cur = cur->next; // Chuyển sang nút kế tiếp
    }
}

DLLNode* HistoryLog::findById(string id) {
    // Do đã bỏ Hash Table, ta chuyển sang dùng thuật toán Duyệt tuần tự (Linear Search) 
    // trên Danh sách liên kết đôi để tìm kiếm node có ID tương ứng.
    DLLNode* cur = head;
    
    while (cur != nullptr) {
        if (cur->data.id == id) {
            return cur; // Tìm thấy phần tử trùng ID, trả về con trỏ DLLNode*
        }
        cur = cur->next;
    }
    
    return nullptr; // Duyệt hết danh sách không thấy thì trả về nullptr
}