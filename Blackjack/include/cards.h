#pragma once
#include <prerequisites.h>


class cards
{
    public:
        vector<Card> createDeck();
        int calculateHandValue(vector<Card>& hand);
        void displayHand(const vector<Card>& hand, const string& owner, bool hideDealerCard);
};
