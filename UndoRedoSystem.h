#pragma once
#ifndef UNDO_REDO_SYSTEM_H
#define UNDO_REDO_SYSTEM_H

#include <string>
#include <iostream>
#include <unordered_map> //thu vien hash

using namespace std;

// Cau truc du lieu cua mot Thao tac (Action)
struct Action {
    string id;
    string name;
    string timestamp;
};

// Node danh cho Ngan xep (Stack - DSLK don)
struct StackNode {
    Action data;
    StackNode* next;
};

// Node danh cho Nhat ky Lich su (History - DSLK doi)
struct DLLNode {
    Action data;
    DLLNode* prev;
    DLLNode* next;
};


class MyStack {
private:
    StackNode* top; // giống slide

public:
    MyStack();
    ~MyStack();

    void push(Action act);
    Action pop();
    Action topElement(); // tránh trùng tên biến top
    bool isEmpty();
    int size();
    void clear();
};


class HistoryLog {
private:
    DLLNode* head;
    DLLNode* tail;
    DLLNode* current;
    unordered_map<string, DLLNode*> idIndex; // Hash Table: tra cuu Node theo id, do phuc tap O(1)

public:
    HistoryLog();
    ~HistoryLog();
    DLLNode* getCurrent();
    void setCurrent(DLLNode* node);
    DLLNode* getHead();
    void addLog(Action act);
    void clearFuture(DLLNode* node);
    void displayHistory();
    DLLNode* findById(string id);
};


class UndoRedoManager {
private:
    MyStack undoStack;
    MyStack redoStack;
    HistoryLog log;
    string getCurrentTimeStr();

public:
    UndoRedoManager();
    void executeNewAction(string actionName, bool verbose = true);
    void undoOneStep();
    void redoOneStep();
    void viewHistory();
    void jumpToID(string targetId);
    int loadFromFile(string filename, bool verbose = true); // tra ve so thao tac da nap, -1 neu khong mo duoc file
    void runPerformanceTest(); // doc TestData_small/medium/large.txt va do thoi gian xu ly
};

#endif

