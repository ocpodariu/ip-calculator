#include "IPAddress.h"
#include "InternetAddress.h"
#include "Util.h"

#include <iostream>
#include <fstream>

int main () {
    // Indicates whether the program should exit
    bool exit = false;

    std::string option;

    std::cout << "IP Calculator v1.0" << std::endl;
    
    while (!exit) {
        std::cout << std::endl << ">> ";
        std::cin >> option; std::cin.ignore();

        if (option == "identify") {
            IPAddress ip, mask;

            std::cout << "Enter IP address:  "; std::cin >> ip;
            std::cout << "Enter subnet mask: "; std::cin >> mask;

            switch (Util::identifyAddress(InternetAddress(ip, mask))) {
                case 0: std::cout << "This is a network address." << std::endl; break;
                case 1: std::cout << "This is a broadcast address." << std::endl; break;
                case 2: std::cout << "This is a host address." << std::endl; break;
            }
        } else if (option == "subnet") {
            int input_mode, output_mode;

            std::cout << "Choose input mode (0 - keyboard; 1 - file): ";
            std::cin >> input_mode; std::cin.ignore();

            std::cout << "Choose output mode (0 - console; 1 - file): ";
            std::cin >> output_mode; std::cin.ignore();

            if (input_mode) { // File input
                std::string input_filename;

                std::cout << "Enter input filename: ";
                std::cin >> input_filename; std::cin.ignore();

                if (output_mode) { // File input + File output
                    std::string output_filename;
                    std::cout << "Enter output filename: ";
                    std::cin >> output_filename; std::cin.ignore();

                    Util::subnetNetwork(input_filename, output_filename);
                } else { // File input + Console output
                    std::vector<InternetAddress> subnetworks;
                    subnetworks = Util::subnetNetwork(input_filename);

                    if (subnetworks.size() == 0) {
                        std::cout << "Invalid input!" << std::endl;
                        std::cout << "Original network cannot be split into this many subnetworks." << std::endl;
                    } else {
                        std::cout << std::endl;
                        
                        for (unsigned int i = 0; i < subnetworks.size(); i++) {
                            std::cout << "Subnetwork #" << (i + 1) << std::endl;
                            std::cout << subnetworks[i] << std::endl;
                        }
                    }
                }
            } else { // Keyboard input
                IPAddress ip, mask;
                int nr_subnetworks;
                std::vector<int> nr_hosts;

                std::cout << std::endl;
                std::cout << "Enter original network details:" << std::endl;
                std::cout << " - IP address:  "; std::cin >> ip;
                std::cout << " - Subnet mask: "; std::cin >> mask;

                std::cout << std::endl;
                std::cout << "Enter number of subnetworks: "; std::cin >> nr_subnetworks;
                nr_hosts.resize(nr_subnetworks);

                std::cout << std::endl;
                std::cout << "Enter number of host IPs required by each subnetwork:" << std::endl;
                for (int i = 0; i < nr_subnetworks; i++) {
                    std::cout << " - subnetwork " << (i + 1) << ": ";
                    std::cin >> nr_hosts[i];
                }

                if (output_mode) { // Keyboard input + File output
                    std::string output_filename;
                    std::cout << "Enter output filename: ";
                    std::cin >> output_filename; std::cin.ignore();

                    Util::subnetNetwork(InternetAddress(ip, mask), nr_hosts, output_filename);
                } else { // Keyboard input + Console output
                    std::vector<InternetAddress> subnetworks;
                    subnetworks = Util::subnetNetwork(InternetAddress(ip, mask), nr_hosts);

                    if (subnetworks.size() == 0) {
                        std::cout << "Invalid input!" << std::endl;
                        std::cout << "Original network cannot be split into this many subnetworks." << std::endl;
                    } else {
                        std::cout << std::endl;
                        std::cout << "Original network" << std::endl;
                        std::cout << InternetAddress(ip, mask) << std::endl;
                        std::cout << "--------------------" << std::endl << std::endl;

                        for (unsigned int i = 0; i < subnetworks.size(); i++) {
                            std::cout << "Subnetwork #" << (i + 1) << std::endl;
                            std::cout << subnetworks[i] << std::endl;
                        }
                    }
                }
            }
        } else if (option == "exit") {
            std::cout << "Exiting..." << std::endl;
            exit = true;
        } else {
            std::cout << "Invalid option. Try again..." << std::endl;
        }
    }

    return 0;
}