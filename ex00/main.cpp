#include "BitcoinExchange.hpp"

int	main(int argc, char* argv[])
{
	std::ifstream	dataFile, inputFile;
	
	if (argc != 2)
    {
        std::cout<<RED<<"❌ ERROR: Invalid number of arguments !"<<RESET<<std::endl;
        std::cout<<CYAN<<"Please, use only input file as an argument"<<RESET<<std::endl;
		return 1;
    }
	dataFile.open("data.csv");		
	if (!dataFile.is_open())
    {
        std::cout<<RED<<"❌ ERROR [database]: No such file or directory !"<<RESET<<std::endl;
        return 2;
    }
    inputFile.open(argv[1]);
	if (!inputFile.is_open())
    {
        std::cout<<RED<<"❌ ERROR [input file]: No such file or directory !"<<RESET<<std::endl;
        return 3;
    }
	BitcoinExchange btc(dataFile);
	btc.displayResult(inputFile);
	dataFile.close();
	inputFile.close();
	return 0;
}