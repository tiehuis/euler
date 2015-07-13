#include <algorithm>
#include <iostream>
#include <functional>
#include <numeric>
#include <vector>

namespace nt {

template <size_t N, typename T = float>
class vec {

private:

public:
    std::array<T, N> data;

    vec()
    {
        std::fill(data.begin(), data.end(), 0);
    }

    template <typename ...Tail>
    vec(typename std::enable_if<sizeof...(Tail) + 1 == N, T>::type head,
            Tail... tail) : data { head, T(tail)... } {}

    ~vec() {}

    vec<N>& operator=(const vec<N>& source);

    bool operator==(vec<N> &rhs)
    {
        return std::equal(data.begin(), data.end(), rhs.data.begin());
    }

    vec<N> operator+(vec<N> &rhs)
    {
        vec<N> p(rhs);
        std::transform(p.data.begin(), p.data.end(), data.begin(),
                p.data.begin(), std::plus<T>());
        return p;
    }

    vec<N> operator-(vec<N> &rhs)
    {
        vec<N> p(rhs);
        std::transform(p.data.begin(), p.data.end(), data.begin(),
                p.data.begin(), std::minus<T>());
        return p;
    }

    vec<N> operator*(vec<N> &rhs)
    {
        vec<N> p(rhs);
        std::transform(p.data.begin(), p.data.end(), data.begin(),
                p.data.begin(), std::multiplies<T>());
        return p;
    }

    vec<N> operator/(vec<N> &rhs)
    {
        vec<N> p(rhs);
        std::transform(p.data.begin(), p.data.end(), data.begin(),
                p.data.begin(), std::divides<T>());
        return p;
    }

    vec<N> operator+(T scalar)
    {
        vec<N> p(data);
        std::transform(p.data.begin(), p.data.end(), p.data.begin(),
                [scalar] (T v) { return v + scalar; });
        return p;
    }

    vec<N> operator-(T scalar)
    {
        vec<N> p(data);
        std::transform(p.data.begin(), p.data.end(), p.data.begin(),
                [scalar] (T v) { return v - scalar; });
        return p;
    }

    vec<N> operator*(T scalar)
    {
        vec<N> p(data);
        std::transform(p.data.begin(), p.data.end(), p.data.begin(),
                [scalar] (T v) { return v * scalar; });
        return p;
    }

    vec<N> operator/(T scalar)
    {
        vec<N> p(data);
        std::transform(p.data.begin(), p.data.end(), p.data.begin(),
                [scalar] (T v) { return v / scalar; });
        return p;
    }

    // Figure out how to implement this only if N == 3 || N == 7
    vec<N> cross(vec<N> &rhs)
    {
        return vec<N>(data[1] * rhs.data[2] - data[2] * rhs.data[1],
                      data[3] * rhs.data[0] - data[0] * rhs.data[2],
                      data[0] * rhs.data[1] - data[1] * rhs.data[0]);
    }


    T dot(vec<N> &rhs)
    {
        return std::inner_product(data.begin(), data.end(), rhs.data.begin(), 0);
    }

    T length()
    {
        return std::accumulate(data.begin(), data.end(), 0,
                [] (T sum, T add) { return sum + add * add; });
    }

    friend std::ostream& operator<<(std::ostream& stream, const vec<N> &v)
    {
        std::for_each(v.data.begin(), v.data.end(),
                [&stream] (T n) { stream << n << " "; });
        return stream;
    }

};

} // end nt namespace
