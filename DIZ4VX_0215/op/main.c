#include <stdio.h>
#include <stdlib.h>

int main()
{
FILE *fp;

fp = fopen("Attila.txt", "wt");

fprintf(fp, "Dobai Attila,BI,DIZ4VX\n");

fclose(fp);





    return 0;
}
