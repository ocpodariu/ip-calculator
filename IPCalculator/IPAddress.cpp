#include "IPAddress.h"

#include <string>

IPAddress::IPAddress (unsigned char a, unsigned char b, unsigned char c, unsigned char d) : m_a(a), m_b(b), m_c(c), m_d(d) {}

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