#include "stdafx.h"
#include "resource.h"
#include "afxsock.h"
#include "math.h"
#include "Tokenizer.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CWinApp theApp;

void TextColor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

void FixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void GotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

struct Name
{
	string User;
	string Pass;
};
struct Ngay
{
	string day;
};
struct KQSX
{
	string TenTinhThanh;
	string GiaiDB;
	string GiaiNhat;
	string GiaiNhi;
	string GiaiBa;
	string GiaiTu;
	string GiaiNam;
	string GiaiSau;
	string GiaiBay;
	string GiaiTam;
};

vector<string> Tokenizer::Split(const string& s, const char delim)
{
	vector<string> result;

	stringstream ss(s);
	string item;

	while (getline(ss, item, delim))
	{
		result.push_back(item);
	}

	return result;
}

string Parse(string s)
{
	vector<string> parts = Tokenizer::Split(s, '	');
	string a;
	a = parts[1];
	return a;
}

bool CheckNgay(char* Day)
{
	ifstream f;
	f.open("DanhSachNgay.txt");
	Ngay* ngay = new Ngay[7];
	for (int i = 0; i < 7; i++)
	{
		getline(f, ngay[i].day);
	}
	for (int i = 0; i < 7; i++)
	{
		if (ngay[i].day == Day)
		{
			return true;
		}
	}
	return false;
}

string TimKQSX(string Ngay, string TenTinhThanh)
{
	KQSX* a = new KQSX[8];
	ifstream f;
	if (Ngay == "12-02-2020")
		f.open("12-02-2020.txt");
	if (Ngay == "13-02-2020")
		f.open("13-02-2020.txt");
	if (Ngay == "14-02-2020")
		f.open("14-02-2020.txt");
	if (Ngay == "15-02-2020")
		f.open("15-02-2020.txt");
	if (Ngay == "16-02-2020")
		f.open("16-02-2020.txt");
	if (Ngay == "17-02-2020")
		f.open("17-02-2020.txt");
	if (Ngay == "18-02-2020")
		f.open("18-02-2020.txt");
	for (int i = 0; i < 8; i++)
	{
		getline(f, a[i].TenTinhThanh);
		getline(f, a[i].GiaiDB);
		getline(f, a[i].GiaiNhat);
		getline(f, a[i].GiaiNhi);
		getline(f, a[i].GiaiBa);
		getline(f, a[i].GiaiTu);
		getline(f, a[i].GiaiNam);
		getline(f, a[i].GiaiSau);
		getline(f, a[i].GiaiBay);
		getline(f, a[i].GiaiTam);
	}
	for (int i = 0; i < 8; i++)
	{
		if (a[i].TenTinhThanh == TenTinhThanh)
		{
			return (a[i].TenTinhThanh + "\n" + a[i].GiaiDB + "\n" + a[i].GiaiNhat + "\n" + a[i].GiaiNhi + "\n" + a[i].GiaiBa + "\n" + a[i].GiaiTu + "\n" + a[i].GiaiNam + "\n" + a[i].GiaiSau + "\n" + a[i].GiaiBay + "\n" + a[i].GiaiTam + "\n");
		}
	}
	return ("Ket qua mo thuong khong co");
}

string KiemTraVeSo(string Ngay, string Tentinhthanh, string Sove)
{
	string GiaiTrung = "Chuc ban may mam lan sau";
	ifstream f;
	int indexColor = 0;
	KQSX* a = new KQSX[10];

	if (Ngay == "12-02-2020")
		f.open("12-02-2020.txt");
	if (Ngay == "13-02-2020")
		f.open("13-02-2020.txt");
	if (Ngay == "14-02-2020")
		f.open("14-02-2020.txt");
	if (Ngay == "15-02-2020")
		f.open("15-02-2020.txt");
	if (Ngay == "16-02-2020")
		f.open("16-02-2020.txt");
	if (Ngay == "17-02-2020")
		f.open("17-02-2020.txt");
	if (Ngay == "18-02-2020")
		f.open("18-02-2020.txt");
	for (int i = 0; i < 8; i++)
	{
		getline(f, a[i].TenTinhThanh);
		getline(f, a[i].GiaiDB);
		a[i].GiaiDB = Parse(a[i].GiaiDB);
		getline(f, a[i].GiaiNhat);
		a[i].GiaiNhat = Parse(a[i].GiaiNhat);
		getline(f, a[i].GiaiNhi);
		a[i].GiaiNhi = Parse(a[i].GiaiNhi);
		getline(f, a[i].GiaiBa);
		a[i].GiaiBa = Parse(a[i].GiaiBa);
		getline(f, a[i].GiaiTu);
		a[i].GiaiTu = Parse(a[i].GiaiTu);
		getline(f, a[i].GiaiNam);
		a[i].GiaiNam = Parse(a[i].GiaiNam);
		getline(f, a[i].GiaiSau);
		a[i].GiaiSau = Parse(a[i].GiaiSau);
		getline(f, a[i].GiaiBay);
		a[i].GiaiBay = Parse(a[i].GiaiBay);
		getline(f, a[i].GiaiTam);
		a[i].GiaiTam = Parse(a[i].GiaiTam);
	}
	for (int i = 0; i < 8; i++)
	{
		if (a[i].TenTinhThanh == Tentinhthanh)
		{
			if (Sove == a[i].GiaiDB)
				GiaiTrung = "Woah! chuc mung ban da trung giai Dac biet tri gia 2.000.000.000 vnd";
			else
			{
				if ((stoi(Sove) % 100000) == stoi(a[i].GiaiNhat))
					GiaiTrung = "GiaiNhat";
				else
				{

					if ((stoi(Sove) % 100000) == stoi(a[i].GiaiNhi))
						GiaiTrung = "GiaiNhi";
					else
					{
						vector<string> parts = Tokenizer::Split(a[i].GiaiBa, '-');
						if ((stoi(Sove) % 100000) == stoi(parts[0]) || (stoi(Sove) % 100000) == stoi(parts[1]))
							GiaiTrung = "GiaiBa";
						else
						{
							vector<string> parts = Tokenizer::Split(a[i].GiaiTu, '-');
							if ((stoi(Sove) % 100000) == stoi(parts[0]) || (stoi(Sove) % 100000) == stoi(parts[1]) || (stoi(Sove) % 100000) == stoi(parts[2]) || (stoi(Sove) % 100000) == stoi(parts[3]) || (stoi(Sove) % 100000) == stoi(parts[4]) || (stoi(Sove) % 100000) == stoi(parts[5]) || (stoi(Sove) % 100000) == stoi(parts[6]))
								GiaiTrung = "GiaiTu";
							else
							{
								if (stoi(Sove) % 10000 == stoi(a[i].GiaiNam))
									GiaiTrung = "GiaiNam";
								else
								{
									vector<string> parts1 = Tokenizer::Split(a[i].GiaiSau, '-');
									if (stoi(Sove) % 10000 == stoi(parts1[0]) || stoi(Sove) % 10000 == stoi(parts1[1]) || stoi(Sove) % 10000 == stoi(parts1[2]))
										GiaiTrung = "GiaiSau";
									else
									{
										if (stoi(Sove) % 1000 == stoi(a[i].GiaiBay))
											GiaiTrung = "GiaiBay";
										else
										{
											if (stoi(Sove) % 100 == stoi(a[i].GiaiTam))
												GiaiTrung = "GiaiTam";
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return GiaiTrung;
}

int SaveUser(string user, string pass)
{
	ifstream f;
	f.open("TaiKhoan.txt");

	int n, k;
	string m, s;
	Name a[30];
	f >> n;
	for (int i = 0; i < 30; i++)
	{
		a[i].User = "";
		a[i].Pass = "";
	}
	k = -1;
	for (int i = 0; i < n; i++)
	{
		f >> m;
		f >> s;
		a[i].User = m;
		a[i].Pass = s;
		if (user == a[i].User)
		{
			k = 0;
			return 0;
		}
	}


	if (k == -1)
	{
		n++;
		a[n - 1].User = user;
		a[n - 1].Pass = pass;
		remove("TaiKhoan.txt"); // xoa file 
		ofstream f1;
		f1.open("TaiKhoan.txt"); // tao lai file moi cung ten
		f1 << n;
		f1 << endl;
		// ghi lai danh sach user bao gom ca user vua moi tao
		for (int i = 0; i < n; i++)
		{
			f1 << a[i].User;
			f1 << " ";
			f1 << a[i].Pass;
			f1 << endl;
		}
	}
	return 1;

}

bool SearchUSer(string user, string pass)
{
	ifstream f;
	f.open("TaiKhoan.txt");

	int n, k;
	string m, s;
	Name a[50];
	while (!f)
	{

		cout << "tep tin khong ton tai";
		return false;
	}

	f >> n;
	for (int i = 0; i < 50; i++)
	{
		a[i].User = "NULL";
	}
	for (int i = 0; i < n; i++)
	{
		f >> m;
		f >> s;
		a[i].User = m;
		a[i].Pass = s;
	}
	k = -1;
	for (int i = 0; i < n; i++)
	{
		if (a[i].User == user && a[i].Pass == pass)
		{
			k = 0;
			return true;
		}
	}
	return false;
}

bool SearchTinhThanh(string FileName, string TinhThanh)
{
	ifstream f;
	string a[8];
	if (FileName == "12-02-2020-TinhThanh")
		f.open("12-02-2020-TinhThanh.txt");
	if (FileName == "13-02-2020-TinhThanh")
		f.open("13-02-2020-TinhThanh.txt");
	if (FileName == "14-02-2020-TinhThanh")
		f.open("14-02-2020-TinhThanh.txt");
	if (FileName == "15-02-2020-TinhThanh")
		f.open("15-02-2020-TinhThanh.txt");
	if (FileName == "16-02-2020-TinhThanh")
		f.open("16-02-2020-TinhThanh.txt");
	if (FileName == "17-02-2020-TinhThanh")
		f.open("17-02-2020-TinhThanh.txt");
	if (FileName == "18-02-2020-TinhThanh")
		f.open("18-02-2020-TinhThanh.txt");
	if (!f)
	{
		cout << "tep tin khong ton tai";
		return false;
	}
	for (int i = 0; i < 8; i++)
	{
		f >> a[i];
	}
	for (int i = 0; i < 8; i++)
	{
		if (a[i] == TinhThanh)
		{
			return true;
		}
	}
	return false;
}

ifstream Output(string day)
{
	ifstream f;
	string a[8];
	if (day == "12-02-2020-TinhThanh")
		f.open("12-02-2020-TinhThanh.txt");
	if (day == "13-02-2020-TinhThanh")
		f.open("13-02-2020-TinhThanh.txt");
	if (day == "14-02-2020-TinhThanh")
		f.open("14-02-2020-TinhThanh.txt");
	if (day == "15-02-2020-TinhThanh")
		f.open("15-02-2020-TinhThanh.txt");
	if (day == "16-02-2020-TinhThanh")
		f.open("16-02-2020-TinhThanh.txt");
	if (day == "17-02-2020-TinhThanh")
		f.open("17-02-2020-TinhThanh.txt");
	if (day == "18-02-2020-TinhThanh")
		f.open("18-02-2020-TinhThanh.txt");
	if (!f)
	{
		cout << "tep tin khong ton tai";
	}
	return f;
}

void Exit(CSocket& server)
{
	TextColor(10);
	cout << "\nExit..." << endl;
	server.Close();

	exit(0);
	return;
}

void SendDay(CSocket& sockClients, char* Ngay)
{
	//xử lý ngày vừa nhận
	char* FileName; //Để lấy ra những tỉnh thành của ngày đã nhập
	char extend[] = "-TinhThanh";
	int len1 = strlen(extend);
	int len2 = strlen(Ngay);
	int length = len1 + len2 + 1;
	FileName = Ngay;
	strcat_s(FileName, length, extend);
	string myString;
	myString.assign(Ngay, len2);
	myString.substr(0, length - len2);
	ifstream ff = Output(FileName);
	string ds[8];
	for (int i = 0; i < 8; i++)
	{
		ff >> ds[i];
		int len_t = strlen(ds[i].c_str());
		sockClients.Send((char*)&len_t, sizeof(int), 0);
		sockClients.Send(ds[i].c_str(), len_t, 0);
	}

}

void TruyVan(CSocket& sockClients, char* Ngay)
{
	//xử lý ngày vừa nhận
	string myString;
	int size = strlen(Ngay);
	myString.assign(Ngay, size);

	//cắt ra để lấy ngày
	string temp = myString.substr(0, 10);

	//int flag = 1;
	int kq; // kq = kqtv
	sockClients.Receive((char*)&kq, sizeof(kq), 0);
	// kq = 1: xuất danh sách tỉnh thành có kqxs ra	
	// truy van 1 <TenTinhThanh>
	if (kq == 1)
	{
		char* Tentinhthanh;
		int len_ten;
		bool isValid;
		do
		{
			//Nhận tên tỉnh thành
			sockClients.Receive((char*)&len_ten, sizeof(int), 0);
			Tentinhthanh = new char[len_ten];
			sockClients.Receive(Tentinhthanh, len_ten, 0);
			Tentinhthanh[len_ten] = '\0';

			//Kiem tra xem tinh thanh co hop le hay khong
			isValid = SearchTinhThanh(Ngay, Tentinhthanh);
			if (isValid == true)
			{
				string TraCuu = TimKQSX(temp, Tentinhthanh);
				int len_tracuu = strlen(TraCuu.c_str());
				// tra ket qua
				sockClients.Send((char*)&len_tracuu, sizeof(int), 0);
				sockClients.Send(TraCuu.c_str(), len_tracuu, 0);
				//flag = 1;
			}
			else
			{
				string result = "false";
				int len_result = strlen(result.c_str());
				sockClients.Send((char*)&len_result, sizeof(int), 0);
				sockClients.Send(result.c_str(), len_result, 0);
				//flag = 0;
			}
		} while (isValid == false);
	}

	// nhận truy vấn 2 từ client
	if (kq == 2)
	{
		char* Tentinhthanh;
		int len_ten;
		char* Sove;
		int len_sove;
		bool CkTinhThanh;
		do
		{
			// nhận tên tỉnh thành
			sockClients.Receive((char*)&len_ten, sizeof(int), 0);
			Tentinhthanh = new char[len_ten];
			sockClients.Receive(Tentinhthanh, len_ten, 0);
			Tentinhthanh[len_ten] = '\0';

			sockClients.Receive((char*)&len_sove, sizeof(int), 0);
			Sove = new char[len_sove];
			sockClients.Receive(Sove, len_sove, 0);
			Sove[len_sove] = '\0';

			//Kiểm tra tên tỉnh thành có hợp lệ hay không
			CkTinhThanh = SearchTinhThanh(Ngay, Tentinhthanh);
			if (CkTinhThanh == true)
			{
				string KiemTra = KiemTraVeSo(temp, Tentinhthanh, Sove);
				int len_ktra = strlen(KiemTra.c_str());
				// gửi kết quả của hàm kiểm tra cho client
				sockClients.Send((char*)&len_ktra, sizeof(int), 0);
				sockClients.Send(KiemTra.c_str(), len_ktra, 0);
				//flag = 1;
			}
			else
			{
				string result = "false";
				int len_result = strlen(result.c_str());
				sockClients.Send((char*)&len_result, sizeof(int), 0);
				sockClients.Send(result.c_str(), len_result, 0);
				//flag = 0;
			}
		} while (CkTinhThanh == false);
	}

	//
	if (kq == 3)
	{
		Exit(sockClients);
	}
	//return flag;
}

void DangNhap(CSocket& sockClients)
{
	int flag;
	int k, x;
	char* User;
	int lenU;
	char* Pass;
	int lenP;

	//Các biến để nhận ngày đã nhập từ client
	char* day;
	int len_day;
	int CkDay;
	sockClients.Receive(&lenU, sizeof(int), 0);
	User = new char[lenU];
	sockClients.Receive(User, lenU, 0);
	User[lenU] = '\0';

	sockClients.Receive(&lenP, sizeof(int), 0);
	Pass = new char[lenP];
	sockClients.Receive(Pass, lenP, 0);
	Pass[lenP] = '\0';
	// đăng nhập thành công
	if (SearchUSer(User, Pass) == true)
	{
		int rs = 1;
		sockClients.Send((char*)&rs, sizeof(rs), 0);
		ifstream ff;
		ff.open("DanhSachNgay.txt");
		string ds1[7];
		for (int i = 0; i < 7; i++)
		{
			ff >> ds1[i];
			int len_t = strlen(ds1[i].c_str());
			sockClients.Send((char*)&len_t, sizeof(int), 0);
			sockClients.Send(ds1[i].c_str(), len_t, 0);
		}
		// nhận truy vấn ngày của client gửi cho
		do
		{
			sockClients.Receive((char*)&len_day, sizeof(int), 0);
			day = new char[len_day];
			sockClients.Receive(day, len_day, 0);
			day[len_day] = '\0';
			if (CheckNgay(day) == false)
			{
				cout << "Ngay khong hop le. Hay nhap lai" << endl;
				CkDay = 0;
				sockClients.Send((char*)&CkDay, sizeof(CkDay), 0);
			}
			else
			{
				CkDay = 1;
				sockClients.Send((char*)&CkDay, sizeof(CkDay), 0);
			}
		} while (CheckNgay(day) == false);

		int x; // x = h
		sockClients.Receive((char*)&x, sizeof(x), 0);

		if (x == 1) // x = h = 1
		{
			char truyvan23[] = "\n1. <TenTinhThanh> : xem kqxs cua ngay vua nhap \n2. <TenTinhThanh> <SoVe>: de tra cuu giai thuong\n3. <EXIT>: De thoat";
			int tv23 = strlen(truyvan23);
			sockClients.Send((char*)&tv23, sizeof(int), 0);
			sockClients.Send(truyvan23, sizeof(truyvan23), 0);
			SendDay(sockClients, day);
			while (1)
			{
				TruyVan(sockClients, day);
			}
		}
	}
	else
	{
		int p = 0;
		sockClients.Send((char*)&p, sizeof(p), 0);
		return;
	}
	//return 1;
}

void DangKy(CSocket& sockClients)
{
	int k, x;
	char* User;
	int lenU;
	char* Pass;
	int lenP;
	sockClients.Listen(5);
	// ---------------------------------------
	// my code
	// nhận User đã kiểm tra đúng

	sockClients.Receive(&lenU, sizeof(int), 0);
	User = new char[lenU];
	sockClients.Receive(User, lenU, 0);
	User[lenU] = '\0';
	// nhận pass
	sockClients.Receive(&lenP, sizeof(int), 0);
	Pass = new char[lenP];
	sockClients.Receive(Pass, lenP, 0);
	Pass[lenP] = '\0';

	if (SaveUser(User, Pass) == 0)
	{
		x = 0;
		cout << "   Dang ki khong thanh cong. Tai khoan da duoc dang ki" << endl;
		sockClients.Send((char*)&x, sizeof(int), 0);
	}
	else
	{
		x = 1;
		k = 2;
		cout << "   Dang ki thanh cong" << endl;
		sockClients.Send((char*)&x, sizeof(int), 0);
		DangNhap(sockClients);
	}
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;



	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: MFC initialization failed\n"));
		nRetCode = 1;
	}

	else
	{
		// TODO: code your application's behavior here.
		CSocket server;
		unsigned int port = 1234;
		int i;
		AfxSocketInit(NULL);

		server.Create(port);
		server.Listen(5);

		//Nhap so luong client
		int num_client;
		bool isValid;
		string temp;
		do
		{
			cout << "\nNhap so luong Client: ";
			isValid = true;
			cin >> temp;
			if (temp.length() <= 0)
			{
				isValid = false;
				cout << "\nVui long nhap dung so luong hoac dinh dang" << endl;
			}
			else
			{
				for (int i = 0; i < temp.length(); ++i)
				{
					if (temp[i] < 48 || temp[i] > 57)
						isValid = false;
				}
				if (isValid == false)
				{
					cout << "\nVui long nhap dung so luong hoac dinh dang" << endl;
				}
			}
		} while (isValid != true);
		num_client = stoi(temp);

		printf("\nDang lang nghe ket noi tu Client...\n");

		//Tao mang chua cac socket client
		CSocket* sockClients = new CSocket[num_client];
		for (i = 0; i < num_client; i++)
		{
			server.Accept(sockClients[i]);
			printf("Da tiep nhan client %d/%d\n", i + 1, num_client);
			//Bao cho client biet minh la client thu may
			sockClients[i].Send((char*)&i, sizeof(int), 0);

			int k, x;
			char* User;
			int lenU;
			char* Pass;
			int lenP;
			int j = i;
			// k là giá trị choose

			sockClients[i].Receive((char*)&k, sizeof(k), 0);
			if (k == 1)
			{
				while (1)
				{
					DangKy(sockClients[j]);
				}
			}
			// 2 là đăng nhập
			if (k == 2)
			{
				while (1)
				{
					DangNhap(sockClients[j]);
				}
			}
		}
		server.Close();
		getchar();
		return nRetCode;
	}
}
