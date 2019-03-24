#pragma once
#include"xuLiStringBigInt.h"
#include"QInt.h"

typedef struct
{
	uint32_t data[4];
}QFloat;



int SoPhanTuSauDauCham(string phanThapPhan);

string Float_1(int n);

void tachQFloat(string bigFloat, string& phanNguyen, string& phanThapPhan);

void chuanHoaQFloat(string &number, int &soMu);

QFloat Arr_To_QFloat(const string& binArr);

string DecToBin_QFloat(string number);

void ScanQFloat(QFloat &x, string number);

string QFloat_To_Arr(const QFloat& number);

void canBangHaiChuoi_2(string &a, string &b);

string _2_Mu_Tru_N(int n);

string BinToDec_PhanThapPhan(string str);

void xoa_0_Cuoi_String(string &str);

string BinToDec_QFloat(string arr);

void PrintQfloat(QFloat number);