#include <iostream>

using namespace std;

class String
{
private:
	int size;
	char* str;

public:
	String(const char*);
	~String();
	char* changeString(const char*);
	char* returnString();
	int length();
	char* addString(const char*);
	char* insertSymbol(int, char);
	char* stringToUpReg();
	char* stringToLowReg();
	void viewASCII();
};

String::~String()
{
	delete[] str;
}

String::String(const char* text)
: size((int)strlen(text)), str(new char[size + 1])
{
	strcpy_s(str, strlen(text) + 1, text);
}

char* String::changeString(const char* text)
{
	delete[] str;
	size = strlen(text);
	str = new char[size + 1];
	strcpy_s(str, size + 1, text);
	return str;
}

char* String::returnString()
{
	return str;
}

int String::length()
{
	return size;
}

char* String::addString(const char* text){
	int newSize = size + strlen(text);
	char* newStr = new char[newSize + 1];
	strcpy_s(newStr, newSize + 1, str);
	delete[] str;
	size = newSize;
	strcat_s(newStr, newSize + 1, text);
	str = newStr;
	return str;
}

char* String::insertSymbol(int index, char symbol)
{
	--index;
	if (index >= 0 && index <= size){
		++size;
		char* newStr = new char[size + 1];
		strcpy_s(newStr, size + 1, str);
		strncpy_s(newStr, size + 1, str, index);
		strcat_s(newStr, size + 1, &str[index - 1]);
		newStr[index] = symbol;
		delete[] str;
		str = newStr;
	}
	else cout << "Invalid index!" << endl;
	return str;
}

char* String::stringToUpReg()
{
	for (int count = 0; count < size; ++count)
	if (str[count] >= 'a'&&str[count] <= 'z')
		str[count] -= 32;
	return str;
}

char* String::stringToLowReg()
{
	for (int count = 0; count < size; ++count)
	if (str[count] >= 'A'&&str[count] <= 'Z')
		str[count] += 32;
	return str;
}

void String::viewASCII()
{
	cout << "There are ASCII kodes of symbols: ";
	for (int count = 0; count < size; ++count)
		cout << (int)str[count] << " ";
	cout << endl;
}

int main(){
	String str_("Enjoy");
	cout << "My string was inicialised by word: " << str_.returnString() << endl;
	cout << "String after changing: " << str_.changeString("David") << endl;
	cout << "Length of string: " << str_.length() << endl;
	cout << "Our string after adding another one: " << str_.addString(" Blane") << endl;
	cout << "Our string after insetring of a symbol: " << str_.insertSymbol(12, '!') << endl;
	str_.viewASCII();
	cout << "All letters are upper case: " << str_.stringToUpReg() << endl;
	cout << "All letters are lower case: " << str_.stringToLowReg() << endl;
	return 0;
}
