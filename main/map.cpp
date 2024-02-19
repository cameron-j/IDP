#include "map.h"

#define START_IDX 0
#define D1_IDX 1
#define D2_IDX 2
#define B1_IDX N_DROPOFFS+1
#define B2_IDX N_DROPOFFS+2
#define B3_IDX N_DROPOFFS+3
#define B4_IDX N_DROPOFFS+4
#define J1_IDX N_DROPOFFS+N_BLOCKS+1
#define J2_IDX N_DROPOFFS+N_BLOCKS+2
#define J3_IDX N_DROPOFFS+N_BLOCKS+3
#define J4_IDX N_DROPOFFS+N_BLOCKS+4
#define J5_IDX N_DROPOFFS+N_BLOCKS+5
#define J6_IDX N_DROPOFFS+N_BLOCKS+6
#define J7_IDX N_DROPOFFS+N_BLOCKS+7
#define J8_IDX N_DROPOFFS+N_BLOCKS+8
#define J9_IDX N_DROPOFFS+N_BLOCKS+9
#define J10_IDX N_DROPOFFS+N_BLOCKS+10
#define J11_IDX N_DROPOFFS+N_BLOCKS+11

MapNode create_map_node(unsigned char type) {
    MapNode new_node;
    new_node.type = type;
    new_node.id = ++node_count; // First node id is 1 so that 0 can be used as null (no node)
    return new_node;
}

MapNode get_map_node(unsigned char id) {
    return nodes[id - 1];
}

void connect_map_nodes(unsigned char n1_idx, unsigned char n2_idx, unsigned int dist, char dir12, char dir21=0) {
    adj_matrix[nodes[n1_idx].id][nodes[n2_idx].id].dist = dist;
    adj_matrix[nodes[n1_idx].id][nodes[n2_idx].id].dir = dir12;
    adj_matrix[nodes[n2_idx].id][nodes[n1_idx].id].dist = dist;
    if (dir21 == 0) {
        adj_matrix[nodes[n2_idx].id][nodes[n1_idx].id].dir = -dir12;
    }
    else {
        adj_matrix[nodes[n2_idx].id][nodes[n1_idx].id].dir = dir21;
    }
}

void setup_map() {
    // Creates the nodes
    node_count = 0;
    int idx = 0;
    nodes[idx++] = create_map_node(S_NODE);

    for (int _ = 0; _ < N_DROPOFFS; _++) {
        nodes[idx++] = create_map_node(D_NODE);
    }

    for (int _ = 0; _ < N_BLOCKS; _++) {
        nodes[idx++] = create_map_node(B_NODE);
    }

    for (int _ = 0; _ < N_JUNCTIONS; _++) {
        nodes[idx++] = create_map_node(J_NODE);
    }

    // Connects the nodes
    connect_map_nodes(START_IDX, J3_IDX, 30, FORWARDS);
    connect_map_nodes(D1_IDX, J1_IDX, 30, FORWARDS);
    connect_map_nodes(D2_IDX, J4_IDX, 30, FORWARDS);
    connect_map_nodes(J1_IDX, J2_IDX, 70, RIGHT);
    connect_map_nodes(J2_IDX, J3_IDX, 30, RIGHT);
    connect_map_nodes(J3_IDX, J4_IDX, 100, RIGHT);
    connect_map_nodes(J2_IDX, B1_IDX, 30, FORWARDS);
    connect_map_nodes(J1_IDX, J8_IDX, 85, FORWARDS);
    connect_map_nodes(J4_IDX, J5_IDX, 85, FORWARDS);
    connect_map_nodes(B2_IDX, J6_IDX, 30, FORWARDS);
    connect_map_nodes(J8_IDX, J7_IDX, 100, RIGHT);
    connect_map_nodes(J7_IDX, J6_IDX, 30, RIGHT);
    connect_map_nodes(J6_IDX, J5_IDX, 70, RIGHT);
    connect_map_nodes(J8_IDX, J10_IDX, 170, FORWARDS, LEFT);
    connect_map_nodes(J10_IDX, J11_IDX, 40, RIGHT);
    connect_map_nodes(J11_IDX, J5_IDX, 130, RIGHT, BACKWARDS);
    connect_map_nodes(B4_IDX, J9_IDX, 40, RIGHT);
    connect_map_nodes(B3_IDX, J11_IDX, 35, FORWARDS);
    connect_map_nodes(J7_IDX, J9_IDX, 35, FORWARDS);
    connect_map_nodes(J9_IDX, J10_IDX, 35, FORWARDS);
}

void initialise_robot() {
    prev_state.position = 1; // 1 is the id of the start node
    prev_state.direction = FORWARDS;
}

void map_init() {
    setup_map();
    initialise_robot();
}
