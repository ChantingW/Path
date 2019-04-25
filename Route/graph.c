#include <graph.h>
#include <stdio.h>
#include <stdlib.h>


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
    headS->visit=0;
    headS->lastId=-1;
    headS->dist=9999;
    return headS;
}


int ExistSnode (Graph* PtG, int id)//id is the first
{
    Snode* tmp=PtG->snode;
    while(     PtG->snode->nextSnode != NULL  )
    {
        if (PtG->snode->nodeId == id)
        {
            PtG->snode=tmp;
            return 1;//exist
        }
        PtG->snode= PtG->snode->nextSnode;
    }
    if (PtG->snode->nodeId == id)
    {
        PtG->snode=tmp;
        return 1;//exist
    }

    PtG->snode=tmp;
    return 0;//does not exist
}

int ExistAnode (Snode* snode, int id)//id is the second
{
    Anode* tmp=snode->anode;
    while(   snode->anode->nextAnode != NULL  )
    {
        if (snode->anode->nodeId== id)
        {
            snode->anode=tmp;
            return 1;//exist
        }
        snode->anode=snode->anode->nextAnode;
    }
    if (snode->anode->nodeId== id)
    {
        snode->anode=tmp;
        return 1;//exist
    }

    snode->anode=tmp;
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
    Snode* tmpS=PtG->snode;

    if(ExistSnode(PtG, PtE->idV1))
    {
        while(PtG->snode->nodeId != PtE->idV1)
        {
            PtG->snode=PtG->snode->nextSnode;
        }


        Anode* tmpA=PtG->snode->anode;


        if(ExistAnode(PtG->snode, PtE->idV2))
        {

        }
        else
        {
            while(PtG->snode->anode->nextAnode != NULL )
            {
                PtG->snode->anode=PtG->snode->anode->nextAnode;
            }
            Anode* PtNewAnode=(Anode*)malloc(sizeof(Anode));
            PtG->snode->anode->nextAnode=PtNewAnode;
            PtNewAnode->length=PtE->length;
            PtNewAnode->nodeId=PtE->idV2;
            PtNewAnode->nextAnode=NULL;
//printf("%i %i\n",PtG->snode->nodeId,PtG->snode->anode->nextAnode->nodeId);
        }

        PtG->snode->anode=tmpA;

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
        PtNewSnode->visit=0;
        PtNewSnode->dist=9999;
        PtNewSnode->lastId=-1;
        PtNewAnode->length=PtE->length;
        PtNewAnode->nodeId=PtE->idV2;
        PtNewAnode->nextAnode=NULL;
        PtG->snode->nextSnode=PtNewSnode;
        PtG->snode->nextSnode->anode->nextAnode=PtNewAnode;
//printf("%i %i\n",PtG->snode->nextSnode->nodeId,PtG->snode->nextSnode->anode->nextAnode->nodeId);
    }
    PtG->snode=tmpS;

    if(ExistSnode(PtG, PtE->idV2))
    {
        while(PtG->snode->nodeId != PtE->idV2)
        {
            PtG->snode=PtG->snode->nextSnode;
        }
        Anode* tmpA=PtG->snode->anode;
        if(ExistAnode(PtG->snode, PtE->idV1))
        {
        }

        else
        {
            while(PtG->snode->anode->nextAnode != NULL )
            {
                PtG->snode->anode=PtG->snode->anode->nextAnode;
            }
            Anode* PtNewAnode=(Anode*)malloc(sizeof(Anode));
            PtNewAnode->length=PtE->length;
            PtNewAnode->nodeId=PtE->idV1;
            PtNewAnode->nextAnode=NULL;
            PtG->snode->anode->nextAnode=PtNewAnode;
//printf("%i %i\n",PtG->snode->nodeId,PtG->snode->anode->nextAnode->nodeId);
        }
        PtG->snode->anode=tmpA;

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
        PtNewSnode->visit=0;
        PtNewSnode->dist=9999;
        PtNewSnode->lastId=-1;
        PtNewAnode->length=PtE->length;
        PtNewAnode->nodeId=PtE->idV1;
        PtNewAnode->nextAnode=NULL;
        PtG->snode->nextSnode=PtNewSnode;
        PtG->snode->nextSnode->anode->nextAnode=PtNewAnode;
//printf("%i %i\n",PtG->snode->nextSnode->nodeId,PtG->snode->nextSnode->anode->nextAnode->nodeId);

    }
    PtG->snode=tmpS;
    return PtG;
}
