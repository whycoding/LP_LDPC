#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "lp_var.h"
#include "glpk_var.h"

float GeneGauss(int mean,float stdev);

void Add_obj()
{

	int i;
	char num[5];
	sig = (float*)malloc(n * sizeof(float));
	for(i = 0; i < n; i++)
		sig[i] = 1.0;

	stdev = sqrt(1.0 / (2*CODERATE*pow(10,SNR/10)));

	for(i = 0; i < n; i++)
		sig[i] += GeneGauss(0,stdev);

	/////////////////////////////////////////////////////////
	//	assign the sig to cplex as the r
	//  here just print them
/*	glpk_data = fopen("//home//why/document//lp//lp.txt","a+");
	fprintf(glpk_data,"minimize f : %f*f1",sig[0]);
	for(int i =1; i < n; i ++)
		fprintf(glpk_data,"+%f*f%d" , sig[i],i+1);
	fprintf(glpk_data,";\n");
	fclose(glpk_data);
*/
	/////////////////////////////////////////////////////////
	glp_add_cols(lp, n);
	glp_set_obj_dir(lp, GLP_MIN);
	for(i = 1; i <= n; i ++)
	{

		sprintf(num, "%d", i);
		glp_set_col_name(lp, i, num);
		glp_set_col_bnds(lp, i, GLP_DB, 0.0, 1.0);
		glp_set_obj_coef(lp, i, sig[i-1]);
	}
     free(sig);

}

float GeneGauss(int mean,float stdev)
{
	static float V1, V2, S;
	static int phase = 0;
	float X;

	if(phase == 0)
	{
		do
		{
			float U1 = (float)rand() / RAND_MAX;
			float U2 = (float)rand() / RAND_MAX;

			V1 = 2 * U1 - 1;
			V2 = 2 * U2 - 1;
			S = V1 * V1 + V2 * V2;
		}while(S >= 1 || S == 0);

		X = V1 * sqrt(-2 * log(S) / S);
	}
	else
		X = V2 * sqrt(-2 * log(S) / S);

	phase = 1 - phase;
	return (X * stdev + mean);
}
