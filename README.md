Dynamic Position Heap
=====================

Description
------------
A Dynamic implementation of a Position Heap for string indexing and pattern search on a collection of strings,
based on Ross McConell's: http://www.cs.colostate.edu/PositionHeaps/

How to Use
-----------
Execute the main file and you'll get a menu asking to choose one of the following options:
``
         0. Quit
         1. Insert String
         2. Delete String
         3. Find positions of a pattern in the strings
         4. Print nodes of the heap
         5. Graph heap
```

* Option 0 stops the interaction with the structure.
* Option 1 inserts a string in the structure.
* Option 2 given an ID, deletes the string who's represented by it.
* Option 3 first shows all the strings in the heap with their IDs. Later receives a pattern, returning a list containing pairs where the first number represents the string ID and the second one the position where it begins on that string.
* Option 4 prints a list of all the nodes in the structure, following the next format (ID, position).
* Option 5 writes on the file tree.txt Graphviz code that allows you to see the Heap (black lines are the normal edges, red ones are the Maximal-Reach pointers). You can paste the code on http://www.webgraphviz.com/ to get the Heap.

Example
-------
* If first we insert a string we must choose the option 1 and then type for example `abaa` will get the message: `Inserted with ID: 1` then if we Graph the Heap we'll get:

<p align="center">
  <img src="https://github.com/tmunoz/Position-heap/blob/master/exampleIMG/ex1.png">
</p>

* Let's say that now we want to insert `babb` as you may notice will get the message: `Inserted with ID: 2` and if we Graph it:

<p align="center">
  <img src="https://github.com/tmunoz/Position-heap/blob/master/exampleIMG/ex2.png">
</p>

* What if we want to search for the pattern `ba`, we must choose option `3` and type `ba` we will see the following list:
```The strings in the heap are:
    1. abaa$1
    2. babb$2

The positions of the pattern are:
    2, 1
    1, 2
```

If we look the strings on our structure based for example on the first of the positions found `(2, 1)` and we now go to the string `2`: `babb` we can see that on the position `1` there is a letter `b` and the next letter is an `a` so the position `1` is where the pattern starts in the string `2`.

* Now if we want to delete a string, we must choose option `2` and then type the string ID for example `1`, this will delete the string `abaa` and if we Graph the resultant structure we will get:

<p align="center">
  <img src="https://github.com/tmunoz/Position-heap/blob/master/exampleIMG/ex3.png">
</p>

* Notice that if we now insert a string we'll get the ID `1` instead of `3` because we deleted string `1` before so its ID is available. Let's insert the string `ab` and then search for the pattern `ab` giving the next graph:

<p align="center">
  <img src="https://github.com/tmunoz/Position-heap/blob/master/exampleIMG/ex4.png">
</p>

