#include <stdio.h>
#include <stdlib.h>
char * strcpy(char *dst, char *src){
	int i=0;
	while(*(src + i) != "\0"){
		*(dst + i) = *(src + i);
		i++;
	}
	return dst;
}
int main(){
	int k=0;
	for (int i=0; i<10; i++){
		k += i;
		for (int j=0; j<i; j++){
			k+= j;
			if (k>1000){
				break;
			}
		}
		printf("ok\n");
	}
	printf("%d\n", k);
	return 0;
}