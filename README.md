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

# Number Letter Mapper (Poosible Combo Checker)

### How to Run
* In read_dictionary File change the anme of dictionary file to either one in the zipped folder (UPPERCASE or newdict) or use your own. If you are using your own dictionary make sure each line contains only 1 word.

```
usage : ./object file <total number of numbers> total_num *[numbers]
```
```
gcc Mapper.c -o ./map<br>
./map 1 12 123
```
The above command will print all the possible combinations of words having 2 and 3 letters
* Keep in mid that the output of the program totally depends on the worth of the device it is running on. 
* It may malfunction sometime due to overwhelmingly large number of combinations that normal laptops cannot handle.
* Therefore using too many argument like more than 2 or 3 or using large length arguments like length of 5 or 6 can take upto 24 hours of time to print the output due to that many permutations. Hence, use small arguments like the one in the example above.