#include "bits.h"
#include "errors.h"

namespace util
{
std::vector<uint8_t> convertBits(unsigned char *data, unsigned int const dataLength,
                                 int const fromBits, int const toBits, bool const pad)
{
    int acc = 0;
    int bits = 0;
    std::vector<uint8_t> ret;
    int maxV = (1 << toBits) - 1;
    int maxAcc = (1 << (fromBits + toBits - 1)) - 1;

    unsigned int ct = 0;
    for (unsigned char value = *data; ct<dataLength; value = *++data)
    {
        int valueAsInt = value & 0xff;

        if ((valueAsInt < 0) || (valueAsInt >> fromBits != 0))
        {
            throw std::invalid_argument(ERROR_MSG_CONVERT_BITS);
        }

        acc = ((acc << fromBits) | valueAsInt) & maxAcc;
        bits += fromBits;

        while (bits >= toBits)
        {
            bits -= toBits;
            ret.push_back((acc >> bits) & maxV);
        }
        ct++;
    }

    if (pad)
    {
        if (bits > 0)
        {
            ret.push_back((acc << (toBits - bits)) & maxV);
        }
    }
    else if (bits >= fromBits || ((acc << (toBits - bits)) & maxV) != 0)
    {
        throw std::invalid_argument(ERROR_MSG_CONVERT_BITS);
    }

    return ret;
}
}
