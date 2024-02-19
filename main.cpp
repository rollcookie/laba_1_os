#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <tchar.h>
#include <string>
#include <vector>

using std::string;
using std::cout;
using std::cin;
using std::vector;

struct employee
{
	int num; // идентификационный номер сотрудника
	char name[10]; // имя сотрудника
	double hours; // количество отработанных часов
};

int main()
{
	setlocale(LC_ALL, "Russian");
	string fileName;
	cout << "enter file name\n";
	cin >> fileName;
	int n;
	cout << "enter amount of records\n";
	cin >> n;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	LPCWSTR szCmdline = _tcsdup(TEXT("Creator.exe"));
	std::wstring fileNameW = std::wstring(fileName.begin(), fileName.end());
	std::wstring szCmdlineArgs = L"Creator.exe " + fileNameW + L" " + std::to_wstring(n);
	LPWSTR szCmdlineArgsDup = _wcsdup(szCmdlineArgs.c_str());	
	CreateProcess(szCmdline, szCmdlineArgsDup, NULL, NULL, 0, 0, NULL, NULL, &si, &pi);

	WaitForSingleObject(pi.hProcess, INFINITE);

	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);

	vector<employee> employees;
	employee e;

	std::ifstream fin(fileName, std::ios::binary);

	while (fin.read(reinterpret_cast<char*>(&e), sizeof(employee)))
	{
		employees.push_back(e);
	}

	for (int i = 0; i < employees.size(); i++)
	{
		cout << employees[i].num << ' ' << employees[i].name << ' ' << employees[i].hours  << '\n';
	}

	fin.close();

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	string reportName;
	cout << "enter report file name\n";
	cin >> reportName;
	double salary;
	cout << "enter salary per hour\n";
	cin >> salary;

	szCmdline = _tcsdup(TEXT("Reporter.exe"));
	std::wstring reportNameW = std::wstring(reportName.begin(), reportName.end());
	szCmdlineArgs = L"Reporter.exe " + fileNameW + L" " + reportNameW + L" " + std::to_wstring(salary);
	szCmdlineArgsDup = _wcsdup(szCmdlineArgs.c_str());
	CreateProcess(szCmdline, szCmdlineArgsDup, NULL, NULL, 0, 0, NULL, NULL, &si, &pi);

	WaitForSingleObject(pi.hProcess, INFINITE);

	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);

	string line;
	std::ifstream report(reportName);
	
	while (!report.eof())
	{
		getline(report, line);
		cout << line << '\n';
	}

	report.close();
	
}

