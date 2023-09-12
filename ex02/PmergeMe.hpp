#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <list>
#include <sstream>
#include <climits>
#include <exception>
#include <sys/time.h>

#define RED	    "\33[1;31m"
#define GREEN	"\33[1;32m"
#define YELLOW	"\33[1;33m"
#define CYAN	"\33[1;36m"
#define PINK	"\33[1;35m"
#define BLUE	"\33[1;34m"
#define RESET	"\33[0;m"

class PmergeMe
{
    public:
        PmergeMe(void); 
        PmergeMe(const std::string& numSequence);
        PmergeMe(const PmergeMe& other);
        PmergeMe&   operator=(const PmergeMe& other);
        ~PmergeMe(void);

        int getVectorSize(void) const;
        int getListSize(void) const;

        void    vectorFordJohnson(int begin, int end);
        void    listFordJohnson(int begin, int end);

        void    checkVectorSort(void);
        void    checkListSort(void);

        void    displayVector(unsigned int value) const;
        void    displayList(unsigned int value) const;

    private:
        std::vector<int>    _vector;
        std::list<int>      _list;
        int                 _vectorAction;
        int                 _listAction;

        void    _fillContainer(std::string& numSequence);
        void    _vectorInsertionSort(int begin, int end);
        void    _vectorMergeSort(int begin, int end);
        void    _listInsertionSort(int begin, int end);
        void    _listMergeSort(int begin, int end);
};

#endif