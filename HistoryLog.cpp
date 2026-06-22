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

void HistoryLog::addLog(Action act) {
    DLLNode* newNode = new DLLNode{ act, nullptr, nullptr };
    if (head == nullptr) {
        head = tail = current = newNode;
    }
    else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
        current = newNode; 
    }

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

}

void HistoryLog::displayHistory() {
    if (head == nullptr) {
        cout << " -> Nhat ky trong!\n";
        return;
    }
    DLLNode* cur = head;
    cout << "\n======= NHAT KY LOG TOAN CANH =======\n";
    while (cur != nullptr) {
        if (cur == current) {
            cout << " --> [" << cur->data.id << " | " << cur->data.name << " | " << cur->data.timestamp << "] (Hien tai)\n";
        }
        else {
            cout << "     [" << cur->data.id << " | " << cur->data.name << " | " << cur->data.timestamp << "]\n";
        }
        cur = cur->next;
    }
    cout << "=====================================\n";
}

DLLNode* HistoryLog::findById(string id) {
    DLLNode* cur = head;

    while (cur != nullptr) {
        if (cur->data.id == id) {
            return cur; // Tìm thấy phần tử trùng ID, trả về con trỏ DLLNode*
        }
        cur = cur->next;
    }

    return nullptr; // Duyệt hết danh sách không thấy thì trả về nullptr
}
