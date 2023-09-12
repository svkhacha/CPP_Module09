#include "PmergeMe.hpp"

int main(int argc, char* argv[])
{
   std::string  numSequence;
   for (int i = 1; i < argc; ++i)
    {
        numSequence += argv[i];
        if (i != argc - 1)
        numSequence += " ";
    }

    PmergeMe obj;
    try
    {
        obj = PmergeMe(numSequence);
    }
    catch (const std::exception& e)
    {
        std::cout<<e.what()<<std::endl;
        return 1;
    }

    // std::cout<<PINK<<"Before[std::vector]: "<<RESET;
    // obj.displayVector(10);
    // std::cout<<PINK<<"Before[std::list]: "<<RESET;
    // obj.displayList(10);
    std::cout<<PINK<<"Before: "<<RESET;
    obj.displayList(10);

    struct timeval  time;
    gettimeofday(&time, NULL);
    long long   vectorBefore = time.tv_sec * 1000000LL + time.tv_usec; // in microseconds
    obj.vectorFordJohnson(0, obj.getVectorSize() - 1);
    gettimeofday(&time, NULL);
    long long   vectorAfter = time.tv_sec * 1000000LL + time.tv_usec; // in microseconds

    gettimeofday(&time, NULL);
    long long   listBefore = time.tv_sec * 1000000LL + time.tv_usec; // in microseconds
    obj.listFordJohnson(0, obj.getListSize() - 1);
    gettimeofday(&time, NULL);
    long long   listAfter = time.tv_sec * 1000000LL + time.tv_usec; // in microseconds

    // std::cout<<GREEN<<"After[std::vector]: "<<RESET;
    // obj.displayVector(10); 
    // std::cout<<GREEN<<"After[std::list]: "<<RESET;
    // obj.displayList(10); 
    std::cout<<GREEN<<"After: "<<RESET;
    obj.displayList(10); 

    std::cout<<BLUE<<"Time to process a range of "<<obj.getVectorSize();
    std::cout<<" elements with std::vector :  "<<RESET;
    std::cout<<YELLOW<<(vectorAfter - vectorBefore) / 1000.0<<" us"<<RESET<<std::endl;

    std::cout<<BLUE<<"Time to process a range of "<<obj.getListSize();
    std::cout<<" elements with std::list :  "<<RESET;
    std::cout<<YELLOW<<(listAfter - listBefore) / 1000.0<<" us"<<RESET<<std::endl;
    return 0;
}