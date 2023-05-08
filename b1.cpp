// Bai 1: Xuat file chua thong tin sinh vien gom ten, lop, mssv, ma nganh
#include <iostream>
#include <fstream>
using namespace std;
struct sv
{
    char ten[30];
    char lop[12];
    char mssv[12];
    char maNganh[20];
};
void xuatFile(); // khong truyen doi so nen de trong
int main()
{
    xuatFile();
    return 0;
}
void xuatFile()
{
    fstream fout; // ten bien xuat file la fout
    fout.open("b1.csv", ios::out | ios::app);
    int n;
    cout << "\nSo luong sinh vien la ";
    cin >> n;
    sv a[n];
    cin.ignore();
    for (int i = 0; i < n; i++)
    {
        cout << "Nhap ten cua sinh vien thu " << i + 1 << ": ";
        cin.getline(a[i].ten, 29);
        cout << "Nhap lop cua sinh vien thu " << i + 1 << ": ";
        cin.getline(a[i].lop, 29);
        cout << "Nhap ma so cua sinh vien thu " << i + 1 << ": ";
        cin.getline(a[i].mssv, 29);
        cout << "Nhap ma nganh cua sinh vien thu " << i + 1 << ": ";
        cin.getline(a[i].maNganh, 29);
        fout << a[i].ten << "," << a[i].lop << "," << a[i].mssv << "," << a[i].maNganh << endl;
    }
    fout.close();
}