#ifndef TRACKER_H
#define TRACKER_H
#include <vector>

// header file for tracker.cpp
struct tracker
{
   double initAmt = 0;
   double amt = 0;
   double currentBet = 0;
};

tracker initTracking(const std::vector<double> &buyIn);
void statsTracking(tracker &t);
void placeBet(tracker &t, const std::vector<double> &b);
void endGameTracking(tracker &t, double r);

#endif
