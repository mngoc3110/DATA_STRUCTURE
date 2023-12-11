#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP
#include <iostream>
#include <string>
//#include <filesystem>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/types.h>
#include <dirent.h>
#endif
using namespace std;
class Node {
public:
    string data;
    Node* next;
    Node(const string& value) : data(value), next(nullptr) {}
};
class LinkedList {
private:
    Node* head;
    int size;
public:
    /********************************************
     * Hàm khởi tạo với con trỏ là head và size = 0
    *********************************************/
    LinkedList() : head(nullptr), size(0) {}
    /********************************************
     * Thêm vào linkedlist
    *********************************************/
    void insert(const string& value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
        size++;
    }
    /********************************************
     * Đến số lượng file txt trong folder
    *********************************************/
   int getCountOfTxtFiles() const {
    // Khởi tạo biến đếm
    int count = 0;

    // Con trỏ duyệt danh sách
    Node* current = head;

    // Duyệt qua danh sách
    while (current != nullptr) {
        // Lấy tên file từ node hiện tại
        string filename = current->data;

        // Kiểm tra đuôi mở rộng
        if (filename.substr(filename.find_last_of(".") + 1) == "txt") {
            // Tăng biến đếm
            count++;
        }

        // Di chuyển con trỏ đến node tiếp theo
        current = current->next;
    }

    // Trả về số lượng file txt
    return count;
}

    /********************************************
     * In ra số lượng sách
    *********************************************/


   





static void Print() {
    LinkedList fileList;
    std::string folderPath = "book/";

    int txtFileCount = 0;

#ifdef _WIN32
    WIN32_FIND_DATAA findData;
    HANDLE hFind = INVALID_HANDLE_VALUE;

    std::string searchPath = folderPath + "*.txt";
    hFind = FindFirstFileA(searchPath.c_str(), &findData);
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            fileList.insert(findData.cFileName);
            txtFileCount++;
        } while (FindNextFileA(hFind, &findData));
        FindClose(hFind);
    }
#else
    DIR* dir;
    struct dirent* ent;

    if ((dir = opendir(folderPath.c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            std::string fileName = ent->d_name;
            if (fileName.size() >= 4 && fileName.substr(fileName.size() - 4) == ".txt") {
                fileList.insert(fileName);
                txtFileCount++;
            }
        }
        closedir(dir);
    }
#endif

    std::cout << "Amount of books: " << txtFileCount << std::endl << std::endl;
}


};
#endif