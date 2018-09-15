#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int P_url=0;
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

char mygetc(char *str)
{
	return str[P_url++];
}
void goback()
{
	P_url--;
}
void resetpurl(){
	P_url=0;
}
int isachar(char c){
	if(c>='a'&&c<='z') return 1;
	if(c>='A'&&c<='Z') return 2;
	if(c>='0'&&c<='9') return 3;
	if(c=='-'||c=='_'||c=='.') return 4;
	return 0;
}
int urlmatch(char *matstr,char *stdstr){
	char m,n;
	int np=0;
	n=stdstr[np++];
	m=mygetc(matstr);
	if(m!='/') {
		goback();
		return 0;
	}
	m=mygetc(matstr);
	while(m==n){
		if(m=='\0') {goback();return 1;}
		n=stdstr[np++];
		m=mygetc(matstr);
		if(n=='\0') {goback();return 1;}
	}
	goback();
	return 0;
}
int strmatch(char *matstr,char *savestr){
	char m;
	int np=0;
	savestr[0]='\0';
	m=mygetc(matstr);
	if(m!='/') return 0;
	m=mygetc(matstr);
	if(m=='\0') return 0;
	while(m!='/'&&m!='\0'){
		if(isachar(m)>0){
			savestr[np++]=m;
		}
		else return 0;
		m=mygetc(matstr);
	}
	goback();
	savestr[np]='\0';
	return 1;
}
int intmatch(char *matstr,char *savestr){
	char m;
	int np=0;
	savestr[0]='\0';
	m=mygetc(matstr);
	if(m!='/') return 0;
	m=mygetc(matstr);
	if(m=='\0') return 0;
	while(m!='/'&&m!='\0'){
		if(m>='0'&&m<='9'){
			if(np==0&&m=='0') ;
			else savestr[np++]=m;
		}
		else return 0;
		m=mygetc(matstr);
	}
	goback();
	savestr[np]='\0';
	return 1;
}
int pathmatch(char *matstr,char *savestr){
	char m;
	int np=0;
	savestr[0]='\0';
	m=mygetc(matstr);
	if(m!='/') return 0;
	m=mygetc(matstr);
	if(m=='\0') return 0;
	while(m!='\0'){
		if(isachar(m)>0||m=='/'){
			savestr[np++]=m;
		}
		else return 0;
		m=mygetc(matstr);
	}
	goback();
	savestr[np]='\0';
	return 1;
}
int nullmatch(char *matstr){
	char m;
	m=mygetc(matstr);
	if(m!='/') return 0;
	m=mygetc(matstr);
	if(m=='\0') {goback();return 1;}
	return 0;
}
int endmatch(char *matstr){
	char m;
	m=mygetc(matstr);
	if(m=='\0') {goback();return 1;}
	return 0;
}

void urlheadadd(url *purl,char *strs){
	mat *pmat=purl->head;
	if(pmat==NULL){
		pmat=(mat*)malloc(sizeof(mat));
		pmat->right=NULL;
		strcpy(pmat->strs,strs);
		purl->head=pmat;
		return;
	}
	while(pmat->right!=NULL) pmat=pmat->right;
	pmat->right=(mat*)malloc(sizeof(mat));
	pmat->right->right=NULL;
	strcpy(pmat->right->strs,strs);
}
void matmatch(url * purl, mat * pmat){
	int flag=0;
	switch(pmat->flag){
		case 1:{
			flag=urlmatch(purl->urlstr,pmat->strs);printf("--------urlmat:%s,get:%d\n",pmat->strs,flag);
			if(flag==1){
				purl->flag=1;return;
			}else{
				purl->flag=0;return;
			}
		}
		case 2:{
			flag=strmatch(purl->urlstr,pmat->strs);printf("--------strmat:%s,get:%d\n",pmat->strs,flag);
			if(flag==1){
				purl->flag=1;
				urlheadadd(purl,pmat->strs);
				return;
			}else{
				purl->flag=0;return;
			}
		}
		case 3:{
			flag=intmatch(purl->urlstr,pmat->strs);printf("--------intmat:%s,get:%d\n",pmat->strs,flag);
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
			flag=pathmatch(purl->urlstr,pmat->strs);printf("--------pathmat:%s,get:%d\n",pmat->strs,flag);
			if(flag==1){
				purl->flag=1;
				urlheadadd(purl,pmat->strs);
				return;
			}else{
				purl->flag=0;
				return;
			}
		}
		case 5:{
			flag=nullmatch(purl->urlstr);printf("--------nullmatch:/,get:%d\n",flag);
			purl->flag=flag;
			return;
		}
		case 6:{
			flag=endmatch(purl->urlstr);printf("---------endmatch: ,get:%d\n",flag);
			purl->flag=flag;
			return;
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
			if(rules[i].head==NULL){
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
			//check " "
			if(c==' '){
				pmat->flag=6;
				break;
			}
			//check "/"
			else if (c!='/') printf("error:/\n");

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
		}
		pmat=NULL;

		//read rules name
		scanf("%s ",rules[i].name);
	}
	//read urls
	for(i=0;i<m;i++){
		scanf("%s",urls[i].urlstr);
		urls[i].flag=0;
		urls[i].head=NULL;
		urls[i].name=NULL;
	}
	printf("analysis the urls:\n");
	//analysis the urls
	for(i=0;i<m;i++){
		purl=&urls[i];printf("analysis purl %d:%s\n",i,purl->urlstr);
		for(j=0;j<n;j++){
			prule=&rules[j];printf("----analysis prule %d:%s\n",j,prule->name);
			resetpurl();freehead(purl->head);purl->head=NULL;
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
	printf("print the analysised urls\n");
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
	printf("free all memory\n");
	//free all memory
	for(i=0;i<n;i++){
		freehead(rules[i].head);
	}
	for(i=0;i<m;i++){
		freehead(urls[i].head);
	}
	
	return 0;
}
