//operator overloading is a concept of c++ that allow you to redeine the befavior of operator like '+', '-', '*', '/', '[]'for your class or struct

#include <iostream>

using namespace std;

class Box {
private:
    double length;
    double width;
    double height;

public:
    // Constructor
    Box(double l = 0.0, double w = 0.0, double h = 0.0)
        : length(l), width(w), height(h) {}

    // Method to calculate volume
    double volume() const {
        return length * width * height;
    }

    // Overloading the + operator to add volumes of two Box objects
    Box operator+(const Box& b) const {
        Box result;
        result.length = this->length + b.length;
        result.width = this->width + b.width;
        result.height = this->height + b.height;
        return result;
    }

    // Method to display dimensions of the Box
    void display(){
        cout << "Dimensions: " << length << " x " << width << " x " << height << endl;
    }
};

int main() {
    // Create two Box objects
    Box box1(2.0, 3.0, 4.0);
    Box box2(1.0, 2.0, 3.0);

    // Use the overloaded + operator to add volumes of box1 and box2
    Box resultBox = box1 + box2;

    // Display dimensions and volumes
    cout << "Box 1:" << endl;
    box1.display();
    cout << "Volume of Box 1: " << box1.volume() << endl;

    cout << "\nBox 2:" << endl;
    box2.display();
    cout << "Volume of Box 2: " << box2.volume() << endl;

    cout << "\nResultant Box (Box 1 + Box 2):" << endl;
    resultBox.display();
    cout << "Volume of Resultant Box: " << resultBox.volume() << endl;

    return 0;
}
