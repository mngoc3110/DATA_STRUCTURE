#include <iostream>
#include <algorithm>
#include <cstdlib>
#include "class/user.hpp"
#include <fstream>
#include "quanly/quanly.hpp"
#include <iomanip>

#include "LinkedList.hpp"
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/types.h>
#include <dirent.h>
#endif
using namespace std;
/************************************
    Số lần đăng nhập
    Toạ độ con trỏ password
*************************************/
int ATTEMP = 3;
bool check = false;
int y=17; 
/************************************
    Các hàm sử dụng
*************************************/
int LoginDisplay();
int ManageDisplay();
char Getch(); 
int NumberTicket(); 
void printSuccessful();
int TicketDisplay();
void printFail();
void printDN();
/************************************
    Hàm main
*************************************/
int main(void) {
    /********************************************
    win sử dụng thư viện conio.h để xài hàm getch()
    *********************************************/
    
 
    /********************************************
       Giữ chương trình luôn chạy
    *********************************************/
    while(true){
        /********************************************
         * Cursor giữ giá trị trả về của hàm login
         * If else theo chức năng
         * cursor = 0 là đăng nhập quản lý
         * cursor = 1 là các chức năng khác
        *********************************************/
        int Cursor = LoginDisplay();
        if(Cursor==1){
            Manager a;
            if(a.DangNhap()){
                /****************************************************
                 * CursorManager giữ giá trị của chức năng quản lý
                 * Sẽ có 3 chức năng chính 
                 * Nếu như hiển thị thông tin sách -> gọi hàm và kết
                 thúc giao diện terminal bằng endwin()
                 * Nếu như thêm sách -> nhập số lượng sách -> gọi hàm
                 và có chức năng kiểm tra thông tin sách vừa nhập
                 * Nếu xoá sách thì cũng như thêm sách
                 * goto để quay lại hàm ban đầu mà không cần đệ quy
                *****************************************************/
                printSuccessful();
                MANAGE:int CursorManager = ManageDisplay();
                bool ExitFlag = false;
                
                    if(CursorManager ==  1&& !ExitFlag){
                        a.ShowBook();
                        while(true){
                            cout<<"\n\nGO BACK ENTER 0:";
                            int Back;
                            cin>>Back;
                            if(Back==0){
                                goto MANAGE;
                            } else {
                                cout<<"Enter again!!!\n\n";
                            }
                        }
                            
                    } else if(CursorManager ==  2&& !ExitFlag){
                        cout<<"________________________________\n";
                        cout<<"\n|  ENTER NUMBER OF BOOK: ";
                        int amount; 
                        cin>>amount;
                        cout<<"\n________________________________\n";
                        cin.ignore();
                        a.AddBook(amount);
                        cout<<"\nWANT TO CHECK AGAIN?"<<endl;
                        cout<<"Y: YES        N: NO\n";
                        cout<<endl;
                        char XacNhan;
                        cout<<"Enter here: ";
                        cin>>XacNhan;
                        while(XacNhan=='y'){
                            a.ShowBook();
                           
                            printSuccessful();
                            goto MANAGE;
                        } if(XacNhan=='n'){
                            cout<<"_________________________________\n";
                            cout<<"|      ADDING SUCCESSFULLY      |\n"<<endl;
                            cout<<"|_______________________________|\n\n";
                            goto MANAGE;
                        }
                    } else if(CursorManager ==  3){
                        a.ShowBook();
                        cout<<endl;
                        cout<<"________________________________________\n";
                        cout<<"| HOW MANY BOOK YOU WANT TO DELETE?: ";
                        int SoLuong;
                        cin>>SoLuong;
                        cout<<endl;
                        cout<<"|_______________________________________|\n"; 
                        for(int i=0;i<SoLuong;i++){
                            string sach;
                            cout<<"\n\n________________________________________\n";
                            cout<<"| PLEASE ENTER BOOK LABEL: ";
                            cin>>sach;
                            cout<<endl;
                            cout<<"|_______________________________________|\n\n\n";
                            a.DeleteBook(sach);
                            printSuccessful();
                        }
                        goto MANAGE;
                    } 
                    else {
                        break;
                    }                   
                
            /********************************************
             * Thực hiện chức năng giới hạn đăng nhập
             * Nhập sai mật khẩu 3 lần -> khoá 30s 
             * reset số lần thử và con trỏ password
            *********************************************/
            } else {
                ATTEMP = 3;
                y=5;
                printDN();
                
            }
        /********************************************
         * Mượn sách -> số lượng sách cần mượn
         -> ID người dùng sẽ được tự động tạo khi 
         nhập tên người dùng và sẽ dựa theo thời gian 
         thực
         * Trả sách -> làm ngược lại
        *********************************************/
        } else if(Cursor==2){
            char keyBanDoc;
            user b;
            int Selection;
            while(true){
                Selection=TicketDisplay();
                if(Selection==1){                   
                    cin>>b;
                    cout<<b;
                    b.ShowBook();
                    cout<<"HOW MANY BOOK WANT TO BORROW: ";
                    int SoLuongSach;
                    cin>>SoLuongSach;
                    for(int i=0;i<SoLuongSach;i++){
                        cout<<"ENTER NUMBER/ID: ";
                        string MaSo; 
                        cin>>MaSo;
                        cout<<"ENTER BOOK LABEL: ";
                        string Ma;
                        cin>>Ma;
                        b.Muon(Ma,MaSo);
                    } 
                } else if(Selection==2){
                    cout<<"ENTER NUMBER TICKET: ";
                    int SoPhieuMuon;
                    cin>>SoPhieuMuon;
                    cout<<"ENTER BOOK LABEL: ";
                    string MaSach;
                    cin>>MaSach;
                    b.TraSach(SoPhieuMuon,MaSach);
                    printSuccessful();
                }
            }
        /********************************************
         * Thoát chương trình 
        *********************************************/   
        } else if(Cursor==0){
            cout<<"\n\n\n_________________________________________________________________________\n";
            cout<<"|                         THANKS FOR USING SYSTEM                       |\n";
            cout<<"|_______________________________________________________________________|\n\n\n";
            break; 
        }
    }
}
/*******************************************************
    sử dụng thư viện ncurse                             
    công dụng: làm giao diện cho phần quản lý phiếu mượn
********************************************************/
int ManageDisplay() {
    cout<<endl<<endl;
    cout<<"        MANAGER DISPLAY\n\n\n";
    cout<<"-------------------------------------\n";
    cout<<"| 1. SHOW BOOK                      |\n";
    cout<<"| 2. ADD BOOK                       |\n";
    cout<<"| 3. DELETE BOOK                    |\n";
    cout<<"| 0. BACK                           |\n";
    cout<<"-------------------------------------\n";
    /*
        xử lý hàm getch() tại đây 
    */
    cout<<"Enter your choice: ";
    int Choice;
    cin>>Choice;
    if(Choice==0){
        LoginDisplay();
    } else if(Choice==1){
        return Choice;
    } else if(Choice == 2){
        return Choice;
    }else if(Choice==3){
        return Choice;
    } 
    else {
        cout<<"\n\nPLEASE ENTER AGAIN!!!\n\n";
        ManageDisplay();
    }
    return 0;
}
/*******************************************************
    sử dụng thư viện ncurse                             
    công dụng: làm giao diện cho phần đăng nhập
********************************************************/
int LoginDisplay(){ 
    cout<<endl<<endl;
    cout<<"        LIBRARY MANAGEMENT\n\n\n";
    cout<<"-------------------------------------\n";
    cout<<"| 1. MANAGER                        |\n";
    cout<<"| 2. ACCOUNTING                     |\n";
    cout<<"| 0. QUIT                           |\n";
    cout<<"-------------------------------------\n";
    /*
        xử lý hàm getch() tại đây 
    */
    cout<<"Enter your choice: ";
    int Choice;
    cin>>Choice;
    if(Choice==0){
        cout<<"\n\n\n_________________________________________________________________________\n";
        cout<<"|                         THANKS FOR USING SYSTEM                       |\n";
        cout<<"|_______________________________________________________________________|\n\n\n";
        exit(0);
    } else if(Choice==1){
        return Choice;
    } else if(Choice == 2){
        return Choice;
    } else {
        LoginDisplay();
    }
    return 0;
}
/*******************************************************
    sử dụng nhập xuất file                             
    công dụng: thực hiện chức năng đăng nhập
    nếu như nhập đúng sẽ cho phép truy cập
    nếu sai thì -1 lần thử 3 lần thì sẽ thoát
********************************************************/
bool Manager::DangNhap(){
    bool login = false;
    string line1, line2;
    string id, pass;
    ifstream file("quanly/quanly.txt");
    if(file.is_open()){
        getline(file,line1);
        getline(file,line2);
        file.close();
    } else {
        cout<<"Khong the mo file\n";
    }
    cout<<"________________________________\n";
    cout<<"|         LOGIN SYSTEM         |\n";
    cout<<"|______________________________|\n";
    cout<<"ENTER YOUR ID: ";
    cin>>id;
    fflush(stdin);
    cout<<"ENTER YOUR PASSWORD: ";
    //pass = Manager::inputPassword(y,2);
    cin>>pass;
    fflush(stdin);
    while(ATTEMP>0 && !login){
        if(id==line1 && pass==line2){
            return true;
            login=true;
            break;
        } else{
            cout<<"********************************\n";
            cout<<"*     WRONG PASSWORD OR ID     *\n";
            cout<<"*     PLEASE ENTER AGAIN       *\n";
            cout<<"********************************\n"<<endl;
            ATTEMP-=1;
            y+=11;
            DangNhap();
        }
    }
    if(ATTEMP == 0&&!check){
        cout<<endl;
        check=true;
        return false;
        
    }
    return false;
}
/*************************************************************
    sử dụng thư viện termios                             
    công dụng: dùng để nhận diện khi nào người dùng nhấn esc
**************************************************************/
// char Getch() {
//     char buf = 0;
//     struct termios old = {0};
//     if (tcgetattr(0, &old) < 0)
//         perror("tcsetattr()");
//     old.c_lflag &= ~ICANON;
//     old.c_lflag &= ~ECHO;
//     old.c_cc[VMIN] = 1;
//     old.c_cc[VTIME] = 0;
//     if (tcsetattr(0, TCSANOW, &old) < 0)
//         perror("tcsetattr ICANON");
//     if (read(0, &buf, 1) < 0)
//         perror("read()");
//     old.c_lflag |= ICANON;
//     old.c_lflag |= ECHO;
//     if (tcsetattr(0, TCSADRAIN, &old) < 0)
//         perror("tcsetattr ~ICANON");
//     return buf;
// }
/*******************************************************
    sử dụng thư viện fstream                           
    công dụng: mở thư mục và đọc file cần ghi
********************************************************/
void Book::read() {
    ofstream file;
    string fileName = "book/"+MaSach + ".txt"; 
    file.open(fileName); 
    file << left << setw(10) << MaSach << setw(40) << TenSach << setw(20) << TacGia << setw(20) << NhaXuatBan << setw(20) << GiaBan << setw(20) << Nam << setw(20) << SoTrang << setw(20) << NgayNhapKho << setw(20) << TinhTrang << endl;
    file.close(); 
}
/*******************************************************
    sử dụng thư viện fstream                             
    công dụng: xuất sách ra ngoài
********************************************************/
void Book::Output() {
    std::string folderPath = "book/";

#ifdef _WIN32 // Kiểm tra hệ điều hành là Windows
    WIN32_FIND_DATAA findData;
    HANDLE hFind = FindFirstFileA((folderPath + "*").c_str(), &findData);

    if (hFind != INVALID_HANDLE_VALUE) {
        int BookCount = 0;
        do {
            std::string fileName = findData.cFileName;
            if (fileName.find(".txt") != std::string::npos) {
                std::ifstream file(folderPath + fileName);
                std::string bookInfo;
                while (std::getline(file, bookInfo)) {
                    std::cout << bookInfo << std::endl;
                }
                file.close();
                std::cout << "------------------------" << std::endl;
                BookCount++;
            }
        } while (FindNextFileA(hFind, &findData));

        FindClose(hFind);

        if (BookCount == 0) {
            std::cout << "Kho đang trống" << std::endl;
        }
    } else {
        std::cout << "Không thể mở thư mục sách." << std::endl;
    }

#elif defined(__APPLE__) // Kiểm tra hệ điều hành là macOS
    DIR *dir;
    struct dirent *ent;
    int BookCount = 0;
    if ((dir = opendir(folderPath.c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            std::string fileName = ent->d_name;
            if (fileName.find(".txt") != std::string::npos) {
                std::ifstream file(folderPath + fileName);
                std::string bookInfo;
                while (std::getline(file, bookInfo)) {
                    std::cout << bookInfo << std::endl;
                }
                file.close();
                std::cout << "------------------------" << std::endl;
                BookCount++;
            }
        }
        closedir(dir);

        if (BookCount == 0) {
            std::cout << "Kho đang trống" << std::endl;
        }
    } else {
        std::cout << "Không thể mở thư mục sách." << std::endl;
    }

#else
    std::cout << "Hệ điều hành không được hỗ trợ." << std::endl;
#endif
}
/*********************************************************                    
    công dụng: kiểm tra hệ thống đang ở phiếu muợn số mấy
    và tiếp tục tăng thứ tự phiếu mượn
**********************************************************/
int NumberTicket(){
    static int soPhieuMuon = 1;
    ifstream TestFile;
    while(true){
        string tenPhieuMuon = "PhieuMuon/PhieuMuon" + to_string(soPhieuMuon) + ".txt";
        TestFile.open(tenPhieuMuon);
        if(TestFile){
            TestFile.close();
            soPhieuMuon++;
        } else{
            break;
        }
    }
    return soPhieuMuon;
}
/*******************************************************
    sử dụng thư viện fstream                             
    công dụng: dùng để thực hiện chức năng mượn sách
    cũng như tạo phiếu mượn
********************************************************/
void user::Muon(const string& tenFile, const string kyTuThayThe) {
    string MaSoPhieuMuon = to_string(NumberTicket());
    string File = "book/"+tenFile+".txt";
    ifstream inputFile(File); 
    if (!inputFile.is_open()) {
        cout << "Lỗi: Không thể mở file." << endl;
        return;
    }
    string duLieu((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
    bool canMuonSach = true;
    if (!duLieu.empty()) {
        size_t pos = duLieu.find_last_not_of(" \t\n\r\f\v");
        if (pos != string::npos && duLieu[pos] == '0') {
            duLieu.erase(pos);
            duLieu += MaSoPhieuMuon;
        } else {
            printFail();
            return;
        }
    } else {
        cout << "BOOK HAS BEEN BORROWED." << endl;
        printSuccessful();
        return;
    }
    if (canMuonSach) {
    } else {
        cout << "Không thể mượn sách." << endl;
        printFail();
        return;
    }
    ofstream putFile(File, ios::trunc); 
    if (!putFile.is_open()) {
        cout << "Lỗi: Không thể mở file." << endl;
        return;
    }
    putFile << duLieu; 
    putFile.close();
    string tenPhieuMuon = "PhieuMuon/PhieuMuon" + MaSoPhieuMuon + ".txt";
    ofstream outputFile(tenPhieuMuon);
    if (!outputFile.is_open()) {
        cout << "Lỗi: Không thể tạo phiếu mượn." << endl;
        return;
    }
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);
    tm ngayPhaiTra = *localTime;
    ngayPhaiTra.tm_mday += 7;
    mktime(&ngayPhaiTra);
    outputFile << "So phieu muon: " << MaSoPhieuMuon << endl;
    outputFile << "Ma ban doc: " << kyTuThayThe << endl;
    outputFile << "Ma sach: " << tenFile << endl;
    outputFile << "Ngay muon: " << put_time(localTime, "%d/%m/%Y") << endl;
    outputFile << "Ngay phai tra: " << put_time(&ngayPhaiTra, "%d/%m/%Y") << endl;
    outputFile << "Tinh trang: 1" << endl;
    outputFile.close();
    printSuccessful();
    cout << "TICKET SUCCESSFULLY CREATED." << endl;
}
/*******************************************************
    sử dụng thư viện fstream                             
    công dụng: thực hiện chức năng trả sách
********************************************************/
void user::TraSach(int SoPhieuMuon, string MaSach){
    if(SoPhieuMuon<0 ||SoPhieuMuon == 0){
        cout<<"Phieu muon khong ton tai\n\n";
        return;
    }
    string ten_tep = "PhieuMuon/PhieuMuon" +to_string(SoPhieuMuon)+".txt";
    fstream file(ten_tep, ios::in | ios::out);
    if (!file.is_open()) {
        cout << "Không thể mở tệp văn bản." << endl;
        return;
    }
    string line;
    bool daThayThe = false;
    while (getline(file, line)) {
        if (line.find("Tinh trang: 1") != string::npos) {
            line = " 0";
            streampos position = file.tellg();
            file.seekp(position - static_cast<streamoff>(line.length()));
            file << line;
            daThayThe = true;
            break;
        }
    }
    file.close();
    string fileBook = "book/"+MaSach+".txt"; 
    ifstream inputFile(fileBook); 
    if (!inputFile.is_open()) {
        cout << "Lỗi: Không thể mở file." << endl;
        return;
    }
    string duLieu((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
    bool canMuonSach = true;
    if (!duLieu.empty()) {
        size_t pos = duLieu.find_last_not_of(" \t\n\r\f\v");
        if (pos != string::npos && duLieu[pos] != '0') {
            duLieu.erase(pos);
            duLieu += "0";
        } else {
            canMuonSach = false;
        }
    }
    if (canMuonSach) {
    } else {
        cout << "Không thể mượn sách." << endl;
        printFail(); 
        return;
    }
    ofstream putFile(fileBook, ios::trunc); 
    if (!putFile.is_open()) {
        cout << "Lỗi: Không thể mở file." << endl;
        return;
    }
    putFile << duLieu; 
    putFile.close();
    if (daThayThe) {
        cout << "Sách đã trả thành công" << endl;
    } else {
        cout << "Không tìm thấy sách" << endl;
    }
}
/*******************************************************                    
    công dụng: in chữ nếu như chức năng thành công
********************************************************/
void printSuccessful() { 
    printf("███████╗██   ██╗███████╗███████╗███████╗███████╗███████╗███████╗██   ██╗██═╗    ██═╗\n");
    printf("██╔════╝██   ██║██ ╔═══╝██ ╔═══╝██╔════╝██╔════╝██╔════╝██╔════╝██   ██║██ ║    ██ ║\n");
    printf("███████╗██   ██║██ ║    ██ ║    █████╗  ███████╗███████╗██████  ██   ██║██ ║    ██ ║\n");
    printf("╚════██║██   ██║██ ║    ██ ║    ██╔══╝  ╚════██║╚════██║██╔═══╝ ██   ██║██ ║    ██ ║\n");
    printf("███████║███████║███████╗███████╗███████╗███████║███████║██║     ███████║███████╗███████╗\n");
    printf("╚══════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝╚══════╝╚══════╝╚═╝      ╚═════╝ ╚═════╝ ╚═════╝\n");
    //sleep(2); // Dừng chương trình trong 2 giây
    // clear();
    // endwin(); // Kết thúc môi trường ncurses
}
/*******************************************************
    sử dụng thư viện ncurse                             
    công dụng: làm giao diện cho phần phiếu mượn
********************************************************/
int TicketDisplay(){   
    cout<<endl<<endl;
    cout<<"        MANAGER DISPLAY\n\n\n";
    cout<<"-------------------------------------\n";
    cout<<"| 1. BORROW                         |\n";
    cout<<"| 2. REMOVE                         |\n";
    cout<<"| 0. BACK                           |\n";
    cout<<"-------------------------------------\n";
    /*
        xử lý hàm getch() tại đây 
    */
    cout<<"Enter your choice: ";
    int Choice;
    cin>>Choice;
    if(Choice==0){
        LoginDisplay();
    } else if(Choice==1){
        return Choice;
    } else if(Choice == 2){
        return Choice;
    }
    else {
        cout<<"\n\nPLEASE ENTER AGAIN!!!\n\n";
        TicketDisplay();
    }
    return 0;
}
/*******************************************************                           
    công dụng: in chữ nếu như chức năng bị sai
********************************************************/
void printFail() { 
    printf("████████╗████████╗███████╗██═╗ \n");
    printf("███╔════╝██╔═══██║   ██ ╔╝██ ║ \n");
    printf("██████╗  ████████║   ██ ║ ██ ║ \n");
    printf("██╔═══╝  ██╔═══██║   ██ ║ ██ ║ \n");
    printf("██║      ██║   ██║███████╗███████╗\n");
    printf("╚═╝      ╚═╝   ╚═╝ ╚═════╝ ╚═════╝\n");
    //sleep(2); // Dừng chương trình trong 2 giây
    // clear();
    // endwin(); // Kết thúc môi trường ncurses
}
/*******************************************************                           
    công dụng: in chữ nếu như chức năng bị sai
    chờ 30s mới được sử dụng chức năng đăng nhập
********************************************************/
void printDN() { 
    printf("████████╗████████╗███████╗██═╗ \n");
    printf("███╔════╝██╔═══██║   ██ ╔╝██ ║ \n");
    printf("██████╗  ████████║   ██ ║ ██ ║ \n");
    printf("██╔═══╝  ██╔═══██║   ██ ║ ██ ║ \n");
    printf("██║      ██║   ██║███████╗███████╗\n");
    printf("╚═╝      ╚═╝   ╚═╝ ╚═════╝ ╚═════╝\n");
    printf("\n\n\n");
    printf("PLESE WAIT FOR 30 SECOND\n");
    //sleep(30); // Dừng chương trình trong 30 giây
    // clear();
    // endwin(); // Kết thúc môi trường ncurses
}