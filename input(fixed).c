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
printf("%i %i\n",PtG->snode->nodeId,PtG->snode->anode->nextAnode->nodeId);
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
        PtNewAnode->length=PtE->length;
        PtNewAnode->nodeId=PtE->idV2;
        PtNewAnode->nextAnode=NULL;
        PtG->snode->nextSnode=PtNewSnode;
        PtG->snode->nextSnode->anode->nextAnode=PtNewAnode;
printf("%i %i\n",PtG->snode->nextSnode->nodeId,PtG->snode->nextSnode->anode->nextAnode->nodeId);
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
printf("%i %i\n",PtG->snode->nodeId,PtG->snode->anode->nextAnode->nodeId);
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
        PtNewAnode->length=PtE->length;
        PtNewAnode->nodeId=PtE->idV1;
        PtNewAnode->nextAnode=NULL;
        PtG->snode->nextSnode=PtNewSnode;
        PtG->snode->nextSnode->anode->nextAnode=PtNewAnode;
printf("%i %i\n",PtG->snode->nextSnode->nodeId,PtG->snode->nextSnode->anode->nextAnode->nodeId);

    }
    PtG->snode=tmpS;
    return PtG;
}







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
    printf("r");
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
    printf("%i",n);

    return PtG;
}

int main()
{
    FILE *PtF = fopen("Final_Map.map", "r");
    Graph* PtG=CreateGraph(100000);
    printf("1");
    PtG=Read(PtG, PtF);
    printf("1");
    PtG->snode=PtG->snode->nextSnode->nextSnode;
    printf("b");
    printf("%i",PtG->snode->nodeId);
    //PtG->snode->anode=PtG->snode->anode->nextAnode;
    printf("%i %i",PtG->snode->nodeId,PtG->snode->anode->nodeId);
    printf("2");
    fclose(PtF);
    return 0;
}

