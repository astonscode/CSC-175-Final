#include "tracker.h"
#include <iostream>
using namespace std;

// initialize and return a tracker configured from the provided buy-in range
tracker initTracking(vector<double> &buyIn)
{
   tracker t;
   t.initAmt = buyIn[0] * 5;
   t.amt = t.initAmt;
   t.currentBet = 0;
   cout << "Balance: $" << t.amt << endl;
   cout << "Current Bet: $" << t.currentBet << endl;
   return t;
}

double outcome(double bet, int result) // calculates outcome based on bet and result
{
   if (result == 0) // loss
   {
      return 0;
   }
   else if (result == 1) // push
   {
      return bet;
   }
   else // win
   {
      return bet * 2;
   }
}

void statsTracking(tracker &t) // displays current stats
{
   cout << "\nMoney: $" << t.amt << endl;
   cout << "Current Bet: $" << t.currentBet << endl;
   cout << "IF Win: $" << outcome(t.currentBet, 2) << endl;
   cout << "IF Push: $" << outcome(t.currentBet, 1) << endl;
   cout << "IF Loss: $" << outcome(t.currentBet, 0) << endl;
}

void placeBet(tracker &t, vector<double> &b) // places a bet and validates input
{
   double bet;
   cout << "\nCurrent balance: $" << t.amt << endl;
   cout << "Place your bet (must be between $" << b[0] << " and $" << b[1] << "): $";
   cin >> bet;
   while (true)
   {
      if (bet > t.amt)
      {
         cout << "Bet exceeds current balance ($" << t.amt << ").\nNew Bet > $";
         cin >> bet;
         if (bet == 0)
         {
            cin.clear();
            cin.ignore(10000, '\n');
         }
         continue;
      }
      if (b[0] > bet)
      {
         cout << "Minimum buy-in not met ($" << b[0] << ").\nNew Bet > $";
         cin >> bet;
         if (bet == 0)
         {
            cin.clear();
            cin.ignore(10000, '\n');
         }
         continue;
      }
      if (bet > b[1])
      {
         cout << "Exceeded maximum bet ($" << b[1] << ").\nNew Bet > $";
         cin >> bet;
         if (bet == 0)
         {
            cin.clear();
            cin.ignore(10000, '\n');
         }
         continue;
      }
      t.currentBet = bet;
      t.amt -= bet;
      break;
   }
}

void endGameTracking(tracker &t, double r) // ends tracking for a game based on result
{
   if (r == 0)
   {
      cout << "you lost...\n";
   }
   else if (r == 0.5)
   {
      cout << "push! $" << t.currentBet << " stake awarded." << endl;
      t.amt += t.currentBet;
   }
   else
   {
      cout << "you won! $" << t.currentBet * 2 << " awarded!" << endl;
      t.amt += t.currentBet * 2;
   }

   t.currentBet = 0;
   cout << "Your money: $" << t.amt << endl;
   cout << "-----------------------------------" << endl; // sky - line was not showing up for each win/loss case
}