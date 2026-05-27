/*
 SolitairePoker.c
 
 Notes: The 52 cards of a deck are represented as integers: 0 .. 51
 0..12 are clubs Ace, 2, ..., King
 13..25 are diamonds Ace, 2, ..., King
 26..38 are hearts Ace, 2, ..., King
 39..51 are spades Ace, 2, ..., King

 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//do not remove
#include "include.code" //Include custom header file (it contains necessary functions)
//A version of the file:include.code is available from the assignment page
//as studentinclude.code which you should save locally as include.code
//include.code contains implementations for seed, instructions, and private_nextcard(int)
//used by shuffle and next card.
//The version used during testing is slightly different but will not affect your efforts.
//For testing you may modify studentinclude.code -- it will not be part of your submission.


// Function to shuffle the deck
//you should call this before each deal (including the first)
void shuffle() {
    private_nextcard(1); // Call a custom function to shuffle
}

// Function to get the next card to be dealt
//call this to deal a card. Do not call rand().
int nextcard() {
    return private_nextcard(0); // Call a custom function to get the next card
}

// Enumeration for different poker hands
enum hands { UNKNOWN, HIGHCARD, PAIR, TWOPAIR, TRIPS, STRAIGHT,
    FLUSH, FULLHOUSE, QUADS, STRAIGHTFLUSH, ROYALFLUSH };
char * handNames[] ={ "UNKNOWN", "HIGHCARD", "PAIR", "TWOPAIR", "TRIPS", "STRAIGHT",
    "FLUSH", "FULLHOUSE", "QUADS", "STRAIGHTFLUSH", "ROYALFLUSH" }; // Names of each hand

// Enumeration for card suits
enum suits {CLUB, DIAMOND, HEART, SPADE};
char * suitNames[] ={ "CLUB", "DIAMOND", "HEART", "SPADE"}; // Names of card suits

// Enumeration for card ranks
enum ranks {ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING};
char * rankNames[] ={ "ACE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN",
    "EIGHT", "NINE", "TEN", "JACK", "QUEEN", "KING"}; // Names of card ranks

//FUNCTION PROTOTYPES: YOU MUST IMPLEMENT THESE FUNCTIONS

// Function to get the rank of a card
enum ranks getrank(int card);

// Function to get the suit of a card
enum suits getsuit(int card);

// Function to evaluate the poker hand
enum hands eval(int []);

// Function to check for a royal flush
int royalflush(int []);

// Function to check for a straight flush
int straightflush(int []);

// Function to check for four of a kind
int fourofkind(int []);

// Function to check for a full house
int fullhouse(int []);

// Function to check for a flush
int flush(int []);

// Function to check for a straight
int straight(int []);

// Function to check for three of a kind
int threekind(int []);

// Function to check for two pairs
int twopair(int []);

// Function to check for a pair
int pair(int []);

void displayScore(int handNumber, int score, enum hands handType) {
    if (handType == TWOPAIR) {
printf("Hand %2d: Score: 7 TWOPAIR\n", handNumber + 1);
}
if (handType == PAIR) {
printf("Hand %2d: Score: 3 PAIR\n", handNumber + 1);
}
if (handType == STRAIGHTFLUSH) {
printf("Hand %2d: Score: 45 STRAIGHTFLUSH\n", handNumber + 1);
}
if (handType == FLUSH) {
printf("Hand %2d: Score: 26 FLUSH\n", handNumber + 1);
}
if (handType == ROYALFLUSH) {
printf("Hand %2d: Score: 50 ROYALFLUSH\n", handNumber + 1);
}
if (handType == QUADS) {
printf("Hand %2d: Score: 40 QUADS\n", handNumber + 1);
}
if (handType == TRIPS) {
printf("Hand %2d: Score: 11 TRIPS\n", handNumber + 1);
}
if (handType == STRAIGHT) {
printf("Hand %2d: Score: 17 STRAIGHT\n", handNumber + 1);
}
if (handType == FULLHOUSE) {
printf("Hand %2d: Score: 32 FULLHOUSE\n", handNumber + 1);
}
else{
printf("Hand %2d: Score: 1 HIGHCARD\n", handNumber + 1);
}
}

void updateScoreSheet(int scoreSheet[], int handNumber, int score) {
if (handNumber >= 0 && handNumber < 10) {
    scoreSheet[handNumber] = score;
}
}

int main(int argc, char ** argv) {
    //do not remove
    seed(argc, argv); // Seed the random number generator
    instructions(); // Display game instructions
    shuffle();

int totalScore=0;
int hand[5];
int scoreSheet[10];
int handNumber = 0; // Initialize the hand number

// Continue playing until you run out of hands

while (handNumber < 10) {
    for (int i = 0; i < 5; i++) {
        hand[i] = nextcard();
}
printf("Hand %d: ", handNumber + 1);

for (int i = 0; i < 5; i++) {
    printf("%s-%s\t", suitNames[getsuit(hand[i])], rankNames[getrank(hand[i])]);
}
printf("\n");

printf("Select up to three cards to replace [1-5] and press enter: ");
char input[32];

if (fgets(input, sizeof(input), stdin) == NULL) {
    printf("Error reading input.\n");
    continue;

}
char *token = strtok(input, " \n");
int numDraws = 0;
int drawCards[3];

while (token != NULL && numDraws < 3) {
    drawCards[numDraws++] = atoi(token);
    token = strtok(NULL, " \n");
}

for (int i = 0; i < numDraws; i++) {
    hand[drawCards[i] - 1] = nextcard();
}
printf("Hand %d: ", handNumber + 1);
for (int i = 0; i < 5; i++) {
    printf("%s-%s\t", suitNames[getsuit(hand[i])], rankNames[getrank(hand[i])]);
}
printf("\n");

int handScore = eval(hand);
enum hands handType = eval(hand); // Get the actual hand type

displayScore(handNumber, handScore, handType); // Pass the hand type
updateScoreSheet(scoreSheet, handNumber, handScore);

totalScore += handScore;

handNumber++;

}
printf("Total Points:      %d\n", totalScore);


return totalScore; // Return the total score

}


//TODO:
//THE FOLLOWING STUBS NEED TO BE IMPLEMENTED CORRECTLY

// Function to get the suit of a card
enum suits getsuit(int card){
    return (enum suits)(card / 13);
}

// Function to get the rank of a card
enum ranks getrank(int card){
    return (enum ranks)(card % 13);
}
// Function to evaluate the poker hand
enum hands eval(int hand[]){
    if (royalflush(hand)) return ROYALFLUSH;
    if (straightflush(hand)) return STRAIGHTFLUSH;
    if (fourofkind(hand)) return QUADS;
    if (fullhouse(hand)) return FULLHOUSE;
    if (threekind(hand)) return TRIPS;
    if (twopair(hand)) return TWOPAIR;
    if (pair(hand)) return PAIR;
    if (straight(hand)) return STRAIGHT;
    if (flush(hand)) return FLUSH;
    return HIGHCARD;
}

// Function to check for a royal flush
int royalflush(int hand[]){
    int suitCount[4] = {0};
    int rankCount[13] = {0};
    for (int i = 0; i < 5; i++) {
        int suit = getsuit(hand[i]);
        int rank = getrank(hand[i]);
        suitCount[suit]++;
        rankCount[rank]++;
    }
    int suitWithFiveCards = -1; // Initialize to an invalid suit
// Check for a suit with all five cards
for (int i = 0; i < 4; i++) {
    if (suitCount[i] == 5) {
        suitWithFiveCards = i;
        break;
    }
}
// Check if we have the required ranks for a Royal Flush in that suit
if (suitWithFiveCards != -1 && rankCount[TEN] && rankCount[JACK] && rankCount[QUEEN] && rankCount[KING] && rankCount[ACE]) {
    return 50; // Found a Royal Flush, return the score (50)
}
return 0;
}

// Function to check for a straight flush
int straightflush(int hand[]){
    int suitCount[4] = {0};
    int rankCount[13] = {0};
    for (int i = 0; i < 5; i++) {
        int suit = getsuit(hand[i]);
        int rank = getrank(hand[i]);
        suitCount[suit]++;
        rankCount[rank]++;
    }
    for (int i = 0; i < 4; i++) {
        if (suitCount[i] == 5) { // Check for a flush
        for (int j = 0; j < 9; j++) {
            if (rankCount[j] && rankCount[j + 1] && rankCount[j + 2] && rankCount[j + 3] && rankCount[j + 4]) {
                return 45; // Found a straight flush, return the score (45)
                }
            }
        }
    }
return 0;
}

// Function to check for a flush
int flush(int hand[]){
    int suitCount[4] = {0};
    for (int i = 0; i < 5; i++) {
        int suit = getsuit(hand[i]);
        suitCount[suit]++;
    }
    for (int i = 0; i < 4; i++) {
        if (suitCount[i] == 5) {
            return 26;
        }
    }
return 0;
}

// Function to check for a straight
int straight(int hand[]){
  int rankCount[13] = {0};
  for (int i = 0; i < 5; i++) {
    int rank = getrank(hand[i]);
    rankCount[rank]++;
    }
    for (int i = 0; i < 9; i++) {
        if (rankCount[i] && rankCount[i + 1] && rankCount[i + 2] && rankCount[i + 3] && rankCount[i + 4]) {
            return 17;
        }
    }
    if (rankCount[TWO] && rankCount[THREE] && rankCount[FOUR] && rankCount[FIVE] && rankCount[ACE]) {
        return 17;
    }
return 0;
}

// Function to check for four of a kind
int fourofkind(int hand[]){
    int rankCount[13] = {0};
    for (int i = 0; i < 5; i++) {
        int rank = getrank(hand[i]);
        rankCount[rank]++;
    }
    for (int i = 0; i < 13; i++) {
        if (rankCount[i] == 4) {
            return 40;
        }
    }
return 0;
}

// Function to check for a full house
int fullhouse(int hand[]){
    int rankCount[13] = {0};
    for (int i = 0; i < 5; i++) {
        int rank = getrank(hand[i]);
        rankCount[rank]++;
    }
    int threeKindRank = -1;
    int pairRank = -1;
    for (int i = 0; i < 13; i++) {
        if (rankCount[i] == 3) {
            threeKindRank = i;
        } else if (rankCount[i] == 2) {
            pairRank = i;
            }
    }
    if (threeKindRank != -1 && pairRank != -1) {
        return 32;
    }
return 0;
}

// Function to check for three of a kind
int threekind(int hand[]){
    int rankCount[13] = {0};
    for (int i = 0; i < 5; i++) {
        int rank = getrank(hand[i]);
        rankCount[rank]++;
    }
    int threeKindRank = -1;
    for (int i = 0; i < 13; i++) {
        if (rankCount[i] == 3) {
            threeKindRank = i;
            break;
        }
    }
    if (threeKindRank != -1) {
        return 11;
    }
return 0;
}

// Function to check for two pairs
int twopair(int hand[]){
    int rankCount[13] = {0};
    int pairCount = 0;
    for (int i = 0; i < 5; i++) {
        int rank = getrank(hand[i]);
        rankCount[rank]++;
        if (rankCount[rank] == 2) {
            pairCount++;
        }
    }
    if (pairCount == 2) {
        return 7;
    }
return 0;
}

// Function to check for a pair
int pair(int hand[]){
    int rankCount[13] = {0};
    for (int i = 0; i < 5; i++) {
        int rank = getrank(hand[i]);
        rankCount[rank]++;
    }
    for (int i = 0; i < 13; i++) {
        if (rankCount[i] == 2) {
            return 1;
        }
    }
return 0;
}