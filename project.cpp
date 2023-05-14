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
    int namPhatHanh; // check year
};
struct bookBorRe // file quan ly
{
    string tenSach; // lay ten sach
    string borName; // ten nguoi muon
    string borDay;  // ngay muon
    string reDay;   // ngay den han
};
void xuatFile(book a[]);
void docFile(int &n, book a[]);
void xuatFile2(bookBorRe b[]);
void docFile2(int &n, bookBorRe b[]);
void hoiAdmin(char &chAd);
void dangNhapKyAdmin(bool &quyenAdmin);
void inThongTinSach(int n, book a[]);         // a[] la mang chua sach
void inThongTinMuonTra(int n, bookBorRe b[]); // b[] la mang muon tra
void hamSearchSach(int n, book mangSach[]);
void searchTheoThongTin(int search, int n, book mangSach[]);
void quanLy(int n, book mangChuaSach[], int n1, bookBorRe mangMuonTra[]);

int main()
{
    char chAd;
    book mangChuaSach[5000];
    bookBorRe mangMuonTra[5000];
    int tinhNang;
    bool quyenAdmin = false;
    cout << "Chao mung den voi du an quan ly thu vien cua team 8\n";
hoiAdmin:
    hoiAdmin(chAd); // kiểm tra có phải admin hay không -> truyền tham chiếu chAd
    switch (chAd)
    {
    case 'y':
    case 'Y':
    {
        dangNhapKyAdmin(quyenAdmin);
        if (quyenAdmin == true)
        {
        nhapLai:
            system("cls"); // xoa man hinh giong clrscr trong pascal
            cout << "\nMoi chon tinh nang\n";
            cout << "Tim kiem sach              - chon '1' \n";
            cout << "Nhap sach vao thu vien     - chon '2' \n";
            cout << "Quan ly sach               - chon '3' \n";
            cout << "Thoat                      - chon '0' \n";
            // xoa sach trong tuong lai
            cout << "Xin moi nhap tinh nang theo so: ";
            cin >> tinhNang;
            int soLuongSach = 0, soLuongSach1 = 0;
            docFile(soLuongSach, mangChuaSach);
            system("cls");
            switch (tinhNang)
            {
            case 1:
                hamSearchSach(soLuongSach, mangChuaSach); // số lượng sách ở đâu mà chuyển nhỉ
                goto nhapLai;
            case 2:
                xuatFile(mangChuaSach);
                goto nhapLai;
            case 3:
                docFile2(soLuongSach1, mangMuonTra);
                quanLy(soLuongSach, mangChuaSach, soLuongSach1, mangMuonTra);
                goto nhapLai;
            case 0:
                goto end;
            default:
                cout << "\nVui long nhap lai.\n";
                goto nhapLai;
            }
        }
        else
            goto hoiAdmin;
    }
    case 'n':
    case 'N':
        int soSach = 0;
        docFile(soSach, mangChuaSach);
        hamSearchSach(soSach, mangChuaSach); // non-admin chi duoc tim kiem sach
        system("pause");
        break;
    }
end:
    system("cls");
    cout << "\n\nCam on da su dung chuong trinh!\n\n";
    system("pause");
    return 0;
}
void hoiAdmin(char &chAd)
{
    bool admin = false;
    do
    {
        cout << "\nBan co phai la admin khong(y/n)? ";
        cin.get(chAd);
        cin.ignore();
        // tolower(chAd); // chuyển về sang chưu thường
        if (chAd == 'y' || chAd == 'n' || chAd == 'Y' || chAd == 'N')
            admin = true;
        else
            cout << "Vui long nhap lai! " << endl;
    } while (admin == false);
    system("cls");
}

void dangNhapKyAdmin(bool &quyenAdmin)
{
    char username[100];
    char passMacDinh[] = "LamBeauty";
    char nhapPass[100];
    char userMacDinh[] = "admin";
    char check;
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
            cout << "\nTai khoan hoac mat khau sai. Vui long nhap lai.\n";
            if (times == 0)
            {
                do
                {
                    cout << "\nBan co muon roi tinh nang dang nhap khong(y/n)? ";
                    cin.get(check);      // j
                    cin.ignore(1, '\n'); // "\n"
                    if (check == 'y' || check == 'Y')
                        goto ended;
                    else if (check == 'n' || check == 'N')
                    {
                        goto again;
                        system("cls");
                    }
                    else
                        cout << "\nVung long nhap lai.\n";
                } while (!(check == 'Y' && check == 'N' && check == 'y' && check == 'n'));
            } // quay ve hoi admin
        }
    } while (quyenAdmin == false);
ended:
    cout << "\nDang chay...\n\n";
    system("cls");
}
void xuatFile(book mangSach[])
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
            cin >> mangSach[i].namPhatHanh;
        } while (mangSach[i].namPhatHanh < 1);
        fout << mangSach[i].tenSach << "," << mangSach[i].theLoai << "," << mangSach[i].tenTacGia << "," << mangSach[i].nxb << "," << mangSach[i].namPhatHanh << "\n";
    }
    fout.close();
}
void docFile(int &n, book mangSach[])
{
    fstream fin;
    fin.open("fileChuaSach.csv", ios::in);
    if (fin.is_open())
    {
        while (getline(fin, mangSach[n].tenSach, ',') && getline(fin, mangSach[n].theLoai, ',') && getline(fin, mangSach[n].tenTacGia, ',') && getline(fin, mangSach[n].nxb, ',') && fin >> mangSach[n].namPhatHanh)
            n++;
        fin.close();
    }
    else
        cout << "Error. Vui long khoi dong lai chuong trinh.";
}
void xuatFile2(bookBorRe b[])
{
    fstream fout;
    int n;
    fout.open("fileQuanLy.csv", ios::out | ios::app);
    cout << "Nhap thong ve sach cho muon\n-------------------------------------------------------";
    cout << "\nNhap so luong sach can nhap: ";
    cin >> n;
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
    if (fin.is_open())
    {
        while (getline(fin, b[n1].tenSach, ',') && getline(fin, b[n1].borName, ',') && getline(fin, b[n1].borDay, ',') && getline(fin, b[n1].reDay))
            n1++;
        fin.close();
    }
    else
        cout << "Error. Vui long khoi dong lai chuong trinh.";
}
void inThongTinSach(int n, book a[])
{ // in thông tin sách trong mảng book
    cout << "Thong tin sach hien co\n---------------------------------------" << endl;
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        cout << a[i].tenSach << endl;
        cout << "Ten tac gia: " << a[i].tenTacGia << endl;
        cout << "The loai: " << a[i].theLoai << endl;
        cout << "Nha xuat ban: " << a[i].nxb << endl;
        cout << "Nam phat hanh: " << a[i].namPhatHanh << "\n\n";
    }
}
void inThongTinMuonTra(int n, bookBorRe b[])
{ // in thông tin sách trong mảng book
    cout << "Thong tin sach hien co\n---------------------------------------" << endl;
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        cout << b[i].tenSach << endl;
        cout << "Ten nguoi muon: " << b[i].borName << endl;
        cout << "Ngay muon: " << b[i].borDay << endl;
        cout << "Ngay den han: " << b[i].reDay << "\n\n";
    }
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
                cout << mangSach[i].tenSach << endl;
                cout << "Ten tac gia: " << mangSach[i].tenTacGia << endl;
                cout << "The loai: " << mangSach[i].theLoai << endl;
                cout << "Nha xuat ban: " << mangSach[i].nxb << endl;
                cout << "Nam phat hanh: " << mangSach[i].namPhatHanh << "\n\n";
            }
        }
        if (checkTimThongTin == false)
            cout << "Sach khong co trong thu vien !\n";
        system("pause");
        break;
    case 2:
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
                cout << mangSach[i].tenSach << endl;
                cout << "Ten tac gia: " << mangSach[i].tenTacGia << endl;
                cout << "The loai: " << mangSach[i].theLoai << endl;
                cout << "Nha xuat ban: " << mangSach[i].nxb << endl;
                cout << "Nam phat hanh: " << mangSach[i].namPhatHanh << "\n\n";
            }
        }
        if (checkTimThongTin == false)
            cout << "Sach cua tac gia nay hien chua co trong thu vien !\n";
        system("pause");
        break;
    case 3:
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
                cout << mangSach[i].tenSach << endl;
                cout << "Ten tac gia: " << mangSach[i].tenTacGia << endl;
                cout << "The loai: " << mangSach[i].theLoai << endl;
                cout << "Nha xuat ban: " << mangSach[i].nxb << endl;
                cout << "Nam phat hanh: " << mangSach[i].namPhatHanh << "\n\n";
            }
        }
        if (checkTimThongTin == false)
            cout << "The loai khong co trong thu vien!\n";
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
                cout << mangSach[i].tenSach << endl;
                cout << "Ten tac gia: " << mangSach[i].tenTacGia << endl;
                cout << "The loai: " << mangSach[i].theLoai << endl;
                cout << "Nha xuat ban: " << mangSach[i].nxb << endl;
                cout << "Nam phat hanh: " << mangSach[i].namPhatHanh << "\n\n";
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
            if (mangSach[i].namPhatHanh == year)
            {
                checkTimThongTin = true;
                cout << mangSach[i].tenSach << endl;
                cout << "Ten tac gia: " << mangSach[i].tenTacGia << endl;
                cout << "The loai: " << mangSach[i].theLoai << endl;
                cout << "Nha xuat ban: " << mangSach[i].nxb << endl;
                cout << "Nam phat hanh: " << mangSach[i].namPhatHanh << "\n\n";
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

void quanLy(int n, book mangChuaSach[], int n1, bookBorRe mangMuonTra[])
{
    int search;
    string data;
    bool checkTimThongTin = false;
nhapLai:
    system("cls");
    cout << "\nQuan ly sach: nguoi muon tra, sach dang duoc muon, so luong sach\n";
    cout << "Tra cuu muon tra theo ten sach  - chon '1'\n";
    cout << "Tra cuu muon tra theo ten       - chon '2'\n";
    cout << "Thong tin sach hien co          - chon '3'\n";
    cout << "Thong tin sach dang duoc muon   - chon '4'\n";
    cout << "Them nguoi muon sach            - chon '5'\n";
    cout << "Quay lai chon tinh nang         - chon '0'\n";
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
        for (int i = 0; i < n1; i++)
        {
            transform(mangMuonTra[i].tenSach.begin(), mangMuonTra[i].tenSach.end(), mangMuonTra[i].tenSach.begin(), ::tolower);
            if (mangMuonTra[i].tenSach.find(data) != string::npos)
            {                            // hàm find, nếu nội dung của data trung với tenSach -> trả ra giá trị đầu tiên
                checkTimThongTin = true; // npos, tức không tìm được vị trí index của tenSach trùng với data
                cout << mangMuonTra[i].tenSach << endl;
                cout << "Ten nguoi muon: " << mangMuonTra[i].borName << endl;
                cout << "Ngay muon: " << mangMuonTra[i].borDay << endl;
                cout << "Ngay den han: " << mangMuonTra[i].reDay << "\n\n";
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
        for (int i = 0; i < n1; i++)
        {
            transform(mangMuonTra[i].borName.begin(), mangMuonTra[i].borName.end(), mangMuonTra[i].borName.begin(), ::tolower);
            if (mangMuonTra[i].borName.find(data) != string::npos)
            {
                checkTimThongTin = true;
                cout << mangMuonTra[i].tenSach << endl;
                cout << "Ten nguoi muon: " << mangMuonTra[i].borName << endl;
                cout << "Ngay muon: " << mangMuonTra[i].borDay << endl;
                cout << "Ngay den han: " << mangMuonTra[i].reDay << "\n\n";
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
            cout << "In tat ca thong tin ve sach hien co(1/0)? ";
            cin >> search;
            if (!(search == 1 || search == 0))
                cout << "Vui long nhap lai!" << endl;
        } while (!(search == 1 || search == 0));
        if (search == 1)
        {
            docFile(n, mangChuaSach);
            inThongTinSach(n, mangChuaSach);
        }
        system("pause");
        goto nhapLai;
    case 4:
        inThongTinMuonTra(n1, mangMuonTra);
        system("pause");
        goto nhapLai;
    case 5:
        xuatFile2(mangMuonTra);
        goto nhapLai;
    case 0:
        cout << "\nDang tro lai chon tinh nang...\n";
        break;
    default:
        cout << "\nLua chon khong hop le. Vui long chon lai.\n";
        goto nhapLai;
    }
}
