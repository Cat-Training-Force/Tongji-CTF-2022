#include<bits/stdc++.h>
using namespace std;
char s[11];
char mp[25]={
	116,47,36,36,36,
	36,47,47,36,36,
	47,36,47,47,47,
	47,47,36,36,47,
	36,36,36,36,117,
};

void change(){
	for(int i=0;i<25;i++){
		int x=-1,y=mp[i];
		while(x){
			x--;y++;
		}mp[i]=y;

	}
}

int main(){
	printf("input:\n");
	scanf("%s",s);	
	int n;
	n=strlen(s);
	printf("Waiting for the maze:\n");
	change();
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			printf("%c ",mp[i*5+j]);
		}
		printf("\n");
	}
	if(n!=8){printf("fail!\n");exit(0);}
	if(n==8){
		int i;
		int a1=0,a2=0;
		if(mp[a1*5+a2]!='s'){
			printf("fail!\n");exit(0);
		}
		for(i=0;i<8;i++){
			if(s[i]=='U'){
				a1--;
				if(a1<0||mp[a1*5+a2]=='#'){
					printf("fail!\n");exit(0);
				}
			}
			if(s[i]=='D'){
				a1++;
				if(a1>=5||mp[a1*5+a2]=='#'){
					printf("fail!\n");exit(0);
				}
			}
			if(s[i]=='L'){
				a2--;
				if(a2<0||mp[a1*5+a2]=='#'){
					printf("fail!\n");exit(0);
				}
			}
			if(s[i]=='R'){
				a2++;
				if(a2>=5||mp[a1*5+a2]=='#'){
					printf("fail!\n");exit(0);
				}
			}
		}
		if(mp[a1*5+a2]=='t'){
			printf("good!\n");
			printf("flag{%s}",s);
		}else {
			printf("fail!\n");exit(0);
		}
	}return 0;
}
