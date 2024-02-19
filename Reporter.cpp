#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using std::ofstream;
using std::cout;
using std::cin;
using std::string;
using std::istringstream;
using std::vector;

struct employee
{
    int num; // идентификационный номер сотрудника
    char name[10]; // имя сотрудника
    double hours; // количество отработанных часов
};


int main(int argc, char* argv[])
{
    if (argc != 4) 
    {
        cout << "invalid number of arguments\n";
        return -1;
    }
    std::ifstream fin(argv[1], std::ios::binary);

    vector<employee> employees;
    employee e;

    while(fin.read(reinterpret_cast<char*>(&e), sizeof(employee)))
    {
        employees.push_back(e);
    }
    
    std::sort(employees.begin(), employees.end(), cmp);

    fin.close();

    double salary = std::stod(argv[3]);
    ofstream fout(argv[2]);
    fout << "Отчет по файлу " << argv[1] << '\n';
    for (int i = 0; i < employees.size(); i++) 
    {
        fout << employees[i].num << ' ' << employees[i].name << ' ' << employees[i].hours << ' ' <<  employees[i].hours * salary << '\n';
    }
}


