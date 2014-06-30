#include <fstream>
#include "Storage.h"
#include <string>
//Storage::DISALLOW_COPY_AND_ASSIGN(Storage storage) {}
Storage::Storage() {
    readFromFile("Agenda.data");
}

    // storage structure with list, or you have better structures e.g. balanced tree
bool Storage::readFromFile(const char *fpath) {
    std::fstream readFile;
    readFile.open(fpath);
    if (!readFile)
        return false;
    std::string tem[500];
    std::string temp;
    int count = 0;
    int countvaild = 0;
    while (getline(readFile, temp, '"')) {
        if (getline(readFile, temp, '"')) {
            if (temp == "User")
            continue;
            if (temp == "Meeting")
                break;
            tem[count] = temp;
            countvaild++;
            count++;
        }
        if (temp.length() == 0) {
            count -= countvaild;
            countvaild = 0;
        }
        if (countvaild == 4)
                countvaild = 0;
    }
    for (int i = 0; i < count; i += 4) {
        User user(tem[i], tem[i+1], tem[i+2], tem[i+3]);
        userList_.push_back(user);
    }
    count = 0;
    countvaild = 0;
    while (getline(readFile, temp, '"')) {
        if (getline(readFile, temp, '"')) {
            tem[count] = temp;
            countvaild++;
            count++;
        }
        if (temp.length() == 0) {
            count -= countvaild;
            countvaild = 0;
        }
        if (countvaild == 4)
            countvaild = 0;
    }
    for (int i = 0; i < count; i += 4) {
        Meeting meeting(tem[i], tem[i+1], Date::stringToDate(tem[i+2]), Date::stringToDate(tem[i+3]), tem[i+4]);
        meetingList_.push_back(meeting);
    }
    readFile.close();
    return true;
}

bool Storage::writeToFile(const char *fpath) {
    std::fstream writeFile;
    writeFile.open(fpath);
    if (!writeFile)
        return false;
    writeFile << "{collection:\"User\",total:" << userList_.size() << "}\n";
    for (auto i = userList_.begin(); i != userList_.end(); i++) {
        writeFile << "{name:\"" << i->getName() << "\"" << ",password:\""
        << i->getPassword() << "\",email:\"" << i->getEmail()
        << "\",phone:\"" << i->getPhone() << "\"}\n";
    }
    writeFile << "{collection:\"Meeting\",total:" << meetingList_.size() << "}\n";
    for (auto i = meetingList_.begin(); i != meetingList_.end(); i++) {
        writeFile << "{sponsor:\"" << i->getSponsor() << "\"" << ",participator:\""
        << i->getParticipator() << "\",sdate:\"" << Date::dateToString(i->getStartDate()) << "\",edate:\""
        <<Date::dateToString(i->getEndDate()) << "\",title:\"" << i->getTitle() << "\"}\n";
    }
    writeFile.close();
    return true;
}

Storage* Storage::instance_ = NULL;

Storage* Storage::getInstance(void) {
    if (instance_ == NULL)
        instance_ = new Storage;
    return instance_;
}

Storage::~Storage() {
    sync();
    delete instance_;
}

	// CRUD for User & Meeting using C++11 Function Template and Lambda Expressions
void Storage::createUser(const User& user) {
    userList_.push_back(user);
}

std::list<User> Storage::queryUser(std::function<bool(const User&)> filter) {
    std::list<User> FoundedUser;
    for (auto i = userList_.begin(); i != userList_.end(); i++) {
        if (filter(*i)) {
            FoundedUser.push_back(*i);
        }
    }
    return FoundedUser;
}
// return found users
int Storage::updateUser(std::function<bool(const User&)> filter, std::function<void(User&)> switcher) {
    int count = 0;
    for (auto i = userList_.begin(); i != userList_.end(); i++) {
        if (filter(*i)) {
            switcher(*i);
            count++;
        }
    }
    return count;
}
// return the number of updated users
int Storage::deleteUser(std::function<bool(const User&)> filter) {
    int count = 0;
    for (auto i = userList_.begin(); i != userList_.end(); i++) {
        if (filter(*i)) {
            userList_.erase(i);
            count++;
        }
    }
    return count;
}
// return the number of deleted users
void Storage::createMeeting(const Meeting& meeting) {
    meetingList_.push_back(meeting);
}

std::list<Meeting> Storage::queryMeeting(std::function<bool(const Meeting&)> filter) {
    std::list<Meeting> FoundedMeeting;
    for (auto i = meetingList_.begin(); i != meetingList_.end(); i++) {
        if (filter(*i)) {
            FoundedMeeting.push_back(*i);
        }
    }
    return FoundedMeeting;
}
// return found meetings
int Storage::updateMeeting(std::function<bool(const Meeting&)> filter, std::function<void(Meeting&)> switcher) {
    int count = 0;
    for (auto i = meetingList_.begin(); i != meetingList_.end(); i++) {
        if (filter(*i)) {
            switcher(*i);
            count++;
        }
    }
    return count;
}
// return the number of updated meetings
int Storage::deleteMeeting(std::function<bool(const Meeting&)> filter) {
    int count = 0;
    for (auto i = meetingList_.begin(); i != meetingList_.end(); i++) {
        if (filter(*i)) {
            meetingList_.erase(i);
            count++;
        }
    }
    return count;
}
// return the number of deleted meetings
// File IO
bool Storage::sync(void) {
    return writeToFile("Agenda.data");
}

