#ifndef _INTERNET_ADDRESS_H
#define _INTERNET_ADDRESS_H

#include "IPAddress.h"

// An Internet address is defined by an IP address and
// a subnet mask. It can represent a network address,
// a broadcast address or a host address.
class InternetAddress {
 public:
    InternetAddress (IPAddress& ip, IPAddress& mask);

 private:
    IPAddress m_address;
    IPAddress m_subnet_mask;
};

#endif // _INTERNET_ADDRESS_H