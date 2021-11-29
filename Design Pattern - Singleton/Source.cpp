#include <iostream>

using namespace std;

/*
	Singleton je design pattern koji nam sluzi da kreiramo samo jednu instancu neke klase iz nekog razloga.
	Npr postoji samo jedan Direktor u firmi ITD...
	Prvo sto moramo uraditi jeste da u protected: ili private: scopu stavimo defaultni konstruktor,
	operator= i copy konstruktor = default
	Posle toga moramo kreirati thread safe static funkciju koja nam vraca instancu.


*/

class BaseSingleton {
protected:
	BaseSingleton(){}
	BaseSingleton& operator=(const BaseSingleton&) = default;
	BaseSingleton(const BaseSingleton&) = default;

public:

	static BaseSingleton& getInstance() {
		static BaseSingleton instance;
		return instance;
	}

	virtual void use() {
		cout << "Using base Singleton" << endl;
	}

};

class DerivedSingleton : public BaseSingleton {

private:
	DerivedSingleton() {}
	DerivedSingleton& operator=(const DerivedSingleton&) = default;
	DerivedSingleton(const DerivedSingleton&) = default;
public:

	static DerivedSingleton& getInstance() {
		static DerivedSingleton instance;
		return instance;
	}

	virtual void use() {
		cout << "Using Derived Singleton" << endl;
	}
};


int main() {
	BaseSingleton& base = BaseSingleton::getInstance();
	DerivedSingleton& derived = DerivedSingleton::getInstance();

	base.use();
	derived.use();

	return 0;
}