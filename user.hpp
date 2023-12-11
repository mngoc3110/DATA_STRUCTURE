#ifndef USER_HPP
#define USER_HPP


#include <iostream>
#include <random>
#include <string>
#include <cstdlib>
#include <chrono>
#include <wx/wx.h>


using namespace std;
class user {
    public:
        string name;
        string date;
        int maso;
        string Address;
        string phone;
    public:
        user(){
            name = " ";
            date = " ";
            maso = 0;
            Address = "Dai hoc su pham";
            phone = " ";
        }
        string getName() const { return name; }
       // string getDate() const { return date;}
        int getMaso() const { return maso;}
        string getAddress()const{return Address;}
        string getPhone()const{return phone;}
        /********************************************
         * Viết ở main
        *********************************************/
        //void TraSach(int SoPhieuMuon, string MaSach);
        /********************************************
         * viết ở main
        *********************************************/
        //void Muon(const string& tenFile, const string kyTuThayThe);
        /********************************************
         * Tạo random 1 số gồm 4 chữ số
         * và số cuối cùng phải khác 0
        *********************************************/
        int getnumber() {
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<int> dist(100, 999);
            int maso = dist(gen)*10+1 ;
            return maso;
        }
        /********************************************
         * Lấy ra thời gian hiện tại
        *********************************************/
        string gettime(){
            time_t currenttime = time(nullptr);
            tm* time = localtime(&currenttime);
            char buffer[80];
            strftime(buffer,sizeof(buffer), "%d-%m-%Y", time);
            date = buffer;
            return date;
        }
        /********************************************
         * Toán tử nhập tên
        *********************************************/
        friend istream& operator>>(istream& is,user& a){
            //cin.ignore();
            cout<<"ENTER NAME: ";
            getline(cin,a.name);
            fflush(stdin);
            return is;
        }
        /********************************************
         * Toán tử xuất
        *********************************************/
        friend ostream& operator<<(ostream& os, user a){
            os<<"NAME: "<<a.name<<endl;
            os<<"DATE: "<<a.gettime()<<endl;
            os<<"NUMBER: "<<a.getnumber()<<endl;
            os<<"ADDRRESS: "<<a.Address<<endl;
            os<<"PHONE NUMBER: "<<a.phone<<endl;
            return os;
        }
        void Xuat(){
            cout<<"NAME: "<<name<<endl;
            cout<<"DATE: "<<gettime()<<endl;
            cout<<"NUMBER: "<<getnumber()<<endl;
        }
        void Nhap(){
            cout<<"ENTER YOUR ADDRESS: ";
            getline(cin,Address);
            cout<<"ENTER YOUR PHONE NUMBER: ";
            cin>>phone;
            cin.ignore();
        }
};






class UserNode {
public:
    user data;
    UserNode* next;
    UserNode(const user& userData) : data(userData), next(nullptr) {}
};

class LinkedListUser : public user{
private:
    UserNode* head;
    int size;

public:
    LinkedListUser() : head(nullptr), size(0) {}
    void insert(const user& member){
        UserNode* newUserNode = new UserNode(member);
        if (head == nullptr) {
            head = newUserNode;
        } else {
            UserNode* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newUserNode;
        }
        size++;
    }
    void print(){
        UserNode* current = head;
        while (current != nullptr) {
            cout << current->data << endl;
            current = current->next;
        }
    }
    bool contains(string name) {
    UserNode* current = head;
    while (current != nullptr) {
        if (current->data.getName() == name) {
            return true;
        }
        current = current->next;
    }
    return false;
}
 UserNode* getHead() const {
        return head;
    }
    int getSize() const {
        int count = 0;
        UserNode* current = head;
        while (current != nullptr) {
            count++;
            current = current->next;
        }
        return count;
    }
};


#endif
