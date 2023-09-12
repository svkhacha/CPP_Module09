#include "RPN.hpp"

RPN::RPN(void) { }
RPN::RPN(const RPN& other) { *this = other; }

RPN&    RPN::operator=(const RPN& other)
{
    if (this != &other)
    {
        *this = other;
    }
    return *this;
}

RPN::~RPN(void) { }

void    RPN::checkAndCalculate(std::string expression)
{
    int operand1, operand2 = 0;
    size_t  length = expression.length();

    for (size_t i = 0; i < length; ++i)
    {
        if (!(expression[i] >= '0' && expression[i] <= '9') && !(expression[i] == '+' ||
            expression[i] == '-' || expression[i] == '*' || expression[i] == '/' || expression[i] == ' '))
            {
                std::cout<<RED<<"❌ ERROR: Not valid symbols occurred !"<<RESET<<std::endl;
                return ;
            }
    }
    for (size_t i = 0; i < length; ++i)
    {
        if (expression[i] == ' ')
            continue;
        if (expression[i] >= '0' && expression[i] <= '9')
            this->_stack.push(expression[i] - 48);
        else
        {
            if (this->_stack.size() > 1)
                ;
            else
            {
                std::cout<<RED<<"❌ ERROR: Not valid postfix notation !"<<RESET<<std::endl;
                while (this->_stack.empty() == 0)
                {
                    this->_stack.pop();
                }
                return ;
            }
            if (expression[i] == '+')
            {
                operand2 = this->_stack.top();
                this->_stack.pop();
                operand1 = this->_stack.top();
                this->_stack.pop();
                this->_stack.push(operand1 + operand2);
            }
            else if (expression[i] == '-')
            {
                operand2 = this->_stack.top();
                this->_stack.pop();
                operand1 = this->_stack.top();
                this->_stack.pop();
                this->_stack.push(operand1 - operand2);
            }
            else if (expression[i] == '*')
            {
                operand2 = this->_stack.top();
                this->_stack.pop();
                operand1 = this->_stack.top();
                this->_stack.pop();
                this->_stack.push(operand1 * operand2);
            }
            else if (expression[i] == '/')
            {
                operand2 = this->_stack.top();
                this->_stack.pop();
                operand1 = this->_stack.top();
                this->_stack.pop();
                if (operand2 != 0)
                    this->_stack.push(operand1 / operand2);
                else
                {
                    std::cout<<RED<<"❌ ERROR: Division by zero is forbidden !"<<RESET<<std::endl;
                    while (this->_stack.empty() == 0)
                    {
                        this->_stack.pop();
                    }
                    return;
                }
            }
        }
    }
    if (this->_stack.size() != 1)
    {
        std::cout<<RED<<"❌ ERROR"<<RESET<<std::endl;
        while (this->_stack.empty() == 0)
        {
            this->_stack.pop();
        }
        return ;
    }
    std::cout<<this->_stack.top()<<std::endl;
    while (this->_stack.empty() == 0)
    {
        this->_stack.pop();
    }
    return ;
}