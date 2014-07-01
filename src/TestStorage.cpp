#include <iostream>
#include "Storage.h"
bool fuc(const Meeting& meeting) {
if (meeting.getParticipator() == "Bill")
return true;
return false;
}


using namespace std;

int main() {
    Storage *ptr = Storage::getInstance();
    Date d1(2005, 3, 15, 20, 33);
    Date d2(2013, 10, 30, 5, 22);
    User u1("Bill", "123456","123456@qq.com","18819473330");
    User u2("weiping", "123456","654321@qq.com","8888888888");
    Meeting meet1("weiping", "Bill", d1, d2, "fu");
    Meeting meet2("weiping", "Bill", d1, d2, "ssssssssss");
    ptr->createMeeting(meet1);
    ptr->createMeeting(meet2);
    ptr->createUser(u1);
    ptr->createUser(u2);
    ptr->deleteMeeting(fuc);
    ptr->sync();
    getchar();
    return 0;
}
