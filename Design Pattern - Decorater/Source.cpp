#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

using namespace std;
/*


class Shape {
public:
	virtual void str()const = 0;
};

class Circle : public Shape {
private:
	int radius;
public:
	Circle(int radius) : radius(radius){}
	void resize(int scalar) {
		radius *= scalar;
	}

	void str() const override {
		
		cout << "A circle of radius." << radius << endl;
	}
};

class Square : public Shape {
private:
	int side;
public:
	Square(int side):side(side){}

	void resize(int scalar) {
		side *= scalar;
	}

	void str() const override {

		cout << "A square of radius." << side << endl;
	}
};

class ColoredShape : public Shape {
private:
	string color;
	Shape* shape;
public:
	ColoredShape(string color, Shape* shape) : color(color),shape(shape){}

	void str() const override {
		shape->str();
		cout << " has the color" << color << endl;
	}
};

class TransparentShape : public Shape {
private:
	int transparent;
	Shape* shape;
public:

	TransparentShape(int transp, Shape* shape) : transparent(transp), shape(shape) {}

	void str() const override {
		shape->str();
		cout <<   " is transparent :" << transparent << endl;
	}


};

*/


class Component {
public:
	virtual void send(const string&) = 0;
	virtual ~Component(){}
};

class MessageSender : public Component {
public:
	void send(const string& message) {
		cout << message << endl;
	}
};

class MessageSenderDecorator : public Component {
protected:
	Component* component;
public:
	MessageSenderDecorator(Component* component): component(component){}

	void send(const string& message) {
		component->send(message);
	}

	virtual ~MessageSenderDecorator() {
		delete component;
	}
};

class AddingDateDecorator : public MessageSenderDecorator {
public:
	AddingDateDecorator(Component* component): MessageSenderDecorator(component){}

	void send(const string& message) {
		time_t my_time = time(NULL);
		std::string s = std::ctime(&my_time);
		string newMessage = message + "\n" + s;
		component->send(newMessage);
		
	}
};

class SaveInALocalFileDecorator : public MessageSenderDecorator {
private:
	string fileName;
public:
	SaveInALocalFileDecorator(Component* component,string fileName) : MessageSenderDecorator(component), fileName(fileName){}

	void send(const string& message) {
		
		ofstream file(fileName);
		file << message << endl;
		file.close();
		component->send(message);

	}
};


class EncryptDecorator : public MessageSenderDecorator {
private:
	int shift;
public:
	EncryptDecorator(Component* component, int shift) : MessageSenderDecorator(component), shift(shift) {}

	void send(const string& message) {
		string encryptedMessage = "";
		for (int i = 0; i < message.size(); i++) {
			char currentChar = message[i];
			currentChar = (currentChar + shift) % 256;
			encryptedMessage += currentChar;
		}
		component->send(encryptedMessage);
		

	}
};



int main() {
	/*
	Square square(5);
	ColoredShape redSquare("red", &square);
	redSquare.str();

	TransparentShape transSquare(1, &square);
	transSquare.str();

	Shape* c1 = new TransparentShape(5,new ColoredShape("blue", new Circle(5)));

	c1->str();
	*/


	Component* sender = new AddingDateDecorator(new SaveInALocalFileDecorator(new EncryptDecorator(new MessageSender(),10),"history.txt"));

	sender->send("Test poruka");


	return 0;
}