#ifndef TRACKER_H
#define TRACKER_H
#include <vector>

using namespace std;
// header file for tracker.cpp
struct tracker
{
   double initAmt = 0;
   double amt = 0;
   double currentBet = 0;
};

tracker initTracking(vector<double> &buyIn);
void statsTracking(tracker &t);
void placeBet(tracker &t, vector<double> &b);
void endGameTracking(tracker &t, double r);

#endif
