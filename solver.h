#ifndef SOLVER
#define SOLVER

#include <iostream>

class solver {
    
public:
    
                solver          ( void );
               ~solver          ( void );
    
    void        alloc           ( void );
    
    void        load_input      ( void );
    void        find_neigh      ( int  );
    void        apply_filter    ( int );
    
    void        save_best       ( int, int );
    void        start_bfs       ( int );
    
    void        solve           ( void );
    void        print           ( void );
    
private:
    int n;
    int k;
    
    int source;
    int destination;
    
    
    // variables for storing best solution
    int *       best_path;
    int         best_filter;
    int         best_map_len;
    int         best_lev_len;
    
    int         curr_lev_len;
    
    // variables for storing map representation and walktrough
    int *       map_origin;
    int *       map_filter;
    int *       visited;
    int *       depth;
    
    int *       lever;
    int **      lever_vector;
    
    my_queue    q;
};

solver::solver( void )
: n(0), k(0), source(0), destination(0), best_path(NULL), best_filter(0), best_map_len(-1), best_lev_len(0), curr_lev_len(0),

  map_origin(  NULL),
  map_filter(  NULL),
  visited(     NULL),
  depth(       NULL),
  lever(       NULL),
  lever_vector(NULL) { }

solver::~solver ( void )
{
    delete map_origin;
    delete map_filter;
    delete visited;
    delete depth;
    delete best_path;
    
    if (k)
    {
        delete lever;
        
        for (int i = 0; i < k; i++)
            delete [] lever_vector[i];
        delete [] lever_vector;
    }
}


void solver::alloc( void ) {
    
    map_origin = new int [n * n];
    map_filter = new int [n * n];
    visited    = new int [n * n];
    depth      = new int [n * n];
    best_path  = new int [n * n];
    
    if (k)
    {
        lever = new int [k];
        lever_vector = new int * [k];
        
        for (int i = 0; i < k; i++)
            lever_vector[i] = new int [n];
    }
    
    q.create( n * n );
}

void solver::load_input( void ) {
    
    char c;
    
    std::cin >> n >> k; alloc();
    
    for (int i = 0; i < k; i++) {
        
        std::cin >> lever[i];
        
        for (int j = 0; j < n; j++)
        {
            std::cin >> c;
            lever_vector[i][j] = (int)c - '0';
        }
    }
    
    // turned aroudn because of my imagination
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = 0; j < n; j++)
        {
            std::cin >> c;
            map_origin[ i * n + j ] = (int)c - '0';
            visited[ i * n + j ] = -1;
        }
    }
    
    source = (n - 1) * n;
    
    int x, y;
    
    std::cin >> x >> y;
    
    destination = (n - y) * n + x - 1;
}

void solver::find_neigh( int position )
{
    if ( position >= n && map_filter[position - n] == 0 && visited[position - n] == -1 && (position - n != (n - 1) * n ) ) // cam go up
    {
        visited[position - n] = position;
        depth[position - n] = depth[position] + 1;
        q.enqueue( position - n );
    }
    
    if ( position % n != n - 1 && map_filter[position + 1] == 0 && visited[position + 1] == -1 && (position + 1 != (n - 1) * n ) ) // can go right
    {
        visited[position + 1] = position;
        depth[position + 1] = depth[position] + 1;
        q.enqueue( position + 1 );
    }
    
    if ( position < (n - 1) * n && map_filter[position + n] == 0 && visited[position + n] == -1 && (position + n != (n - 1) * n ) ) // can go down
    {
        visited[position + n] = position;
        depth[position + n] = depth[position] + 1;
        q.enqueue( position + n );
    }
    
    if ( position % n != 0 && map_filter[position - 1] == 0 && visited[position - 1] == -1 && (position - 1 != (n - 1) * n ) ) // can go left
    {
        visited[position - 1] = position;
        depth[position - 1] = depth[position] + 1;
        q.enqueue( position - 1 );
    }
}

void solver::apply_filter ( int filter )
{
    int len_to_lever   = 0; // lenght to pull farthest lever
    int len_minus_one  = 0; // lenght plus two if lever at -1
    
    for ( int i = 0; i < n * n; i++ ) map_filter[i] = map_origin[i];
    
    // calculate the lever distance
    for ( int lever_i = k - 1; lever_i >= 0; lever_i-- ) {
        
        if (filter & (1 << lever_i)) // if lever is used in filter
        {
            if (len_to_lever < 2 * lever[lever_i] && lever[lever_i] != -1) // save the most distant lever
                len_to_lever = 2 * lever[lever_i];
            
            if (lever[lever_i] == -1 ) // save if lever at -1 is used
                len_minus_one = 2;
            
            // XOR
            for ( int i = 0; i < n; i++ )
            {
                for ( int k = 0; k < n; k++ )
                {
                    if (!map_filter[i * n + k] != !lever_vector[lever_i][k] ) map_filter[i * n + k] = 1;
                    else map_filter[i * n + k] = 0;
                }
            }
        }
    }
    
    curr_lev_len = len_to_lever + len_minus_one;
}

void solver::save_best( int filter, int map_len ) {
    
    best_filter  = filter;
    best_map_len = map_len;
    best_lev_len = curr_lev_len;
    
    int tmp = destination;
    
    for ( int i = 0; visited[tmp] != -1; i++ )
    {
        best_path[i] = tmp;
        tmp = visited[tmp];
    }
}

void solver::start_bfs( int filter )
{
    apply_filter( filter );
    depth[source] = 0;
    
    if (map_filter[ source ] == 1) return;
    
    q.enqueue( source );
    
    int current;
    
    while ( ! q.is_empty() )
    {
        current = q.dequeue();
        
        if (current == destination && depth[current] != -1 &&
            (depth[current] + curr_lev_len < best_map_len + best_lev_len || best_map_len == -1)) {
            
            save_best(filter, depth[current]);
        }
        
        find_neigh( current );
    }
    
    return;
}

void solver::solve( void ) {
    
    load_input();
    
    // for all lever combinations
    for (int i = 0; i < 1<<k; i++) {
        
        // reset visited
        for ( int v = 0; v < n * n; v++ )
            visited[v] = -1;
        
        start_bfs(i);
    }
}

void solver::print( void ) {
    
    std::cout << best_map_len + best_lev_len << std::endl;
    
    if ( best_map_len < 0 ) return;
    
    for ( int i = 0; i < k; i++ )
    {
        if ( best_filter & (1<<i) )
            std::cout << "1";
        else
            std::cout << "0";
    }
    
    if (k)
        std::cout << std::endl;
    
    std::cout << "[1;1]";
    
    for ( int i = best_map_len; i > 0; i-- )
        std::cout << ",[" << (best_path[i-1] % n) + 1 << ";" << n - (best_path[i-1]/n) << "]";
    std::cout << std::endl;
}

#endif
