#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>

#include "./betmgm.cpp"
//#include "./fshandler.cpp"
#include "./gameplay.cpp"
using namespace std;








/********************************************/
/*                 MAIN                     */
/********************************************/
int main()
{
   srand(time(0));
   MainMenu();

   return 0;
}

/********************************************/
/*                 MENUS                    */
/********************************************/
void MainMenu()
{
   bool continueGame = true;
   int menuPlace = 5;

   while (continueGame)
   {
      if (menuPlace == 5)
      {
         // MAIN MENU
         cout << "Welcome to" << endl;
         cout << R"($$$$$$$\   $$\                     $$\                                $$\)" << endl;
         cout << R"($$  __$$\  $$ |                    $$ |                               $$ |)" << endl;
         cout << R"($$ |  $$ | $$ | $$$$$$\   $$$$$$$\ $$ |  $$\  $$\  $$$$$$\   $$$$$$$\ $$ |  $$\)" << endl;
         cout << R"($$$$$$$\ | $$ | \____$$\ $$  _____|$$ | $$ | \__| \____$$\ $$  _____| $$ | $$ |)" << endl;
         cout << R"($$  __$$\  $$ | $$$$$$$ |$$ /      $$$$$$ /  $$\\  $$$$$$$ |$$ /      $$$$$$ /)" << endl;
         cout << R"($$ |  $$ | $$ |$$  __$$ |$$ |      $$  _$$<   $$ |$$  __$$ |$$ |      $$  _$$<)" << endl;
         cout << R"($$$$$$$  | $$ |\$$$$$$$ |\$$$$$$$\ $$ | \$$\  $$ |\$$$$$$$ |\$$$$$$$\ $$ | \$$\)" << endl;
         cout << R"(\_______/  \__| \_______| \_______|\__|  \__| $$ | \_______| \_______|\__|  \__|)" << endl;
         cout << R"(          By: Aston, Matt, & Sky       $$\    $$ |)" << endl;
         cout << R"(                                        \$$$$$$  |)" << endl;
         cout << R"(                                         \______/)" << endl;
         cout << endl;
         cout << "                   Please choose from the options below" << endl;
         cout << "                              1. Play Game\n"
                 "                              2. Directions\n"
                 "                              3. Hi-Scores\n"
                 "                              4. Quit Game\n";
         cout << endl
              << endl;

         cin >> menuPlace;
         if (menuPlace == 5)
         {
            menuPlace = menuPlace + 1;
         }
      }
      else if (menuPlace == 1)
      {
         // PLAY GAME
         Gameplay();
         continueGame = false;
      }
      else if (menuPlace == 2)
      {
         // DIRECTIONS
         cout << R"(.------..------..------.     .------..------.     .------..------..------..------.)" << endl;
         cout << R"(|H.--. ||O.--. ||W.--. |     |T.--. ||O.--. |     |P.--. ||L.--. ||A.--. ||Y.--. |)" << endl;
         cout << R"(| :/\: || :/\: || :/\: |     | :/\: || :/\: |     | :/\: || :/\: || (\/) || (\/) |)" << endl;
         cout << R"(| (__) || :\/: || :\/: |     | (__) || :\/: |     | (__) || (__) || :\/: || :\/: |)" << endl;
         cout << R"(| '--'H|| '--'O|| '--'W|     | '--'T|| '--'O|     | '--'P|| '--'L|| '--'A|| '--'Y|)" << endl;
         cout << R"(`------'`------'`------'     `------'`------'     `------'`------'`------'`------')" << endl;
         cout << endl;

         cout << "THE GOAL:" << endl;
         cout << "The goal of Blackjack is to get your hand as close to 21 as possible without going over." << endl;
         cout << "You will be playing against a dealer with the same goal. Both the player and dealer will" << endl;
         cout << "start with 2 cards, however, the dealers second card will be face down to the player until" << endl;
         cout << "you take your first turn. You will lose if you bust (your total score goes over 21) or if" << endl;
         cout << "the dealers score is closer to 21 than yours." << endl;
         cout << "YOUR TURN:" << endl;
         cout << "On your turn, you can either hit or stand. 'Hit' means to add another card to your hand while" << endl;
         cout << "'Stand' means that you do not want any more cards and will stand on your current total." << endl;
         cout << "CALCULATING YOUR SCORE:" << endl;
         cout << "Numbered cards are their face values, face cards have a value of 10, and ace's have a value" << endl;
         cout << "of either 1 or 11. Ace's will automatically have a value of 11, if the ace being 11 will put" << endl;
         cout << "your total score over 21, then it will automatically change to a value of 1." << endl;
         cout << "THE DEALER'S PLAY:" << endl;
         cout << "After you have taken your first turn, the dealers second card will be turned over for you to" << endl;
         cout << "see. If their total is 17 or more, the dealer must stand. If their total is 16 or under, they" << endl;
         cout << "must hit and continue to hit until their total reaches 17 or more, at which point they must stand." << endl;
         cout << "If the dealer has an ace, and counting it as an 11 would put them at 17 or more but under 21, then" << endl;
         cout << "the dealer must count it as an 11 and stand." << endl;
         cout << endl;
         // possibly add info about betting

         cout << "                   Please choose from the options below" << endl;
         cout << "                              1. Play Game\n"
                 //"                              2. Directions\n"
                 "                              2. Hi-Scores\n"  // 3
                 "                              3. Quit Game\n"  // 4
                 "                              4. Main Menu\n"; // 5

         cin >> menuPlace;
         if (menuPlace >= 2 && menuPlace <= 4)
         {
            menuPlace = menuPlace + 1;
         }
      }
      else if (menuPlace == 3)
      {
         // HI-SCORES or MONEY
         cout << "Hi Scores!\n\n";
         // Insert Hi-scores display function
         cout << "                   Please choose from the options below" << endl;
         cout << "                              1. Play Game\n"
                 "                              2. Directions\n"
                 //"                              3. Hi-Scores\n"
                 "                              3. Quit Game\n"  // 4
                 "                              4. Main Menu\n"; // 5

         cin >> menuPlace;
         if (menuPlace >= 3 && menuPlace <= 4)
         {
            menuPlace = menuPlace + 1;
         }
      }
      else if (menuPlace == 4)
      {
         // QUIT GAME
         continueGame = false;
      }
      else
      {
         // INPUT ERROR
         cin.clear();
         cin.ignore(10000, '\n');
         cout << "Invalid input, please try again.\n";
         cout << "                   Please choose from the options below" << endl;
         cout << "                              1. Play Game\n"
                 "                              2. Directions\n"
                 "                              3. Hi-Scores\n"
                 "                              4. Quit Game\n"
                 "                              5. Main Menu\n";

         cin >> menuPlace;
      }
   }
   cout << "Thank you for playing. Goodbye!";
}





