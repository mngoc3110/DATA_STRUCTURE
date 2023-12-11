#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP
#include <iostream>
#include <string>
#include <dirent.h>
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
        int count = 0;
        Node* current = head;
        while (current != nullptr) {
            string filename = current->data;
            if (filename.substr(filename.find_last_of(".") + 1) == "txt") {
                count++;
            }
            current = current->next;
        }
        return count;
    }
    /********************************************
     * In ra số lượng sách
    *********************************************/
    static void Print() {
        LinkedList fileList;
        DIR* dir;
        struct dirent* entry;
        string directoryPath = "book/";  
        dir = opendir(directoryPath.c_str());
        if (dir == nullptr) {
            cerr << "Failed to open directory." << endl;
            return;
        }
        while ((entry = readdir(dir)) != nullptr) {
            if (entry->d_type == DT_REG) {
                fileList.insert(entry->d_name);
            }
        }
        closedir(dir);
        int txtFileCount = fileList.getCountOfTxtFiles();
        cout << "Amount of books: " << txtFileCount << endl<<endl;

   
    }
};
#endif