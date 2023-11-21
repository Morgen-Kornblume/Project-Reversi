#include<iostream>
#include<iomanip>
#include"lib/board.h"
#include<cstdlib>
using namespace std;

int main(){

    board test;
    test.print();
    test.print_with_hint(1);
    test.print_with_hint(-1);
    test.print_with_predict(node(2,3,-1));
    test.print_with_predict(node(7,7,1));
    test.move(node(2,3,-1));
    test.print();
    test.save("test");
    test.print_with_hint(1);
    test.undo();
    test.print();
    test.print_with_hint(-1);
    test.load("test");
    test.print();
    system("pause");
}