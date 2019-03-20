#pragma once
#include"xuLiStringBigInt.h"
#include"QInt.h"

typedef struct
{
	uint32_t data[4];
}QFloat;

string QFloat_To_Arr(const QFloat& number);

QFloat Arr_To_QFloat(const string& binArr);


int SoPhanTuSauDauCham(string phanThapPhan);

//Tao so thuc 1 vs n so 0 ngoai sau
string Float_1(int n);

//chuyen phan thap phan cua QFloat tu Dec -> Bin
string DecToBin_phanThapPhan(string phanThapPhan);

//Tach phan nguyen va phan thap phan cua QFloat
void tachQFloat(string bigFloat, string& phanNguyen, string& phanThapPhan);

//Dung voi so duong, sai vs so am do ham DecToBin dua ve 128 bit
string DecToBin_QFloat(string bigFloat);

//Chuan hoa ve dang ( 1.F * 2^E )
int chuanHoaQFloat(string& floatNum, int chuan = MAX);

//chuyen phan mu qua nhi phan, chuoi nay chac chan du exp_bit
string DecToBin_exp(int soMuE, int chuan = MAX);

void ScanQFloat(QFloat& x, string Fnum);

string _2_Mu_Tru_N(int n);

string BinToDec_PhanThapPhan(string str);

string BinToDec_QFloat(string arr);

string _2_Mu_Tru_N(int n);
