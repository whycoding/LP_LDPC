#include <stdio.h>
#include <stdlib.h>

#include "lp_var.h"
#include "glpk_var.h"


int* Getnj(int j);
void Subset(int* nj,int begin,int end,int* s,int k,int num);
int In(int i, int* nj, int* s, int k);
int Get_combination(int p,int j);
int Get_pow(int k);

void Add_st()
{
	int* nj;
	int* s;
	int j,k;
	int st_number = 0;

	//add row
	for(j = 1; j <= p; j+=2)
		st_number += Get_combination(p,j);
	st_number *= m;  //m* single row

	glp_add_rows(lp, st_number);

	for(j = 0; j < m; j++)                //Ã¿¸öÐ£Ñé½ÚµãÖ´ÐÐÒ»´Î
	{
		nj = Getnj(j);

		for(k = 1; k <= p; k += 2)        //Ñ¡È¡ÆæÊýµÄ¼¯ºÏs,ËüµÄ»ùÎªk
		{
			s = (int*)malloc(k * sizeof(int));
			Subset(nj,0,p-1,s,k,k);      //k1ÊÇsµÄ³¤¶È£¬k2ÊÇÒªÑ¡È¡ÊýµÄ¸öÊý

			free(s);
		}

		free(nj);
	}


		/*FILE* glpk_data;
		glpk_data = fopen("//home//why/document//lp//lp.txt","a+");

		for(j = 1; j <= n; j ++)
			fprintf(glpk_data,"s.t. s%d : f%d <= 1\n;", j,j);
		fprintf(glpk_data,"end;\n");

		fclose(glpk_data);
		*/

		glp_load_matrix(lp, st_number*p, ia, ja, ar);

}

int* Getnj(int j)
{
	int i;
	FILE* f;
	int* nj;
	char* tem;

	f = fopen("//home//why/document//lp//codeword//PEG36x27-Alist.txt","r");
	nj = (int*)malloc(p*sizeof(int));
	tem = (char*)malloc(3*n*sizeof(char));

	for(i = 0; i < 4+j; i ++)
	{
		fscanf(f, "%[^\n]", tem);
		fscanf(f, "%c", tem);
	}
	for(i = 0; i < p; i ++)
	{
		fscanf(f, "%s", tem );
		nj[i] = atoi(tem);
	}
	free(tem);
	fclose(f);

	//////////////////////////////////////////////////
	//for test
	//printf("j = %d nj is\n", j);
	//for(i = 0; i < p; i ++)
	//	printf("%d ",nj[i]);
	//printf("\n");

	///////////////////////////////////////////////////
	return nj;
}

void Subset(int* nj,int begin,int end,int* s,int k,int num)
{
	int i;


	char st_num[5];
	if(num == 0 )
	{
		//FILE* glpk_data;
		//static int stname = n+1;
		//glpk_data = fopen("//home//why/document//lp//lp.txt","a+");
		////////////////////////////////////////////////
		//print to test

		//printf("one %d mod subset of nj is\n",k);
		//for( i=0;i<k;i++)
		//	printf("%d ",nj[s[i]]);
		//printf("\n");
		///////////////////////////////////////////////
	    //½«ÔÚsÖÐµÄ±äÁ¿ÏµÊýÉèÎª1£¬²»ÔÚsÖÐµÄ±äÁ¿ÏµÊýÉèÎª-1
		//Ô¼Êø×ó±ß¼Óp-k,ÓÒ±ßÎªp-1
		//sÖÐÎªÔªËØµÄÐòºÅ ±ØÐës[i] = nj[s[i]];²Å¿ÉÊ¹ÓÃ£¡£¡£¡£¡£¡£¡£¡

		/*
		 if(In(nj[0], nj, s, k))
			fprintf(glpk_data,"s.t. s%d : f%d", stname++,nj[0]);
		else
			fprintf(glpk_data,"s.t. s%d : -f%d", stname++,nj[0]);
		for( i=1; i < p; i++)
		{
			if(In(nj[i], nj, s, k))
				fprintf(glpk_data,"+f%d", nj[i]);
			else
				fprintf(glpk_data,"-f%d", nj[i]);
		}
		fprintf(glpk_data,"+%d <= %d;\n", p-k,p-1);

		fclose(glpk_data);
		*/

	//////////////////////////////////////////////
		for( i=0; i < p; i++)
		{
			if(In(nj[i], nj, s, k))
			{
			ia[indication] = ia_num;
			ja[indication] = nj[i];
			ar[indication] = 1;
			indication ++;
			}
			else
			{
			ia[indication] = ia_num;
			ja[indication] = nj[i];
			ar[indication] = -1;
			indication ++;
			}
		}


		sprintf(st_num, "%d", ia_num);

		glp_set_row_name(lp, ia_num, st_num);
		glp_set_row_bnds(lp, ia_num, GLP_UP, 0.0, (float)(k-1));
		ia_num ++;



		return ;
	}

	for(s[k-num] = begin; begin <= end-num+1; begin++ )
	{
		s[k-num] = begin;
		Subset(nj,begin+1,end,s,k,num-1);
	}
}

int In(int i, int* nj, int* s, int k)
{
	int tem;
	for(tem = 0; tem < k; tem++)
	{
		if(i == nj[s[tem]])
			break;
	}
	if(tem < k)
		return  1;

	return 0;


}


int Get_combination(int p,int j)
{
	return Get_pow(p)/Get_pow(j)/Get_pow(p-j);
}

int Get_pow(int k)
{
	int i;
	int result = 1;
	for(i = k; i > 1; i--)
		result *= i;
	return result;
}
