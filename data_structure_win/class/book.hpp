#ifndef BOOK_HPP
#define BOOK_HPP
#include <iostream>
#include <fstream>
#include "vector.hpp"
#include <cstdio>
#include <string>
using namespace std;

class Book{
    private:
        string MaSach;
        string TenSach;
        string TacGia;
        string NhaXuatBan;
        float GiaBan;
        int Nam;
        int SoTrang;
        string NgayNhapKho;
        int TinhTrang;
    public:
        Book(){
            MaSach = " ";
            TenSach = " ";
            TacGia = " ";
            NhaXuatBan = " ";
            GiaBan = 0.0;
            Nam = 0;
            SoTrang = 0;
            NgayNhapKho = " ";
            TinhTrang = 0;
        }    
        ~Book(){}
        /********************************************
         * Viết ở main
        *********************************************/
        void read();
        /********************************************
         * Nhập sách
         * Nếu như mã sách đã tồn tại thì không cho
         * Ghi thông tin vào file txt
        *********************************************/
        void Input(int amount){
            MyVector<Book> b;
            Book a;
            for(int i=0;i<amount;i++){
                cout<<"ENTER BOOK LABEL<MA + NUMBER>: ";
                cin>>a.MaSach;
                bool check = true;
                size_t size = b.getSize();
                for(int i=0;i<size;i++){
                    if(b[i].MaSach == a.MaSach){
                        cout<<"BOOK HAS EXISTED\n";
                        Input(amount - 1);
                    }
                }
                cout<<"ENTER BOOK NAME: ";
                cin.ignore();
                getline(cin,a.TenSach);
                fflush(stdin);
                cout<<"ENTER AUTHOR NAME: ";
                getline(cin,a.TacGia);
                fflush(stdin);
                cout<<"ENTER PUBLISHER: ";
                getline(cin,a.NhaXuatBan);
                fflush(stdin);
                cout<<"ENTER SELLING PRICE: ";
                cin>>a.GiaBan;
                cout<<"ENTER RELEASE DATE: ";
                cin>>a.Nam;
                cout<<"ENTER BOOK PAGE NUMBER: ";
                cin>>a.SoTrang;
                cout<<"ENTER RECEIPT DATE: ";
                cin>>a.NgayNhapKho;
                b.push_back(a);
                a.read();
            }
        }
        /********************************************
         * xuất sách viết ở main
        *********************************************/
        void Output();
        /********************************************
         * xoá sách bằng cách truy cập vào folder
         * Sử dụng hàm remove 
        *********************************************/
        void Deleted(string& sach){
            string tenFile = "book/" + sach + ".txt"; 
            if (remove(tenFile.c_str()) != 0) {
                //perror("CANNOT REMOVE BOOK");
            } else {
                printf("\033[1;31m|-----BOOK %s HAS REMOVED-----|\033[0m\n\n", sach.c_str());
            }
        }
};
#endif