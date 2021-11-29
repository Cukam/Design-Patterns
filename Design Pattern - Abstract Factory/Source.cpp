#include <iostream>

using namespace std;


class ISto {
public:
		
	virtual void opis() = 0;

	virtual ~ISto(){}
};


class IStolica {
public:

	virtual void opis() = 0;
	virtual ~IStolica() {}
};


class IPolica {
public:

	virtual void opis() = 0;
	virtual ~IPolica(){}
};

class DrveniSto : public ISto {
public:
	void opis() override {
		cout << "Drveni Sto ..." << endl;
	}
};

class ModerniSto : public ISto {
public:
	void opis() override {
		cout << "Moderni Sto ..." << endl;
	}
};

class DrvenaStolica : public IStolica {
public:
	void opis() override {
		cout << "Drvena Stolica ..." << endl;
	}
};


class ModernaStolica : public IStolica {
public:
	void opis() override {
		cout << "Moderna Stolica ..." << endl;
	}
};


class DrvenaPolica : public IPolica {
public:
	void opis() override {
		cout << "Drvena Polica ..." << endl;
	}
};

class ModernaPolica : public IPolica {
public:
	void opis() override {
		cout << "Moderna Polica ..." << endl;
	}
};


class FabrikaNamestaja {
public:

	virtual ISto* napraviSto() = 0;
	virtual IStolica* napraviStolicu() = 0;
	virtual IPolica* napraviPolicu() = 0;
};


class FabrikaModernogNamestaja : public FabrikaNamestaja {
public:
	
	ISto* napraviSto() override {
		return new ModerniSto();
	 }
	IStolica* napraviStolicu() override {
		return new ModernaStolica();
	 }
	IPolica* napraviPolicu() override {
		return new ModernaPolica();
	 }

};


class FabrikaDrvenogNamestaja : public FabrikaNamestaja {
public:

	ISto* napraviSto() override {
		return new DrveniSto();
	}
	IStolica* napraviStolicu() override {
		return new DrvenaStolica();
	}
	IPolica* napraviPolicu() override {
		return new DrvenaPolica();
	}

};


class Soba {
private:
	ISto* sto;
	IPolica* polica;
	IStolica* stolica;
public:

	void setSto(ISto* sto) {
		this->sto = sto;
	}

	void setStolica(IStolica* stolica) {
		this->stolica = stolica;
	}

	void setPolica(IPolica* polica) {
		this->polica = polica;
	}

	void opisiSobu() {
		cout << "Opis moje sobe : " << endl;
		sto->opis();
		stolica->opis();
		polica->opis();
	}



	~Soba() {
		delete sto;
		delete polica;
		delete stolica;
	}
};



class SobaBuilder {
protected:
	Soba* soba;
public:

	SobaBuilder() {
		soba = new Soba();
	}


	virtual SobaBuilder& staviSto() = 0;
	virtual SobaBuilder& staviStolicu() = 0;
	virtual SobaBuilder& staviPolicu() = 0;

	Soba* getSoba() {
		return soba;
	}

	static SobaBuilder* odrediBuildera(int odabir);

	~SobaBuilder() {
		delete soba;
	}
};


class ModernaSobaBuilder : public SobaBuilder{
private:
	FabrikaModernogNamestaja fabrika;
public:
		


	SobaBuilder& staviSto() {
		soba->setSto(fabrika.napraviSto());
		return *this;
	 }
	SobaBuilder& staviStolicu() {
		soba->setStolica(fabrika.napraviStolicu());
		return *this;
	 }
	SobaBuilder& staviPolicu() {
		soba->setPolica(fabrika.napraviPolicu());
		return *this;
	 }
};


class DrvenaSobaBuilder : public SobaBuilder {
private:
	FabrikaDrvenogNamestaja fabrika;
public:



	SobaBuilder& staviSto() {
		soba->setSto(fabrika.napraviSto());
		return *this;
	}
	SobaBuilder& staviStolicu() {
		soba->setStolica(fabrika.napraviStolicu());
		return *this;
	}
	SobaBuilder& staviPolicu() {
		soba->setPolica(fabrika.napraviPolicu());
		return *this;
	}
};


SobaBuilder* SobaBuilder::odrediBuildera(int odabir) {
	switch (odabir) {
	case 0:
		return new ModernaSobaBuilder();
	case 1:
		return new DrvenaSobaBuilder();
	default:
		return nullptr;
	}
 }


class Dizajner {


public:

	Soba* getSoba(int odabir) {
		SobaBuilder* builder = SobaBuilder::odrediBuildera(odabir);
		builder->staviSto().staviPolicu().staviStolicu();
		
		return builder->getSoba();

	}

};


int main() {
	Dizajner dir;


	Soba* mojaPrvaDrvenaSoba = dir.getSoba(1);
	Soba* mojaPrvaModernaSoba = dir.getSoba(0);


	mojaPrvaDrvenaSoba->opisiSobu();
	mojaPrvaModernaSoba->opisiSobu();


	delete mojaPrvaDrvenaSoba;
	delete mojaPrvaModernaSoba;

	return 0;
}