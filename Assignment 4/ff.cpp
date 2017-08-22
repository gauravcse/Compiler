#include<bits/stdc++.h>
using namespace std;
set<char> NTs,Ts;
vector<char> T;
vector<char> NT;
char **FT;
char **FLWT;
vector<string> P;
int num_prod,nt_num,t_num;

int getIndex(vector<char> A,char c)
{
	int i=0;
	for(i=0;i<A.size();i++)	
	{
		if(A[i]==c)
		return i;
	}
	return -1;
}

void addEpsilon(char c)
{
	FT[getIndex(NT,c)][t_num-1]='e';
}

int hasEpsilon(char c)
{
	if(FT[getIndex(NT,c)][t_num-1]=='e')
		return(1);
	return(0);
}

int isNonTerminal(char c)
{
	int i;
	for(i=0;i<NT.size();i++)	
	{
		if(NT[i]==c)
		{
			return 1;
		}
	}
	return 0;
}

int isTerminal(char c)
{
	int i=0;
	for(i=0;i<T.size();i++)	
	{
		if(T[i]==c)
			return 1;
	}
	return 0;
}

void ComputeFollow()
{
	int len,i,j,k,added=0;
	char sym1,sym2,elm1,elm2,sym;
	FLWT[getIndex(NT,NT[0])][t_num-1]='$';
	for(i=0;i<num_prod;i++)
	{
		len=P[i].length();
		for(j=3;j<len;j++)	
		{
			sym1=P[i][j];
			sym2=P[i][j+1];
			if(isNonTerminal(sym1) && isTerminal(sym2))
			{
				FLWT[getIndex(NT,sym1)][getIndex(T,sym2)]=sym2;
			}
		}
	}

	for(i=0;i<num_prod;i++)
	{
		len=P[i].length();
		for(j=3;j<len;j++)
		{
			sym1=P[i][j];
			sym2=P[i][j+1];
			if(isNonTerminal(sym1) && isNonTerminal(sym2))
			{
				for(k=0;k<t_num;k++)
				{
					elm1=FLWT[getIndex(NT,sym1)][k];
					elm2=FT[getIndex(NT,sym2)][k];
					if(elm1!=elm2)
					{
						if(elm2!='\0' && elm2!='e')
						{
							FLWT[getIndex(NT,sym1)][k]=elm2;
						}
					}
				}
			}
		}
	}

	for(i=0;i<num_prod;i++)
	{
		sym1=P[i][P[i].length()-1];
		if(isNonTerminal(sym1))
		{
			sym2=P[i][0];
			for(k=0;k<t_num;k++)
			{
				elm1=FLWT[getIndex(NT,sym1)][k];
				elm2=FLWT[getIndex(NT,sym2)][k];
				if(elm1!=elm2)
				{
					if(elm2!='\0' && elm2!='e')
					{
						added=1;
						FLWT[getIndex(NT,sym1)][k]=elm2;
					}
				}
			}
		}
		sym=P[i][P[i].length()-1];
		if(isNonTerminal(sym) && hasEpsilon(sym))
		{
			sym1=P[i][P[i].length()-2];
			if(isNonTerminal(sym1))
			{
				sym2=P[i][0];
				for(k=0;k<t_num;k++)
				{
					elm1=FLWT[getIndex(NT,sym1)][k];
					elm2=FLWT[getIndex(NT,sym2)][k];
					if(elm1!=elm2)
					{
						if(elm2!='\0' && elm2!='e')
						{
							added=1;
							FLWT[getIndex(NT,sym1)][k]=elm2;
						}
					}
				}
			}
		
			if(i==t_num+1)
			{
				if(added)
				{
					i=-1;
					added=0;
				}
			}
		}
	}
}

void ComputeFirst() {
	int added=0,i,j,k;
	char X,elm1,elm2;
	for(i=0;i<nt_num;i++) {
		for(j=0;j<t_num;j++) {
			FT[i][j]='\0';
		}
	}
	for(i=0;i<num_prod;i++) {
		X = P[i][3];
		if(X=='e')
		{
			addEpsilon(P[i][0]);
		}
		else if(isTerminal(X))
		{
			FT[getIndex(NT,P[i][0])][getIndex(T,X)]=X;
		}
	}
	
	for(i=0;i<num_prod;i++)
	{
		X = P[i][3];
		if(isNonTerminal(X))
		{
			for(j=3;j<P[i].length();j++)	
			{
				X=P[i][j];
				for(k=0;k<nt_num;k++)
				{
					elm1=FT[getIndex(NT,P[i][0])][k];
					elm2=FT[getIndex(NT,X)][k];
					if(elm1!=elm2)
					{
						if(elm2!='\0')
						{
							added=1;
							FT[getIndex(NT,P[i][0])][k]=elm2;
						}
					}
				}
				if(!hasEpsilon(X))
				{
					break;
				}
			}
			if(j==P[i].length())
			{
				added=1;
				FT[getIndex(NT,P[i][0])][5]='e';
			}
		}
		if(i==t_num+1)
		{
			if(added)
			{
				i=-1;
				added=0;
			}
		}
	}
}
void chomp(char *s) {
    while(*s && *s != '\n' && *s != '\r') s++;
 
    *s = '\0';
}
int getpos(char c) {
	int i;
	for(i=0;i<nt_num;i++)
	{
		if(NT[i]==c)
			return i;
	}
	return -1;
}	
bool contains_e(string s)
{
	for(int i=0;i<s.length();i++)
	{
		if(s[i]=='e')
			return true;
	}
	return false;
}	
string get_row(char **arr,int n)
{
	string ss="";
	for(int i=0;i<t_num;i++)
	{
		ss+=arr[n][i];
	}
	return ss;
}

int main()
{
	int i,j;
	FILE *fp;
	int max=10;
	fp=fopen("gmr.txt","r");
	char s[max];
	while(fgets(s,100,fp)!=NULL)
	{
		chomp(s);
		string ss(s);
		P.push_back(s);
		num_prod++;
	}
	for(int i=0;i<num_prod;i++)
	{
		if(find(NT.begin(),NT.end(),P[i][0])==NT.end())
			NT.push_back(P[i][0]);

	}
	nt_num=NT.size();
	for(int i=0;i<num_prod;i++)
	{
		for(int j=3;j<P[i].length();j++)
		{
			if(P[i][j]>'a' && P[i][j]<'z' && find(T.begin(),T.end(),P[i][j])==T.end() && find(NT.begin(),NT.end(),P[i][j])==NT.end() )
			{
				T.push_back(P[i][j]);
			}
		}
	}
	for(int  i=num_prod-1;i>=0;i--)
	{
		for(int j=3;j<P[i].length();j++)
		{
			if(find(T.begin(),T.end(),P[i][j])==T.end() && find(NT.begin(),NT.end(),P[i][j])==NT.end())
			{
				T.push_back(P[i][j]);
			}
		}
	}
	
	reverse(T.begin(),T.end());
	swap(T[nt_num-2],T[nt_num-3]);
	t_num=T.size();
	FT = new char*[nt_num];
	for(int i = 0; i < nt_num; ++i)
	    FT[i] = new char[t_num];
	FLWT = new char*[nt_num];
	for(int i = 0; i < nt_num; ++i)
	    FLWT[i] = new char[t_num];
	ComputeFirst();
	for(i=0;i<num_prod;i++)
	{
		cout<<P[i]<<endl;
	}

	for(i=0;i<nt_num;i++)
	{
		printf("FIRST(%c)={",NT[i]);
		for(j=0;j<t_num;j++)
		{
			if(FT[i][j]!='\0')
				printf("%c,",FT[i][j]);
		}
		printf("\b}\n");
	}

	ComputeFollow();
	
	for(i=0;i<nt_num;i++)
	{
		printf("FOLLOW(%c)={",NT[i]);
		for(j=0;j<t_num;j++)
		{
			if(FLWT[i][j]!='\0')
			printf("%c,",FLWT[i][j]);
		}
		printf("\b}\n");
	}

	map< pair<char,char>, string > table;
	for(int i=0;i<nt_num;i++)
	{
		for(int j=0;j<t_num;j++)
		{
			if(T[j]!='e'){
			pair<char,char> pp = make_pair(NT[i],T[j]);
			table[pp]="";
			}
		}
		pair<char,char> pp = make_pair(NT[i],'$');
		table[pp]="";
	}
	
	for(int i=0;i<num_prod;i++)
	{
		char nt = P[i][0];
		int ind=getpos(nt);
		string s(P[i]);
		
		if(!contains_e(s))
		{	
			string t=get_row(FT,ind);
			for(int j=0;j<t.length();j++)
			{
				if(FT[ind][j]!='e' && FT[ind][j])
				{
					pair<char,char> pp = make_pair(NT[getpos(nt)],FT[ind][j]);
					table[pp]=s;
				}
			}
		}
	}	
	for(int i=0;i<num_prod;i++)
	{
		char nt = P[i][0];
		int ind=getpos(nt);
		string s(P[i]);
		
		if(contains_e(s))
		{
			string t=get_row(FLWT,ind);
			for(int j=0;j<t.length();j++)
			{
				if(FLWT[ind][j])
				{
					pair<char,char> pp = make_pair(NT[getpos(nt)],FLWT[ind][j]);
					table[pp]=s;
					
				}
			}
		}
	}
	cout<<"PARSING TABLE::"<<endl<<"(row,column)=production rule"<<endl;
	for(map<pair<char, char> ,string> :: iterator it = table.begin(); it != table.end();it++) {
		cout<<it->first.first<<","<<it->first.second<<"="<<it->second<<endl;
	}
	stack<char> exprs;
	//vector<string> exprs;
	
	exprs.push('$');
	exprs.push(NT[0]);
	
	FILE *fq=fopen("expr.txt","r");		
	char e[10];
	fgets(e,100,fq);
	chomp(e);
	string ss(e);
	char top,symbol;
	int pointer=0;
	cout<<"\nParser\nTop\t\tPointer\t\tProduction"<<endl;
	while(!exprs.empty())
	{
		top=exprs.top();
		exprs.pop();
		symbol=ss[pointer];

		pair<char,char> pp = make_pair(top,symbol);
		pair<char,char> pp1 = make_pair(symbol,top);
		cout<<top<<"\t\t"<<symbol<<"\t\t"<<table[pp]<<endl;
		if(symbol!='$' && top==symbol)
		{
			pointer++;
			continue;
		}
		else if(symbol=='$' && top==symbol)
		{
			cout<<"Accepted"<<endl;
			break;
		}	
		if(table.count(pp)!=0 && table[pp].length()>3)
		{
			string to_be_pushed=table[pp].substr(3);
			if(to_be_pushed=="e")
			{
				continue;
			}	
			reverse(to_be_pushed.begin(),to_be_pushed.end());
			for(int l=0;l<to_be_pushed.length();l++)
			{
				exprs.push(to_be_pushed[l]);
			}
		}
		else
		{
			cout<<"Error"<<endl;
			exit(0);
		}

	}
	
	return 0;
}
