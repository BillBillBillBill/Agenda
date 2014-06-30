#include<iostream>
#include"Storage.h"


using namespace std;

int main() {
    Storage *ptr = Storage::getInstance();
    Date d1(2005, 3, 15, 20, 33);
    Date d2(2013, 10, 30, 5, 22);
	User u1("Bill", "123456","123456@qq.com","18819473330");
    Meeting mee("OK", "dsa", d1, d2, "fu");
    ptr->createMeeting(mee);
	ptr->createUser(u1);
    ptr->sync();
	getchar();
	return 0;
}
