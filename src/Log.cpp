#include "Log.h"
using namespace std;
std::string Log::getCurrentTime() {
        time_t timep;
        std::stringstream ss;
        std::string out;
        struct tm *p;
        time(&timep); /*获得time_t结构的时间，UTC时间*/
        p = localtime(&timep); /*转换为struct tm结构的当地时间*/
        ss << 1900 + p->tm_year << "-" << 1 + p->tm_mon << "-" << p->tm_mday << "/" << p->tm_hour << ":" << p->tm_min << ":" << p->tm_sec;
        ss >> out;
        return out;
}

void Log::writetofile(std::string type, std::string user, bool status) {
        std::ofstream out;

        out.open("Log.data",ios::app);
        if (type == "Start Agenda")
        out << "-----------------------------------------------------------------------------------------------------------\n";
        if (type == "Writing data to file")
        out << "\n\n";
        out << "Time: ";
        out << left << setw(18) << Log::getCurrentTime();
        out << "  Operation: ";
        out << left << setw(31) << type;
        out << "User:";
        out << left << setw(12) << user;
        out << "Status: ";
        if (status)
            out << "Succeed";
        else
            out << "Fail";
        out << "\n";
        if (type == "Reading agenda data")
            out << "\n";
        if (type == "Quit Agenda")
            out << "-----------------------------------------------------------------------------------------------------------\n";

        out.close();
}

Log::Log() {
}

