#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

// Khai báo cấu trúc Employee để biểu diễn thông tin của mỗi nhân viên
struct Employee
{
    string name;
    int age;
    int id;
    double hourlyRate; // Mức lương hàng giờ của nhân viên
    int hoursWorked;
    double taxRate;        // Tỷ lệ thuế thu nhập cá nhân (%)
    double insuranceRate;  // Tỷ lệ bảo hiểm (%)
    double bonus;          // Phụ cấp thưởng doanh thu
    double livingExpenses; // Phụ cấp chi phí sinh hoạt

    // Hàm tính tổng lương của một nhân viên sau khi khấu trừ thuế, bảo hiểm và thêm các phụ cấp
    double calculatePay() const
    {
        double grossPay = hourlyRate * hoursWorked;
        double taxDeduction = calculateTaxDeduction(grossPay);
        double insuranceDeduction = calculateInsuranceDeduction(grossPay);
        double bonusAmount = calculateBonus();
        double livingExpensesAmount = calculateLivingExpenses();
        return grossPay - taxDeduction - insuranceDeduction + bonusAmount + livingExpensesAmount;
    }

    // Hàm tính khấu trừ thuế thu nhập cá nhân
    double calculateTaxDeduction(double grossPay) const
    {
        return grossPay * (taxRate / 100.0);
    }

    // Hàm tính khấu trừ bảo hiểm
    double calculateInsuranceDeduction(double grossPay) const
    {
        return grossPay * (insuranceRate / 100.0);
    }

    // Hàm tính phụ cấp thưởng doanh thu
    double calculateBonus() const
    {
        return bonus;
    }

    // Hàm tính phụ cấp chi phí sinh hoạt
    double calculateLivingExpenses() const
    {
        return livingExpenses;
    }

    // Hàm hiển thị thông tin của một nhân viên
    void displayInfo() const
    {
        cout << "ID: " << id << ", Name: " << name << ", Age: " << age << ", Hourly Rate: $" << hourlyRate << ", Hours Worked: " << hoursWorked << endl;
    }
};

// Lớp PayrollSystem để quản lý danh sách các nhân viên và các chức năng liên quan
class PayrollSystem
{
private:
    vector<Employee> employees; // Danh sách các nhân viên
    string filename;            // Tên tệp dữ liệu

public:
    // Constructor với tên tệp dữ liệu
    PayrollSystem(const string &filename) : filename(filename) {}

    // Hàm đọc dữ liệu từ tệp
    void readData()
    {
        ifstream file(filename);
        if (!file)
        {
            cout << "Error: Cannot open file." << endl;
            return;
        }

        employees.clear(); // Xóa dữ liệu cũ
        Employee emp;
        while (file >> emp.name >> emp.age >> emp.id >> emp.hourlyRate >> emp.hoursWorked >> emp.taxRate >> emp.insuranceRate >> emp.bonus >> emp.livingExpenses)
        {
            employees.push_back(emp);
        }
        file.close();
    }

    // Hàm lưu dữ liệu vào tệp
    void saveData() const
    {
        ofstream file(filename);
        if (!file)
        {
            cout << "Error: Cannot create file." << endl;
            return;
        }

        for (const auto &emp : employees)
        {
            file << emp.name << " " << emp.age << " " << emp.id << " " << emp.hourlyRate << " " << emp.hoursWorked << " "
                 << emp.taxRate << " " << emp.insuranceRate << " " << emp.bonus << " " << emp.livingExpenses << endl;
        }
        file.close();
    }

    // Function to add a new employee
    void addEmployee(Employee &emp)
    {
        if (employees.empty())
        {
            emp.id = 1; //  Assign ID to 1 if there are no employees.
        }
        else
        {
            // Find the largest ID in the employee list and increase it by
            //  1 to assign it to the new employee
            int maxId = 0;
            for (const auto &employee : employees)
            {
                if (employee.id > maxId)
                {
                    maxId = employee.id;
                }
            }
            emp.id = maxId + 1; // Assign ID to new employee
        }
        employees.push_back(emp);
    }

    // Function to display information of all employees
    void displayEmployees() const
    {
        if (employees.empty())
        {
            cout << "No employees to display." << endl;
            return;
        }
        cout << "Employee list:" << endl;
        for (const auto &emp : employees)
        {
            emp.displayInfo();
        }
    }

    // Function to delete an employee based on ID
    void deleteEmployee(int id)
    {
        auto it = find_if(employees.begin(), employees.end(), [id](const Employee &emp)
                          { return emp.id == id; });
        if (it != employees.end())
        {
            employees.erase(it);
            cout << "Employee with ID " << id << " has been deleted." << endl;
        }
        else
        {
            cout << "Employee with ID " << id << " not found." << endl;
        }
    }

    // Function updates an employee's info based on ID
    void updateEmployee(int id, const Employee &newInfo)
    {
        auto it = find_if(employees.begin(), employees.end(), [id](const Employee &emp)
                          { return emp.id == id; });
        if (it != employees.end())
        {
            *it = newInfo;
            cout << "Employee with ID " << id << " has been updated." << endl;
        }
        else
        {
            cout << "Employee with ID " << id << " not found." << endl;
        }
    }

    // Hàm tính tổng lương của toàn bộ nhân viên
    double calculateTotalPayroll() const
    {
        double totalPayroll = 0.0;
        for (const auto &emp : employees)
        {
            totalPayroll += emp.calculatePay();
        }
        return totalPayroll;
    }

    // Hàm tính lương cho một nhân viên dựa trên ID
    double calculatePayForEmployee(int id) const
    {
        auto it = find_if(employees.begin(), employees.end(), [id](const Employee &emp)
                          { return emp.id == id; });
        if (it != employees.end())
        {
            return it->calculatePay();
        }
        else
        {
            cout << "Employee with ID " << id << " not found." << endl;
            return 0.0;
        }
    }

    // Hàm tìm kiếm nhân viên dựa trên ID
    void findEmployeeById(int id) const
    {
        auto it = find_if(employees.begin(), employees.end(), [id](const Employee &emp)
                          { return emp.id == id; });
        if (it != employees.end())
        {
            cout << "Employee found:" << endl;
            it->displayInfo();
        }
        else
        {
            cout << "Employee with ID " << id << " not found." << endl;
        }
    }

    // Hàm hiển thị bản thông báo cho một nhân viên dựa trên ID
    void showPayStatementById(int id) const
    {
        auto it = find_if(employees.begin(), employees.end(), [id](const Employee &emp)
                          { return emp.id == id; });
        if (it != employees.end())
        {
            cout << "Pay Statement for Employee with ID " << id << ":" << endl;
            cout << "--------------------------------------" << endl;
            cout << "Name: " << it->name << endl;
            cout << "Age: " << it->age << endl;
            cout << "Hourly Rate: $" << it->hourlyRate << endl;
            cout << "Hours Worked: " << it->hoursWorked << endl;
            cout << "Tax Rate (%): " << it->taxRate << endl;
            cout << "Insurance Rate (%): " << it->insuranceRate << endl;
            cout << "Bonus: $" << it->bonus << endl;
            cout << "Living Expenses: $" << it->livingExpenses << endl;
            cout << "--------------------------------------" << endl;
            cout << "Total Pay: $" << fixed << setprecision(2) << it->calculatePay() << endl;
        }
        else
        {
            cout << "Employee with ID " << id << " not found." << endl;
        }
    }
};

// Hàm hiển thị menu và lựa chọn tác vụ
int displayMenu()
{
    cout << "Payroll System Menu" << endl;
    cout << "1. Add Employee" << endl;
    cout << "2. Display All Employees" << endl;
    cout << "3. Delete Employee" << endl;
    cout << "4. Update Employee" << endl;
    cout << "5. Calculate Pay for Employee" << endl;
    cout << "6. Find Employee by ID" << endl;
    cout << "7. Calculate Total Payroll" << endl;
    cout << "8. Show Pay Statement for Employee" << endl;
    cout << "9. Exit" << endl;
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    return choice;
}

int main()
{
    PayrollSystem payroll("employees.txt"); // Tạo một đối tượng PayrollSystem và chỉ định tên tệp dữ liệu

    // Đọc dữ liệu từ tệp
    payroll.readData();

    int choice;
    do
    {
        choice = displayMenu();
        switch (choice)
        {
        case 1:
        {
            Employee emp;
            cout << "Enter employee details:" << endl;
            cout << "Name: ";
            cin >> emp.name;
            cout << "Age: ";
            cin >> emp.age;
            cout << "Hourly Rate: ";
            cin >> emp.hourlyRate;
            cout << "Hours Worked: ";
            cin >> emp.hoursWorked;
            cout << "Tax Rate (%): ";
            cin >> emp.taxRate;
            cout << "Insurance Rate (%): ";
            cin >> emp.insuranceRate;
            cout << "Bonus: ";
            cin >> emp.bonus;
            cout << "Living Expenses: ";
            cin >> emp.livingExpenses;
            payroll.addEmployee(emp);
            cout << "Employee added successfully." << endl;
            break;
        }
        case 2:
            payroll.displayEmployees();
            break;
        case 3:
        {
            int idToDelete;
            cout << "Enter employee ID to delete: ";
            cin >> idToDelete;
            payroll.deleteEmployee(idToDelete);
            break;
        }
        case 4:
        {
            int idToUpdate;
            cout << "Enter employee ID to update: ";
            cin >> idToUpdate;
            Employee newInfo;
            cout << "Enter updated employee details:" << endl;
            cout << "Name: ";
            cin >> newInfo.name;
            cout << "Age: ";
            cin >> newInfo.age;
            cout << "Hourly Rate: ";
            cin >> newInfo.hourlyRate;
            cout << "Hours Worked: ";
            cin >> newInfo.hoursWorked;
            cout << "Tax Rate (%): ";
            cin >> newInfo.taxRate;
            cout << "Insurance Rate (%): ";
            cin >> newInfo.insuranceRate;
            cout << "Bonus: ";
            cin >> newInfo.bonus;
            cout << "Living Expenses: ";
            cin >> newInfo.livingExpenses;
            payroll.updateEmployee(idToUpdate, newInfo);
            break;
        }
        case 5:
        {
            int idToCalculate;
            cout << "Enter employee ID to calculate pay: ";
            cin >> idToCalculate;
            double pay = payroll.calculatePayForEmployee(idToCalculate);
            cout << "Pay for employee with ID " << idToCalculate << " is: $" << pay << endl;
            break;
        }
        case 6:
        {
            int idToFind;
            cout << "Enter employee ID to find: ";
            cin >> idToFind;
            payroll.findEmployeeById(idToFind);
            break;
        }
        case 7:
            cout << "Total payroll: $" << payroll.calculateTotalPayroll() << endl;
            break;
        case 8:
        {
            int idToShow;
            cout << "Enter employee ID to show pay statement: ";
            cin >> idToShow;
            payroll.showPayStatementById(idToShow);
            break;
        }
        case 9:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 9);

    // Lưu dữ liệu vào tệp
    payroll.saveData();

    return 0;
}
