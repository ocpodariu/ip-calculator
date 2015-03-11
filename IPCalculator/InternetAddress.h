#ifndef _INTERNET_ADDRESS_H
#define _INTERNET_ADDRESS_H

#include "IPAddress.h"

#include <iostream>

// An Internet address is defined by an IP address and
// a subnet mask. It can represent a network address,
// a broadcast address or a host address.
class InternetAddress {
 public:
    InternetAddress (IPAddress& ip, IPAddress& mask);

    friend std::ostream& operator<< (std::ostream& os, const InternetAddress& addr);
	friend std::istream& operator>> (std::istream& is, InternetAddress& addr);

    IPAddress getIPAddress () const;
    IPAddress getSubnetMask () const;

    void setIPAddress (IPAddress& ip);
    void setIPAddress (unsigned char a, unsigned char b, unsigned char c, unsigned char d);
    
    void setSubnetMask (IPAddress& mask);
    void setSubnetMask (unsigned char a, unsigned char b, unsigned char c, unsigned char d);

 private:
    IPAddress m_address;
    IPAddress m_subnet_mask;
};

#endif // _INTERNET_ADDRESS_H