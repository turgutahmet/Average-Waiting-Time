//author: Ahmet TURGUT 150117046
//email: turgutahmt@gmail.com

#define Error( Str )        FatalError( Str )
#define FatalError( Str )   fprintf( stderr, "%s\n", Str ), exit( 1 )   
#define Infinity (6000000000L)		
#define MaxTrees (12)   
#define Capacity (4095)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Math.h>	 
#define ID_LEN 20

 int total_e; //total of burst time
 int e_max;		//maximum of burst time
 int quantum;	//quantum variable
 int first=1;	//for control in the second reading 
 int count;		//count of object p1,p2,p3.... 
 
  typedef struct Operation{
	char id[ID_LEN];
	float e;
	float last_e;
	int t_arr;
	int timeOfWait;
	float priority; 
	
}Operation;

		struct BinNode; //I transfered from binomial.h. This is your template.
        typedef struct BinNode *BinTree;
        struct Collection;
        typedef struct Collection *BinQueue;

        BinQueue Initialize( void );
        BinQueue Insert(Operation Operate, BinQueue H );
        BinQueue Merge( BinQueue H1, BinQueue H2 );
        Operation FindMin( BinQueue H );
        int IsEmpty( BinQueue H );
		void process_array(Operation *p);
		void find_value(Operation *p,int i);
        typedef struct BinNode *Position;

        struct BinNode{ //struct of binomial tree
		    struct Operation Operate;
            Position    LeftChild;
            Position    NextSibling;
        };

        struct Collection{	//struct of binomial heap
            int CurrentSize;
            BinTree TheTrees[ MaxTrees ];
        };
		
		void process_create( Operation *p,char *buf,float e,float arr,int i){ //this goal is create struct and fill with variable into the struct
			if(first==1){
				total_e=total_e+e;
			}
			
			p[i].e=e;if(p[i].e>e_max){e_max=p[i].e;}
			p[i].last_e=e;
			p[i].t_arr=arr;
			strcpy(p[i].id,buf);
			p[i].timeOfWait=0;
			p[i].priority=0;
			
		}
		
		BinQueue Insert( Operation Operate, BinQueue H ){ //You sent me this method with .7z file. This mean is insert in heap.
            BinTree NewNode;
            BinQueue OneOperate;
			
            NewNode = malloc( sizeof( struct BinNode ) );
            if( NewNode == NULL )
                FatalError( "Out of space!!!" );
            NewNode->LeftChild = NewNode->NextSibling = NULL;
			NewNode->Operate = Operate;
           

            OneOperate = Initialize( );
            OneOperate->CurrentSize = 1;
            OneOperate->TheTrees[ 0 ] = NewNode;

            return Merge( H, OneOperate );
        }
        
          BinTree CombineTrees( BinTree T1, BinTree T2 ){
            if( T1->Operate.priority > T2->Operate.priority )
                return CombineTrees( T2, T1 );
            T2->NextSibling = T1->LeftChild;
            T1->LeftChild = T2;
            return T1;
        }
        
		void execute(Operation *p){ //this method goal is find waiting time and print in the screen. The biggest part of the code works here. 
									//I find the priority values and add them to the structure. Then I calculate the waiting times based on the quantum number.
			BinQueue H1;
			Operation Operate;
			BinTree b; 
		 	float timeOfWait;
		 	int j;
		 	double c;
			float ex;
			double func;
			for(int q=1; q<=10; q++){
			 		timeOfWait=0;
			 		 process_array(p);//reading file this mean is renew in linkedlist(Operate) for each quantum number
					  j=0;
			 		 
			 		 while(j<=total_e){
			 		 	
			 		 	H1 = Initialize();	//initialize Heap
			 		 		
			 		 	for(int k=0;k<count;k++){
						  if(p[k].t_arr <= j && p[k].last_e>0){
						  	
							//find value of priority
							if(p[k].e==p[k].last_e){
								c=1;
							}else{
								ex=((2*p[k].last_e)/(3*e_max));
								ex=pow(ex,3);
								ex=-ex;
								c=1/(exp(ex));
							}
							func=c*p[k].last_e;
							p[k].priority=func;
							c=0;
							ex=0;
							Insert(p[k],H1);
							func=0;
						  }
						}
			 		 			
						  Operate=FindMin(H1);//find minimum number of priority in heap
						  
						  if(Operate.last_e>q){
						  	
						  	for(int l=0;l<count;l++){
						  		
						  		if(strcmp(Operate.id,p[l].id) == 0){
								  
								  
								  //find value of priority
								  p[l].last_e=p[l].last_e-q;
								  
								  if(p[l].e==p[l].last_e){
									c=1;
								  }else{
									ex=((2*p[l].last_e)/(3*e_max));
									ex=pow(ex,3);
									ex=-ex;
									c=1/(exp(ex));
								  }
									func=c*p[l].last_e;
									p[l].priority=func;
									c=0;
									ex=0;
									func=0;
								  }
						  		
							  }
							  j=j+q;
						  }else{
						  	 
						  	for(int m=0;m<count;m++){
						  		
						  		if(strcmp(Operate.id,p[m].id) == 0){j=j+p[m].last_e;
						  			
						  			p[m].last_e=0;
									  p[m].timeOfWait=j-(p[m].t_arr+Operate.e);
									 	timeOfWait=timeOfWait+p[m].timeOfWait;  
								  }
								  
							  }
						  }
						  free(H1);if(j==total_e)j++;
						  
					  	
					  }
					  for(int u=0;u<count;u++){printf("%d %s %d\n",u,p[u].id,p[u].timeOfWait);}printf("q=%d \nAWT= %.f/%d \nAWT= %.3f\n\n",q,timeOfWait,count, timeOfWait/count); //print
					  
				 }
		}	
	
		int counter_object(){//this method goal is find the count of object
			char buf[20];
		   float a,b; int i=0;
		   FILE *fp = fopen ( "input.txt", "r" );
		   if(fp!=NULL){
		   	while(fscanf(fp,"%s %f %f",buf,&a,&b) != EOF){
		   		 i++;
			   }
		   }
		   fclose ( fp );
		   
			return i;
		}
		
		void process_array(Operation *p){ //reading a file
			
		   char buf[20];
		   float a,b; int i=0;
		   FILE *fp = fopen ( "input.txt", "r" );
		   if(fp!=NULL){
		   	while(fscanf(fp,"%s %f %f",buf,&a,&b) != EOF){
		   		 process_create(p,buf,a,b,i);i++;
			   }
		   }
		   fclose ( fp );
		}
        BinQueue Initialize( void ){ //You sent me this method with .7z file. This mean is initialize heap.
            BinQueue H;
            int i;

            H = malloc( sizeof( struct Collection ) );
            if( H == NULL )
                FatalError( "Out of space!!!" );
            H->CurrentSize = 0;
            for( i = 0; i < MaxTrees; i++ )
                H->TheTrees[ i ] = NULL;
            return H;
        }
        
		int IsEmpty( BinQueue H ){
            return H->CurrentSize == 0;
        }
  
        

        Operation FindMin( BinQueue H ){//You sent me this method with .7z file. This mean is Find minimum priority value in heap.
            int i;
            Operation MinOperate;

            if(IsEmpty(H)){
                return MinOperate;
            }

            MinOperate.priority = Infinity;
			
            for( i = 0; i < MaxTrees; i++ ){
                if( H->TheTrees[ i ] && H->TheTrees[ i ]->Operate.priority <= MinOperate.priority ) {
                    MinOperate = H->TheTrees[ i ]->Operate;
				}	
            }

            return MinOperate;
        }


        BinQueue Merge( BinQueue H1, BinQueue H2 ){//You sent me this method with .7z file. Merge process.
            BinTree T1, T2, Carry = NULL;
            int i, j;

            if( H1->CurrentSize + H2->CurrentSize > Capacity )
                Error( "Merge would exceed capacity" );

            H1->CurrentSize += H2->CurrentSize;
            for( i = 0, j = 1; j <= H1->CurrentSize; i++, j *= 2 ){
                T1 = H1->TheTrees[ i ]; T2 = H2->TheTrees[ i ];

                switch( !!T1 + 2 * !!T2 + 4 * !!Carry )
                {
                    case 0: 
                    case 1: 
                        break;
                    case 2: 
                        H1->TheTrees[ i ] = T2;
                        H2->TheTrees[ i ] = NULL;
                        break;
                    case 4: 
                        H1->TheTrees[ i ] = Carry;
                        Carry = NULL;
                        break;
                    case 3: 
                        Carry = CombineTrees( T1, T2 );
                        H1->TheTrees[ i ] = H2->TheTrees[ i ] = NULL;
                        break;
                    case 5: 
                        Carry = CombineTrees( T1, Carry );
                        H1->TheTrees[ i ] = NULL;
                        break;
                    case 6: 
                        Carry = CombineTrees( T2, Carry );
                        H2->TheTrees[ i ] = NULL;
                        break;
                    case 7: 
                        H1->TheTrees[ i ] = Carry;
                        Carry = CombineTrees( T1, T2 );
                        H2->TheTrees[ i ] = NULL;
                        break;
                }
            }
            return H1;
        }
		
			
int main(){

	total_e=0;
    count=counter_object(); //calculate the count of object with method
    
    Operation *p=(Operation *)malloc(sizeof(Operation) * count);
	
    process_array(p); //reading a file
	first=2;
    printf("The input file (PID, e, tarr):\n-----------------------------\n");
   	  		  
    int i=0;
    while(i<count){
	   printf("	%s 	%.f 	%d\n",p[i].id,p[i].e,p[i].t_arr);
	   i++;
	  
    }printf("Time  |  Operation | Waiting Time\n------------------------------------------------\n");
 	
    execute(p); //calculate waiting time
 
	return 0;
}
