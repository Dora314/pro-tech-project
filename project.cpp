#include <bits/stdc++.h>
using namespace std;
struct date
{
    int d;
    int m;
    int y;
};
struct bookInfo
{
    char bookName[50];
    char bookCate[50];
    char bookAuthor[50];
    char publisher[50];
    date year;
};
struct bookBorRe
{
    bookInfo name;
    char borName[50];
    date borDay;
    date reDay;
};
int main()
{
    return 0;
}
