
#include <iostream>
#include <cstdlib>

int main() {
    std::cout << "CPU Scheduling Simulator" << std::endl;
    std::cout << "========================" << std::endl;
    std::cout << "1. Shortest Job First (SJF)" << std::endl;
    std::cout << "2. Round Robin (RR)" << std::endl;
    std::cout << "Choose an algorithm (1-2): ";
    
    int choice;
    std::cin >> choice;
    
    if (choice == 1) {
        int result = system("./SJF");
        if (result != 0) {
            std::cout << "Error executing SJF program." << std::endl;
        }
    } else if (choice == 2) {
        int result = system("./RR");
        if (result != 0) {
            std::cout << "Error executing RR program." << std::endl;
        }
    } else {
        std::cout << "Invalid choice. Exiting." << std::endl;
        return 1;
    }
    
    return 0;
}
