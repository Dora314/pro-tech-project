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
void xuatFile();                // ghi file sách trong thư viện
void docFile(int &n, book a[]); // đọc file chứa sách trong thư viện
void xuatFile2();
void docFile2(int &n, bookBorRe b[]);

void hoiAdmin(int &chAd);
void dangNhapKyAdmin(bool &quyenAdmin);

void inSach_dungChoHamSearch(int i, book a[]);
void inMuonTra(int i, bookBorRe b[]);         // i la vi tri tai phan tu can in ra console
void inThongTinSach(int n, book a[]);         // a[] la mang chua sach
void inThongTinMuonTra(int n, bookBorRe b[]); // b[] la mang muon tra

void hamSearchSach(int n, book mangSach[]);
void searchTheoThongTin(int search, int n, book mangSach[]);

void quanLy(int n, book mangChuaSach[], int n1, bookBorRe mangMuonTra[]);
void xoaSach(int soLuongSach, book a[]);
void xoaThongTinNguoiMuon(int &soLuongSachMuon, bookBorRe mangMuonTra[]);
void chinhSuaThongTin(int soLuongSachMuon, bookBorRe mangMuonTra[]); // do chỉnh sửa thông tin nên không cần biến đổi số lượng sách mượn
void hamCapNhatSoLuongSachTrongThuVien(int &soSachThuVien, book mangSach[]);

int main()
{
    int chAd;
    book mangChuaSach[5000];
    bookBorRe mangMuonTra[5000];
    int tinhNang, soLuongSach, soLuongSachMuon;
    bool quyenAdmin = false;
    system("cls");
    cout << "         CHAO MUNG DEN VOI DU AN QUAN LY THU VIEN CUA TEAM 8!\n";
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
            cout << "\n        MOI BAN CHON TINH NANG\n";
            cout << "__________________________________________\n";
            cout << "||                           ||          ||\n";
            cout << "||Tim kiem sach              || Chon '1' ||\n";
            cout << "||Nhap sach vao thu vien     || Chon '2' ||\n";
            cout << "||Quan ly sach               || Chon '3' ||\n";
            cout << "||Thoat                      || Chon '0' ||\n";
            cout << "||___________________________||__________||\n";
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
                docFile(soLuongSach, mangChuaSach);     // đọc file chứa sách
                docFile2(soLuongSachMuon, mangMuonTra); // đọc file chứa mượn sách
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
    nhapLaiKhongPhaiAdmin:
        system("cls"); // xoa man hinh giong clrscr trong pascal
        cout << "\n     MOI BAN CHON TINH NANG\n";
        cout << "____________________________________\n";
        cout << "||                    ||          ||\n";
        cout << "||Tim kiem sach       || Chon '1' ||\n";
        cout << "||Thoat               || Chon '0' ||\n";
        cout << "||____________________||__________||\n";
        cout << "Xin moi nhap tinh nang theo so: ";
        cin >> tinhNang;
        system("cls");
        switch (tinhNang)
        {
        case 1:
        {
            docFile(soLuongSach, mangChuaSach);
            hamSearchSach(soLuongSach, mangChuaSach); // non-admin chi duoc tim kiem sach
            goto nhapLaiKhongPhaiAdmin;
        }
        case 0:
            goto end;
        default:
            cout << "\n\nVui long nhap lai!\n\n";
            system("pause");
            goto nhapLaiKhongPhaiAdmin;
        }
    }
    }
end:
    system("cls");
    cout << "\n\nCam on da su dung chuong trinh! Xin chao va hen gap lai!\n_______________________________________________________\n\n";
    system("pause");
    return 0;
}

void hoiAdmin(int &chAd)
{
    bool admin = false;
    do
    {
        cout << "\nBan co phai la admin khong? (Nhap 1 = CO, 0 = KHONG): ";
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
    char passMacDinh[] = "quanLy";
    int check;
    cin.ignore(1);
again:
    int times = 3;
    do
    {
        cout << "\nMoi ban nhap ten dang nhap: ";
        cin.getline(username, 10);
        cout << "__________________________________\n";
        cout << "\nMoi ban nhap mat khau: ";
        cin.getline(nhapPass, 20);

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
                    cout << "\nBan co muon roi tinh nang dang nhap khong? (Nhap 1 = CO, 0 = KHONG): ";
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
    int namPhatHanh, n;
    fout.open("fileChuaSach.csv", ios::out | ios::app);
    cout << "           NHAP THONG TIN SACH VAO THU VIEN\n";
    cout << "-------------------------------------------------------\n";
    cout << "Moi ban nhap so luong sach can nhap vao thu vien: ";
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
        fout << mangSach[i].tenSach << "," << mangSach[i].theLoai << "," << mangSach[i].tenTacGia << "," << mangSach[i].nxb << "," << namPhatHanh << '\n';
    }
    fout.close();
}

void docFile(int &n, book mangSach[])
{
    fstream fin;
    fin.open("fileChuaSach.csv", ios::in);
    n = 0; // reset số sách sau mỗi lần đọc
    if (fin.is_open())
    {
        while (getline(fin, mangSach[n].tenSach, ',') && getline(fin, mangSach[n].theLoai, ',') && getline(fin, mangSach[n].tenTacGia, ',') && getline(fin, mangSach[n].nxb, ',') && getline(fin, mangSach[n].namPhatHanh))
            // số lượng sách
            n++;
        fin.close();
    }
    else
        cout << "Error!!! Vui long khoi dong lai chuong trinh.";
}

void xuatFile2()
{
    fstream fout;
    int n;
    fout.open("fileQuanLy.csv", ios::out | ios::app);
    cout << "            NHAP THONG TIN VE SACH CHO MUON\n";
    cout << "-------------------------------------------------------\n";
    cout << "\nMoi ban nhap so luong sach cho muon: ";
    cin >> n;
    bookBorRe mangSachChoMuon[n];
    cin.ignore();
    time_t now = time(0); // hàm lấy thời gian hiện tại - thời gian thực
    tm *ltm = localtime(&now);
    for (int i = 0; i < n; i++)
    {
        system("cls");
        cout << "Nhap ten sach thu " << i + 1 << ": ";
        getline(cin, mangSachChoMuon[i].tenSach);
        cout << "Nhap ten nguoi muon: ";
        getline(cin, mangSachChoMuon[i].borName);
        fout << mangSachChoMuon[i].tenSach << "," << mangSachChoMuon[i].borName << "," << ltm->tm_mday << "-" << 1 + ltm->tm_mon << "-" << 1900 + ltm->tm_year << "," << ltm->tm_mday << "-" << 2 + ltm->tm_mon << "-" << 1900 + ltm->tm_year << '\n';
    }
    fout.close();
}

void docFile2(int &n1, bookBorRe mangMuonTra[])
{
    fstream fin;
    fin.open("fileQuanLy.csv", ios::in);
    n1 = 0; // đọc số sách đang được mượn trong file - reset số sách sau mỗi lần đọc
    if (fin.is_open())
    {
        // hàm getline dùng để đọc hết cả dòng
        // hàm getline nếu có 2 tham số -> (cin, length) || nếu có 3 tham số (cin, thông tin, dừng cho đến khi gặp kí tự - delimeter)
        while (getline(fin, mangMuonTra[n1].tenSach, ',') && getline(fin, mangMuonTra[n1].borName, ',') && getline(fin, mangMuonTra[n1].borDay, ',') && getline(fin, mangMuonTra[n1].reDay))
            n1++;
        fin.close();
    }
    else
        cout << "Error!!! Vui long khoi dong lai chuong trinh!";
}

void inSach_dungChoHamSearch(int i, book a[]) // In thông tin sách có trong thư viện
{
    cout << endl;
    cout << a[i].tenSach << endl;
    cout << "The loai: " << a[i].theLoai << endl;
    cout << "Ten tac gia: " << a[i].tenTacGia << endl;
    cout << "Nha xuat ban: " << a[i].nxb << endl;
    cout << "Nam phat hanh: " << a[i].namPhatHanh;
    cout << "-------------------------------------------------\n";
}

void inMuonTra(int i, bookBorRe b[]) // In thông tin người mượn sách
{
    cout << endl;
    cout << b[i].tenSach << endl;
    cout << "Ten nguoi muon: " << b[i].borName << endl;
    cout << "Ngay muon: " << b[i].borDay << endl;
    cout << "Ngay den han: " << b[i].reDay;
    cout << "-------------------------------------------------\n";
}

void inThongTinSach(int n, book a[])
{ // in thông tin sách trong mảng book
    cout << "         THONG TIN SACH HIEN CO TRONG THU VIEN\n";
    cout << "-------------------------------------------------------\n";
    cout << endl;
    for (int i = 0; i < n; i++)
        inSach_dungChoHamSearch(i, a);
}

void inThongTinMuonTra(int n, bookBorRe b[])
{ // in thông tin sách trong mảng book
    cout << "            THONG TIN SACH DANG DUOC MUON\n";
    cout << "-------------------------------------------------------\n";
    cout << endl;
    for (int i = 0; i < n; i++)
        inMuonTra(i, b);
}

void hamSearchSach(int n, book mangSach[])
{
    int search;
    cout << "\n     XIN MOI NHAP LUA CHON\n";
    cout << "____________________________________\n";
    cout << "||                    ||          ||\n";
    cout << "||Ten sach            || Chon '1' ||\n";
    cout << "||The loai            || Chon '2' ||\n";
    cout << "||Ten tac gia         || Chon '3' ||\n";
    cout << "||Nha xuat ban        || Chon '4' ||\n";
    cout << "||Nam phat hanh       || Chon '5' ||\n";
    cout << "||Thoat               || Chon '0' ||\n";
    cout << "||____________________||__________||\n";
    do
    {
        cout << "Moi ban chon: ";
        cin >> search;
        if (!(search == 0 || search == 1 || search == 2 || search == 3 || search == 4 || search == 5))
            cout << "Lua chon khong hop le!!!\n\n";
    } while (!(search == 0 || search == 1 || search == 2 || search == 3 || search == 4 || search == 5));
    system("cls");
    searchTheoThongTin(search, n, mangSach);
}

void searchTheoThongTin(int search, int soLuongSach, book mangSach[])
{
    string data, temp;
    bool checkTimThongTin = false; // tra ve false neu kh tim duoc
    cin.ignore();
    switch (search)
    {
    case 1:
        cout << "Moi ban nhap ten sach: ";
        getline(cin, data);
        cout << endl;
        transform(data.begin(), data.end(), data.begin(), ::tolower); // hàm chuyển sang lowercase, dùng cho string only (LƯU Ý: cần có thư viện bits để dùng)
        for (int i = 0; i < soLuongSach; i++)
        {
            // dùng biến temp, giúp dữ liệu trong csv kh bị đổi vd Harry Poter vẫn giữ nguyên thay vì harry potter
            temp = mangSach[i].tenSach;
            transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
            if (temp.find(data) != string::npos)
            {                            // hàm find, nếu nội dung của data trung với tenSach -> trả ra giá trị đầu tiên //data = ora (0123) -> doraemon (01234567->8)
                checkTimThongTin = true; // npos, tức không tìm được vị trí index của tenSach trùng với data
                inSach_dungChoHamSearch(i, mangSach);
            }
        }
        if (checkTimThongTin == false)
            cout << "Sach khong co trong thu vien !\n";
        cout << "Dang quay ve chon tinh nang. Vui long cho...";
        system("pause");
        break;
    case 2:
        cout << "Moi ban nhap the loai: ";
        getline(cin, data);
        cout << endl;
        transform(data.begin(), data.end(), data.begin(), ::tolower);
        for (int i = 0; i < soLuongSach; i++)
        {
            temp = mangSach[i].theLoai;
            transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
            if (temp.find(data) != string::npos)
            {
                checkTimThongTin = true;
                inSach_dungChoHamSearch(i, mangSach);
            }
        }
        if (checkTimThongTin == false)
            cout << "The loai khong co trong thu vien!\n";
        cout << "Dang quay ve chon tinh nang. Vui long cho...";
        system("pause");
        break;
    case 3:
        cout << "Moi ban nhap ten tac gia: ";
        getline(cin, data);
        cout << endl;
        transform(data.begin(), data.end(), data.begin(), ::tolower);
        for (int i = 0; i < soLuongSach; i++)
        {
            temp = mangSach[i].tenTacGia;
            transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
            if (temp.find(data) != string::npos)
            {
                checkTimThongTin = true;
                inSach_dungChoHamSearch(i, mangSach);
            }
        }
        if (checkTimThongTin == false)
            cout << "Sach cua tac gia nay hien chua co trong thu vien !\n";
        cout << "Dang quay ve chon tinh nang. Vui long cho...\n";
        system("pause");
        break;
    case 4:
        cout << "Moi ban nhap nha xuat ban : ";
        getline(cin, data);
        cout << endl;
        transform(data.begin(), data.end(), data.begin(), ::tolower);
        for (int i = 0; i < soLuongSach; i++)
        {
            temp = mangSach[i].nxb;
            transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
            if (temp.find(data) != string::npos)
            {
                checkTimThongTin = true;
                inSach_dungChoHamSearch(i, mangSach);
            }
        }
        if (checkTimThongTin == false)
            cout << "Nha xuat ban sach nay khong co trong thu vien !\n";
        cout << "Dang quay ve chon tinh nang. Vui long cho...\n";
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
        for (int i = 0; i < soLuongSach; i++)
        {
            if (stoi(mangSach[i].namPhatHanh) == year) // chuyển string sang integer - string to interger (vì trong file, năm được lưu thành string)
            {
                checkTimThongTin = true;
                inSach_dungChoHamSearch(i, mangSach);
            }
        }
        if (checkTimThongTin == false)
            cout << "Thu vien hien khong co sach cua nam nay !\n";
        cout << "Dang quay ve chon tinh nang. Vui long cho...\n";
        system("pause");
        break;
    case 0:
        cout << "Dang thoat chuong trinh...\n\n";
        break;
    }
}

void quanLy(int n, book mangChuaSach[], int soLuongSachMuon, bookBorRe mangMuonTra[])
{
    int search;
    string data, temp;
    bool checkTimThongTin = false;
nhapLai:
    system("cls");
    cout << "\n                     QUAN LY SACH\n";
    cout << "_________________________________________________________\n";
    cout << "||                                          ||         ||\n";
    cout << "||Tra cuu muon tra theo ten sach            || Chon '1'||\n";
    cout << "||Tra cuu muon tra theo ten nguoi muon      || Chon '2'||\n";
    cout << "||Thong tin sach hien co                    || Chon '3'||\n";
    cout << "||Thong tin sach dang duoc muon             || Chon '4'||\n";
    cout << "||Them nguoi muon sach                      || Chon '5'||\n"; // thêm (thì fileQuanLy ++) và fileSach - 1 sách ---> ghi lại file mượn và file sách
    cout << "||Xoa nguoi muon sach                       || Chon '6'||\n";
    cout << "||Xoa sach khoi thu vien                    || Chon '7'||\n";
    cout << "||Sua thong tin                             || Chon '8'||\n";
    cout << "||Quay lai chon tinh nang                   || Chon '0'||\n";
    cout << "||__________________________________________||_________||\n";
    // cout << "Thong ke so sach(cung tac gia,the loai,.) - chon '8'\n";
    do
    {
        cout << "Moi ban chon: ";
        cin >> search;
        if (!(search == 0 || search == 1 || search == 2 || search == 3 || search == 4 || search == 5 || search == 6 || search == 7 || search == 8))
            cout << "Lua chon khong hop le !\n";
    } while (!(search == 0 || search == 1 || search == 2 || search == 3 || search == 4 || search == 5 || search == 6 || search == 7 || search == 8));
    cin.ignore(); // xóa đệm từ cin search
    docFile(n, mangChuaSach);
    docFile2(soLuongSachMuon, mangMuonTra);
    system("cls");

    switch (search)
    {
    case 1:
        cout << "Moi ban nhap ten sach: ";
        getline(cin, data);
        cout << endl;

        transform(data.begin(), data.end(), data.begin(), ::tolower); // hàm chuyển sang lowercase, dùng cho string only (LƯU Ý: cần có thư viện bits để dùng)
        for (int i = 0; i < soLuongSachMuon; i++)
        {
            temp = mangMuonTra[i].tenSach;
            transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
            if (temp.find(data) != string::npos)
            {                            // hàm find, nếu nội dung của data trung với tenSach -> trả ra giá trị đầu tiên
                checkTimThongTin = true; // npos, tức không tìm được vị trí index của tenSach trùng với data
                inMuonTra(i, mangMuonTra);
            }
        }
        if (checkTimThongTin == false)
        {
            cout << "Quyen sach nay van chua duoc muon.\n";
        }
        cout << "Nhan phim bat ki de quay lai tinh nang quan ly.\n";
        system("pause");
        goto nhapLai;

    case 2:
        cout << "Moi ban nhap ten nguoi muon: ";
        getline(cin, data);
        cout << endl;
        transform(data.begin(), data.end(), data.begin(), ::tolower); // hàm chuyển sang lowercase, dùng cho string only (LƯU Ý: cần có thư viện bits để dùng)
        for (int i = 0; i < soLuongSachMuon; i++)
        {
            temp = mangMuonTra[i].borName;
            transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
            if (temp.find(data) != string::npos)
            {
                checkTimThongTin = true;
                inMuonTra(i, mangMuonTra);
            }
        }
        if (checkTimThongTin == false)
        {
            cout << "Khong tim thay ten nguoi muon!\n";
        }
        cout << "Nhan nut bat ki de quay lai tinh nang quan ly.\n";
        system("pause");
        goto nhapLai;

    case 3:
        cout << "So luong sach hien co trong thu vien la " << n << endl; // vd kho 100 cuôn - 9 cuốn mượn
        do
        {
            cout << "Ban co muon xuat tat ca thong tin ve sach hien co trong thu vien khong? (Nhap 1 = CO, 0 = KHONG): ";
            cin >> search;
            cout << "--------------------------------------------------------------------------------------------------\n";
            if (!(search == 1 || search == 0))
                cout << "Vui long nhap lai!" << endl;
        } while (!(search == 1 || search == 0));
        if (search == 1)
        {
            inThongTinSach(n, mangChuaSach);
        }
        cout << "Nhan phim bat ki de quay lai tinh nang quan ly.\n";
        system("pause");
        goto nhapLai;

    case 4:
        cout << "So luong sach hien dang duoc muon la " << soLuongSachMuon << endl;
        do
        {
            cout << "Ban co muon xuat tat ca thong tin ve sach dang duoc muon khong? (Nhap 1 = CO, 0 = KHONG): ";
            cin >> search;
            cout << "--------------------------------------------------------------------------------------------------\n";
            if (!(search == 1 || search == 0))
                cout << "Vui long nhap lai!" << endl;
        } while (!(search == 1 || search == 0));
        if (search == 1)
        {
            inThongTinMuonTra(soLuongSachMuon, mangMuonTra);
        }
        cout << "Nhan phim bat ki de quay lai tinh nang quan ly.\n";
        system("pause");
        goto nhapLai;
    case 5:
        xuatFile2();                            // thêm 1 người mượn
        docFile2(soLuongSachMuon, mangMuonTra); // đọc lại để update số lượng người mượn
        hamCapNhatSoLuongSachTrongThuVien(n, mangChuaSach);
        goto nhapLai;
    case 6:
        xoaThongTinNguoiMuon(soLuongSachMuon, mangMuonTra);
        hamCapNhatSoLuongSachTrongThuVien(n, mangChuaSach);
        goto nhapLai;
    case 7:
        xoaSach(n, mangChuaSach);
        goto nhapLai;
    case 8:
        chinhSuaThongTin(soLuongSachMuon, mangMuonTra);
        goto nhapLai;
    case 0:
        break;
    default:
        cout << "\nLua chon khong hop le! Vui long chon lai!\n";
        goto nhapLai;
    }
}

void xoaSach(int soLuongSach, book a[]) // a là mảng chứa sách trong thư viên
{
    string data, temp;
    int tempNam;
xoaLai:
    int search;
    bool checkTimThongTin = false; // bao nguoi dung neu khong co sach
    system("cls");
    cout << "\n             XOA SACH\n";
    cout << "________________________________________________n";
    cout << "||                                ||         ||\n";
    cout << "||Xoa sach theo ten sach          || Chon '1'||\n";
    cout << "||Xoa sach theo the loai          || Chon '2'||\n";
    cout << "||Xoa sach theo ten tac gia       || Chon '3'||\n";
    cout << "||Xoa sach theo nha xuat ban      || Chon '4'||\n";
    cout << "||Xoa sach theo nam xuat ban      || Chon '5'||\n";
    cout << "||Quay lai chon tinh nang         || Chon '0'||\n";
    cout << "||________________________________||_________||\n";
    do
    {
        cout << "Moi ban chon: ";
        cin >> search;
        if (!(search == 0 || search == 1 || search == 2 || search == 3 || search == 4 || search == 5))
        {
            cout << "\nLua chon khong hop le ! Vui long chon lai \n";
        }
    } while (!(search == 0 || search == 1 || search == 2 || search == 3 || search == 4 || search == 5));
    cin.ignore();
    system("cls");
    switch (search)
    {
    case 1:
    {
        cout << "\nMoi ban nhap ten sach can xoa: ";
        getline(cin, data);
        transform(data.begin(), data.end(), data.begin(), ::tolower);
        fstream fout("fileChuaSach.csv", ios::out);
        for (int i = 0; i < soLuongSach; i++)
        {
            temp = a[i].tenSach;
            transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
            if (temp == data)
            {
                checkTimThongTin = true;
                continue; // bo qua neu day la sach can xoa
            }
            // in ra fileQuanLy sach khong can xoa
            fout << a[i].tenSach << "," << a[i].theLoai << "," << a[i].tenTacGia << "," << a[i].nxb << "," << a[i].namPhatHanh << endl;
        }
        fout.close();
        if (checkTimThongTin == false)
            cout << "\nKhong tim thay ten sach!\n";
        else
            cout << "\n------------------DA XOA THANH CONG------------------\n";
        system("pause");
        docFile(soLuongSach, a); // đọc lại để update số lượng sách
        goto xoaLai;
    }
    case 2:
    {
        cout << "\nMoi ban nhap ten the loai sach can xoa: ";
        getline(cin, data);
        transform(data.begin(), data.end(), data.begin(), ::tolower);
        fstream fout("fileChuaSach.csv", ios::out);
        for (int i = 0; i < soLuongSach; i++)
        {
            temp = a[i].theLoai;
            transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
            if (temp == data)
            {
                checkTimThongTin = true;
                continue; // bo qua neu day la sach can xoa
            }
            // in ra fileQuanLy sach khong can xoa
            fout << a[i].tenSach << "," << a[i].theLoai << "," << a[i].tenTacGia << "," << a[i].nxb << "," << a[i].namPhatHanh << endl;
        }
        fout.close();
        if (checkTimThongTin == false)
            cout << "\nKhong tim thay ten the loai sach!\n";
        else
            cout << "\n------------------DA XOA THANH CONG------------------\n";
        system("pause");
        docFile(soLuongSach, a);
        goto xoaLai;
    }
    case 3:
    {
        cout << "\nMoi ban nhap ten tac gia can xoa: ";
        getline(cin, data);
        transform(data.begin(), data.end(), data.begin(), ::tolower);
        fstream fout("fileChuaSach.csv", ios::out);
        for (int i = 0; i < soLuongSach; i++)
        {
            temp = a[i].tenTacGia;
            transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
            if (temp == data)
            {
                checkTimThongTin = true;
                continue; // bo qua neu day la sach can xoa
            }
            fout << a[i].tenSach << "," << a[i].theLoai << "," << a[i].tenTacGia << "," << a[i].nxb << "," << a[i].namPhatHanh << endl;
        }
        fout.close();
        if (checkTimThongTin == false)
            cout << "\nKhong tim thay ten tac gia!\n";
        else
            cout << "\n------------------DA XOA THANH CONG------------------\n";
        system("pause");
        docFile(soLuongSach, a);
        goto xoaLai;
    }
    case 4:
    {
        cout << "\nMoi ban nhap ten nha xuat ban can xoa: ";
        getline(cin, data);
        transform(data.begin(), data.end(), data.begin(), ::tolower);
        fstream fout("fileChuaSach.csv", ios::out);
        for (int i = 0; i < soLuongSach; i++)
        {
            temp = a[i].nxb;
            transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
            if (temp == data)
            {
                checkTimThongTin = true;
                continue; // bo qua neu day la sach can xoa
            }
            fout << a[i].tenSach << "," << a[i].theLoai << "," << a[i].tenTacGia << "," << a[i].nxb << "," << a[i].namPhatHanh << endl;
        }
        fout.close();
        if (checkTimThongTin == false)
            cout << "\nKhong tim thay ten nha xuat ban!\n";
        else
            cout << "\n------------------DA XOA THANH CONG------------------\n";
        system("pause");
        docFile(soLuongSach, a);
        goto xoaLai;
    }
    case 5:
    {
        int namPhatHanh;
        do
        {
            cout << "\nMoi ban nhap nam phat hanh can xoa: ";
            cin >> namPhatHanh;
        } while (namPhatHanh < 1);
        cout << endl;
        fstream fout("fileChuaSach.csv", ios::out);
        for (int i = 0; i < soLuongSach; i++)
        {
            tempNam = stoi(a[i].namPhatHanh); // stoi chuyen string thanh integer
            if (tempNam == namPhatHanh)
            {
                checkTimThongTin = true;
                continue; // bo qua neu day la sach can xoa
            }
            fout << a[i].tenSach << "," << a[i].theLoai << "," << a[i].tenTacGia << "," << a[i].nxb << "," << a[i].namPhatHanh << endl;
        }
        fout.close();
        if (checkTimThongTin == false)
            cout << "\nKhong tim thay nam phat hanh!\n";
        else
            cout << "\n------------------DA XOA THANH CONG------------------\n";
        system("pause");
        docFile(soLuongSach, a);
        goto xoaLai;
    }
    case 0:
        break;
    }
}

void xoaThongTinNguoiMuon(int &soLuongSachMuon, bookBorRe mangMuonTra[])
{
    // số lượng sách mượn sẽ thay đổi sau khi xóa tên người mượn
    string data, temp;
    bool found = false; // tạo biến false để check
    int n = soLuongSachMuon;

    cout << "\n---------------------NHAP THONG TIN CAN XOA--------------------- \n\n";
    cout << "Moi ban nhap ten cua nguoi muon: ";
    getline(cin, data);
    transform(data.begin(), data.end(), data.begin(), ::tolower);
    system("cls");

    // Check trường hợp người cần xóa.
    // TH1 : VD trong những người mượn, có những người trùng tên Nam : Đăng Nam, Nam Anh, Nhật Nam,...
    // -->> những thông tin của người trùng tên Nam
    // --> gõ tên sách và tên đầy đủ của người tên Nam vd: Đăng Nam - Harry Potter
    // TH2 : có mỗi người có tên đó -> cho n = 1 -> xóa luôn không phải gõ lại (đang phát triển)
    for (int i = 0; i < soLuongSachMuon; i++)
    {
        temp = mangMuonTra[i].borName;

        transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
        if (temp.find(data) != string::npos)
        {
            found = true;
            inMuonTra(i, mangMuonTra);
        }
    }
    if (found == false)
        cout << "\nKhong co ten nguoi muon trong danh sach !!!\n";
    else
    {
        cout << "Vui long nhap day du ten va ten sach muon xoa theo noi dung o tren.\n";
        cout << "____________________________________________________________________\n";
        string tenNguoiMuon, tenSachMuon;
        cout << "Hay nhap ten cua nguoi muon xoa (Vui long nhap chinh xac thong tin nhu file da luu): ";
        getline(cin, tenNguoiMuon);
        cout << "Hay nhap ten cuon sach muon tra (Vui long nhap chinh xac thong tin nhu file da luu): ";
        getline(cin, tenSachMuon);

        fstream myFile("fileQuanLy.csv", ios::out);
        for (int i = 0; i < n; i++)
        { // n = soLuongSachMuon (tui gán để tránh bị đổi giá trị soLuong)
            if (tenNguoiMuon == mangMuonTra[i].borName && tenSachMuon == mangMuonTra[i].tenSach)
            {
                continue;
            }
            myFile << mangMuonTra[i].tenSach << "," << mangMuonTra[i].borName << "," << mangMuonTra[i].borDay << "," << mangMuonTra[i].reDay << endl;
        }
        docFile2(soLuongSachMuon, mangMuonTra); // update số lượn trong file quản lý
        myFile.close();
        cout << "\n------------------DA XOA THANH CONG------------------\n";
        cout << "Nhan phim bat ki de quay lai tinh nang quan ly.\n";
        cout << "Dang chay...\n";
        system("pause");
    }
}

void hamCapNhatSoLuongSachTrongThuVien(int &soLuongSach, book mangSach[])
{
    int option;
    string tenSach;
    cout << "\n";
    cout << "                        CAP NHAT SO LUONG SACH\n";
    cout << "_________________________________________________________________________\n";
    cout << "||                                                             ||        ||\n";
    cout << "||Cap nhat sach DA CHO MUON vao thu vien (Sach da cho muon)    || Nhap 0 ||\n"; // sau khi xóa ra fileQuanLy -> nhập vào fileChuaSach
    cout << "||Cap nhat sach DA TRA vao thu vien (Sach duoc tra lai)        || Nhap 1 ||\n"; // xóa sách từ fileChuaSach -> nhập sang fileQuanLy
    cout << "||_____________________________________________________________||________||\n";
    do
    {
        cout << "Moi ban nhap: ";
        cin >> option;
        cin.ignore();
        if (!(option == 0 || option == 1))
        {
            cout << "Lua chon khong hop le, Vui long nhap lai \n";
        }
    } while (!(option == 0 || option == 1));
    switch (option)
    {
    case 0:
    {

        cout << "\n\n";
        cout << "------------CAP NHAT SO LUONG SACH TRONG THU VIEN------------\n";
        cout << "Moi ban nhap ten sach vua cho muon (Vui long nhap chinh xac ten sach): ";
        getline(cin, tenSach);

        int n = soLuongSach; // gán để cập nhật số sach, nếu kh bị ảnh hương trong lúc ghi
        fstream myFile("fileChuaSach.csv", ios::out);
        for (int i = 0; i < n; i++)
        { // n = soLuongSachMuon (tui gán để tránh bị đổi giá trị soLuong)
            if (tenSach == mangSach[i].tenSach)
            {
                continue;
            }
            myFile << mangSach[i].tenSach << "," << mangSach[i].theLoai << "," << mangSach[i].tenTacGia << "," << mangSach[i].nxb << "," << mangSach[i].namPhatHanh << endl;
        }

        docFile(soLuongSach, mangSach); // đọc lại để update số sách đã cho mượn
        myFile.close();
        cout << "\n------------------DA CAP NHAT------------------\n";
        cout << "Nhan phim bat ki de quay lai tinh nang quan ly.\n";
        system("pause");
        break;
    }

    case 1:
    {
        cout << "\n\n";
        cout << "------------CAP NHAT SO LUONG SACH TRONG THU VIEN------------\n";
        xuatFile();
        docFile(soLuongSach, mangSach); // update số sách đã được trả
        break;
    }
    }
}

void chinhSuaThongTin(int soLuongSachMuon, bookBorRe mangMuonTra[])
{ // sửa đối tên nếu sai
    // in hết thông tin để quản lý có thể xem thông tin nào cần sửa
    cout << "---------------------THONG TIN NGUOI MUON SACH--------------------- \n";
    for (int i = 0; i < soLuongSachMuon; i++)
    {
        inMuonTra(i, mangMuonTra);
    }
    string data1, data2;
    cout << "---------------------NHAP THONG TIN CAN CHINH SUA--------------------- \n";
    cout << "Moi ban nhap ten nguoi muon muon sua - ten sai (Vui long nhap dung ten ma thong tin vua in): ";
    getline(cin, data1);
    cout << "Ban se chinh sua ten nguoi muon thanh: ";
    getline(cin, data2);
    system("cls");
    fstream myFile;
    myFile.open("fileQuanLy.csv", ios::out);
    for (int i = 0; i < soLuongSachMuon; i++)
    {
        // in ra thông tin mới của sách
        if (data1 == mangMuonTra[i].borName)
        {
            // data1 = tên muốn sửa
            // data2 = tên sửa
            myFile << mangMuonTra[i].tenSach << "," << data2 << "," << mangMuonTra[i].borDay << "," << mangMuonTra[i].reDay << '\n';
            continue;
        }
        myFile << mangMuonTra[i].tenSach << "," << mangMuonTra[i].borName << "," << mangMuonTra[i].borDay << "," << mangMuonTra[i].reDay << endl;
    }
    myFile.close();
    cout << "\n------------------DA CHINH SUA XONG------------------\n";
    system("pause");
}