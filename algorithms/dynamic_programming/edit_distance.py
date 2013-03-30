# Edit Distance
#

# -----------------------------------
# Takes two words (and optional cost for iNsert, Delete, and Change
# and calculates the edit distance between changing word 1 into word 2

def edit_distance (word1, word2, n=1, d=1, c=1):
    w1 = " " + word1
    w2 = " " + word2
    len1, len2 = len(word1), len(word2)
    # D is a 2-D array with D[i][j] represents the edit distance between
    # A[1...i] and B[1..j]
    D = []
    for x in range(len1 + 1):
        D.append([x])
        for y in range(1, len2 + 1):
            if x == 0:
                D[x].append(y)
            else:
                D[x].append(0)
    for i in range(1, len1 + 1):
        for j in range(1, len2 + 1):
            if w1[i] == w2[j]:
                D[i][j] = D[i-1][j-1]
            else:
                # D[i-1,j] + d is A[1..i] map int B[1..j] and then deleted
                # D[i][j-1] + n is A[1..i] map into B[1..j-1] and then inserted
                # D[i-1][j-1] + c is A[1..i-1] map into B[1..j-1] and then changed
                D[i][j] = min(D[i-1][j] + d, D[i][j-1] + n, D[i-1][j-1] + c)
    print D[len1, len2]
