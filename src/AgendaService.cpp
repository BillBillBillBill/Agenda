#include "AgendaService.h"
AgendaService::AgendaService() {
    
}

AgendaService::~AgendaService() {
    
}

bool AgendaService::userLogIn(std::string userName, std::string password) {
    for (auto i = storage_->userList_.begin(); i != storage_->userList_.end(); i++) {
        if ((*i).getName() == userName && (*i).getPassword() == password) {
            return true;
        }
    }
    return false;
}

bool AgendaService::userRegister(std::string userName, std::string password,std::string email, std::string phone) {
    User = new User(userName, password, email, phone);
    storage_->createUser(User);
    return true;
}

bool AgendaService::deleteUser(std::string userName, std::string password) {
    
}
 // a user can only delete itself
std::list<User> AgendaService::listAllUsers(void) {
    
}

bool AgendaService::createMeeting(std::string userName, std::string title, std::string participator, std::string startDate, std::string endDate) {
    
}

std::list<Meeting> AgendaService::meetingQuery(std::string userName, std::string title) {
    
}

std::list<Meeting> AgendaService::meetingQuery(std::string userName, std::string startDate, std::string endDate) {
    
}

std::list<Meeting> AgendaService::listAllMeetings(std::string userName) {
    
}

std::list<Meeting> AgendaService::listAllSponsorMeetings(std::string userName) {
    
}

std::list<Meeting> AgendaService::listAllParticipateMeetings(std::string userName) {
    
}

bool AgendaService::deleteMeeting(std::string userName, std::string title) {
    
}

bool AgendaService::deleteAllMeetings(std::string userName) {
    
}

void AgendaService::startAgenda(void) {
    
}

void AgendaService::quitAgenda(void) {
    
}

