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

string _2_chi_thi_p(vector<string>strArr)
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

	if (strArr[0] == "10")
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
	return res;
}

string _1_chi_thi_p(vector<string> strArr)
{
	QInt a, b;
	QInt res;

	if (strArr[2] == "+")
	{
		ScanQInt(a, strArr[1]);
		ScanQInt(b, strArr[3]);
		res = a + b;
	}
	else if (strArr[2] == "-")
	{
		ScanQInt(a, strArr[1]);
		ScanQInt(b, strArr[3]);
		res = a - b;
	}
	else if (strArr[2] == "*")
	{
		ScanQInt(a, strArr[1]);
		ScanQInt(b, strArr[3]);
		res = a * b;
	}
	else if (strArr[2] == "/")
	{
		ScanQInt(a, strArr[1]);
		ScanQInt(b, strArr[3]);
		res = a / b;
	}
	else if (strArr[2] == "<<")
	{
		ScanQInt(a, strArr[1]);
		int bit = toInt(strArr[3]);
		res = a << bit;
	}
	else if (strArr[2] == ">>")
	{
		ScanQInt(a, strArr[1]);
		int bit = toInt(strArr[3]);
		res = a >> bit;
	}
	else if (strArr[2] == "rol")
	{
		ScanQInt(a, strArr[1]);
		res = rol(a);

	}
	else if (strArr[2] == "ror")
	{
		ScanQInt(a, strArr[1]);
		res = ror(a);
	}
	return QInt_To_Arr(res);

}

string XuLiFILE(vector<string> strArr)
{
	string res;
	if (strArr.size() == 3)// 2 chi thi p, thuong la chuyen doi he co so
	{
		res = _1_chi_thi_p(strArr);
	}
	else if (strArr.size() == 4) //1 chi thi p, thuong la +,-,*,/,<<,>>,rol,ror,...
	{
		res = _2_chi_thi_p(strArr);
	}
	return res;
}



int main()
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

		//Xu li tung dong
		string output = XuLiFILE(strArr);

		//viet vao file output
		fo << output << endl;
	}
	fo.close();
	fi.close();

	
	//Viet cho dung cmd phan QFloat, khi nop nho nop phan nay, nho Uyen test thu coi no co chay ko
	/*
	string res;
	strArr.clear();
	for (int i=1;i<argc;i++)
	{
	strArr.push_back(string(argv[i]);
	}

	res=2_chi_thi_p(strArr);
	cout<<res<<endl;
	
	*/

	system("pause");
	return 0;
}
