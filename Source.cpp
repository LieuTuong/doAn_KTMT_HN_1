#include"QInt.h"
#include"QFloat.h"
#include<vector>
#include<fstream>
#include<cstring>
using namespace std;

vector<string> tachToken(string x)
{
	vector<string> res;
	int len = x.length();

	char* cstr = new char[len + 1];
	strcpy(cstr, x.c_str());
	char* token;
	token = strtok(cstr, " ");
	while (token != 0)
	{
		res.push_back(string(token));
		token = strtok(NULL, " ");
	}
	return res;
}



bool ToanTuGiuaQInt_QInt(string x)
{
	return (x == "+" || x == "-" || x == "*" || x == "/"||x=="&"||x=="|"||x=="^");
}


bool ToanTuGiuaQInt_Int(string x)
{
	return (x == "<<" || x == ">>" || x == "rol" || x == "ror");
}


QInt tinhToanQInt_QInt(QInt a, QInt b, string toanTu)
{
	QInt res;
	if (toanTu == "+")
		res = a + b;
	else if (toanTu == "-")
		res = a - b;
	else if (toanTu == "*")
		res = a * b;
	else if (toanTu == "/")
		res = a / b;
	else if (toanTu == "&")
		res = a & b;
	else if (toanTu == "|")
		res = a | b;
	else if (toanTu == "^")
		res = a ^ b;
	return res;
}


QInt tinhToanQInt_Int(QInt a, int b, string toanTu)
{
	QInt res;
	if (toanTu == "<<")
		res = a << b;
	else if (toanTu == ">>")
		res = a >> b;
	else if (toanTu == "rol")
		res = rol(a, b);
	else if (toanTu == "ror")
		res = ror(a, b);
	

	return res;
}


string _1_chi_thi_p_QInt(vector<string> strArr)
{
	QInt a, b,resQInt;
	string res;
	int heCoSo;
	 
	if (strArr[0] == "2")//Neu la he 2
	{
		heCoSo = 2;
		ScanQInt(a, BinToDec(strArr[1]));
		if (ToanTuGiuaQInt_QInt(strArr[2]))//Neu la toan tu xu li giua QInt voi QInt nhu +, - ,* ,/ ...
		{
			ScanQInt(b, BinToDec(strArr[3]));
			resQInt = tinhToanQInt_QInt(a, b, strArr[2]);
		}
		else if (ToanTuGiuaQInt_Int(strArr[2])) //Neu la toan tu xu li giua QInt voi int nhu <<, >>, rol, ror,..
		{
			int bit = toInt(BinToDec(strArr[3]));//tu he 2 -> he 10, r chuyen sang so nguyen
			resQInt = tinhToanQInt_Int(a, bit, strArr[2]);
		}
		else // toan tu 1 ngoi nhu ~
		{
			resQInt = ~a;
		}
	}

	else if (strArr[0] == "10")// Neu la he 10
	{
		heCoSo = 10;
		ScanQInt(a, strArr[1]);
		if (ToanTuGiuaQInt_QInt(strArr[2]))
		{
			ScanQInt(b, strArr[3]);
			resQInt=tinhToanQInt_QInt(a, b, strArr[2]);
		}
		else if (ToanTuGiuaQInt_Int(strArr[2]))
		{
			int bit = toInt(strArr[3]);
			resQInt=tinhToanQInt_Int(a, bit, strArr[2]);
		}
		else //toan tu ~
		{
			resQInt = ~a;
		}
	}

	else // He 16
	{
		heCoSo = 16;
		ScanQInt(a, HexToDec(strArr[1]));
		if (ToanTuGiuaQInt_QInt(strArr[2]))
		{
			ScanQInt(b, HexToDec(strArr[3]));
			resQInt=tinhToanQInt_QInt(a, b, strArr[2]);
		}
		else if (ToanTuGiuaQInt_Int(strArr[2]))
		{
			int bit = toInt(HexToDec(strArr[3]));
			resQInt = tinhToanQInt_Int(a, bit, strArr[2]);
		}
		else //toan tu ~
		{
			resQInt = ~a;
		}
	}

	string resStr = QInt_To_Arr(resQInt);//chuyen tu QInt sang mang nhi phan

	//Tra ket qua theo he co so ma file input de ra
	if (heCoSo == 10)
	{
		resStr = BinToDec(resStr);
	}
	else if (heCoSo == 16)
	{
		resStr = BinToHex(resStr);
	}
	return resStr;
}


string _2_chi_thi_p_QInt(vector<string>strArr)
{
	string res;
	if (strArr[0] == "2")
	{
		if (strArr[1] == "10")// yeu cau chuyen tu he 2 -> he 10
		{
			res = BinToDec(strArr[2]);
		}
		else if (strArr[1] == "16")// yeu cau chuyen tu he 2 -> he 16
		{
			res = BinToHex(strArr[2]);
		}
	}

	else if (strArr[0] == "10")
	{
		if (strArr[1] == "2")// He 10 -> he 2
		{
			res = DecToBin(strArr[2]);
		}
		else if (strArr[1] == "16")//He 10 -> He 16
		{
			res = DecToHex(strArr[2]);
		}
	}


	else if (strArr[0] == "16")
	{
		if (strArr[1] == "2")
		{
			res = HexToBin(strArr[2]);
		}
		else if (strArr[1] == "10")
		{
			res = HexToDec(strArr[2]);
		}
	}
	return res;
}


string XuLiFILE_QInt(vector<string> strArr)
{
	string res;
	if (strArr.size() == 3)// 2 chi thi p, thuong la chuyen doi he co so
	{
		res = _1_chi_thi_p_QInt(strArr);
	}
	else if (strArr.size() == 4) //1 chi thi p, thuong la +,-,*,/,<<,>>,rol,ror,...
	{
		res = _2_chi_thi_p_QInt(strArr);
	}
	return res;
}

string XuLiFILE_QFloat(vector<string> strArr)
{
	string res;
	if (strArr[0] == "2" && strArr[1] == "10")// chuyen tu he 2 -> he 10
	{
		res = BinToDec_QFloat(strArr[2]);
	}

	else if (strArr[0] == "10" && strArr[1] == "2")
	{
		res = DecToBin_QFloat(strArr[2]);
	}
	return res;
}

int main(int argc, char* argv[])
{
	ifstream fi("Text.txt");//Luc nop bai thi sua lai la ifstream fi(argv[1])
	ofstream fo("output.txt"); //Luc nop bai thi sua lai la ofstream fo(argv[2])
	if (fi.fail() || fo.fail())
	{
		cout << "\nKhong the mo FILE";
		return 0;
	}

	string tmp;
	vector<string> strArr;
	while (!fi.eof())
	{
		//Xoa mang vector de lam chuoi moi
		strArr.clear();

		//Doc tung dong trong file
		getline(fi, tmp);
		int len = tmp.length();
		if (len == 0)return 0;//Neu gap dong trong, tuc cuoi file, return

		//Tach chuoi thanh cac token
		strArr = tachToken(tmp);

		string output;
		if (argv[argc - 1] == "1")// Xu li FILE QInt
		{
			output = XuLiFILE_QInt(strArr);
		}
		else //Xu li FILE QFloat
		{
			output = XuLiFILE_QFloat(strArr);
		}

		//viet vao file output
		fo << output << endl;
	}
	fo.close();
	fi.close();

	
	

	system("pause");
	return 0;
}


