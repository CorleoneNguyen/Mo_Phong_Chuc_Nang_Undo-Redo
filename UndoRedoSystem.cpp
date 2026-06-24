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

int UndoRedoManager::loadFromFile(string filename, bool verbose) {
    ifstream file(filename);
    if (!file.is_open()) {
        if (verbose) cout << " >> Khong the mo file: " << filename << "\n";
        return -1;
    }

    string actionName;
    int count = 0;
    while (getline(file, actionName)) {
        if (!actionName.empty()) {
            executeNewAction(actionName, verbose);
            count++;
        }
    }
    file.close();

    if (verbose) {
        cout << " >> Nap du lieu tu file \"" << filename << "\" thanh cong! (" << count << " thao tac)\n";
    }
    return count;
}

void UndoRedoManager::runPerformanceTest() {
    vector<string> files = { "TestData_Nhom2_small.txt", "TestData_Nhom2_medium.txt", "TestData_Nhom2_large.txt" };

    cout << "\n=========== KET QUA DANH GIA HIEU SUAT ===========\n";
    cout << left << setw(22) << "File"
        << setw(12) << "So dong"
        << setw(18) << "Thoi gian (ms)"
        << "TB (ms/thao tac)\n";

    for (size_t i = 0; i < files.size(); i++) {
        auto start = chrono::high_resolution_clock::now();
        int count = loadFromFile(files[i], false);
        auto end = chrono::high_resolution_clock::now();

        if (count < 0) {
            cout << left << setw(22) << files[i] << "-> Khong tim thay file!\n";
            continue;
        }

        double ms = chrono::duration<double, milli>(end - start).count();
        cout << left << setw(22) << files[i]
            << setw(12) << count
                << setw(18) << fixed << setprecision(3) << ms
                << fixed << setprecision(5) << (count > 0 ? ms / count : 0.0) << "\n";
    }
    cout << "====================================================\n";
}
