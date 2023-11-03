#ifndef MY_QUEUE
#define MY_QUEUE

template< typename T, size_t N >

class my_queue {
    
public:
    my_queue() noexcept;
   ~my_queue();
    
    void add( const T& value );
    
private:
    
    unsigned capacity;
    unsigned size;
    
    int front;
    int rear;
    T * queue;
};

template <typename T>
void my_queue::add( const T& value ) {
    
    if (capacity == m_size) reserve(capaccity ? capacity * 2 : 1);
    
    rear = ( (rear + 1) % capacity );
    new (queue + rear) T (value);
    size++;
}

#endif
