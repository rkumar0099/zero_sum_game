# zero_sum_game
Alice picks a sequence (x1, x2, x3) of 3 numbers from the set S = {-1, 0, 1}, Bob picks two
positions i < j in the sequence. Alice and Bob simultaneously reveal their choices to one
another and s dollars are transferred from Alice to Bob, where s is the unique value in S that
is congruent to xj - xi modulo 3. For example, if Alice picks (1, -1, 1) and Bob picks 2 < 3
then Alice pays Bob x3 - x2 = 2 = 2 - (-1) mod3 congruent -1 dollars, that is she earns one dollar from Bob.
Alice's strategy is to choose her sequence at random so that her expected earnings are maxi-
mizes, regardless of Bob's choice. How much probability should she assign to each sequence?

A code to calculate all the sequences that give alice postive earnings, and we remove all those sequence from the set and assign equal probability to the remaining sequences.

However, in order to gain some insight into the problem, the extension version of the problem had been tried by us that is we chose Set S = {-2, -1, 0, 1, 2} and then calculate 
expected earnings on mod5. The code given calculates all possible sequences. 
