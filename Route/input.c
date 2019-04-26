#include <graph.h>
#include <stdio.h>
#include <stdlib.h>



Graph* Read (Graph* PtG, FILE* PtF)
{//to read all links in the map file to the program
    char* buf;
    char buf1[255];
    char buf2[255];
    char buf3[255];//3 buffer array
    buf=(char*)malloc(255*sizeof(char));//malloc
    int node1;
    int node2;
    float length;
    Edge* PtE;
    fgets(buf, 1000, PtF);//read the first line
    int n=2;
    while(n>=2 && n<=2345)
    {
        fgets(buf, 1000, PtF);
        sscanf(buf, "%*s %*s node=%s node=%s %*s length=%s", buf1,buf2,buf3);//the special structure to get the value
        node1=atoi(buf1);
        node2=atoi(buf2);
        length=atof(buf3);//covet the string into number

        PtE->idV1=node1;
        PtE->idV2=node2;
        PtE->length=length;
        PtG=InsertEdge(PtG,PtE);
        n++;//add the information
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
}//create a node to store the geographical information


Node* Readnode (FILE* PtF)
{//read the geographical information of all nodes in the map file
    char* buf;
    char buf1[255];
    char buf2[255];
    char buf3[255];//3 buffer arrays
    buf=(char*)malloc(255*sizeof(char));
    int id;
    float lat;
    float lon;
    int n=2346;

    Node* Info=CreateNode();
    Node* startInfo=Info;
    while(n>=2346 && n<=6286)
    {
        fgets(buf, 1000, PtF);//get a line
        sscanf(buf, "%*s  id=%s lat=%s lon=%s %*s", buf1,buf2,buf3);//parse the line and get the substring
        id=atoi(buf1);
        lat=atof(buf2);
        lon=atof(buf3);//change the substirng into numver

        Info->id=id;
        Info->lat=lat;
        Info->lon=lon;
        n++;//add
        if(n==6287)
            break;//end
        Info->nextNode=CreateNode ();
        Info=Info->nextNode;//next line

    }
    Info=startInfo;
    return Info;
}

int idexist(Node* Info, int startid, int endid)
{//to judge if the id exists
    Node* startInfo=Info;
    int a=0;
    int b=0;
    while(Info != NULL)
    {//go through the node list
        if(Info->id ==startid)
            a=1;//find the id
        Info=Info->nextNode;//next node
    }
    Info=startInfo;

    while(Info != NULL)
    {//for the end id, do again
        if(Info->id ==endid)
            b=1;
        Info=Info->nextNode;
    }
    Info=startInfo;

    if(a+b==2)//find both
        return 1;
    else
        return 0;//does not find
}
