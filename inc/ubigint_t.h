#include <string>

namespace crypto
{
    struct InvalidData : public std::exception
    {
        const char *msg() const throw();
    };

    class ubigint_t
    {
    private:
        std::string rawdata = "0";

        bool validatedata();
        void cutzeros();

    public:
        ubigint_t();
        ubigint_t(std::string inputdata);

        std::string get() const;
        ubigint_t operator+(ubigint_t &rh);
        ubigint_t operator*(ubigint_t &rh);
        friend std::istream &operator>>(std::istream &is, ubigint_t &num);
    };
    std::ostream &operator<<(std::ostream &os, const ubigint_t &num);
    std::istream &operator>>(std::istream &instream, ubigint_t &num);
} // namespace crypto
