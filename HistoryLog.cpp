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

    int idx = hashFunc(act.id);
    newNode->hashNext = hashTable[idx];
    hashTable[idx] = newNode;
}


void HistoryLog::clearFuture(DLLNode* node) {
    // 1. Xác định Node đầu tiên của tương lai cần xóa
    DLLNode* toDelete = (node == nullptr) ? head : node->next;

    // 2. Cập nhật lại con trỏ head/tail của danh sách chính trước khi xóa
    if (node == nullptr) {
        head = tail = current = nullptr;
    }
    else {
        node->next = nullptr;
        tail = node; // Cắt đuôi từ vị trí hiện tại
    }

    // 3. Tiến hành xóa từng Node tương lai trong cả DLL và HashTable
    while (toDelete != nullptr) {
        DLLNode* temp = toDelete;
        toDelete = toDelete->next; // Dịch sang Node tiếp theo trước khi delete

        // XÓA KHỎI HASH TABLE (Dùng con trỏ cấp 2 chuẩn)
        int idx = hashFunc(temp->data.id);
        DLLNode** pp = &hashTable[idx];

        while (*pp && *pp != temp) {
            pp = &((*pp)->hashNext);
        }

        if (*pp) {
            *pp = temp->hashNext; // Bẻ nhánh liên kết nối tiếp, loại bỏ hoàn toàn temp khỏi hash
        }

        delete temp; // Giải phóng bộ nhớ của Node cũ
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
    DLLNode* cur = hashTable[hashFunc(id)];
    while (cur && cur->data.id != id) cur = cur->hashNext;
    return cur; // Nếu không tìm thấy, cur sẽ tự bằng nullptr và trả về luôn
}
