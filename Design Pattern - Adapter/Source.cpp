#include <iostream>

using namespace std;


class ShapeDrawerV1 {

public:

	
	void drawRectangle(){
		cout << "Drawing rectangle at position :" << endl;
	}

	void drawCircle() {
		cout << "Drawing circle at position :" << endl;
	}
};


class ShapeDrawerV2 {

	
public:
	
	virtual void draw(int odabir) = 0;
	virtual ~ShapeDrawerV2(){}
};

class ShapeDrawerV2Adapter : public ShapeDrawerV2 {
private:
	
	ShapeDrawerV1 shapeDrawer;
public:

	


	void draw(int odabir) {
		if (odabir == 1) {
			shapeDrawer.drawCircle();
		}
		else {
			shapeDrawer.drawRectangle();
		}
	}
};

int main() {

	ShapeDrawerV2Adapter* adapter = new ShapeDrawerV2Adapter();


	adapter->draw(2);


	delete adapter;

	return 0;
}