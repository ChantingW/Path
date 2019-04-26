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

    int storepath[9999]={0};//to store the sequence of id of the route
    int startid;
    int endid;
    printf("Please input the StartID and EndID:");
    scanf("%i %i",&startid,&endid);//input the ids
    if (idexist(Info, startid, endid)==0)
    {
        printf("Wrong node ID(Does not exist)");
        return 0;
    }

    getpath( PtG, startid, endid, storepath);//get the sequences
    if(storepath[0] == 0)
    {
        printf("There are no path between these two nodes");
        return 0;
    }//can find the path

    SelectedInfo=getPathNode(Info, storepath);//get the lat and lon of the node in the path

    writenode(Info);

    writepath( SelectedInfo);

    writelink(Info, PtG);

    fclose(PtF);
    return 0;
}
