#include "IPAddress.h"

IPAddress::IPAddress (unsigned char a, unsigned char b, unsigned char c, unsigned char d) : m_a(a), m_b(b), m_c(c), m_d(d) {}

std::ostream& operator<< (std::ostream& os, const IPAddress& addr) {
    os << (int) addr.m_a << '.'
       << (int) addr.m_b << '.'
       << (int) addr.m_c << '.'
       << (int) addr.m_d;

    return os;
}