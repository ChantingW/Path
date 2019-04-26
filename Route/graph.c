#include <graph.h>
#include <stdio.h>
#include <stdlib.h>


Anode* createheadA()//create a head for the list of Anode
{
    Anode* headA=(Anode*)malloc(sizeof(Anode));
    headA->length=-1;
    headA->nextAnode=NULL;
    headA->nodeId=-1;
    return headA;
}

Snode* createheadS()//create a head for the list of Snode
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
{//to judge if the Snode with the input id exists
    Snode* tmp=PtG->snode;
    while(     PtG->snode->nextSnode != NULL  )//to go through the list
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
{//to judge if the Anode with the input id exists
    Anode* tmp=snode->anode;
    while(   snode->anode->nextAnode != NULL  )//to go through the list
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


Graph* CreateGraph (int Vnum)//to create the new graph
{
    Graph* PtrToGraph = (Graph*)malloc(sizeof(Graph));
    PtrToGraph->Nv=Vnum;
    PtrToGraph->Ne=0;
    PtrToGraph->snode=createheadS();
    return PtrToGraph;
}

Graph* InsertEdge (Graph* PtG, Edge* PtE)//to insert a edge to the graph
{
    Snode* tmpS=PtG->snode;

    if(ExistSnode(PtG, PtE->idV1))//if the snode exists
    {
        while(PtG->snode->nodeId != PtE->idV1)
        {
            PtG->snode=PtG->snode->nextSnode;
        }


        Anode* tmpA=PtG->snode->anode;


        if(ExistAnode(PtG->snode, PtE->idV2))//if the anode also exists
        {

        }
        else//if the anode does not exist
        {
            while(PtG->snode->anode->nextAnode != NULL )
            {
                PtG->snode->anode=PtG->snode->anode->nextAnode;
            }
            Anode* PtNewAnode=(Anode*)malloc(sizeof(Anode));
            PtG->snode->anode->nextAnode=PtNewAnode;
            PtNewAnode->length=PtE->length;
            PtNewAnode->nodeId=PtE->idV2;
            PtNewAnode->nextAnode=NULL;//insert the anode
        }

        PtG->snode->anode=tmpA;

    }
    else//if the snode does not exist
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
        PtG->snode->nextSnode->anode->nextAnode=PtNewAnode;//insert the snode and anode
    }
    PtG->snode=tmpS;

    if(ExistSnode(PtG, PtE->idV2))//change idV1 and idV2 the following code is similar
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
        PtNewSnode->lastId=-1;//initialize
        PtNewAnode->length=PtE->length;
        PtNewAnode->nodeId=PtE->idV1;
        PtNewAnode->nextAnode=NULL;
        PtG->snode->nextSnode=PtNewSnode;
        PtG->snode->nextSnode->anode->nextAnode=PtNewAnode;
    }
    PtG->snode=tmpS;//let the pointer go to the initial place
    return PtG;
}
