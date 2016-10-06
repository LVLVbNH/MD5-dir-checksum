// MD5.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "openssl/md5.h"
#include <conio.h>
#include <Windows.h>
#include <string>

using namespace std;



int main()
{
	setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);



	wstring stemp;
	getline(wcin, stemp);
	wcout << stemp << endl;
	LPCWSTR dir = stemp.c_str();
	wstring specChar = L"*";
	wstring aaa = dir + specChar;


	WIN32_FIND_DATAW wfd;
	HANDLE const hFind = FindFirstFileW(aaa.c_str(), &wfd);
	setlocale(LC_ALL, "");

	if (INVALID_HANDLE_VALUE != hFind)
	{
		do
		{
			wstring name = wfd.cFileName;
			wstring path = dir + name;

			ifstream file(path, ios::binary);


			if (file.fail())
			{

				continue;
			}


			unsigned int size = 0;
			unsigned char *input = 0;

			file.seekg(0, ios::end);
			size = file.tellg();
			file.seekg(0, ios::beg);

			input = new unsigned char[(int)size];
			for (register int i = 0; !file.eof(); ++i)
				input[i] = file.get();

			unsigned char md5hash[MD5_DIGEST_LENGTH] = { 0 };


			MD5(input, size, md5hash);


			const char hexDigits[17] = "0123456789ABCDEF";
			static char md5hash_str[2 * MD5_DIGEST_LENGTH + 1];
			int i;
			for (i = 0; i < MD5_DIGEST_LENGTH; i++)
			{
				md5hash_str[i * 2] = hexDigits[(md5hash[i] >> 4) & 0xF];
				md5hash_str[i * 2 + 1] = hexDigits[md5hash[i] & 0xF];
			}
			md5hash_str[MD5_DIGEST_LENGTH * 2] = '\0';

			wcout << wfd.cFileName << L" Хэш: " << md5hash_str << endl;                                //вывод хэша на экран
		} while (NULL != FindNextFileW(hFind, &wfd));

		FindClose(hFind);
	}

	system("pause");
	return 0;

}