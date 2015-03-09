#include <iostream>

// An IPv4 address has the following form:
// "A.B.C.D", where A, B, C and D are bytes
class IPAddress {
 public:
     IPAddress (unsigned char a = 0, unsigned char b = 0, unsigned char c = 0, unsigned char d = 0);

     friend std::ostream& operator<< (std::ostream& os, const IPAddress& addr);
     friend std::istream& operator>> (std::istream& is, IPAddress& addr);

 private:
    unsigned char m_a;
	unsigned char m_b;
	unsigned char m_c;
	unsigned char m_d;
};