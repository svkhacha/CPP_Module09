#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void) { }

BitcoinExchange::BitcoinExchange(std::ifstream& dataFile)
{
    size_t                          datePart, comma;
    std::pair<std::string, float>   rateAndText;
    std::string                     eachLine, date, rate = "";

    std::getline(dataFile, eachLine);
    while (std::getline(dataFile, eachLine))
    {
        comma   = eachLine.find(',');
        date    = eachLine.substr(0, comma);
        if (comma != std::string::npos)
            rate = eachLine.substr(comma + 1);
        datePart = _checkDate(date);
        if (!datePart)
        {
            _data.clear();
            std::cout<<RED<<"[data.csv] Error: bad input => "<<RESET<<date<<std::endl;
            return ;
        }
        rateAndText = _checkValue(rate);
        if (rateAndText.first != "valid")
        {
            _data.clear();
            std::cout<<RED<<"[data.csv] "<<rateAndText.first<<RESET;
            return ;
        }
        _data[datePart] = rateAndText.second;  
    }
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
    for (std::map<unsigned int, float>::const_iterator it = other._data.begin();
        it != other._data.end(); ++it)
            this->_data[(*it).first] = (*it).second; // this->_data[it->first] = it->second;
}

BitcoinExchange&    BitcoinExchange::operator=(const BitcoinExchange& other)
{
    if (this != &other)
    {
        this->_data.clear();
        for (std::map<unsigned int, float>::const_iterator it = other._data.begin();
            it != other._data.end(); ++it)
                this->_data[(*it).first] = (*it).second;
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange(void) { }

void    BitcoinExchange::_splitStr(std::string& lineStr)
{
    size_t  begin = lineStr.find_first_not_of(" \f\n\r\t\v");
    lineStr.erase(0, begin);
    size_t  end = lineStr.find_last_not_of(" \f\n\r\t\v");
    lineStr.erase(end + 1);
}

unsigned int    BitcoinExchange::_calculateDays(int year, int month, int day)
{
    int february = 28 + (((year < 1582) && (year % 4 == 0)) ||
        ((year >= 1582) && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)));
    int months[12] = {31, february, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int accumulate = std::accumulate(months, months + (month - 1), 0);
    int daysTillDate = accumulate + day;
    
    unsigned int leapYears = 0;
    for (int i = 1; i < year; ++i)
        leapYears += (((year < 1582) && (i % 4 == 0)) ||
            ((year >= 1582) && ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0)));
    unsigned int    daysCalculated = leapYears + 365 * (year - 1) + daysTillDate; 
        return daysCalculated;
}

unsigned int    BitcoinExchange::_checkDate(const std::string& dateStr)
{
    size_t  forbiddenChars = dateStr.find_first_not_of("-0123456789");
    if (dateStr.length() != 10 || forbiddenChars != std::string::npos ||
        dateStr[4] != '-' || dateStr[7] != '-')
    return 0;

    std::string         yyyy = dateStr.substr(0, 4);
    std::istringstream  yearStream(yyyy);
    std::string         mm = dateStr.substr(5, 2);
    std::istringstream  monthStream(mm);
    std::string         dd = dateStr.substr(8, 2);
    std::istringstream  dayStream(dd);
    int Year, Month, Day;
    yearStream>>Year;
    monthStream>>Month;
    dayStream>>Day;
    if (Year < 1 || Month < 1 || Month > 12 || Day < 1 || Day > 31)
        return 0;
    int daysInMonth = 31;
    if (Month == 4 || Month == 6 || Month == 9 || Month == 11)
        daysInMonth = 30;
    else if (Month == 2)
        daysInMonth = 28 + (((Year < 1582) && (Year % 4 == 0)) ||
        ((Year >= 1582) && ((Year % 4 == 0 && Year % 100 != 0) || Year % 400 == 0)));
    if (Day > daysInMonth)
        return 0;
    return _calculateDays(Year, Month, Day);
}

std::pair<std::string, float>   BitcoinExchange::_checkValue(const std::string& valueStr)
{
    if (valueStr == "" || valueStr == "+" || valueStr == "-")
        return std::make_pair(RED "Error: missing value => " RESET, 0.0);
    size_t  forbiddenChars = valueStr.find_first_not_of("0123456789");
    if (valueStr[0] == '-' || valueStr[0] == '+')
        forbiddenChars = valueStr.substr(1).find_first_not_of("0123456789");
    if (forbiddenChars == std::string::npos)
    {
        std::stringstream  valueStream(valueStr);
        long long integerValue;
        valueStream >> integerValue;
        if (integerValue > INT_MAX)
            return std::make_pair(RED "Error: too large a number.\n" RESET, 0.0);
        if (integerValue < INT_MIN)
            return std::make_pair(RED "Error: too small a number.\n" RESET, 0.0);
        if (integerValue < 0)
            return std::make_pair(RED "Error: not a positive number.\n" RESET, 0.0);
        return std::make_pair("valid", static_cast<float>(integerValue));
    }
    char*   end;
    float   floatValue = strtof(valueStr.c_str(), &end);
    if (*end != '\0')
        return std::make_pair(RED "Error: not a valid number.\n" RESET, 0.0);
    if (floatValue == HUGE_VALF)
        return std::make_pair(RED "Error: too large a number.\n" RESET, 0.0);
    if (floatValue < -HUGE_VALF)
        return std::make_pair(RED "Error: too small a number.\n" RESET, 0.0);
    if (floatValue < 0)
        return std::make_pair(RED "Error: not a positive number.\n" RESET, 0.0);
    return std::make_pair("valid", floatValue);
}

void    BitcoinExchange::displayResult(std::ifstream& inputFile)
{
    if (_data.empty())
        return ;
    size_t                                  datePart, pipe;
    std::string                             eachLine, date, value;
    std::pair<std::string, float>           valueAndText;
    std::map<unsigned int, float>::iterator it, startIt;

    startIt = _data.begin();
    std::getline(inputFile, eachLine);
    while(std::getline(inputFile, eachLine))
    {
        pipe    = eachLine.find('|');
        date    = eachLine.substr(0, pipe);
        value   = "";
        if (pipe != std::string::npos)
            value = eachLine.substr(pipe + 1);
        this->_splitStr(date);
        this->_splitStr(value);
        datePart = _checkDate(date);
        if (datePart)
        {
            it = _data.find(datePart);
            while (--datePart && datePart >= startIt->first && it == _data.end())
                it = _data.find(datePart);
            if (it == _data.end())
                std::cout<<RED<<"Error: no such date in data.csv => "<<RESET<<date<<std::endl;
            else
            {
                valueAndText = _checkValue(value);
                if (valueAndText.first != "valid")
                {
                    std::cout<<valueAndText.first;
                    if (value == "")
                        std::cout<<date<<std::endl;
                }
                else if (valueAndText.second > 1000)
                    std::cout<<RED<<"Error: the price is greater than 1000 => "<<RESET<<value<<std::endl;
                else
                {
                    std::cout<<GREEN<<date<<" => "<<valueAndText.second<<" = "<<RESET;
                    std::cout<<YELLOW<<valueAndText.second * (*it).second<<RESET<<std::endl;
                }
            }
        }
        else
            std::cout<<RED<<"Error: bad input => "<<RESET<<date<<std::endl;
    }
}
