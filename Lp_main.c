#include "glpk_var.h"
#include "lp_var.h"
#include <stdio.h>

int n,m,p,q;           //p is the num of 1 in row ,q is in column
float* sig;
float CODERATE;
float stdev;           //put the difinition of SNR to top_main


//notice the size of ia!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 glp_prob *lp;
 int ia[1+25000];
 int ja[1+25000];
 double ar[1+25000];

int indication;
int ia_num;
glp_smcp parm;

void Init();
void Add_var();
void Add_obj();
void Add_st();
int Judge();
void Test();
void Test2();

int Lp_main()
{
	Init();

//	printf("\n\n\nfirst step : add the variables\n");
	Add_var();

//	printf("\n\n\nsecond step : add the objective\n");
	Add_obj();

//	printf("\n\n\nthird step : add the constraints\n");
	Add_st();
//Test();
//Test2();
	return Judge();
}


void Init()
{
	lp = glp_create_prob();
	glp_set_prob_name(lp, "sample");

	glp_init_smcp(&parm);
	parm.msg_lev = GLP_MSG_OFF;

	ia_num=1;
	indication=1;
}

int Judge()
{
	int i;
	double fi;

	glp_simplex(lp, &parm);
	for(i = 1; i <= n; i ++)
	{
		fi = glp_get_col_prim(lp, i);
//		printf("%lf \n", fi);
		if(fi != 0)
			break;
	}
	glp_delete_prob(lp);

	if(i <= n)
	{
	     printf("fail\n");return 1;
	}

	else
	{
	     printf("succeed\n");return 0;
	}

}


void Test()
{
     FILE* ftest;
     int i,j;
     int len;
     int ind[10];
     double var[10];

     ftest = fopen("//home//why//document//ceshi//multiple//ftest.txt","a+");

     fprintf(ftest,"the obj dir is %d\n",glp_get_obj_dir(lp));
     for( i = 1; i <= glp_get_num_cols(lp); i ++)
     {
          fprintf(ftest, "+ %lf*f%d", glp_get_obj_coef(lp,i),i);
     }

     fprintf(ftest,"\nthe number of row is %d\n",glp_get_num_rows(lp));

     for( i = 100; i <= glp_get_num_rows(lp); i ++)
     {
          fprintf(ftest,"the type of row %s is %d ",glp_get_row_name(lp, i),glp_get_row_type(lp, i));
          fprintf(ftest," up bound is %lf\n",glp_get_row_ub(lp, i));

          len = glp_get_mat_row(lp, i, ind, var);
          for(j = len; j > 0; j--)
               fprintf(ftest, "f[%d]=%f ",ind[j],var[j]);
          fprintf(ftest," \n");

     }


     fprintf(ftest,"the number of coloum is %d\n",glp_get_num_cols(lp));

     for( i = 1; i <= glp_get_num_cols(lp); i ++)
     {
          fprintf(ftest,"the type of coloum %s is %d ",glp_get_col_name(lp, i),glp_get_col_type(lp, i));
          fprintf(ftest,"low bound is %lf, up bound is %lf\n",glp_get_col_lb(lp, i),glp_get_col_ub(lp, i));
     }


     fclose(ftest);
}

void Test2()
{
     FILE* ftest;
     int i,j;

     ftest = fopen("//home//why//document//ceshi//multiple//ftest2.txt","a+");

     for(i = 0, j = 1; i < 800; i ++)
     {
          fprintf(ftest,"this is row %d\n", ia[i*6+1]);
          for(j = 1; j <=6; j++)
          {
               fprintf(ftest,"+ %lf*f%d",ar[i*6+j], ja[i*6+j]);
          }
          fprintf(ftest, "\n");
     }

     fclose(ftest);
}

