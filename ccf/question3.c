#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int p=0;
typedef struct MATCH
{
	int flag;
	char strs[101];
	//struct MATCH * left;
	struct MATCH * right;
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

void freehead(mat * trash){
	mat *mp=trash;
	mat *np;
	while(mp!=NULL){
		np=mp->right;
		free(mp);
		mp=np;
	}
}

char mygetc()
{

}
void goback()
{

}
int urlmatch(char *matstr,char *stdstr){
	
}
int strmatch(char *matstr,char *savestr){

}
int intmatch(char *matstr,char *savestr){
	
}
int pathmatch(char *matstr,char *savestr){
	
}

void urlheadadd(url *purl,char *strs){
	mat *pmat=purl->head;
	while(pmat->right!=NULL) pmat=pmat->right;
	pmat->right=(mat*)malloc(sizeof(mat));
	pmat->right->right==NULL;
	strcpy(pmat->strs,strs);
}
void matmatch(url * purl, mat * pmat){
	int flag=0;
	switch(pmat->flag){
		case 1:{
			flag=urlmatch(purl->urls,pmat->strs);
			if(flag==1){
				purl->flag=1;return;
			}else{
				purl->flag=0;return;
			}
		}
		case 2:{
			flag=strmatch(purl->urls,pmat->strs);//remember to set strs's end :'\0'
			if(flag==1){
				purl->flag=1;
				urlheadadd(purl,pmat->strs);
				return;
			}else{
				purl->flag=0;return;
			}
		}
		case 3:{
			flag=intmatch(purl->urls,pmat->strs);//remember to set strs's end :'\0'
			if(flag==1){
				purl->flag=1;
				urlheadadd(purl,pmat->strs);
				return;
			}else{
				purl->flag=0;
				return;
			}
		}
		case 4:{
			flag=pathmatch(purl->urls,pmat->strs);//remember to ..
			if(flag==1){
				purl->flag=1;
				urlheadadd(purl,pmat->strs);
				return;
			}else{
				purl->flag=0;
				return;
			}
		}
	}
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
	rul *prule;
	url *purl;
	scanf("%d %d ",&n,&m);

	//read rules
	for(i=0;i<n;i++){
		scanf("%c",&c);
		while(1){
			//check "/"
			if(c!='/') printf("error:/\n");
			else if(rules[i].head==NULL){
				rules[i].head=(mat*)malloc(sizeof(mat));
				pmat=rules[i].head;
				//pmat->left=NULL;
				pmat->right=NULL;
			}
			else if(rules[i].head!=NULL){
				pmat->right=(mat*)malloc(sizeof(mat));
				//pmat->right->left=pmat;
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
					scanf("%c%c",&c,&c);
					pmat->flag=3;
				}
				else if(c=='p'){
					scanf("%c%c%c",&c,&c,&c);
					pmat->flag=4;
				}
				else if(c=='s'){
					scanf("%c%c",&c,&c);
					pmat->flag=2;
				}
				scanf("%c",&c);
				if(c!='>') printf("error:>\n");
				scanf("%c",&c);
			}
			//check "/url"
			else{
				pmat->flag=1;
				p=-1;cache[0]='\0';
				while(1){
					if(c=='/'||c==' ') break;
					cache[++p]=c;
					scanf("%c",&c);
				}
				cache[++p]='\0';printf("++%s\n",cache);
				strcpy(pmat->strs,cache);
			}
			if(c==' ') break;
		}
		pmat=NULL;

		//read rules name
		scanf("%s ",&rules[i].name);
	}
	//read urls
	for(i=0;i<m;i++){
		scanf("%s",&urls[i].urlstr);
		urls[i].flag=0;
		urls[i].head=NULL;
		urls[i].name=NULL;
	}

	//analysis the urls
	for(i=0;i<m;i++){
		purl=&urls[i];
		for(j=0;j<n;j++){
			prule=&rules[j];
			p=0;
			pmat=prule->head;
			while(pmat!=NULL){
				matmatch(purl,pmat);
				if(purl->flag==0) break;
				else pmat=pmat->right;
			}
			if(purl->flag==1) {
				purl->name=prule->name;
				break;
			}
		}
	}
	//print the analysised urls
	for(i=0;i<m;i++){
		purl=&urls[i];
		if(purl->flag==0) printf("404");
		else{
			printf("%s",purl->name);
			for(pmat=purl->head;pmat!=NULL;pmat=pmat->right) printf(" %s",pmat->strs);
		}
		printf("\n");
	}

	//free all memory
	for(i=0;i<n;i++){
		freehead(rules[i].head);
	}
	for(i=0;i<m;i++){
		freehead(urls[i].head);
	}
	
	return 0;
}
