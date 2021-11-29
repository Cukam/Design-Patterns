#include <iostream>

using namespace std;

/* Ovaj Design Pattern sluzi da bi pravili neke konkretne proizvode...
	Proizvod, Konkretni Proizvodi, Fabrika, Konkretna Fabrika

*/

class Automobil {
protected:
	int brojTockova;
	string nazivMotora;
public:

	Automobil(int brojTockova,string nazivMotora) : brojTockova(brojTockova),nazivMotora(nazivMotora) {}
	Automobil() : brojTockova(0),nazivMotora("") {}


	virtual void opisiAutomobil() = 0;

	virtual ~Automobil(){}
};

class Ferari : public Automobil {

public:

	Ferari() : Automobil(4, "V8"){}


	void opisiAutomobil() {
		cout << "Ovaj automobil ima " << this->brojTockova << " i motor mu je " << this->nazivMotora << endl;
	 }
};

class Maserati : public Automobil {
private:
	int velicina;
public:

	Maserati(int velicina) : Automobil(2, "V16"),velicina(velicina) {}


	void opisiAutomobil() {
		cout << "Ovaj automobil ima " << this->brojTockova << " i motor mu je " << this->nazivMotora << "i njegova velicina je :" << this->velicina << endl;
	}
};



class FabrikaAutomobila {

public:

	virtual Automobil* getAutomobil(int odabir) = 0;
	
	virtual ~FabrikaAutomobila(){}
};

class NemackaFabrikaAutomobila : public FabrikaAutomobila {
public:
	Automobil* getAutomobil(int odabir) {
		switch (odabir) {
		case 1:
			return new Maserati(150);
		case 2:
			return new Ferari();
		default:
			return nullptr;
		}
	}
};


int main() {
	NemackaFabrikaAutomobila nemacka;

	Automobil* mojPrviAutomobil = nemacka.getAutomobil(1);
	mojPrviAutomobil->opisiAutomobil();
	Automobil* mojDrugiAutomobil = nemacka.getAutomobil(2);
	mojDrugiAutomobil->opisiAutomobil();

	delete mojPrviAutomobil;
	delete mojDrugiAutomobil;

	return 0;
}