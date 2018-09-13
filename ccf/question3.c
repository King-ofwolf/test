#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int p=0;
typedef struct MATCH
{
	int flag;
	char strs[101];
	MATCH * left;
	MATCH * right;
}mat;

typedef struct RULE
{
	mat *head;
	char name[100];
}rul;

typedef struct URL
{
	int flag;
	char urlstr[101];
	char *name;
	mat *head;
}url;

char mygetc()
{

}
void goback()
{

}

int main(int argc, char const *argv[])
{
	int n,m;
	int i,j;
	char cache[101];int p;
	char c;
	mat *pmat=NULL;
	rul rules[101];
	url urls[101];

	scanf("%d %d ",&n,&m);
	for(i=0;i<n;i++){
		scanf("%c",&c);
		while(1){
			//check "/"
			if(c!='/') printf("error:/\n");
			else if(rules[i].head==NULL){
				rules[i].head=(mat*)malloc(sizeof(mat));
				pmat=rules[i].head;
				pmat->left=NULL;pmat->right=NULL;
			}
			else if(rules[i].head!=NULL){
				pmat->right=(mat*)malloc(sizeof(mat));
				pmat->right->left=pmat;
				pmat=pmat->right;
				pmat->right=NULL;
			}

			//check "/ "
			scanf("%c",&c);
			if(c==' '){
				pmat->flag=5;
				break;
			}
			//check "/<"
			else if(c=='<'){
				scanf("%c",&c);
				if(c=='i'){
					scanf("%c%c");
					pmat->flag=3;
				}
				else(c=='p'){
					scanf("%c%c%c");
					pmat->flag=4;
				}
				else(c=='s'){
					scanf("%c%c");
					pmat->flag=2;
				}
				scanf("%c",&c);
				if(c!='>') printf("error:>\n");
				scanf("%c",&c);
			}
			//check "/url"
			else{
				pmat->flag=1;
				p=-1;cache[0]='\0'
				while(1){
					if(c=='/'||c==' ') break;
					cache[++p]=c;
					scanf("%c",&c);
				}
				strcpy(pmat->strs,cache);
			}
		}
		pmat=NULL;

	}
	
	return 0;
}