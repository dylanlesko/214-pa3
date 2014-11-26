214-pa3
=======

Assignment 3: Indexer

###Version
1.0

###Introduction
In this assignment you will practice using the file system API (as well as pointers in
different data structures). In particular you will be creating, opening, reading,
writing, and deleting files.

Your task is to write an indexing program, called an indexer. Given a set of files, an
indexer will parse the files and create an inverted index, which maps each token
found in the files to the subset of files that contain that token. In your indexer, you
will also maintain the frequency with which each token appears in each file. 

###Invocation
    make
    ./index <outputfile> <dir to read>
