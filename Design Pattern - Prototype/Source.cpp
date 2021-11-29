#include <iostream>
#include <unordered_map>
using namespace std;


enum class ButtonType {BUTTON, RADIO, CHECKBOX};


class IButton {
protected:
	string tekst;
	string bojaPozadine;
	static unordered_map<ButtonType, IButton*> prototypes;
public:

	IButton(string tekst,string boja) : tekst(tekst), bojaPozadine(boja){}

	void setTekst(string tekst) {
		this->tekst = tekst;
	}

	void setBojaPozadine(string boja) {
		this->bojaPozadine = boja;
	}


	static IButton* build(ButtonType);

	virtual IButton* clone() = 0;

	virtual void opis() = 0;

	virtual ~IButton(){}
};


unordered_map<ButtonType, IButton*> IButton::prototypes
= unordered_map<ButtonType, IButton*>();

class Button : public IButton {
private:

	int height;
	int width;

public:

	Button(int width,int height,string tekst,string boja) : IButton(tekst,boja), height(height),width(width){}
	Button(const Button& drugi): IButton(drugi),height(drugi.height),width(drugi.width) {}
	void setHeight(int h) {
		this->height = h;
	}

	void setWidth(int w) {
		this->width = w;
	}

	IButton* clone() override {
		return new Button(*this);
	 }

	 void opis() {
		 cout << "Ovo je Dugme koje ima :" << this->height << "x" << this->width << ", a ovo je tekst : " << this->tekst << " i ovo je boja pozadine :" << this->bojaPozadine << endl;
	}
};



class RadioButton : public IButton {
private:

	string RadioButtonID;

public:

	RadioButton(string RadioButtonID, string tekst, string boja) : IButton(tekst, boja),RadioButtonID(RadioButtonID) {}
	RadioButton(const RadioButton& drugi) : IButton(drugi), RadioButtonID(drugi.RadioButtonID) {}
	
	void setRatioButtonID(string r) {
		this->RadioButtonID = r;
	}

	IButton* clone() override {
		return new RadioButton(*this);
	}

	void opis() {
		cout << "Ovo je RadioDugme koje ima ID :" << this->RadioButtonID  << ", a ovo je tekst : " << this->tekst << " i ovo je boja pozadine :" << this->bojaPozadine << endl;
	}
};


class CheckBox : public IButton {
private:

	bool checked = false;

public:

	CheckBox( string tekst, string boja) : IButton(tekst, boja) {}
	CheckBox(const CheckBox& drugi) : IButton(drugi), checked(drugi.checked) {}

	void setChecked(bool c) {
		this->checked = c;
	}

	IButton* clone() override {
		return new CheckBox(*this);
	}

	void opis() {
		cout << "Ovo je CheckBox Dugme koje je cekirano ili ne ? " << this->checked << ", a ovo je tekst : " << this->tekst << " i ovo je boja pozadine :" << this->bojaPozadine << endl;
	}
};


IButton* IButton::build(ButtonType b) {
	if (prototypes.find(b) == prototypes.end()) {
		switch (b) {
		case ButtonType::BUTTON:
			std::cout << "Kreiram prototip tipa Button" << std::endl;
			prototypes[b] = new Button(10, 30, "", "#BBBBBBB");
			break;
		case ButtonType::CHECKBOX:
			std::cout << "Kreiram prototip tipa CheckBox" << std::endl;
			prototypes[b] = new CheckBox("", "#BBBBBB");
			break;
		case ButtonType::RADIO:
			std::cout << "Kreiram prototip tipa RadioButton" << std::endl;
			prototypes[b] = new RadioButton("", "#BBBBBB", "");
			break;
		}
	}

	return prototypes[b]->clone();
}





int main() {


	IButton* mojePrvoDugme = IButton::build(ButtonType::RADIO);
	IButton* mojeDrugoDugme = IButton::build(ButtonType::BUTTON);
	IButton* mojeTreceDugme = IButton::build(ButtonType::CHECKBOX);
	IButton* mojeCetvrtoDugme = mojePrvoDugme->clone();

	mojePrvoDugme->opis();
	mojeDrugoDugme->opis();
	mojeTreceDugme->opis();
	mojeCetvrtoDugme->opis();


	delete mojePrvoDugme;
	delete mojeDrugoDugme;
	delete mojeTreceDugme;
	delete mojeCetvrtoDugme;


	return 0;

}