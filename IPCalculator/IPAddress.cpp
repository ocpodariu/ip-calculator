#include "IPAddress.h"

#include <string>

IPAddress::IPAddress (unsigned char a, unsigned char b, unsigned char c, unsigned char d) : m_a(a), m_b(b), m_c(c), m_d(d) {}

IPAddress IPAddress::operator& (const IPAddress& addr) const {
    return IPAddress(m_a & addr.m_a,
                     m_b & addr.m_b,
                     m_c & addr.m_c,
                     m_d & addr.m_d);
}

IPAddress IPAddress::operator| (const IPAddress& addr) const {
    return IPAddress(m_a | addr.m_a,
                     m_b | addr.m_b,
                     m_c | addr.m_c,
                     m_d | addr.m_d);
}

IPAddress IPAddress::operator~ () const {
    return IPAddress(~this->m_a,
                     ~this->m_b,
                     ~this->m_c,
                     ~this->m_d);
}

bool IPAddress::operator== (const IPAddress& addr) const {
    return (m_a == addr.m_a) &&
           (m_b == addr.m_b) &&
           (m_c == addr.m_c) &&
           (m_d == addr.m_d);
}

bool IPAddress::operator!= (const IPAddress& addr) const {
    return !(operator==(addr));
}

std::ostream& operator<< (std::ostream& os, const IPAddress& addr) {
    os << (int) addr.m_a << '.'
       << (int) addr.m_b << '.'
       << (int) addr.m_c << '.'
       << (int) addr.m_d;

    return os;
}

std::istream& operator>> (std::istream& is, IPAddress& addr) {
    // TODO check correctness of input
    // (now I'm assuming the input is correct: "A.B.C.D")

    // Read entire line
    std::string line;
    std::getline(is, line);

    // Split the line using '.' as delimiter
    size_t pos = 0;
    std::string delimiter = ".";
    std::string content;
    
    // Read A
    // If the line contains at least one delimiter character
    if ((pos = line.find(delimiter)) != std::string::npos) {
        content = line.substr(0, pos);
        addr.m_a = atoi(content.c_str());
        line.erase(0, pos + 1);
    }
    
    // Read B
    // If the line contains at least one delimiter character
    if ((pos = line.find(delimiter)) != std::string::npos) {
        content = line.substr(0, pos);
        addr.m_b = atoi(content.c_str());
        line.erase(0, pos + 1);
    }
    
    // Read C
    // If the line contains at least one delimiter character
    if ((pos = line.find(delimiter)) != std::string::npos) {
        content = line.substr(0, pos);
        addr.m_c = atoi(content.c_str());
        line.erase(0, pos + 1);
    }
    
    // Read D
    // The remaining part of the string has no more delimiters
    addr.m_d = atoi(line.c_str());

    return is;
}

void IPAddress::setAddress (unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    m_a = a;
    m_b = b;
    m_c = c;
    m_d = d;
}

void IPAddress::setAddress (unsigned int addr) {
    // Reset all 4 bytes
    m_a = 0;
    m_b = 0;
    m_c = 0;
    m_d = 0;

    // "addr" is a 32 bit integer = [b31 b30 ... b1 b0],
    // that will be split into 4 separate bytes:
    //      A = [b31 ... b24];
    //      B = [b23 ... b16];
    //      C = [b15 ...  b8];
    //      D = [ b7 ...  b0].
    
    // Each byte will be created using the formula
    // to convert from base 2 to base 10:
    //      nr base 10 = 2^n * bn + ... + 2^0 * b0;

    int i, last_bit;

    // Create last byte (D)
    for (i = 0; i < 8; i++) {
        last_bit = addr & 1;
        m_d += pow(2, i) * last_bit;
        addr = addr >> 1;
    }

    // Create third byte (C)
    for (i = 0; i < 8; i++) {
        last_bit = addr & 1;
        m_c += pow(2, i) * last_bit;
        addr = addr >> 1;
    }

    // Create second byte (B)
    for (i = 0; i < 8; i++) {
        last_bit = addr & 1;
        m_b += pow(2, i) * last_bit;
        addr = addr >> 1;
    }

    // Create first byte (A)
    for (i = 0; i < 8; i++) {
        last_bit = addr & 1;
        m_a += pow(2, i) * last_bit;
        addr = addr >> 1;
    }
}