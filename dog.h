#ifndef DOG_H
#define DOG_H

#include <string>
using std::string;

class Model
{
public:
  Model(string _value);
  void setModelData(std::string data);
  void printModelData();
private:
  string intputValue;
};

class Dog {
  public:
    string name;
    Model _model;
  public:
    Dog (string n);
    string getGreeting ();
    void makeSound (string value);
    //void inputValue(string text);  测试从js的input框传递到c++并打印
    string inputValue(string text);
};

#endif
