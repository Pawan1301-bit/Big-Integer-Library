//friend function is the function that is not the member of the function but it  has the access to the private and protected members of the functions
#include<iostream>
using namespace std;

class car{
    private: 
        string make, model;
        int year;
    public:
        car(string make , string model , int year)
            :make(make), model(model), year(year) {}
        friend void displayCarInfo(const car &c);
};
void displayCarInfo(const car &c){
    cout << "make :" << c.make << "  model :" << c.model << "  year :" << c.year << endl;
}
int main(){
    car mycar("TATA", "Range rover", 2015);
    displayCarInfo(mycar);
    return 0;
}