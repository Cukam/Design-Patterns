#include <iostream>

using namespace std;


/*
	Bridge je Design pattern koji ima 2 dela. On odvaja Implementaciju
	od Apstrakcije. Npr ako imamo Prozor koji se drugacije predstavlja u Windowsu i Linuxu
	Onda cemo imati 2 implementacije (sa zajednickim interfejsom) i imacemo apstrakciju
	Prozor koji ima objekat Implementator.

*/

class ImplementatorCrtanja {
public:
	virtual void crtajPortret(double, double) = 0;
	virtual ~ImplementatorCrtanja(){}
};

class DaVinci : public ImplementatorCrtanja {
public:
	DaVinci(){}
	virtual ~DaVinci(){}

	void crtajPortret(double visina, double sirina) override {
		cout << "Leonardov Crtez velicine " << visina << "x" << sirina << endl;
	}
};

class Pikaso : public ImplementatorCrtanja {
public:
	Pikaso() {}
	virtual ~Pikaso() {}

	void crtajPortret(double visina, double sirina) override {
		cout << "Pikasov Crtez velicine " << visina << "x" << sirina << endl;
	}
};


class Slika {
public:
	virtual void crtaj() = 0;
	virtual void promeniVelicinu(double) = 0;
	virtual void promeniUmetnika(ImplementatorCrtanja*) = 0;
};

class Portret : public Slika {
private:
	double visina, sirina;
	ImplementatorCrtanja* implementator;
public:
	Portret(double visina,double sirina,ImplementatorCrtanja* impl) : visina(visina), sirina(sirina),implementator(impl) {}

	void crtaj() override{
		implementator->crtajPortret(visina, sirina);
	}
	 void promeniVelicinu(double skalar) override{
		 this->visina *= skalar;
		 this->sirina *= skalar;
	}
	 void promeniUmetnika(ImplementatorCrtanja* noviUmetnik) override{
		 implementator = noviUmetnik;
	}
};


int main() {

	ImplementatorCrtanja* najjaciUmetnik = new Pikaso();
	ImplementatorCrtanja* drugiNajjaciUmetnik = new DaVinci();

	Portret* portret = new Portret(50, 50, najjaciUmetnik);

	portret->crtaj();

	portret->promeniVelicinu(2);

	portret->promeniUmetnika(drugiNajjaciUmetnik);

	portret->crtaj();


	delete najjaciUmetnik;
	delete drugiNajjaciUmetnik;
	delete portret;


	return 0;
}