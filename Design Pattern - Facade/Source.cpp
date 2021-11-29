#include <iostream>


using namespace std;

class Subsystem1 {
public:
	string operation1()const {
		return "Subsystem1: Ready!\n";
	}

	string operationN()const {
		return "Subsystem1: Go!\n";
	}
};


class Subsystem2 {
public:
	string operation1() const {
		return "Subsystem2 : Get Ready! \n";
	}
	string operationZ() const {
		return "Subsystem2: Fire!\n";
	}
};


class Facade {
protected:
	Subsystem1* subsystem1;
	Subsystem2* subsystem2;
public:
	Facade(Subsystem1* sub1, Subsystem2* sub2) : subsystem1(sub1), subsystem2(sub2){}
	~Facade() {
		delete subsystem1;
		delete subsystem2;
	}


	string Operation() {
		string result = "Facade initializes subsystems:\n";
		result += this->subsystem1->operation1();
		result += this->subsystem2->operation1();
		result += "Facade orders subsystems to perform the action:\n";
		result += this->subsystem1->operationN();
		result += this->subsystem2->operationZ();
		return result;
	}
};

int main() {
	Subsystem1* subsystem1 = new Subsystem1();
	Subsystem2* subsystem2 = new Subsystem2();
	Facade* facade = new Facade(subsystem1, subsystem2);

	delete facade;
	delete subsystem1;
	delete subsystem2;

	return 0;
}
