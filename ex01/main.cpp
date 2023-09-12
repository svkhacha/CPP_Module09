#include "RPN.hpp"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout<<RED<<"❌ ERROR: The program must take 1 argument !"<<RESET<<std::endl;
        return 1;
    }
    
    RPN obj;
    obj.checkAndCalculate(argv[1]);
    return 0;
}