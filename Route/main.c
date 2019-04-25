#include <graph.h>
#include <stdio.h>
#include <stdlib.h>
#include <input.h>
#include <find.h>
#include <output.h>



int main()
{
    FILE *PtF = fopen("Final_Map.map", "r");
    Graph* PtG=CreateGraph(100000);
    printf("go");
    PtG=Read(PtG, PtF);
    Node* Info=Readnode (PtF);
    Node* SelectedInfo;
    //dijkstra(PtG, -1887865267);
    int storepath[9999]={0};
    int startid;
    int endid;
    printf("Please input the StartID and EndID:");
    scanf("%i %i",&startid,&endid);
    if (idexist(Info, startid, endid)==0)
    {
        printf("Wrong node ID(Does not exist)");
        return 0;
    }
    //printf("1");
    getpath( PtG, startid, endid, storepath);
    if(storepath[0] == 0)
    {
        printf("There are no path between theseb two nodes");
        return 0;
    }
    //printf("2");
    SelectedInfo=getPathNode(Info, storepath);
    //printf("3");

   // printf("%i\n",SelectedInfo->id);
    //printf("%i\n",Info->id);
    writenode(Info);
    //printf("3");
    writepath( SelectedInfo);
    //printf("4");
    writelink(Info, PtG);

   /* while(PtG->snode->nextSnode != NULL)
    {
        while(PtG->snode->anode->nextAnode!=NULL)
        {
            printf("%i %i \n",PtG->snode->nodeId, PtG->snode->anode->nodeId);
            PtG->snode->anode=PtG->snode->anode->nextAnode;

        }
        printf("%i %i\n",PtG->snode->nodeId, PtG->snode->anode->nodeId);
        printf("\n");
        PtG->snode=PtG->snode->nextSnode;
    }
    while(PtG->snode->anode->nextAnode!=NULL)
    {
        printf("%i %i\n",PtG->snode->nodeId, PtG->snode->anode->nodeId);
        PtG->snode->anode=PtG->snode->anode->nextAnode;

    }
    printf("%i %i\n",PtG->snode->nodeId, PtG->snode->anode->nodeId);
    printf("\n");*/

   /* while(PtG->snode->nextSnode != NULL)
    {
        printf("%f %i\n", PtG->snode->dist, PtG->snode->visit);
        PtG->snode=PtG->snode->nextSnode;
    }
    PtG->snode=PtG->snode->nextSnode;*/

   // printf("1");
    //PtG->snode=PtG->snode->nextSnode->nextSnode;
   // printf("b");
    //printf("%i",PtG->snode->nodeId);
    //PtG->snode->anode=PtG->snode->anode->nextAnode;
    //printf("%i %i",PtG->snode->nodeId,PtG->snode->anode->nodeId);
    fclose(PtF);
    return 0;
}
