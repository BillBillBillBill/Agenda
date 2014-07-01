#include "AgendaService.h"


AgendaUI::AgendaUI() {
    startAgenda();
}

void AgendaUI::OperationLoop(void) {
    
}



void AgendaUI::startAgenda(void) {
    agendaService_.startAgenda();
    userName_ = NULL;
    userPassword_ = NULL;
}

std::string AgendaUI::getOperation() {
    
}

bool AgendaUI::executeOperation(std::string op) {
    
}

void AgendaUI::userLogIn(void) {
    std::cout << "Login\n";
    std::cout << "UserName:\n";
    std::cin >> userName_;
    std::cout << "Password:\n";
    std::cin >> userPassword_;

}

void AgendaUI::userRegister(void) {
    std::cout << "Register\n";
    std::cout << "UserName:\n";
    std::cout << "Password:\n";
    std::cout << "Emali:\n";
    std::cout << "Phone:\n";
}

void AgendaUI::quitAgenda(void) {
    agendaService_.();
    userName_ = NULL;
    userPassword_ = NULL;
}

void AgendaUI::userLogOut(void) {
    if ()
        std::cout << "Log out succeed!!\n";
    else
        std::cout << "Log out fail!!\n";
}

void AgendaUI::deleteUser(void) {
    
}

void AgendaUI::listAllUsers(void) {
    
}

void AgendaUI::createMeeting(void) {
    
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
    std::cout << "Meetings:\n";
    std::list<Meeting> 
    for()
}

    // dates
std::string userName_;
std::string userPassword_;
AgendaService agendaService_;
};
