#include "ISXOD.h"
#include "recordmerger.h"
#include <iostream>

int main() 
{
    FileProcessor processor;
        
    processor.readFile("test.csv");
        
    processor.processData();
        
    processor.writeResult("output.csv");
        
    std::cout << "--------------NICE--------------" << std::endl;
    return 0;
        
}
