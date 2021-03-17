#include <iostream>
#include <string>
#include <functional>

#include "dog.h"
#include "emscripten/bind.h"

using namespace emscripten;
using namespace std;

//模拟数据绑定
std::map<std::string, std::function<void(std::string)> > modelChange;

void Model::setModelData(std::string data)
{
  this->intputValue = data;
}
Model::Model(string value)
{
  intputValue = value;
  modelChange["inputvalue"] = std::bind(&Model::setModelData, this, std::placeholders::_1);
}
void Model::printModelData()
{
  cout << "Model数据改变:" << this->intputValue << endl;
}


//vm
Dog::Dog(string n) : name(n), _model("init") {}

string Dog::getGreeting () {
  return "My name is " + name + ", hello from C++!";
}

void Dog::makeSound (string value) {
  cout << value << '\n';
}

string Dog::inputValue(string text)
{
  modelChange["inputvalue"](text);
  this->_model.printModelData();
  return text;
}

//模拟返回去填充input值
// string Dog::inputValue(string text)
// {
//   text = text + "wasm";
//   return text;
// }

//模拟打印js传递过来的值
// void Dog::inputValue(string text)
// {
//   cout << text << endl;
// }

EMSCRIPTEN_BINDINGS(c)
{
  class_<Dog>("Dog")
      .constructor<string>()
      .function("makeSound", &Dog::makeSound)
      .function("getGreeting", &Dog::getGreeting)
      .function("inputValue", &Dog::inputValue);
}
