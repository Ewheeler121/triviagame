This is a fork of TronNerd82's triviagame.
It's a full rewrite of the trivia.c that stores all inputs dynamically, so
we don't have to store things in a fixed buffer. The README below has some
lines removed to reflex the changes.

This is a simple trivia game written in C.

Provided in this program are 20 trivia questions, one of which will
automatically win the game should it be answered correctly. To add or remove
any questions and/or answers, simply edit the according questions.txt or
answers.txt files, with each question recieving its own line, and the
corresponding answer being on the same line in its respective file.

Example:
	In questions.txt, line 1 reads:
	"What is the capital or Argentina ???"

	In answers.txt, the answer to that question is also on line 1.

Questions are shuffled using the Fisher-Yates algorithm.
Some of these questions are rather strange or obscure, so feel free to change
the questions to something you and your friends will understand as you please.
Just make sure to change the answers along with them. ;)

To compile the game, simply run:
	gcc -Wall trivia.c -o trivia

Have fun! :)
