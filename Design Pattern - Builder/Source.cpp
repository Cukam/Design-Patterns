#include <iostream>

using namespace std;


// Sluzi za pravljenje kompleksnog objekta koji moze da ima 2 ili vise konkretnih vrednosti.
// Ima Proizvod, Apstraktnog Buildera, Concrete Buildera i to 2 ili vise i Directora koji dodatno pomaze
// sakrivanju podataka.


class Pica {
private:
	int velicina;
	string nazivPice;
	bool daLiImaPapricice;
public:

	Pica(int velicina,string naziv,bool daLi) : velicina(velicina),nazivPice(naziv),daLiImaPapricice(daLi) {}
	Pica() : velicina(0), nazivPice(""), daLiImaPapricice(false) {}

	int getVelicina() {
		return velicina;
	}

	string getNazivPice() {
		return nazivPice;
	}

	string getDaLiImaPapricice() {
		if (daLiImaPapricice) {
			return "Da.";
		}
		return "Ne";
	}

	void setVelicina(int vel) {
		this->velicina = vel;
	}

	void setNazivPice(string nazivPice) {
		this->nazivPice = nazivPice;
	}

	void setDaLiImaPapricice(bool daLi) {
		this->daLiImaPapricice = daLi;
	}

	void opisiPicu() {
		cout << "Ova pica je velicine : " << this->velicina << "i zove se :  " << this->nazivPice << " i da li ima papricice ? " << this->getDaLiImaPapricice() << endl;
	}
};


class PicaBuilder {
protected:
	Pica* pica;
public:
	virtual ~PicaBuilder() { delete pica; }

	PicaBuilder() {
		pica = new Pica();
	}

	virtual PicaBuilder& staviVelicinu() = 0;

	virtual PicaBuilder& staviNazivPice() = 0;

	virtual PicaBuilder& staviPapricice() = 0;

	Pica* getPica() {
		return pica;
	}
};


class MargaritaConcreteBuilder : public PicaBuilder {

public:

	MargaritaConcreteBuilder() : PicaBuilder(){}

	PicaBuilder& staviVelicinu() override {
		pica->setVelicina(50);
		return *this;
	 }

	PicaBuilder& staviNazivPice() override {
		pica->setNazivPice("Margarita");
		return *this;
	}

	PicaBuilder& staviPapricice() {
		pica->setDaLiImaPapricice(true);
		return *this;
	}

	
};


class QuatroConcreteBuilder : public PicaBuilder {

public:

	QuatroConcreteBuilder() : PicaBuilder() {}

	PicaBuilder& staviVelicinu() override {
		pica->setVelicina(100);
		return *this;
	}

	PicaBuilder& staviNazivPice() override {
		pica->setNazivPice("Quatro");
		return *this;
	}

	PicaBuilder& staviPapricice() {
		pica->setDaLiImaPapricice(true);
		return *this;
	}


};



class CovekKojiPraviPicu {

public:

	Pica* build(PicaBuilder* builder) {

		builder->staviVelicinu().staviNazivPice().staviVelicinu();

		return builder->getPica();
	}
};


int main() {

	CovekKojiPraviPicu dir;

	QuatroConcreteBuilder quatro;
	MargaritaConcreteBuilder margarita;

	Pica* mojaPrvaPica = dir.build(&quatro);
	Pica* mojaDrugaPica = dir.build(&margarita);

	mojaPrvaPica->opisiPicu();
	mojaDrugaPica->opisiPicu();


	delete mojaPrvaPica;
	delete mojaDrugaPica;


	return 0;



}