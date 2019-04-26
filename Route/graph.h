
struct Anode{
    int nodeId;
    struct Anode* nextAnode;
    double length;
};
typedef struct Anode Anode;

struct Snode{//start node
    int nodeId;
    Anode* anode;
    struct Snode* nextSnode;
    int visit;//if it has been visited
    int lastId;//the id of the last node
    float dist;//the distance from the strat point
};
typedef struct Snode Snode;



typedef struct {
    int Ne;
    int Nv;
    Snode* snode;

}Graph;


typedef struct {
    int idV1;
    int idV2;
    float length;
}Edge;

struct Node{
    int id;
    float lat;
    float lon;
    struct Node* nextNode;
};
typedef struct Node Node;

Anode* createheadA();
Snode* createheadS();
int ExistSnode ();
int ExistAnode ();
Graph* CreateGraph ();
Graph* InsertEdge ();
