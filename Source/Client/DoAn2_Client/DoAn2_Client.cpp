#include "stdafx.h"
#include "resource.h"
#include "afxsock.h"
#include <string>
#include <fstream>
#include <iostream>
#include <conio.h>
#include <stdlib.h>

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

bool CheckEmail(char* user)
{
	int len = strlen(user);
	char* email = "moc.liamg@";
	int len_E = strlen(email);
	if (_strnicmp(_strrev(user), email, len_E) == 0)
		return true;
	return false;
}

void Intro()
{
	GotoXY(30, 2);
	TextColor(10);
	cout << "~~~~~~~~~~~~~~~~~~> Xo So Kien Thiet <~~~~~~~~~~~~~~~~~~\n";
	Sleep(100);
	GotoXY(30, 4);
	TextColor(9);
	cout << "      ___           ___           ___                 ";
	GotoXY(30, 5);
	Sleep(100);
	cout << "     /__/|         /  /\\         /__/|          ___   ";
	GotoXY(30, 6);
	Sleep(100);
	cout << "    |  |:|        /  /:/_       |  |:|         /  /\\  ";
	GotoXY(30, 7);
	Sleep(100);
	cout << "    |  |:|       /  /:/ /\\      |  |:|        /  /:/  ";
	GotoXY(30, 8);
	Sleep(100);
	cout << "  __|__|:|      /  /:/ /::\\   __|  |:|       /  /:/   ";
	GotoXY(30, 9);
	Sleep(100);
	cout << " /__/::::\____ /__/:/ /:/\\:\\ /__/\\_|:|____  /  /::\\   ";
	GotoXY(30, 10);
	Sleep(100);
	cout << "    ~\\~~\\::::/ \\  \\:\\/:/~/:/ \\  \\:\\/:::::/ /__/:/\\:\\  ";
	GotoXY(30, 11);
	Sleep(100);
	cout << "     |~~|:|~~   \\  \\::/ /:/   \\  \\::/~~~~  \\__\\/  \\:\\ ";
	GotoXY(30, 12);
	Sleep(100);
	cout << "     |  |:|      \\__\\/ /:/     \\  \\:\\           \\  \\:\\";
	GotoXY(30, 13);
	Sleep(100);
	cout << "     |  |:|        /__/:/       \\  \\:\\           \\__\\/";
	GotoXY(30, 14);
	Sleep(100);
	cout << "     |__|/         \\__\\/         \\__\\/                ";
	TextColor(12);
	GotoXY(30, 17);
	Sleep(100);
	cout << "~~~~~~~~~~~~~~~~~~> Ich nuoc loi nha <~~~~~~~~~~~~~~~~~~\n";

}

int Menu()
{
	GotoXY(51, 20);
	Sleep(100);
	TextColor(13);
	cout << "TAO TAI KHOAN(T)";
	GotoXY(51, 21);
	Sleep(100);
	cout << "DANG NHAP(D)";
	GotoXY(51, 22);
	Sleep(100);
	cout << "THOAT(E)";
	int result;
	int _COMMAND;
	do {
		_COMMAND = toupper(_getch());
		if (_COMMAND == 'T')
			result = 1;
		else if (_COMMAND == 'D')
			result = 2;
		else if (_COMMAND == 'E')
			result = 3;
	} while (_COMMAND != 'T' && _COMMAND != 'D' && _COMMAND != 'E');
	return result;
}

void Exit(CSocket& client)
{
	TextColor(10);
	cout << "\nExit..." << endl;
	client.Close();
	exit(0);
	return;
}

char* TruyVan(CSocket& client, char* temp1)
{
	cout << "\nBam phim 'h' de duoc huong dan";
	char* tv23;
	int Tv23;
	do
	{
		cout << "\nchon: ";
		cin >> temp1;
		if (strcmp(temp1, "h") == 0)
		{
			int h = 1;
			client.Send((char*)&h, sizeof(h), 0);
			// Nhận truyvan23 từ server;
			client.Receive((char*)&Tv23, sizeof(Tv23), 0);
			tv23 = new char[Tv23];
			client.Receive(tv23, strlen(tv23), 0);
			tv23[Tv23] = '\0';
			return tv23;
		}
		else
		{
			cout << "\nHay bam phim h de nhan duoc huong dan !" << endl;
		}
	} while (strcmp(temp1, "h") != 0);
}

void PrintTinhThanh(CSocket& client, char* ngay)
{
	//nhận danh sách các tỉnh thành
	cout << "Danh sach cac tinh thanh mo thuong trong ngay vua nhap:" << endl;
	char* list = new char[8];
	for (int i = 0; i < 8; i++)
	{
		int len_list;
		client.Receive((char*)&len_list, sizeof(int), 0);
		client.Receive(list, len_list, 0);
		list[len_list] = '\0';
		TextColor(27);
		cout << list << endl;
	}
}

void DSTV(CSocket& client, char* tv23)
{
	TextColor(14);
	cout << tv23 << endl;
	int kqtv;
	string temp;
	do
	{
		//kqtv = toupper(_getch());
		cout << "Chon: ";
		cin >> temp;
		if (temp != "1" && temp != "2" && temp != "3")
		{
			cout << "Vui long nhap lai so thu tu truy van ...\n";
		}
	} while (temp != "1" && temp != "2" && temp != "3");
	// gởi kết quả truy vấn cho Server
	kqtv = stoi(temp);
	client.Send((char*)&kqtv, sizeof(kqtv), 0);
	// truy vấn 2: <tênTỉnhThành>
	if (kqtv == 1)
	{
		char* ketqua;
		int len_kq;
		string temp;
		do
		{
			char* Tentinhthanh = new char[10];
			cout << "<TenTinhThanh(viet Hoa dau chu cai)>: ";
			cin >> Tentinhthanh;

			int len_ten = strlen(Tentinhthanh);

			// gui yeu cau cho sv
			client.Send((char*)&len_ten, sizeof(int), 0);
			client.Send(Tentinhthanh, len_ten, 0);

			// nhan ket qua
			client.Receive((char*)&len_kq, sizeof(int), 0);
			ketqua = new char[len_kq];
			client.Receive(ketqua, len_kq, 0);
			ketqua[len_kq] = '\0';
			temp = ketqua;
			if (temp == "false")
			{
				cout << "Ten tinh thanh khong hop le! Vui long nhap lai\n";
			}
			else
			{
				TextColor(27);
				cout << ketqua << endl;
			}
		} while (temp == "false");
	}

	// truy vấn 3 : <tenTinhThanh> <soVe> 
	if (kqtv == 2)
	{
		char* ketqua;
		int len_kq;
		string temp;
		do
		{
			//Nhập vào tỉnh thành
			char* Tentinhthanh = new char[10];
			cout << "<TenTinhThanh(viet Hoa dau chu cai)>: ";
			cin >> Tentinhthanh;
			int len_ten = strlen(Tentinhthanh);

			//Gửi tỉnh thành cho server
			client.Send((char*)&len_ten, sizeof(int), 0);
			client.Send(Tentinhthanh, len_ten, 0);

			//nhập vào số vé
			char* Sove = new char[100];
			bool checkSove;
			do
			{
				TextColor(14);
				checkSove = true;
				cout << "<Sove>: ";
				cin >> Sove;
				if (strlen(Sove) <= 0 || strlen(Sove) > 6)
				{
					TextColor(12);
					checkSove = false;
					cout << "\nSo ve khong dung dinh dang! Vui long nhap lai..." << endl;
				}
				else
				{
					for (int i = 0; i < strlen(Sove); ++i)
					{
						if (Sove[i] < 48 || Sove[i] > 57)
							checkSove = false;
					}
					if (checkSove == false)
						cout << "\nSo ve khong dung dinh dang! Vui long nhap lai...";
				}
			} while (checkSove != true);

			int len_sove = strlen(Sove);

			//gủi số vé cho server
			client.Send((char*)&len_sove, sizeof(int), 0);
			client.Send(Sove, len_sove, 0);

			// nhận kết quả truy vấn
			client.Receive((char*)&len_kq, sizeof(int), 0);
			ketqua = new char(len_kq);
			client.Receive(ketqua, len_kq, 0);
			ketqua[len_kq] = '\0';
			TextColor(27);
			temp = ketqua;
			if (temp == "false")
			{
				TextColor(14);
				cout << "Ten tinh thanh khong hop le! Vui long nhap lai\n";
			}
			else
			{
				TextColor(27);
				cout << ketqua << endl;
			}
		} while (temp == "false");
	}

	// truy vấn 4: <exit>
	if (kqtv == 3)
	{
		Exit(client);
	}
}

void DangNhap(CSocket& client)
{
	system("cls");

	//biến để gửi ngày cần tra cứu
	char* day = new char[10];
	int len_day;

	char* userName;
	int lengthUsername;
	char* passWord;
	int lengthPassword;
	userName = new char[50];
	passWord = new char[50];
	TextColor(13);
	GotoXY(40, 1);
	cout << "DANG NHAP" << endl;
	GotoXY(35, 2);
	cout << "UserName: ";
	TextColor(15);
	cin >> userName;
	lengthUsername = strlen(userName);
	GotoXY(35, 3);
	TextColor(13);
	cout << "Password: ";
	TextColor(15);
	cin >> passWord;
	lengthPassword = strlen(passWord);

	client.Send(&lengthUsername, sizeof(lengthUsername), 0);
	client.Send(userName, lengthUsername, 0);
	client.Send(&lengthPassword, sizeof(lengthPassword), 0);
	client.Send(passWord, lengthPassword, 0);

	int result;
	client.Receive((char*)&result, sizeof(int), 0);
	do
	{
		if (result == 1)
		{
			system("cls");
			TextColor(13);
			GotoXY(35, 1);
			cout << "Chuc mung ban da dang nhap thanh cong!" << endl;
			TextColor(14);

			char* ListDay = new char[7];
			cout << "Danh sach cac ngay co the do xo so:" << endl;
			int j = 3;
			for (int i = 0; i < 7; i++)
			{
				int len_t;
				client.Receive((char*)&len_t, sizeof(int), 0);
				client.Receive(ListDay, len_t, 0);
				ListDay[len_t] = '\0';

				TextColor(27);
				GotoXY(35, j);
				cout << ListDay << endl;
				j++;
			}
			int ckDay;
			do
			{
				TextColor(14);
				cout << "\nNhap ngay muon tra cuu(dd-mm-yyyy): ";
				cin >> day;

				//Gửi ngày muốn tra cứu
				len_day = strlen(day);
				client.Send(&len_day, sizeof(int), 0);
				client.Send(day, len_day, 0);
				client.Receive((char*)&ckDay, sizeof(int), 0);

				if (ckDay == 0)
				{
					cout << "\nHay nhap ngay co trong danh sach tren" << endl;
				}
				else
				{
					break;
				}
			} while (ckDay == 0);

			char* temp = new char[1];
			char* tv23 = TruyVan(client, temp);
			PrintTinhThanh(client, day);
			while (1)
			{
				TextColor(14);
				DSTV(client, tv23);
			}
		}
		else
		{
			TextColor(12);
			GotoXY(28, 5);
			cout << "Sai ten dang nhap hoac mat khau! Bam phim bat ky de dang nhap lai..." << endl;
			_getch();
			return;
		}
	} while (result != 1);
}

void DangKy(CSocket& client)
{
	char* UserName;
	int lenUser;
	char* Password;
	int lenPass;
	bool isValid;
	UserName = new char[50];
	Password = new char[50];

	do
	{
		TextColor(13);
		system("cls");
		GotoXY(40, 1);
		cout << "DANG KY TAI KHOAN" << endl;
		GotoXY(35, 2);
		TextColor(13);
		cout << "User: ";
		TextColor(15);
		cin >> UserName;
		lenUser = strlen(UserName);

		isValid = CheckEmail(UserName);
		if (isValid == false)
		{
			GotoXY(35, 5);
			TextColor(12);
			cout << "User bat buoc la 1 dia chi gmail! Bam phim bat ky de nhap lai..." << endl;
			_getch();
		}

	} while (isValid == false);


	client.Send(&lenUser, sizeof(int), 0);
	client.Send(_strrev(UserName), lenUser, 0);

	GotoXY(35, 3);
	TextColor(13);
	cout << "Pass: ";
	TextColor(15);
	cin >> Password;
	lenPass = strlen(Password);
	client.Send(&lenPass, sizeof(int), 0);
	client.Send((Password), lenPass, 0);
	// a là x bên server
	int a;
	client.Receive((char*)&a, sizeof(a), 0);
	if (a == 0)
	{
		GotoXY(35, 5);
		TextColor(12);
		cout << "\nTai khoan da ton tai. Bam phim bat ky de chuyen lai man hinh dang ky..." << endl;
		_getch();
	}
	else
	{
		GotoXY(35, 5);
		TextColor(12);
		cout << "\nBan da dang ky thanh cong! Bam phim bat ky de chuyen toi man hinh dang nhap...";
		_getch();
		DangNhap(client);
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
		CSocket client;
		char sAdd[1000];
		unsigned int port = 1234; //Cung port voi server
		AfxSocketInit(NULL);

		//1. Tao socket
		client.Create();

		// Nhap dic chi IP cua server
		TextColor(12);
		printf("\nNhap dia chi IP cua server: ");
		TextColor(15);
		cin >> (sAdd);

		if (client.Connect(CA2W(sAdd), port))
		{
			int indexColor = 0;
			do
			{
				GotoXY(26, 14);
				TextColor(indexColor++);
				cout << "Ket noi toi server thanh cong! Bam phim bat ky de tiep tuc...";
				Sleep(100);
			} while (!_kbhit());
			//Nhan tu server, cho biet day la client thu may
			int id;
			client.Receive((char*)&id, sizeof(id), 0);
			system("cls");
			Intro();
			int select = Menu();

			client.Send((char*)&select, sizeof(select), 0);
			if (select == 1)
			{
				while (1)
				{
					DangKy(client);
				}
			}
			else if (select == 2)
			{
				while (1)
				{
					DangNhap(client);
				}
			}
			else
				Exit(client);
		}
		else
			printf("Khong connect duoc toi server....");
	}
	return nRetCode;
}
