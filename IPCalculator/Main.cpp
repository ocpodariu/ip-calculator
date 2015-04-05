#include "IPAddress.h"
#include "InternetAddress.h"
#include "Util.h"

#include <iostream>
#include <fstream>
#include <iomanip>

void displayHelp ();
void displayLicense ();
void displaySubnetInputFileStructure ();

int main () {
    // Indicates whether the program should exit
    bool exit = false;
    
    std::string option;

    std::cout << "IP Calculator v1.0" << std::endl << std::endl;
    std::cout << "Type \"help\" to display all available options." << std::endl;
    
    while (!exit) {
        std::cout << std::endl << ">> ";
        std::cin >> option; std::cin.ignore();

        if (option == "help") {
            displayHelp();
        } else if (option == "identify") {
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
        } else if (option == "subnet-input") {
            displaySubnetInputFileStructure();
        } else if (option == "license") {
            displayLicense();
        } else if (option == "exit") {
            std::cout << "Exiting..." << std::endl;
            exit = true;
        } else {
            std::cout << "Invalid option. Try again..." << std::endl;
        }
    }

    return 0;
}

void displayHelp () {
    std::cout << std::left;

    std::cout << std::endl;
    std::cout << "\t" << std::setw(16) << "help";
    std::cout << "Display all available options." << std::endl;

    std::cout << std::endl;
    std::cout << "\t" << std::setw(16) << "identify";
    std::cout << "Identify the type of an IP address" << std::endl;
    std::cout << "\t" << std::setw(16) << " ";
    std::cout << "(network / broadcast / host)." << std::endl;

    std::cout << std::endl;
    std::cout << "\t" << std::setw(16) << "license";
    std::cout << "Display license information." << std::endl;

    std::cout << std::endl;
    std::cout << "\t" << std::setw(16) << "subnet";
    std::cout << "Subnet a larger network into multiple" << std::endl;
    std::cout << "\t" << std::setw(16) << " ";
    std::cout << "smaller ones." << std::endl;

    std::cout << std::endl;
    std::cout << "\t" << std::setw(16) << "subnet-input";
    std::cout << "Display the input file structure for" << std::endl;
    std::cout << "\t" << std::setw(16) << " ";
    std::cout << "subnetting." << std::endl;

    std::cout << std::endl;
    std::cout << "\t" << std::setw(16) << "exit";
    std::cout << "Exit the program." << std::endl;

    // Reset stream (deactivate left alignment)
    std::cout << std::internal;
}

void displayLicense () {
    std::cout << "The MIT License (MIT)" << std::endl << std::endl;
    std::cout << "Copyright (c) 2015 PODARIU Ovidiu" << std::endl << std::endl;

    std::cout << "Permission is hereby granted, free of charge, to any person " << std::endl
              << "obtaining a copy of this software and associated documentation " << std::endl
              << "files (the \"Software\"), to deal in the Software without " << std::endl
              << "restriction, including without limitation the rights to use, " << std::endl
              << "copy, modify, merge, publish, distribute, sublicense, and/or " << std::endl
              << "sell copies of the Software, and to permit persons to whom " << std::endl
              << "the Software is furnished to do so, subject to the following " << std::endl
              << "conditions:" << std::endl << std::endl;

    std::cout << "The above copyright notice and this permission notice shall " << std::endl
              << "be included in all copies or substantial portions of the " << std::endl
              << "Software." << std::endl << std::endl;

    std::cout << "THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY " << std::endl
              << "KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE " << std::endl
              << "WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR " << std::endl
              << "PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS " << std::endl
              << "OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR " << std::endl
              << "OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR " << std::endl
              << "OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE " << std::endl
              << "SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE." << std::endl;
}

void displaySubnetInputFileStructure () {
    std::cout << "Structure of the subnet input file:" << std::endl << std::endl;

    std::cout << "\t#" << std::setfill('-') << std::setw(52) << "" << "#" << std::endl;
    std::cout << "\t| " << std::setw(50) << std::setfill(' ') << "" << " |"  << std::endl;

    std::cout << std::setfill(' ') << std::left;
    std::cout << "\t| " << std::setw(50) << "<original-network-ip-address>" << " |" << std::endl;
    std::cout << "\t| " << std::setw(50) << "<original-network-subnet-mask>" << " |" << std::endl;
    std::cout << "\t| " << std::setw(50) << "" << " |"  << std::endl;

    std::cout << "\t| " << std::setw(50) << "<number-of-subnetworks>" << " |" << std::endl;
    std::cout << "\t| " << std::setw(50) << "" << " |"  << std::endl;

    std::cout << "\t| " << std::setw(50) << "<number-of-host-ip's-necessarry-for-subnetwork-1>" <<  " |" << std::endl;
    std::cout << "\t| " << std::setw(50) << "<number-of-host-ip's-necessarry-for-subnetwork-2>" <<  " |" << std::endl;
    std::cout << "\t| " << std::setw(50) << "..." <<  " |" << std::endl;
    std::cout << "\t| " << std::setw(50) << "<number-of-host-ip's-necessarry-for-subnetwork-n>" <<  " |" << std::endl;
    
    std::cout << "\t| " << std::setw(50) << "" << " |"  << std::endl;
    std::cout << "\t#" << std::setfill('-') << std::setw(52) << "" << "#" << std::endl;

    // Reset stream (deactivate left alignment)
    std::cout << std::setfill(' ') << std::internal;
}