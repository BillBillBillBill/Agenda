#include <iostream>
#include "AgendaService.h"
#include "AgendaUI.h"

AgendaUI::AgendaUI() {
    startAgenda();
}

AgendaUI::~AgendaUI() {
    quitAgenda();
}

void AgendaUI::OperationLoop(void) {
    while (true) {
        std::string op;
        std::cout << getOperation();
        std::cin >> op;
        if (!executeOperation(op)) {
            std::cout << "Input wrong, Please try again\n";
        }
        if (op == "-q") {
            std::cout << "Thank you for use\n";
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
    ret += "Welcome to Agenda!\n";
    if (agendaService_.userLogIn(userName_, userPassword_)) {
        ret += "Hello! ";
        ret += userName_;
        ret += ", What do you want to do?\n";
        ret += "-del        Delete User\n";
        ret += "-lau        List All Users\n";
        ret += "-cm         Create A Meeting\n";
        ret += "-lam        List All Meetings\n";
        ret += "-lsam       List All Sponsor Meetings\n";
        ret += "-lpam       List All Participate Meetings\n";
        ret += "-qmbt       Query Meeting By Title\n";
        ret += "-qmbti       Query Meeting By Time Interval\n";
        ret += "-dmbt       Delete Meeting By Title\n";
        ret += "-dm         Delete All Meetings\n";
        ret += "-o          Logout\n";
        ret += "-q          Quit Agenda\n\n";
    } else {
        ret += "You haven't sign in, you can:\n";
        ret += "-r          User Register\n";
        ret += "-l          Login\n";
        ret += "-q          Quit Agenda\n";
    }
    return ret;
}

bool AgendaUI::executeOperation(std::string op) {
        if (agendaService_.userLogIn(userName_, userPassword_)) {
            if (op == "-del") {
                deleteUser();
                return true;
            }
            else if (op == "-lau") {
                listAllUsers();
                return true;
            }
            else if (op == "cm") {
                createMeeting();
                return true;
            }
            else if (op == "-lam") {
                listAllMeetings();
                return true;
            }
            else if (op == "-lsam") {
                listAllSponsorMeetings();
                return true;
            }
            else if (op == "-lpam") {
                listAllParticipateMeetings();
                return true;
            }
            else if (op == "-qmbt") {
                queryMeetingByTitle();
                return true;
            }
            else if (op == "-qmbti") {
                queryMeetingByTimeInterval();
                return true;
            }
            else if (op == "-dmbt") {
                deleteMeetingByTitle();
                return true;
            }
            else if (op == "-dmbt") {
                deleteMeetingByTitle();
                return true;
            }
            else if (op == "-dm") {
                deleteAllMeetings();
                return true;
            }
            else if (op == "-o") {
                userLogOut();
                return true;
            }
            else if (op == "-q") {
                quitAgenda();
                return true;
            }
            else {
                return false;
            }
        } else {
        if ( op == "-r") {
            userRegister();
            return true;
            }
        else if (op == "-l") {
            userLogIn();
            return true;
            }
        else if (op == "-q") {
            quitAgenda();
            return true;
            }
        else {
            return false;
            }
        }
}

void AgendaUI::userLogIn(void) {
    std::cout << "Login...\n";
    std::cout << "UserName:\n";
    std::cin >> userName_;
    std::cout << "Password:\n";
    std::cin >> userPassword_;
    if (agendaService_.userLogIn(userName_, userPassword_))
        std::cout << "Login succeed!!\n";
    else
        std::cout << "Login fail!!\n";
}

void AgendaUI::userRegister(void) {
    std::string name, password, email, phone;
    std::cout << "Registing....\n";

    std::cout << "UserName:\n";

    std::cout << "Password:\n";

    std::cout << "Emali:\n";

    std::cout << "Phone:\n";
    if (agendaService_.userRegister(name, password, email, phone))
        std::cout << "Succeed to register!!\n";
    else
        std::cout << "Fail to register!!\n";
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
        std::cout << "Delete User succeed!!\n";
    else
        std::cout << "Delete User fail!!\n";
    userLogOut();
}

void AgendaUI::listAllUsers(void) {
    std::cout << "List All Users\n";
    std::list<User> listtoprint;
    std::list<User> oringin = agendaService_.listAllUsers();
    for (std::list<User>::iterator i = oringin.begin(); i != oringin.end(); i++) {
        std::cout << "Name:  " << i->getName();
        std::cout << "Email:  " << i->getEmail();
        std::cout << "Phone:  " << i->getPhone();
        std::cout << "\n";
    }
}

void AgendaUI::createMeeting(void) {
    std::string Sponsor, participator, title, starttime, endtime;
    std::cout << "Creating Meeting.....\n";
    std::cout << "Please input the Sponsor:\n";
    std::cin >> Sponsor;
    std::cout << "Please input the participator:\n";
    std::cin >> participator;
    std::cout << "Please input the title:\n";
    std::cin >> title;
    std::cout << "Please input start time:<yyyy-mm-dd/hh:mm>\n";
    std::cin >> starttime;
    std::cout << "Please input end time:<yyyy-mm-dd/hh:mm>\n";
    std::cin >> endtime;
    if (agendaService_.createMeeting(Sponsor, title, participator, starttime, endtime))
        std::cout << "Create Meeting Succeed\n";
    else
        std::cout << "Create Meeting Fail!\n";
}

void AgendaUI::listAllMeetings(void) {
    std::cout << "List All Meetings\n";
    std::list<Meeting> listtoprint;
    std::list<Meeting> oringin = agendaService_.listAllMeetings(userName_);
    for (std::list<Meeting>::iterator i = oringin.begin(); i != oringin.end(); i++) {
        listtoprint.push_back(*i);
    }
    printMeetings(listtoprint);
}

void AgendaUI::listAllSponsorMeetings(void) {
    std::cout << "List All Sponsor Meetings\n";
    std::list<Meeting> listtoprint;
    std::list<Meeting> oringin = agendaService_.listAllSponsorMeetings(userName_);
    for (std::list<Meeting>::iterator i = oringin.begin(); i != oringin.end(); i++) {
        listtoprint.push_back(*i);
    }
    printMeetings(listtoprint);
}

void AgendaUI::listAllParticipateMeetings(void) {
    std::cout << "List All Participate Meetings\n";
    std::list<Meeting> listtoprint;
    std::list<Meeting> oringin = agendaService_.listAllParticipateMeetings(userName_);
    for (std::list<Meeting>::iterator i = oringin.begin(); i != oringin.end(); i++) {
        listtoprint.push_back(*i);
    }
    printMeetings(listtoprint);
}

void AgendaUI::queryMeetingByTitle(void) {
    std::cout << "Query Meeting By Title\n";
    std::string title;
    std::cout << "Please input the title:";
    std::cin >> title;
    std::list<Meeting> listtoprint;
    std::list<Meeting> oringin = agendaService_.meetingQuery(userName_, title);
    for (std::list<Meeting>::iterator i = oringin.begin(); i != oringin.end(); i++) {
        listtoprint.push_back(*i);
    }
    printMeetings(listtoprint);
}

void AgendaUI::queryMeetingByTimeInterval(void) {
    std::cout << "Query Meeting By Time Interval\n";
    std::string ST, ET;
    std::list<Meeting> listtoprint;
    std::cout << "Please input start time:<yyyy-mm-dd/hh:mm>\n";
    std::cin >> ST;
    std::cout << "Please input end time:<yyyy-mm-dd/hh:mm>\n";
    std::cin >> ET;
    std::list<Meeting> oringin = agendaService_.meetingQuery(userName_, ST, ET);
    for (std::list<Meeting>::iterator i = oringin.begin(); i != oringin.end(); i++) {
        listtoprint.push_back(*i);
    }
    printMeetings(listtoprint);
}

void AgendaUI::deleteMeetingByTitle(void) {
    std::cout << "Delete Meeting By Title\n";
    std::string title;
    std::cout << "Please input the title:";
    std::cin >> title;
    std::list<Meeting> listtoprint;
    ///////////////////////////////////////////////////////////////////////
    for (std::list<Meeting>::iterator i = oringin.begin(); i != oringin.end(); i++) {
        listtoprint.push_back(*i);
    }
    printMeetings(listtoprint);
}

void AgendaUI::deleteAllMeetings(void) {
    std::cout << "Delete All Meetings\n";
    std::list<Meeting> listtoprint;
    /////////////std::list<Meeting> oringin = agendaService_.deleteAllMeetings(userName_);
    for (std::list<Meeting>::iterator i = oringin.begin(); i != oringin.end(); i++) {
        listtoprint.push_back(*i);
    }
    printMeetings(listtoprint);
}

void AgendaUI::printMeetings(std::list<Meeting> meetings) {
    std::cout << "Numbers of Meetings:  " << meetings.size() << "\n";
    std::cout << "Meetings:\n";
    for(std::list<Meeting>::iterator i = meetings.begin() ; i != meetings.end() ; i++) {
        std::cout << "Sponsor: " << i->getSponsor();
        std::cout << "   Participator: " << i->getParticipator();
        std::cout << "   Title: " << i->getTitle();
        std::cout << "\n";
        std::cout << "   Start time: " << Date::dateToString(i->getStartDate());
        std::cout << "   End time: " << Date::dateToString(i->getEndDate());
        std::cout << "\n";
    }
}

