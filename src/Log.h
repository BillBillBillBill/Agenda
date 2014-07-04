#include <time.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

class Log {
    public:
    Log();
    static std::string getCurrentTime();
    static void writetofile(std::string type, std::string user, bool status);

};
