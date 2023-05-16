// Hệ thống quản lý thư viện bởi team 8
#include <bits/stdc++.h>
using namespace std;
#define endl "\n" // gán \n cho endl
struct book       // file chua sach
{
    string tenSach;
    string theLoai;
    string tenTacGia;
    string nxb;
    string namPhatHanh; // check year
};
struct bookBorRe // file quan ly
{
    string tenSach; // lay ten sach
    string borName; // ten nguoi muon
    string borDay;  // ngay muon
    string reDay;   // ngay den han
};
void xuatFile();
void docFile(int &n, book a[]);
void xuatFile2();
void docFile2(int &n, bookBorRe b[]);
void hoiAdmin(int &chAd);
void dangNhapKyAdmin(bool &quyenAdmin);
void inSach(int i, book a[]);
void inMuonTra(int i, bookBorRe b[]);         // i la vi tri tai phan tu can in ra console
void inThongTinSach(int n, book a[]);         // a[] la mang chua sach
void inThongTinMuonTra(int n, bookBorRe b[]); // b[] la mang muon tra
void hamSearchSach(int n, book mangSach[]);
void searchTheoThongTin(int search, int n, book mangSach[]);
void quanLy(int n, book mangChuaSach[], int n1, bookBorRe mangMuonTra[]);

int main()
{
    int chAd;
    book mangChuaSach[5000];
    bookBorRe mangMuonTra[5000];
    int tinhNang;
    int soLuongSach, soLuongSachMuon;
    bool quyenAdmin = false;
    cout << "CHAO MUNG DEN VOI DU AN QUAN LY THU VIEN CUA TEAM 8!\n";
    cout << "__________________________________________________________________________\n";
hoiAdmin:
    hoiAdmin(chAd); // kiểm tra có phải admin hay không -> truyền tham chiếu chAd
    switch (chAd)
    {
    case 1:
    {
        dangNhapKyAdmin(quyenAdmin);
        if (quyenAdmin == true)
        {
        nhapLai:
            system("cls"); // xoa man hinh giong clrscr trong pascal
            cout << "\nMOI CHON TINH NANG\n";
            cout << "Tim kiem sach              - chon '1' \n";
            cout << "Nhap sach vao thu vien     - chon '2' \n";
            cout << "Quan ly sach               - chon '3' \n";
            cout << "Thoat                      - chon '0' \n";
            // xoa sach trong tuong lai
            cout << "Xin moi nhap tinh nang theo so: ";
            cin >> tinhNang;
            system("cls");
            switch (tinhNang)
            {
            case 1:
                docFile(soLuongSach, mangChuaSach);
                hamSearchSach(soLuongSach, mangChuaSach);
                goto nhapLai;
            case 2:
                xuatFile();
                goto nhapLai;
            case 3:
                docFile(soLuongSach, mangChuaSach);
                docFile2(soLuongSachMuon, mangMuonTra);
                quanLy(soLuongSach, mangChuaSach, soLuongSachMuon, mangMuonTra);
                goto nhapLai;
            case 0:
                goto end;
            default:
                cout << "\nVui long nhap lai.\n";
                system("pause");
                goto nhapLai;
            }
        }
        else
            goto hoiAdmin;
    }
    case 0:
    {
    nhapLai1:
        system("cls"); // xoa man hinh giong clrscr trong pascal
        cout << "\nMOI CHON TINH NANG\n";
        cout << "Tim kiem sach       - chon '1' \n";
        cout << "Thoat               - chon '0' \n";
        cout << "Xin moi nhap tinh nang theo so: ";
        cin >> tinhNang;
        system("cls");
        switch (tinhNang)
        {
        case 1:
        {
            int soSach = 0;
            docFile(soSach, mangChuaSach);
            hamSearchSach(soSach, mangChuaSach); // non-admin chi duoc tim kiem sach
            goto nhapLai1;
        }
        case 0:
            goto end;
        default:
            cout << "\n\nVui long nhap lai!\n\n";
            system("pause");
            goto nhapLai1;
        }
    }
    }
end:
    system("cls");
    cout << "\n\nCam on da su dung chuong trinh! Xin chao va hen gap lai!\n_____________________________________\n\n";
    system("pause");
    return 0;
}
void hoiAdmin(int &chAd)
{
    bool admin = false;
    do
    {
        cout << "\nBan co phai la admin khong (Nhap 1 = CO, 0 = KHONG)? ";
        cin >> chAd;
        if (chAd == 1 || chAd == 0)
            admin = true;
        else
            cout << "Vui long nhap lai! " << endl;
    } while (admin == false);
    system("cls");
}

void dangNhapKyAdmin(bool &quyenAdmin)
{
    char username[100];
    char nhapPass[100];
    char userMacDinh[] = "admin";
    char passMacDinh[] = "LamBeauty";
    int check;
    cin.ignore(1);
again:
    int times = 3;
    do
    {
        cout << "\nNhap ten dang nhap: ";
        cin.getline(username, 99);
        cout << "\nMoi ban nhap mat khau: ";
        cin.getline(nhapPass, 99);
        if (strcmp(passMacDinh, nhapPass) == 0 && strcmp(userMacDinh, username) == 0)
            quyenAdmin = true;
        else
        {
            times--;
            cout << "\nTen tai khoan hoac mat khau sai. Vui long nhap lai.\n";
            if (times == 0)
            {
                do
                {
                    cout << "\nBan co muon roi tinh nang dang nhap khong (Nhap 1 = CO, 0 = KHONG)? ";
                    cin >> check;
                    if (check == 1)
                        goto ended;
                    else if (check == 0)
                    {
                        goto again;
                        system("cls");
                    }
                    else
                        cout << "\nVui long nhap lai.\n";
                } while (!(check == 0 && check == 1));
            } // quay ve hoi admin
        }
    } while (quyenAdmin == false);
ended:
    cout << "\nDang chay...\n\n";
    system("cls");
}
void xuatFile()
{
    fstream fout;
    int n, namPhatHanh;
    fout.open("fileChuaSach.csv", ios::out | ios::app);
    cout << "Nhap thong tin ve sach\n-------------------------------------------------------";
    cout << "\nNhap so luong sach can nhap: ";
    cin >> n;
    book mangSach[n];
    for (int i = 0; i < n; i++)
    {
        system("cls");
        cout << "Nhap ten sach thu " << i + 1 << ": ";
        cin.ignore();
        getline(cin, mangSach[i].tenSach);
        cout << "Nhap ten the loai: ";
        getline(cin, mangSach[i].theLoai);
        cout << "Nhap ten tac gia: ";
        getline(cin, mangSach[i].tenTacGia);
        cout << "Nhap ten nha xuat ban: ";
        getline(cin, mangSach[i].nxb);
        do
        {
            cout << "Nhap nam phat hanh: ";
            cin >> namPhatHanh;
        } while (namPhatHanh < 1);
        fout << mangSach[i].tenSach << "," << mangSach[i].theLoai << "," << mangSach[i].tenTacGia << "," << mangSach[i].nxb << "," << namPhatHanh << "\n";
    }
    fout.close();
}
void docFile(int &n, book mangSach[])
{
    fstream fin;
    fin.open("fileChuaSach.csv", ios::in);
    n = 0;
    if (fin.is_open())
    {
        while (getline(fin, mangSach[n].tenSach, ',') && getline(fin, mangSach[n].theLoai, ',') && getline(fin, mangSach[n].tenTacGia, ',') && getline(fin, mangSach[n].nxb, ',') && getline(fin, mangSach[n].namPhatHanh))
            n++;
        fin.close();
    }
    else
        cout << "Error. Vui long khoi dong lai chuong trinh.";
}
void xuatFile2()
{
    fstream fout;
    int n;
    fout.open("fileQuanLy.csv", ios::out | ios::app);
    cout << "Nhap thong tin ve sach cho muon\n-------------------------------------------------------";
    cout << "\nNhap so luong sach can nhap: ";
    cin >> n;
    bookBorRe b[n];
    cin.ignore();
    time_t now = time(0); // lay thoi gian hien tai
    tm *ltm = localtime(&now);
    for (int i = 0; i < n; i++)
    {
        system("cls");
        cout << "Nhap ten sach thu " << i + 1 << ": ";
        getline(cin, b[i].tenSach);
        cout << "Nhap ten nguoi muon: ";
        getline(cin, b[i].borName);
        fout << b[i].tenSach << "," << b[i].borName << "," << ltm->tm_mday << "-" << 1 + ltm->tm_mon << "-" << 1900 + ltm->tm_year << "," << ltm->tm_mday << "-" << 2 + ltm->tm_mon << "-" << 1900 + ltm->tm_year << endl;
    }
    fout.close();
}
void docFile2(int &n1, bookBorRe b[])
{
    fstream fin;
    fin.open("fileQuanLy.csv", ios::in);
    n1 = 0;
    if (fin.is_open())
    {
        while (getline(fin, b[n1].tenSach, ',') && getline(fin, b[n1].borName, ',') && getline(fin, b[n1].borDay, ',') && getline(fin, b[n1].reDay))
            n1++;
        fin.close();
    }
    else
        cout << "Error. Vui long khoi dong lai chuong trinh.";
}
void inSach(int i, book a[])
{
    cout << endl;
    cout << a[i].tenSach << endl;
    cout << "The loai: " << a[i].theLoai << endl;
    cout << "Ten tac gia: " << a[i].tenTacGia << endl;
    cout << "Nha xuat ban: " << a[i].nxb << endl;
    cout << "Nam phat hanh: " << a[i].namPhatHanh << "\n\n";
}
void inMuonTra(int i, bookBorRe b[])
{
    cout << endl;
    cout << b[i].tenSach << endl;
    cout << "Ten nguoi muon: " << b[i].borName << endl;
    cout << "Ngay muon: " << b[i].borDay << endl;
    cout << "Ngay den han: " << b[i].reDay << "\n\n";
}
void inThongTinSach(int n, book a[])
{ // in thông tin sách trong mảng book
    cout << "Thong tin sach hien co\n---------------------------------------" << endl;
    cout << endl;
    for (int i = 0; i < n; i++)
        inSach(i, a);
}
void inThongTinMuonTra(int n, bookBorRe b[])
{ // in thông tin sách trong mảng book
    cout << "Thong tin sach hien co\n---------------------------------------" << endl;
    cout << endl;
    for (int i = 0; i < n; i++)
        inMuonTra(i, b);
}
void hamSearchSach(int n, book mangSach[])
{
    int search;
    cout << "\nChon thong tin ban muon tim kiem\n";
    cout << "Ten sach      - chon '1' \n";
    cout << "The loai      - chon '2' \n";
    cout << "Ten tac gia   - chon '3' \n";
    cout << "Nha xuat ban  - chon '4' \n";
    cout << "Nam phat hanh - chon '5' \n"; // tinh nang lam sau
    cout << "Thoat         - chon '0' \n";
    do
    {
        cout << "Moi ban chon: ";
        cin >> search;
        if (search == 0 || search == 1 || search == 2 || search == 3 || search == 4 || search == 5)
            break;
        else
            cout << "Lua chon khong hop le!!!\n\n";
    } while (search != 0 || search != 1 || search != 2 || search != 3 || search != 4 || search != 5);
    system("cls");
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
        cout << endl;
        transform(data.begin(), data.end(), data.begin(), ::tolower); // hàm chuyển sang lowercase, dùng cho string only (LƯU Ý: cần có thư viện bits để dùng)
        for (int i = 0; i < n; i++)
        {
            transform(mangSach[i].tenSach.begin(), mangSach[i].tenSach.end(), mangSach[i].tenSach.begin(), ::tolower);
            if (mangSach[i].tenSach.find(data) != string::npos)
            {                            // hàm find, nếu nội dung của data trung với tenSach -> trả ra giá trị đầu tiên //data = ora (0123) -> doraemon (01234567 ->8)         find(oea)
                checkTimThongTin = true; // npos, tức không tìm được vị trí index của tenSach trùng với data
                inSach(i, mangSach);
            }
        }
        if (checkTimThongTin == false)
            cout << "Sach khong co trong thu vien !\n";
        system("pause");
        break;
    case 2:
        cout << "Moi ban nhap the loai: ";
        getline(cin, data);
        cout << endl;
        transform(data.begin(), data.end(), data.begin(), ::tolower);
        for (int i = 0; i < n; i++)
        {
            transform(mangSach[i].theLoai.begin(), mangSach[i].theLoai.end(), mangSach[i].theLoai.begin(), ::tolower);
            if (mangSach[i].theLoai.find(data) != string::npos)
            {
                checkTimThongTin = true;
                inSach(i, mangSach);
            }
        }
        if (checkTimThongTin == false)
            cout << "The loai khong co trong thu vien!\n";
        system("pause");
        break;
    case 3:
        cout << "Moi ban nhap ten tac gia: ";
        getline(cin, data);
        cout << endl;
        transform(data.begin(), data.end(), data.begin(), ::tolower);
        for (int i = 0; i < n; i++)
        {
            transform(mangSach[i].tenTacGia.begin(), mangSach[i].tenTacGia.end(), mangSach[i].tenTacGia.begin(), ::tolower);
            if (mangSach[i].tenTacGia.find(data) != string::npos)
            {
                checkTimThongTin = true;
                inSach(i, mangSach);
            }
        }
        if (checkTimThongTin == false)
            cout << "Sach cua tac gia nay hien chua co trong thu vien !\n";
        system("pause");
        break;
    case 4:
        cout << "Moi ban nhap nha xuat ban : ";
        getline(cin, data);
        cout << endl;
        transform(data.begin(), data.end(), data.begin(), ::tolower);
        for (int i = 0; i < n; i++)
        {
            transform(mangSach[i].nxb.begin(), mangSach[i].nxb.end(), mangSach[i].nxb.begin(), ::tolower);

            if (mangSach[i].nxb.find(data) != string::npos)
            {
                checkTimThongTin = true;
                inSach(i, mangSach);
            }
        }
        if (checkTimThongTin == false)
            cout << "Nha xuat ban sach nay khong co trong thu vien !\n";
        system("pause");
        break;
    case 5:
        int year;
        do
        {
            cout << "Moi ban nhap nam xuat ban : ";
            cin >> year;
        } while (year < 1);
        cout << endl;
        for (int i = 0; i < n; i++)
        {
            if (stoi(mangSach[i].namPhatHanh) == year) // chuyen tu string sang integer
            {
                checkTimThongTin = true;
                inSach(i, mangSach);
            }
        }
        if (checkTimThongTin == false)
            cout << "Thu vien hien khong co sach cua nam nay !\n";
        system("pause");
        break;
    case 0:
        cout << "Dang thoat chuong trinh....\n\n";
        break;
    }
}

void quanLy(int n, book mangChuaSach[], int soLuongSachMuon, bookBorRe mangMuonTra[])
{
    int search;
    string data;
    bool checkTimThongTin = false;
nhapLai:
    system("cls");
    cout << "\nQUAN LY SACH\n_______________________________________________\n";
    cout << "Tra cuu muon tra theo ten sach            - chon '1'\n";
    cout << "Tra cuu muon tra theo ten nguoi muon      - chon '2'\n";
    cout << "Thong tin sach hien co                    - chon '3'\n";
    cout << "Thong tin sach dang duoc muon             - chon '4'\n";
    cout << "Them nguoi muon sach                      - chon '5'\n";
    cout << "Quay lai chon tinh nang                   - chon '0'\n";
    do
    {
        cout << "Moi ban chon: ";
        cin >> search;
        if (search == 0 || search == 1 || search == 2 || search == 3 || search == 4 || search == 5)
            break;
        else
            cout << "Lua chon khong hop le !\n";
    } while (!(search == 0 || search == 1 || search == 2 || search == 3 || search == 4 || search == 5));
    cin.ignore();
    system("cls");
    switch (search)
    {
    case 1:
        cout << "Moi ban nhap ten sach: ";
        getline(cin, data);
        cout << endl;
        // hàm transform
        transform(data.begin(), data.end(), data.begin(), ::tolower); // hàm chuyển sang lowercase, dùng cho string only (LƯU Ý: cần có thư viện bits để dùng)
        for (int i = 0; i < soLuongSachMuon; i++)
        {
            transform(mangMuonTra[i].tenSach.begin(), mangMuonTra[i].tenSach.end(), mangMuonTra[i].tenSach.begin(), ::tolower);
            if (mangMuonTra[i].tenSach.find(data) != string::npos)
            {                            // hàm find, nếu nội dung của data trung với tenSach -> trả ra giá trị đầu tiên
                checkTimThongTin = true; // npos, tức không tìm được vị trí index của tenSach trùng với data
                inMuonTra(i, mangMuonTra);
            }
        }
        if (checkTimThongTin == false)
            cout << "Quyen sach nay van chua duoc muon !\n";
        system("pause");
        goto nhapLai;
    case 2:
        cout << "Moi ban nhap ten nguoi muon: ";
        getline(cin, data);
        cout << endl;
        transform(data.begin(), data.end(), data.begin(), ::tolower); // hàm chuyển sang lowercase, dùng cho string only (LƯU Ý: cần có thư viện bits để dùng)
        for (int i = 0; i < soLuongSachMuon; i++)
        {
            transform(mangMuonTra[i].borName.begin(), mangMuonTra[i].borName.end(), mangMuonTra[i].borName.begin(), ::tolower);
            if (mangMuonTra[i].borName.find(data) != string::npos)
            {
                checkTimThongTin = true;
                inMuonTra(i, mangMuonTra);
            }
        }
        if (checkTimThongTin == false)
            cout << "Khong tim thay ten nguoi muon !\n";
        system("pause");
        goto nhapLai;
    case 3:
        cout << "So luong sach hien co la " << n << endl;
        do
        {
            cout << "In tat ca thong tin ve sach hien co (Nhap 1 = CO, 0 = KHONG)? ";
            cin >> search;
            if (!(search == 1 || search == 0))
                cout << "Vui long nhap lai!" << endl;
        } while (!(search == 1 || search == 0));
        if (search == 1)
            inThongTinSach(n, mangChuaSach);
        system("pause");
        goto nhapLai;
    case 4:
        cout << "So luong sach hien dang duoc muon la " << soLuongSachMuon << endl;
        do
        {
            cout << "In tat ca thong tin ve sach hien co (Nhap 1 = CO, 0 = KHONG)? ";
            cin >> search;
            if (!(search == 1 || search == 0))
                cout << "Vui long nhap lai!" << endl;
        } while (!(search == 1 || search == 0));
        if (search == 1)
            inThongTinMuonTra(soLuongSachMuon, mangMuonTra);
        system("pause");
        goto nhapLai;
    case 5:
        xuatFile2();
        goto nhapLai;
    case 0:
        break;
    default:
        cout << "\nLua chon khong hop le. Vui long chon lai.\n";
        goto nhapLai;
    }
}
