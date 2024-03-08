#include <iostream>
#include <string>
#include <memory>


class Toy {
    std::string toyName;
    public:
    Toy(std::string _toyName): toyName(_toyName){};
    std::string getToyName() {
        return toyName;
    }
};

class shared_ptr_toy{
    Toy* toy;
    int* counter;
public:
    shared_ptr_toy(std::string _nameToy, int _n) : toy(new Toy(_nameToy)), counter(new int(_n)){};

    shared_ptr_toy(std::string _nameToy) : toy(new Toy(_nameToy)), counter(new int(1)){};

    shared_ptr_toy(){};
    
    shared_ptr_toy(const shared_ptr_toy& other) {
        toy = new Toy(*other.toy);
        counter = new int(*other.counter += 1);
        
    }
    
    shared_ptr_toy& operator = (const shared_ptr_toy& other) {
        if (this == &other) {
            return *this;
        }
        if (this != nullptr) {
            if(*counter == 1) {
            delete toy, counter;
            }
            else {
                counter -=1;
            }
        }
        toy = new Toy(*other.toy);
        counter = new int(*other.counter += 1);
        return *this;
    }
    
    std::string getToyName() {
        if(counter == nullptr) {
            return "Nothing";
        }
        else {
            return toy->getToyName();
        }   
    }

    void reset() {
        toy = nullptr;
        counter = nullptr;
    }
    
    Toy* get() const {
        return toy;
    }
    
    int use_count() const {
        return *counter;
    }
    
    ~shared_ptr_toy() {
        if(counter == nullptr) {
            delete toy, counter;
        }
    }
};
shared_ptr_toy make_shared_toy(std::string _toyName, int n = 1) {
    return  shared_ptr_toy(_toyName, n);
}

int main() {
   shared_ptr_toy toy_01 = make_shared_toy("ball");
   shared_ptr_toy toy_02(toy_01);
   shared_ptr_toy toy_03("duck");
   std::cout << "=================================================" << std::endl;
   std::cout << toy_01.getToyName() << " links:" << toy_01.use_count() << "  "
             << toy_02.getToyName() << " links:" << toy_02.use_count() << "  "
             << toy_03.getToyName() << " links:" << toy_03.use_count() << std::endl;
   std::cout << "=================================================" << std::endl;
   toy_02 = toy_03;
   std::cout << toy_01.getToyName() << " links:" << toy_01.use_count() << "  "
             << toy_02.getToyName() << " links:" << toy_02.use_count() << "  "
             << toy_03.getToyName() << " links:" << toy_03.use_count() << std::endl;
   std::cout << "=================================================" << std::endl;
   toy_01.reset();
   std::cout << toy_01.getToyName() << " links:" << toy_01.use_count() << "  "
             << toy_02.getToyName() << " links:" << toy_02.use_count() << "  "
             << toy_03.getToyName() << " links:" << toy_03.use_count() << std::endl;
   std::cout << "=================================================" << std::endl;
   

  return 0;
}

/*
Если ваш класс реализован правильно, вы получите следующий вывод:

=================================================

ball links:2  ball links:2  duck links:1

=================================================

ball links:1  duck links:2  duck links:2

=================================================

Toy ball was dropped

Nothing links:0  duck links:2  duck links:2

=================================================

Toy duck was dropped
*/