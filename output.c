#include <graph.h>
#include <stdio.h>
#include <stdlib.h>
#include <input.h>
#include <find.h>


int* getpath (Graph* PtG, int start, int endid, int storepath[])
{
    dijkstra ( PtG, start);
    int i=2;


    Snode* startSnode=PtG->snode;
    while(PtG->snode->nodeId != endid)
    {
        PtG->snode=PtG->snode->nextSnode;
    }
    storepath[1]=PtG->snode->nodeId;
    storepath[2]=PtG->snode->lastId;

    while(1)
    {
        PtG->snode=startSnode;
        while(PtG->snode->nodeId != storepath[i])
        {
            PtG->snode=PtG->snode->nextSnode;
        }

        if(PtG->snode->lastId==start)
        {
            storepath[i+1]=PtG->snode->lastId;
            storepath[0]=1;
            break;
        }

        if(PtG->snode->lastId==-1)
        {
            storepath[i+1]=PtG->snode->lastId;
            storepath[0]=0;
            break;
        }
        storepath[i+1]=PtG->snode->lastId;
        ++i;
    }

    PtG->snode=startSnode;
    return storepath;
}


