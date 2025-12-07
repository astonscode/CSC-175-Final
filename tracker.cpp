#include "tracker.h"
#include <iostream>
using namespace std;

// initialize and return a tracker configured from the provided buy-in range
tracker initTracking(const std::vector<double> &buyIn)
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
   std::cout << "\nMoney: $" << t.amt << endl;
   std::cout << "Current Bet: $" << t.currentBet << endl;
   std::cout << "IF Win: $" << outcome(t.currentBet, 2) << endl;
   std::cout << "IF Push: $" << outcome(t.currentBet, 1) << endl;
   std::cout << "IF Loss: $" << outcome(t.currentBet, 0) << endl;
}

void placeBet(tracker &t, const std::vector<double> &b) // places a bet and validates input
{
   double bet;
   std::cout << "\nCurrent balance: $" << t.amt << endl;
   std::cout << "Place your bet (must be between $" << b[0] << " and $" << b[1] << "): $";
   cin >> bet;
   while (true)
   {
      if (bet > t.amt)
      {
         std::cout << "Bet exceeds current balance ($" << t.amt << ").\nNew Bet > $";
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
         std::cout << "Minimum buy-in not met ($" << b[0] << ").\nNew Bet > $";
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
         std::cout << "Exceeded maximum bet ($" << b[1] << ").\nNew Bet > $";
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
      std::cout << "you lost...\n";
   }
   else if (r == 0.5)
   {
      std::cout << "push! $" << t.currentBet << " stake awarded." << endl;
      t.amt += t.currentBet;
   }
   else
   {
      std::cout << "you won! $" << t.currentBet * 2 << " awarded!" << endl;
      t.amt += t.currentBet * 2;
   }

   t.currentBet = 0;
   std::cout << "Your money: $" << t.amt << endl;
   std::cout << "-----------------------------------" << endl; //sky - line was not showing up for each win/loss case
}