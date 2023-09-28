# Hangman
This Program is written in C - Lang with some unreal cheat rules designed specifically for the game designer.

### How to Run
```
gcc Hangman.c -o game
./game
```

### Rules
* Designer will enter the length of the word to be guessed as well as the no of guesses for the player based on the complexity of the word to be guessed.
* Program will read all words of length L from dict.txt
* At start designer will not have selected any word just the length of the word
* Word_array from dict.txt will be divided into word_length+1 subarrays based on index of guessed letter in each word + an array that does not contain any words containing the guesses letter.
* As user will enter the guess, designer will select teh sub catogory to select the word from that may or may not contain the letter player guessed. 
* Game will go on untill the guesses are finished or the player has guessed the char correctly.

### Note
<strong>To print all the functioning or say original word array and subarrays at each guess or iteration, uncomment the code commented and wrapped in '-' & its explaination.<strong>