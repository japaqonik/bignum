#include "../inc/ubigint_t.h"
#include <iostream>
#include <algorithm>

namespace crypto
{

    const char *InvalidData::msg() const throw()
    {
        return "Digit in input data is not a number!!!";
    };

    ubigint_t::ubigint_t()
    {
        if (!validatedata())
            throw InvalidData();
        cutzeros();
    };

    ubigint_t::ubigint_t(std::string inputdata) : rawdata{inputdata}
    {
        if (!validatedata())
            throw InvalidData();
        cutzeros();
    };

    bool ubigint_t::validatedata()
    {
        for (const auto &digit : rawdata)
        {
            if (digit < '0' || digit > '9')
            {
                return false;
            }
        }
        return true;
    };

    void ubigint_t::cutzeros()
    {
        while (rawdata.size() > 1 && rawdata.front() == '0')
        {
            rawdata.erase(rawdata.begin());
        }

        if (rawdata.empty())
        {
            rawdata = "0";
        }
    };

    std::string ubigint_t::get() const
    {
        return rawdata;
    };

    ubigint_t ubigint_t::operator+(ubigint_t &rh)
    {
        if (rawdata.size() < rh.rawdata.size())
        {
            return rh + *this;
        }

        const auto longerstring = rawdata;
        const auto shorterstring = rh.rawdata;

        auto longerit = longerstring.rbegin();
        auto shortertit = shorterstring.rbegin();

        std::string result = "";
        result.reserve(longerstring.size() + shorterstring.size());

        auto mem = 0;
        for (; longerit != longerstring.rend(); ++longerit)
        {
            const auto eofrhreached = shortertit == shorterstring.rend();
            const auto a = *longerit - '0';
            const auto b = eofrhreached ? 0 : *shortertit - '0';

            const auto sum = a + b + mem;

            result.push_back(std::to_string(sum % 10).front());
            mem = sum / 10;

            if (!eofrhreached)
            {
                ++shortertit;
            }
        }

        result.push_back(std::to_string(mem).front());

        std::reverse(result.begin(), result.end());

        return ubigint_t(result);
    };

    ubigint_t ubigint_t::operator*(ubigint_t &rh)
    {
        ubigint_t result;
        auto index = 0;
        for (auto rhit = rh.rawdata.rbegin(); rhit != rh.rawdata.rend(); ++rhit)
        {
            const auto rh = *rhit - '0';
            std::string onedigitresult = "";
            auto mem = 0;
            for (auto lhit = rawdata.rbegin(); lhit != rawdata.rend(); ++lhit)
            {
                const auto lh = *lhit - '0';
                const auto product = rh * lh + mem;

                onedigitresult.push_back(std::to_string(product % 10).front());
                mem = product / 10;
            }

            onedigitresult.push_back(std::to_string(mem).front());
            std::reverse(onedigitresult.begin(), onedigitresult.end());

            for (uint8_t i = 0; i < index; ++i)
            {
                onedigitresult.push_back('0');
            }

            ubigint_t stepresult(onedigitresult);
            result = result + stepresult;

            ++index;
        }

        return result;
    };

    std::ostream &operator<<(std::ostream &os, const ubigint_t &num)
    {
        os << num.get();
        return os;
    };

    std::istream &operator>>(std::istream &instream, ubigint_t &num)
    {
        instream >> num.rawdata;
        return instream;
    };

} // namespace crypto