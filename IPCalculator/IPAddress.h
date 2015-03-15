#ifndef _IP_ADDRESS_H_
#define _IP_ADDRESS_H_

#include <iostream>

// An IPv4 address has the following form:
// "A.B.C.D", where A, B, C and D are bytes
class IPAddress {
 public:
     friend class InternetAddress;

     IPAddress (unsigned char a = 0, unsigned char b = 0, unsigned char c = 0, unsigned char d = 0);
     IPAddress (unsigned int addr);

     IPAddress operator& (const IPAddress& addr) const;
     IPAddress operator| (const IPAddress& addr) const;
     IPAddress operator~ () const;
     
     bool operator== (const IPAddress& addr) const;
     bool operator!= (const IPAddress& addr) const;

     friend std::ostream& operator<< (std::ostream& os, const IPAddress& addr);
     friend std::istream& operator>> (std::istream& is, IPAddress& addr);

     void setAddress (unsigned char a, unsigned char b, unsigned char c, unsigned char d);

     // Sets the IP address using a 32-bit integer representation
     void setAddress (unsigned int addr);

     // Returns the corresponding 32-bit integer representation
     unsigned int toUInteger () const;

     // Returns the next IP address, following this one i.e adding +1 to it
     IPAddress nextIPAddress () const;

 private:
     unsigned char m_a;
     unsigned char m_b;
     unsigned char m_c;
     unsigned char m_d;
};

#endif // _IPADDRESS_H_