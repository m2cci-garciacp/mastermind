#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main ()
{	
	const char *list[7];
	list[0] = "bleu";
	list[1] = "rouge";
	list[2] = "vert";
	list[3] = "jaune";
	list[4] = "orange";
	list[5] = "rose";
	list[6] = "noir";
	
	FILE *file ;
	char fname[200] ;
	
	for (int N=5; N<=7; N++){
		sprintf(fname, "./data/data_lvl%d.dat",N);
		file = fopen(fname, "w");
		fprintf(file, "%d\n",N);
		for (int a=0; a<N; a++) {for (int b=0; b<N; b++) {for (int c=0; c<N; c++) {for (int d=0; d<N; d++) {
			//printf("%d ", d);
			fprintf(file, "%s-%s-%s-%s\n",list[a], list[b], list[c], list[d]);
		}}}}
		fclose(file);
	}
		
		
	return 0;
}
