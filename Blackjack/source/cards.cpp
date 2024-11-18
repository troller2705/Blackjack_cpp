#include <include/cards.h>

// Deck of cards
vector<Card> cards::createDeck() {
    vector<Card> deck;
    vector<string> ranks = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
    vector<string> suits = { "Hearts", "Diamonds", "Clubs", "Spades" };

    for (const string& suit : suits) {
        for (const string& rank : ranks) {
            int value = (rank == "A") ? 11 : (rank == "J" || rank == "Q" || rank == "K") ? 10 : stoi(rank);
            deck.push_back({ rank, suit, value });
        }
    }
    random_shuffle(deck.begin(), deck.end());
    return deck;
}

// Calculate hand value
int cards::calculateHandValue(vector<Card>& hand) {
    int value = 0, aceCount = 0;
    for (const Card& card : hand) {
        value += card.value;
        if (card.rank == "A") aceCount++;
    }
    while (value > 21 && aceCount > 0) {
        value -= 10;
        aceCount--;
    }
    return value;
}

// Display hand
void cards::displayHand(const vector<Card>& hand, const string& owner, bool hideDealerCard = false) {
    cout << owner << " hand: ";
    for (size_t i = 0; i < hand.size(); i++) {
        if (hideDealerCard && i == 1) {
            cout << "[Hidden Card], ";
        }
        else {
            cout << hand[i].rank << " of " << hand[i].suit << ", ";
        }
    }
    if (!hideDealerCard) {
        cout << "(Value: " << calculateHandValue(const_cast<vector<Card>&>(hand)) << ")";
    }
    cout << endl;
}