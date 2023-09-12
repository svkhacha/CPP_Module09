#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void) { }

PmergeMe::PmergeMe(const std::string& numSequence)
{
    std::string integers = numSequence;
    try
    {
        this->_fillContainer(integers);
    }
    catch (const std::exception& e)
    {
        throw std::runtime_error(RED "❌ ERROR" RESET);
    }
    _listAction = _vectorAction = getVectorSize() / 100;
    if (_vectorAction < 16)
        _listAction = _vectorAction = 16;
}

PmergeMe::PmergeMe(const PmergeMe& other)
{
    int vectorIndex = 0;
    this->_vectorAction = other._vectorAction;
    this->_listAction = other._listAction;
    this->_vector.reserve(other._vector.size());
    for (std::list<int>::const_iterator it = other._list.begin(); it != other._list.end(); ++it)
    {
        this->_list.push_back(*it);
        this->_vector.push_back(other._vector[vectorIndex++]);
    }
}

PmergeMe&   PmergeMe::operator=(const PmergeMe& other)
{
    if (this != &other)
    {
        int vectorIndex = 0;
        this->_vectorAction = other._vectorAction;
        this->_listAction = other._listAction;
        this->_vector.clear();
        this->_list.clear();
        this->_vector.reserve(other._vector.size());
        for (std::list<int>::const_iterator it = other._list.begin(); it != other._list.end(); ++it)
        {
            this->_list.push_back(*it);
            this->_vector.push_back(other._vector[vectorIndex++]);
        }
    }
    return *this;
}

PmergeMe::~PmergeMe(void) { }

void    PmergeMe::_fillContainer(std::string& numSequence)
{
    long long   integer;
    size_t      forbiddenChars = numSequence.find_first_not_of(" +0123456789");
    if (forbiddenChars != std::string::npos)
        throw std::runtime_error(RED "❌ ERROR" RESET);
    else
    {
        size_t  whitespace = numSequence.find(' ');
        while (1)
        {
            std::stringstream numStream(numSequence.substr(0, whitespace));
            numStream >> integer;
            if (integer == 0  || integer > INT_MAX)
            {
                this->_vector.clear();
                this->_list.clear();
                throw std::runtime_error(RED "❌ ERROR" RESET);
                return ;
            }
            this->_vector.push_back(static_cast<int>(integer));
            this->_list.push_back(static_cast<int>(integer));
            numSequence = numSequence.substr(whitespace + 1);
            if (whitespace == std::string::npos)
                break ;
            whitespace = numSequence.find(' ');
        }
    }
}

void    PmergeMe::_vectorInsertionSort(int begin, int end)
{
    int i, key, j;
    for (i = begin + 1; i <= end; ++i)
    {
        key = _vector[i];
        j = i;

        while (j > begin && key < _vector[j - 1])
        {
            _vector[j] = _vector[j - 1];
            --j;
        }
        _vector[j] = key;
    }
}

void    PmergeMe::_vectorMergeSort(int begin, int end)
{
    int mid = (begin + end) / 2;
    int i = begin;
    int j = mid + 1;
    int index = 0;
    std::vector<int>    tmp(end - begin + 1);

    while (i <= mid && j <= end)
    {
        if (_vector[i] < _vector[j])
            tmp[index++] = _vector[i++];
        else
            tmp[index++] = _vector[j++];
    }
    while (i <= mid)
        tmp[index++] = _vector[i++];
    while (j <= end)
        tmp[index++] = _vector[j++];
    for (int i = 0; i < index; ++i)
        _vector[begin + i] = tmp[i];
}

void    PmergeMe::vectorFordJohnson(int begin, int end)
{
    if (end - begin < _vectorAction)
    {
        _vectorInsertionSort(begin, end);
        return ;
    }
    vectorFordJohnson(begin, (begin + end) / 2);
    vectorFordJohnson((begin + end) / 2 + 1, end);
    _vectorMergeSort(begin, end);
}

void    PmergeMe::checkVectorSort(void)
{
    if (_vector.empty())
    {
        std::cout<<YELLOW<<"The vector is empty !"<<RESET<<std::endl;
        return ;
    }
    std::vector<int>::const_iterator    comparisonIt;
    for (std::vector<int>::const_iterator it = _vector.begin(); it != _vector.end(); ++it)
    {
        comparisonIt = it;
        std::advance(comparisonIt, 1);
        if (comparisonIt != _vector.end())
        {
            if (*it > *comparisonIt)
            {
                std::cout<<YELLOW<<"The vector is not sorted :("<<RESET<<std::endl;
                return ;
            }
        }
    }
    std::cout<<YELLOW<<"The vector is sorted :)"<<RESET<<std::endl;
}

int PmergeMe::getVectorSize(void) const { return this->_vector.size(); }

void    PmergeMe::displayVector(unsigned int value) const
{
    if (_vector.empty() ==  true || value == 0)
        return ;
    std::vector<int>::const_iterator    it = _vector.begin();
    std::cout<<CYAN<<*it;
    it++;
    for (; it != _vector.end() && --value; ++it)
        std::cout<<" "<<*it;
    if (it != _vector.end())
    {
        std::vector<int>::const_iterator    it1 = _vector.end();
        if (it1 - it > 2)
            std::cout<<" ...";
        for (int i = 0; i < 2 && it1 > it; ++i)
            it1--;
        for (; it1 != _vector.end(); ++it1)
            std::cout<<" "<<*it1;
    }
    std::cout<<RESET<<std::endl;
}

void    PmergeMe::_listInsertionSort(int begin, int end)
{
    std::list<int>::iterator    beginIt, iIt, jIt, keyIt;
    int i, key;
    beginIt = _list.begin();
    iIt = _list.begin();
    std::advance(beginIt, begin);
    std::advance(iIt, begin + 1);

    for (i = begin + 1; i <= end; ++i)
    {
        key = *iIt;
        jIt = iIt;

        while (jIt != beginIt && *(--jIt) > key)
        {
            keyIt = jIt;
            ++jIt;
            *jIt = *keyIt;
            --jIt;
        }
        if (*jIt > key)
            *jIt = key;
        else
            *(++jIt) = key;
        ++iIt;
    } 
}

void    PmergeMe::_listMergeSort(int begin, int end)
{
    std::list<int>::iterator    mid = _list.begin();
    std::advance(mid, (begin + end) / 2);
    std::list<int>::iterator    left = _list.begin();
    std::advance(left, begin);
    std::list<int>::iterator    right = mid;
    std::advance(right, 1);
    std::list<int>::iterator    endIt = _list.begin();
    std::advance(endIt, end + 1);
    std::list<int>::iterator    midNext = mid;
    std::advance(midNext, 1);
    
    std::list<int>  tmp;
    while (left != midNext && right != endIt)
    {
        if (*left < *right)
            tmp.push_back(*left++);
        else
            tmp.push_back(*right++);
    }
    while (left != midNext)
        tmp.push_back(*left++);
    while (right != endIt)
        tmp.push_back(*right++);
    left = _list.begin();
    std::advance(left, begin);
    std::list<int>::iterator    tmpIt = tmp.begin();
    while (left != endIt)
        *left++ = *tmpIt++;
}

void    PmergeMe::listFordJohnson(int begin, int end)
{
    if (end - begin < _listAction)
    {
        _listInsertionSort(begin, end);
        return ;
    }
    listFordJohnson(begin, (begin + end) / 2);
    listFordJohnson((begin + end) / 2 + 1, end);
    _listMergeSort(begin, end);
}

void    PmergeMe::checkListSort(void)
{
    if (_list.empty())
    {
        std::cout<<YELLOW<<"The list is empty !"<<RESET<<std::endl;
        return ;
    }
    std::list<int>::const_iterator  comparisonIt;
    for (std::list<int>::const_iterator it = _list.begin(); it != _list.end(); ++it)
    {
        comparisonIt = it;
        std::advance(comparisonIt, 1);
        if (comparisonIt != _list.end())
        {
            if (*it > *comparisonIt)
            {
                std::cout<<YELLOW<<"The list is not sorted :("<<RESET<<std::endl;
                return ;
            }
        }
    }
    std::cout<<YELLOW<<"The list is sorted :)"<<RESET<<std::endl;
}

int PmergeMe::getListSize(void) const {return this->_list.size(); }

void    PmergeMe::displayList(unsigned int value) const
{
    if (_list.empty() == true || value == 0)
        return ;
    std::list<int>::const_iterator  it = _list.begin();
    std::cout<<CYAN<<*it;
    it++;
    for (; it != _list.end() && (--value); ++it)
        std::cout<<" "<<*it;
    if (it != _list.end())
    {
        std::list<int>::const_iterator  it1 = _list.end();
        if (std::distance(it, it1) > 2)
            std::cout<<" ...";
        for (int i = 0; i < 2 && (std::distance(it, it1) > 0); ++i)
            it1--;
        for (; it1 != _list.end(); ++it1)
            std::cout<<" "<<*it1;
    }
    std::cout<<RESET<<std::endl;
}