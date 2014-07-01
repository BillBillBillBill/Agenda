#include <iostream>
#include "AgendaService.h"
#include "AgendaUI.h"

AgendaUI::AgendaUI() {
    startAgenda();
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
    
}

void AgendaUI::listAllSponsorMeetings(void) {
    
}

void AgendaUI::listAllParticipateMeetings(void) {
    
}

void AgendaUI::queryMeetingByTitle(void) {
    
}

void AgendaUI::queryMeetingByTimeInterval(void) {
    
}

void AgendaUI::deleteMeetingByTitle(void) {
    
}

void AgendaUI::deleteAllMeetings(void) {
    
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

