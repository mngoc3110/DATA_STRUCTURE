#ifndef QUANLY_HPP
#define QUANLY_HPP
#include <iostream>
#include <fstream>
#include <termios.h>
#include <unistd.h>
#include "../LinkedList.hpp"
#include "../class/book.hpp"
using namespace std;
class Manager : public Book{
    private:
        string ID;
        string PassWord;
    public:
        Manager(){
            ID = " ";
            PassWord = " ";
        }
        ~Manager(){}
        bool DangNhap();
        /********************************************
         * Sử dụng Linkedlist đọc folder để in ra số
        lượng sách đang có
         * in ra terminal như bình thường bằng cách 
        gọi hàm output được viết ở main
        *********************************************/
        void ShowBook(){
            LinkedList::Print();
            cout<<endl<<endl;
            cout<<"\n\n|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|\n";
            cout<<"|------------------------------------------------------------------------------------LIBRARY----------------------------------------------------------------------------------------|\n";
            cout<<"|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|\n\n";
            cout << left << setw(10) << "Mã Sách" << setw(40) << "Tên Sách" << setw(25) << "Tác Giả" << setw(25) << "Nhà Xuất Bản" << setw(20) << "Giá Bán" << setw(25) << "Năm phát hành" << setw(20) << "Số trang" << setw(25) << "Ngày nhập Kho" << setw(20) << "Tình Trạng" << endl;
            Book::Output();
        };
        /********************************************
         * Trang trí, gọi hàm Input ở book.hpp
        *********************************************/
        void AddBook(int amount){                 
            cout<<endl<<endl;
            cout<<"_______________________________\n";
            cout<<"|-------ENTER YOUR BOOK-------|\n";
            cout<<"|_____________________________|\n\n";
            Book::Input(amount);
        };
        /********************************************
         * Gọi hàm ở book.hpp
        *********************************************/
        void DeleteBook(string& sach){
            Book::Deleted(sach);
        };
        /********************************************
         * Kiểm tra kí tự
        *********************************************/
        bool isPromptKey(char cInput) {
            return cInput == '\n' || cInput == '\r';
        }
        /********************************************
         * Kiểm tra có phải nút ESC không
        *********************************************/
        bool isSystemKey(char cInput) {
            return cInput == 27; 
        }
        /********************************************
         * Kiểm tra có hợp lệ không
        *********************************************/
        bool isValidChar(char cInput) {
            return isalnum(cInput) || ispunct(cInput) || cInput == ' ';
        }
        /********************************************
         * Điền vào chỗ trống
        *********************************************/
        void fillRow(char character, int length) {
            for (int i = 0; i < length; i++) {
                cout << character;
            }
            cout << endl;
        }
        /********************************************
         * Điều chỉnh vị trí con trỏ
        *********************************************/
        void setCursorPos(int x, int y) {
            cout << "\033[" << y << ";" << x << "H";
        }
        /********************************************
         * Mã hoá mật khẩu sử dụng termios.h
         * fill vào vị trí được nhập '*'
         * check xem mật khẩu có trống hay không
        *********************************************/
        string inputPassword(int yOffset, short type) {
            int sX = 0; 
            int sY = yOffset; 
            int dx = 1;
            int sLength = 20;
            string strPassword = "PASSWORD: ";
            string strInput;
            char cInput;
            cout << strPassword;
            if (!strInput.empty())
                fillRow('*', strInput.length());
            while (true) {
                setCursorPos(sX + dx + strPassword.length() + strInput.length(), sY);
                do {
                    termios oldt;
                    tcgetattr(STDIN_FILENO, &oldt);
                    termios newt = oldt;
                    newt.c_lflag &= ~ICANON;
                    newt.c_lflag &= ~ECHO;
                    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
                    cInput = getchar();
                    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
                } while (!isPromptKey(cInput) && (cInput != '\b' || strInput.empty()) && (strInput.length() >= sLength || !isValidChar(cInput)) && !isSystemKey(cInput));
                if (isPromptKey(cInput)) {
                    if (cInput == '\n' && strInput.empty()) {
                        cout << "Mật khẩu không được để trống!" << endl;
                        continue;
                    }
                    break;
                }
                if (isSystemKey(cInput)) {
                    cInput = getchar();
                    continue;
                }
                if (cInput == '\b')
                    strInput.pop_back();
                else {
                    strInput += cInput;
                    cout << '*';
                }
            }
            cout<<endl<<endl;
            return strInput;
        }
};
#endif