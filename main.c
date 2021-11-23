#include<stdio.h>
#include<stdlib.h>
#include<string.h>



struct mot{
    char* str;
    int taille;
} ;
typedef struct {
    struct mot* mot;
    int taille;
}dict ;


//Chargement du dictionnaire.
dict charger_dico(FILE* f,int N) 
{
    dict dico;
    dico.mot = (struct mot*) malloc( N * sizeof(struct mot));
    dico.taille = N ;
    char buffer[40];
    int i = 0 ;
    int Taille_buffer = 0;
    for(int j=1;j<N;j++) 
    {
        fscanf(f,"%s",buffer); 
        Taille_buffer = strlen(buffer);     
        dico.mot[i].str= (char*)malloc((Taille_buffer + 1)*sizeof(char));
        strcpy(dico.mot[i].str,buffer);
        dico.mot[i].taille = Taille_buffer;
        i++;
    }
    return dico;
}

//tailles des mots
void statistiques(dict d)
{
	//Recherche du Max du dictionnaire
	int Max=1;
	int M;

	for(int i=0;i<d.taille;i++)
	{
		M = d.mot[i].taille;   
		if(M>Max){
			Max = M;
		}
	}
	//Calcul de la moyenne
	float Moy;
	for(int j=0; j<d.taille;j++)
	{
		Moy = Moy + d.mot[j].taille;
	}
	float moyenne = Moy/d.taille;
	
	
	//creation tableau de nombre d'occurence des tailles
	int Tab_occur[Max];
	for(int i=0;i<Max;i++){
		Tab_occur[i] = 0;
		for( int j=0; j<d.taille;j++)
		{
			if(d.mot[j].taille == i+1)
			{
				Tab_occur[i]++;
			}
		}			
	}
	
	printf("Lancement de la recherche des mots (STATS WORDS)\n");
	printf("(II) Taille minimum des mots : %d\n",1);
	printf("(II) Taille maximum des mots : %d\n",Max);
	printf("(II) Taille moyenne des mots : %f\n",moyenne);
	
	
	for(int i=0;i<Max;i++)
	{
		double p = (double)Tab_occur[i]*100/((double)d.taille);
		printf("(II) Taille %d\t: %d mots \t ( %.3f %% ) \t", i+1, Tab_occur[i],p);
		int a = p/(0.25)+1;
		for(int i=0; i<a;i++)
		{
			printf("#");
		}
		printf("\n");
	}
}
//La taille du dictionnaire
int taille_dico(FILE* nom_fichier){
	int taille_dico = 0;
	char buffer[100];
	if(nom_fichier == NULL)
	{
		printf("fichier non trouvé");
	}
	while(fscanf(nom_fichier,"%s",buffer)!=EOF){
		taille_dico++;
	}
	return taille_dico;
}

int nbLettres(dict d)
{
	int n;
	for(int i=0 ; i<d.taille ; i++)
	{
		for(int k=0;k<d.mot[i].taille;k++)
		{
			n++;
		}
	}
	return n;
}


//statistique_2
void statistiques_2(dict d)
{
	int n = nbLettres(d);
	char alphabet[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	int alpha_occur[26];
	for(int j=0 ; j<26 ; j++)
	{
		alpha_occur[j]=0;
		for(int i=0 ; i<d.taille ; i++)
		{
			for(int k=0;k<d.mot[i].taille;k++)
			{
				if(d.mot[i].str[k] == alphabet[j])
				{
					alpha_occur[j]++;
				}
			}
		}
	}
	printf("Lancement de la recherche des mots (STATS LETTERS)\n");
	for(int i=0;i<26;i++)
	{
		double p = (double)alpha_occur[i]*100/(double)n;
		printf("(II) Lettre (%c) : %d  lettres (%.3f%%) \t", alphabet[i],alpha_occur[i],p); 
		int a = p/(0.25)+1;
		for(int i=0; i<a;i++)
		{
				printf("#");
		}
		printf("\n");
	}
	
	
}
//statistique_3
int est_palindrome(char* str)
{
	int l = strlen(str);
    int m = l / 2; 
    int i = 0;
    while (i < m) {
        if (str[i] != str[l - i - 1])
            return 0;
        i = i + 1;
    }
    return 1;
}
void statistiques_3(dict d1,dict d2)
{
	int cpt=0;
	int cpt_2=0;
	for(int i=0;i<d1.taille;i++)
	{
		if(est_palindrome(d1.mot[i].str)==1)
		{
			cpt_2++;
			printf("Le mot numero %d (%s) est %deme un plindrome\n",cpt,d2.mot[i].str,cpt_2);
		}
		cpt++;
	}
}


int est_anagramme(char* str_1,char* str_2)
 {
	int l1 = strlen(str_1);
	int l2 = strlen(str_2);
	int occ[l1];
	if(l1!=l2){return 0;}
	for(int i=0;i<l1;i++)
	{
		occ[i]=0;
		for(int j=0;j<l2;j++)
		{
			if(str_2[j]==str_1[i])
			{
				occ[i]++;
			}				
		}
	}
	for(int i=0;i<l2;i++)
	{
		if(occ[i]==0){return 0;}
		if(occ[i]>1)
		{
			int cpt=0;
			for(int j=0;j<l1;j++)
			{
				if(str_1[i]==str_1[j]){cpt++;}
			}
			if(cpt!=occ[i]){return 0;};
		}
	}
	return 1;
}
void anagramme(dict d1,dict d2, char* s)
{
	printf("lancement de la recherche de mots (anagrammes)\n");
	for(int i=0;i<d1.taille;i++)           
	{
		int cpt = 0;
		if(est_anagramme(s,d1.mot[i].str))
		{
			cpt++;
			printf("  le mot numero %d (%s) est %deme un anagramme\n",i,d2.mot[i].str,cpt);
		}			
	}
}




int est_pattern(char* str1,char* str2)
{
	if(strlen(str1) != strlen(str2)){return 0;};
	int l = strlen(str1);
	//int cpt=0;
	for(int i=0; i<l; i++)
	{		
		if(str2[i] == '?' )
		{
			continue ;
		}
		else if(str1[i]!=str2[i])
		{
			return 0;
		}
	}
	return 1;
}


void pattern(char* str,dict d1,dict d2)
{
	int count = 0;
	printf("Lancement de la recherche des mots (?)\n");
	
  for(int i=0; i<d1.taille;i++)
  {
    if(d1.mot[i].taille!=strlen(str)){continue;}
    if(est_pattern(d1.mot[i].str,str))
    {
      count ++;
      printf("\tle mot numero %d (%s) est %deme repond au critere\n",i,d2.mot[i].str,count);
    }
  }
	printf("On a trouve %d mots\n",count);
}




void pattern_2(char* str,dict d1, dict d2)
{
	printf("Lancement de la recherche de mot (*)\n");
	int count = 0;
	int l = strlen(str);
	int p1,p2;
	for(int i=1;i<l;i++)
	{
		if(str[i] == '*'){
			p1 = i;
			p2 = i+1;
		}
	}
	if(str[0] == '*'){
		p1=0;
		p2=1;
	}
	for(int i=0; i<d1.taille; i++)
	{
		int len = strlen(d1.mot[i].str);
		int cpt1 = 0;
		int	cpt2 = 0;
		for(int j=0;j<p1;j++)
		{
			if(d1.mot[i].str[j] == str[j])
				cpt1 ++;
		}
		for(int k=p2; k<l; k++)
		{
			if(d1.mot[i].str[len-l+k] == str[k])
				cpt2 ++;
		}
		if((cpt1 == p1) && (cpt2 == (l-p2)))
		{
			count++;
			printf("\tLe mot numero %d (%s) est %ieme repond au critere\n",i,d2.mot[i].str,count);
		}
	}
}

void scrabble(dict d1,dict d2, char* str)
{
	printf("Lancement de la recherche des mots (SCRABBLE)\n");
	int l = strlen(str);
	int count = 0;
	for(int i=0; i<d1.taille; i++)
	{	
		if(d1.mot[i].taille <= l)
		{
			int occur[l];
			//On remplit le tableau occur de 0.
			for(int i = 0 ; i<l ; i++)
			{
				occur[i] = 0;
			}
			//On parcourt les lettres des mots de dictionnaire.
			for(int j=0; j<d1.mot[i].taille; j++){
				//On parcourt les lettres de str.
				for(int k=0; k<l;k++){
					if(d1.mot[i].str[j] == str[k]){
						occur[k]++;
					}
				}
			}
			int cpt = 0;
			for(int i = 0 ; i<l ; i++)
			{
				if(occur[i] == 1){
					cpt++;
				}
			}
			if(cpt == d1.mot[i].taille){
					count++;
					printf("\tLe mot numero %d (%s) est %deme repond au critere\n",i,d2.mot[i].str,count);
			}
		}
	}
}




void correc(dict d1, dict d2, char* str)
{
	printf("lancement de la recherche de mots (CORRECTION)\n");
	int r=0;
	int L = strlen(str);
	char str2[L]; 
	for(int k=0;k<L;k++)
	{
		str2[k] = str[k];
	}
	for(int j=0;j<d1.taille;j++)
	{
		if(L!=d1.mot[j].taille)
		{
			continue;
		}
		for(int i=0;i<L;i++)
		{
			str2[i] = '?';
			
			if(est_pattern(d1.mot[j].str,str2))
			{
				r++;
				printf("Le mot numero %d (%s) est %dieme repond au critere\n",i,d2.mot[j].str,r);
			}
			str2[i] = str[i];
		}
	}
}




int main()
{	
	
	FILE* fichier_1;
	FILE* fichier_2;
	fichier_1 = fopen("french_word_sudent-master\\dic\\french-sans-accents-utf8.txt","r");
	fichier_2 = fopen("french_word_sudent-master\\dic\\french-avec-accents-utf8.txt","r");
	int n=taille_dico(fichier_1);
	//printf("la taille du dictionnaire est:%d\n",n);
	//printf("%d",est_anagramme("aabc","abcc"));
	fseek(fichier_1,0,SEEK_SET);
	fseek(fichier_2,0,SEEK_SET);
	dict dico1 = charger_dico(fichier_1,n);
	dict dico2 = charger_dico(fichier_2,n);
	fclose(fichier_1);
	fclose(fichier_2);
	//statistiques(dico1);
	//statistiques_2(dico1);
	//statistiques_3(dico1,dico2);
	//anagramme(dico1,dico2, "mange");
	//pattern("mang?",dico1,dico2);
	//pattern_2("man*ter",dico1, dico2);   
	scrabble(dico1,dico2, "azerty");
	//correc(dico1, dico2, "manget");
	
	
	
	return 0;
}