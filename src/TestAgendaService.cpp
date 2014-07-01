#include <iostream>
#include "Storage.h"
#include "AgendaService.h"
bool fuc(const Meeting& meeting) {
if (meeting.getParticipator() == "Bill")
return true;
return false;
}


using namespace std;

int main() {
    AgendaService agenda;
    Storage *ptr = Storage::getInstance();
    agenda.userLogIn("fuck","aaa");
    agenda.userRegister("huangweiping", "caonima","xxx","333");
    agenda.userRegister("weiping2", "caonima","xxx","333");
    agenda.userRegister("Bill", "123456","123456@qq.com","18819473330");
    agenda.userRegister("weiping", "123456","654321@qq.com","8888888888");
    agenda.userLogIn("huangweiping","aaa");
    agenda.userLogIn("huangweiping","caonima");
    Date d1(2005, 3, 15, 20, 33);
    Date d2(2013, 10, 30, 5, 22);
    agenda.createMeeting("huangweiping","fuccccc", "SB","2014-06-01/12:00","2014-06-05/12:00"
);
    agenda.createMeeting("weiping", "fu", "Bill", "2014-06-01/12:00","2014-06-05/12:00");
    agenda.createMeeting("weiping", "ssssssssss", "Bill", "2014-06-01/12:00","2014-06-05/12:00");
    //agenda.deleteMeeting("Bill","fu");
    //agenda.deleteAllMeetings("weiping");
    list<Meeting> a = agenda.listAllSponsorMeetings("weiping");
    for (list<Meeting>::iterator i = a.begin(); i != a.end(); i++) {
        cout << "Sponsor:" << (*i).getSponsor() << "  Title:" << (*i).getTitle() << endl;
    }
    list<User> b = agenda.listAllUsers();
    for (list<User>::iterator i = b.begin(); i != b.end(); i++) {
        cout << "User:" << (*i).getName() << "  Password:" << (*i).getPassword() << endl;
    }
    getchar();
    return 0;
}
