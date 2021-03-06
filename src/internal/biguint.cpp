#include <utility>

#include "bigint/integer.h"
#include "internal/biguint.h"
#include "errors.h"

BigUInt::BigUInt(std::string value) : m_value(std::move(value))
{}

std::string BigUInt::getHexValue() const
{
    std::string ret;

    try
    {
        integer number(m_value, 10);
        number = abs(number);
        ret = number.str(16);
    }
    catch (...)
    {
        throw std::invalid_argument(ERROR_MSG_VALUE + m_value);
    }

    if (ret.size() % 2 != 0)
    {
        ret.insert(ret.begin(), '0');
    }

    return ret;
}

const std::string &BigUInt::getValue() const
{
    return m_value;
}

