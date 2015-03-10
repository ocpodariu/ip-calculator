#include "InternetAddress.h"

InternetAddress::InternetAddress (IPAddress& ip, IPAddress& mask) : m_address(ip), m_subnet_mask(mask) {}