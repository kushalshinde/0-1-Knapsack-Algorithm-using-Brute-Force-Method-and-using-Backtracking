#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int earning_max = 0;
int position = 0;
int weight_max=0;
int *bag;

struct index{
	int	mass;
	int	earning;
};


void brute (int position, int total_element, struct index now, struct index N[], int element_knapsack[], int maxelement_knapsack[])
{
	if(total_element < position+1) 
		return;

	now.mass = now.mass + N[position].mass;
	now.earning = now.earning + N[position].earning;
	
	element_knapsack[position] = 1;
	
	if(earning_max < now.earning)
	{
		if(now.mass <= weight_max)
		{
			earning_max = now.earning;
			int i;
			
			for(i=0;i < total_element;++i){
				maxelement_knapsack[i] = element_knapsack[i];
			}
		}	
	}
	
	brute(position+1, total_element, now, N, element_knapsack, maxelement_knapsack);
	element_knapsack[position] = 0;
	now.mass -= N[position].mass;
	now.earning -= N[position].earning;
	brute(position+1 ,total_element ,now ,N ,element_knapsack ,maxelement_knapsack);
}


int main(int argc,char* argv[])
{
	int i;
	int total_element;
	char buff[255];
	FILE *file_ptr;
	file_ptr=fopen(argv[1],"r");
    
	if (file_ptr == NULL)
    {
    	printf("\nError opening file ...\n");	
    	exit(1);
    }
 	else
 	{
		fscanf(file_ptr,"%s",buff);	
		total_element = atoi (buff);

		struct index N[total_element];

		int mass[total_element];
		int earning[total_element];
////////////////////////////////////////////////////////
		
		for(i=0;i < total_element;++i){
			fscanf(file_ptr,"%s",buff);
			N[i].mass = atoi(strtok(buff," ,"));
		}

		for(i=0;i < total_element;++i){
			fscanf(file_ptr,"%s",buff);
			N[i].earning = atoi(strtok(buff," ,"));
		}
////////////////////////////////////////////////////////

		fscanf(file_ptr,"%s",buff);
		weight_max = atoi (buff);

		int element_knapsack[total_element];
		int	maxelement_knapsack[total_element];

		
		for(i=0;i < total_element;++i){
			element_knapsack [total_element] = 0;
			maxelement_knapsack [total_element] = 0;
		}
		
		bag = maxelement_knapsack;
		struct index now; 
		now.earning = 0;
		now.mass = 0;
		brute (0,total_element, now, N, element_knapsack, maxelement_knapsack);

		FILE *fp;
		fp = fopen("brute_output.txt", "w");

		if (fp == NULL)
		{
			printf("Error opening file...\n");
			exit(1);
		}
		
		int max=0;
		
		for(i=0;i < total_element;++i){
			if(maxelement_knapsack[i]==1)
			max=max+N[i].mass;
		}
		
		fprintf(fp, "%d\n", max);
		max=0;
		int itemcount=0;
		
		for(i=0;i < total_element;++i){
			if(maxelement_knapsack[i]==1)
			{
				max=max+N[i].earning;
				itemcount++;
			}
		}
		fprintf(fp,"%d",max);

		//printf("\n");
		fprintf(fp,"\n");

		int x=0;	
		for(i=0;i < total_element;++i){
			if (bag[i] == 1)
			{
				if(x == itemcount-1)
				{
					fprintf(fp,"%d", i);
				}
				else
				{
					fprintf(fp,"%d, ",i);
					x++;
				}
			}
		}
		fclose(fp);
	}
	fclose(file_ptr);
	//printf("\n");
}