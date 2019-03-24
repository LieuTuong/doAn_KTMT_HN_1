#include"QFloat.h"





int SoPhanTuSauDauCham(string phanThapPhan)
{
	int dauCham = phanThapPhan.find_first_of('.');
	return phanThapPhan.length() - dauCham - 1;
}
string Float_1(int n)
{
	string res = "1.";
	for (int i = 0; i < n; i++)
	{
		res.push_back('0');
	}
	return res;
}


void tachQFloat(string bigFloat, string& phanNguyen, string& phanThapPhan)
{
	int len = bigFloat.length();
	int dauCham = bigFloat.find_first_of('.');
	phanNguyen.assign(bigFloat, 0, dauCham);
	phanThapPhan.assign(bigFloat, dauCham, len - phanNguyen.length());//dg co dang (.x)
	phanThapPhan.insert(0, 1, '0');//dua ve dang (0.x)
}


void chuanHoaQFloat(string &number, int &soMu)
{
	string phanNguyen, phanThapPhan;
	tachQFloat(number, phanNguyen, phanThapPhan);
	phanNguyen = DecToBin(phanNguyen);

	bool kiemTra = false;
	bool kiemTra_1 = false; // neu so 1 nam o trong phan thap phan
	bool flag = false;
	int n_PhanNguyen = phanNguyen.size();

	int i = 0; // luu so luong chu so sau 1 cua phan nguyen
	if (phanNguyen[0] == '1')
	{
		i = n_PhanNguyen - 1;
		kiemTra = true;
		flag = true;
	}
	string sub = phanNguyen.substr(n_PhanNguyen - i);

	string res;
	res += sub; // ket qua
	string tmp;
	int k = 0, m = 0; // bien dem 
	int j = 0; // luu vi tri so 1 dau tien cua phan thap phan
	int len_sauDauCham;
	string so1;		// de tao chuoi string = 1 de kiem tra sau khi * 2
	bool kiemTra_2 = false;  // 
	while (1)
	{
		phanThapPhan = phanThapPhan * 2;
		len_sauDauCham = SoPhanTuSauDauCham(phanThapPhan);
		so1 = Float_1(len_sauDauCham);  // tao so 1 
		if (phanThapPhan == so1)
		{
			tmp.push_back('1');
			break;
		}
		else if (phanThapPhan > so1)
		{
			if (kiemTra_2 == false)
			{
				kiemTra_1 = true;
			}
			tmp.push_back('1');
			int DauCham = phanThapPhan.find_first_of('.');
			for (int i = 0; i < DauCham; i++)
			{
				phanThapPhan[i] = '0';
			}
		}
		else
		{
			tmp.push_back('0');
		}

		k++; // tang k
		if (kiemTra_2 == false && kiemTra_1 == true)
		{
			j = k;
			kiemTra_2 = true;
			kiemTra = true;
		}
		if (kiemTra == true)
		{
			m++;
		}
		if (flag == true)
		{
			if (m == 112 - i)
			{
				break;
			}
		}
		else
		{
			if (m == 112 - i + 1)
			{
				break;
			}
		}
	}

	if (kiemTra_1 == false && flag == false)
	{
		j = tmp.size();
		tmp = "0";
	}
	else
	{
		if (flag == false)
		{
			tmp = remove0(tmp);
			tmp.erase(0, 1);
		}
	}
	res += tmp;
	if (m + i >= 112)
	{
		phanThapPhan = phanThapPhan * 2;
		len_sauDauCham = SoPhanTuSauDauCham(phanThapPhan);
		so1 = Float_1(len_sauDauCham);
		if (phanThapPhan == so1 || phanThapPhan > so1)
		{
			res = CongBit(res, "1");
		}
	}
	string ketQua;
	soMu = flag == false ? -j : i;
	ketQua += "1.";
	ketQua += res;
	number = ketQua;
}



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


string DecToBin_QFloat(string number)
{
	string res;
	if (IsSign(number) == true)
	{
		res.push_back('1');
		number.erase(0, 1);
	}
	else
	{
		res.push_back('0');
	}
	int E;
	chuanHoaQFloat(number, E);
	E += 16383;
	string str_E = DecToBin(to_string(E));
	if (str_E.size() < 15)
	{
		str_E.insert(0, 1, '0');
	}
	number.erase(0, 2);

	int n = number.size();
	if (n < 112)
	{
		number.insert(n, 112 - n, '0');
	}
	res = res + str_E + number;
	return res;
}

void ScanQFloat(QFloat &x, string number)
{
	string res;
	res = DecToBin_QFloat(number);
	cout << res << endl;
	x = Arr_To_QFloat(res);
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



void canBangHaiChuoi_2(string &a, string &b)
{
	int a_len = a.length(), b_len = b.length();
	if (a_len > b_len)
	{
		b.insert(b_len, a_len - b_len, '0');
	}
	else
	{
		a.insert(a_len, b_len - a_len, '0');
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
			canBangHaiChuoi_2(tmp, res);
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
	if (E > "16383")
	{
		E = E - "16383";
	}
	else
	{
		E = "16383" - E;
		E.insert(0, 1, '-');
	}

	xoa_0_Cuoi_String(S);
	string x = "1." + S;
	x.erase(1, 1);// xoa dau . 

	//them dau . vao
	int doDoi = stoi(E);
	if (doDoi > 0)
	{
		x.insert(doDoi + 1, 1, '.');
	}
	else
	{
		x.insert(0, abs(doDoi), '0');
		x.insert(1, 1, '.');

	}

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

