#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <ctime>
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
void displayHand(vector<string> deck, bool player);
void calculateDealerHand();
void calculatePlayerHand();
void Gameplay();
void MainMenu();
// displays menu's
void playAgainValid(char &again); // validates input for playAgain variable

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

// split into two functions for dealer and player?
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
        else
        {
            // dealer
            if (dealerScore + 11 == 17 || dealerScore + 11 > 21)
            {
                return 1;
            }
            return 11;
        }
    }

    return stoi(card);
}

void calculatePlayerHandValue()
{
    playerScore = 0;

    for (int card = 0; card < playerHand.size(); card++)
    {
        playerScore += cardValue(playerHand[card], true);
    }
}

void calculateDealerHandValue()
{
    dealerScore = 0;
    for (int card = 0; card < dealerHand.size(); card++)
    {
        dealerScore += cardValue(dealerHand[card], false);
    }
}

// split into two functions for player and dealer
void displayHand(vector<string> deck, bool player)
{

   // Each card has 4 lines of ASCII art
   vector<string> line1;
   vector<string> line2;
   vector<string> line3;
   vector<string> line4;

   for (int card = 0; card < deck.size(); card++)
   {
      // calculate spacing on the card display
      string cardNum = deck[card];
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
   for (int i = 0; i < deck.size(); i++)
      cout << line1[i] << "   ";
   cout << endl;

   for (int i = 0; i < deck.size(); i++)
      cout << line2[i] << "   ";
   cout << endl;

   for (int i = 0; i < deck.size(); i++)
      cout << line3[i] << "   ";
   cout << endl;

   for (int i = 0; i < deck.size(); i++)
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

void resetHand()
{

   playerHand.clear();
   dealerHand.clear();

   createDeck();
   playerHand.push_back(drawCard());
   playerHand.push_back(drawCard());

   dealerHand.push_back(drawCard());
}

void dealerLogic()
{
   bool logic = true;
   calculateDealerHandValue();
   // dealerHand.push_back(drawCard());
   while (logic)
   {

      calculateDealerHandValue();

      if (dealerScore > 21)
      {
         cout << "-----------------------------------\n";
         cout << "\nDealer busts. Player wins.\n\n";
         displayHand(dealerHand, false);
         displayHand(playerHand, true);
         cout << endl;
         logic = false;
         break;

         // pay player
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

         logic = false;
         break;
      }
      else if (dealerScore < 21 && playerScore == 21)
      {
         cout << "-----------------------------------\n";
         cout << "\nBlackjack! Player Wins!\n\n";
         displayHand(dealerHand, false);
         displayHand(playerHand, true);
         cout << endl;
         logic = false;
         break;
      }
      else if (dealerScore > 16)
      {
         if (dealerScore > playerScore)
         {
            cout << "-----------------------------------\n";
            cout << "Dealer has " << dealerScore << " -- player loses" << endl;
            displayHand(dealerHand, false);
            displayHand(playerHand, true);
            cout << endl;
         }
         else
         {
            cout << "-----------------------------------\n";
            cout << "Dealer has " << dealerScore << "-- player Wins. \n\n";
            displayHand(dealerHand, false);
            displayHand(playerHand, true);
            cout << endl;
         }
         break;
      }

      dealerHand.push_back(drawCard());
   }

   resetHand();
}

void Gameplay()
{
   char playAgain = 'y';
   while (playAgain == 'y' || playAgain == 'Y')
   {
      loop = true;
      int option;

      // Player bets
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

            // add to winnings
         }

         // Create function to display In Game User Interface
         cout << "(1) Hit      (2) Stand       (3) Quit" << endl;
         cin >> option;

         switch (option)
         {
         // ace check set to automatically choose best option
         case 1:
            cout << "-----------------------------------\n";
            cout << "\nPlayer Hit.\n";
            playerHand.push_back(drawCard());
            calculatePlayerHandValue();
            //

            if (playerScore > 21)
            {
               cout << "-----------------------------------\n";
               displayHand(playerHand, true);
               cout << playerScore << " - PLAYER BUSTS!\n\n";
               cout << "-----------------------------------\n";

               // ask if they want to play another hand
               cout << "Play another hand? (y/n)" << endl;
               cin >> playAgain;
               playAgainValid(playAgain);

               // Remove bet amount from player's funds

               resetHand();

               continue;
            }
            else if (playerScore == 21)
            {
               // Check if dealer gets 21 first. if not, blackjack player wins
               dealerLogic();

               // Add payout to total player funds

               resetHand();
               // ask if they want to play another hand
               cout << "Play another hand? (y/n)" << endl;
               cin >> playAgain;
               playAgainValid(playAgain);
               continue;
            }

            // displayHand(dealerHand,false);

            break;

         case 2:
            cout << "-----------------------------------\n";
            cout << "\nPlayer Stand.\n\n";
            // dealer logic
            dealerLogic();
            cout << "-----------------------------------\n";
            // ask if they want to play another hand
            cout << "Play another hand? (y/n)" << endl;
            cin >> playAgain;
            playAgainValid(playAgain);
            break;
         case 3:
            cout << "-----------------------------------\n";
            cout << "Player Quit.\n";
            cout << "-----------------------------------\n";
            loop = false;
            break;

         default:
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "-----------------------------------\n";
            cout << "Invalid input, please try again.\n";
            cout << "-----------------------------------\n";
         }
         // resetHand();
         // Player decides to hit or stay
         // if 21 or less, dealer reveals card 2
         // if dealer has 16 or less, must hit. else, stand

         if (playAgain == 'n' || playAgain == 'N')
         {
            loop = false;
         }

      }
   }
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

