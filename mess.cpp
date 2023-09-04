#include <fstream>
#include <iostream>
#include <string>
using namespace std;

class Message {
	string _text;
	string _sender;
	string _receiver;

public:
	Message(string text, string sender, string receiver) :_text(text), _sender(sender), _receiver(receiver) {}

	friend fstream& operator >>(fstream& is, Message& obj2);
	friend ostream& operator <<(ostream& os, const Message& obj2);
};