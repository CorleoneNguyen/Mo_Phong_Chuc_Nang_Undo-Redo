#pragma once
#ifndef UNDO_REDO_SYSTEM_H
#define UNDO_REDO_SYSTEM_H

#include <string>
#include <iostream>

using namespace std;

struct Action {
    string id;
    string name;
    string timestamp;
};

// Node danh cho ngan xep (Stack - DSLK don)
struct StackNode {
    Action data;
    StackNode* next;
};

// Node danh cho lich su thao tac (History - DSLK doi)
struct DLLNode {
    Action data;
    DLLNode* prev;
    DLLNode* next;
    DLLNode* hashNext;//hash table
};


class MyStack {
private:
    StackNode* top;

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

    static const int HASH_SIZE = 2220;
    DLLNode* hashTable[HASH_SIZE] = { nullptr };
    int hashFunc(string id) {
        int h = 0;
        for (char c : id) h = (h * 31 + c) % HASH_SIZE;
        return h;
    }
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
    int loadFromFile(string filename, bool verbose = true); 
    void runPerformanceTest(); // doc TestData_small/medium/large.txt va do thoi gian xu ly
};

#endif
