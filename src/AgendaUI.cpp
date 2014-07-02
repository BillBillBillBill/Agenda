#include <iostream>
#include <iomanip>
#include "AgendaService.h"
#include "AgendaUI.h"


AgendaUI::AgendaUI() {
    startAgenda();
}



void AgendaUI::OperationLoop(void) {
    while (true) {
        std::string op;
        std::cout << getOperation();
        if (agendaService_.userLogIn(userName_, userPassword_) && userName_ != "" && userPassword_ != "") {
        std::cout << "Agenda@" << userName_ << " ： # ";
        } else {
        std::cout << "Agenda ： ~$ ";}
        std::cin >> op;
        if (!executeOperation(op)) {
            std::cout << "Input wrong, Please try again\n";
        }
        if (op == "q") {
            break;
        }
    }
}



void AgendaUI::startAgenda(void) {
    agendaService_.startAgenda();
    userName_ = "";
    userPassword_ = "";
}

std::string AgendaUI::getOperation() {
    std::string ret = "";
    ret += "\n-----------------------Agenda-----------------------\n";
    if (agendaService_.userLogIn(userName_, userPassword_) && userName_ != "" && userPassword_ != "") {
        ret += "Hello,";
        ret += userName_;
        ret += ", What do you want to do?\n";
        ret += "\nAction :\n";
        ret += "o      -    Log out Agenda\n";
        ret += "dc     -    Delete Agenda Account\n";
        ret += "lu     -    List All Users\n";
        ret += "cm     -    Create A Meeting\n";
        ret += "la     -    List All Meetings\n";
        ret += "las    -    List All Sponsor Meetings\n";
        ret += "lap    -    List All Participate Meetings\n";
        ret += "qm     -    Query Meeting By Title\n";
        ret += "qt     -    Query Meeting By Time Interval\n";
        ret += "dm     -    Delete Meeting By Title\n";
        ret += "da     -    Delete All Meetings\n";

    } else {
        ret += "You haven't sign in\n";
        ret += "Action :\n";
        ret += "l      -    Log in Agenda by user name and password\n";
        ret += "r      -    Register an Agenda account\n";
        ret += "q      -    Quit Agenda\n";
    }
    ret += "----------------------------------------------------\n\n";
    return ret;
}

bool AgendaUI::executeOperation(std::string op) {
        if (agendaService_.userLogIn(userName_, userPassword_) && userName_ != "" && userPassword_ != "") {
            if (op == "dc") {
                deleteUser();
                return true;
            }
            else if (op == "lu") {
                listAllUsers();
                return true;
            }
            else if (op == "cm") {
                createMeeting();
                return true;
            }
            else if (op == "la") {
                listAllMeetings();
                return true;
            }
            else if (op == "las") {
                listAllSponsorMeetings();
                return true;
            }
            else if (op == "lap") {
                listAllParticipateMeetings();
                return true;
            }
            else if (op == "qm") {
                queryMeetingByTitle();
                return true;
            }
            else if (op == "qt") {
                queryMeetingByTimeInterval();
                return true;
            }
            else if (op == "dm") {
                deleteMeetingByTitle();
                return true;
            }
            else if (op == "da") {
                deleteAllMeetings();
                return true;
            }
            else if (op == "o") {
                userLogOut();
                return true;
            }
            else {
                return false;
            }
        } else {
        if ( op == "r") {
            userRegister();
            return true;
            }
        else if (op == "l") {
            userLogIn();
            return true;
            }
        else if (op == "q") {
            quitAgenda();
            return true;
            }
        else {
            return false;
            }
        }
}

void AgendaUI::userLogIn(void) {
    std::cout << "[log in] [user name] [password]\n";
    std::cout << "[log in] ";
    std::cin >> userName_;
    std::cin >> userPassword_;
    if (agendaService_.userLogIn(userName_, userPassword_) && userName_ != "" && userPassword_ != "")
        std::cout << "[log in] succeed!\n";
    else
        std::cout << "[error] log in fail!\n";
}

void AgendaUI::userRegister(void) {
    std::string name, password, email, phone;
    std::cout << "[register] [user name] [password] [email] [phone] \n";
    std::cout << "[register] ";
    std::cin >> name;
    std::cin >> password;
    std::cin >> email;
    std::cin >> phone;
    if (agendaService_.userRegister(name, password, email, phone)){
        std::cout << "[register] succeed!\n";
        userName_ = name;
        userPassword_ = password;
        userLogIn();
        }
    else
        std::cout << "[error] register fail!\n";
}

void AgendaUI::quitAgenda(void) {
    agendaService_.quitAgenda();
    userName_ = "";
    userPassword_ = "";
}

void AgendaUI::userLogOut(void) {
    userName_ = "";
    userPassword_ = "";
}

void AgendaUI::deleteUser(void) {
    if (agendaService_.deleteUser(userName_, userPassword_))
        std::cout << "[delete agenda account] succeed!\n";
    else
        std::cout << "[error] delete agenda account fail!!\n";
    userLogOut();
}

void AgendaUI::listAllUsers(void) {
    std::cout << "[List All Users]\n\n";
    std::list<User> listtoprint;
    std::list<User> oringin = agendaService_.listAllUsers();
    std::cout << std::left <<  std::setw(13) << "Name" << std::left <<  std::setw(20) << "Email"  << std::left <<  std::setw(13) << "Phone";
    std::cout << "\n";
    for (std::list<User>::iterator i = oringin.begin(); i != oringin.end(); i++) {
        std::cout << std::left <<  std::setw(13) << i->getName();
        std::cout << std::left <<  std::setw(20) << i->getEmail();
        std::cout << std::left <<  std::setw(13) << i->getPhone();
        std::cout << "\n";
    }
}

void AgendaUI::createMeeting(void) {
    std::string participator, title, starttime, endtime;
    std::cout << "[create meeting] [title] [participator] [statr time<yyyy-mm-dd/hh:mm>] [end time<yyyy-mm-dd/hh:mm>]\n";
    std::cout << "[create meeting] ";
    std::cin >> title;
    std::cin >> participator;
    std::cin >> starttime;
    std::cin >> endtime;
    if (agendaService_.createMeeting(userName_, title, participator, starttime, endtime))
        std::cout << "[create meeting] succeed!\n";
    else
        std::cout << "[error] create meeting fail!\n";
}

void AgendaUI::listAllMeetings(void) {
    std::cout << "[List All Meetings]\n\n";
    std::list<Meeting> listtoprint;
    std::list<Meeting> oringin = agendaService_.listAllMeetings(userName_);
    for (std::list<Meeting>::iterator i = oringin.begin(); i != oringin.end(); i++) {
        listtoprint.push_back(*i);
    }
    printMeetings(listtoprint);
}

void AgendaUI::listAllSponsorMeetings(void) {
    std::cout << "[List All Sponsor Meetings]\n";
    std::list<Meeting> listtoprint;
    std::list<Meeting> oringin = agendaService_.listAllSponsorMeetings(userName_);
    for (std::list<Meeting>::iterator i = oringin.begin(); i != oringin.end(); i++) {
        listtoprint.push_back(*i);
    }
    printMeetings(listtoprint);
}

void AgendaUI::listAllParticipateMeetings(void) {
    std::cout << "[List All Participate Meetings]\n";
    std::list<Meeting> listtoprint;
    std::list<Meeting> oringin = agendaService_.listAllParticipateMeetings(userName_);
    for (std::list<Meeting>::iterator i = oringin.begin(); i != oringin.end(); i++) {
        listtoprint.push_back(*i);
    }
    printMeetings(listtoprint);
}

void AgendaUI::queryMeetingByTitle(void) {
    std::cout << "[query meeting] [title]\n";
    std::string title;
    std::cout << "[query meeting] ";
    std::cin >> title;
    std::list<Meeting> listtoprint;
    std::list<Meeting> oringin = agendaService_.meetingQuery(userName_, title);
    for (std::list<Meeting>::iterator i = oringin.begin(); i != oringin.end(); i++) {
        listtoprint.push_back(*i);
    }
    printMeetings(listtoprint);
}

void AgendaUI::queryMeetingByTimeInterval(void) {
    std::cout << "[query meetings] [start time<yyyy-mm-dd/hh:mm>] [end time<yyyy-mm-dd/hh:mm>]\n";
    std::cout << "[query meetings] ";
    std::string ST, ET;
    std::list<Meeting> listtoprint;
    std::cin >> ST;
    std::cin >> ET;
    std::list<Meeting> oringin = agendaService_.meetingQuery(userName_, ST, ET);
    for (std::list<Meeting>::iterator i = oringin.begin(); i != oringin.end(); i++) {
        listtoprint.push_back(*i);
    }
    printMeetings(listtoprint);
}

void AgendaUI::deleteMeetingByTitle(void) {
    std::cout << " [delete meeting] [title]\n";
    std::cout << " [delete meeting] ";
    std::string title;
    listAllMeetings();
    std::cin >> title;
    if (agendaService_.deleteMeeting(userName_, title)) {
        std::cout << "[delete meeting by title] succeed!";
        } else {
        std::cout << "[error] delete meeting fail!";
        }
    std::cout << "\n";
}

void AgendaUI::deleteAllMeetings(void) {
    if (agendaService_.deleteAllMeetings(userName_))
        std::cout << "[delete all meetings] succeed!";
    else
        std::cout << "[error] delete meeting fail!";
    std::cout << "\n";
}

void AgendaUI::printMeetings(std::list<Meeting> meetings) {
    std::cout << std::left <<  std::setw(13) << "Title" << std::left <<  std::setw(13) << "Sponsor" << std::left << std::setw(15) << "Participator" << std::left << std::setw(18) << "Start time" << std::left << std::setw(18) << "End time";
    std::cout << "\n";
    for(std::list<Meeting>::iterator i = meetings.begin() ; i != meetings.end() ; i++) {
        std::cout << std::left << std::setw(13) << i->getTitle();
        std::cout << std::left << std::setw(13) << i->getSponsor();
        std::cout << std::left << std::setw(15) << i->getParticipator();
        std::cout << std::left << std::setw(18) << Date::dateToString(i->getStartDate());
        std::cout << std::left << std::setw(18) << Date::dateToString(i->getEndDate());
        std::cout << "\n";
    }
}

