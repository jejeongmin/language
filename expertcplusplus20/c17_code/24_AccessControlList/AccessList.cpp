#include "AccessList.h"

using namespace std;

AccessList::AccessList(initializer_list<string_view> initlist)
{
	mAllowed.insert(begin(initlist), end(initlist));
}

void AccessList::addUser(string_view user)
{
	mAllowed.emplace(user);
}

void AccessList::removeUser(string_view user)
{
	mAllowed.erase(string(user));
}

bool AccessList::isAllowed(string_view user) const
{
	return (mAllowed.count(string(user)) != 0);
}

/*
	오.. 이렇게 하니 좀 간결하고, 세련되어 보이네.
*/
vector<string> AccessList::getAllUsers() const
{
	return { begin(mAllowed), end(mAllowed) };
}
