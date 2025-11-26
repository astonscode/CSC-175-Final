#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

std::vector<std::string> cards = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
//std::vector<std::string> suits = {"♠", "♣︎", "♦︎", "♥︎"};
std::vector<std::string> suits = {"S", "C", "D","H"};
vector<string> deck;
vector<string> playerHand;
vector<string> dealerHand;

int dealerScore, playerScore;

bool loop = true;

void createDeck();
string drawCard(vector<string> cards);
int cardValue(string card, bool player);
void displayHand(vector<string> deck,bool player);
void calculateDealerHand();
void calculatePlayerHand();
void Gameplay();
void MainMenu();                   //displays menu's
void playAgainValid (char &again); //validates input for playAgain variable


/*void gameEnd()
{
   if (score == 21)
   {
      std::cout << "You have reached 21!";
   }
   else if (score > 21)
   {
      std::cout << "You exceeded 21...\nYou lost...";
   }
}*/

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
if (menuPlace == 5) {
   //MAIN MENU
   cout <<  "Welcome to" << endl;
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
   cout <<  "                   Please choose from the options below"<<endl;
   cout<<   "                              1. Play Game\n"
            "                              2. Directions\n"
            "                              3. Hi-Scores\n"
            "                              4. Quit Game\n";
   cout << endl << endl;

   cin >> menuPlace;
   if (menuPlace == 5) {
      menuPlace = menuPlace + 1;
   }

} else if (menuPlace == 1) {
   //PLAY GAME
      Gameplay();
   continueGame = false;

} else if (menuPlace == 2) {
   //DIRECTIONS
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
   //possibly add info about betting

   cout <<  "                   Please choose from the options below"<<endl;
   cout<<   "                              1. Play Game\n"
          //"                              2. Directions\n"
            "                              2. Hi-Scores\n"  //3
            "                              3. Quit Game\n"  //4
            "                              4. Main Menu\n"; //5

   cin >> menuPlace;
   if (menuPlace >= 2 && menuPlace <= 4) {
      menuPlace = menuPlace + 1;
   }


} else if (menuPlace == 3) {
   //HI-SCORES or MONEY
   cout<<"Hi Scores!\n\n";
   //Insert Hi-scores display function
   cout <<  "                   Please choose from the options below"<<endl;
   cout<<   "                              1. Play Game\n"
            "                              2. Directions\n"
          //"                              3. Hi-Scores\n"
            "                              3. Quit Game\n"  //4
            "                              4. Main Menu\n"; //5

   cin >> menuPlace;
   if (menuPlace >= 3 && menuPlace <= 4) {
      menuPlace = menuPlace + 1;
   }

} else if (menuPlace == 4) {
   //QUIT GAME
   continueGame = false;

} else{
   //INPUT ERROR
   cin.clear();
   cin.ignore(10000, '\n');
         cout<<"Invalid input, please try again.\n";
   cout <<  "                   Please choose from the options below"<<endl;
   cout<<   "                              1. Play Game\n"
            "                              2. Directions\n"
            "                              3. Hi-Scores\n"
            "                              4. Quit Game\n"
            "                              5. Main Menu\n";

   cin >> menuPlace;
      }
   }
   cout<<"Thank you for playing. Goodbye!";
}


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
   {cout<<"Deck is empty.\n";}

   int randomCard = rand() % deck.size();
   string card = deck[randomCard];

   deck.erase(deck.begin() + randomCard);
   return card;
}


//split into two functions for dealer and player?
int cardValue(string card, bool player)
{
   if ((card[0] == '1' && card[1]=='0')||card[0] == 'K' || card[0]== 'Q' || card[0]== 'J')//10 check
   {
      return 10;
   }
   else if (card[0] == 'A')
   {
      //Ace logic
      if (player)//doesn't need player tag unless we're implementing soft 17
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
         //dealer
         if (dealerScore + 11 == 17 || dealerScore + 11 >21)
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


//split into two functions for player and dealer
void displayHand(vector<string> deck,bool player)
{


   // Each card has 4 lines of ASCII art
   vector<string> line1;
   vector<string> line2;
   vector<string> line3;
   vector<string> line4;

   for (int card = 0; card < deck.size(); card++)
   {
      //calculate spacing on the card display
      string cardNum = deck[card];
      string spacing;
      int cardWidth = 5;
      int paddingRight = cardWidth - cardNum.length();
      if (paddingRight < 0) paddingRight = 0; //just in case
      spacing = string(paddingRight, ' ');


      line1.push_back("╭─────╮");
      line2.push_back("│" + cardNum + spacing + "│");
      line3.push_back("│     │");
      line4.push_back("╰─────╯");
   }

   //print cards side by side
   for (int i = 0; i < deck.size(); i++) cout << line1[i] << "   ";
   cout << endl;

   for (int i = 0; i < deck.size(); i++) cout << line2[i] << "   ";
   cout << endl;

   for (int i = 0; i < deck.size(); i++) cout << line3[i] << "   ";
   cout << endl;

   for (int i = 0; i < deck.size(); i++) cout << line4[i] << "   ";
   cout << endl;

   if (player)
   {
      cout<<"\nPLAYER: "<<playerScore;
      cout<<"\n\n";
   }
   else
   {
      cout<<"\nDEALER: "<<dealerScore;
      cout<<"\n\n";
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
   //dealerHand.push_back(drawCard());
   while (logic)
   {


      calculateDealerHandValue();



      if (dealerScore > 21)
      {
         cout<<"-----------------------------------\n";
         cout<<"\nDealer busts. Player wins.\n\n";
         displayHand(dealerHand,false);
         displayHand(playerHand, true);
         cout<< endl;
         logic = false;
         break;

         //pay player
      }


      else if (dealerScore <= 16)
      {
         dealerHand.push_back(drawCard());
         calculateDealerHandValue();
         displayHand(dealerHand,false);
         displayHand(playerHand, true);
         continue;

      }
      else if (dealerScore == playerScore)
      {
         cout<<"-----------------------------------\n";
         cout<<"\nPush.\n\n";
         displayHand(dealerHand,false);
         displayHand(playerHand, true);
         cout<< endl;

         logic = false;
         break;
      }
      else if (dealerScore <21 && playerScore == 21)
      {
         cout<<"-----------------------------------\n";
         cout<<"\nBlackjack! Player Wins!\n\n";
         displayHand(dealerHand,false);
         displayHand(playerHand, true);
         cout<< endl;
         logic = false;
         break;
      }
      else if (dealerScore >16)
      {
         if (dealerScore > playerScore)
         {
            cout<<"-----------------------------------\n";
            cout<< "Dealer has " << dealerScore << " -- player loses" << endl;
            displayHand(dealerHand,false);
            displayHand(playerHand,true);
            cout<< endl;
         }
         else
         {
            cout<<"-----------------------------------\n";
            cout<< "Dealer has " << dealerScore << "-- player Wins. \n\n";
            displayHand(dealerHand,false);
            displayHand(playerHand,true);
            cout<< endl;
         }
         break;
      }

      dealerHand.push_back(drawCard());
   }

   resetHand();

}


void Gameplay() {
   char playAgain = 'y';
   while (playAgain == 'y' || playAgain == 'Y') {
      loop = true;
      int option;

      //Player bets
      resetHand();


      while (loop)
      {
         //Show Dealer Hand
         calculateDealerHandValue();
         displayHand(dealerHand,false);

         //Show Player hand
         calculatePlayerHandValue();
         displayHand(playerHand,true);

         //blackjack on first hand check
         if (playerScore == 21)
         {
            //add dealer logic check to see if they get 21 too.
            dealerLogic();
            continue;

            //add to winnings
         }

         //Create function to display In Game User Interface
         cout<<"(1) Hit      (2) Stand       (3) Quit" << endl;
         cin>>option;

         switch (option)
         {
            //ace check set to automatically choose best option
            case 1:
               cout<<"-----------------------------------\n";
               cout<<"\nPlayer Hit.\n";
               playerHand.push_back(drawCard());
               calculatePlayerHandValue();
               //

               if (playerScore > 21)
               {
                  cout<<"-----------------------------------\n";
                  displayHand(playerHand,true);
                  cout<<playerScore <<" - PLAYER BUSTS!\n\n";
                  cout<<"-----------------------------------\n";

                  //ask if they want to play another hand
                  cout << "Play another hand? (y/n)" << endl;
                  cin >> playAgain;
                  playAgainValid(playAgain);

                  //Remove bet amount from player's funds

                  resetHand();

                  continue;

               }
               else if (playerScore == 21)
               {
                  //Check if dealer gets 21 first. if not, blackjack player wins
                  dealerLogic();

                  //Add payout to total player funds

                  resetHand();
                  //ask if they want to play another hand
                  cout << "Play another hand? (y/n)" << endl;
                  cin >> playAgain;
                  playAgainValid(playAgain);
                  continue;
               }

               //displayHand(dealerHand,false);

               break;

            case 2:
               cout<<"-----------------------------------\n";
               cout<<"\nPlayer Stand.\n\n";
               //dealer logic
               dealerLogic();
               cout<<"-----------------------------------\n";
               //ask if they want to play another hand
               cout << "Play another hand? (y/n)" << endl;
               cin >> playAgain;
               playAgainValid(playAgain);
               break;
            case 3:
               cout<<"-----------------------------------\n";
               cout<<"Player Quit.\n";
               cout<<"-----------------------------------\n";
               loop = false;
               break;

            default:
               cin.clear();
               cin.ignore(10000, '\n');
               cout<<"-----------------------------------\n";
               cout<<"Invalid input, please try again.\n";
               cout<<"-----------------------------------\n";
         }
         //resetHand();
         //Player decides to hit or stay
         //if 21 or less, dealer reveals card 2
         //if dealer has 16 or less, must hit. else, stand

         if (playAgain == 'n' || playAgain == 'N') {
            loop = false;
         }
      }
   }



}


void playAgainValid (char &again) {
   while ((again != 'y' && again != 'Y') && (again != 'n' && again != 'N')) {
      if ((again != 'y' && again != 'Y') && (again != 'n' && again != 'N')) {
         cin.clear();
         cin.ignore(10000, '\n');
         cout<<"Invalid input, please try again.\n";
         cin >> again;
      }
   }
}

