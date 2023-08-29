#include <fstream>
#include <iostream>
#include <vector>
//#include "write.h"
using namespace std;

class User {
	string _name;
	string _login;
	string _pass;

public:
	User(string name, string login, string pass) :_name(name), _login(login), _pass(pass) {}

	friend fstream& operator >>(fstream& is, User& obj);
	friend ostream& operator <<(ostream& os, const User& obj);
};

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

class Message {
	string _text;
	string _sender;
	string _receiver;

public:
	Message(string text, string sender, string receiver) :_text(text), _sender(sender), _receiver(receiver) {}

	friend fstream& operator >>(fstream& is, Message& obj2);
	friend ostream& operator <<(ostream& os, const Message& obj2);
};


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
		// Для создания файла используем параметр ios::trunc
		user_file = fstream((user_f_name.c_str()), ios::in | ios::out | ios::trunc);
	std::vector<User> v;
	if (user_file) {
		User obj("Alex", "qwerty", "12345"); //  формируем данные для класса user
		v.push_back(obj);
		user_file << v[0] << endl; // Запишем данные в файл
		obj = { "Alexander", "qasdf", "3466" };
		v.push_back(obj);
		user_file << v[1] << endl; // Запишем данные в файл
		obj = { "evlampiy", "exsdf", "6776" };
		v.push_back(obj);
		user_file << v[2] << endl; // Запишем данные в файл
		// Чтобы считать данные из файла, надо установить позицию для чтения в начало файла
		user_file.seekg(0, ios_base::beg);
		// Считываем данные из файла
		int i = 0;
		while (!user_file.eof() && (i < v.size())) {
			user_file >> obj;
			v[i] = obj;
			cout << v[i] << endl;
			i++;
		                                           }
		user_file.close();
	}
	else
	    {
		cout << "Could not open file users.txt !" << '\n';
		return 0;

	    }
	
	std::string file_mess_name = "message.txt";
	fstream user_file2 = fstream((file_mess_name.c_str()), ios::in | ios::out);
	if (!user_file2)
		// Для создания файла используем параметр ios::trunc
		user_file2 = fstream((file_mess_name.c_str()), ios::in | ios::out | ios::trunc);
	std::vector<Message> vm;
	if (user_file2) {
		Message obj2("привет!", "Alexander", "Alexey");
		vm.push_back(obj2);
		user_file2 << vm[0] << endl;
		obj2 = { "Пока!", "Alexey", "Alexander" };
		vm.push_back(obj2);
		user_file2 << vm[1] << endl;
		obj2 = { "Порагулять", "evlampiy", "Alexey" }; // т.к.для пробы взят txt файл и string, то нужно без пробелов
		vm.push_back(obj2);
		user_file2 << vm[2] << endl;
		// Запишем данные по в файл
	//	user_file2 << obj2 << endl;
		// Чтобы считать данные из файла, надо установить позицию для чтения в начало файла
		user_file2.seekg(0, ios_base::beg);
		// Считываем данные из файла

		int i = 0;

		while (!user_file2.eof() && (i < vm.size())) { //читаем пока не конец файла и не превышен размер вектора
			user_file2 >> obj2;
			vm[i] = obj2;
			cout << vm[i] << endl;
			i++;
		                                            }
		user_file2.close();
		/*for (unsigned i = 0; i < vm.size(); i++)
		{
			std::cout<<"\n";
			std::cout << vm[i] << std::endl;
		}*/

	}
	else
	{
		cout << "Could not open file message.txt !" << '\n';
		return 0;
	}
		return 0;

}