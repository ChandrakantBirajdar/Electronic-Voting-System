#include "header.h"

void updateBatchId(int batchId){
    int newbatchId=(++batchId);
    FILE *file = fopen("topBatchId.txt","w");
    if(file!=NULL){
        fprintf(file,"%d",newbatchId);
        fclose(file);
    }
}
int getBatchId(){
    int batchId=0;
    FILE *file = fopen("topBatchId.txt","r");
    if(file!=NULL){
        fscanf(file,"%d",&batchId);
        fclose(file);
    }
    updateBatchId(batchId);
    return batchId;
}