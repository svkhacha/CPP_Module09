#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <string>
#include <algorithm>
#include <stack>

#define RED     "\33[1;31m"
#define RESET   "\33[0;m"

class RPN
{
    public:
        RPN(void);
        RPN(const RPN& other);
        RPN&    operator=(const RPN& other);
        ~RPN(void);

        void    checkAndCalculate(std::string expression);
    
    private:
        std::stack<int> _stack;
};

#endif