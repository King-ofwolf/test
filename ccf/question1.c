#include<stdio.h>
int main(void)
{
	/* code */
	int c=1,lastc=1;
	int total=0;
	while(c!=0){
		scanf("%d",&c);
		if(c==1) {
			total+=1;
			lastc=1;
		}
		else if (c==2){
			if (lastc==1) {
				total+=2;
				lastc=2;
			}
			else {
				total=total+lastc+2;
				lastc+=2;
			}
		}
	}
	printf("%d",total);
	return 0;
}