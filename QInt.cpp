#include "xuLiStringBigInt.h"
#include"QInt.h"
#include <bitset>



// do ko chac unsigned int luon la 4 bytes, nen dung unit32_t
struct QInt
{
	uint32_t data[4] = { 0 };

	QInt& operator=(const QInt &number2)
	{
		if (this != &number2)
		{
			for (int i = 0; i < 4; i++)
			{
				data[i] = number2.data[i];
			}
		}
		return *this;
	}

	QInt& operator=(const int &number2)
	{
		string str = to_string(number2);
		str = DecToBin(str);
		int n = str.length();
		if (n < 128)
		{
			str.insert(0, 128 - n, '0');
		}
		QInt number;
		for (int i = 0; i < MAX; i++)
		{
			if (str[i] == '1')
			{
				number.data[i / 32] = number.data[i / 32] | (1 << (32 - 1 - i % 32));
			}
		}
		return *this = number;
	}
};


// Ham lay bu 1
string bu1(string a)
{
	string tmp;
	for (int i = 0; i < MAX; i++)
	{
		char x = (a[i] == '1') ? '0' : '1';
		tmp.push_back(x);
	}
	return tmp;
}


//Ham lay bu 2
string bu2(string a)
{
	string dayBu1 = bu1(a);
	int soDu = 1;
	string bu2;
	for (int i = MAX - 1; i >= 0; i--)
	{
		char x;
		if (dayBu1[i] == '0' && soDu == 1)
		{
			x = '1';
			soDu = 0;
		}
		else if (dayBu1[i] == '0'&& soDu == 0)
		{
			x = '0';
			soDu = 0;
		}
		else if (dayBu1[i] == '1' && soDu == 0)
		{
			x = '1';
			soDu = 0;
		}
		else if (dayBu1[i] == '1'&& soDu == 1)
		{
			x = '0';
			soDu = 1;
		}
		bu2.insert(0, 1, x);
	}
	return bu2;
}


//Ham chuyen tu QInt sang mang int a[MAX]
string QInt_To_Arr(const QInt& number)
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



//Ham chuyen tu mang a sang Qint

QInt Arr_To_QInt(const string& binArr)
{

	string _128bit = binArr;
	int n = binArr.length();
	if (n < 128)
	{
		_128bit.insert(0, MAX - n, '0');
	}

	QInt number;
	for (int i = 0; i < MAX; i++)
	{
		if (_128bit[i] == '1')
		{
			number.data[i / 32] = number.data[i / 32] | (1 << (32 - 1 - i % 32));
		}
	}
	return number;
}

//he 10 -> he 2
string DecToBin(string userInputStr)
{
	string binary(MAX, '0');

	//Kiem tra xem userInputStr co phai la so am ko
	bool IsSigned = IsSign(userInputStr);
	if (IsSigned)
	{
		userInputStr = absolute(userInputStr); //Lay tri tuyet doi cua chuoi
	}


	// chia userInputStr cho 2 r lay so du bo vao binary
	for (int i = 0; userInputStr.length() != 0; i++)
	{
		if ((userInputStr[userInputStr.length() - 1] - 48) % 2 != 0) {
			binary[i] = '1';
			userInputStr[userInputStr.length() - 1] -= 1;
		}
		else binary[i] = '0';
		userInputStr = chia2(userInputStr);
	}

	//Dao chuoi lai
	binary = reverse(binary);

	if (IsSigned) //Neu la so am, thi bieu dien so bu 2
	{
		binary = bu2(binary);
	}

	return binary;

}


// he 2 -> he 10
string BinToDec(string bit)
{
	string decNum, tmp;
	if (bit.length() < MAX)
	{
		bit.insert(0,MAX-bit.length(),'0');
	}
	

	for (int i = 0; i < MAX; i++)
	{
		if (bit[i] == '1')
		{
			tmp = _x_mu_n(2, MAX - i - 1);
			if (i == 0)// so la so am
			{
				tmp = tmp * -1;
			}
		}
		else
			tmp = "0";
		decNum = decNum + tmp;
	}
	return decNum;
}

//ham chuyen (bo 4 bit) Bin sang gia tri HEX tuong ung
char nibbles(string binVal)
{
	char c;

	if (binVal == "0000")      c = '0';
	else if (binVal == "0001") c = '1';
	else if (binVal == "0010") c = '2';
	else if (binVal == "0011") c = '3';
	else if (binVal == "0100") c = '4';
	else if (binVal == "0101") c = '5';
	else if (binVal == "0110") c = '6';
	else if (binVal == "0111") c = '7';
	else if (binVal == "1000") c = '8';
	else if (binVal == "1001") c = '9';
	else if (binVal == "1010") c = 'A';
	else if (binVal == "1011") c = 'B';
	else if (binVal == "1100") c = 'C';
	else if (binVal == "1101") c = 'D';
	else if (binVal == "1110") c = 'E';
	else if (binVal == "1111") c = 'F';

	return c;
}


//--------------- Chuyen tu he 16 sang he 2 ----------------------
string tu16_2(char x)
{
	string res;

	if (x == '0')      res = "0000";
	else if (x == '1') res = "0001";
	else if (x == '2') res = "0010";
	else if (x == '3') res = "0011";
	else if (x == '4') res = "0100";
	else if (x == '5') res = "0101";
	else if (x == '6') res = "0110";
	else if (x == '7') res = "0111";
	else if (x == '8') res = "1000";
	else if (x == '9') res = "1001";
	else if (x == 'A'||x=='a') res = "1010";
	else if (x == 'B'||x=='b') res = "1011";
	else if (x == 'C'||x=='c') res = "1100";
	else if (x == 'D'||x=='d') res = "1101";
	else if (x == 'E'||x=='e') res = "1110";
	else if (x == 'F'||x=='f') res = "1111";

	return res;
		
}

string HexToBin(string HexStr)
{
	string res = "";
	for (int i = 0; i < HexStr.length(); i++)
	{
		res.append(tu16_2(HexStr[i]));
	}
	return res;
}

//-----------------------------------------------------------------

//----------------chuyen tu he 16 sang he 10 (theo chuan 128 bit)----------

string HexToDec(string HexStr)
{
	string bin = HexToBin(HexStr);
	return BinToDec(bin);
}

// he 2 -> he 16
string BinToHex(string bin)
{
	string res = "0x";
	int Blen = bin.length();
	if (Blen % 4 != 0) //neu Blen ko chia het cho 4, thi them n so 0 sao cho (n + Blen) chia het cho 4
	{
		int newLen = 4 * ((Blen / 4) + 1);
		bin.insert(0, newLen - Blen, '0');
	}

	//Tach chuoi thanh tung bo 4, r doi nhung bo 4 do sang Hex tuong ung
	for (int i = 0; i < bin.length(); i += 4)
	{
		string bo4Bit;
		int k = i;
		int j = 1;
		while (j <= 4)
		{
			bo4Bit.push_back(bin[k]);
			k++;
			j++;
		}
		res.push_back(nibbles(bo4Bit));
	}

	return res;
}


// he 10 -> he 16
string DecToHex(string dec)
{
	string res;
	res = DecToBin(dec);
	res = BinToHex(res);

	return res;
}

//Ham nhap so QInt
void ScanQInt(QInt &number, string userInputStr)
{
	string binArr = DecToBin(userInputStr);

	number = Arr_To_QInt(binArr);

	cout << endl;

	//Luc nop bai thi xoa cai nay
	for (int i = 0; i < 4; i++)
	{
		cout << bitset<32>(number.data[i]);
	}
}

//ham xuat so QInt, xuat ra so he thap phan
void PrintQInt(QInt number)
{
	//chuyen tu QInt sang mang a
	string bin = QInt_To_Arr(number);

	//Tu mang nhi phan a chuyen sang so thap phan	
	string decNum = BinToDec(bin);

	cout << "\nSo chuyen sang he thap phan: ";
	cout << decNum;
}


//=============================  CAC TOAN TU <, >, >=, <= , ==, =
bool IsNegative(string num)
{
	return (num[0] == '1') ? true : false;
}

bool IsEqual(const QInt& N1, const QInt& N2)
{
	string n1 = QInt_To_Arr(N1);
	string n2 = QInt_To_Arr(N2);
	return n1 == n2;
}

bool IsLess(const QInt& N1, const QInt& N2)
{
	//chuyen QInt qua mang de so sanh
	string n1 = QInt_To_Arr(N1);
	string n2 = QInt_To_Arr(N2);

	//xet dau cua 2 QInt 
	bool sign1 = IsNegative(n1);
	bool sign2 = IsNegative(n2);

	if (sign1 && !sign2)// n1 am, n2 duong
	{
		return true;
	}
	else if (!sign1 && sign2)
	{
		return false;
	}

	else// n1, n2 cung dau 
	{
		int viTriBit1_n1 = n1.find_first_of('1');
		int viTriBit1_n2 = n2.find_first_of('1');

		while (1)
		{
			{
				if (viTriBit1_n1 > viTriBit1_n2)//vi tri bit 1 cua a > vi tri bit 1 dau tien cua b
					return true;
				else if (viTriBit1_n1 < viTriBit1_n2)
					return false;
				else  //viTriBit1_n1 == viTriBit1_n2
				{
					viTriBit1_n1 = n1.find_first_of('1', viTriBit1_n1 + 1); //Tim vi tri bit 1 tiep theo
					viTriBit1_n2 = n2.find_first_of('1', viTriBit1_n2 + 1);
				}
			}
		}
	}

}

bool IsGreater(const QInt& N1, const QInt& N2)
{
	return !IsLess(N1, N2) && !IsEqual(N1, N2);
}

bool operator < (const QInt& N1, const QInt& N2)
{
	return IsLess(N1, N2);
}

bool operator > (const QInt& N1, const QInt& N2)
{
	return IsGreater(N1, N2);
}

bool operator <= (const QInt& N1, const QInt& N2)
{
	return IsLess(N1, N2) || IsEqual(N1, N2);
}

bool operator >= (const QInt& N1, const QInt& N2)
{
	return IsGreater(N1, N2) || IsEqual(N1, N2);
}

bool operator == (const QInt& N1, const QInt& N2)
{
	return IsEqual(N1, N2);
}

//==================================================================================

// ===================TOAN TU &, |, ^, ~ , << , >>
QInt operator & (const QInt& a, const QInt& b)
{
	QInt res;
	for (int i = 0; i < 4; i++)
	{
		res.data[i] = a.data[i] & b.data[i];
	}
	return res;
}




QInt operator | (const QInt& a, const QInt& b)
{
	QInt res;
	for (int i = 0; i < 4; i++)
	{
		res.data[i] = a.data[i] | b.data[i];
	}
	return res;
}


QInt operator ^ (const QInt& a, const QInt& b)
{
	QInt res;
	for (int i = 0; i < 4; i++)
	{
		res.data[i] = a.data[i] ^ b.data[i];
	}
	return res;
}


QInt operator ~ (const QInt& a)
{
	QInt res;
	for (int i = 0; i < 4; i++)
	{
		res.data[i] = ~a.data[i];
	}
	return res;
}


string dichPhai(const string& a, int bit)
{
	string res;
	if (bit > a.length()) return res;//neu dich so luong bit nhieu hon 128, thi toan bi mang se = 0
	if (bit < 0)
	{
		cout << "\nSo luong bit dich khong hop le." << endl;
		res = a;
	}
	else
	{
		char tmp = (IsNegative(a)) ? '1' : '0';
		for (int i = a.length() - 1; i >= 0; i--)
		{
			char c = (i - bit) < 0 ? tmp : a[i - bit];
			res.push_back(c);
		}
	}
	res = reverse(res);

	return res;
}

string dichTrai(const string& b, int bit)
{
	string res;
	if (bit > b.length()) return res;
	if (bit < 0)
	{
		cout << "\nSo luong bit dich khong hop le" << endl;
		res = b;
	}
	else
	{
		for (int i = 0; i < b.length(); i++)
		{
			char c = (i + bit) > (b.length() - 1) ? '0' : b[i + bit];
			res.push_back(c);
		}
	}
	return res;
}


QInt operator >> (const QInt& a, unsigned int bit)
{
	string res;
	string A = QInt_To_Arr(a);
	res = dichPhai(A, bit);
	return  Arr_To_QInt(res);
}

QInt operator << (const QInt& a, int bit)
{

	string A = QInt_To_Arr(a);
	string res = dichTrai(A, bit);
	return  Arr_To_QInt(res);
}



QInt rol(const QInt& a,int bit)
{
	string A = QInt_To_Arr(a);
	string tmp;

	tmp.assign(A, 0, bit);
	A.erase(0, bit);
	A.append(tmp);
	
	return  Arr_To_QInt(A);
}



QInt ror(const QInt& a,int bit)
{
	string A = QInt_To_Arr(a);
	string tmp;

	tmp.assign(A, 0, MAX - bit);
	A.erase(0,MAX-bit);
	A.append(tmp);

	return Arr_To_QInt(A);
}

//===================================================================================================


//================================ TOAN TU + - * /
string CongBit(const string& A, const string& B)
{
	string a = A, b = B;
	canBang2Chuoi(a, b);
	int n = a.size();
	int temp = 0;
	string res(n, '0');
	for (int i = n - 1; i >= 0; i--)
	{
		temp = stringToNum(a[i]) + stringToNum(b[i]) + temp;
		if (temp == 2)
		{
			temp = 1;
		}
		else if (temp == 3)
		{
			res[i] = '1';
			temp = 1;
		}
		else if (temp == 1)
		{
			res[i] = '1';
			temp = 0;
		}
	}
	return res;
}


/*Phep tru 2 QInt a va b
   a-b=a+(-b)
   a + soBu2(b)*/
string TruBit(const string& n1, const string& n2)
{
	string bu2_n2 = bu2(n2);
	return  CongBit(n1, bu2_n2);
}

QInt operator + (const QInt& n1, const QInt& n2)
{
	string num1 = QInt_To_Arr(n1);
	string num2 = QInt_To_Arr(n2);
	string res;
	res = CongBit(num1, num2);
	return Arr_To_QInt(res);
}


QInt operator - (const QInt& n1, const QInt& n2)
{
	string res;
	string num1 = QInt_To_Arr(n1);
	string num2 = QInt_To_Arr(n2);
	res = TruBit(num1, num2);
	return Arr_To_QInt(res);
}
void dichPhaiString(string &str)
{
	bool kiemTra = false;
	if (str[0] == '1')
	{
		kiemTra = true;
	}
	int n = str.size();
	for (int i = n - 1; i >= 1; i--)
	{
		str[i] = str[i - 1];
	}
	if (kiemTra == true)
	{
		str[0] = '1';
	}
}

QInt operator * (const QInt& m, const QInt& q)
{
	string A(MAX, '0');
	string M = QInt_To_Arr(m);
	string Q = QInt_To_Arr(q);
	string res;
	string A_Q_Qo;
	int k = MAX;
	A_Q_Qo += A;
	A_Q_Qo += Q;
	A_Q_Qo.push_back('0');
	int n = A_Q_Qo.size();
	while (k > 0)
	{
		if (A_Q_Qo[n - 2] == '1'&&A_Q_Qo[n - 1] == '0')
		{
			A = TruBit(A, M);
			int m = A.size();
			A_Q_Qo.replace(0, m, A);
		}
		else if (A_Q_Qo[n - 2] == '0'&&A_Q_Qo[n - 1] == '1')
		{
			A = CongBit(A, M);
			int m = A.size();
			A_Q_Qo.replace(0, m, A);
		}

		A_Q_Qo = dichPhai(A_Q_Qo, 1);
		A = A_Q_Qo.substr(0, MAX + 1); // luu lai gia tri moi cua A 
		k--;
	}
	A_Q_Qo.pop_back();
	res = A_Q_Qo.substr(A_Q_Qo.size() - MAX);

	return Arr_To_QInt(res);

}

//================================================/////////////////////
QInt operator / (const QInt& number1, const QInt& number2)
{
	string M = QInt_To_Arr(number2);

	//kiem tra so chia co phai la so 0
	/*bool la_So_0 = false;
	if (kiemTraQInt(M) == true)
	{
		cout<<"aaaaa" ;
	}*/
	string Q = QInt_To_Arr(number1);

	//=======================kiem tra dau cua phep chia ====================
	bool kiemTra = false; // luu dau cua ket qua phep chia
	if (IsNegative(Q) == true && IsNegative(M) == false)
	{
		Q = bu2(Q); // neu la so am thi lay bu 2
		kiemTra = true;  //ket qua phep chia la so am
	}
	else if (IsNegative(Q) == false && IsNegative(M) == true)
	{
		M = bu2(M);
		kiemTra = true;
	}
	else if (IsNegative(Q) == true && IsNegative(M) == true)
	{
		M = bu2(M);
		Q = bu2(Q);
	}
	cout << "\nM: " << M << endl;
	cout << "Q: " << Q << endl;
	//===================================== thuc hien phep chia ========================
	string A;
	int n = Q.size();
	if (IsSign(Q) == false)
	{
		A.append(n, '0');
	}
	else
	{

		A.append(n, '1');
	}

	cout << "\n" << A;

	int k = n;
	string A_Q;
	QInt number;
	A_Q += A;
	A_Q += Q;
	cout << A_Q.size();
	while (k > 0)
	{
		A_Q = dichTrai(A_Q, 1);
		A = A_Q.substr(0, n);
		Q = A_Q.substr(n);

		//A=A-M
		A = TruBit(A, M);
		if (IsNegative(A) == true)
		{
			Q[n - 1] = '0';
			A = CongBit(A, M);
		}
		else
		{
			Q[n - 1] = '1';
		}
		A_Q.clear();
		A_Q += A;
		A_Q += Q;
		k--;
	}
	Q = A_Q.substr(n);

	if (kiemTra == true)
	{
		Q = bu2(Q);
	}
	
	return Arr_To_QInt(Q);
}



