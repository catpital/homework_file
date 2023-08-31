#include <fstream>
#include <iostream>
#include <vector>
#include "user.cpp"
#include "mess.cpp"
#include <filesystem>
#include <sstream>

using namespace std;
namespace fs = std::filesystem;

#if defined(_WIN32) 
 #define PLATFORM_NAME "windows 32-bit" // Windows 32-bit
 #elif defined(_WIN64)
 #define PLATFORM_NAME "windows 64-bit" // Windows 64-bit
 #elif defined(__ANDROID__)
 #define PLATFORM_NAME "android"   // Android 
 #elif defined(__linux__)
 #define PLATFORM_NAME "linux"     // Debian, Ubuntu, Gentoo, Fedora, openSUSE, RedHat, Centos � ������
 #elif TARGET_OS_IPHONE == 1
 #define PLATFORM_NAME "ios"       // Apple iOS
 #elif TARGET_OS_MAC == 1
 #define PLATFORM_NAME "osx"       // Apple OSX
 #else
 #define PLATFORM_NAME  "OS not detected" // �� �� ����������
 #endif



fstream& operator >>(fstream& is, User& obj)
{
	is >> obj._name;
	is >> obj._login;
	is >> obj._pass;
	return is;
}
ostream& operator <<(ostream& os, const User& obj)
{
	os << obj._name;
	os << ' ';
	os << obj._login;
	os << ' ';
	os << obj._pass;
	return os;
}

fstream& operator >>(fstream& is, Message& obj2)
{
	is >> obj2._text;
	is >> obj2._sender;
	is >> obj2._receiver;
	return is;
}
ostream& operator <<(ostream& os, const Message& obj2)
{

	os << obj2._text;
	os << ' ';
	os << obj2._sender; //os << From: 
	os << ' ';
	os << obj2._receiver; //os << "To: ";
	return os;
}

int main() 
{
	setlocale(LC_ALL, "");
	
	std::string user_f_name = "user.txt";
	fstream user_file = fstream((user_f_name.c_str()), ios::in | ios::out);
	if (!user_file)
	{	// ��� �������� ����� ���������� �������� ios::trunc
		user_file = fstream((user_f_name.c_str()), ios::in | ios::out | ios::trunc);
		// ��� linux ������ �������� ��� ������������� ������ ������� �������������
		if (PLATFORM_NAME=="linux") {
			
			fs::permissions(user_f_name.c_str(), fs::perms::owner_exec | fs::perms::owner_read | fs::perms::owner_write, fs::perm_options::add);
			fs::permissions(user_f_name.c_str(),
				fs::perms::group_read | fs::perms::group_write | fs::perms::group_exec | fs::perms::others_exec | fs::perms::others_all | fs::perms::others_write | fs::perms::others_read,
				fs::perm_options::remove);
		                }
	}
	std::vector<User> v;
	if (user_file) {
		User obj("Alex", "qwerty", "12345"); //  ��������� ������ ��� ������ user
		v.push_back(obj);
		user_file << v[0] << endl; // ������� ������ � ����
		obj = { "Alexander", "qasdf", "3466" };
		v.push_back(obj);
		user_file << v[1] << endl; // ������� ������ � ����
		obj = { "evlampiy", "exsdf", "6776" };
		v.push_back(obj);
		user_file << v[2] << endl; // ������� ������ � ����
		// ����� ������� ������ �� �����, ���� ���������� ������� ��� ������ � ������ �����
		user_file.seekg(0, ios_base::beg);
		// ��������� ������ �� �����
		int i = 0;
		while (!user_file.eof() && (i < v.size())) {
			user_file >> obj;
			v[i] = obj;
			cout << v[i] << endl;
			i++;
		                                           }
		user_file.close(); // ��������� ����
	}
	else
	    {
		cout << "Could not open file users.txt !" << '\n';
		return 0;

	    }
	
	std::string file_mess_name = "message.txt";
	fstream user_file2 = fstream((file_mess_name.c_str()), ios::in | ios::out);
	if (!user_file2)
	{	// ��� �������� ����� ���������� �������� ios::trunc
		user_file2 = fstream((file_mess_name.c_str()), ios::in | ios::out | ios::trunc);
		if (PLATFORM_NAME == "linux") {

			fs::permissions(file_mess_name.c_str(), fs::perms::owner_exec | fs::perms::owner_read | fs::perms::owner_write, fs::perm_options::add);
			fs::permissions(file_mess_name.c_str(),
				fs::perms::group_read | fs::perms::group_write | fs::perms::group_exec | fs::perms::others_exec | fs::perms::others_all | fs::perms::others_write | fs::perms::others_read,
				fs::perm_options::remove);
		}
	}
		std::vector<Message> vm;
	if (user_file2) {
		Message obj2("������!", "Alexander", "Alexey");
		vm.push_back(obj2);
		user_file2 << vm[0] << endl;
		obj2 = { "����!", "Alexey", "Alexander" };
		vm.push_back(obj2);
		user_file2 << vm[1] << endl;
		obj2 = { "����������", "evlampiy", "Alexey" }; // �.�.��� ����� ���� txt ���� � string, �� ����� ��� ��������
		vm.push_back(obj2);
		user_file2 << vm[2] << endl;		// ������� ������ �� � ����

		// ����� ������� ������ �� �����, ���� ���������� ������� ��� ������ � ������ �����
		user_file2.seekg(0, ios_base::beg);
		int i = 0; 
		while (!user_file2.eof() && (i < vm.size())) { //������ ���� �� ����� ����� � �� �������� ������ �������
			user_file2 >> obj2; // ��������� ������ �� �����
			vm[i] = obj2;
			cout << vm[i] << endl;
			i++;
		                                             }
	
		user_file2.close(); // ��������� ����
	
	}
	else
	{
		cout << "Could not open file message.txt !" << '\n';
		return 0;
	}
		return 0;

}