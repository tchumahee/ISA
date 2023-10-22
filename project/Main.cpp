#include <iostream>
#include "ISA.h"

int main()
{
    Processor procesor = Processor();
    ISA isa = ISA(procesor);

    isa.readCode("ASM_source.txt");

    try {
        isa.evaluateCode();
    }
    catch (std::exception ex) {
        std::cout << ex.what() << endl;
    }
    
}
