# Spacer
#

# -----------------------------------
# Takes an essay document of with no spaces and uses dynamic programming
# to readd the spaces such that the entire essay ends up with the correct 
# spaces at the right places

import random
import string

WORDLIST_FILENAME = "words.txt"

def loadWords():
    """
    Returns a list of valid words. Words are strings of lowercase letters.
    
    Depending on the size of the word list, this function may
    take a while to finish.
    """
    print "Loading word list from file..."
    # inFile: file
    inFile = open(WORDLIST_FILENAME, 'r', 0)
    # line: string
    line = inFile.readline()
    # wordlist: list of strings
    wordlist = string.split(line)
    print "  ", len(wordlist), "words loaded."
    return wordlist

def spacer ():
	# get words
    words = loadWords()
    # get doc
    doc_path = raw_input("file name?: ")
    doc = open(doc_path, 'r', 0)
    essay = doc.read()
    # D[j] implies that chars 1-j is a valid collection of words
    D, F = [], []
    print essay
    essay_length = len(essay)
    for x in range(essay_length):
        D.append(False)
        F.append(False)
    # D[j] stores whether chars 1-j form a valid cluster of words
    # We will first check D[1] and then D[1...j], if it is valid cluster we set D(j) = True
    # To check further we loop through each k such that D[1...k] is true and D[k+1,j] belongs in dictionary
    for j in range(1, essay_length + 1):
        if essay[:j] in words:
            D[j] = True
            F[0] = essay[:j]
            for each in range(1, j):
                F[each] = False
        else:
            for k in range(1, j):
                if D[k] and (essay[k:j] in words):
                    D[j] = True
                    F[k] = essay[k:j]
                    for each in range(k+1, j):
                        F[each] = False
                    break                                                       
    fixed = []
    for each in F:
        if each:
            fixed.append(each)
    print D
    print F
    print fixed
                    
                  
                
        
