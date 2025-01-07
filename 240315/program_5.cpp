// first time solve this type problem(ban loop, recursive, for_each) without solution
// At first, use any_of, complicated but work well
// At second version, use set_intersection to simpfy the code, it could work with set and vector at same time.
// funny.

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <set>

struct Process
{
    std::string name { };
    std::vector<std::string> resources { };
};

namespace std {
    istream& operator >> (istream& is, Process& process) {
        string resource;
        getline(is, process.name, ':');
        getline(is, resource);
        stringstream ss(resource);
        process.resources = vector<string> { istream_iterator<string>{ ss },
                                                    istream_iterator<string>{ }};
        std::sort(std::begin(process.resources), std::end(process.resources));
        return is;
    }

    ostream& operator << (ostream& os, Process const& process) {
        os << process.name << ": ";
        std::copy(std::begin(process.resources), std::end(process.resources), std::ostream_iterator<std::string> { os, " " });
        return os;
    }
}

int main() {
    std::cout << "Enter resources that are busy:";
    std::set<std::string> busy_res {std::istream_iterator<std::string>{ std::cin },
                                            std::istream_iterator<std::string> { }};

    // for (auto& res: busy_res) {
    //     std::cout << res << '\n';
    // } 

    std::ifstream ifs("/Users/lyon/Desktop/TDDD38/practice/240315/processes.txt");
    std::vector<Process> processes {std::istream_iterator<Process>{ ifs },
                                         std::istream_iterator<Process>{ }};
    processes.erase(std::remove_if(std::begin(processes), std::end(processes), [&busy_res](Process& process) {
        std::vector<std::string> overlep { };
        std::set_intersection(std::begin(process.resources), std::end(process.resources),
                                std::begin(busy_res), std::end(busy_res),
                                std::back_inserter(overlep));
        return overlep.size() > 0;
        // return std::any_of(std::begin(process.resources), std::end(process.resources), [&busy_res](std::string& res) {
        //     return std::any_of(std::begin(busy_res), std::end(busy_res), [&res](BusyResource& busy_res) {
        //         return res == busy_res.busy_resource;
        //     });
        // });
    }), std::end(processes));
    
    std::cout << "Processs that can run unhindered:\n";
    std::copy(std::begin(processes), std::end(processes), std::ostream_iterator<Process>{ std::cout, "\n" });
    
    std::cout << processes.size() << '\n';
}

/* Example 1:

$ ./a.out
Enter resources that are busy: disk <ctrl+D>
Processs that can run unhindered:
Web Browser: network
Print Manager: network printer
Input Handler: keyboard
Image Processing: GPU display
Video Streaming: display network speakers
Print Driver Service: printer
Photo Viewer: display
Scientific Computation Module: GPU
Text Editor: display keyboard
Network Scanning Tool: USB network
Audio Playback: speakers
System Update Service: GPU USB network
Document Conversion Tool: display printer
Graphic Design Software: GPU display
Simulation Engine: GPU
E-Mail Client: network

Example 2:

$ ./a.out 
Enter resources that are busy: network display printer GPU <ctrl+D>
Processs that can run unhindered:
Input Handler: keyboard
File Management Tool: USB disk
Audio Playback: speakers
Disk Cleaning Utility: disk

Example 3:

$ ./a.out 
Enter resources that are busy: USB speakers keyboard <ctrl+D>
Processs that can run unhindered:
Data Analysis Tool: disk network
Web Browser: network
Print Manager: network printer
Image Processing: GPU display
Print Driver Service: printer
Photo Viewer: display
Database Management System: disk network
Scientific Computation Module: GPU
Document Conversion Tool: display printer
Disk Cleaning Utility: disk
Graphic Design Software: GPU display
Simulation Engine: GPU
E-Mail Client: network
*/