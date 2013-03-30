4dim
6.18712
10.389
17.2315
28.5261
47.2399
78.2535
130.212
217.176
362.957
604.499
1011.04
1693.59

3dim
4.55684
7.22258
11.3082
17.6495
27.6071
43.3885
68.2806
107.303
169.201
267.737
422.663
668.96

2dim 
2.75087
3.90444
5.46304
7.63986
10.6942
14.9946
21.0476
29.5549
41.8111
59.0915
83.2272
117.602

0dim 
1.20651
1.22657
1.23588
1.23897
1.24269
1.25643
1.25824
1.26168
1.26917
1.26722
1.27551
1.27421
//TODO: pruning
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/random/uniform_01.hpp>
#include <sstream>
#include <iostream>
#include <vector>
#include <iterator>

#define pair std::pair <float, unsigned long>

using namespace std;

class BinaryHeap {
    public:
        BinaryHeap(unsigned long numpoints);
        ~BinaryHeap();
        void push(pair element);
        pair pop();
        void print();
        int size() 
        { 
            return heap.size(); 
        }
    private:
        int left(int parent);
        int right(int parent);
        int parent(int child);
        void heapifyup(int current);
        void heapifydown(int current);
    private:
        vector<pair> heap;
};

// Instantiates Binary Heap
BinaryHeap::BinaryHeap(unsigned long numpoints)
{
    heap = vector<pair>(numpoints);
}

// virtual for Binary Heap
BinaryHeap::~BinaryHeap()
{
}

/* * * * * *
 * push(pair element): pushes the element
 * into the heap 
 * * * * * */
void BinaryHeap::push(pair element)
{
    heap.push_back(element);
    heapifyup(heap.size() - 1);
}

/* * * * * *
 * pop(): returns the minimum element, which is
 * located at the root of the tree
 * * * * * */
pair BinaryHeap::pop()
{
    pair min = heap.front();
    heap[0] = heap.at(heap.size() - 1);
    heap.pop_back();
    heapifydown(0);
    return min;
}

/* * * * * *
 * print(): prints our current heap
 * * * * * */


void BinaryHeap::print()
{

    vector<pair>::iterator pos = heap.begin();
    cout << "Heap = ";
    while ( pos != heap.end() ) {
        cout << (*pos).first << " ";
        ++pos;
    }
    cout << endl;

}


/* * * * * *
 * When you add an element to the heap, we want to
 * insert it in the last spot and then move it upwards
 * by comparing to parent nodes, if smaller then 
 * swapping occurs, this is repeated until in order. 
 * * * * * */
void BinaryHeap::heapifyup(int current)
{    
    while ( ( current > 0 ) && ( parent(current) >= 0 ) &&
            ( heap[parent(current)].first > heap[current].first ) )
    {
        pair temp = heap[parent(current)];
        heap[parent(current)] = heap[current];
        heap[current] = temp;
        current = parent(current);
    }
}

/* * * * * *
 * When you remove an element from the heap
 * we want to maintain the structure of the heap
 * so we move everything down a spot by comparing
 * the key of the parent node with the children, if 
 * children have lower priority, it is swapped, and is 
 * repeated for newly swapped nodes until heap is
 * re-established 
 * * * * * */
 
void BinaryHeap::heapifydown(int current)
{
    int child = left(current);
    if ( ( child > 0 ) && ( right(current) > 0 ) &&
         ( heap[child].first > heap[right(current)].first ) )
    {
        child = right(current);
    }
    if ( child > 0 )
    {
        pair temp = heap[current];
        heap[current] = heap[child];
        heap[child] = temp;
        heapifydown(child);
    }
}

int BinaryHeap::left(int parentIndex)
{
    int i = ( parentIndex << 1 ) + 1; // Arithmetic calculation described on wikipedia: 2 * parent + 1
    return ( i < heap.size() ) ? i : -1;
}

int BinaryHeap::right(int parent)
{
    int i = ( parent << 1 ) + 2; // Arithmetic calculation described on wikipedia: 2 * parent + 2
    return ( i < heap.size() ) ? i : -1;
}

int BinaryHeap::parent(int child)
{
    if (child != 0)
    {
        int i = (child - 1) >> 1;
        return i;
    }
    return -1;
}

int main(int argc, char *argv[]) {
    const rlim_t kStackSize = 67104768;//16 * 1024 * 1024;   // min stack size = 16 MB
    struct rlimit rl;
    int result;

    result = getrlimit(RLIMIT_STACK, &rl);
    if (result == 0)
    {
        if (rl.rlim_cur < kStackSize)
        {
            rl.rlim_cur = kStackSize;
            result = setrlimit(RLIMIT_STACK, &rl);
            if (result != 0)
            {
                fprintf(stderr, "setrlimit returned result = %d\n", result);
            }
        }
    }
    
    // check arguments
    if (argc != 5) {
        std::cout << "Usage: randmst <debug flag> <numpoints> <numtrials> <dimension>";
        return 0;
    }

    // parse arguments
    unsigned long numpoints;
    std::istringstream(argv[2]) >> numpoints;
    unsigned long numtrials;
    std::istringstream(argv[3]) >> numtrials;
    unsigned short dimension;
    std::istringstream(argv[4]) >> dimension;

    // declare edge weight array
    ///float distances[numpoints][numpoints];

    // declare array whose elements indicate whether each node is in our growing tree
    bool intree[numpoints];

    // declare array for minimum distance between growing tree and remaining nodes
    float mindist[numpoints];
    
    // initialize random number generator
    boost::mt19937 rng;
    rng.seed(std::time(NULL) + getpid());
    float min = 0.0;
    float max = 1.0;
    boost::uniform_real<float> u(min, max);
    boost::variate_generator<boost::mt19937&, boost::uniform_real<float> > gen(rng, u);

    // declare total weight counter
    float totalweight;

    // initialize total weight over trials counter
    float weightsum = 0.0;
    
    switch (dimension){
        case 0: // random edge weights
            for (unsigned long t = 0; t < numtrials; t++) {
                BinaryHeap heap = BinaryHeap(numpoints);
                std::fill_n(intree, numpoints, false);
                std::fill_n(mindist, numpoints, 3.0); // the maximum possible distance in the dimensions we're dealing with is 2

                // size of MST
                totalweight = 0.0;
                
                // Prim's algorithm
                heap.push(std::make_pair(0.0, 0));
                unsigned long connected = 0;
                while (connected < numpoints) {
                    pair p = heap.pop();
                    if (!intree[p.second]) {
                        intree[p.second] = true;
                        totalweight += p.first;
                        
                        // distance from node p.second to each other node
                        for (unsigned long j = 0; j < numpoints; j++) {
                            if (!intree[j]) {
                                float distance = gen();
                                if (distance < mindist[j]) {
                                    mindist[j] = distance;
                                    heap.push(std::make_pair(distance, j));
                                }
                            }
                        }
                        connected++;
                    }
                }
                weightsum += totalweight;
                //heap.print();
            }
            std::cout << weightsum / numtrials << std::endl;

            break;
        case 2: // square
            for (unsigned long t = 0; t < numtrials; t++) {
                BinaryHeap heap = BinaryHeap(numpoints);
                std::fill_n(intree, numpoints, false);
                std::fill_n(mindist, numpoints, 3.0); // the maximum possible distance in the dimensions we're dealing with is 2

                // size of MST
                totalweight = 0.0;
                
                // declare arrays for w x y z coordinates of each node
                float x[numpoints];
                float y[numpoints];
                
                // randomly assign positions to each node
                for (unsigned long i = 0; i < numpoints; i++) {
                    x[i] = gen();
                    y[i] = gen();
                }
                
                // Prim's algorithm
                heap.push(std::make_pair(0.0, 0));
                unsigned long connected = 0;
                while (connected < numpoints) {
                    pair p = heap.pop();
                    if (!intree[p.second]) {
                        intree[p.second] = true;
                        totalweight += p.first;
                        
                        // distance from node p.second to each other node
                        for (unsigned long j = 0; j < numpoints; j++) {
                            if (!intree[j]) {
                                float xdiff = x[p.second] - x[j];
                                float ydiff = y[p.second] - y[j];
                                float distance = xdiff*xdiff + ydiff*ydiff; // technically distance squared, but it doesn't matter since the relative priorities remain the same
                                if (distance < mindist[j]) {
                                    mindist[j] = distance;
                                    heap.push(std::make_pair(distance, j));
                                }
                            }
                        }
                        connected++;
                    }
                }
                weightsum += totalweight;
                //heap.print();
            }
            std::cout << weightsum / numtrials << std::endl;
            
            break;
        case 3: // cube
            break;
        case 4: // hypercube
            break;
    }
    
    return 0;
}
