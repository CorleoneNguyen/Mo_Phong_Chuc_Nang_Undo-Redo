#include "UndoRedoSystem.h"
#include <ctime>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <chrono>

UndoRedoManager::UndoRedoManager() {
}

// Lay gio:phut:giay hien tai, dung lam timestamp cho moi hanh dong
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
    log.clearFuture(log.getCurrent()); // pha vo "tuong lai" cu truoc khi sinh ID moi

    DLLNode* curNode = log.getCurrent();
    int nextId = (curNode != nullptr) ? stoi(curNode->data.id) + 1 : 1;
    string id = to_string(nextId);

    Action act = { id, actionName, getCurrentTimeStr() };

    log.addLog(act);
    undoStack.push(act);
    redoStack.clear(); // hanh dong moi pha vo chuoi Redo cu

    if (verbose) {
        cout << " >> Thuc hien thanh cong: " << actionName << " (" << id << ")\n";
    }
}

static const string JUMP_MARKER = "__JUMP__";

void UndoRedoManager::undoOneStep() {
    if (undoStack.isEmpty()) {
        cout << " >> Khong the Undo! Ban dang o trang thai ban dau.\n";
        return;
    }

    Action act = undoStack.pop();
    redoStack.push(act);

    if (act.name == JUMP_MARKER) {
        // act.id = ID dich (luc Jump toi), act.timestamp = ID goc (truoc khi Jump)
        DLLNode* originNode = log.findById(act.timestamp);
        log.setCurrent(originNode); // co the la nullptr neu goc la "truoc hanh dong dau tien"
        cout << " >> Da Hoan tac (Undo Jump): Tro ve ID " << act.timestamp << "\n";
        return;
    }

    if (log.getCurrent() != nullptr) {
        log.setCurrent(log.getCurrent()->prev); // lui con tro lich su ve 1 buoc
    }

    cout << " >> Da Hoan tac (Undo): " << act.name << "\n";
}

void UndoRedoManager::redoOneStep() {
    if (redoStack.isEmpty()) {
        cout << " >> Khong the Redo! Khong co thao tac nao de lam lai.\n";
        return;
    }

    Action act = redoStack.pop();
    undoStack.push(act);

    if (act.name == JUMP_MARKER) {
        // Lam lai dung buoc Jump nay: nhay thang toi ID dich (act.id)
        DLLNode* targetNode = log.findById(act.id);
        log.setCurrent(targetNode);
        cout << " >> Da Lam lai (Redo Jump): Nhay den ID " << act.id << "\n";
        return;
    }

    if (log.getCurrent() == nullptr) {
        log.setCurrent(log.getHead());
    }
    else {
        log.setCurrent(log.getCurrent()->next); // tien con tro lich su len 1 buoc
    }

    cout << " >> Da Lam lai (Redo): " << act.name << "\n";
}

void UndoRedoManager::viewHistory() {
    log.displayHistory();
}

void UndoRedoManager::jumpToID(string targetId) {
    DLLNode* targetNode = log.findById(targetId);
    if (targetNode == nullptr) {
        cout << " >> Loi: Khong tim thay ID " << targetId << " trong nhat ky!\n";
        return;
    }

    DLLNode* originNode = log.getCurrent();
    string originId = (originNode != nullptr) ? originNode->data.id : "0"; // "0" = truoc hanh dong dau tien

    log.setCurrent(targetNode);

    Action marker = { targetId, JUMP_MARKER, originId };
    undoStack.push(marker);
    redoStack.clear(); // Jump cung la mot hanh dong moi -> pha vo nhanh Redo cu

    cout << " >> Da nhay den trang thai cua ID: " << targetId << "\n";
}

int UndoRedoManager::loadFromFile(string filename, bool verbose)
    // 1. Mở file có tên 'filename' bằng ifstream. Nếu mở lỗi, in thông báo (nếu verbose = true) và trả về -1.
    // 2. Tạo một biến đếm count = 0 và một chuỗi tạm để đọc dữ liệu.
    // 3. Dùng vòng lặp dữ liệu đọc từng dòng từ file (getline). Với mỗi dòng không rỗng, gọi hàm executeNewAction(line, verbose) và tăng count.
    // 4. Đóng file và trả về số lượng hành động (count) đã nạp thành công.
{
    std::ifstream file(filename);     // 1
    if (!file.is_open()) 
    {
        if (verbose)
        {
            cout << "Loi: Khong the mo file " << filename << endl;
        }
        return -1;
    }

    int count = 0;    // 2
    string line;
        
    while (std::getline(file, line))    // 3
    {
        if (!line.empty()) 
        {
            executeAction(line, !verbose);
            count++;
        }
    }
    file.close();   // 4
    return count;
}

void UndoRedoManager::runPerformanceTest() 
    // 1. Tạo một vector chứa danh sách 3 file: "TestData_Nhom2_small.txt", "TestData_Nhom2_medium.txt", "TestData_Nhom2_large.txt".
    // 2. In tiêu đề bảng hiển thị kết quả (File, Số dòng, Thời gian ms, Trung bình ms/thao tác).
    // 3. Chạy vòng lặp qua 3 file trên:
    //    - Sử dụng thư viện <chrono> lấy mốc thời gian bắt đầu (high_resolution_clock::now()).
    //    - Gọi hàm loadFromFile(file, false) để nạp dữ liệu (để verbose = false để tránh I/O màn hình làm sai lệch thời gian đo).
    //    - Lấy mốc thời gian kết thúc và tính số miligiây (ms) thực thi.
    //    - Tính toán thời gian trung bình cho mỗi thao tác (ms / count) và in kết quả ra định dạng bảng đẹp mắt, căn lề thẳng hàng.
{
    std::vector<string> files =   // 3-1
    {
        "TestData_Nhom2_small.txt",
        "TestData_Nhom2_medium.txt",
        "TestData_Nhom2_large.txt"
    };

    cout << "\n\n";
    cout << std::left << std::setw(30) << "File"     // 3-2
        << std::setw(15) << "So dong"
        << std::setw(20) << "Thoi gian ms"
        << "Trung binh ms/thao tac" << "\n";
    cout << "\n";

    for (const string& file : files) 
    {
        auto start = std::chrono::high_resolution_clock::now();
        int count = loadFromFile(file, false);

        auto end = std::chrono::high_resolution_clock::now();     // 3-3

        if (count == -1) 
        {
            cout << std::left << std::setw(30) << file
                << std::setw(15) << "Loi doc file" << "\n";
            continue;
        }

        std::chrono::duration<double, std::milli> duration = end - start;
        double elapsedMs = duration.count();

        double avgMsPerOp = (count > 0) ? (elapsedMs / count) : 0.0;  //  3-4
        cout << std::left << std::setw(30) << file
            << std::setw(15) << count
            << std::setw(20) << std::fixed << std::setprecision(2) << elapsedMs
            << std::fixed << std::setprecision(5) << avgMsPerOp << "\n";
    }
    cout << "\n";
}

    
