#include "AgendaService.h"
#include <string>
#include <iostream>
std::string NAME;
std::string TITLE;  //also as password
std::string NP;
std::string N;
std::string E;
std::string PHONE;
Date SD;
Date ED;
bool queryMeetingsByUser(const Meeting& meeting) {
    if (NAME == "admin")
        return true;
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
    if (NAME == "admin")
        return true;
    if (NAME == meeting.getSponsor())
        return true;
    return false;
}

bool queryMeetingsBySponsorTitle(const Meeting& meeting) {
    if (NAME == "admin" && TITLE == meeting.getTitle())
        return true;
    if (NAME == meeting.getSponsor() && TITLE == meeting.getTitle())
        return true;
    return false;
}

bool queryMeetingsByNameTime(const Meeting& meeting) {
    if (NAME == "admin" && 
       (((meeting.getStartDate() <= SD && meeting.getEndDate() >= SD) || (meeting.getEndDate() >= ED && meeting.getStartDate() <= ED))
 || (SD >= meeting.getStartDate() && meeting.getEndDate() >= ED)
 || (SD <= meeting.getStartDate() && meeting.getEndDate() <= ED)))
        return true;
    if ((NAME == meeting.getParticipator() || NAME == meeting.getSponsor()) && 
       (((meeting.getStartDate() <= SD && meeting.getEndDate() >= SD) || (meeting.getEndDate() >= ED && meeting.getStartDate() <= ED))
 || (SD >= meeting.getStartDate() && meeting.getEndDate() >= ED)
 || (SD <= meeting.getStartDate() && meeting.getEndDate() <= ED)))
        return true;
    return false;
}

bool queryMeetingByNameTitle(const Meeting& meeting) {
    if (NAME == "admin" && TITLE == meeting.getTitle())
        return true;
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
    if (N == "admin" && TITLE == "admin" && user.getName() == NAME)
    return true;
    return (user.getPassword() == TITLE && user.getName() == NAME);
}

bool FindUser(const User& user) {
return (user.getName() == NAME);
}


void changefile(User& user) {
user.setPassword(NP);
user.setPhone(PHONE);
user.setEmail(E);
}




AgendaService::AgendaService() {
    startAgenda();
}

AgendaService::~AgendaService() {
    quitAgenda();
    if (storage_)
    delete storage_;
}

bool AgendaService::changeuserfile(std::string userName, std::string password, std::string name , std::string newpassword ,std::string email, std::string phone) {
    
    TITLE = password;
    NAME = name;
    N = userName;
    NP = newpassword;
    E = email;
    PHONE = phone;
if (storage_->updateUser(CheckUserValid, changefile))
return true;
return false;
}




bool AgendaService::userLogIn(std::string userName, std::string password) {
    TITLE = password;
    NAME = userName;
    if ((storage_->queryUser(CheckUserValid)).size() > 0) {
        return true;}
    return false;
}

bool AgendaService::userRegister(std::string userName, std::string password,std::string email, std::string phone) {
/*        if (userName == "") {
        std::cout << "[register] You must input the Name.Fail to register!!\n";
        return false;
    }
    if (password == "") {
        std::cout << "[register] You must input the Password.Fail to register!!\n";
        return false;
    }
    if (email == "") {
        std::cout << "[register] You must input the Email.Fail to register!!\n";
        return false;
    }
    if (phone == "") {
        std::cout << "[register] You must input the Phone.Fail to register!!\n";
        return false;
    }*/
    std::list<User> l = listAllUsers();
    for (std::list<User>::iterator i = l.begin(); i != l.end(); i++) {
            if (i->getName() == userName) {
                //std::cout << "[register] The name has been used.\n";
                return false;
            }
    }
    
    storage_->createUser(User(userName, password, email, phone));
    return true;
}

bool AgendaService::deleteUser(std::string userName, std::string password) {
    int count = 0;
    TITLE = password;
    NAME = userName;
    count = storage_->deleteUser(CheckUserValid);
    if (count != 0) {
        storage_->deleteMeeting(queryMeetingsByUser);
        return true;
        } else {
        return false;
        }
}
 // a user can only delete itself
bool AgendaService::deleteUser(std::string userName) {
    int count = 0;
    NAME = userName;
    count = storage_->deleteUser(FindUser);
    if (count != 0) {
        storage_->deleteMeeting(queryMeetingsByUser);
        return true;
        } else {
        return false;
        }
}




std::list<User> AgendaService::listAllUsers(void) {
    return storage_->queryUser(queryUserALL);
}

bool AgendaService::createMeeting(std::string userName, std::string title, std::string participator, std::string startDate, std::string endDate) {
    std::list<User> a = listAllUsers();
    bool flag = false;
    for (std::list<User>::iterator i = a.begin(); i != a.end(); i++) {
            if (i->getName() == participator)
             flag = true;
    } //participator exist or not
    std::list<Meeting> b = listAllMeetings(userName);
    std::list<Meeting> c = listAllMeetings(participator);
    for (std::list<Meeting>::iterator i = b.begin(); i != b.end(); i++) {
            if (((i->getStartDate() <= Date::stringToDate(startDate) && i->getEndDate() > Date::stringToDate(startDate)) || (i->getEndDate() >= Date::stringToDate(endDate) && i->getStartDate() < Date::stringToDate(endDate))) || (Date::stringToDate(startDate) >= i->getStartDate() && i->getEndDate() >= Date::stringToDate(endDate)) || (Date::stringToDate(startDate) <= i->getStartDate() && i->getEndDate() <= Date::stringToDate(endDate))  || i->getTitle() == title)
            return false;//exist meeting
    }
    for (std::list<Meeting>::iterator i = c.begin(); i != c.end(); i++) {
           if (((i->getStartDate() <= Date::stringToDate(startDate) && i->getEndDate() > Date::stringToDate(startDate)) || (i->getEndDate() >= Date::stringToDate(endDate) && i->getStartDate() < Date::stringToDate(endDate))) || (Date::stringToDate(startDate) >= i->getStartDate() && i->getEndDate() >= Date::stringToDate(endDate)) || (Date::stringToDate(startDate) <= i->getStartDate() && i->getEndDate() <= Date::stringToDate(endDate))  || i->getTitle() == title)
            return false;//exist meeting
    }
    
    if (flag && Date::isValid(Date::stringToDate(startDate)) && Date::isValid(Date::stringToDate(endDate))) {
    if (Date::stringToDate(endDate) <= Date::stringToDate(startDate))
    return false;
    storage_->createMeeting(Meeting(userName, participator,
Date::stringToDate(startDate), Date::stringToDate(endDate), title));
    return true;
    } else {
    return false;
    }
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
    return storage_->deleteMeeting(queryMeetingsBySponsorTitle);
}

bool AgendaService::deleteAllMeetings(std::string userName) {
    NAME = userName;
    return storage_->deleteMeeting(queryMeetingsBySponsor);
}

void AgendaService::startAgenda(void) {
    storage_ = Storage::getInstance();
}

void AgendaService::quitAgenda(void) {
    storage_->sync();
}

