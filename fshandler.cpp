#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>

#include "tracker.h"
#include "fshandler.h"

using namespace std;

vector<User> loadUsers()
{
   vector<User> u;
   ifstream file("sv.txt");
   string l;

   while (getline(file, l))
   {
      stringstream ss(l);
      string rank, name, dash, money;
      ss >> rank >> name >> dash >> money;
      money.erase(0, 1);
      int m = stoi(money);
      u.push_back({name, m});
   }

   return u;
}

void saveUsers(vector<User> &users)
{
   ofstream file("sv.txt", ios::trunc);
   int r = 1;
   for (auto &u : users)
   {
      file << r << ". " << u.name << " - $" << u.money << "\n";
      r++;
   }
}

void updateUser(vector<User> &users, string &name, int amt)
{
   bool f = false; // find
   for (auto &u : users)
   {
      if (u.name == name)
      {
         u.money = amt;
         f = true;
         break;
      }
   }

   if (!f)
   {
      users.push_back({name, amt});
   }
}

void sortUsers(vector<User> &users)
{
   sort(users.begin(), users.end(), [](User &a, User &b)
        { return a.money > b.money; });
}
