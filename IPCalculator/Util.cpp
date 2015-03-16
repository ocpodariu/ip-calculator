#include "Util.h"

#include <algorithm>

int Util::identifyAddress(const InternetAddress& addr) {
    if (addr.isNetworkAddress())
        return 0;
    else if (addr.isBroadcastAddress())
        return 1;
    else
        return 2;
}

bool compare(int x, int y) {
    return x > y;
}

std::vector<InternetAddress> Util::subnetNetwork (InternetAddress network, std::vector<int> hosts) {
    std::vector<InternetAddress> subnetworks;
    subnetworks.reserve(hosts.size());

    // Make sure the address is the first available
    // host IP address of the network
    network.setIPAddress(network.getNetworkAddress().nextIPAddress());

    // Each subnetwork (i) needs to accommodate (hosts[i] + 2)
    // IPs (1 for the network address and 1 for the broadcast)
    for (unsigned int i = 0; i < hosts.size(); i++)
        hosts[i] += 2;

    // Sort the subnetworks in descending order to ensure
    // a correct subnetting process
    std::sort(hosts.begin(), hosts.end(), compare);

    int n;
    unsigned int mask_32bit;
    IPAddress subnet_mask;
    
    for (unsigned int i = 0 ; i < hosts.size(); i++) {
        // Find smallest power of 2  >= hosts[i]
        n = 1;
        while (hosts[i] > n)
            n = n << 1;

        // Determine corresponding subnet mask
        mask_32bit = n - 1;
        network.setSubnetMask(~mask_32bit);

        // Store this subnetwork
        subnetworks.push_back(InternetAddress(network.getIPAddress(), network.getSubnetMask()));

        // Set the starting IP address of the next subnetwork
        // (the first available host IP address, not the network address)
        network.setIPAddress(network.getBroadcastAddress().nextIPAddress().nextIPAddress());
    }

    return subnetworks;
}