#include<stdio.h>

int main(void)
{
	int n,l,t;
	int i,j,num;
	int p=-1;
	int place[104],v[104];
	int *sort[104];
	int *c;

	scanf("%d %d %d",&n,&l,&t);
	for (i = 0; i < n; i++){
		scanf("%d",&place[i]);
	}
	for (i = 0; i < n; i++){
		c=&place[i];
		if(p == -1) sort[++p]=c;
		else{
			for(num = 0; num <= p; num++){
				if(*c<*sort[0]) {
					for(j=p+1;j>0;j--) {sort[j]=sort[j-1];}
					sort[0]=c;p++;//break;
				}
				else if(*c>*sort[p]) {
					sort[++p]=c;//break;
				}
				else if(*c>*sort[num]&&*c<*sort[num+1]) {
					for(j=p+1;j>num+1;j--){sort[j]=sort[j-1];}
					sort[num+1]=c;p++;//break;
				}
			}
		}
		v[i]=1;
	}
	for (i = 1; i <= t; i++){
		if(*sort[0]==0) v[0]=1;
		for(num = 0; num < n-1; num++){
			if(*sort[num]==*sort[num+1]){
				v[num]=-1;v[num+1]=1;
			}
		}
		if(*sort[n-1]==l) v[n-1]=-1;
		for (num = 0; num < n; num++){
			//printf("%d ",*sort[num]);
			*sort[num]+=v[num];
		}
		//printf("\n");
	}
	for (num = 0; num < n-1; num++){
		printf("%d ",place[num]);
	}
	printf("%d",place[num]);
	return 0;
}