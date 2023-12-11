#include <iostream>
#include <random>
#include <string>
#include <cstdlib>
#include <chrono>
#include "../quanly/quanly.hpp"
using namespace std;
class user : public Manager{
    protected:
        string name;
        string date;
        int maso;
    public:
        /********************************************
         * Viết ở main
        *********************************************/
        void TraSach(int SoPhieuMuon, string MaSach);
        /********************************************
         * viết ở main
        *********************************************/
        void Muon(const string& tenFile, const string kyTuThayThe);
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
            cin.ignore();
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
            return os;
        }
};




