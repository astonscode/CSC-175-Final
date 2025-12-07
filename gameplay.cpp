#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <ctime>
#include "tracker.h"

using namespace std;

std::vector<std::string> cards = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
// std::vector<std::string> suits = {"♠", "♣︎", "♦︎", "♥︎"};
std::vector<std::string> suits = {"S", "C", "D", "H"};
vector<string> deck;
vector<string> playerHand;
vector<string> dealerHand;
bool loop = true;
int dealerScore, playerScore;

void createDeck();
string drawCard(vector<string> cards);
int cardValue(string card, bool player);
void displayHand(vector<string> displayDeck, bool player);
void calculateDealerHand();
void calculatePlayerHand();
void Gameplay();
void MainMenu();
void playAgainValid(char &again); // validates input for playAgain variable

// creates the main deck by looping through cards and suits vector and adding to deck vector.
void createDeck()
{
   deck.clear();
   for (int suit = 0; suit < 4; suit++)
   {
      for (int card = 0; card < 13; card++)
      {
         deck.push_back(cards[card] + suits[suit]);
      }
   }
}

// creates global tracker object and initializes it
vector<double> betRange = {5.0, 500.0}; // min and max bet amounts
tracker gt;

// Pulls a random card from deck and removes it from vector
string drawCard()
{

   if (deck.empty())
   {
      cout << "Deck is empty.\n";
   }

   int randomCard = rand() % deck.size();
   string card = deck[randomCard];

   deck.erase(deck.begin() + randomCard);
   return card;
}

// makes decisions based on what card is to assign it a value. Returns value of card.
int cardValue(string card, bool player)
{
   if ((card[0] == '1' && card[1] == '0') || card[0] == 'K' || card[0] == 'Q' || card[0] == 'J') // 10 check
   {
      return 10;
   }
   else if (card[0] == 'A')
   {
      // Ace logic
      if (player) // doesn't need player tag unless we're implementing soft 17
      {
         if (playerScore + 11 > 21)
         {
            return 1;
         }
         else
         {
            return 11;
         }
      }

      // dealer soft 17 check
      if (!player && dealerScore + 11 == 17 || dealerScore + 11 > 21)
      {
         return 1;
      }
      return 11;
   }

   // stoi converts a string into an int so it can be used in calculations.
   return stoi(card);
}

// Moves all aces to bottom of a vector to calculate hand.
vector<string> handSort(vector<string> sortDeck)
{
   vector<string> temp;
   vector<string> aces;
   vector<string> nonAces;

   for (int i = 0; i < sortDeck.size(); i++)
   {
      string charCheck = sortDeck[i];
      if (charCheck[0] == 'A')
      {
         aces.push_back(sortDeck[i]);
      }
      else
      {
         nonAces.push_back(sortDeck[i]);
      }
   }
   for (int j = 0; j < nonAces.size(); j++)
   {
      temp.push_back(nonAces[j]);
   }
   for (int k = 0; k < aces.size(); k++)
   {
      temp.push_back(aces[k]);
   }
   return temp;
}

// loops through hand and call cardValue function on each card. Update score
void calculatePlayerHandValue()
{
   playerScore = 0;
   vector<string> temp = handSort(playerHand);

   for (int card = 0; card < temp.size(); card++)
   {
      // cout<<temp[0];
      playerScore += cardValue(temp[card], true);
      // dealerScore += cardValue(playerHand[card], true);
   }
}

void calculateDealerHandValue()
{
   dealerScore = 0;
   vector<string> temp = handSort(dealerHand);

   for (int card = 0; card < temp.size(); card++)
   {
      dealerScore += cardValue(temp[card], false);
      // dealerScore += cardValue(dealerHand[card], false);
   }
}

// Displays Player/Deal hand and scores
void displayHand(vector<string> displayDeck, bool player)
{

   // Each card has 4 lines of ASCII art
   vector<string> line1;
   vector<string> line2;
   vector<string> line3;
   vector<string> line4;

   for (int card = 0; card < displayDeck.size(); card++)
   {
      // calculate spacing on the card display
      string cardNum = displayDeck[card];
      string spacing;
      int cardWidth = 5;
      int paddingRight = cardWidth - cardNum.length();
      if (paddingRight < 0)
         paddingRight = 0; // just in case
      spacing = string(paddingRight, ' ');

      line1.push_back("╭─────╮");
      line2.push_back("│" + cardNum + spacing + "│");
      line3.push_back("│     │");
      line4.push_back("╰─────╯");
   }

   // print cards side by side
   for (int i = 0; i < displayDeck.size(); i++)
      cout << line1[i] << "   ";
   cout << endl;

   for (int i = 0; i < displayDeck.size(); i++)
      cout << line2[i] << "   ";
   cout << endl;

   for (int i = 0; i < displayDeck.size(); i++)
      cout << line3[i] << "   ";
   cout << endl;

   for (int i = 0; i < displayDeck.size(); i++)
      cout << line4[i] << "   ";
   cout << endl;

   if (player)
   {
      cout << "\nPLAYER: " << playerScore;
      cout << "\n\n";
   }
   else
   {
      cout << "\nDEALER: " << dealerScore;
      cout << "\n\n";
   }
}

// Resets hand by creating new deck of 52 cards, clearing both hands, and drawing new hands
void resetHand()
{
   playerHand.clear();
   dealerHand.clear();

   createDeck();
   playerHand.push_back(drawCard());
   playerHand.push_back(drawCard());

   dealerHand.push_back(drawCard());
}


// Dealer decisions based on certain criteria - wins/losses
void dealerLogic()
{
   bool logic = true;
   calculateDealerHandValue();

   while (logic)
   {

      calculateDealerHandValue();

      if (dealerScore > 21)
      {
         cout << "-----------------------------------\n";
         cout << "\nDealer busts. Player wins!!!\n\n";
         displayHand(dealerHand, false);
         displayHand(playerHand, true);
         cout << endl;
         // logic = false;

         // pay player
         endGameTracking(gt, 2);
         break;
      }

      else if (dealerScore <= 16)
      {
         dealerHand.push_back(drawCard());
         calculateDealerHandValue();
         displayHand(dealerHand, false);
         displayHand(playerHand, true);
         continue;
      }
      else if (dealerScore == playerScore)
      {
         cout << "-----------------------------------\n";
         cout << "\nPush.\n\n";
         displayHand(dealerHand, false);
         displayHand(playerHand, true);
         cout << endl;

         // logic = false;
         // player gets money back
         endGameTracking(gt, 0.5);

         break;
      }
      else if (dealerScore < 21 && playerScore == 21)
      {
         cout << "-----------------------------------\n";
         cout << "\nBlackjack! Player Wins!!!\n\n";
         displayHand(dealerHand, false);
         displayHand(playerHand, true);
         cout << endl;
         // logic = false;

         // player wins 1.5x bet
         endGameTracking(gt, 2);
         break;
      }
      else if (dealerScore > 16)
      {
         if (dealerScore > playerScore)
         {
            cout << "-----------------------------------\n";
            cout << "Dealer has " << dealerScore << " -- Player Loses..." << endl;
            displayHand(dealerHand, false);
            displayHand(playerHand, true);
            cout << endl;
            // player loses bet amount

         }
         else
         {
            cout << "-----------------------------------\n";
            cout << "Dealer has " << dealerScore << "-- Player Wins!!! \n\n";
            displayHand(dealerHand, false);
            displayHand(playerHand, true);
            cout << endl;
            // player wins bet amount
            endGameTracking(gt, 2);
         }

      }
      break;
      //dealerHand.push_back(drawCard());
   }
   resetHand();

}

// Main gameplay loop that connects all the previous functions.
// allows player to make decisions and decide to play or quit. Bets are made here too
void Gameplay()
{

   char playAgain = 'y';
   gt = initTracking(betRange);
   placeBet(gt, betRange);
   statsTracking(gt);

   while (playAgain == 'y' || playAgain == 'Y')
   {
      loop = true;
      int option;

      resetHand();

      while (loop)
      {

         // Show Dealer Hand
         calculateDealerHandValue();
         displayHand(dealerHand, false);

         // Show Player hand
         calculatePlayerHandValue();
         displayHand(playerHand, true);

         // blackjack on first hand check
         if (playerScore == 21)
         {
            // add dealer logic check to see if they get 21 too.
            dealerLogic();
            continue;
         }

         // In Game User Interface
         cout << "(1) Hit      (2) Stand       (3) Quit" << "\n> ";
         cin >> option;

         switch (option)
         {
         case 1:
            cout << "-----------------------------------\n";
            cout << "\nPlayer Hit.\n";
            playerHand.push_back(drawCard());
            calculatePlayerHandValue();

            if (playerScore > 21)
            {
               cout << "-----------------------------------\n";
               displayHand(playerHand, true);
               cout << playerScore << " - PLAYER BUSTS!\n\n";
               cout << "-----------------------------------\n";

               endGameTracking(gt, 0);

               // Play Again?
               cout << "Play another hand? (y/n)\n> ";
               cin >> playAgain;
               playAgainValid(playAgain);

               if (playAgain == 'y' || playAgain == 'Y')
               {
                  resetHand();
                  placeBet(gt, betRange);
                  statsTracking(gt);
               }

               continue;
            }
            else if (playerScore == 21)
            {
               // Check if dealer gets 21 first. if not, blackjack player wins
               cout << "You have 21! You won't need to play this round further. Only way you lose is if the dealer pushes...\n";
               dealerLogic();

               // Play Again?
               cout << "Play another hand? (y/n)\n> ";
               cin >> playAgain;
               playAgainValid(playAgain);

               if (playAgain == 'y' || playAgain == 'Y')
               {
                  resetHand();
                  placeBet(gt, betRange);
                  statsTracking(gt);
               }

               continue;
            }

            break;

         case 2:
            cout << "-----------------------------------\n";
            cout << "\nPlayer Stand.\n\n";
            // dealer logic
            dealerLogic();
            cout << "-----------------------------------\n";
            // Play Again?
            cout << "Play another hand? (y/n)\n> ";
            cin >> playAgain;
            playAgainValid(playAgain);

            if (playAgain == 'y' || playAgain == 'Y')
            {
               if (gt.amt == 0)
               {
                  char c;
                  cout<<"You are out of money. Would you like to buy back in?";
                  cin>>c;
                  if (c == 'y' || c == 'Y')
                  {
                     gt = initTracking(betRange);

                     resetHand();
                     placeBet(gt, betRange);
                     statsTracking(gt);
                  }
                  else
                  {
                     MainMenu();
                  }
                  break;

               }
               resetHand();
               placeBet(gt, betRange);
               statsTracking(gt);
            }

            break;
         case 3:
            cout << "-----------------------------------\n";
            cout << "Player Quit.\n";
            cout << "-----------------------------------\n";
            loop = false;
            MainMenu();
            break;

         default:
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "-----------------------------------\n";
            cout << "Invalid input. Please try again.\n";
            cout << "-----------------------------------\n";
         }

         if (playAgain == 'n' || playAgain == 'N')
         {
            loop = false;
            MainMenu();
         }
      }
      break;
   }
   playAgain = 'n';
}

void playAgainValid(char &again)
{
   while ((again != 'y' && again != 'Y') && (again != 'n' && again != 'N'))
   {
      if ((again != 'y' && again != 'Y') && (again != 'n' && again != 'N'))
      {
         cin.clear();
         cin.ignore(10000, '\n');
         cout << "Invalid input, please try again.\n";
         cin >> again;
      }
   }
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
         cout << "> ";
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
         cout << "BETTING:" << endl;
         cout << "Each players starts out with $25. You can bet a minimum of $5 and a maximum of $500 on each hand." << endl;
         cout << "If the player wins, your bet is doubled and returned to you. On a loss you lose your bet. On a push" << endl;
         cout << "(you and the dealer tie) you will have your bet returned to you at the same value." << endl;
         cout << endl; //sky - added betting info

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
         loop = false;
         continueGame = false;
         cout << "Thank you for playing. Goodbye!\n";
         break;
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
}
