// Hệ thống quản lý thư viện bởi team 8
#include <bits/stdc++.h>
using namespace std;
struct date
{
    int d;
    int m;
    int y;
};
struct book // struct thông tin sách bao gồm tên, các kiểu
{
    string tenSach;
    string theLoai;
    string tenTacGia;
    string nxb;
    int namPhatHanh; // check year
    friend istream &operator>>(istream &inputInfo, book &thongTin)
    { // phải có tham chiếu & đề thay đổi biến randomday
        cout << "Nhap ten sach: ";
        inputInfo >> thongTin.tenSach;
        cout << "Nhap the loai sach: ";
        inputInfo >> thongTin.theLoai;
        cout << "Nhap ten tac gia: ";
        inputInfo >> thongTin.tenTacGia;
        cout << "Nhap nha xuat ban: ";
        inputInfo >> thongTin.nxb;
        do
        {
            cout << "Nhap nam phat hanh: ";
            inputInfo >> thongTin.namPhatHanh;
        } while (thongTin.namPhatHanh < 1);
        return inputInfo;
    }
    void inSach()
    {
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
void nhapXuat(void);
void quanLy(int n, bookBorRe mangMuonTra[]);
int main()
{
    char chAd;
    bool quyenAdmin = false;
    book mangChuaSach[100];
    bookBorRe mangMuonTra[100];
    int soLuongSach, tinhNang;
    hoiAdmin(chAd); // kiểm tra có phải admin hay không
    switch (chAd)
    {
    case 'y':
    case 'Y':
        dangNhapKyAdmin(quyenAdmin); // kiểm tra để cấp quyền admin
    nhapLai:
        cout << "\nMoi chon tinh nang\n";
        cout << "Tim kiem sach              - chon '1' \n";
        cout << "Nhap sach vao thu vien     - chon '2' \n";
        cout << "Quan ly muon tra sach      - chon '3' \n";
        cout << "Moi nhap ";
        cin >> tinhNang;
        switch (tinhNang)
        {
        case 1:
            hamSearchSach(soLuongSach, mangChuaSach);
            goto nhapLai;
        case 2:
            nhapXuat();
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
    // hamSearchSach(sachObject.tenSach,sachObject.theLoai,sachObject.tenTacGia,sachObject.nxb,sachObject.namPhatHanh);
    return 0;
}
void hoiAdmin(char &chAd)
{
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
void inThongTinSach(int n, book mangSach[])
{
    cout << "Thong tin sach hien co\n";
    for (int i = 0; i < n; i++)
    {
        mangSach[i].inSach();
        cout << '\n';
    }
}
void hamSearchSach(int n, book mangSach[])
{
    int search;
    cout << "Chon thong tin ban muon tim kiem\n";
    cout << "Ten sach      - chon '1' \n";
    cout << "Ten tac gia   - chon '2' \n";
    cout << "The loai      - chon '3' \n";
    cout << "Nha xuat ban  - chon '4' \n";
    cout << "Nam phat hanh - chon '5' \n"; // tinh nang lam sau
    cout << "Moi ban chon: ";
    cin >> search;
    searchTheoThongTin(search, n, mangSach);
}
void searchTheoThongTin(int search, int n, book mangSach[])
{
    string data;
    if (search = 1)
    {
        cout << "Moi ban nhap ten sach: ";
        getline(cin, data);
        bool checkTimThongTin = false; // tra ve false neu kh tim duoc
        for (int i = 0; i < n; i++)
            if (mangSach[i].tenSach.find(data) != string::npos)
            {                            // hàm find, nếu nội dung của data trung với tenSach -> trả ra giá trị đầu tiên
                checkTimThongTin = true; // npos, tức không tìm được vị trí index của tenSach trùng với data
                mangSach[i].inSach();
            }
        if (checkTimThongTin == false)
            cout << "Sach khong co trong thu vien !";
    }
    if (search = 2)
    {
        cout << "Moi ban nhap ten tac gia: ";
        getline(cin, data);
        bool checkTimThongTin = false; // tra ve false neu kh tim duoc
        for (int i = 0; i < n; i++)
            if (mangSach[i].tenTacGia.find(data) != string::npos)
            {                            // hàm find, nếu nội dung của data trung với tenSach -> trả ra giá trị đầu tiên
                checkTimThongTin = true; // npos, tức không tìm được vị trí index của tenSach trùng với data
                mangSach[i].inSach();
            }
        if (checkTimThongTin == false)
            cout << "Sach cua tac gia nay hien chua co trong thu vien !";
    }
    if (search = 3)
    {
        cout << "Moi ban nhap the loai: ";
        getline(cin, data);
        bool checkTimThongTin = false; // tra ve false neu kh tim duoc
        for (int i = 0; i < n; i++)
            if (mangSach[i].theLoai.find(data) != string::npos)
            {                            // hàm find, nếu nội dung của data trung với tenSach -> trả ra giá trị đầu tiên
                checkTimThongTin = true; // npos, tức không tìm được vị trí index của tenSach trùng với data
                mangSach[i].inSach();
            }
        if (checkTimThongTin == false)
            cout << "The loai khong co trong thu vien!";
    }
    if (search = 4)
    {
        cout << "Moi ban nhap nha xuat ban : ";
        getline(cin, data);
        bool checkTimThongTin = false; // tra ve false neu kh tim duoc
        for (int i = 0; i < n; i++)
            if (mangSach[i].nxb.find(data) != string::npos)
            {                            // hàm find, nếu nội dung của data trung với tenSach -> trả ra giá trị đầu tiên
                checkTimThongTin = true; // npos, tức không tìm được vị trí index của tenSach trùng với data
                mangSach[i].inSach();
            }
        if (checkTimThongTin == false)
            cout << "Nha xuat ban sach nay khong co trong thu vien !";
    }
}
void nhapXuat(void)
{
}
void quanLy(int n, bookBorRe mangMuonTra[])
{
    int search;
    string data;
nhapLai:
    cout << "\nQuan ly sach: muon tra, so luong sach, xem sach hien co:";
    cout << "\nTen nguoi muon    - chon '1'";
    cout << "\nTen sach          - chon '2'";
    cout << "\nMoi ban chon: ";
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