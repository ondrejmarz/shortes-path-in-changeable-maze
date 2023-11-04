#ifndef MY_QUEUE
#define MY_QUEUE

#include <cstdlib>

class my_queue {
    
public:
                my_queue            ( const int );
               ~my_queue            ( void );
    
    void        enqueue             ( const int );
    int         dequeue             ( void );
    
private:
    
    unsigned    capacity;
    unsigned    size;
    
    int         front;
    int         rear;
    int *       queue;
};

my_queue::my_queue( const int cap ): capacity(cap), size(0), front(0), rear(-1) {
    
    queue = new int [capacity];
}

my_queue::~my_queue( void ) {
    
    delete queue;
}

void my_queue::enqueue( const int value ) {
    
    rear = ( (rear + 1) % capacity );
    queue[rear] = value;
    size++;
}

int my_queue::dequeue( void ) {
    
    if (size == 0) return -1;
    
    int dequeued = queue[front];
    front = ((front + 1) % capacity);
    size--;
    
    return dequeued;
}

#endif
