#include <include/logic.h>

// Player choices
char logic::getPlayerChoice(bool canSplit, bool canDoubleDown) {
    char choice;
    cout << "\nOptions: (H)it, (S)tand";
    if (canSplit) cout << ", S(P)lit";
    if (canDoubleDown) cout << ", (D)ouble Down";
    cout << ", (X) Pass: ";
    cin >> choice;
    return toupper(choice);
}

// Game logic
void logic::playBlackjack() {
    cards cards;
    vector<Card> deck = cards.createDeck();
    int playerCredits = 1000;
    srand(static_cast<unsigned int>(std::time(0)));

    while (playerCredits > 0) {
        cout << "\nCurrent credits: " << playerCredits << endl;
        cout << "Place your bet: ";
        int bet;
        cin >> bet;

        if (bet > playerCredits) {
            cout << "Not enough credits! Try again.\n";
            continue;
        }

        vector<Card> playerHand, dealerHand;
        playerHand.push_back(deck.back()); deck.pop_back();
        dealerHand.push_back(deck.back()); deck.pop_back();
        playerHand.push_back(deck.back()); deck.pop_back();
        dealerHand.push_back(deck.back()); deck.pop_back();

        cards.displayHand(playerHand, "Player", false);
        cards.displayHand(dealerHand, "Dealer", true);

        bool playerTurn = true, splitAvailable = false, doubleDownAvailable = false, pass = false;
        vector<Card> splitHand;

        if (playerHand[0].rank == playerHand[1].rank) splitAvailable = true;
        if (cards.calculateHandValue(playerHand) >= 9 && cards.calculateHandValue(playerHand) <= 11) doubleDownAvailable = true;

        while (playerTurn) {
            char choice = getPlayerChoice(splitAvailable, doubleDownAvailable);
            switch (choice) {
            case 'H': {
                playerHand.push_back(deck.back()); deck.pop_back();
                cards.displayHand(playerHand, "Player", false);
                if (cards.calculateHandValue(playerHand) > 21) {
                    cout << "Player busts!\n";
                    playerTurn = false;
                }
                break;
            }
            case 'S':
                playerTurn = false;
                break;
            case 'P':
                if (splitAvailable) {
                    splitHand.push_back(playerHand.back());
                    playerHand.pop_back();
                    playerHand.push_back(deck.back()); deck.pop_back();
                    splitHand.push_back(deck.back()); deck.pop_back();
                    cout << "Hand split!\n";
                    cards.displayHand(playerHand, "Player (Hand 1)", false);
                    cards.displayHand(splitHand, "Player (Hand 2)", false);
                    splitAvailable = false;
                }
                else {
                    cout << "Invalid choice!\n";
                }
                break;
            case 'D':
                if (doubleDownAvailable) {
                    bet *= 2;
                    playerHand.push_back(deck.back()); deck.pop_back();
                    cards.displayHand(playerHand, "Player", false);
                    playerTurn = false;
                }
                else {
                    cout << "Invalid choice!\n";
                }
                break;
            case 'X':
                pass = true;
                playerCredits -= bet / 2;
                playerTurn = false;
                break;
            default:
                cout << "Invalid choice! Try again.\n";
            }
        }

        if (!pass) {
            // Dealer's turn
            cards.displayHand(dealerHand, "Dealer", false);
            while (cards.calculateHandValue(dealerHand) < 17) {
                dealerHand.push_back(deck.back()); deck.pop_back();
                cards.displayHand(dealerHand, "Dealer", false);
            }

            int playerTotal = cards.calculateHandValue(playerHand);
            int dealerTotal = cards.calculateHandValue(dealerHand);

            cout << "\nFinal results:\n";
            cards.displayHand(playerHand, "Player", false);
            cards.displayHand(dealerHand, "Dealer", false);

            if (playerTotal > 21 || (dealerTotal <= 21 && dealerTotal > playerTotal)) {
                cout << "Dealer wins!\n";
                playerCredits -= bet;
            }
            else if (dealerTotal > 21 || playerTotal > dealerTotal) {
                cout << "Player wins!\n";
                playerCredits += bet;
            }
            else {
                cout << "It's a tie!\n";
            }
        }

        if (playerCredits <= 0) {
            cout << "You are out of credits! Game over.\n";
        }
    }
}