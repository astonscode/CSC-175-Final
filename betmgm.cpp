#include <iostream>
#include <vector>
using namespace std;

class BetMGM
{
public:
   // int score =  0;
   vector<double> buyIn;
   double initAmt;
   double amt;
   double current;
   void dis() // display current money
   {
      cout << "\nYour money: $" << amt << endl;
   }
   void bet(double x) // x = bet amount
   {
      // should accept when x > amt and when buyIn[0] > x > buyIn[1]
      while (true)
      {
         if (x > amt)
         {
            cout << "Bet exceeds current balance ($" << amt << ").\nNew Bet > $";
            cin >> x;
            if (x == 0)
            {
               cin.clear();
               cin.ignore(10000, '\n');
            }
            continue;
         }
         if (buyIn[0] > x)
         {
            cout << "Minimum buy-in not met ($" << buyIn[0] << ").\nNew Bet > $";
            cin >> x;
            if (x == 0)
            {
               cin.clear();
               cin.ignore(10000, '\n');
            }
            continue;
         }
         if (x > buyIn[1])
         {
            cout << "Exceeded maximum bet ($" << buyIn[1] << ").\nNew Bet > $";
            cin >> x;
            if (x == 0)
            {
               cin.clear();
               cin.ignore(10000, '\n');
            }
            continue;
         }
         break;
      }
      amt -= x;
      cout << "you bet $" << x << ". you have $" << amt << " left.";
      current = x;
   }
   void finish(double r) // r = result of game: 0 = loss, 0.5 = push, 1 = win
   {
      if (r == 0)
      {
         cout << "you lost...\n";
         current = 0;
         dis();
      }
      else if (r == 0.5)
      {
         cout << "push! $" << current << " stake awarded.";
         amt += current;
         current = 0;
         dis();
      }
      else
      {
         cout << "you won! $" << current * 2 << " awarded!";
         amt += current * 2;
         current = 0;
         dis();
      }
   }
   BetMGM(vector<double> b)
   {
      buyIn = b;
      initAmt = buyIn[0] * 5;
      amt = initAmt;
   }
};

int main()
{
   BetMGM player({5, 200}); // declare player object
   player.bet(5);           // bet function
   player.dis();            // display stats

   player.finish(1);

   return 0;
}