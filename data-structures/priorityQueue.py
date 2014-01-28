# PriorityQueue
#

# -----------------------------------
# Priority Queue: Binary Heap
# Implemented using a binary heap; stored as a dictionary.

class binary_heap(dict):
    # constructor
    def __init__(self):
        self.__heap = []
        dict.__init__(self)
        
    # deletemin to find and delete min from heap
    def deletemin(self):
        float min = heap.front().first;
        heap[0] = heap.at(heap.size() - 1);
        heap.pop_back();
        heapifydown(0);
        return min;
