# 🔄 Undo/Redo Management System with Jump-to-ID

[![Institution](https://img.shields.io/badge/University-UTH-008080.svg)](https://ut.edu.vn/)
[![Language](https://img.shields.io/badge/Language-C%2B%2B17-blue.svg)](https://isocpp.org/)
[![Course](https://img.shields.io/badge/Course-Data%20Structures%20%26%20Algorithms-red.svg)]()
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)

Mô phỏng chức năng **Hoàn tác (Undo)** và **Làm lại (Redo)** kết hợp **Nhảy trạng thái (Jump-to-ID)** sử dụng kết hợp các Cấu trúc Dữ liệu: **Ngăn xếp (Stack - Singly Linked List)**, **Danh sách liên kết đôi (Doubly Linked List)** và **Bảng băm (Hash Table)**.
## ✨ Tính năng nổi bật

- **Cơ chế Undo/Redo chuẩn:** Tự động phá vỡ nhánh "Redo" tương lai khi thực hiện hành động mới (`Execute`).
- **Lưu trữ lịch sử toàn cảnh:** Danh sách liên kết đôi cho phép duyệt nhật ký thao tác theo 2 chiều linh hoạt.
- **Tính năng Jump-to-ID (O(1)):** Tra cứu tức thì và nhảy đến bất kỳ ID thao tác nào trong quá khứ thông qua Bảng băm (Hash Table).
- **Tích hợp Jump Marker:** Bản thân thao tác Jump cũng được coi là một hành động và có thể `Undo`/`Redo` bình thường để quay lại vị trí trước khi nhảy.
- **Đánh giá hiệu năng tích hợp:** Công cụ đo thời gian tự động (`std::chrono`) kiểm thử với các bộ dữ liệu lên đến 2,000 thao tác.

---

## 🏗️ Cấu trúc Dữ liệu & Giải thuật

Hệ thống kết hợp 3 cấu trúc dữ liệu cốt lõi để đạt được hiệu năng tối ưu:

| Chức năng / Thao tác | Cấu trúc Dữ liệu sử dụng | Độ phức tạp thời gian | Ghi chú |
| :--- | :--- | :---: | :--- |
| **`executeNewAction()`** | Stack (đơn) + DLL + Hash Table | **$O(1)$** | Sinh ID, ghi log, push Undo Stack, xóa Redo Stack |
| **`undoOneStep()`** | Stack (đơn) + DLL | **$O(1)$** | Pop Undo Stack, push Redo Stack, lùi con trỏ `current` |
| **`redoOneStep()`** | Stack (đơn) + DLL | **$O(1)$** | Pop Redo Stack, push Undo Stack, tiến con trỏ `current` |
| **`jumpToID(id)`** | Hash Table + DLL | **$O(1)$** *(trung bình)* | Tra cứu nhanh qua Hash Table thay vì duyệt $O(N)$ |
| **`clearFuture()`** | DLL + Hash Table | **$O(K)$** | $K$ là số node "tương lai" cần giải phóng khỏi RAM & Hash Table |

---

## 📁 Cấu trúc thư mục dự án

```text
.
├── src/
│   ├── Action.h               # Struct định nghĩa thực thể hành động
│   ├── MyStack.h / .cpp       # Cài đặt Ngăn xếp dạng Singly Linked List
│   ├── HistoryLog.h / .cpp    # Cài đặt Doubly Linked List & Hash Table
│   ├── UndoRedoSystem.h / .cpp# Bộ điều khiển trung tâm (UndoRedoManager)
│   └── main.cpp               # Giao diện điều khiển Console (Menu)
├── data/
│   ├── DemoData_Nhom2.txt         # Bộ dữ liệu mẫu chạy demo
│   ├── TestData_Nhom2_small.txt   # 20 thao tác (Small test)
│   ├── TestData_Nhom2_medium.txt  # 200 thao tác (Medium test)
│   └── TestData_Nhom2_large.txt   # 2000 thao tác (Large test)
└── README.md
