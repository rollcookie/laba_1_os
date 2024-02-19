#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

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
    if (argc != 3) 
    {
        cout << "invalid number of arguments\n";
        return -1;
    }
    ofstream fout(argv[1], std::ios::binary);

    int n = std::stoi(argv[2]);

    employee e;
    string line;

    vector<employee> employees(n);

    for (int i = 0; i < n; i++) 
    {
        cout << "enter employee data(num, name, hours)\n";
        getline(cin, line);
        istringstream ss(line);
        ss >> e.num;
        ss >> e.name;
        ss >> e.hours;

        employees[i] = e;
    }

    for (int i = 0; i < n; i++) 
    {
        fout.write(reinterpret_cast<char*>(&employees[i]), sizeof(employee));
    }

    fout.close();
}

