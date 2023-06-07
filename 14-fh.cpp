#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const string fileName = "Employee.txt";

struct Employee
{
    int EmpID;
    string EmpName, Post, Department;
    float Salary;

    void ReadData()
    {
        cout << "Employee ID: ";
        cin >> EmpID;
        cout << "Employee Name: ";
        cin >> EmpName;
        cout << "Employee's Post: ";
        cin >> Post;
        cout << "Employee's Department: ";
        cin >> Department;
        cout << "Salary: ";
        cin >> Salary;
    }

    void DisplayRecord() const
    {
        cout << "_______________________________" << endl;
        cout << "ID: " << EmpID << endl;
        cout << "Name: " << EmpName << endl;
        cout << "Post: " << Post << endl;
        cout << "Department: " << Department << endl;
        cout << "Salary: " << Salary << endl;
    }
};

vector<Employee> LoadEmployeesFromFile()
{
    vector<Employee> employees;
    ifstream file(fileName);
    if (file)
    {
        Employee employee;
        while (file >> employee.EmpID >> employee.EmpName >> employee.Post >> employee.Department >> employee.Salary)
        {
            employees.push_back(employee);
        }
        file.close();
    }
    return employees;
}

void SaveEmployeesToFile(const vector<Employee> &employees)
{
    ofstream file(fileName);
    if (file)
    {
        for (const auto &employee : employees)
        {
            file << employee.EmpID << " "
                 << employee.EmpName << " "
                 << employee.Post << " "
                 << employee.Department << " "
                 << employee.Salary << endl;
        }
        file.close();
    }
}

int main()
{
    vector<Employee> employees = LoadEmployeesFromFile();

    while (true)
    {
        cout << "*******Menu********" << endl;
        cout << "1 => Add a new record" << endl;
        cout << "2 => Search record from employee id" << endl;
        cout << "3 => List Employee of particular department" << endl;
        cout << "4 => Display all employees" << endl;
        cout << "7 => Exit from the program" << endl;
        cout << "********************" << endl;

        char option;
        cin >> option;

        if (option == '1')
        {
            Employee emp;
            emp.ReadData();

            auto it = find_if(employees.begin(), employees.end(),
                              [&emp](const Employee &e)
                              { return e.EmpID == emp.EmpID; });

            if (it != employees.end())
            {
                cout << "This ID already exists. Try another ID." << endl;
            }
            else
            {
                employees.push_back(emp);
                cout << "New record has been added successfully..." << endl;
            }
        }
        else if (option == '2')
        {
            int ID;
            cout << "Enter ID of an employee to be searched: ";
            cin >> ID;

            auto it = find_if(employees.begin(), employees.end(),
                              [ID](const Employee &e)
                              { return e.EmpID == ID; });

            if (it != employees.end())
            {
                cout << "The record found...." << endl;
                it->DisplayRecord();
            }
            else
            {
                cout << "Data not found for employee ID#" << ID << endl;
            }
        }
        else if (option == '3')
        {
            string Dept;
            cout << "Enter department name to list employees within it: ";
            cin >> Dept;

            bool found = false;
            for (const auto &emp : employees)
            {
                if (emp.Department == Dept)
                {
                    if (!found)
                    {
                        cout << "The record found for this department" << endl;
                        found = true;
                    }
                    emp.DisplayRecord();
                }
            }

            if (!found)
            {
                cout << "Data not found for department " << Dept << endl;
            }
        }
        else if (option == '4')
        {
            if (employees.empty())
            {
                cout << "No records found." << endl;
            }
            else
            {
                for (const auto &emp : employees)
                {
                    emp.DisplayRecord();
                }
            }
        }
        else if (option == '7')
        {
            SaveEmployeesToFile(employees);
            break;
        }
        else
        {
            cout << "Invalid option" << endl;
        }

        cout << "\nDo you want to continue? (y/n): ";
        cin >> option;

        if (option == 'n' || option == 'N')
        {
            SaveEmployeesToFile(employees);
            break;
        }
    }

    return 0;
}
