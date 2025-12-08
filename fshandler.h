#ifndef FSHANDLER_H
#define FSHANDLER_H

#include <string>
#include <vector>

using namespace std;

struct User
{
   string name;
   int money;
};

vector<User> loadUsers();
void saveUsers(vector<User> &users);
void updateUser(vector<User> &users, string &name, int amt);
void sortUsers(vector<User> &users);

#endif
