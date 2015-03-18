#include "Util.h"

#include <fstream>
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

    // Each subnetwork (i) needs to accommodate (hosts[i] + 2)
    // IPs (1 for the network address and 1 for the broadcast)
    for (unsigned int i = 0; i < hosts.size(); i++)
        hosts[i] += 2;

    // Sort the subnetworks in descending order to ensure
    // a correct subnetting process
    std::sort(hosts.begin(), hosts.end(), compare);
    
    // Check if the network can be split into
    // that many subnetworks
    std::vector<int> powers(hosts.size(), 1);
    unsigned int sum = 0;

    for (unsigned int i = 0; i < hosts.size(); i++) {
        // Find smallest power of 2  >= hosts[i]
        while (hosts[i] > powers[i])
            powers[i] = powers[i] << 1;

        sum += powers[i];
    }
    
    if (sum > network.getNrHosts() + 2)
        return subnetworks;

    // Make sure the address is the first available
    // host IP address of the network
    network.setIPAddress(network.getNetworkAddress().nextIPAddress());

    unsigned int mask_32bit;
    IPAddress subnet_mask;
    
    for (unsigned int i = 0 ; i < hosts.size(); i++) {
        // Determine corresponding subnet mask
        mask_32bit = powers[i] - 1;
        network.setSubnetMask(~mask_32bit);

        // Store this subnetwork
        subnetworks.push_back(InternetAddress(network.getIPAddress(), network.getSubnetMask()));

        // Set the starting IP address of the next subnetwork
        // (the first available host IP address, not the network address)
        network.setIPAddress(network.getBroadcastAddress().nextIPAddress().nextIPAddress());
    }

    return subnetworks;
}

std::vector<InternetAddress> Util::subnetNetwork (const std::string& inputFilename) {
    std::ifstream f(inputFilename);

    // Original network
    IPAddress ip, mask;
    f >> ip >> mask;
    
    // (n) subnetworks each requiring (nr_hosts[i]) host IPs
    int n;
    std::vector<int> nr_hosts;

    f >> n;

    int x;
    for (int i = 0; i < n; i++)
        if (f >> x)
            nr_hosts.push_back(x);

    return subnetNetwork(InternetAddress(ip, mask), nr_hosts);
}

void Util::subnetNetwork (const std::string& inputFilename, const std::string& outputFilename) {
    std::ifstream f(inputFilename);

    // Original network
    IPAddress ip, mask;
    f >> ip >> mask;
    
    // (n) subnetworks each requiring (nr_hosts[i]) host IPs
    int n;
    std::vector<int> nr_hosts;

    f >> n;

    int x;
    for (int i = 0; i < n; i++)
        if (f >> x)
            nr_hosts.push_back(x);

    subnetNetwork(InternetAddress(ip, mask), nr_hosts, outputFilename);
}

void Util::subnetNetwork (InternetAddress network, std::vector<int> hosts, const std::string& outputFilename) {
    std::vector<InternetAddress> subnetworks;
    subnetworks = subnetNetwork(network, hosts);

    std::ofstream f(outputFilename);

    if (subnetworks.size() == 0) {
        f << "ERROR: Original network cannot be split into this many subnetworks!";
    } else {
        f << "Original network" << std::endl;
        f << network << std::endl;
        f << "--------------------" << std::endl << std::endl;

        for (unsigned int i = 0; i < subnetworks.size(); i++) {
            f << "Subnetwork #" << i + 1 << std::endl;
            f << subnetworks[i] << std::endl;
        }
    }
}