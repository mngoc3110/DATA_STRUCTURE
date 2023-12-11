#include <wx/wx.h>
#include <random>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <wx/event.h>
#include <wx/grid.h>
#include <wx/dir.h>
#include <wx/filename.h>
#include <sstream>
#include "Headers/LinkedList.hpp"
#include "user.hpp"
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/types.h>
#include <dirent.h>
#endif
using namespace std;
LinkedListUser listUser;
namespace fs = filesystem;
/******************************************
    Khai báo các class được khởi tạo
*******************************************/
class MainFrame;
class LoginDisplay;
class ShowBook;
class AddBook;
class DeleteBook;
class TicketDisplay;
class UserBorrowBook;
class BorrowBook;
class RestoreDisplay;
class App;
/******************************************
    Màng hình quản lý
    Hiển thị thông tin sách
    Thêm sách
    Xoá sách
*******************************************/
class ManageDisplay : public wxFrame {
    public:
        ManageDisplay(const wxString& title): wxFrame(nullptr,wxID_ANY,title,wxDefaultPosition,wxSize(1450,880)){
            wxPanel* panel = new wxPanel(this);
            wxStaticText* titleLabel = new wxStaticText(panel, wxID_ANY, "MANAGE DISPLAY",
            wxPoint(525 ,100), wxSize(500, 30));
            wxFont font(wxFontInfo(50).Bold());
            titleLabel->SetFont(font);
            wxButton* Button1 = new wxButton(panel, wxID_ANY, "SHOW", wxPoint(600, 300), wxSize(200, 30));
            Button1->Bind(wxEVT_BUTTON, &ManageDisplay::GoToShowBook  , this, Button1->GetId());
            wxButton* Button2 = new wxButton(panel, wxID_ANY, "ADD", wxPoint(600, 400), wxSize(200, 30));
            Button2->Bind(wxEVT_BUTTON, &ManageDisplay::GoToAddBook  , this, Button2->GetId());
            wxButton* Button3 = new wxButton(panel, wxID_ANY, "DELETE", wxPoint(600, 500), wxSize(200, 30));
            Button3->Bind(wxEVT_BUTTON, &ManageDisplay::GoToDelete,this,Button3->GetId());
            wxButton* backButton = new wxButton(panel, wxID_ANY, "BACK", wxPoint(600, 600), wxSize(200, 30));
            backButton->Bind(wxEVT_BUTTON, &ManageDisplay::BackToMain, this, backButton->GetId());
        }
        void BackToMain(wxCommandEvent& event);
        void GoToShowBook(wxCommandEvent& event);
        void GoToAddBook(wxCommandEvent& event);
        void GoToDelete(wxCommandEvent& event);
};
/******************************************
    Hiển thị thông tin sách
    In ra số lượng sách
    Thông tin từng cuốn sách
*******************************************/
class ShowBook : public wxFrame{
    public:
        ShowBook(const wxString& title): wxFrame(nullptr,wxID_ANY,title,wxDefaultPosition,wxSize(1450,880)){
            // Set the frame size and create a panel
   // SetSize(wxSize(800, 600));
    wxPanel* panel = new wxPanel(this, wxID_ANY);

    // Create a grid to display book information
    wxGrid* grid = new wxGrid(panel, wxID_ANY);
    grid->CreateGrid(0, 9); // Create a grid with 9 columns, initially with no rows

    // Set column labels
    grid->SetColLabelValue(0, "Mã sách");
    grid->SetColLabelValue(1, "Tên sách");
    grid->SetColLabelValue(2, "Tác giả");
    grid->SetColLabelValue(3, "Nhà xuất bản");
    grid->SetColLabelValue(4, "Giá bán");
    grid->SetColLabelValue(5, "Năm phát hành");
    grid->SetColLabelValue(6, "Số trang");
    grid->SetColLabelValue(7, "Ngày nhập kho");
    grid->SetColLabelValue(8, "Tình trạng");

    // Open the "book" directory
wxString bookDir = wxFileName::GetCwd() + wxFileName::GetPathSeparator() + "book/";
wxDir bookDirectory(bookDir);

if (bookDirectory.IsOpened()) {
    wxString filename;
    bool cont = bookDirectory.GetFirst(&filename, "*.txt", wxDIR_FILES);

    while (cont) {
        // Read book information from the text file
        std::ifstream file(bookDir + filename.ToStdString());
        std::string line;
        int row = grid->GetNumberRows();

        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string masach, tensach, Tacgia, nhaxuatban, giaban, namphathanh, sotrang, ngaynhapkho,tinhtrang;


            // Split the line into individual fields
            std::istringstream lineStream(line);
            lineStream >> masach >> tensach >> Tacgia >> nhaxuatban >> giaban>> namphathanh >> sotrang >> ngaynhapkho >> tinhtrang;

            // Add a new row to the grid
            grid->AppendRows();

            // Set cell values for the new row
            grid->SetCellValue(row, 0, wxString::FromUTF8(masach.c_str()));
            grid->SetCellValue(row, 1, wxString::FromUTF8(tensach.c_str()));
            grid->SetCellValue(row, 2, wxString::FromUTF8(Tacgia.c_str()));
            grid->SetCellValue(row, 3, wxString::FromUTF8(nhaxuatban.c_str()));
            grid->SetCellValue(row, 4, wxString::FromUTF8(giaban.c_str()));
            grid->SetCellValue(row, 5, wxString::FromUTF8(namphathanh.c_str()));
            grid->SetCellValue(row, 6, wxString::FromUTF8(sotrang.c_str()));
            grid->SetCellValue(row, 7, wxString::FromUTF8(ngaynhapkho.c_str()));
            grid->SetCellValue(row, 8, wxString::FromUTF8(tinhtrang.c_str()));

            row++;
        }

        file.close();
        cont = bookDirectory.GetNext(&filename);
    }
}

    // Set the font for the grid
    wxFont font(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    grid->SetFont(font);
    grid->SetColSize(0, 100);  // Mã sách
    grid->SetColSize(1, 250);  // Tên sách
    grid->SetColSize(2, 150);  // Tác giả
    grid->SetColSize(3, 200);  // Nhà xuất bản
    grid->SetColSize(4, 100);  // Giá bán
    grid->SetColSize(5, 150);  // Năm phát hành
    grid->SetColSize(6, 100);  // Số trang
    grid->SetColSize(7, 150);  // Ngày nhập kho
    grid->SetColSize(8, 140);  // Tình trạng
    // Create a sizer to arrange the controls
    Bind(wxEVT_CHAR_HOOK, &ShowBook::OnKeyDown, this);
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(grid, 3, wxEXPAND | wxALL, 10);
    panel->SetSizer(sizer);
}




        /******************************
         * Quay về màng hình quản lý *
        *******************************/
        void BackToManage(wxCommandEvent& event);

        void OnKeyDown(wxKeyEvent& event) {
            if (event.GetKeyCode() == WXK_ESCAPE) {
                GoBack();
            } else {
                event.Skip();
            }
        }

        void OnBackButtonClicked(wxCommandEvent& event) {
            GoBack();
        }

        void GoBack();
};
/******************************************
    Thêm sách
*******************************************/
class AddBook : public wxFrame{
    public:
        AddBook(const wxString& title) : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(1450, 880)){
            /******************************************
             * Trang trí giao diện
             * Tiêu đề
             * Các ô nhập liệu
            *******************************************/
        wxPanel* panel = new wxPanel(this);
        wxStaticText* titleLabel = new wxStaticText(panel, wxID_ANY, "ENTER NEW BOOK",wxPoint(525, 100), wxSize(200, 30));
        wxFont font(wxFontInfo(50).Bold());
        titleLabel->SetFont(font);
        wxFont normal(wxFontInfo(30).Bold());
        wxStaticText* label = new wxStaticText(panel, wxID_ANY,"BOOK LABEL:",wxPoint(525,200),wxSize(200,30));
        wxStaticText* name = new wxStaticText(panel, wxID_ANY,"BOOK NAME:",wxPoint(525,250),wxSize(200,30));
        wxStaticText* author = new wxStaticText(panel, wxID_ANY,"AUTHOR:",wxPoint(525,300),wxSize(200,30));
        wxStaticText* pub = new wxStaticText(panel, wxID_ANY,"PUBLISHER:",wxPoint(525,350),wxSize(200,30));
        wxStaticText* price = new wxStaticText(panel, wxID_ANY,"PRICE:",wxPoint(525,400),wxSize(200,30));
        wxStaticText* date = new wxStaticText(panel, wxID_ANY,"DATE RELEASE:",wxPoint(525,450),wxSize(200,30));
        wxStaticText* number = new wxStaticText(panel, wxID_ANY,"PAGES NUMBER:",wxPoint(525,500),wxSize(200,30));
        wxStaticText* recipt = new wxStaticText(panel, wxID_ANY,"RECIPT DAY:",wxPoint(525,550),wxSize(200,30));
        label->SetFont(normal);
        name->SetFont(normal);
        author->SetFont(normal);
        pub->SetFont(normal);
        price->SetFont(normal);
        date->SetFont(normal);
        number->SetFont(normal);
        recipt->SetFont(normal);
        BookLabel = new wxTextCtrl(panel, wxID_ANY, "",wxPoint(800, 200), wxSize(200, 30));
        BookName = new wxTextCtrl(panel, wxID_ANY, "",wxPoint(800, 250), wxSize(200, 30));
        Author = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(800, 300), wxSize(200, 30));
        Publisher = new wxTextCtrl(panel, wxID_ANY, "",wxPoint(800, 350), wxSize(200, 30));
        Price = new wxTextCtrl(panel, wxID_ANY, "",wxPoint(800, 400), wxSize(200, 30));
        Date = new wxTextCtrl(panel, wxID_ANY, "",wxPoint(800, 450), wxSize(200, 30));
        Number = new wxTextCtrl(panel, wxID_ANY, "",wxPoint(800, 500), wxSize(200, 30));
        Receipt = new wxTextCtrl(panel, wxID_ANY, "",wxPoint(800, 550), wxSize(200, 30));
        wxButton* backButton = new wxButton(panel, wxID_ANY, "BACK", wxPoint(550, 650), wxSize(200, 30));
        backButton->Bind(wxEVT_BUTTON, &AddBook::BackToManage, this, backButton->GetId());
        wxButton* add = new wxButton(panel, wxID_ANY, "ADD",wxPoint(800, 650), wxSize(200, 30));
        add->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {AddToFile(event);});
    }
    /*Quay về màng hình quản lý*/
    void BackToManage(wxCommandEvent& event);
    /******************************************
     * Thêm sách vào file txt
     * nhận giá trị nhập vào
     * chuyển thành kiểu chuỗi
     * kiểm tra xem sách được nhập có trong kia hay chưa
     * Không có thì tiến hành thêm vào file txt
    *******************************************/
    void AddToFile(wxCommandEvent& event){
        wxString label = BookLabel->GetValue();
        wxString name = BookName->GetValue();
        wxString author = Author->GetValue();
        wxString publisher = Publisher->GetValue();
        wxString price = Price->GetValue();
        wxString date = Date->GetValue();
        wxString number = Number->GetValue();
        wxString receipt = Receipt->GetValue();
        string labelString = label.ToStdString();
        string nameString = name.ToStdString();
        string authorString = author.ToStdString();
        string publisherString = publisher.ToStdString();
        string priceString = price.ToStdString();
        string dateString = date.ToStdString();
        string numberString = number.ToStdString();
        string receiptString = receipt.ToStdString();
        string BookExist = "book/" + labelString + ".txt";
        if (fs::exists(BookExist)) {
            wxMessageBox("Mã sách đã tồn tại", "Lỗi nhập sách", wxOK | wxICON_ERROR);
            label.Clear();
            name.Clear();
            author.Clear();
            publisher.Clear();
            price.Clear();
            date.Clear();
            number.Clear();
            receipt.Clear();
            return;
        } else{
        ofstream file;
        string FileName = "book/"+labelString+".txt";
        file.open(FileName);
        file << left << setw(30) << labelString << setw(30) << nameString << setw(30) << authorString << setw(30) << publisherString << setw(30) << priceString << setw(30) << dateString<< setw(30) << numberString << setw(30) << receiptString << setw(30) << 0 << endl;
        file.close();
        wxMessageBox("Đã thêm sách", "Thông báo", wxOK | wxICON_ERROR);
        }
    }
    private:
        wxTextCtrl* BookLabel;
        wxTextCtrl* BookName;
        wxTextCtrl* Author;
        wxTextCtrl* Publisher;
        wxTextCtrl* Price;
        wxTextCtrl* Date;
        wxTextCtrl* Receipt;
        wxTextCtrl* Number;
};
/******************************************
    Xoá sách
*******************************************/
class DeleteBook : public wxFrame{
    public:
        DeleteBook(const wxString& title): wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(1450, 880)){
        /******************************************
         * Trang trí giao diện
         * Ô nhập mã sách muốn xoá
         * Nút quay về
         * Nút xoá
        *******************************************/
        wxPanel* panel = new wxPanel(this);
        wxFont font(wxFontInfo(50).Bold());
        wxFont normal(wxFontInfo(30).Bold());
        wxButton* ShowBookLabel= new wxButton(panel, wxID_ANY, "Book label", wxPoint(900, 300), wxSize(200, 30));
        ShowBookLabel->Bind(wxEVT_BUTTON, &DeleteBook::ShowBookLabel, this, ShowBookLabel->GetId());
        wxStaticText* titleLabel = new wxStaticText(panel, wxID_ANY, "ENTER BOOK WANT TO DELETE",wxPoint(350, 100), wxSize(200, 30));
        titleLabel->SetFont(font);
        wxStaticText* text = new wxStaticText(panel,wxID_ANY,"BOOK LABEL",wxPoint(400,300),wxSize(200,30));
        BookLabel = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(650, 300), wxSize(200, 30));
        text->SetFont(normal);
        wxButton* backButton = new wxButton(panel, wxID_ANY, "BACK", wxPoint(500, 400), wxSize(200, 30));
        backButton->Bind(wxEVT_BUTTON, &DeleteBook::BackToManage, this, backButton->GetId());
        wxButton* deletebook = new wxButton(panel, wxID_ANY, "DELETE", wxPoint(800, 400), wxSize(200, 30));
        deletebook->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {  Delete(event); });
    }
    /******************************************
     * Quay về màng hình chính
    *******************************************/
    void BackToManage(wxCommandEvent& event);
    /******************************************
     * Hàm xoá sách
     * nhận giá trị vừa nhập
     * chuyển thành kiểu chuỗi
     * kiểm tra và tiến hành xoá
    *******************************************/
    void Delete(wxCommandEvent& event) {
    wxString label = BookLabel->GetValue();
    string labelString = label.ToStdString();
    string FileName = "book/" + labelString + ".txt";

    // Mở tệp tin để đọc
    ifstream file(FileName);
    if (!file) {
        wxMessageBox("CANNOT OPEN FILE", "Thông báo", wxOK | wxICON_ERROR);
        return;
    }

    // Đọc toàn bộ nội dung tệp tin
    string fileContent, line;
    while (getline(file, line)) {
        fileContent += line + "\n";
    }

    // Xóa kí tự trống cuối cùng nếu có
    if (!fileContent.empty() && fileContent[fileContent.length() - 1] == '\n') {
        fileContent = fileContent.substr(0, fileContent.length() - 1);
    }

    // Kiểm tra kí tự cuối cùng
    if (!fileContent.empty() && fileContent.back() == '0') {

        remove(FileName.c_str());
        wxMessageBox("BOOK HAS BEEN DELETED", "NOTICE", wxOK | wxICON_INFORMATION);
    } else {
        wxMessageBox("BOOK HAS BEEN BORROWED", "NOTICE", wxOK | wxICON_INFORMATION);
    }

    // Đóng tệp tin
    file.close();

    label.Clear();
}
    /******************************************
     * Hiển thị các mã sách có trong kho
     * Lặp qua các file cái nào có đuôi.txt
     * thì hiện lên
    *******************************************/
    void ShowBookLabel(wxCommandEvent& event){
        wxString fileList;
        for (const auto& entry : fs::directory_iterator("book/")) {
            if (entry.path().extension() == ".txt") {
                fileList += entry.path().filename().string() + "\n";
            }
        }
        wxMessageDialog dialog(this, fileList, "Danh sách mã sách", wxOK | wxICON_INFORMATION);
        dialog.ShowModal();
    }
    private:
        wxTextCtrl* BookLabel;
        int NumberBook;
};
/******************************************
    Giao diện đăng nhập
*******************************************/
class LoginDisplay : public wxFrame {
public:
    LoginDisplay(const wxString& title, MainFrame* mainFrame): wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(1450, 880)),mainFrame(mainFrame) {
        /******************************************
         * Trang trí giao diện
         * Tiêu đề
         * Ô nhập liệu
         * Nút quay về
         * Nút đăng nhập
        *******************************************/
        wxPanel* panel = new wxPanel(this);
        wxStaticText* titleLabel = new wxStaticText(this, wxID_ANY, "LOGIN DISPLAY",wxPoint(525, 100), wxSize(300, 200));
        wxFont font(wxFontInfo(50).Bold());
        titleLabel->SetFont(font);
        wxStaticText* user = new wxStaticText(this,wxID_ANY,"USER NAME: ",wxPoint(500,300),wxSize(0,30));
        wxFont normal(wxFontInfo(30).Bold());
        wxStaticText* pass = new wxStaticText(this,wxID_ANY,"PASSWORD: ",wxPoint(500,400),wxSize(0,30));
        user->SetFont(normal);
        pass->SetFont(normal);
        usernameInput = new wxTextCtrl(this, wxID_ANY, "",wxPoint(700, 300), wxSize(250, 30));
        passwordInput = new wxTextCtrl(this, wxID_ANY, "",wxPoint(700, 400), wxSize(250, 30),wxTE_PASSWORD);
        wxButton* backButton = new wxButton(this, wxID_ANY, "BACK", wxPoint(500, 600), wxSize(200, 30));
        backButton->Bind(wxEVT_BUTTON, &LoginDisplay::BackToMain, this, backButton->GetId());
        wxButton* loginButton = new wxButton(this, wxID_ANY, "LOGIN",wxPoint(750, 600), wxSize(200, 30));
        loginButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {CheckLogin(event);});
    }
    /******************************************
     * giao diện quản lý
    *******************************************/
    void GoToManageDisplay(){
        ManageDisplay* manage = new ManageDisplay("MANAGE DISPLAY");
        manage->Show(true);
        Close();
    }
    /******************************************
     * Quay về màng hình chính
    *******************************************/
    void BackToMain(wxCommandEvent& event);
    /******************************************
     * Kiểm tra đăng nhập
     * Nhận giá trị
     * mở file kiểm tra đúng giá trị chưa
     * đúng thì nhảy đến quản lý
     * Sai thì nhập lại
     * Quá 3 lần thì khoá 30s
    *******************************************/
    void CheckLogin(wxCommandEvent& event) {
        static int Attempt = 3;
        bool login = false;
        wxString username = usernameInput->GetValue();
        wxString password = passwordInput->GetValue();
        string line1, line2;
        ifstream file("quanly.txt");
        if (file.is_open()) {
            getline(file, line1);
            getline(file, line2);
            file.close();
        } else {
            cout << "Can not open file\n";
        }
        if (username == line1 && password == line2) {
            GoToManageDisplay();
            login = true;
        } else {
            usernameInput->Clear();
            passwordInput->Clear();
            if (Attempt > 0) {
                wxMessageBox("Bạn đã nhập sai mật khẩu! Vui lòng thử lại.", "Lỗi đăng nhập", wxOK | wxICON_ERROR);
            }
            Attempt--;
        }
        if (login) {
            //đi đến đăng nhập
        } else if (Attempt == 0) {
            wxMessageBox("PLEASED WAIT 30S", "LOGIN FAIL", wxOK | wxICON_ERROR);
            this_thread::sleep_for(chrono::seconds(30));
            Attempt = 3;
        }
    }
private:
    wxTextCtrl* usernameInput;
    wxTextCtrl* passwordInput;
    MainFrame* mainFrame;
};
/******************************************
    Màng hình chính
*******************************************/
class MainFrame : public wxFrame {
public:
    MainFrame(const wxString& title): wxFrame(nullptr, wxID_ANY, title) {
        /******************************************
         * Trang trí giao diện
         * Tiêu đề
         * 2 nút chức năng
        *******************************************/
        wxStaticText* text = new wxStaticText(this, wxID_ANY, "LIBRARY MANAGEMENT",wxPoint(450, 100), wxSize(300, 200));
        wxPanel* panel = new wxPanel(this);
        SetSizer(new wxBoxSizer(wxVERTICAL));
        GetSizer()->Add(panel, 1, wxEXPAND);
        wxFont font(wxFontInfo(50).Bold());
        text->SetFont(font);
        wxButton* button1 = new wxButton(this, wxID_ANY, "MANAGE",wxPoint(550, 300), wxSize(400, 100));
        button1->Bind(wxEVT_BUTTON, &MainFrame::OnOpenSecondScreen, this, button1->GetId());
        wxButton* button2 = new wxButton(panel, wxID_ANY, "TICKET",wxPoint(550, 500), wxSize(400, 100));
        button2->Bind(wxEVT_BUTTON, &MainFrame::GoToTicketDisplay, this, button2->GetId());
        //esc dể thoát
        Bind(wxEVT_CHAR_HOOK, &MainFrame::OnKeyPress, this);
    }
    /******************************************
     * Nhấn ESC để thoát chương trình
    *******************************************/
    void OnKeyPress(wxKeyEvent& event){
        if (event.GetKeyCode() == WXK_ESCAPE){
            Close();
        }else{
            event.Skip();
        }
    }
    /******************************************
     * Mở màng hình đăng nhập
    *******************************************/
    void OnOpenSecondScreen(wxCommandEvent& event) {
        LoginDisplay* login = new LoginDisplay("LOGIN DISPLAY", this);
        login->Show(true);
        Close();
    }
    /******************************************
     * Mở màng hình quản lý phiếu
    *******************************************/
    void GoToTicketDisplay(wxCommandEvent& event);
    wxDECLARE_EVENT_TABLE();
};
wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_BUTTON(wxID_ANY, MainFrame::OnOpenSecondScreen)
    EVT_CHAR_HOOK(MainFrame::OnKeyPress)
wxEND_EVENT_TABLE()
/******************************************
    Giao diện quản lý phiếu mượn
*******************************************/
class TicketDisplay : public wxFrame{
    public:
        TicketDisplay(const wxString& title): wxFrame(nullptr,wxID_ANY,title,wxDefaultPosition,wxSize(1450,880)){
            /******************************************
             * Trang trí giao diện
             * Tiêu đề
             * 2 nút chức năng
             * nút quay về
            *******************************************/
            wxPanel* panel = new wxPanel(this);
            wxFont font(wxFontInfo(50).Bold());
            wxStaticText* titleLabel = new wxStaticText(panel, wxID_ANY, "TICKET DISPLAY",
            wxPoint(525, 100), wxSize(200, 30));
            titleLabel->SetFont(font);
            wxButton* Button1 = new wxButton(panel, wxID_ANY, "BORROW", wxPoint(625, 300), wxSize(200, 30));
            Button1->Bind(wxEVT_BUTTON, &TicketDisplay::GoToBorrow  , this, Button1->GetId());
            wxButton* Button2 = new wxButton(panel, wxID_ANY, "RESTORE", wxPoint(625, 400), wxSize(200, 30));
            Button2->Bind(wxEVT_BUTTON, &TicketDisplay::GoToRestore  , this, Button2->GetId());
            wxButton* Button3 = new wxButton(panel, wxID_ANY, "MEMBER", wxPoint(625,500),wxSize(200,30));
            Button3->Bind(wxEVT_BUTTON, &TicketDisplay::GoToMember, this, Button3->GetId());
            wxButton* backButton = new wxButton(panel, wxID_ANY, "BACK", wxPoint(625, 600), wxSize(200, 30));
            backButton->Bind(wxEVT_BUTTON, &TicketDisplay::BackToMain, this, backButton->GetId());
        }
        void GoToMember(wxCommandEvent& event);
        /******************************************
         * Quay về màng hình chính
        *******************************************/
        void BackToMain(wxCommandEvent& event){
            MainFrame* mainFrame = new MainFrame("MAIN DISPLAY");
            mainFrame->SetClientSize(1450, 880);
            mainFrame->Center();
            mainFrame->Show(true);
            Close();
        }
        /******************************************
         * Tạo phiếu mượn
         * Trả phiếu mượn
        *******************************************/
        void GoToBorrow(wxCommandEvent& event);
        void GoToRestore(wxCommandEvent& event);
};
/******************************************
    Thông tin người dùng mượn sách
*******************************************/
class UserBorrowBook : public wxFrame{
    public:
        UserBorrowBook(const wxString& title, wxString& name): wxFrame(nullptr,wxID_ANY,title,wxDefaultPosition,wxSize(400,400)){
            /******************************************
             * Trang trí giao diện
             * Tên người mượn
             * ID người mượn
             * Ngày mượn
            *******************************************/

            a.name = name;
            a.date = GetRealTime();
            int Number = GetRandomNumber();
            a.maso = Number;
            wxString number = wxString::Format("%d", Number);
            wxPanel* panel = new wxPanel(this);
            wxFont font(wxFontInfo(15).Bold());
            wxStaticText* person = new wxStaticText(panel, wxID_ANY, name,wxPoint(150, 50), wxSize(200, 30));
            person->SetFont(font);
            wxStaticText* personname = new wxStaticText(panel,wxID_ANY, "Your name is:",wxPoint(50, 50), wxSize(200, 30));
            personname->SetFont(font);

            wxString date = GetRealTime();
            wxStaticText* id = new wxStaticText(panel,wxID_ANY, "Your ID is:", wxPoint(50, 100), wxSize(200, 30));
            id->SetFont(font);
            wxStaticText* num = new wxStaticText(panel,wxID_ANY, number, wxPoint(150,100),wxSize(200,30));
            num->SetFont(font);
            wxStaticText* dateday = new wxStaticText(panel,wxID_ANY, "Today is:",wxPoint(50, 150), wxSize(200, 30));
            dateday->SetFont(font);
            wxStaticText* day = new wxStaticText(panel,wxID_ANY, date, wxPoint(150,150),wxSize(200,30));
            day->SetFont(font);
            //tao o nhap lieu
            wxStaticText* add = new wxStaticText(panel,wxID_ANY, "ADDRESS",wxPoint(50, 200), wxSize(200, 30));
            wxStaticText* phone= new wxStaticText(panel,wxID_ANY, "PHONE",wxPoint(50, 250), wxSize(200, 30));
             ADDRESS = new wxTextCtrl(panel, wxID_ANY, "",wxPoint(150, 200), wxSize(100, 30));
             PHONE = new wxTextCtrl(panel, wxID_ANY, "",wxPoint(150, 250), wxSize(100, 30));
            wxButton* SAVE = new wxButton(panel, wxID_ANY, "SAVE", wxPoint(100, 300), wxSize(200, 30));
            SAVE->Bind(wxEVT_BUTTON, &UserBorrowBook::SAVEINFO, this, SAVE->GetId());
        }
        /******************************************
         * Tạo ID
        *******************************************/
        void SAVEINFO(wxCommandEvent& event){
            string address = ADDRESS->GetValue().ToStdString();
            string phone = PHONE->GetValue().ToStdString();
            a.phone = phone;
            a.Address = address;
            listUser.insert(a);
            //listUser.print();
        }
        int GetRandomNumber(){
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<int> dist(100, 999);
            int maso = dist(gen)*10+1 ;
            return maso;
        }
        /******************************************
            Ngày mượn
        *******************************************/
        string GetRealTime(){
            string date;
            time_t currenttime = time(nullptr);
            tm* time = localtime(&currenttime);
            char buffer[80];
            strftime(buffer,sizeof(buffer), "%d-%m-%Y", time);
            date = buffer;
            return date;
        }
    private:
        user a;
        wxTextCtrl* PHONE;
        wxTextCtrl* ADDRESS;

};
/******************************************
    Taọ phiếu mượn sách
*******************************************/
class BorrowBook : public wxFrame {
public:
    BorrowBook(const wxString& title): wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(1450, 880)){
        /******************************************
         * Trang trí giao diện
         * Nhập tên người dùng
         * Nhấn continue sẽ hiện ra tên người dùng
         * và màng hình tạo phiếu mượn
        *******************************************/
        wxPanel* panel = new wxPanel(this);
        wxFont font(wxFontInfo(30).Bold());
        wxStaticText* nameLabel = new wxStaticText(panel, wxID_ANY, "Enter Your Name:",wxPoint(100, 100), wxSize(200, 30));
        nameLabel->SetFont(font);
        nameTextCtrl = new wxTextCtrl(panel, wxID_ANY, "",wxPoint(400, 100), wxSize(200, 30));
        wxButton* continueButton = new wxButton(panel, wxID_ANY, "Continue", wxPoint(700, 100), wxSize(200, 30));
        continueButton->Bind(wxEVT_BUTTON, &BorrowBook::OnContinue, this, continueButton->GetId());
        wxButton* back = new wxButton(panel,wxID_ANY,"BACK",wxPoint(1000, 100), wxSize(200, 30));
        back->Bind(wxEVT_BUTTON, &BorrowBook::BackToTicketDisplay, this, back->GetId());
    }
    /******************************************
     * Quay về màng hình quản lý phiếu mượn
    *******************************************/
    void BackToTicketDisplay(wxCommandEvent& event){
            TicketDisplay* ticket = new TicketDisplay("TICKET DISPLAY");
            ticket->Show(true);
            Close();
        }
    /******************************************
     * Nhập tên người dùng xong sẽ hiện ra
     * các ô nhập liệu
     * và tạo phiếu mượn
    *******************************************/
    void OnContinue(wxCommandEvent& event){
        wxString name = nameTextCtrl->GetValue();
        string namelist = name.ToStdString();
        if (name.IsEmpty()) {
            wxMessageBox("Please enter your name.", "Error", wxOK | wxICON_ERROR);
        }
        else if(!listUser.contains(namelist)) {

            wxMessageBox("Welcome, " + name + "!", "Success", wxOK | wxICON_INFORMATION);
            nameTextCtrl->Clear();
            UserBorrowBook* user = new UserBorrowBook("USER",name);
            user->Show(true);
            /******************************************
             * Tiếp tục tạo phiếu mượn
            *******************************************/
            wxStaticText* text = new wxStaticText(this,wxID_ANY,"BORROW TICKET",wxPoint(525, 200), wxSize(200, 30));
            wxFont font(wxFontInfo(50).Bold());
            wxFont normal(wxFontInfo(30).Bold());
            text->SetFont(font);
            wxStaticText* id = new wxStaticText(this, wxID_ANY, "USER ID:",
            wxPoint(500, 300), wxSize(200, 30));
            wxStaticText* pass = new wxStaticText(this, wxID_ANY, "BOOK LABEL:",
            wxPoint(500, 350), wxSize(200, 30));
            id->SetFont(normal);
            pass->SetFont(normal);
            UserID = new wxTextCtrl(this, wxID_ANY, "user id",
            wxPoint(725, 300), wxSize(200, 30));
            BookLabel= new wxTextCtrl(this, wxID_ANY, "book label",
            wxPoint(725, 350), wxSize(200, 30));
            wxButton* borrow = new wxButton(this,wxID_ANY,"BORROW",wxPoint(600, 500), wxSize(200, 30));
            borrow->Bind(wxEVT_BUTTON, &BorrowBook::Muon, this, borrow->GetId());
        }
    }
    /******************************************
     * Tạo số phiếu mượn
    *******************************************/
    int NumberTicket(){
        static int SoPhieuMuon = 1;
        ifstream File;
        while(true){
            string TenPhieuMuon = "PhieuMuon/PhieuMuon" + to_string(SoPhieuMuon) + ".txt";
            File.open(TenPhieuMuon);
            if(File){
                File.close();
                SoPhieuMuon++;
            } else {
                break;
            }
        }
        return SoPhieuMuon;
    }
    /******************************************
     * Tạo phiếu mượn
    *******************************************/
    void Muon(wxCommandEvent& event) {
        string kyTuThayThe = UserID->GetValue().ToStdString();
        string tenFile = BookLabel->GetValue().ToStdString();
        string MaSoPhieuMuon = to_string(NumberTicket());
        string File = "book/"+tenFile+".txt";
        ifstream inputFile(File);
        if (!inputFile.is_open()) {
            wxMessageBox("CANNOT CREATE FILE", "Thong bao", wxOK | wxICON_ERROR);
            cout << "Lỗi: Không thể mở file." << endl;
            UserID->Clear();
            BookLabel->Clear();
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
                //printFail();
                return;
            }
        } else {
            wxMessageBox("BOOK HAS BEEN BORROWED", "Thong bao", wxOK | wxICON_ERROR);
            cout << "BOOK HAS BEEN BORROWED." << endl;
            UserID->Clear();
            BookLabel->Clear();
            //printSuccessful();
            return;
        }
        if (canMuonSach) {
        } else {
            wxMessageBox("CANNOT BORROW", "Thong bao", wxOK | wxICON_ERROR);
            cout << "Không thể mượn sách." << endl;
            UserID->Clear();
            BookLabel->Clear();
            //printFail();
            return;
        }
        ofstream putFile(File, ios::trunc);
        if (!putFile.is_open()) {
            wxMessageBox("CANNOT OPEN FILE", "Thong bao", wxOK | wxICON_ERROR);
            cout << "Lỗi: Không thể mở file." << endl;
            UserID->Clear();
            BookLabel->Clear();
            return;
        }
        putFile << duLieu;
        putFile.close();
        string tenPhieuMuon = "PhieuMuon/PhieuMuon" + MaSoPhieuMuon + ".txt";
        ofstream outputFile(tenPhieuMuon);
        if (!outputFile.is_open()) {
            wxMessageBox("CANNOT CREATE TICKET", "Thong bao", wxOK | wxICON_ERROR);
            cout << "Lỗi: Không thể tạo phiếu mượn." << endl;
            UserID->Clear();
            BookLabel->Clear();
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
        //printSuccessful();
        wxMessageBox("TICKET SUCCESSFULLY CREATED", "Thong bao", wxOK | wxICON_ERROR);
        cout << "TICKET SUCCESSFULLY CREATED." << endl;
        UserID->Clear();
        BookLabel->Clear();
    }
private:
    wxTextCtrl* nameTextCtrl;
    wxTextCtrl* UserID;
    wxTextCtrl* BookLabel;

};
/******************************************
    Trả phiếu mượn
*******************************************/
class RestoreDisplay : public wxFrame{
    public:
    RestoreDisplay(const wxString& title): wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(1450, 880)){
        /******************************************
         * Trang trí giao diện
         * Tiêu đề
         * Nhập mã phiếu
         * Nhập mã sách
        *******************************************/
        wxPanel* panel = new wxPanel(this);
        wxFont font(wxFontInfo(50).Bold());
        wxFont normal(wxFontInfo(30).Bold());
        wxStaticText* text = new wxStaticText(panel,wxID_ANY,"RESTORE",wxPoint(600, 40), wxSize(100, 30));
        text->SetFont(font);
        wxStaticText* num = new wxStaticText(panel,wxID_ANY,"NUMBER TICKET:",wxPoint(450, 300), wxSize(100, 30));
        num->SetFont(normal);
        NumberTicket = new wxTextCtrl(panel,wxID_ANY,"",wxPoint(750, 300), wxSize(200, 30));
        wxStaticText* label = new wxStaticText(panel,wxID_ANY,"BOOK LABEL:",wxPoint(450, 350), wxSize(100, 30));
        label->SetFont(normal);
        BookLabel = new wxTextCtrl(panel,wxID_ANY,"",wxPoint(750, 350), wxSize(200, 30));
        wxButton* restore = new wxButton(panel,wxID_ANY,"RESTORE",wxPoint(550, 400), wxSize(100, 30));
        restore->Bind(wxEVT_BUTTON, &RestoreDisplay::RestoreFunction, this, restore->GetId());
        wxButton* back = new wxButton(panel,wxID_ANY,"BACK",wxPoint(750, 400), wxSize(100, 30));
        back->Bind(wxEVT_BUTTON, &RestoreDisplay::BackToTicketDisplay, this, back->GetId());
    }
    /******************************************
     * Quay về màng hình quản lý phiếu mượn
    *******************************************/
    void BackToTicketDisplay(wxCommandEvent& event) {
        TicketDisplay* ticket = new TicketDisplay("TICKET DISPLAY");
        ticket->Show(true);
        Close();
    }
    /******************************************
     * Hàm trả sách
     * Nhận giá trị
     * Kiểm tra đúng số phiếu hay không
     * Tiến hành tạo phiếu mượn
    *******************************************/
    void RestoreFunction(wxCommandEvent& event){
        string numberticket = NumberTicket->GetValue().ToStdString();
        string MaSach = BookLabel->GetValue().ToStdString();
        if (numberticket.empty() || MaSach.empty()) {
            wxMessageBox("Vui lòng nhập giá trị cho NumberTicket và BookLabel", "Lỗi", wxOK | wxICON_ERROR);
            return;
        }
        int SoPhieuMuon = stoi(numberticket);
        string ten_tep = "PhieuMuon/PhieuMuon" + to_string(SoPhieuMuon) + ".txt";
        fstream file(ten_tep, ios::in | ios::out);
        if (!file.is_open()) {
            wxMessageBox("Không thể tìm thấy phiếu mượn này", "Lỗi", wxOK | wxICON_ERROR);
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
        string fileBook = "book/" + MaSach + ".txt";
        ifstream inputFile(fileBook);
        if (!inputFile.is_open()) {
            wxMessageBox("Không thể tìm thấy sách này", "Lỗi", wxOK | wxICON_ERROR);
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
            wxMessageBox("Sách đã được mượn", "Lỗi", wxOK | wxICON_ERROR);
            return;
        }
        ofstream putFile(fileBook, ios::trunc);
        if (!putFile.is_open()) {
            wxMessageBox("Lỗi hệ thống", "Lỗi", wxOK | wxICON_ERROR);
            return;
        }
        putFile << duLieu;
        putFile.close();
        if (daThayThe) {
            wxMessageBox("Đã khôi phục thành công", "Thông báo", wxOK | wxICON_ERROR);
        } else {
            wxMessageBox("Sách đã được khôi phục trước đó", "Thông báo", wxOK | wxICON_ERROR);
        }
    }
    private:
        wxTextCtrl* NumberTicket;
        wxTextCtrl* BookLabel;
};






class Member : public wxFrame {
public:
   Member(const wxString& title) : wxFrame(NULL, wxID_ANY, title) {
    // Set the frame size and create a panel
    SetSize(wxSize(1450, 880));
    wxPanel* panel = new wxPanel(this, wxID_ANY);

    // Create a grid to display user information
    wxGrid* grid = new wxGrid(panel, wxID_ANY);
    grid->CreateGrid(listUser.getSize(), 5); // Tạo lưới với 5 cột (tên, mã số, địa chỉ, số điện thoại, ngày mượn)

    // Set column labels
    grid->SetColLabelValue(0, "Tên");
    grid->SetColLabelValue(1, "Mã số");
    grid->SetColLabelValue(2, "Địa chỉ");
    grid->SetColLabelValue(3, "Số điện thoại");
    grid->SetColLabelValue(4, "Ngày mượn");

    // Populate the grid with user information
    UserNode* current = listUser.getHead();
    int row = 0;
    while (current != nullptr) {
        grid->SetCellValue(row, 0, wxString::FromUTF8(current->data.getName().c_str()));
        grid->SetCellValue(row, 1, wxString::Format("%d", current->data.getMaso()));
        grid->SetCellValue(row, 2, wxString::FromUTF8(current->data.getAddress().c_str()));
        grid->SetCellValue(row, 3, wxString::FromUTF8(current->data.getPhone().c_str()));
        grid->SetCellValue(row, 4, wxString::FromUTF8(current->data.gettime().c_str()));
        current = current->next;
        row++;
    }

    // Set the font for the grid
    wxFont font(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    grid->SetFont(font);

    grid->SetColSize(0, 270);  // Mã sách
    grid->SetColSize(1, 270);  // Tên sách
    grid->SetColSize(2, 270);  // Tác giả
    grid->SetColSize(3, 270);  // Nhà xuất bản
    grid->SetColSize(4, 270);  // Giá bán
    // Create a sizer to arrange the controls
    Bind(wxEVT_CHAR_HOOK, &Member::OnKeyDown, this);
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(grid, 1, wxEXPAND | wxALL, 10);
    panel->SetSizer(sizer);
}
void OnKeyDown(wxKeyEvent& event) {
    if (event.GetKeyCode() == WXK_ESCAPE) {
        GoBack();
    } else {
        event.Skip();
    }
}

void OnBackButtonClicked(wxCommandEvent& event) {
    GoBack();
}

void GoBack() {
    // Thực hiện các hành động cần thiết để quay lại trang trước đó
    TicketDisplay* ticket = new TicketDisplay("TICKET DISPLAY");
    ticket->Show(true);
    Close();
}




};



/******************************************
 * Hàm main chạy chương trình
*******************************************/
class App : public wxApp {
public:
    bool OnInit() {
        MainFrame* mainFrame = new MainFrame("MAIN DISPLAY");
        mainFrame->SetClientSize(1450, 880);
        mainFrame->Center();
        mainFrame->Show();
        return true;
    }
};
void TicketDisplay::GoToMember(wxCommandEvent& event){
    Member* member = new Member("MEMBER DISPLAY");
    member->Show(true);
    Close();
}
void TicketDisplay::GoToRestore(wxCommandEvent& event){
    RestoreDisplay* restore = new RestoreDisplay("RESTORE DISPLAY");
    restore->Show(true);
    Close();
}
void LoginDisplay::BackToMain(wxCommandEvent& event) {
    MainFrame* mainFrame = new MainFrame("MAIN DISPLAY");
    mainFrame->SetClientSize(1450, 880);
    mainFrame->Center();
    mainFrame->Show(true);
    Close();
}
void ManageDisplay::BackToMain(wxCommandEvent& event) {
    MainFrame* mainFrame = new MainFrame("MAIN DISPLAY");
    mainFrame->SetClientSize(1450, 880);
    mainFrame->Center();
    mainFrame->Show(true);
    Close();
}
void ShowBook::BackToManage(wxCommandEvent& event){
    ManageDisplay* manage = new ManageDisplay("MANAGE DISPLAY");
    manage->Show(true);
    Close();
}
void ManageDisplay::GoToShowBook(wxCommandEvent& event){
    ShowBook* show = new ShowBook("MANAGE DISPLAY");
    show->Show(true);
    Close();
}
void ManageDisplay::GoToAddBook(wxCommandEvent& event){
    AddBook* add = new AddBook("ADD BOOK");
    add->Show(true);
    Close();
}
void ManageDisplay::GoToDelete(wxCommandEvent& event){
    DeleteBook* dele = new DeleteBook("DELETE BOOK");
    dele->Show(true);
    Close();
}
void AddBook::BackToManage(wxCommandEvent& event){
    ManageDisplay* manage = new ManageDisplay("MANAGE DISPLAY");
    manage->Show(true);
    Close();
}
void DeleteBook::BackToManage(wxCommandEvent& event){
    ManageDisplay* manage = new ManageDisplay("MANAGE DISPLAY");
    manage->Show(true);
    Close();
}
void MainFrame::GoToTicketDisplay(wxCommandEvent& event){
    TicketDisplay* ticket = new TicketDisplay("TICKET DISPLAY");
    ticket->Show(true);
    Close();
}
void TicketDisplay::GoToBorrow(wxCommandEvent& event){
    BorrowBook* borrow = new BorrowBook("BORROW BOOK");
    borrow->Show(true);
    Close();
}
void ShowBook::GoBack() {
    // Thực hiện các hành động cần thiết để quay lại trang trước đó
    ManageDisplay* manage = new ManageDisplay("MANAGE DISPLAY");
    manage->Show(true);
    Close();
}
/******************************************
 * Chạy chương trình
*******************************************/
wxIMPLEMENT_APP(App);





