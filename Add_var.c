#include <stdio.h>
#include <stdlib.h>
#include "lp_var.h"
#include "glpk_var.h"

void Add_var()
{
	FILE* f;
	char num_m [5];
	char num_n [5];
	char num_p [5];
	char num_q [5];

	f = fopen(codeword_txt,"r");
	if( f == NULL)
	{
		printf("read the ldpc matrix failed\n");
		return;
	}

	fscanf(f, "%s", num_m);
	fscanf(f, "%[^\n]", num_n);
	fscanf(f, "%s", num_p);
	fscanf(f, "%[^\n]", num_q);
	fclose(f);

	m = atoi(num_m);
	n = atoi(num_n);
	p = atoi(num_p);
	q = atoi(num_q);
	/////////////////////////////////////////////////////////
	//验证结果
	//printf("the matrix is %d * %d with p = %d , q = %d\n", m,n,p,q);
	/////////////////////////////////////////////////////////////

	CODERATE = (n-m) / (double)(n);

	return ;
}
