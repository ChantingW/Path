#include <stdio.h>
#include <stdlib.h>

struct Anode{
    int nodeId;
    struct Anode* nextAnode;
    double length;
}; //heng lianbiao dierbufen
typedef struct Anode Anode;

struct Snode{//start node
    int nodeId;
    Anode* anode;
    struct Snode* nextSnode;
}; //heng lianbiao diyibufen
typedef struct Snode Snode;

/*typedef struct {
    Snode* thisSnode;
    Nodes* nextSnode;
}Nodes; //shu lianbiao*/


typedef struct {
    int Ne;
    int Nv;
    Snode* snode;

}Graph;


typedef struct {
    int idV1;
    int idV2;
    double length;
}Edge;


Anode* createheadA()
{
    Anode* headA=(Anode*)malloc(sizeof(Anode));
    headA->length=-1;
    headA->nextAnode=NULL;
    headA->nodeId=-1;
    return headA;
}

Snode* createheadS()
{
    Snode* headS=(Snode*)malloc(sizeof(Snode));
    headS->anode=createheadA();
    headS->nextSnode=NULL;
    headS->nodeId=-1;
    return headS;
}


int ExistSnode (Graph* PtG, int id)//id is the first
{
    while(     PtG->snode->nextSnode != NULL  )
    {
        if (PtG->snode->nodeId == id)
        {
            return 1;//exist
        }
        PtG->snode= PtG->snode->nextSnode;
    }
    if (PtG->snode->nodeId == id)
    {
        return 1;//exist
    }

    return 0;//does not exist
}

int ExistAnode (Snode* snode, int id)//id is the second
{
    while(   snode->anode->nextAnode != NULL  )
    {
        if (snode->anode->nodeId== id)
        {
            return 1;//exist
        }
        snode->anode=snode->anode->nextAnode;
    }
    if (snode->anode->nodeId== id)
    {
        return 1;//exist
    }

    return 0;//does not exist
}


Graph* CreateGraph (int Vnum)
{
    Graph* PtrToGraph = (Graph*)malloc(sizeof(Graph));
    PtrToGraph->Nv=Vnum;
    PtrToGraph->Ne=0;
    PtrToGraph->snode=createheadS();
    return PtrToGraph;
}

Graph* InsertEdge (Graph* PtG, Edge* PtE)
{

    if(ExistSnode(PtG, PtE->idV1))
    {
        while(PtG->snode->nodeId != PtE->idV1)
        {
            PtG->snode=PtG->snode->nextSnode;
        }
        if(ExistAnode(PtG->snode, PtE->idV2))
        {
            while(PtG->snode->nodeId != PtE->idV1)
            {
                PtG->snode=PtG->snode->nextSnode;
            }

            while( PtG->snode->anode->nodeId != PtE->idV2)
            {
                PtG->snode->anode=PtG->snode->anode->nextAnode;
            }
            Anode* PtNewAnode=(Anode*)malloc(sizeof(Anode));
            PtNewAnode->nodeId=PtE->idV2;
            PtNewAnode->length=PtE->length;
            PtNewAnode->nextAnode=PtG->snode->anode->nextAnode;
            PtG->snode->anode->nextAnode=PtNewAnode;
        }
        else
        {
            while(PtG->snode->anode->nextAnode != NULL )
            {
                PtG->snode->anode=PtG->snode->anode->nextAnode;
            }
            Anode* PtNewAnode=(Anode*)malloc(sizeof(Anode));
            PtG->snode->anode->nextAnode=PtNewAnode;

        }

    }
    else
    {
        while(PtG->snode->nextSnode != NULL)
        {
            PtG->snode=PtG->snode->nextSnode;
        }

        Snode* PtNewSnode=(Snode*)malloc(sizeof(Snode));
        Anode* PtNewAnode=(Anode*)malloc(sizeof(Anode));
        PtNewSnode->nextSnode=NULL;
        PtNewSnode->nodeId=PtE->idV1;
        PtNewSnode->anode=createheadA();
        PtNewAnode->length=PtE->length;
        PtNewAnode->nodeId=PtE->idV2;
        PtNewAnode->nextAnode=NULL;
        PtG->snode->nextSnode=PtNewSnode;
        PtG->snode->nextSnode->anode->nextAnode=PtNewAnode;


    }


    if(ExistSnode(PtG, PtE->idV2))
    {
        while(PtG->snode->nodeId != PtE->idV2)
        {
            PtG->snode=PtG->snode->nextSnode;
        }
        if(ExistAnode(PtG->snode, PtE->idV1))
        {
            while(PtG->snode->nodeId != PtE->idV2)
            {
                PtG->snode=PtG->snode->nextSnode;
            }

            while( PtG->snode->anode->nodeId != PtE->idV1)
            {
                PtG->snode->anode=PtG->snode->anode->nextAnode;
            }
            Anode* PtNewAnode=(Anode*)malloc(sizeof(Anode));
            PtNewAnode->nodeId=PtE->idV1;
            PtNewAnode->length=PtE->length;
            PtNewAnode->nextAnode=PtG->snode->anode->nextAnode;
            PtG->snode->anode->nextAnode=PtNewAnode;
        }
        else
        {
            while(PtG->snode->anode->nextAnode != NULL )
            {
                PtG->snode->anode=PtG->snode->anode->nextAnode;
            }
            Anode* PtNewAnode=(Anode*)malloc(sizeof(Anode));
            PtG->snode->anode->nextAnode=PtNewAnode;

        }

    }
    else
    {
        while(PtG->snode->nextSnode != NULL)
        {
            PtG->snode=PtG->snode->nextSnode;
        }

        Snode* PtNewSnode=(Snode*)malloc(sizeof(Snode));
        Anode* PtNewAnode=(Anode*)malloc(sizeof(Anode));
        PtNewSnode->nextSnode=NULL;
        PtNewSnode->nodeId=PtE->idV2;
        PtNewSnode->anode=createheadA();
        PtNewAnode->length=PtE->length;
        PtNewAnode->nodeId=PtE->idV1;
        PtNewAnode->nextAnode=NULL;
        PtG->snode->nextSnode=PtNewSnode;
        PtG->snode->nextSnode->anode->nextAnode=PtNewAnode;


    }
    return PtG;
}

int main()
{
    Graph* PtG=CreateGraph(10);
    Edge E ={1,2,4.0};
    PtG=InsertEdge(PtG,&E);
    PtG->snode=PtG->snode->nextSnode;
    //PtG->snode->anode=PtG->snode->anode->nextAnode;
    printf("%i %i",PtG->snode->nodeId,PtG->snode->anode->nodeId);
    return 0;
}

