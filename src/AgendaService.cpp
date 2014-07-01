#include "AgendaService.h"
#include <string>
#include <iostream>
std::string NAME;
std::string TITLE;  //also as password
Date SD;
Date ED;
bool queryMeetingsByUser(const Meeting& meeting) {
    if (NAME == meeting.getParticipator() ||
        NAME == meeting.getSponsor())
        return true;
    return false;
}

bool queryMeetingsByParticipator(const Meeting& meeting) {
    if (NAME == meeting.getParticipator())
        return true;
    return false;
}

bool queryMeetingsBySponsor(const Meeting& meeting) {
    if (NAME == meeting.getSponsor())
        return true;
    return false;
}

bool queryMeetingsByNameTime(const Meeting& meeting) {
    if ((NAME == meeting.getParticipator() ||
    NAME == meeting.getSponsor()) && SD == meeting.getStartDate()
    && ED == meeting.getEndDate())
        return true;
    return false;
}

bool queryMeetingByNameTitle(const Meeting& meeting) {
    if ((NAME == meeting.getParticipator() ||
    NAME == meeting.getSponsor()) && TITLE == meeting.getTitle())
        return true;
    return false;
}

bool queryUserByName(const User& user) {
    return (NAME == user.getName());
}

bool queryUserALL(const User& user) {
    return true;
}

bool queryMeetingALL(const Meeting& meeting) {
    return true;
}

bool CheckUserValid(const User& user) {
    return (user.getPassword() == TITLE && user.getName() == NAME);
}


AgendaService::AgendaService() {
    startAgenda();
}

AgendaService::~AgendaService() {
    quitAgenda();
}

bool AgendaService::userLogIn(std::string userName, std::string password) {
    TITLE = password;
    NAME = userName;
    if ((storage_->queryUser(CheckUserValid)).size() > 0) {
        std::cout << "Welcome !!" << userName << "\n";
        return true;}
    std::cout <<  "Fail to Login!\n";
    return false;
}

bool AgendaService::userRegister(std::string userName, std::string password,std::string email, std::string phone) {
    storage_->createUser(User(userName, password, email, phone));
    std::cout <<  "Register a user!\n";
    return true;
}

bool AgendaService::deleteUser(std::string userName, std::string password) {
    int count = 0;
    TITLE = password;
    NAME = userName;
    count = storage_->deleteUser(CheckUserValid);
    if (count != 0)
        storage_->deleteMeeting(queryMeetingsByUser);
    return true;
}
 // a user can only delete itself
std::list<User> AgendaService::listAllUsers(void) {
    return storage_->queryUser(queryUserALL);
}

bool AgendaService::createMeeting(std::string userName, std::string title, std::string participator, std::string startDate, std::string endDate) {
    storage_->createMeeting(Meeting(userName, participator,
Date::stringToDate(startDate), Date::stringToDate(endDate), title));
    return true;
}

std::list<Meeting> AgendaService::meetingQuery(std::string userName, std::string title) {
    NAME = userName;
    TITLE = title;
    return storage_->queryMeeting(queryMeetingByNameTitle);
}

std::list<Meeting> AgendaService::meetingQuery(std::string userName, std::string startDate, std::string endDate) {
    NAME = userName;
    SD = Date::stringToDate(startDate);
    ED = Date::stringToDate(endDate);
    return storage_->queryMeeting(queryMeetingsByNameTime);
}

std::list<Meeting> AgendaService::listAllMeetings(std::string userName) {
    NAME = userName;
    return storage_->queryMeeting(queryMeetingsByUser);
}

std::list<Meeting> AgendaService::listAllSponsorMeetings(std::string userName) {
    NAME = userName;
    return storage_->queryMeeting(queryMeetingsBySponsor);
}

std::list<Meeting> AgendaService::listAllParticipateMeetings(std::string userName) {
    NAME = userName;
    return storage_->queryMeeting(queryMeetingsByParticipator);
}

bool AgendaService::deleteMeeting(std::string userName, std::string title) {
    NAME = userName;
    TITLE = title;
    return storage_->deleteMeeting(queryMeetingByNameTitle);
}

bool AgendaService::deleteAllMeetings(std::string userName) {
    NAME = userName;
    return storage_->deleteMeeting(queryMeetingsByUser);
}

void AgendaService::startAgenda(void) {
    std::cout << "Now start AgendaService..\n";
    storage_ = Storage::getInstance();
}

void AgendaService::quitAgenda(void) {
    std::cout << "Now quit AgendaService..\n";
    storage_->sync();
}

