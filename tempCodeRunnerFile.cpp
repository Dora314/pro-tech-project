 n << endl; // vd kho 100 cuôn - 9 cuốn mượn
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
        chinhSuaThongTin(n, mangChuaSach);
        goto nhapLai;
    case 9:
        chinhSuaThongTin2(soLuongSachMuon, mangMuonTra);
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
    cout << "\n                 XOA SACH\n";
    cout << "===============================================\n";
    cout << "||Xoa sach theo ten sach          || Chon '1'||\n";
    cout << "||Xoa sach theo the loai          || Chon '2'||\n";
    cout << "||Xoa sach theo ten tac gia       || Chon '3'||\n";
    cout << "||Xoa sach theo nha xuat ban      || Chon '4'||\n";
    cout << "||Xoa sach theo nam xuat ban      || Chon '5'||\n";
    cout << "||Quay lai chon tinh nang         || Chon '0'||\n";
    cout << "===============================================\n";
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
        docFile(soLuongSach, a);
        system("pause");
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
        docFile(soLuongSach, a);
        system("pause");
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
        docFile(soLuongSach, a);
        system("pause");
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
        docFile(soLuongSach, a);
        system("pause");
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
        docFile(soLuongSach, a);
        system("pause");
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
        myFile.close();
        cout << "\n------------------DA XOA THANH CONG------------------\n";
        system("pause");
    }
}

void hamCapNhatSoLuongSachTrongThuVien(int &soLuongSach, book mangSach[])
{
    int option, count = 1;
    string tenSach;
    cout << "\n";
    cout << "                        CAP NHAT SO LUONG SACH\n";
    cout << "===========================================================================\n";
    cout << "||Cap nhat sach DA CHO MUON vao thu vien (Sach da cho muon)    || Nhap 0 ||\n"; // sau khi xóa ra fileQuanLy -> nhập vào fileChuaSach
    cout << "||Cap nhat sach DA TRA vao thu vien (Sach duoc tra lai)        || Nhap 1 ||\n"; // xóa sách từ fileChuaSach -> nhập sang fileQuanLy
    cout << "===========================================================================\n";
    do
    {
        cout << "Moi ban nhap: ";
        cin >> option;
        cin.ignore();
        if (!(option == 0 || option == 1))
        {
            cout << "Lua chon khong hop le, Vui long nhap lai \n";
        }