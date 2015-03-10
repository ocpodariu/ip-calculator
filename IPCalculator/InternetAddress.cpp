#include "InternetAddress.h"

InternetAddress::InternetAddress (IPAddress& ip, IPAddress& mask) : m_address(ip), m_subnet_mask(mask) {}

std::ostream& operator<< (std::ostream& os, const InternetAddress& addr) {
    os << "IP: " << addr.m_address     << std::endl;
    os << "SN: " << addr.m_subnet_mask << std::endl;

    return os;
}

std::istream& operator>> (std::istream& is, InternetAddress& addr) {
    is >> addr.m_address;
    is >> addr.m_subnet_mask;

    return is;
}