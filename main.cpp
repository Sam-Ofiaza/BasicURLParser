#include <iostream>
#include <string>
#include <regex>

int main(int argc, char** argv) {

    std::cout << "Num arguments: " << argc << "\nFile path name: " << argv[0] << "\nURL entered: " << argv[1] << "\n";

    std::string url = argv[1];
    std::string current;
    bool valid;

    //Protocol check

    std::__cxx11::regex p1("[a-z]+");
    std::__cxx11::smatch f1;
    valid = std::regex_search(url, f1, p1);
    current = f1.str();

    if(!valid)
        std::cout << "Protocol not found.\n";
    else {
        std::__cxx11::regex p2("(https|http|ftp|ftps)");
        if (std::regex_match(current, p2))
            std::cout << "Protocol: " << current << "\n";
        else
            std::cout << "Protocol: " << current << " is not a valid protocol." "\n";
    }

    //Domain check

    std::__cxx11::regex p3("((([[:alnum:]]|-|_)+)\\.(([[:alnum:]]|-|_)+)\\.(([[:alnum:]]|-|_)+))");
    std::__cxx11::smatch f2;
    valid = std::regex_search(url, f2, p3);
    current = f2.str();

    if(!valid)
        std::cout << "Domain not found.\n";
    else {
        std::__cxx11::regex p8("(com|net|edu|biz|gov)");
        std::string suffix(current.end()-3, current.end());
        bool validSuffix = std::regex_match(suffix, p8);
        if (std::regex_match(current, p3) && validSuffix)
            std::cout << "Domain: " << current << "\n";
        else if(!validSuffix)
            std::cout << "Domain: " << suffix << " is not a valid suffix in domain name " << current << "\n";
        else
            std::cout << "Domain: " << current << " is not a valid domain name.\n";
    }

    //Port check (optional)

    std::__cxx11::regex p4(":[[:digit:]]+\\/");
    std::__cxx11::smatch f3;
    valid = std::regex_search(url, f3, p4);
    current = f3.str();

    if(!valid)
        std::cout << "Port not found.\n";
    else {
        current.erase(current.begin());
        current.erase(current.end() - 1);
        int port = std::stoi(current);
        std::__cxx11::regex p5("[[:digit:]]+");
        if (std::regex_match(current, p5) && port >= 1 && port <= 65535)
            std::cout << "Port: " << current << "\n";
        else
            std::cout << "Port: " << port << " is not a valid port (must be between 1 and 65535).\n";
    }

    //File path check

    std::__cxx11::regex p6("\\/(([[:alpha:]]|\\/)+)\\.(html|htm)");
    std::__cxx11::smatch f4;
    valid = std::regex_search(url, f4, p6);
    current = f4.str();

    if(!valid)
        std::cout << "File path not found.\n";
    else {
        if (std::regex_match(current, p6))
            std::cout << "File path: " << current << "\n";
        else
            std::cout << "File path: " <<  current << " is not a valid file path.\n";
    }

    //Parameters check (optional)

    std::__cxx11::regex p7("\\?.+");
    std::__cxx11::smatch f5;
    valid = std::regex_search(url, f5, p7);
    current = f5.str();

    if(!valid)
        std::cout << "Parameter not found.\n";
    else if(std::regex_match(current, p7))
        std::cout << "Parameter: " << current << "\n";
    else
        std::cout << "Parameter: " << current << " is not a valid parameter.\n";

    return 0;
}
