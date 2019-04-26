#include <graph.h>
#include <stdio.h>
#include <stdlib.h>


int findminId (Graph* PtG)
{//to find the snode that has the min dist now
    Snode* startSnode=PtG->snode;
    float tmpdis=9999;
    int tmpId=0;
    PtG->snode=PtG->snode->nextSnode;
    while(PtG->snode != NULL)
    {
        if(PtG->snode->visit==1)//if the snode has been visited
        {
            PtG->snode=PtG->snode->nextSnode;
            continue;//skip the snode
        }
        if(PtG->snode->dist < tmpdis)//find the snode has the min distance
        {
            tmpdis = PtG->snode->dist;
            tmpId = PtG->snode->nodeId;
        }

        PtG->snode=PtG->snode->nextSnode;//next
    }

    PtG->snode=startSnode;//go back the pointer
    return tmpId;
}

int stage (Graph* PtG, int startid)//this is the stage of the dijkstra algorithm
{
    int adjid;
    float adjlen;
    int t=0;

    Snode* startSnode=PtG->snode;
    while(PtG->snode->nodeId != startid)
    {
        PtG->snode=PtG->snode->nextSnode;
    }//go to the snode with the id equeal to startid
    Snode* idSnode=PtG->snode;
    PtG->snode->visit=1;//set the visit of the snode 1

    Anode* startAnode=idSnode->anode;
    idSnode->anode=idSnode->anode->nextAnode;//skip the empty anode

    while(idSnode->anode != NULL)//go through all anode of the start Snode
    {
        adjid=idSnode->anode->nodeId;
        adjlen=idSnode->anode->length;
        PtG->snode=startSnode;
        while(PtG->snode->nodeId != adjid)
        {
            PtG->snode=PtG->snode->nextSnode;
        }//go to the snode with adjid
        if(PtG->snode->dist > adjlen+idSnode->dist)
        {
            PtG->snode->dist=adjlen+idSnode->dist;
            PtG->snode->lastId=startid;
            t=1;//if change
        }
        idSnode->anode=idSnode->anode->nextAnode;
    }


    PtG->snode=startSnode;
    idSnode->anode=startAnode;
    return t;//if change return 1, else return 0
}


Graph* dijkstra (Graph* PtG, int startid)//dijkstra algorithm
{

    int id=startid;
    int n=1;

    Snode* startSnode=PtG->snode;
    while(PtG->snode->nodeId != startid)
    {
        PtG->snode=PtG->snode->nextSnode;
    }
    PtG->snode->dist=0;
    PtG->snode=startSnode;
    stage (PtG, startid);

    while(1)
    {

        id=findminId (PtG);
        if(id==0)
            break;//when it can not find the start node,complete
        stage (PtG, id);
        ++n;
    }

    return PtG;
}



