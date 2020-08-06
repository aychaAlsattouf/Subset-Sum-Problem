#include<stdio.h>
#include <stdlib.h>
#include <time.h> 
void quicksort(int [100],int,int);
void quicksort_float(float x[100],int first,int last);
void gen_population(int chrom[100][100],int num_chro,int size,int ,int main_matrix[100],int *limit);
void fitness_function(int m[100][100],int fit[100],int height,int width);
void print_fitness(int ff[100], int size);
void print_population(int m[100][100],int height,int width);
void selection(int m[100][100],int height,int width,int fit[100],int start);
void myfunction(float cum[100],float pr[100],int height ,int row[100],int start);
float min(float m[100],int size);
int max(int m[100],int size);
int maxx(int m[100],int size);//find index of maximum
void new_gen_pop(int arr[100][100],int height , int width,int row[100],int s);
void copy_matrix(int m[100][100],int he,int wi,int mm[100],int rr[100][100],int s);
void crossover(int m[100][100],int height,int width,int limit);
void mutation(int m[100][100],int h,int w,int arr[100],int );
void selection_elisist(int my[100][100],int f[100],int width,int height,int type,int tt);
int mmin(int m[100],int size);
int minn(int m[100],int size);//for find index of minimum fitness
void find_best(int my[100][100],int fit[100],int height,int width);
void normalize (float fit[100],int height,int);
float mmax(float m[100],int size);
void copy_to_float(int fit[100], float fi[100] , int height);
void copy_matrix(int m[100][100],int k[100][100],int height,int width);
 void selection_tt(int m[100][100],int width,int height,int s,int fit[100],int t);
 
 
 int main()
 {
  srand(time(NULL));
  int myarray[100],size,n,i,l,j,num_chro;
  int population[100][100],chro_size;
  int fitness[100],t ;
  int num_of_iteration=0,num_it,range,limitt=0,type_selection;
  float nor_fitness[100];
  
  //printf("not that if you enter more enough number of elements that will help you to avoid repeating\n");
  printf("Enter size of the array: ");
  scanf("%d",&size);

  printf("Enter %d elements for your set : \n",size);
  for(i=0;i<size;i++){
    scanf("%d",&myarray[i]);
  }

  quicksort(myarray,0,size-1);//sorting my array

  printf("Sorted elements: ");//print sorted array
  for(int i=0;i<size;i++){
    printf(" %d",myarray[i]);
  }
   range=size-2;
   //printf("\nnumber of element in subset : ");
   chro_size = 2+rand() % range;
  //printf("%d\n",chro_size);
  printf("\nnumber of genes for each chromosoms: %d\n",chro_size);
  printf("enter number of chromosoms:  ");
  scanf("%d",&num_chro);
  printf("enter type of selection that you will use it with Elitist (1 for Roulette 2 for Tournament) : ");
  scanf("%d",&type_selection);
  if(type_selection==2)
  {
	  printf("enter T for each tournament : \n");
	  scanf("%d",&t);
  }
  else{t=0;}
   for(j=0;j<num_chro;j++)
  {
	  for(int k=0;k<chro_size;k++)
	  {
		  population[j][k]=0;
		  
	  }
  }
  gen_population(population,num_chro,size-1,chro_size,myarray,&limitt);//generate initial population
  printf("\n\n%d\n\n",limitt);
  print_population(population,num_chro,chro_size);//void print_population(int m[100][100],int height,int width)
  fitness_function(population,fitness,num_chro,chro_size);//void fitness_function(int m[100][100],int fit[100],int height,int width)
  print_fitness(fitness,num_chro);//void print_fitness(int ff[100], int size)

  printf("enter maximum number of iteration : ");
  scanf("%d",&num_it);
  for(l=0;l<num_chro;l++)
  {
	  nor_fitness[l]=(float) fitness[l];
  }
  while(num_of_iteration<num_it)//loop for find better solution......
  {
	  printf("\n.............(iteration...%d...iteration)..............\n",num_of_iteration+1);
	  //normalize(nor_fitness,num_chro,0);//void normalize (float fit[100],int height)
	  printf("\n.............Elitist Selection..............\n");
	  selection_elisist(population,fitness,chro_size,num_chro,type_selection,t);//void selection_elisist(int my[100][100],int f[100],int width,int height)
	  printf("\n.............CrossOver..............\n");
	   crossover(population,num_chro,chro_size,limitt);//void crossover(int m[100][100],int height,int width)
	   printf("\n.............Mutation..............\n");
	   mutation(population,num_chro,chro_size,myarray,limitt);//void mutation(int m[100][100],int h,int w,int arr[100])
	   printf("\n.............Fitness Functions..............\n");
	   fitness_function(population,fitness,num_chro,chro_size);//fitness_function(int m[100][100],int fit[100],int height,int width)
	   print_fitness(fitness,num_chro);
   for(int O=0;O<num_chro;O++)
  {
	  nor_fitness[O]=(float) fitness[O];
  }
   num_of_iteration++;
  }
  find_best(population,fitness,num_chro,chro_size);//void find_best(int my[100][100],int fit[100],int height,int width)

  scanf("%d",&n); 
 getchar();
  return 0;
}



void quicksort(int x[100],int first,int last){
    int pivot,j,temp,i;

     if(first<last){
         pivot=first;
         i=first;
         j=last;

         while(i<j){
             while(x[i]<=x[pivot]&&i<last)
                 i++;
             while(x[j]>x[pivot])
                 j--;
             if(i<j){
                 temp=x[i];
                  x[i]=x[j];
                  x[j]=temp;
             }
         }

         temp=x[pivot];
         x[pivot]=x[j];
         x[j]=temp;
         quicksort(x,first,j-1);
         quicksort(x,j+1,last);

    }
}
void quicksort_float(float x[100],int first,int last){
    int pivot,j,i;
	float temp;
     if(first<last){
         pivot=first;
         i=first;
         j=last;

         while(i<j){
             while(x[i]<=x[pivot]&&i<last)
                 i++;
             while(x[j]>x[pivot])
                 j--;
             if(i<j){
                 temp=x[i];
                  x[i]=x[j];
                  x[j]=temp;
             }
         }

         temp=x[pivot];
         x[pivot]=x[j];
         x[j]=temp;
         quicksort_float(x,first,j-1);
         quicksort_float(x,j+1,last);

    }
}
void gen_population(int chrom[100][100],int num_chro,int size,int size_chr,int main_matrix[100],int *limit)//gen_population(population,num_chro,size,chro_size,myarray);
{
	int j,a=0,index,k,m=0;
	 srand (time(NULL));
	 *limit=size_chr*size_chr*6;//number of iteration used to find non repeating genes
	printf("we will accept repeat after  specific  number of iterations is :  %d\n",*limit);
  for(j=0;j<num_chro;j++)
  {
	  //printf("00000000\n");
	  for(k=0;k<size_chr;k++)
	  {
		  //printf("1111111111\n");
		  index = rand() % size ;
		//printf("%d\n",index);
		  if(k==0)
		  {
		  chrom[j][k]=main_matrix[index];
		  //printf("1111111000000011 %d\n",chrom[j][k]);
		  }
		  else
		  {
			  a=0;
			  m=0;//to avoid repetance 
			 // printf("1111111111111111111111111 %d\n",k);
			  while(a<=k &&m<=*limit)
			  {
				    // printf("indexxxxx 111111 : %d\n",index);
					 //printf("chrom[%d][%d] : %d\tmain matrix[%d] : %d\n ",j,a,chrom[j][a],index,main_matrix[index]);
				 if(chrom[j][a]==main_matrix[index])
				  {
					  index = rand() % size ;
					  a=0;
				  }
				 else{a++;}
				 m++;
			  }
			    chrom[j][k]=main_matrix[index];
			    //printf("222222 %d\t value:  %d\n",index,chrom[j][k]);
		  }
		  
	  }
  }
}
void print_population(int m[100][100],int height,int width)
{
	int f;
	 for(f =0;f<height;f++)
  {
	  for(int n=0 ;n<width;n++)
	  {
		  printf("%d\t",m[f][n]);
	  }
	  printf("\n");
  }
}
void fitness_function(int m[100][100],int fit[100],int height,int width)
{
	int i,j;
	int sum=0;
	for(i=0;i<height;i++)
	{
		sum=0;
		for(j=0;j<width;j++)
		{
			sum+=m[i][j];
		}
		fit[i]=sum;
	}

}
void print_fitness(int ff[100], int size)
{
 printf("values of fitness function for each chromosom: \n");
  for(int j=0;j<size;j++)
  {
	  printf("%d\n",ff[j]);
  }
}
void selection(int m[100][100],int height,int width,int fit[100],int start)//use roulette selection
{
	 printf("\n.............Roulette Selection..............\n");
	//srand((unsigned int)time(NULL));//for geneate floating numbers
	int i, count[100],j,b=0,n;//sum of fitness funcytions
	float prop[100],q[100],f=0.0,fitness[100];

	fitness_function(m,fit,height,width);
	 copy_to_float(fit,fitness,height);//copy our int fitness value to another float value to calculate normalize

	 normalize(fitness,height,1);//void normalize (float fit[100],int height)
	 if(fitness[height-1] !=  NULL){
					printf("start ponint is : %d\n",start);
					for(i=start;i<height;i++)
					{
						f= f + fitness[i];
					}
					printf("f(sum of normalized fintness) : %.2f\n",f);
					if (f!=0.0){
								for(j=start;j<height;j++)//pk=eval(k)/f
								{
									q[j]=0.0;
									prop[j]=fitness[j]/f;//calculate the probability for each chromosom
									printf("p[%d] : %.2lf\n",j,prop[j]);
								}
								printf("\n");
								myfunction(q,prop,height,count,start);//oid myfunction(float cum[100],float pr[100],int height ,int row[100])
								new_gen_pop(m,height,width,count,start);//void new_gen_pop(int arr[100][100],int height , int width,int row[100])//to reorder the population
								printf("new population after selection: \n");
							    print_population(m,height,width);
							    fitness_function(m,fit,height,width);//void fitness_function(int m[100][100],int fit[100],int height,int width)
							    copy_to_float(fit,fitness,height); 
							    normalize(fitness,height,1);//void normalize (float fit[100],int height)

					         }
					else 
					     {
					    	printf("fitness function is equal to zero :(\n");
					   }
		 }

}
void myfunction(float cum[100],float pr[100],int height ,int row[100],int start)//رح اخد الترتيب السطري يلي رح عوض مكانو بالفنكشن الجديدة
{
	int i ,j,n,m;
	float r;
	//int minnn=0;
	//int maxx=1;
	for(m=start;m<height;m++)
	{
		row[m]=0;
	}
	srand((unsigned int)time(NULL));//for geneate floating numbers
	for(i=start;i<height;i++)
	{
			for(n=start;n<height;n++)
			{
				cum[n]=0.0;
			}
		r=((float)rand()/(float)(RAND_MAX));//min cum to ...1
		for(j=start;j<height;j++)
		{
			for(int m=start;m<=j;m++){
			   cum[j]+=pr[m];
			}
			printf("prop: %.2f\tcum[%d] : %.2f\n",pr[j],j,cum[j]);
			if(r<cum[start])
			{
				row[i]=start;
				break;
			}
			else if(r>cum[j-1]&&r<=cum[j])
			{
				row[i]=j;
			}
		}
		printf("r :  %.2lf\trow : %d\n",r,row[i]);
			//minnn=min(cum,height);
	}
}
int max(int m[100],int size)
{
	int max=m[0];
	int i;
	for(i=0;i<size;i++)
	{
		if(max<m[i])
		{
			max=m[i];
		}
	}
	return max;
}
float mmax(float m[100],int size)
{
	float max=m[0];
	int i;
	for(i=0;i<size;i++)
	{
		if(max<m[i])
		{
			max=m[i];
		}
	}
	return max;
}
int maxx(int m[100],int size)//find index of maximum
{
	int max=m[0];
	int i,c;
	for(i=0;i<size;i++)
	{
		if(max<m[i])
		{
			max=m[i];
			c=i;
		}
	}
	return c;
}
float min(float m[100],int size)
{
	float min=m[0];
	int i;
	for(i=0;i<size;i++)
	{
		if(min>m[i])
		{
			min=m[i];
		}
	}
	return min;
}
int mmin(int m[100],int size)
{
	int min=m[0];
	int i;
	for(i=0;i<size;i++)
	{
		if(min>m[i])
		{
			min=m[i];
		}
	}
	return min;
}
int minn(int m[100],int size)//for find index of minimum fitness
{
	int min=m[0];
	int i,c=0;
	for(i=0;i<size;i++)
	{
		if(min>m[i])
		{
			min=m[i];
			c=i;
		}
	}
	return c;
}
void new_gen_pop(int arr[100][100],int h , int w,int row[100],int s)//row matrix contain order of new rows 
{
	int k,arrr[100][100];//copy from main matrix
	row[0]=0;
	for(k=s;k<h;k++)
	{
		printf("new row[%d] will be that represent %d in previous population\n",k,row[k]);
		for(int c=0;c<w;c++)
		{
			printf("%d\t",arr[row[k]][c]);
		}
		
	printf("\n");

	}
	printf("\n");
	printf("exist population without the rows that we made selection on it is  : \n");//print rxist population  without the row that we made selection on it
	for(int f=0;f<h;f++)
	{ 
		for(int g=0;g<w;g++)
		{
			arrr[f][g]=arr[f][g];//copy the element of orginal matrix arr to new matrix arrr 
			printf("%d\t",arr[f][g]);
		}
		printf("\n");
	}
	printf("\n\n");
	copy_matrix(arr,h,w,row,arrr,s);//void copy_matrix(int m[100][100],int he,int wi,int mm[100],int rr[100][100])
}
void copy_matrix(int m[100][100],int he,int wi,int mm[100],int rr[100][100],int s)//generate new generation from selection//mm represent new rows order
{
	int i,j,l,f,num=0;
	
	for(f=s;f<he;f++)
	{ 
		for(l=0;l<wi;l++)
		{
			m[f][l]=0;//make the original function equal to zero
		}
	}
	 print_population(m,he,wi);
	for(i=s;i<he;i++)
	{
		num=mm[i];
		for(j=0;j<wi;j++)
		{
			m[i][j]=rr[num][j];
		}

	}

}
void crossover(int m[100][100],int height,int width,int limit)
{
	//srand (time(NULL));
	int i ,j,d,temp;
	int row1,row2,repeat=0;
	row1=1+rand() %(height-1);
	row2=1+rand() %(height-1);
	printf("row1 : %d\trow2 : %d\n",row1,row2);
	int crossover_point;
	//if (row1!=row2){
	crossover_point=rand() % (width-1);
	for(i=0;i<height;i++)
	{
		if(i==crossover_point)
		{
			for(int z=0;z<width;z++){
			d=crossover_point;
			repeat=0;
			while(d<width && repeat<limit)//check the new element not equal to element in other row
			{
				if(m[row1][d]==m[row2][z] || m[row2][d]==m[row1][z] || row1==row2 )
				{
					//printf("\nd : %d\n",d);
					row1=1+rand() %(height-1);
					row2=1+rand() %(height-1);
					//printf("row1 : %d\trow2 : %d\n",row1,row2);
				}
				else{//printf("\nz= %d\td= %d\n",z,d);
					d++;}
				repeat++;

			}

			}
			printf("we find this rows in iteration %d\n",repeat);
						printf("random row1 : %d\trandom row2 : %d for do crossover\n",row1,row2);
						for(int l=0;l<width;l++)
						{
							printf("%d\t",m[row1][l]);
						}
						printf("\n");
						for(int n=0;n<width;n++)
						{
							printf("%d\t",m[row2][n]);
						}	
						printf("\n");
						printf("\n");
						printf("\ncrossover point : %d\n",crossover_point);
								for(j=i;j<width;j++)
								{
									temp=m[row1][j];
									m[row1][j]=m[row2][j];
									m[row2][j]=temp;
								}
							}
						}
	for(int p=0;p<width;p++)
	{
		printf("%d\t",m[row1][p]);
	}
	printf("\n");
	for(int n=0;n<width;n++)
	{
		printf("%d\t",m[row2][n]);
	}
	/*}
	else
	{
		printf("we have same row for crossover\n");
		//crossover(m,height,width,limit);//void crossover(int m[100][100],int height,int width,int limit)

	}*/
}
void mutation(int m[100][100],int h,int w,int arr[100],int limit)
{
	int row;
	int col;
	int index_new_chro = rand() % (w-1);
	int new_chro;
	int p=0,i ,j;
	row=1+rand() %( h-1);
    col=rand() % (w-1);
	print_population(m,h,w);
	if(index_new_chro>=0){
   new_chro=arr[index_new_chro];
	printf("\nrow : %d\tcol: %d\tnew_chro : %d\n",row,col,new_chro);
	printf("row : %d\tcol : %d\n",row,col);
	int n=0;
    while(p<w && n<limit)
	{
		if(m[row][p]!=new_chro)
		{
			p++;
		}	
		else{
			row=1+rand() % (h-1);
			 col=rand() % (w-1);
			//printf("row : %d\tcol : %d\n",row,col);
			p=0;
		}
		
		n++;
	}

	printf("\nrow : %d\tcol: %d\tindex_new_chro : %d\n",row,col,new_chro);
	for(i=0;i<h;i++){
	
		for(j=0;j<w;j++)
		{
			if(i==row && j==col)
			{
				m[i][j]=0;
				m[i][j]+=new_chro;
			}
		}
	}
	   printf("\n.............New Population..............\n");
   print_population(m,h,w);

	}
else{printf(".................\n");}
}
void find_best(int my[100][100],int fit[100],int height,int width)
{
	int i,k,n=0,solution=0,m,copy_fitness[100];
	int n1=0,n2=0,p,w=0,index;
	printf("this is fitness functions for last population: \n");
	print_fitness(fit,height);
	for(p=0;p<height;p++)//copy for compare
	{
		copy_fitness[p]=fit[p];
	}
	quicksort(copy_fitness,0,height-1);//void quicksort(int x[100],int first,int last)
	printf("ordered fitness values: \n");
	for( m=0;m<height ; m++)
	{
		printf("fitness[%d] : %d\n",m,copy_fitness[m]);
	}
	
	if(copy_fitness[height-1]<0)
	{
		n+=height-1;
		solution=copy_fitness[height-1];
		printf("index better chromosom is 00000: %d when normalize fitness value is %d\n",n,solution);
				
	}
	else{
		for(i=0 ; i<height;i++)
		{
			if(copy_fitness[i]==0)
			{
				//printf("%.2f\n",fit_zero);
				n=i;
				solution+=copy_fitness[i];
				printf("index better chromosom is 11111 : %d  when normalize fitness value is %d\n",n,solution);
				break;
			}
			else if(copy_fitness[i]>0 )
			{
				if(i==0)
				{//printf("%.2f\n",fit_zero);
				n1+=i;
				n2+=i;
				n+=n1;
				solution=copy_fitness[i];
				printf("index better chromosom is 33333: %d when normalize fitness value is %d\n",n,solution);
				break;
				}
				else
				{ 
					n1+=i-1;
					n2+=i;
					if (copy_fitness[n1]<0)
					{
						if(copy_fitness[n1]*(-1) < copy_fitness[n2])
						{
							n+=n1;
							solution+=copy_fitness[n1];
						}
						else
						{
							n+=n2;
							solution+=copy_fitness[n2];
						}
							printf("index better chromosom is 222222: %d when normalize fitness value is %d\n",n,solution);
					}
					else
					 {
							if(copy_fitness[n1]< copy_fitness[n2])
							{
								n+=n1;
								solution=copy_fitness[n1];
							}
							else
							{
								n+=n2;
								solution=copy_fitness[n2];
							}
					printf("index better chromosom is 33333: %d when normalize fitness value is %d\n",n,solution);
				  }
					break;
			}

		}
		}
	}
	for(k=0;k<height;k++)
	{
		if(fit[k]==solution)
		{
			index=k;
			printf("index of better chromosom is ***** : %d\n",index);
			break;
		}
	}
	printf("the better in index %d  solution is :\n",index);
	for(int o=0;o<width;o++)
	{
		printf("%d  ",my[index][o]);
	}
}
void selection_elisist(int my[100][100],int f[100],int width,int height , int type,int tt)
{
	
	int minn = mmin(f,height);
	int maxx= max(f,height);
	int copy[100][100],copy_fitness[100],solution=0;//copy from orginal matrix
	int i,n=0,n1=0,n2=0,m,k,t,p,w,index;//index row for better chromosom
	print_population(my,height,width);
	printf("\n..............\n");
    copy_matrix(my,copy,height,width);//void copy_matrix(int m[100][100],int k[100][100],int height,int width)
	print_population(copy,height,width);
	//fitness_function(copy,)//void fitness_function(int m[100][100],int fit[100],int height,int width)
	for(p=0;p<height;p++)//copy for compare
	{
		copy_fitness[p]=f[p];
	}
	quicksort(copy_fitness,0,height-1);
	printf("ordered fitness values: \n");
	for( m=0;m<height ; m++)
	{
		printf("fitness[%d] : %d\n",m,copy_fitness[m]);
	}
	if(copy_fitness[height-1]<0)
	{
		n+=height-1;
		solution=copy_fitness[n];
	  printf("index better chromosom is 00000: %d when normalize fitness value is %d\n",n,solution);
	}
	else{
		for(i=0;i<height;i++)
		{
			if(copy_fitness[i]==0)
			{
				//printf("%.2f\n",fit_zero);
				n+=i;
				solution=copy_fitness[i];
				printf("index better chromosom is 11111 : %d  when normalize fitness value is %d\n",n,solution);
				break;
			}
			else if(copy_fitness[i]>0 && copy_fitness[i]!=0)
			{
				if(i==0)
				{//printf("%.2f\n",fit_zero);
				n1+=i;
				n2+=i;
				n+=n1;
				solution=copy_fitness[i];
				break;}
				else
				{ 
					n1+=i-1;
					n2+=i;
					if (copy_fitness[n1]<0)
					{
						if(copy_fitness[n1]*(-1) <copy_fitness[n2])
						{
							n+=n1;
							solution+=copy_fitness[n1];
						}
						else
						{
							n+=n2;
							solution+=copy_fitness[n2];
						}
							printf("index better chromosom is 222222: %d when normalize fitness value is %d\n",n,solution);
					}
					else
					 {
							if(copy_fitness[n1]< copy_fitness[n2])
							{
								n+=n1;
								solution=copy_fitness[n1];
							}
							else
							{
								n+=n2;
								solution=copy_fitness[n2];
							}
					printf("index better chromosom is 222222: %d when normalize fitness value is %d\n",n,solution);
				}
					
			break;}

		}
	}
	}//printf("\n........index : %d.......value :  %d...........\n",n,f[n]);
	//for(a=0;a<number;a++){
	for(k=0;k<height;k++)
	{
		if(f[k]==solution)
		{
			index=k;
			printf("index of better chromosom is ***** : %d\n",index);
			break;
		}
	}
	if(index >= 0){
	for(t=0;t<width;t++)
	{
		my[0][t]=0;
	}
	
	for(w=0;w<width;w++)
	{
		my[0][w]+=copy[index][w];
	}
	print_population(my,height,width);
	if(type==1){
		selection(my,height,width,f,1);}
	//void selection(int m[100][100],int height,int width,int fit[100])
	else if(type==2){
		selection_tt(my,width,height,1,f,tt);}
	//void selection_tt(int m[100][100],int width,int height,int s,int fit[100])
	}
				else{ if(type==1){
					selection(my,height,width,f,1);}
				//void selection(int m[100][100],int height,int width,int fit[100])
				else if(type==2){
					selection_tt(my,width,height,1,f,tt);}
				//void selection_tt(int m[100][100],int width,int height,int s,int fit[100])

	}
}

 void normalize (float fit[100],int height ,int start)//normalize fitness function to solve problem of negative prob
 {
	 int i ,j;
	 float minimum = min(fit,height);
	 float maximum= mmax(fit,height);
	 float fit_copy[100];
	 printf("min fitness : %d\tmax fitness : %d\n",minimum,maximum);
	 if(minimum!=maximum){
	 for(i=start;i<height;i++)
	 {
		 fit_copy[i]=fit[i];
	 }
	 for(int k=start;k<height;k++)
	 {
		 fit[k] = 0;
	 }
	 for(j=start;j<height;j++)
	 {
		 fit[j]= (fit_copy[j]-minimum)/(maximum-minimum);
	 }
	 printf("normalize fitness function :\n");
	 for(int l=start;l<height;l++)
	 {
		 printf("normalize fitness value int  [%d] for fitness  %.2f : %.2f\n",l,fit_copy[l],fit[l]);
	 }
	 }
	 else
	 {
		 printf("you cann't normalize the fitness values  \n");
	 }
 }
 void copy_to_float(int fit[100] , float fi[100] , int height)
 {
	 int i ;
	 for(i=0;i<height;i++)
	 {
		 fi[i]=(float)fit[i];
	 }
 }
 void copy_matrix(int m[100][100],int k[100][100],int height,int width)
 {
	 int i,j;
	 for(i=0;i<height;i++)
	 {
		 for(j=0;j<width;j++)
		 {
			 k[i][j]=m[i][j];
		 }
	 }
 }
 void selection_tt(int m[100][100],int width,int height,int s,int fit[100],int t)
 {
	 int i , j,count=0,p,solution=0,n=0,n1=0,n2=0,index;
	 int copy_matrix[100][100],copy_fitness[100],tt[100],my_sub_array[100];
	 printf("\n.............Tournament Selection..............\n");
	 for(int k=s;k<height;k++)
	 {
		 for(int h=0;h<width;h++)
		 {
			 copy_matrix[k][h]=m[k][h];
			 m[k][h]=0;
		 }
	 }
	 for(p=s;p<height;p++)
	 {
		 //t=2+rand()%(height-1);//generate t for to geberate each new row
		 printf("\nt[%d] : %d\n",p,t);
		 count=0;
		 while(count<t)
		 {
			 tt[count]=1+rand()%(height-1);
			 my_sub_array[count]=fit[tt[count]];//take fitness value in random that index is random number
			 
			 printf("tt[%d] : %d\tfitness value[%d] for row that it is index is %d: %d\n",count,tt[count],count,tt[count],my_sub_array[count]);
		 count++;}
		  quicksort(my_sub_array,0,t-1);
		  for(int g=0;g<t;g++)
		  {
			  printf("my_sub_array[%d] : %d\n",g,my_sub_array[g]);
		  }
		  n=0;
		  n1=0;
		  n2=0;
		  solution=0;
			 if(my_sub_array[t-1]<0)
				{
					n+=t-1;
					solution=my_sub_array[t-1];
					//printf("index better chromosom is 000000000000: %d fitness value is %d\n",n,solution);
				}
				else{
					for(i=s ; i<t;i++)
					{
						if(my_sub_array[i]==0)
						{
							//printf("%.2f\n",fit_zero);
							n=i;
							solution+=my_sub_array[i];
							//printf("index better chromosom is 11111 : %d  when normalize fitness value is %d\n",n,solution);
							break;
						}
						else if(my_sub_array[i]>0 )
						{
							if(i==0)
							{//printf("%.2f\n",fit_zero);
							n1+=i;
							n2+=i;
							n+=n1;
							solution=my_sub_array[i];
							//printf("index better chromosom is 33333: %d when normalize fitness value is %d\n",n,solution);
							break;
							}
							else
							{ 
								n1+=i-1;
								n2+=i;
								//printf("n1 : %d\tn2 : %d\n",n1,n2);
								if (my_sub_array[n1]<0)
								{
									if(my_sub_array[n1]*(-1) < my_sub_array[n2])
									{
										n+=n1;
										solution+=my_sub_array[n1];
										//printf("index better chromosom is 222222: %d when normalize fitness value is %d iffff\n",n,solution);
									}
									else
									{
										n+=n2;
										solution+=my_sub_array[n2];
										//printf("index better chromosom is 222222: %d when normalize fitness value is %d elseeeeee\n",n,solution);
									}
										//printf("index better chromosom is 222222: %d when normalize fitness value is %d\n",n,solution);
								}
								else
								 {
										if(my_sub_array[n1]< my_sub_array[n2])
										{
											n+=n1;
											solution=my_sub_array[n1];
										}
										else
										{
											n+=n2;
											solution=my_sub_array[n2];
										}
								//printf("index better chromosom is 33333: %d fitness value is %d\n",n,solution);
							}
							 break; 	
						}

					}
					}
				}
				index=0;
				for(int l=1;l<height;l++){
					if(fit[l]==solution){
						index+=l;
						printf("index %d\n",index);
						break;
					}
				}
				for(int f=0;f<width;f++)
				{
						m[p][f]=copy_matrix[index][f];
						printf("m[%d][%d] : %d\t",p,f,m[p][f]);
				}
				printf("\n");
     }
	 print_population(m,height,width);
	 }