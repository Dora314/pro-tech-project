// Hệ thống quản lý thư viện bởi team 8
#include <bits/stdc++.h>
using namespace std;
struct date
{
    int d;
    int m;
    int y;
};
struct book
{
    string tenSach;
    string theLoai;
    string tenTacGia;
    string nxb;
    int namPhatHanh; // check year

    friend istream &operator>>(istream &inputInfo, book &thongTin)
    { // phải có tham chiếu & đề thay đổi biến
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
        cout << "                   " << '\n';
        return inputInfo;
    }
};
struct bookBorRe
{
    book sachMuonTra; // lay ten sach
    string borName;   // ten nguoi muon
    date borDay;      // ngay muon
    date reDay;       // ngay den han
};
void xuatFile(book a[]);
void nhapFile(book a[]);
// void xuatFile(bookBorRe b[]);
// void xuatFile(bookBorRe b[]);
void hoiAdmin(char &chAd);
void dangNhapKyAdmin();
void inThongTinSach(int n, book mangSach[]);
void hamSearchSach(int n, book mangSach[]);
void searchTheoThongTin(int search, int n, book mangSach[]);
void quanLy(int n, bookBorRe mangMuonTra[]);

int main()
{
    char chAd;
    book mangChuaSach[5000];
    bookBorRe mangMuonTra[5000];
    int soLuongSach, tinhNang;
    hoiAdmin(chAd); // kiểm tra có phải admin hay không -> truyền tham chiếu chAd
    nhapFile(mangChuaSach);
    switch (chAd)
    {
    case 'y':
    case 'Y':
        dangNhapKyAdmin();
    nhapLai:
        system("cls"); // xoa man hinh giong clrscr trong pascal
        cout << "\nMoi chon tinh nang\n";
        cout << "Tim kiem sach              - chon '1' \n";
        cout << "Nhap sach vao thu vien     - chon '2' \n";
        cout << "Quan ly muon tra sach      - chon '3' \n";
        cout << "Xin moi nhap tinh nang theo so: ";
        cin >> tinhNang;
        system("cls");
        switch (tinhNang)
        {
        case 1:
            hamSearchSach(soLuongSach, mangChuaSach);
            goto nhapLai;
        case 2:
            xuatFile(mangChuaSach);
            goto nhapLai;
        case 3:
            // nhapFile(mangMuonTra);
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
    return 0;
}
void hoiAdmin(char &chAd)
{
    bool admin = false;
    do
    {
        cout << "\nBan co phai la admin khong(y/n)? ";
        cin.get(chAd);
        if (chAd == 'y' || chAd == 'n' || chAd == 'Y' || chAd == 'N')
            admin = true;
        else
            cout << "Vui long nhap lai! " << endl;
    } while (admin == false);
    system("cls");
}

void dangNhapKyAdmin()
{
    bool quyenAdmin = false;
    char username[100];
    char passMacDinh[] = "LamHandsome";
    char nhapPass[100];
    char userMacDinh[] = "admin";
    do
    {
        cout << "\nNhap ten dang nhap: ";
        cin.ignore();
        cin.getline(username, 99);
        cout << "\nMoi ban nhap mat khau: ";
        cin.getline(nhapPass, 99);
        if (strcmp(passMacDinh, nhapPass) == 0 && strcmp(userMacDinh, username) == 0)
            quyenAdmin = true;
        else
            cout << "\nTai khoan hoac mat khau sai. Vui long nhap lai.";
    } while (quyenAdmin == false);
}
void xuatFile(book a[])
{
    fstream fout;
    int n;
    fout.open("fileChuaSach.csv", ios::out | ios::app);
    cout << "Nhap thong tin ve sach\n-------------------------------------------------------";
    cout << "\nNhap so luong sach can nhap: ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        system("cls");
        cout << "Nhap ten sach thu " << i + 1 << ": ";
        cin.ignore();
        getline(cin, a[i].tenSach);
        cout << "Nhap ten the loai: ";
        getline(cin, a[i].theLoai);
        cout << "Nhap ten tac gia: ";
        getline(cin, a[i].tenTacGia);
        cout << "Nhap ten nha xuat ban: ";
        getline(cin, a[i].nxb);
        do
        {
            cout << "Nhap nam phat hanh: ";
            cin >> a[i].namPhatHanh;
        } while (a[i].namPhatHanh < 1);
        fout << a[i].tenSach << "," << a[i].theLoai << "," << a[i].tenTacGia << "," << a[i].nxb << "," << a[i].namPhatHanh << "\n";
    }
    fout.close();
}
void nhapFile(book a[])
{
    fstream fin;
    fin.open("fileChuaSach.csv", ios::in);
    int n = 0;
    if (fin.is_open())
    {
        while (getline(fin, a[n].tenSach, ',') && getline(fin, a[n].theLoai, ',') && getline(fin, a[n].tenTacGia, ',') && getline(fin, a[n].nxb, ',') && fin >> a[n].namPhatHanh)
            n++;
        fin.close();
    }
    else
        cout << "Error. Vui long khoi dong lai chuong trinh.";
    int i = 0;
    while (n--)
    {
        cout << left << setw(35) << a[i].tenSach << "\t" << left << setw(15) << a[i].theLoai << setw(30) << a[i].tenTacGia << setw(20) << a[i].nxb << right << setw(5) << a[i].namPhatHanh << endl;
        i++;
    }
}
// void xuatFile(bookBorRe b[]);
// void xuatFile(bookBorRe b[]);
void inThongTinSach(int n, book mangSach[])
{ // in thông tin sách trong mảng book
    cout << "Thong tin sach: \n";
    for (int i = 0; i < n; i++)
        cout << mangSach[i].tenSach << " " << mangSach[i].tenTacGia << " " << mangSach[i].theLoai << " " << mangSach[i].nxb << " " << mangSach[i].namPhatHanh << '\n';
}

void hamSearchSach(int n, book mangSach[])
{
    int search;
    cout << "\nChon thong tin ban muon tim kiem\n";
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

void searchTheoThongTin(int search, int n, book mangSach[])
{
    string data;
    bool checkTimThongTin = false; // tra ve false neu kh tim duoc
    cin.ignore();
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
                cout << mangSach[i].tenSach << " " << mangSach[i].tenTacGia << " " << mangSach[i].theLoai << " " << mangSach[i].nxb << " " << mangSach[i].namPhatHanh << '\n';
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
            cout << "Moi ban nhap nam xuat ban : ";
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
    bool checkTimThongTin = false;
nhapLai:
    cout << "\nQuan ly sach: muon tra, so luong sach, xem sach hien co \n";
    cout << "Ten nguoi muon          - chon '1'\n";
    cout << "Quan ly so luong sach   - chon '2'\n";
    cout << "Quay lai chon tinh nang - chon '0'\n";
    cout << "Moi ban chon: ";
    cin >> search;
    switch (search)
    {
    case 1:
        cout << "Moi ban nhap ten nguoi muon: ";
        cin.ignore();
        getline(cin, data);
        for (int i = 0; i < n; i++)
            if (mangMuonTra[i].borName.find(data) != string::npos)
            {                            // hàm find, nếu nội dung của data trung với tenNguoiMuon -> trả ra giá trị đầu tiên
                checkTimThongTin = true; // npos, tức không tìm được vị trí index của tenNguoiMuon trùng với data
                cout << mangMuonTra[i].sachMuonTra.tenSach << "    " << mangMuonTra[i].borName << "    " << mangMuonTra[i].borDay.d << "/" << mangMuonTra[i].borDay.m << "/" << mangMuonTra[i].borDay.y << "    " << mangMuonTra[i].reDay.d << "/" << mangMuonTra[i].reDay.m << "/" << mangMuonTra[i].reDay.y << "\n";
            }
        if (checkTimThongTin == false)
            cout << "Khong tim thay nguoi muon sach !";
        goto nhapLai;
    case 2:
        cout << "Moi ban nhap ten sach: ";
        cin.ignore();
        getline(cin, data);
        for (int i = 0; i < n; i++)
            if (mangMuonTra[i].sachMuonTra.tenSach.find(data) != string::npos)
            {                            // hàm find, nếu nội dung của data trung với tenSach -> trả ra giá trị đầu tiên
                checkTimThongTin = true; // npos, tức không tìm được vị trí index của tenSach trùng với data
                cout << mangMuonTra[i].sachMuonTra.tenSach << "    " << mangMuonTra[i].borName << "    " << mangMuonTra[i].borDay.d << "/" << mangMuonTra[i].borDay.m << "/" << mangMuonTra[i].borDay.y << "    " << mangMuonTra[i].reDay.d << "/" << mangMuonTra[i].reDay.m << "/" << mangMuonTra[i].reDay.y << "\n";
            }
        if (checkTimThongTin == false)
            cout << "Sach khong co trong thu vien !";
        goto nhapLai;
    case 0:
        cout << "Dang tro lai chon tinh nang...";
        break;
    default:
        cout << "Lua chon khong hop le. Vui long chon lai.";
        goto nhapLai;
    }
}
// làm sao để khi quản ly xong exit ra ngoài main(chon tinh nang?) á\/done nhé + và thông tin người mượn ở đâu