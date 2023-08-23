#include <iostream>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include <string>
#include <algorithm>
using namespace std;

const int COMPANY_SALARY = 3000000;

class Staff {
	std::string name;
	int salary;
	int exp_year;
public:
	Staff() {
		name = "";
		salary = COMPANY_SALARY;
		exp_year = 0;
	}
	std::string getName() {
		return name;
	}
	virtual int getSalary() {
		return salary;
	}
	int getExp() {
		return exp_year;
	}

	void setName(std::string n) {
		name = n;
	}
	void setSalary(int s) {
		salary = s;
	}
	void setExp(int e) {
		exp_year = e;
	}
	virtual void change_info_person() {
		int choice;
		cout << "\t[?] Ban muon sua gi\n\t[1] Ten\n\t[2] Nam lam viec: "; cin >> choice;
		switch (choice) {
		case 1:
			cin.ignore();
			cout << "\t\t[?] Nhap ten moi: ";
			std::getline(cin, name);
			break;
		case 2:
			cout << "\t\t[?] Nhap nam lam viec moi: "; cin >> exp_year;
			break;
		default:
			cout << "\t\t[!] Lenh khong hop le! ";
			break;
		}
	}
};

class HR : public Staff {
public:
	int getSalary() override {
		return Staff::getSalary();
	}
};

class Engineer : public Staff {
public:
	int getSalary() override {
		return (Staff::getSalary() + (Staff::getSalary() * 15) / 100);
	}
};

class Business : public Staff {
private:
	int contract;
public:
	int getSalary() override {
		return (Staff::getSalary() + (Staff::getSalary() * contract) / 100);
	}
	void setContract() {
		cout << "\t[?] Nhap so hop dong nhan vien nay da ki: "; cin >> contract;
	}
	void setContract(int c) {
		contract = c;
	}
	void change_info_person() override {
		int choice;
		std::string name = "";
		int exp_year = 0;
		int c = 0;
		cout << "\t[?] Ban muon sua gi\n\t[1] Ten\n\t[2] Nam lam viec\n\t[3] Hop dong: "; cin >> choice;
		switch (choice) {
		case 1:
			cin.ignore();
			cout << "\t\t[?] Nhap ten moi: "; getline(cin, name);
			Staff::setName(name);
			break;
		case 2:
			cout << "\t\t[?] Nhap nam lam viec moi: "; cin >> exp_year;
			Staff::setExp(exp_year);
			break;
		case 3:
			cout << "\t\t[?] Nhap hop dong moi: "; cin >> c;
			contract = c;
			break;
		default:
			cout << "\t\t[!] Lenh khong hop le! ";
			break;
		}
	}
};

void clearScreen() {
#ifdef _WIN32
	std::system("cls"); // On Windows
#else
	std::system("clear"); // On other platforms
#endif
}

void press() {
	cout << "Press any key to continue...";
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();
	return;
}

void menu() {
	cout << "[!]" << " [Danh sach cac thao tac ban co the su dung] " << "\n";
	cout << "[1]" << " In danh sach nhan vien" << "\n";
	cout << "[2]" << " Them nhan vien" << "\n";
	cout << "[3]" << " Sua nhan vien" << "\n";
	cout << "[4]" << " Xoa nhan vien" << "\n";
	cout << "[5]" << " Sua muc luong co ban" << "\n";
}

int select_menu() {
	int command;
	cout << "Nhap lua chon cua ban: "; cin >> command;
	return command;
}

void print_list_staff(std::vector<Staff*> list_staff) {
	cout << "+" << std::setfill('-') << std::setw(7) << "+" << std::setw(60) << "+" << "\n";
	cout << '|' << " STT" << "  |" << std::left << std::setfill(' ') << std::setw(22)
		<< " Ho va ten" << "|" << std::setw(17) << " Nam lam viec" << '|' << std::setw(18) << " Luong" << '|' << "\n";
	cout << "+" << std::setfill('-') << std::setw(7) << std::right << "+" << std::setw(60) << std::right << "+" << "\n";
	for (int i = 0; i < list_staff.size(); i++) {
		cout << "|" << "  " << std::setfill(' ') << std::left << std::setw(4) << i + 1 << "|" << " " << std::setw(21)
			<< list_staff[i]->getName() << "|" << " " << std::setw(16) << list_staff[i]->getExp() << "|" << " " << std::setw(17) << list_staff[i]->getSalary() << "|" << "\n";
	}
	cout << "+" << std::setfill('-') << std::setw(7) << std::right << "+" << std::setw(60) << std::right << "+" << "\n";
}

Staff* print_input_person(Staff* staff) {
	std::string name = "";
	int exp_year = 0;

	cin.ignore();
	cout << "\t[?] Nhap ten: "; std::getline(cin, name);
	cout << "\t[?] Nhap nam kinh nghiem: "; cin >> exp_year;
	staff->setName(name);
	staff->setExp(exp_year);
	return staff;
}
void add_staff_HR(std::vector<Staff*>& list_staff) {
	Staff* staff = new HR();
	staff = print_input_person(staff);
	list_staff.push_back(staff);
}
void add_staff_Enginner(std::vector<Staff*>& list_staff) {
	Staff* staff = new Engineer();
	staff = print_input_person(staff);
	list_staff.push_back(staff);
}
void add_staff_Business(std::vector<Staff*>& list_staff) {
	Staff* staff = new Business();
	staff = print_input_person(staff);
	dynamic_cast<Business*>(staff)->setContract();
	list_staff.push_back(staff);
}
void add_staff_menu(std::vector<Staff*>& list_staff) {
	int command;
	cout << "\t[1] HR" << "\n";
	cout << "\t[2] Engineer" << "\n";
	cout << "\t[3] Business" << "\n";
	cout << "Ban muon them nhan vien o vi tri nao: "; cin >> command;
	switch (command) {
	case 1:
		add_staff_HR(list_staff);
		break;
	case 2:
		add_staff_Enginner(list_staff);
		break;
	case 3:
		add_staff_Business(list_staff);
		break;
	}
}

void change_info_staff(std::vector<Staff*>& list_staff) {
	int command;
	std::string name = "";
	int year = 0;
	cout << "\t[?] Ban muon sua nhan vien co STT la bao nhieu: "; cin >> command;
	if (command > list_staff.size()) {
		cout << "\t[!] Nhan vien ban nhap khong ton tai, vui long them nhan vien" << "\n";
		return;
	}
	else {
		if (dynamic_cast<Business*>(list_staff[command - 1]) != nullptr) {
			(static_cast<Business*>(list_staff[command - 1]))->change_info_person();
		}
		else list_staff[command - 1]->change_info_person();
	}
}

void remove_staff(std::vector<Staff*>& list_staff) {
	int postition = 0;
	cout << "\t[!] Nhap STT ban muon xoa: "; cin >> postition;
	list_staff.erase(list_staff.begin() + postition - 1);
}

void change_salary(std::vector<Staff*>& list_staff) {
	int postition = 0;
	int salary = 0;
	cout << "\t[!] Nhap STT ban muon sua luong co ban: "; cin >> postition;
	cout << "\t[?] Nhap so luong co ban moi: "; cin >> salary;
	list_staff[postition - 1]->setSalary(salary);
}
int main() {
	std::vector<Staff*> list_staff;
	while (true) {
		clearScreen();
		menu();
		int command = select_menu();
		switch (command) {
		case 1:
			print_list_staff(list_staff);
			press();
			break;
		case 2:
			add_staff_menu(list_staff);
			press();
			break;
		case 3:
			change_info_staff(list_staff);
			press();
			break;
		case 4:
			remove_staff(list_staff);
			press();
			break;
		case 5:
			change_salary(list_staff);
			press();
			break;
		default:
			return 0;
		}
	}
}