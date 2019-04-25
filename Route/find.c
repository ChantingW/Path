#include <graph.h>
#include <stdio.h>
#include <stdlib.h>



/*
int main()
{
    char buf1[255];
    char buf2[255];
    char buf3[255];
    char* buf;
    buf=(char*)malloc(255*sizeof(char));
    char* string;
    FILE *PtF = fopen("Final_Map.map", "r");
    buf=fgets(buf, 1000, PtF);
    printf("%s", buf);
    int n=1;
    while(n<=10)
    {


    fgets(buf, 1000, PtF);


string=buf;//"<link id=-2143392624 node=-2562 node=-2558 way=-7726 length=2.297085 veg=0.000000 arch=0.000000 land=0.000000 POI=;/link>";
sscanf(string, "%*s %*s node=%s node=%s %*s length=%s", buf1,buf2,buf3);
printf("%s %s %s\n",buf1,buf2,buf3);
int num1=atoi(buf1);
int num2=atoi(buf2);
float num3=atof(buf3);
printf("%i %i %f\n",num1,num2,num3);
++n;
    }
fclose(PtF);
return 0;
}
*/




int findminId (Graph* PtG)
{
    Snode* startSnode=PtG->snode;
    float tmpdis=9999;
    int tmpId=0;
    PtG->snode=PtG->snode->nextSnode;
    while(PtG->snode != NULL)
    {
        if(PtG->snode->visit==1)
        {
            PtG->snode=PtG->snode->nextSnode;
            continue;
        }
        if(PtG->snode->dist < tmpdis)
        {
            tmpdis = PtG->snode->dist;
            tmpId = PtG->snode->nodeId;
        }
       // printf("a");
        PtG->snode=PtG->snode->nextSnode;
    }
//printf("f");
  /*  if(PtG->snode->visit==1)
    {
        PtG->snode=startSnode;
        return tmpId;
    }

    if(PtG->snode->dist < tmpdis)
    {
        tmpdis = PtG->snode->dist;
        tmpId = PtG->snode->nodeId;
    }*/
    PtG->snode=startSnode;
    return tmpId;
}

int stage (Graph* PtG, int startid)
{
    int adjid;
    float adjlen;
    int t=0;

    Snode* startSnode=PtG->snode;
    while(PtG->snode->nodeId != startid)
    {
        PtG->snode=PtG->snode->nextSnode;
    }
    Snode* idSnode=PtG->snode;
    PtG->snode->visit=1;
    //printf("%i %f %i \n",PtG->snode->nodeId, PtG->snode->dist, PtG->snode->lastId);
    Anode* startAnode=idSnode->anode;
    idSnode->anode=idSnode->anode->nextAnode;

    while(idSnode->anode != NULL)
    {
        adjid=idSnode->anode->nodeId;
        adjlen=idSnode->anode->length;
        PtG->snode=startSnode;
        while(PtG->snode->nodeId != adjid)
        {
            PtG->snode=PtG->snode->nextSnode;
        }
        if(PtG->snode->dist > adjlen+idSnode->dist)
        {
            PtG->snode->dist=adjlen+idSnode->dist;
            PtG->snode->lastId=startid;
            t=1;
        }
        idSnode->anode=idSnode->anode->nextAnode;
    }

/*        adjid=idSnode->anode->nodeId;
        adjlen=idSnode->anode->length;
        PtG->snode=startSnode;
        while(PtG->snode->nodeId != adjid)
        {
            PtG->snode=PtG->snode->nextSnode;
        }
        if(PtG->snode->dist > adjlen+idSnode->dist)
        {
            PtG->snode->dist=adjlen+idSnode->dist;
            t=1;
        }
*/
    PtG->snode=startSnode;
    idSnode->anode=startAnode;
    return t;
}


Graph* dijkstra (Graph* PtG, int startid)
{
    //int judge=0;
    int id=startid;
    int n=1;

    Snode* startSnode=PtG->snode;
    while(PtG->snode->nodeId != startid)
    {
        PtG->snode=PtG->snode->nextSnode;
    }
    PtG->snode->dist=0;
    PtG->snode=startSnode;
    //printf("1");
    stage (PtG, startid);
//printf("%i",PtG->snode->nodeId);
    while(1)
    {

        id=findminId (PtG);
        if(id==0)
            break;
        //printf("e");
        //printf("%i ",n);
//printf("%i ",id);
        stage (PtG, id);
//printf("%i ",id);
        //printf("%i\n",n);
        ++n;
    }

    return PtG;
}



