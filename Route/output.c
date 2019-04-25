#include <graph.h>
#include <stdio.h>
#include <stdlib.h>
#include <input.h>
#include <find.h>


int* getpath (Graph* PtG, int start, int endid, int storepath[])
{
    dijkstra ( PtG, start);
    int i=2;

    //printf("j");
    Snode* startSnode=PtG->snode;
    while(PtG->snode->nodeId != endid )
    {
        if(PtG->snode->nextSnode==NULL && PtG->snode->nodeId != endid)
        {
            storepath[0]=0;
            return storepath;
        }
        PtG->snode=PtG->snode->nextSnode;
        //printf("1");
    }
    //printf("k");

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
            //printf("k");
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

Node* getPathNode(Node* Info, int storepath[])
{
    Node* pathInfo=CreateNode();
    Node* startpathInfo=pathInfo;
    Node* startInfo=Info;

    if(storepath[0] == 1)
    {

        int i=1;
        while(storepath[i]!=0)
        {
            Info=startInfo;
            while(Info->id!=storepath[i])
            {
                Info=Info->nextNode;
            }

            pathInfo->id=Info->id;
            pathInfo->lat=Info->lat;
            pathInfo->lon=Info->lon;
            pathInfo->nextNode=CreateNode();

            printf("%i %f %f\n", pathInfo->id, pathInfo->lat, pathInfo->lon);
            ++i;
            pathInfo=pathInfo->nextNode;
        }
    }
    if(storepath[0] == 0)
    {

        printf("There are no path between this two nodes");
    }
    pathInfo=startpathInfo;
    return pathInfo;
}

void writenode(Node* Info)
{
    FILE *fp = fopen("nodes.out","w");
    while(Info != NULL)
    {
        //printf(" %f %f\n",pathInfo->lon,pathInfo->lat);
        fprintf(fp, " %f %f\n",Info->lon,Info->lat);
        Info=Info->nextNode;
    }
    return;
}

void writelink(Node* Info, Graph* PtG)
{
    int tmpsid;
    int tmpaid;
    FILE *fp = fopen("links.out","w");
    Snode* startSnode=PtG->snode;
    Anode* startAnode;
    Node* startInfo=Info;
    float slat;
    float slon;
    PtG->snode=PtG->snode->nextSnode;

    while(PtG->snode != NULL)
    {
        tmpsid=PtG->snode->nodeId;

        while(Info->id != tmpsid)
        {
            Info=Info->nextNode;
        }
        slat=Info->lat;
        slon=Info->lon;
        Info=startInfo;
        startAnode=PtG->snode->anode;
        PtG->snode->anode=PtG->snode->anode->nextAnode;
        while(PtG->snode->anode != NULL)
        {
            tmpaid=PtG->snode->anode->nodeId;
            while(Info->id != tmpaid)
            {
                Info=Info->nextNode;
            }
            fprintf(fp, " %f %f\n",slon,slat);
            fprintf(fp, " %f %f\n\n\n",Info->lon,Info->lat);
            Info=startInfo;
            PtG->snode->anode=PtG->snode->anode->nextAnode;

        }
        PtG->snode->anode=startAnode;
        PtG->snode=PtG->snode->nextSnode;
        //printf(" %f %f\n",pathInfo->lon,pathInfo->lat);
    }
    PtG->snode=startSnode;
    return;
}

/*void writelink()
{

}*/

void writepath(Node* pathInfo)
{
    FILE *fp = fopen("route.out","w");
    while(pathInfo->id != 0)
    {
        //printf(" %f %f\n",pathInfo->lon,pathInfo->lat);
        fprintf(fp, " %f %f\n",pathInfo->lon,pathInfo->lat);
        pathInfo=pathInfo->nextNode;
    }
    return;
}
