#include"QFloat.h"

QFloat Arr_To_QFloat(const string& binArr)
{

	QFloat number;
	for (int i = 0; i < MAX; i++)
	{
		if (binArr[i] == '1')
		{
			number.data[i / 32] = number.data[i / 32] | (1 << (32 - 1 - i % 32));
		}
	}
	return number;
}


string QFloat_To_Arr(const QFloat& number)
{
	string a;
	for (int i = 0; i < MAX; i++)
	{
		if ((number.data[i / 32] >> (32 - 1 - i % 32)) & 1 == 1)
		{
			a.push_back('1');
		}
		else
		{
			a.push_back('0');
		}
	}
	return a;
}

int SoPhanTuSauDauCham(string phanThapPhan)
{
	int dauCham = phanThapPhan.find_first_of('.');
	return phanThapPhan.length() - dauCham - 1;
}

//Tao so thuc 1 vs n so 0 ngoai sau
string Float_1(int n)
{
	string res = "1.";
	for (int i = 0; i < n; i++)
		res.push_back('0');
	return res;
}


//chuyen phan thap phan cua QFloat tu Dec -> Bin
string DecToBin_phanThapPhan(string phanThapPhan)
{
	string res;
	while (1)
	{
		phanThapPhan = phanThapPhan * 2;
		int len_sauDauCham = SoPhanTuSauDauCham(phanThapPhan);
		string so1 = Float_1(len_sauDauCham);

		if (phanThapPhan.compare(so1) == 0)
		{
			res.push_back('1');
			break;
		}
		else if (phanThapPhan.compare(so1) == 1)
		{
			res.push_back('1');
			int DauCham = phanThapPhan.find_first_of('.');
			for (int i = 0; i < DauCham; i++)
				phanThapPhan[i] = '0';
		}
		else
		{
			res.push_back('0');
		}
	}
	return res;
}


//Tach phan nguyen va phan thap phan cua QFloat
void tachQFloat(string bigFloat, string& phanNguyen, string& phanThapPhan)
{
	int len = bigFloat.length();
	int dauCham = bigFloat.find_first_of('.');

	phanNguyen.assign(bigFloat, 0, dauCham);

	phanThapPhan.assign(bigFloat, dauCham, len - phanNguyen.length());//dg co dang (.x)
	phanThapPhan.insert(0, 1, '0');//dua ve dang (0.x)
}


//Ca so am va so duong deu dua ve 128 bit, cat toi dau day
string DecToBin_QFloat(string bigFloat)
{
	string res, phanNguyen, phanThapPhan;

	//tach rieng ( phan nguyen ) va ( phan thap phan )
	tachQFloat(bigFloat, phanNguyen, phanThapPhan);

	//chuyen phan nguyen sang nhi phan
	res = DecToBin(phanNguyen);

	//Vi ham DecToBin luôn trả về mảng 128 phần tử, nên phải cắt bớt các số 0 ở đầu
	remove0(res);

	res.append("."); // them dau . de ngan cach phan nguyen va phan thap phan

	res.append(DecToBin_phanThapPhan(phanThapPhan));// chuyen phan thap phan sang nhi phan, sau do gop chuoi

	return res;
}

//Chuan hoa ve dang ( 1.F * 2^E )
int chuanHoaQFloat(string& floatNum, int chuan = MAX)
{
	// Cai switch nay chi de co the test may so nho, luc nop bai thi xoa
	int bit = 112;
	switch (chuan)
	{
	case 32:
		bit = 23;
		break;
	case 64:
		bit = 52;
		break;
	default:
		cout << "\nChuan ko hop le" << endl;
		break;
	}

	//Vi chi su dung phan F, neu i = (vi tri so 1 dau tien), xoa cac ki tu tu i tro ve truoc

	int dauCham = floatNum.find_first_of('.');
	int so1DauTien = floatNum.find_first_of('1');

	floatNum.erase(dauCham, 1);//xoa dau cham cu
	floatNum.erase(0, so1DauTien + 1);//xoa cac ki tu i tro ve truoc

	//Them 0 vao cuoi sao cho du so bit
	if (floatNum.length() < bit)
		floatNum.insert(floatNum.length(), bit - floatNum.length(), '0');

	return  (dauCham > so1DauTien) ? dauCham - so1DauTien - 1 : dauCham - so1DauTien;// so mu E

}

//chuyen phan mu qua nhi phan, chuoi nay chac chan du exp_bit
string DecToBin_exp(int soMuE, int chuan = MAX)
{
	int k = 15;
	switch (chuan)
	{
	case 32:
		k = 8;
		break;
	case 64:
		k = 11;
		break;
	default:
		cout << "\nChuan ko hop le." << endl;
		break;
	}


	int bias = pow(2, k - 1) - 1;
	int exp = soMuE + bias;
	string bin = toString(exp);

	bin = DecToBin(bin);//chuyen qua nhi phan

	//De chac chan chuoi nay du exp_bit
	if (bin.length() < k)//Neu thieu thi them 0 vao dau chuoi
		bin.insert(0, k - bin.length(), '0');
	else if (bin.length() > k)//Neu du thi cat sao cho con exp_bit
		bin.erase(0, bin.length() - k);

	return bin;
}


void ScanQFloat(QFloat& x, string Fnum)
{
	/*B1: Xet dau Fnum
	  B2: Chuyen Fnum sang nhi phan
	  B3: Chuyen hoa ve dang 1.F * 2^E
	  B4: Tinh exp va chuyen exp sang nhi phan
	  B5: Gop chuoi lai thanh chuoi hoan chinh Sign_EXP_Fraction

	*/
	string res;

	char SignBit = IsSign(Fnum) ? '1' : '0';//B1
	string Fbin = DecToBin_QFloat(Fnum);//B2
	int E = chuanHoaQFloat(Fbin, 32);// B3, dg tinh theo chuan 32 bit
	string exp_bin = DecToBin_exp(E, 32);//B4
	//B5
	res.push_back(SignBit);
	//res.push_back(' ');
	res.append(exp_bin);
	//res.push_back(' ');
	res.append(Fbin);

	x = Arr_To_QFloat(res);
	
	//Luc nop bai xoa cai nay
	cout << endl;
	for (int i = 0; i < 4; i++)
	{
		cout << bitset<32>(x.data[i]);
	}
	
}

string _2_Mu_Tru_N(int n)
{
	string res = "1";
	for (int i = 0; i < n; i++)
	{
		res = res * 5;
	}
	int len = res.size();
	n = n - len;
	if (n > 0)
	{
		res.insert(0, n, '0');
	}
	return res;
}

string BinToDec_PhanThapPhan(string str)
{
	string tmp, res = "0";
	int n = str.length();

	for (int i = 0; i < n; i++)
	{
		if (str[i] == '1')
		{
			tmp = _2_Mu_Tru_N(i + 1);
			canBang2Chuoi(tmp, res);
			res = res + tmp;
		}
	}
	return res;
}
void xoa_0_Cuoi_String(string &str)
{
	int n = str.size();
	int i;
	for (i = n - 1; i >= 0; i--)
	{
		if (str[i] != '0')
		{
			break;
		}
	}
	str.erase(i + 1);
}


string BinToDec_QFloat(string arr)
{
	string res;
	if (arr[0] == '1')
	{
		res.push_back('-');
	}
	arr.erase(0, 1);
	string E_str;
	string S;

	E_str = arr.substr(0, 15);
	S = arr.substr(15);

	string E = BinToDec(E_str);
	E = E - "16383";

	xoa_0_Cuoi_String(S);
	string x = "1." + S;
	x.erase(1, 1);// xoa dau . 

	//them dau . vao
	x.insert(stoi(E) + 1, 1, '.');

	string PhanNguyen, PhanThapPhan;
	tachQFloat(x, PhanNguyen, PhanThapPhan);

	// xoa dang 0. cua phan thap phan
	PhanThapPhan.erase(0, 2);

	//chuyen phan nguyen ve dang thap phan
	PhanNguyen = BinToDec(PhanNguyen);

	//chuyen phan thap phan sang dec
	PhanThapPhan = BinToDec_PhanThapPhan(PhanThapPhan);

	res += PhanNguyen;
	res += ".";
	res += PhanThapPhan;
	return res;
}


void PrintQfloat(QFloat number)
{
	string arr = QFloat_To_Arr(number);
	string res = BinToDec_QFloat(arr);
	cout << res;

}