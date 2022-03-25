Format of input file(example)

Line1:<Algo_code>    # ‘1’ for best first search, ‘2’ for hill climbing
Line2:b c a          #stack 1 of start state
Line3:e d	     #stack 2 of start state
Line4:f		     #stack 3 of start state
Line5:a b d	     #stack 1 of goal state
Line6:f e	     #stack 2 of goal state
Line7:c		     #stack 3 of goal state


Command:
python 3.py <input_filename.txt>