#include <iostream>
#include <string>
#include <memory>


class Toy {
    std::string toyName;
    public:
    Toy(std::string _toyName): toyName(_toyName){};
    Toy() : toyName("SomeName") {};
   
    std::string getToyName() {
        return toyName;
    }
};
class shared_ptr_toy {
    Toy* toy;
    int* counter;
public:
    shared_ptr_toy () {
        toy = new Toy("SomeName");
        counter = new int(1);
    }
    shared_ptr_toy(std::string _toyName) {
        toy = new Toy(_toyName);
        counter = new int(1);
    }
    shared_ptr_toy(const shared_ptr_toy& other) {
        
        toy = other.toy;
        counter = other.counter;
        *counter += 1;
       
    }
    shared_ptr_toy& operator = (const shared_ptr_toy& other) {
        
        if (&this->toy == &other.toy) {
            return *this;
        }
        if (toy != nullptr) {
            if (counter == nullptr) {
            delete toy;
            delete counter;
            }
            *counter -= 1;
        }
        toy = other.toy;
        counter = other.counter;
        *counter += 1;
        return *this;
    }

    std::string getToyName() {
        if(toy != nullptr) {
        return toy->getToyName();
        }
        else {
            return "Nothing";
        }
    }
    int use_count() const {
        return *counter;
    }
    Toy* get() const {
        return toy;
    }
    void reset() {
        std::cout << "Toy " << toy->getToyName() << " was dropped" << std::endl;
        delete toy;
        toy = nullptr;
        delete counter;
        *counter = 0;
    }
    

    ~shared_ptr_toy() {
        if (*counter != 1) {
            (*counter)--;
        }
        else {
            std::cout << "Toy " << toy->getToyName() << " was dropped" << std::endl;
            delete toy;
            delete counter;
        }
    }
};

shared_ptr_toy make_shared(std::string _nameToy) {
    return shared_ptr_toy(_nameToy);
}

int main() {
    shared_ptr_toy toy_01 = make_shared("Ball");
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