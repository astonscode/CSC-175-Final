#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;
/*
class User
{
public:
   string name;
   int money;
   void pushTo(vector<User> &uv)
   {
      uv.push_back(*this);
   }
   User(string n, int m)
   {
      name = n;
      money = m;
   }
   User()
   {
      name = "Player";
      money = 0;
   }
};

vector<User> load(const string &filename)
{
   vector<User> users;
   ifstream file(filename);
   string l;
   while (getline(file, l))
   {
      stringstream ss(l);
      string i, n, d, ds;
      ss >> i >> n >> d >> ds;
      ds.erase(0, 1); // THAT DAMN DOLLAR SIGN GAHHH
      int m = stoi(ds);

      users.push_back(User(n, m));
   }

   return users;
}

void save(const string &f, const vector<User> &users)
{
   ofstream file(f, ios::trunc);
   int rank = 1;

   for (const User &u : users)
   {
      file << rank << ". " << u.name << " - $" << u.money << "\n";
      rank++;
   }
}

void create(int m)
{
   string u;
   cout << "Username: ";
   cin >> u;
   // m is money

   User user(u, m);
}
int main()
{
   string filename = "sv.txt";
   vector<User> users = load(filename);

   string uName;
   cout << "username:\t";
   cin >> uName;

   bool found = false;
   for (User &u : users)
   {
      if (u.name == uName)
      {
         if (dnr > u.money)
         {
            u.money = dnr;
         }
         found = true;
         break;
      }
   }

   if (!found)
   {
      users.push_back(User(uName, dnr));
   }

   sort(users.begin(), users.end(), [](const User &a, const User &b)
        { return a.money > b.money; });

   save(filename, users);

   cout << "Updated.";

   return 0;
}
*/
struct user
{
   string name;
   int money;
};
