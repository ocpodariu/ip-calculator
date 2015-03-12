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

IPAddress InternetAddress::getNetworkAddress () const { return m_network_address; }

IPAddress InternetAddress::getBroadcastAddress () const { return m_broadcast_address; }

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

bool InternetAddress::isNetworkAddress () const { return m_address == m_network_address; }

bool InternetAddress::isBroadcastAddress () const { return m_address == m_broadcast_address; }

bool InternetAddress::isHostAddress () const { return (!isNetworkAddress()) && (!isBroadcastAddress()); }

unsigned int InternetAddress::getNrHosts () const {
    // Create local copies of all 4 bytes
    unsigned char a = m_subnet_mask.m_a;
    unsigned char b = m_subnet_mask.m_b;
    unsigned char c = m_subnet_mask.m_c;
    unsigned char d = m_subnet_mask.m_d;

    // A subnet mask has the following form:
    // 1111...0000, m 1's and n 0's s.t. m + n = 32.
    // Total number of IPs = 2^n.
    // Total number of host IPs = 2^n - 2.
    // (-2 because 1 IP will be the network address
    // an another one will be the broadcast address)

    int n = 0;

    if (d == 255) {
        // No need to update n as d has no zeros
    } else if (d == 0) {
        n += 8;
        if (c == 255) {
            // No need to update n as c has no zeros
        } else if (c == 0) {
            n += 8;
            if (b == 255) {
                // No need to update n as b has no zeros
            } else if (b == 0) {
                n += 8;
                if (a == 255) {
                    // No need to update n as a has no zeros
                } else if (a == 0) {
                    n += 8;
                } else {
                    // Count number of zeros contained in the first byte (a)
                    while ((a & 1) == 0) { n++; a = a >> 1; }
                }
            } else {
                // Count number of zeros contained in the second byte (b)
                while ((b & 1) == 0) { n++; b = b >> 1; }
            }
        } else {
            // Count number of zeros contained in the third byte (c)
            while ((c & 1) == 0) { n++; c = c >> 1; }
        }
    } else {
        // Count number of zeros contained in the last byte (d)
        while ((d & 1) == 0) { n++; d = d >> 1; }
    }

    // Calculate the number of host IPs
    unsigned int nr_hosts = pow(2, n) - 2;

    return nr_hosts;
}

void InternetAddress::calculateNB () {
    // NA = (ip_address) AND (subnet_mask)
    m_network_address = m_address & m_subnet_mask;

    // BA = (ip_address) OR (wildcard), where wildcard = ~subnet_mask
    m_broadcast_address = m_address | (~m_subnet_mask);
}