#include <stdio.h>
#define MAXWIDTH 5
#define MAXHEIGHT 5

int main(void) 
{
    /* code here */
    int i,j;
    int image[MAXHEIGHT][MAXWIDTH];
    for (i = 0; i < MAXHEIGHT; i++) 
    {
        for (j = 0; j < MAXHEIGHT; j++) 
        {
            int read;
            scanf(" %d",&read);
            image[i][j] = read;
        }
    }
    for (i = 0; i < MAXHEIGHT; i++) 
    {
        for (j = 0; j < MAXHEIGHT; j++) 
        {
            printf("%d ",image[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}