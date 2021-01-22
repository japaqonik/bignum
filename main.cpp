#include "inc/ubigint_t.h"
#include <iostream>
#include <cmath>
#include <complex>
#include <vector>

using namespace std;

typedef complex<double> complexdobule_t;
typedef vector<complexdobule_t> vectorcomplex_t;

vectorcomplex_t fft(const vectorcomplex_t &a)
{
    const auto n = a.size();

    if (n == 1)
    {
        return a;
    }

    vectorcomplex_t y0_even(n / 2);
    vectorcomplex_t y1_odd(n / 2);
    for (int i = 0; i < n / 2; i++)
    {
        y0_even[i] = a[i * 2];
        y1_odd[i] = a[i * 2 + 1];
    }

    const auto y0 = fft(y0_even);
    const auto y1 = fft(y1_odd);

    vectorcomplex_t y(n);
    for (int k = 0; k < n / 2; ++k)
    {
        const double aplha = -2 * k * M_PI / n;
        const auto wk = complexdobule_t(cos(aplha), sin(aplha));
        y[k] = y0[k] + wk * y1[k];
        y[k + n / 2] = y0[k] - wk * y1[k];
    }
    return y;
}

vectorcomplex_t ifft(const vectorcomplex_t &a)
{
    const auto n = a.size();
    vectorcomplex_t conj;
    conj.reserve(n);
    for (const auto &e : a)
    {
        conj.push_back(std::conj(e));
    }

    vectorcomplex_t vecFFT = fft(conj);

    vectorcomplex_t result;
    result.reserve(vecFFT.size());
    for (const auto &e : vecFFT)
    {
        result.push_back(std::conj(e) / static_cast<double>(n));
    }

    return result;
}

void print(const vectorcomplex_t &vect)
{
    for (const auto &complexnum : vect)
    {
        cout << complexnum << endl;
    }
}

int main()
{
    vectorcomplex_t n = {1, 2, 3, 4};

    print(n);

    cout << endl
         << endl;

    auto fftres = fft(n);

    print(fftres);

    cout << endl
         << endl;

    auto ifftres = ifft(fftres);

    print(ifftres);

    cout << "Finished sucessfuly" << endl;

    return 0;
}
