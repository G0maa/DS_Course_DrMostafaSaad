#include <bits/stdc++.h>

using namespace std;

// ### START OF Reusable Functions ###
void ReadFile(vector<string> &InLines, const string &path) {
    fstream ReadFile;
    ReadFile.open(path, fstream::in);

    if(ReadFile.fail()) {
        cout << "\nReading file in ReadFile() function FAILED.";
        return;
    }

    string record;
    while(getline(ReadFile, record))
        InLines.push_back(record);
    ReadFile.close();
    return;
}

void WriteFile(const vector<string> &OutLines, const string &path) {
    // auto status = ios::in | ios::out | ios::app;
    fstream ReadFile;
    ReadFile.open(path, fstream::out);

    if(ReadFile.fail()) {
        cout << "\nWriting file in WriteFile() function FAILED.";
        return;
    }

    for(int i = 0; i < (int) OutLines.size(); i++)
        ReadFile << OutLines[i] << '\n';

    ReadFile.close();
    return;
}
// First time using sentinel (insert datatype) ever!        Delimiter is a character!!
// Needs lots of input verification! Also kinda buggy!
void SplitString(vector<string> &InLine, const string &str, const char &delimiter = '\t') {
	vector<int> delimiter_indexes;
    delimiter_indexes.push_back(-1); // Special case for first word.
    

    for(int i = 0; i < (int) str.size(); i++)
        if(str[i] == delimiter)
            delimiter_indexes.push_back(i);

    delimiter_indexes.push_back(str.size()); // Special case for last word... buggy -1.

    int start = 0, end = 0, sz = 0;
    for(int i = 1; i < (int) delimiter_indexes.size(); i++) {
        start = delimiter_indexes[i - 1] + 1;
        end = delimiter_indexes[i];
        sz = end - start;
        string sstr = str.substr(start, sz);
        InLine.push_back(sstr);
    }
}

int ToInt(const string &fakeint) {
    int num = 0;

    for(int i = 0; i < (int) fakeint.size(); i++)
        num = (num * 10) + (fakeint[i] - '0');

    return num;
}
// ### END OF Reusable Functions ###

class Employee {
private:
    string name { };
    int age { };
    int salary { };
    char gender { };

public:
    // Employee(string name, int age, int salary, char gender) :
    //     name(name), age(age), salary(salary), gender(gender) {

    //     }
    Employee() {
        cout << "Enter Name Age Salary Gender: \n";
        cin >> name >> age >> salary >> gender;
    }

    // Could have called this constructor with vector<string> and splitted the input in EmployeeManager.
    Employee(const string &line) {
        vector<string> splitted;
        SplitString(splitted, line);

        name = splitted[0];
        age = ToInt(splitted[1]);
        salary = ToInt(splitted[2]);
        gender = splitted[3][0];
    }

    void Print() const {
        cout << name << ' ' << age << ' ' << salary << ' '<< gender;
    }

    string GetName() const {
        return name;
    }

    int GetAge() const {
        return age;
    }

    void SetSalary(const int &salary_) {
        salary = salary_;
    }

    // As far as I know not recommended, use getters/setters instead.
    string ToString() {
        ostringstream oss;
        oss << name << '\t' << age << '\t' << salary << '\t' << gender;
        return oss.str();
    }
};

class EmployeeManager {
private:
    vector<Employee> employees;

    void DeleteByAge(const int &start, const int &end) {
        for(int i = 0; i < (int) employees.size(); i++) {
            int emp_age = employees[i].GetAge();
            if(emp_age >= start && emp_age <= end) {
                swap(employees[i], employees.back());
                employees.pop_back();
                i--; // re-checking employees.back() for a possible candidate.
            }
        }
    }

    // Can utilize better DS for stroing/sorting names.
    // Assuming unique names.
    void UpdateSalaryByName(const string &name, const int &new_salary) {
        for(int index = 0; index < (int) employees.size(); index++)
            if(employees[index].GetName() == name) {
                employees[index].SetSalary(new_salary);
                break;
            }
    }

public:
    // Slightly in efficient for the sake of using reusable functions.
    void LoadDatabase() {
        employees.clear();

        vector<string> FileOutput;
        string path = "EmployeeData.txt";
        ReadFile(FileOutput, path);

        for(int i = 0; i < (int) FileOutput.size(); i++) {
            Employee new_emp(FileOutput[i]);
            employees.push_back(new_emp);
        }
    }

    void UpdateDatabase() {
        vector<string> OutLines;
        string path = "EmployeeData.txt";

        for(int i = 0; i < (int) employees.size(); i++)
            OutLines.push_back(employees[i].ToString());
            
        WriteFile(OutLines, path);
    }

    void PrintAllEmployees() {
        for(int i = 0; i < (int) employees.size(); i++) {
            employees[i].Print();
            cout << '\n';
        }
    }

    void AddNewEmployee() {
        Employee new_emp;
        employees.push_back(new_emp);
    }

    void DeleteByAge() {
        int start { };
        int end { };
        cout << "Enter age range: ";
        cin >> start >> end;
        if(start > end)
            swap(start, end);

        DeleteByAge(start, end);
    }

    void UpdateSalaryByName() {
        string name { };
        int new_salary { };
        cout << "Enter name and salary: ";
        cin >> name >> new_salary;
        UpdateSalaryByName(name, new_salary);
    }
};

class EmployeeProgram {
private:
    EmployeeManager emp_manager;
    void LoadDatabase() {
        emp_manager.LoadDatabase();
    }

public:
    void run() {
        LoadDatabase();
        int choice = -1;
        cout << "1) Add new employee\n";
        cout << "2) Print all employees\n";
        cout << "3) Delete by age\n";
        cout << "4) Update salary by name\n";
        cout << "Choice: ";
        cin >> choice;

        if(choice == 1)
            emp_manager.AddNewEmployee();
        else if(choice == 2)
            emp_manager.PrintAllEmployees();
        else if(choice == 3)
            emp_manager.DeleteByAge();
        else if(choice == 4)
            emp_manager.UpdateSalaryByName();

         // Not needed in case of choice = 2, but for the sake of simplicity.
        emp_manager.UpdateDatabase();

        if(choice >= 1 && choice <= 4)
            run();
    }
};

int main() {
    EmployeeProgram service;
    service.run();

    cout << "\nBye :)";
    return 0;
}