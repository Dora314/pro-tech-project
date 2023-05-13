// Hệ thống quản lý thư viện bởi team 8
#include <bits/stdc++.h>
using namespace std;
struct date
{
    int d;
    int m;
    int y;
};
struct book // file chua sach
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
struct bookBorRe // file quan ly
{
    string tenSach; // lay ten sach
    string borName; // ten nguoi muon
    date borDay;    // ngay muon
    date reDay;     // ngay den han
};
void xuatFile(book a[]);
void docFile(book a[]);
void xuatFile2(bookBorRe b[]);
void docFile2(bookBorRe b[]);
void hoiAdmin(char &chAd);
void dangNhapKyAdmin(bool &quyenAdmin);
void inThongTinSach(int n, book a[]); // a[] la mang chua sach
void hamSearchSach(int n, book mangSach[]);
void searchTheoThongTin(int search, int n, book mangSach[]);
void quanLy(int n, bookBorRe mangMuonTra[]);

int main()
{
    char chAd;
    book mangChuaSach[5000];
    bookBorRe mangMuonTra[5000];
    int soLuongSach, tinhNang;
    bool quyenAdmin = false;
hoiAdmin:
    hoiAdmin(chAd); // kiểm tra có phải admin hay không -> truyền tham chiếu chAd
    switch (chAd)
    {
    case 'y':
    case 'Y':
        dangNhapKyAdmin(quyenAdmin);
        if (quyenAdmin == true)
        {
        nhapLai:
            system("cls"); // xoa man hinh giong clrscr trong pascal
            cout << "\nMoi chon tinh nang\n";
            cout << "Tim kiem sach              - chon '1' \n";
            cout << "Nhap sach vao thu vien     - chon '2' \n";
            cout << "Quan ly sach      - chon '3' \n";
            cout << "Thoat                      - chon '0' \n";
            // xoa sach trong tuong lai
            cout << "Xin moi nhap tinh nang theo so: ";
            cin >> tinhNang;
            system("cls");
            switch (tinhNang)
            {
            case 1:
                docFile(mangChuaSach);
                hamSearchSach(soLuongSach, mangChuaSach); // số lượng sách ở đâu mà chuyển nhỉ
                goto nhapLai;
            case 2:
                docFile(mangChuaSach);
                xuatFile(mangChuaSach);
                goto nhapLai;
            case 3:
                docFile2(mangMuonTra);
                quanLy(soLuongSach, mangMuonTra);
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
    case 'n':
    case 'N':
        hamSearchSach(soLuongSach, mangChuaSach); // non-admin chi duoc tim kiem sach
        break;
    default:
        cout << "Vui long khoi dong lai chuong trinh.";
        break;
    }
end:
    system("cls");
    cout << "\n\nCam on da su dung chuong trinh!\n\n";
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
    cout << "Dang chay...\n";
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
void docFile(book mangSach[])
{
    fstream fin;
    fin.open("fileChuaSach.csv", ios::in);
    int n = 0;
    if (fin.is_open())
    {
        while (getline(fin, mangSach[n].tenSach, ',') && getline(fin, mangSach[n].theLoai, ',') && getline(fin, mangSach[n].tenTacGia, ',') && getline(fin, mangSach[n].nxb, ',') && fin >> mangSach[n].namPhatHanh)
            n++;
        fin.close();
    }
    else
        cout << "Error. Vui long khoi dong lai chuong trinh.";
}
/*void xuatFile2(bookBorRe b[])
{
    fstream fout;
    int n;
    fout.open("fileQuanLy.csv", ios::out | ios::app);
    cout << "Nhap thong ve sach cho muon\n-------------------------------------------------------";
    cout << "\nNhap so luong sach can nhap: ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        system("cls");
        cout << "Nhap ten sach thu " << i + 1 << ": ";
        cin.ignore();
        getline(cin, b[i].tenSach);
        cout << "Nhap ten nguoi muon: ";
        getline(cin, b[i].borName);
        cout << "Nhap ngay muon ";
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
}*/
void docFile2(bookBorRe b[])
{
    fstream fin;
    fin.open("fileQuanLy.csv", ios::in);
    int n = 0;
    if (fin.is_open())
    {
        while (getline(fin, b[n].tenSach, ',') && getline(fin, b[n].borName, ',') && fin >> b[n].borDay.d && fin >> b[n].borDay.m && fin >> b[n].borDay.y && fin >> b[n].reDay.d && fin >> b[n].reDay.m && fin >> b[n].reDay.y)
            n++;
        fin.close();
    }
    else
        cout << "Error. Vui long khoi dong lai chuong trinh.";
}
void inThongTinSach(int n, book a[])
{ // in thông tin sách trong mảng book
    cout << "Thong tin sach hien co:" << endl;
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
        {
            break;
        }
        else
        {
            cout << "Lua chon khong hop le !\n";
        }
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

        // hàm transform
        transform(data.begin(), data.end(), data.begin(), ::tolower); // hàm chuyển sang lowercase, dùng cho string only (LƯU Ý: cần có thư viện bits để dùng)
        for (int i = 0; i < n; i++)
        {
            transform(mangSach[i].tenSach.begin(), mangSach[i].tenSach.end(), mangSach[i].tenSach.begin(), ::tolower);
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
        transform(data.begin(), data.end(), data.begin(), ::tolower);
        for (int i = 0; i < n; i++)
        {
            transform(mangSach[i].tenTacGia.begin(), mangSach[i].tenTacGia.end(), mangSach[i].tenTacGia.begin(), ::tolower);
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
        transform(data.begin(), data.end(), data.begin(), ::tolower);

        for (int i = 0; i < n; i++)
        {
            transform(mangSach[i].theLoai.begin(), mangSach[i].theLoai.end(), mangSach[i].theLoai.begin(), ::tolower);
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
        transform(data.begin(), data.end(), data.begin(), ::tolower);

        for (int i = 0; i < n; i++)
        {
            transform(mangSach[i].nxb.begin(), mangSach[i].nxb.end(), mangSach[i].nxb.begin(), ::tolower);

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
    cout << "\nQuan ly sach: nguoi muon tra, sach dang duoc muon, so luong sach\n";
    cout << "Tim theo ten nguoi muon   - chon '1'\n";
    cout << "Tra cuu ten sach duoc muon- chon '2'\n";
    cout << "Xem sach hien co          - chon '3'\n";
    cout << "Quay lai chon tinh nang   - chon '0'\n";
    do
    {
        cout << "Moi ban chon: ";
        cin >> search;
        if (search == 0 || search == 1 || search == 2)
        {
            break;
        }
        else
        {
            cout << "Lua chon khong hop le !\n";
        }
    } while (search != 0 || search != 1 || search != 2);
    system("cls");
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
                cout << mangMuonTra[i].tenSach << "    " << mangMuonTra[i].borName << "    " << mangMuonTra[i].borDay.d << "/" << mangMuonTra[i].borDay.m << "/" << mangMuonTra[i].borDay.y << "    " << mangMuonTra[i].reDay.d << "/" << mangMuonTra[i].reDay.m << "/" << mangMuonTra[i].reDay.y << "\n";
            }
        if (checkTimThongTin == false)
            cout << "Khong tim thay nguoi muon sach !";
        goto nhapLai;
    case 2:
        cout << "Moi ban nhap ten sach: ";
        cin.ignore();
        getline(cin, data);
        for (int i = 0; i < n; i++)
            if (mangMuonTra[i].tenSach.find(data) != string::npos)
            {
                checkTimThongTin = true;
                cout << mangMuonTra[i].tenSach << "    " << mangMuonTra[i].borName << "    " << mangMuonTra[i].borDay.d << "/" << mangMuonTra[i].borDay.m << "/" << mangMuonTra[i].borDay.y << "    " << mangMuonTra[i].reDay.d << "/" << mangMuonTra[i].reDay.m << "/" << mangMuonTra[i].reDay.y << "\n";
            }
        if (checkTimThongTin == false)
            cout << "Sach khong co trong thu vien !";
        goto nhapLai;
    case 3:
    // cout << "So luong sach hien co la " << soSach << " cuon sach!";
    case 0:
        cout << "Dang tro lai chon tinh nang...";
        break;
    default:
        cout << "Lua chon khong hop le. Vui long chon lai.";
        goto nhapLai;
    }
}
