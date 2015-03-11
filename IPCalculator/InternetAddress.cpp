#include "InternetAddress.h"

InternetAddress::InternetAddress (IPAddress& ip, IPAddress& mask) : m_address(ip), m_subnet_mask(mask) {
    calculateNB();
}

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

    addr.calculateNB();

    return is;
}

IPAddress InternetAddress::getIPAddress () const { return m_address; }

IPAddress InternetAddress::getSubnetMask () const { return m_subnet_mask; }

void InternetAddress::setIPAddress (IPAddress& ip) {
    m_address = ip;
    calculateNB();
}

void InternetAddress::setIPAddress (unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    m_address.setAddress(a, b, c, d);
    calculateNB();
}

void InternetAddress::setSubnetMask (IPAddress& mask) {
    m_subnet_mask = mask;
    calculateNB();
}

void InternetAddress::setSubnetMask (unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    m_subnet_mask.setAddress(a, b, c, d);
    calculateNB();
}

void InternetAddress::calculateNB () {
    // NA = (ip_address) AND (subnet_mask)
    m_network_address = m_address & m_subnet_mask;

    // BA = (ip_address) OR (wildcard), where wildcard = ~subnet_mask
    m_broadcast_address = m_address | (~m_subnet_mask);
}