// Hệ thống quản lý thư viện bởi team 8
#include <iostream>
using namespace std;

struct date{
    int d;
    int m;
    int y;
};

struct book {// struct thông tin sách bao gồm tên, các kiểu{
    string tenSach;
    string theLoai;
    string tenTacGia;
    string nxb;
    int namPhatHanh; // check year
    friend istream &operator>>(istream &inputInfo, book &thongTin){ // phải có tham chiếu & đề thay đổi biến randomday
        cout << "Nhap ten sach: ";
        inputInfo >> thongTin.tenSach;
        cout << "Nhap the loai sach: ";
        inputInfo >> thongTin.theLoai;
        cout << "Nhap ten tac gia: ";
        inputInfo >> thongTin.tenTacGia;
        cout << "Nhap nha xuat ban: ";
        inputInfo >> thongTin.nxb;
        do{
            cout << "Nhap nam phat hanh: ";
            inputInfo >> thongTin.namPhatHanh;
        } while (thongTin.namPhatHanh < 1);
        cout << "                   "<< '\n';
        return inputInfo;
    }
    void inSach(){
        cout << " " << tenSach << " " << tenTacGia << " " << theLoai << " " << nxb << " " << namPhatHanh << '\n';
    }
};

struct bookBorRe{
    book name;
    char borName[50];
    date borDay;
    date reDay;
};
void inThongTinSach(int n, book mangSach[]);
void hamSearchSach (int n, book mangSach[]);
void searchTheoThongTin(int search, int n, book mangSach[]);

int main()
{
    book mangChuaSach[100];
    int soLuongSachTrongMang = 0; // số lượng của sách sau mỗi lần nhập, vd lần đâu là 0 -> 1 ->...n sách (index)

    char ad;
    cout << "Ban la admin hay khong la admin \n";
    cout << "Neu la Admin, vui long dang nhap \"a\" de thuc hien cac tinh nang quan tri \n";
    cout << "Neu ban kh la Admin, vui long dang nhap \"b\" \n";
    // ở chổ này tạm thời log in tui chua suy nghĩ ra, nên mình làm thời dùng kết quả = d để dùng cho if -> từ if = d -> thuc hien cac tinh năng của admin 
    cout <<"Moi ban nhap: ";
    cin.get(ad);
    if (ad == 'a'){
        while (1){
            int n;
            cout << "----------------------DU AN QUAN LY SACH----------------------\n";
            cout << "1. Them sach \n";
            cout << "2. Tim sach \n";
            cout << "3. Quan ly thu vien \n";
            cout << "0.Exit \n";
            cout << "------------------------------------------------------------\n";
            cout << "Chon so phu hop voi lua chon: ";
            cin >> n;
            if (n == 1){
                cout << "Moi ban nhap thong tin sach \n";
                cin >> mangChuaSach[soLuongSachTrongMang];
                soLuongSachTrongMang++;
            }
            if (n == 2){
                hamSearchSach(soLuongSachTrongMang + 1, mangChuaSach); 
                // cộng 1 bởi vì số lượng sách trong mảng được khởi tạo từ 0 - tức vị trí index -> nên phải cộng 1 giá trị
            }
            if (n == 3){
            }
            if (n == 0){
                break;
            }
        }
    } 

    if (ad == 'b'){
        while (1){
            int n;
            cout << "----------------------DU AN QUAN LY SACH----------------------\n";
            cout << "1. Tim sach \n";
            cout << "0.Exit \n";
            cout << "------------------------------------------------------------\n";
            cout << "Chon so phu hop voi lua chon: ";
            cin >> n;
            if ( n == 1){
                hamSearchSach(soLuongSachTrongMang + 1,mangChuaSach);
            }
            if ( n == 0){
                break;
            }
        }       
    }
}
void inThongTinSach(int n, book mangSach[]){
    cout << "Thong tin sach: \n";
    for (int i = 0; i < n; i++)
    {
        mangSach[i].inSach();
        cout << '\n';
    }
}

void hamSearchSach(int n, book mangSach[]){
    int search;
    cout << "Chon thong tin ban muon tim kiem \n";
    cout << "Ten sach      - chon '1' \n";
    cout << "Ten tac gia   - chon '2' \n";
    cout << "The loai      - chon '3' \n";
    cout << "Nha xuat ban  - chon '4' \n";
    cout << "Nam phat hanh - chon '5' \n"; // tinh nang lam sau
    cout << "Thoat         - chon '0' \n";
    cout << "Moi ban chon: ";
    cin >> search;
    searchTheoThongTin(search, n, mangSach);
}

void searchTheoThongTin(int search, int n, book mangSach[]){
    string data;
    if (search = 1)
    {
        cout << "Moi ban nhap ten sach: ";
        getline(cin, data);
        bool checkTimThongTin = false; // tra ve false neu kh tim duoc
        for (int i = 0; i < n; i++)
        {
            if (mangSach[i].tenSach.find(data) != string::npos)

            {                            // hàm find, nếu nội dung của data trung với tenSach -> trả ra giá trị đầu tiên
                checkTimThongTin = true; // npos, tức không tìm được vị trí index của tenSach trùng với data
                mangSach[i].inSach();
            }
        }
        if (checkTimThongTin == false)
        {
            cout << "Sach khong co trong thu vien !";
        }
    }
    if (search = 2)
    {
        cout << "Moi ban nhap ten tac gia: ";
        getline(cin, data);
        bool checkTimThongTin = false; // tra ve false neu kh tim duoc
        for (int i = 0; i < n; i++)
        {
            if (mangSach[i].tenTacGia.find(data) != string::npos)
            {                            // hàm find, nếu nội dung của data trung với tenSach -> trả ra giá trị đầu tiên
                checkTimThongTin = true; // npos, tức không tìm được vị trí index của tenSach trùng với data
                mangSach[i].inSach();
            }
        }
        if (checkTimThongTin == false)
        {
            cout << "Sach cua tac gia nay hien chua co trong thu vien !";
        }
    }
    if (search = 3)
    {
        cout << "Moi ban nhap the loai: ";
        getline(cin, data);
        bool checkTimThongTin = false; // tra ve false neu kh tim duoc
        for (int i = 0; i < n; i++)
        {
            if (mangSach[i].theLoai.find(data) != string::npos)
            {                            // hàm find, nếu nội dung của data trung với tenSach -> trả ra giá trị đầu tiên
                checkTimThongTin = true; // npos, tức không tìm được vị trí index của tenSach trùng với data
                mangSach[i].inSach();
            }
        }
        if (checkTimThongTin == false)
        {
            cout << "The loai khong co trong thu vien!";
        }
    }
    if (search = 4)
    {
        cout << "Moi ban nhap nha xuat ban : ";
        getline(cin, data);
        bool checkTimThongTin = false; // tra ve false neu kh tim duoc
        for (int i = 0; i < n; i++)
        {
            if (mangSach[i].nxb.find(data) != string::npos)
            {                            // hàm find, nếu nội dung của data trung với tenSach -> trả ra giá trị đầu tiên
                checkTimThongTin = true; // npos, tức không tìm được vị trí index của tenSach trùng với data
                mangSach[i].inSach();
            }
        }
        if (checkTimThongTin == false)
        {
            cout << "Nha xuat ban sach nay khong co trong thu vien !";
        }
    }
}