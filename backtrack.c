#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int max_earn = 0;
int component = 0;
int max_load=0;
int *bag;

struct fork
{
	int	mass;
	int	earning;
	int list_num;
};


int reverse (int component, struct fork current, struct fork N[], int max_load, int total_element)
{
	int j, x[total_element];
	int bound = current.earning;
	for(j=0;j < total_element;j++){
	   x[j] = 0; 
	}
	
	
	for(j=0;total_element >= component && max_load > current.mass;j+=1){
	    if (max_load >= current.mass + N[j].mass){                  
	         x[j] = 1;                                        
			 current.mass = current.mass + N[j].mass; 
			 bound = bound + N[j].earning;
	   	}
	   else{
	        x[j] = (max_load - current.mass)/N[j].mass;  
			current.mass = max_load; 
			bound = bound + N[j].earning * x[j];
	   }
	}
	return bound;
}

void knapsack (int component, int total_element, struct fork current, struct fork N[], int knap_Element[], int knap_Maxweight[])
{
	
	int x;
	int bound = reverse (component, current, N, max_load, total_element);

	if(max_earn > bound) 
		return;

	if(total_element < component+1) 
		return;
	
	current.mass += N[component].mass;
	current.earning += N[component].earning;
	knap_Element[component] = 1;
	
	if (max_load >= current.mass){
		if(current.earning > max_earn){
			max_earn = current.earning;
			for(x=0; x < total_element; ++x){
				knap_Maxweight[x] = knap_Element[x];
			}
		}
	}
	
	knapsack(component+1, total_element, current, N, knap_Element, knap_Maxweight);
	knap_Element[component] = 0;
	current.mass -= N[component].mass;
	current.earning -= N[component].earning;
	knapsack(component+1 ,total_element ,current ,N ,knap_Element ,knap_Maxweight);
}


int main(int argc, char* argv[])
{
	int i;
	int total_element;
	char buff[255];
	
	int j, swap_Weight = 0, swap_Item = 0;														

	struct fork swap;

	
	FILE *file_ptr;
	file_ptr = fopen(argv[1],"r");
    if (file_ptr == NULL){
    	printf("\nError opening file ...\n");
    	exit(1);
    }
 	else{	

		fscanf(file_ptr,"%s",buff);	

		total_element = atoi (buff);
		struct fork N[total_element];
		
		int mass[total_element];
		
		int earning[total_element];
		
		for(i=0;i < total_element; ++i){
			fscanf(file_ptr,"%s",buff);
			N[i].mass = atoi(strtok(buff," ,"));
			N[i].list_num = i;
		}
		
		for(i=0;i < total_element;++i){
			fscanf(file_ptr,"%s",buff);
			N[i].earning = atoi(strtok(buff," ,"));
		}

		fscanf(file_ptr,"%s",buff);
		max_load = atoi (buff);

	
		
		for(i=0;i < total_element - 1;++i){
			for(j=0;j < total_element - i - 1;++j){
				float no1=N[j].earning/N[j].mass,no2=N[j+1].earning/N[j+1].mass;
				if (no2>no1)
				{
					swap   = N[j];
					N[j]   = N[j+1];
					N[j+1] = swap;
				}
			}
		}	

		int knap_Element[total_element];
		int	knap_Maxweight[total_element];

		
		for(i = 0;i < total_element;++i){
			knap_Element [total_element] = 0;
			knap_Maxweight [total_element] = 0;
		}

		bag = knap_Maxweight;
		struct fork current; 
		current.earning = 0;
		current.mass = 0;
		knapsack (0,total_element, current, N, knap_Element, knap_Maxweight);

		FILE *fp;
		fp = fopen("backtrack_output.txt", "w");

		if (fp == NULL)
		{
			printf("Error opening file...\n");
			exit(1);
		}

		int max = 0;
		 
		for(i = 0;i < total_element;++i){
			if(knap_Maxweight[i]==1)
			max=max+N[i].mass;
		}
		
		fprintf(fp, "%d\n", max);
		max=0;
		int itemcount=0;
		
		for(i=0;i < total_element;++i){
			if(knap_Maxweight[i]==1)
			{
				max=max+N[i].earning;
				itemcount++;
			}
		}
		
		fprintf(fp,"%d",max);

		fprintf(fp,"\n");
	
		int order[total_element];
		for(i=0; i<total_element; ++i)
			order[N[i].list_num] = bag[i];
	
		int x=0;	 
		 
		for(i = 0;i < total_element;++i){
			if (order[i] == 1)
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
		
		 
		for(i = 0;i < total_element - 1;++i){
			for(j = 0;j < total_element - i - 1;++j){
				int swap1=0;
				if ( N[j].list_num > N[j+1].list_num )
				{
					swap1   = bag[j];
					bag[j]   = bag[j+1];
					bag[j+1] = swap1;
					swap   = N[j];
					N[j]   = N[j+1];
					N[j+1] = swap;
				}
			}
		}	
		fclose(fp);
	}
	fclose(file_ptr);
}