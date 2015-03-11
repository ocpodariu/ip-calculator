#include "InternetAddress.h"

InternetAddress::InternetAddress (IPAddress& ip, IPAddress& mask) : m_address(ip), m_subnet_mask(mask) {}

std::ostream& operator<< (std::ostream& os, const InternetAddress& addr) {
    os << "IP: " << addr.m_address           << std::endl;
    os << "SN: " << addr.m_subnet_mask       << std::endl;
    os << "NA: " << addr.m_network_address   << std::endl;
    os << "BA: " << addr.m_broadcast_address << std::endl;

    return os;
}

std::istream& operator>> (std::istream& is, InternetAddress& addr) {
    is >> addr.m_address;
    is >> addr.m_subnet_mask;

    return is;
}

IPAddress InternetAddress::getIPAddress () const { return m_address; }

IPAddress InternetAddress::getSubnetMask () const { return m_subnet_mask; }

void InternetAddress::setIPAddress (IPAddress& ip) { m_address = ip; }

void InternetAddress::setIPAddress (unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    m_address.setAddress(a, b, c, d);
}

void InternetAddress::setSubnetMask (IPAddress& mask) { m_subnet_mask = mask; }

void InternetAddress::setSubnetMask (unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    m_subnet_mask.setAddress(a, b, c, d);
}