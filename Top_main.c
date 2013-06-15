#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float SNR ;
int  NZERO = 100;

int Glpk();
int Lp_main();
void Gunplot();

int main()
{
	int num;
	FILE* glpk_out;

	glpk_out = fopen("//home//why//document//lp//result//glpk_out_test.txt", "a+");

    srand(time(0));

	for(SNR = 1.0; SNR <= 6.0; SNR += 0.5)
	{
		num = Glpk();
		fprintf(glpk_out,"SNR is %f, failure number is %d, total number is %d, WER is %f\n", SNR, NZERO, num, NZERO/(float)num);
        printf("%f %f\n", SNR,NZERO/(float)num);
        fflush(glpk_out);

	}
	fclose(glpk_out);

	Gunplot();
	return 0;
}


int Glpk()
{
	int num_total = 0;
	int num_nzero = 0;

	while(num_nzero < NZERO)
	{
		if(Lp_main())
			num_nzero ++;
		num_total ++;
		printf("SNR is %f, failure number is %d, total number is %d\n", SNR, num_nzero, num_total);
	}

	return num_total;
}

void Gunplot()
{

}
