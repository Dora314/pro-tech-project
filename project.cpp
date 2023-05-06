// Hệ thống quản lý thư viện bởi team 8
#include <bits/stdc++.h>
#include <fstream>
using namespace std;

struct date{ // 
    int d;
    int m;
    int y;
};
struct book {// struct thông tin sách bao gồm tên, các kiểu
    string tenSach;
    string theLoai;
    string tenTacGia;
    string nxb;
    int namPhatHanh; // check year
  
    friend istream &operator>>(istream &inputInfo, book &thongTin){ // phải có tham chiếu & đề thay đổi biến 
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
struct bookBorRe
{
    book sachMuonTra; // lay ten sach
    string borName;   // ten nguoi muon
    date borDay;      // ngay muon
    date reDay;       // ngay den han
};

void hoiAdmin(char &chAd);
void dangNhapKyAdmin(bool quyenAdmin);
void inThongTinSach(int n, book mangSach[]);
void hamSearchSach(int n, book mangSach[]);
void searchTheoThongTin(int search, int n, book mangSach[]);
void quanLy(int n, bookBorRe mangMuonTra[]);

//void nhapXuat(void);         => hàm này chưa viết  

int main()
{
    char chAd;
    bool quyenAdmin = false; 
    book mangChuaSach[100];
    bookBorRe mangMuonTra[100];
    int soLuongSach , tinhNang;
    hoiAdmin(chAd); // kiểm tra có phải admin hay không -> truyền tham chiếu chAd
    switch (chAd)
    {
    case 'y':
    case 'Y':
    nhapLai:
        dangNhapKyAdmin(quyenAdmin);
        cout << "\nMoi chon tinh nang\n";
        cout << "Tim kiem sach              - chon '1' \n";
        cout << "Nhap sach vao thu vien     - chon '2' \n";
        cout << "Quan ly muon tra sach      - chon '3' \n";
        cout << "Xin moi nhap tinh nang theo so: ";
        cin >> tinhNang;
        switch (tinhNang)
        {
        case 1:
            hamSearchSach(soLuongSach, mangChuaSach);
            goto nhapLai;
        case 2:
            //nhapXuat(); => chưa viết
            goto nhapLai;
        case 3:
            quanLy(soLuongSach, mangMuonTra);
            goto nhapLai;
        default:
            cout << "\nVui long nhap lai.\n";
            goto nhapLai;
        }
    case 'n':
    case 'N':
        hamSearchSach(soLuongSach, mangChuaSach); // non-admin chi duoc tim kiem sach
        break;
    default:
        cout << "Vui long khoi dong lai chuong trinh.";
        break;
    }

    cout << "Nhap so luong sach: ";
    cin >> soLuongSach;
    for (int i = 0; i < soLuongSach; i++)
    {
        cout << "Moi ban nhap thong tin sach \n";
        cin >> mangChuaSach[i];
    }
    hamSearchSach(soLuongSach, mangChuaSach);
    return 0;
}
void hoiAdmin(char &chAd){ // có gì sao truyền ta, rồi nó return cái gì ? 
    cout << "\nBan co phai la admin(y/n)? ";
    cin.get(chAd);
    do
    {
        cout << "Vui long nhap lai(y/n) ";
        cin.get(chAd);
    } while (chAd != 'y' || chAd != 'n' || chAd != 'Y' || chAd != 'N');
}

void dangNhapKyAdmin(bool quyenAdmin)  
{
    char username[100];
    char passMacDinh[] = "LamHandsome";
    char nhapPass[100];
    char userMacDinh[] = "admin";
    do
    {
        cout << "\nNhap ten dang nhap: ";
        cin.getline(username, 99);
        cout << "\nMoi ban nhap mat khau: ";
        cin.getline(nhapPass, 99);
        if (strcmp(passMacDinh, nhapPass) == 0 && strcmp(userMacDinh, username) == 0)
            quyenAdmin = true;
        else
            cout << "\nTai khoan hoac mat khau sai. Vui long nhap lai.";
    } while (quyenAdmin == false);
}

void inThongTinSach(int n, book mangSach[]){ // in thông tin sách trong mảng book
    cout << "Thong tin sach: \n"; 
    for (int i = 0; i < n; i++)
    {
        mangSach[i].inSach();
        cout << '\n';
    }
}

void hamSearchSach(int n, book mangSach[]){
    int search;
    cout << "Chon thong tin ban muon tim kiem\n";
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
    bool checkTimThongTin = false; // tra ve false neu kh tim duoc
    switch (search)
    {
    case 1:
        cout << "Moi ban nhap ten sach: ";
        getline(cin, data);
        for (int i = 0; i < n; i++)
        {
            if (mangSach[i].tenSach.find(data) != string::npos)
            {                            // hàm find, nếu nội dung của data trung với tenSach -> trả ra giá trị đầu tiên
                checkTimThongTin = true; // npos, tức không tìm được vị trí index của tenSach trùng với data
                cout << " " << mangSach[i].tenSach << " " << mangSach[i].tenTacGia << " " << mangSach[i].theLoai << " " << mangSach[i].nxb << " " << mangSach[i].namPhatHanh << '\n';  
            }
        }
        if (checkTimThongTin == false)
        {
            cout << "Sach khong co trong thu vien !";
        }
        break;
    case 2: 
        cout << "Moi ban nhap ten tac gia: ";
        getline(cin, data);
        for (int i = 0; i < n; i++)
        {
            if (mangSach[i].tenTacGia.find(data) != string::npos)
            {                            
                checkTimThongTin = true; 
                cout << " " << mangSach[i].tenSach << " " << mangSach[i].tenTacGia << " " << mangSach[i].theLoai << " " << mangSach[i].nxb << " " << mangSach[i].namPhatHanh << '\n';  
            }
        }
        if (checkTimThongTin == false)
        {
            cout << "Sach cua tac gia nay hien chua co trong thu vien !";
        }
        break;
    case 3:
        cout << "Moi ban nhap the loai: ";
        getline(cin, data);
        bool checkTimThongTin = false; 
        for (int i = 0; i < n; i++)
        {
            if (mangSach[i].theLoai.find(data) != string::npos)
            {                            
                checkTimThongTin = true; 
                cout << " " << mangSach[i].tenSach << " " << mangSach[i].tenTacGia << " " << mangSach[i].theLoai << " " << mangSach[i].nxb << " " << mangSach[i].namPhatHanh << '\n';  
            }
        }
        if (checkTimThongTin == false)
        {
            cout << "The loai khong co trong thu vien!";
        }
        break;
    case 4:
        cout << "Moi ban nhap nha xuat ban : ";
        getline(cin, data);
        for (int i = 0; i < n; i++)
        {
            if (mangSach[i].nxb.find(data) != string::npos)
            {                           
                checkTimThongTin = true; 
                cout << " " << mangSach[i].tenSach << " " << mangSach[i].tenTacGia << " " << mangSach[i].theLoai << " " << mangSach[i].nxb << " " << mangSach[i].namPhatHanh << '\n';  
            }
        }
        if (checkTimThongTin == false)
        {
            cout << "Nha xuat ban sach nay khong co trong thu vien !";
        }
        break;
    case 5:
        int year;
        do 
        {
            cout << "Moi ban nhap nha xuat ban : ";
            cin >> year;
        } while (year < 1);
        for (int i = 0; i < n; i++)
        {
            if (mangSach[i].namPhatHanh == year)
            {                           
                checkTimThongTin = true; 
                cout << " " << mangSach[i].tenSach << " " << mangSach[i].tenTacGia << " " << mangSach[i].theLoai << " " << mangSach[i].nxb << " " << mangSach[i].namPhatHanh << '\n';  
            }
        
        }
        if (checkTimThongTin == false)
        {
            cout << "Thu vien hien khong co sach cua nam nay !";
        }
        break;   
    default:
        cout << "Lua chon cua ban khong hop le !!!";
        break;
    }
}

void quanLy(int n, bookBorRe mangMuonTra[])
{
    int search;
    string data;
nhapLai:
    cout << "\nQuan ly sach: muon tra, so luong sach, xem sach hien co \n";
    cout << "Ten nguoi muon         - chon '1' \n";
    cout << "Quan ly so luong sach  - chon '2' \n";
    cout << "Moi ban chon: ";
    cin >> search;
    switch (search)
    {
    case 1:
        cout << "Moi ban nhap ten nguoi muon: ";
        cin.ignore();
        getline(cin, data);
        bool checkTimThongTin = false; // tra ve false neu kh tim duoc
        for (int i = 0; i < n; i++)
            if (mangMuonTra[i].borName.find(data) != string::npos)
            {                            // hàm find, nếu nội dung của data trung với tenSach -> trả ra giá trị đầu tiên
                checkTimThongTin = true; // npos, tức không tìm được vị trí index của tenSach trùng với data
                cout << mangMuonTra[i].sachMuonTra.tenSach << "    " << mangMuonTra[i].borName << "    " << mangMuonTra[i].borDay.d << "/" << mangMuonTra[i].borDay.m << "/" << mangMuonTra[i].borDay.y << "    " << mangMuonTra[i].reDay.d << "/" << mangMuonTra[i].reDay.m << "/" << mangMuonTra[i].reDay.y << "\n";
            }
        if (checkTimThongTin == false)
            cout << "Khong tim thay nguoi muon sach !";
        goto nhapLai;
    case 2:
        cout << "Moi ban nhap ten sach: ";
        cin.ignore();
        getline(cin, data);
        bool checkTimThongTin = false; // tra ve false neu kh tim duoc
        for (int i = 0; i < n; i++)
            if (mangMuonTra[i].sachMuonTra.tenSach.find(data) != string::npos)
            {                            // hàm find, nếu nội dung của data trung với tenSach -> trả ra giá trị đầu tiên
                checkTimThongTin = true; // npos, tức không tìm được vị trí index của tenSach trùng với data
                cout << mangMuonTra[i].sachMuonTra.tenSach << "    " << mangMuonTra[i].borName << "    " << mangMuonTra[i].borDay.d << "/" << mangMuonTra[i].borDay.m << "/" << mangMuonTra[i].borDay.y << "    " << mangMuonTra[i].reDay.d << "/" << mangMuonTra[i].reDay.m << "/" << mangMuonTra[i].reDay.y << "\n";
            }
        if (checkTimThongTin == false)
            cout << "Sach khong co trong thu vien !";
        goto nhapLai;
    default:
        cout << "Lua chon khong hop le. Vui long chon lai.";
        goto nhapLai;
    }
}
// làm sao để khi quản ly xong exit ra ngoài main á ? + và thông tin người mượn ở đâu 