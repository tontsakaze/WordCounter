# WordCounter
Program that reads textfile and counts the number of times words appear in it

* Runnable from command line or from .exe
* Uses static hashtable(100000) to store data of words and their count
* User can decide how many top words are printed and in which order
* Data Structures & Algorithm -course assignment
- - -
# How to Use
* Run program from .exe -file or from command line.
* If ran from command line, user can give max. three agruments:
<pre>
1. Path of the file
2. Number of printed words
3. "+" / "-" | In ascending/descending order

Example: 
WordCounter.exe examples/small.txt 10 -
</pre>

- - -
# Example (command line) "WordCounter.exe examples/small.txt 10 -"
<pre>
= = = = = = = = = = = = = = = = = = = = = = =
WORD COUNTER by Toni "tontsakaze" Torvela
- - - - - - - - - - - - - - - - - - - - - - -
Opening file: "examples/small.txt"
- - - - - - - - -
Begin counting words from file...DONE
Begin sorting words...DONE
- - - - - - - - -
Total number of words = 2587
Number of different words = 223
The 10 most common words:
WORD            NUMBER OF OCCURRENCIES
THE             108
AND             96
OF              78
IN              78
CHAPTER         72
FROM            60
PASSAGES        42
INHERITANCE     42
PROGRAMMING     42
TO              42
- - - - - - - - -
Counting and ordering took 0.00800 seconds.
--> 323375.0 words per second. (2587 counted words)

...
</pre>
- - -

# Example (.exe -file)
<pre>
= = = = = = = = = = = = = = = = = = = = = = =
WORD COUNTER by Toni "tontsakaze" Torvela
- - - - - - - - - - - - - - - - - - - - - - -
Filename:
> examples/WarPeace.txt
Opening file: "examples/WarPeace.txt"
- - - - - - - - -
How many top words will be printed?
> 10
Top words in ascending order from least used to most? (y/n)
> n
- - - - - - - - -
Begin counting words from file...DONE
Begin sorting words...DONE
- - - - - - - - -
Total number of words = 556045
Number of different words = 18150
The 10 most common words:
WORD            NUMBER OF OCCURRENCIES
THE             34262
AND             21825
TO              16633
OF              14963
A               10423
HE              9610
IN              8756
HIS             7956
THAT            7709
WAS             7325
- - - - - - - - -
Counting and ordering took 0.57400 seconds.
--> 968719.5 words per second. (556045 counted words)

...
</pre>
- - -
