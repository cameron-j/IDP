#pragma once

#define N_NODES 18 // Number of nodes in entire map
#define N_JUNCTIONS 11
#define N_BLOCKS 4
#define N_DROPOFFS 2

// Node types
#define D_NODE 0 // Dropoff point
#define S_NODE 1 // Start/finish
#define J_NODE 2 // Junction
#define B_NODE 3 // Block

// Directions in reference frame of table
#define FORWARDS 1
#define RIGHT 2
#define LEFT -2
#define BACKWARDS -1

namespace map {
    // Distance and direction for movement between nodes
    typedef struct Displacement_s {
        unsigned int dist;
        char dir;
    } Displacement;

    // State of the robot at a node
    typedef struct State_s {
        unsigned char position; // Node ID
        char direction;
    } State;

    // Data stored about each node on the map
    typedef struct Node_s {
        unsigned char type; // Type of node (D, S, J, B)
        unsigned char id; // unique node id (starts from 1, 0 is null)
    } Node;

    static State prev_state;
    static State next_state;

    static unsigned char node_count;

    // Start, dropoffs, blocks then junctions
    static Node nodes[N_NODES];
    static Displacement adj_matrix[N_NODES][N_NODES];

    Node create_node(unsigned char type);
    Node get_node(unsigned char id);
    void connect_nodes(unsigned char n1_idx, unsigned char n2_idx, unsigned int dist, char dir12, char dir21);
    void setup_map();
    void initialise_robot();
    void init();
}
