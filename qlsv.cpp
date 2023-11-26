#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <fstream>
#include <conio.h>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;

typedef struct student
{
    string name;
    float age;
    float score;
    string ten;
} sv;
void readfilesdata(sv list[], int &num)
{

    ifstream input("data.txt");
    num++;

    while (getline(input, list[num].name, ';'))
    {

        input >> list[num].age;
        input.ignore();
        input >> list[num].score;
        input.ignore();
        num++;
    }
    num--;
}
void title()
{
    cout << "---------Student Infomation List---------\n";
    cout << "+-------+----------------+--------+-------+"
         << "\n";
    cout << "|" << setw(5) << " STT   "
         << "|" << setw(10) << "  Ho Ten        "
         << "|" << setw(5) << " Tuoi   "
         << "|"
         << " Diem  "
         << "|"
         << "\n";
    cout << "+-------+----------------+--------+-------+"
         << "\n";
}
void printfiledata(sv list[], int &num)

{
    title();

    for (int i = 1; i <= num; i++)
    {

        cout << "| " << setw(6) << left << i
             << "| " << setw(15) << left << list[i].name
             << "| " << setw(7) << left << list[i].age
             << "| " << setw(6) << left << list[i].score << "|"
             << "\n";
    }
    cout << "+-------+----------------+--------+-------+"
         << "\n";
}
void addstudent(sv list[], int &num)
{
    string s;
    num++;
    cout << "Tien hanh them sinh vien thu " << num << " : "
         << "\n";
    cout << "Nhap ten: ";
    cin.ignore();
    getline(cin, s);
    list[num].name = s;

    cout << "Nhap tuoi: ";
    cin >> list[num].age;

    cout << "Nhap diem: ";
    cin >> list[num].score;
}
void fixstudent(sv list[], int &num)
{
    int f;
    string s;
    cout << "Nhap so thu tu sinh vien can sua: ";
    cin >> f;
    cout << "Nhap ten: ";
    cin.ignore();
    getline(cin, s);
    list[f].name = s;

    cout << "Nhap tuoi: ";
    cin >> list[f].age;

    cout << "Nhap diem: ";
    cin >> list[f].score;
}

void deletestudent(sv list[], int &num)
{
    int f;
    cout << "Nhap so thu tu sinh vien can xoa: ";
    cin >> f;
    cout << "\n"
         << "Tien hanh xoa sinh vien STT " << f;
    for (int i = f; i < num; i++)
    {
        list[i] = list[i + 1];
    }
    num--;
}
void detatechname(sv list[], int &num)
{
    string ten;
    for (int i = 1; i <= num; i++)
    {
        int t = list[i].name.find_last_of(' ');
        list[i].ten = list[i].name.substr(t + 1);
    }
}
void findstudent(sv list[], int &num)

{
    string s;

    cout << "Nhap ky tu can tim kiem: ";
    cin >> s;
    title();
    for (int i = 1; i <= num; i++)
    {
        int f = -1;
        f = list[i].ten.find(s);
        if (f != -1)
        {
            cout << "| " << setw(6) << left << i
                 << "| " << setw(15) << left << list[i].name
                 << "| " << setw(7) << left << list[i].age
                 << "| " << setw(6) << left << list[i].score << "|"
                 << "\n";
        }
    }
    cout << "+-------+----------------+--------+-------+"
         << "\n";
}
bool sortname(const sv &a, const sv &b)
{
    return a.ten < b.ten;
}
bool sortage(const sv &a, const sv &b)
{
    return a.age < b.age;
}
bool sortscore(const sv &a, const sv &b)
{
    return a.score < b.score;
}
void sortstudent(sv list[], int &num)
{
    int s;
    cout << "Tuy chon cach sap xep: "
         << "\n";
    cout << setw(2) << "  [1]--Sap xep theo ten ABC: "
         << "\n";
    cout << setw(2) << "  [2]--Sap xep theo tuoi tang dan: "
         << "\n";
    cout << setw(2) << "  [3]--Sap xep theo diem tang dan: "
         << "\n";
    cin >> s;
    switch (s)
    {
    case 1:
        detatechname(list, num);
        sort(list, list + num + 1, sortname);
        break;
    case 2:

        sort(list, list + num + 1, sortage);
        break;
    case 3:
        sort(list, list + num + 1, sortscore);
        break;
    }
    printfiledata(list, num);
}
void stats_score(sv list[], int &num)
{
    float dem_g = 0, dem_k = 0, scoremax = 0;
    float diemtb;
    for (int i = 1; i <= num; i++)
    {
        scoremax = max(scoremax, list[i].score);
        diemtb += list[i].score;
        if (list[i].score >= 8)
            dem_g++;
        else if (list[i].score >= 4)
            dem_k++;
    }
    diemtb /= float(num);
    dem_g = (dem_g / float(num)) * 100;
    dem_k = (dem_k / float(num)) * 100;

    cout << "(!)---Diem trung binh ca lop : " << diemtb << "\n";
    cout << "(!)---Ti le sinh vien gioi : " << dem_g << "%"
         << "\n";
    cout << "(!)---Ti le sinh vien kha : " << dem_k << "%"
         << "\n";
    cout << "(!)---Ti le sinh vien yeu : " << 100 - dem_g - dem_k << "%"
         << "\n";
    cout << "(!) Sinh vien co diem cao nhat la: "
         << "\n";
    for (int i = 1; i <= num; i++)
    {
        if (list[i].score == scoremax)
            cout << "    " << list[i].name << "\n";
    }
}
void save(sv list[], int &num)
{

    ofstream output("data.txt");
    for (int i = 1; i <= num; i++)
    {
        output << list[i].name << ";"
               << list[i].age << " "
               << list[i].score << endl;
    }
    output.close();
    cout << "Da luu du lieu vao file data.txt." << endl;
}
int main()
{

    sv list[20];
    string p;
    int s, num = 0, checkthem = 0;
    while (true)
    {
        cout << "Danh sach thao tac: "
             << "\n"
             << "1 - In danh sach SV"
             << "\n"
             << "2 - Them"
             << "\n"
             << "3 - Sua"
             << "\n"
             << "4 - Xoa"
             << "\n"
             << "5 - Tim Kiem"
             << "\n"
             << "6 - Sap xep"
             << "\n"
             << "7 - Thong ke"
             << "\n"
             << "8 - Sao luu"
             << "\n"
             << "0 - Exit"
             << "\n";

        cout << "Nhap lenh ";
        cin >> s;

        if (s == 1)
        {
            cout << "[1]---In danh sach sinh vien:"
                 << "\n";
            if (checkthem == 0)
            {
                readfilesdata(list, num);
                checkthem++;
            }

            printfiledata(list, num);
        }
        else if (s == 2)
        {
            cout << "[2]---Them sinh vien:"
                 << "\n";
            addstudent(list, num);
        }
        else if (s == 3)
        {
            cout << "[3]---Sua sinh vien:"
                 << "\n";
            fixstudent(list, num);
        }
        else if (s == 4)
        {
            cout << "[4]---Xoa sinh vien:"
                 << "\n";
            deletestudent(list, num);
        }
        else if (s == 5)
        {
            cout << "[5]---Tim kiem sinh vien:"
                 << "\n";
            detatechname(list, num);
            findstudent(list, num);
        }
        else if (s == 6)
        {
            cout << "[6]---Sap xep sinh vien:"
                 << "\n";
            sortstudent(list, num);
        }
        else if (s == 7)
        {
            cout << "[7]---Thong ke sinh vien:"
                 << "\n";
            stats_score(list, num);
        }
        else if (s == 8)
        {
            cout << "[8]---Sao luu sinh vien:"
                 << "\n";
            save(list, num);
        }

        else if (s == 0)
        {
            cout << "Da thoat chuong trinh";
            return 0;
        }

        cout << "\n"
             << "press any key to continue...";
        cin.ignore();
        getline(cin, p);
        system("cls");
    }
    return 0;
}