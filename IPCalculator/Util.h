#ifndef _UTIL_H_
#define _UTIL_H_

#include "InternetAddress.h"

#include <vector>
#include <string>

// Helper class that includes methods for IP network
// processes such as identifying the type of an address.
class Util {
 public:
    // Identifies the type of an Internet address:
    //      (0) network address;
    //      (1) broadcast address;
    //      (2) host address.
    static int identifyAddress (const InternetAddress& address);
    
    // Subnet a network into multiple smaller subnetworks.
    // Each subnetwork (i) needs to accommodate hosts[i] hosts.
    // The resulting vector contains all the subnetworks.
    static std::vector<InternetAddress> subnetNetwork (const std::string& inputFilename);
    static std::vector<InternetAddress> subnetNetwork (InternetAddress network, std::vector<int> hosts);
    
    static void subnetNetwork (const std::string& inputFilename, const std::string& outputFilename);
    static void subnetNetwork (InternetAddress network, std::vector<int> hosts, const std::string& outputFilename);
};

#endif // _UTIL_H_