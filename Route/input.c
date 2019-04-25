#include <graph.h>
#include <stdio.h>
#include <stdlib.h>



Graph* Read (Graph* PtG, FILE* PtF)
{
    char* buf;
    char buf1[255];
    char buf2[255];
    char buf3[255];
    buf=(char*)malloc(255*sizeof(char));
    int node1;
    int node2;
    float length;
    Edge* PtE;
    fgets(buf, 1000, PtF);
    int n=2;
   // printf("r");
    while(n>=2 && n<=2345)
    {
        fgets(buf, 1000, PtF);
        sscanf(buf, "%*s %*s node=%s node=%s %*s length=%s", buf1,buf2,buf3);
        node1=atoi(buf1);
        node2=atoi(buf2);
        length=atof(buf3);

        PtE->idV1=node1;
        PtE->idV2=node2;
        PtE->length=length;
        PtG=InsertEdge(PtG,PtE);
        n++;
    }
    //printf("%i",n);

    return PtG;
}

Node* CreateNode ()
{
    Node* nodeInfo=(Node*)malloc(sizeof(Node));
    nodeInfo->id=0;
    nodeInfo->lat=-1;
    nodeInfo->lon=-1;
    nodeInfo->nextNode=NULL;
    return nodeInfo;
}


Node* Readnode (FILE* PtF)
{
    char* buf;
    char buf1[255];
    char buf2[255];
    char buf3[255];
    buf=(char*)malloc(255*sizeof(char));
    int id;
    float lat;
    float lon;
    int n=2346;
    /*for(n=1;n<=2345;++n)
    {
        fgets(buf, 1000, PtF);
    }*/

    Node* Info=CreateNode();
    Node* startInfo=Info;
    while(n>=2346 && n<=6286)
    {
        fgets(buf, 1000, PtF);
        sscanf(buf, "%*s  id=%s lat=%s lon=%s %*s", buf1,buf2,buf3);
        id=atoi(buf1);
        lat=atof(buf2);
        lon=atof(buf3);

        Info->id=id;
        Info->lat=lat;
        Info->lon=lon;
        n++;
        if(n==6287)
            break;
        Info->nextNode=CreateNode ();
        Info=Info->nextNode;

    }
    Info=startInfo;
    return Info;
}
