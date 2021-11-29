#include <iostream>
#include <vector>


using namespace std;


class GraphicObject {
public:
	virtual void draw() = 0;
};

class Circle : public GraphicObject{
public:
	void draw() override {
		cout << " Circle ..." << endl;
	}
};


class Square : public GraphicObject {
public:
	void draw() {
		cout << " Square ..." << endl;
	}
};


class GroupOfObjects : public GraphicObject {
private:
	
	string name;
public:
	vector<GraphicObject*> objects;
	
	GroupOfObjects(string name) : name(name){}
	void draw() {
		cout << "This Group of Objects named : " << name << " has :" << endl;
		for (int i = 0; i < objects.size(); i++) {
			objects[i]->draw();
		}
	}
};


int main() {
	Square s1, s2;
	Circle c1, c2;

	GroupOfObjects mojPrvi("Avion");
	mojPrvi.objects.push_back(&c1);
	mojPrvi.objects.push_back(&c2);

	GroupOfObjects mojDrugi("Avionska Podgrupa");
	
	mojDrugi.objects.push_back(&s1);
	mojDrugi.objects.push_back(&s2);

	mojPrvi.objects.push_back(&mojDrugi);

	mojPrvi.draw();

	return 0;



}