
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<stdbool.h>
#define pi acos(-1)




int main(){
	
	srand(time(0));
	// Start Record the time
    time_t  start = clock();
	
	//***************************************************************************
	//LDPC
	//BPSK 1 or -1
	
	
	
	
	FILE *fp1 = fopen("H_96_48.txt", "r");
	if (fp1 == NULL) {
        fprintf(stderr, "fopen() failed.\n");
        exit(EXIT_FAILURE);
    }
    
    int n,m,dv,dc;
    
    
    fscanf(fp1,"%d ",&n);
    fscanf(fp1,"%d ",&m);	// H 的 row 數量 
    fscanf(fp1,"%d ",&dv);
    fscanf(fp1,"%d ",&dc);
    
    printf("%d %d %d %d\n",n,m,dv,dc);
    
    const double R=(double)(n-m)/n; //coderate
    
    //建立 number of col row nonzero location
	 
   	int* col = (int*)malloc(sizeof(int)*n);		//number of col nonzero 
    
    for(int i=0;i<n;i++){
    	fscanf(fp1,"%d ",&col[i]);
    	
	}
	
	int* row = (int*)malloc(sizeof(int)*m);		//number of row nonzero 
    
    for(int i=0;i<m;i++){
    	fscanf(fp1,"%d ",&row[i]);	
	}	
	
	
	//Construct adjacency list
	//VN 
	int** VN_set = (int **)malloc(sizeof(int*) * n);
	for(int i=0;i<n;i++){
		VN_set[i] = (int *)malloc(sizeof(int) * col[i]);
	}
	//CN
	int** CN_set = (int **)malloc(sizeof(int*) * m);
	for(int i=0;i<m;i++){
		CN_set[i] = (int *)malloc(sizeof(int) * row[i]);
	}	

	

	

	
	for(int i=0;i<n;i++){
		for(int j=0;j<col[i];j++){
			fscanf(fp1,"%d ",&VN_set[i][j]);
			VN_set[i][j]--;
		}
		for(int k=col[i];k<dv;k++){
			int buffer;
			fscanf(fp1,"%d ",&buffer);	//把多餘的 col idex 用 buffer 消耗掉 
		}
	}
	
	
	for(int i=0;i<m;i++){
		for(int j=0;j<row[i];j++){
			fscanf(fp1,"%d ",&CN_set[i][j]);
			CN_set[i][j]--;
		}
		for(int k=row[i];k<dc;k++){
			int buffer;
			fscanf(fp1,"%d ",&buffer);	//把多餘的 col idex 用 buffer 消耗掉 
		}
	}
	
	/*
	for(int i=0;i<n;i++){
		for(int j=0;j<col[i];j++){
			printf("%d ",VN_set[i][j]);
			
		}
		printf("\n");
	}
	for(int i=0;i<m;i++){
		for(int j=0;j<row[i];j++){
			printf("%d ",CN_set[i][j]);
			
		}
		printf("\n");
	}
	*/


	
	fclose(fp1);
	
	
	//***************************************************************************
	// 讀取 cycle 6 的idex 
	
	FILE *fp2 = fopen("6 cycle idex sorting.txt", "r");
	if (fp2 == NULL) {
        fprintf(stderr, "fopen() failed.\n");
        exit(EXIT_FAILURE);
    }
    
    
	int cycle4,cycle6,cycle8;
	fscanf(fp2,"%d ",&cycle4);
	fscanf(fp2,"%d ",&cycle6);
	fscanf(fp2,"%d ",&cycle8);
	
	
    int** cycle_idex = (int **)malloc(sizeof(int*) * cycle6);
	
	for(int i=0;i<cycle6;i++){
		cycle_idex[i] = (int*)malloc(sizeof(int)* 3 );
	}
	for(int i=0;i<cycle6;i++){
		
		for(int j=0;j<3;j++){		
			fscanf(fp2,"%d ",&cycle_idex[i][j]);
		}
		
	}

	
	
	
	
	/*
	for(int i=0;i<cycle6;i++){
		printf("cycle: %d\n",i);
		for(int j=0;j<3;j++){		
			printf("%d ",cycle_idex[i][j]);
		}

		printf("\n");
	}
	*/
	
	fclose(fp2);
	
	//***************************************************************************
	//channel information
	double* Fn = (double *)malloc(sizeof(double) * n);
	//tau
	double** tau= (double **)malloc(sizeof(double*) * m);
	for(int i=0;i<m;i++){
		tau[i] = (double *)malloc(sizeof(double) * dc);
	}
	
	//CN update //CN[j][i]  CN j to CN i
	double** CN = (double **)malloc(sizeof(double*) * m );
	for(int i=0;i<m;i++){
		CN[i] = (double *)malloc(sizeof(double) * dc);
	}
	
	//VN update //VN[i][j]  VN i to CN j
	double** VN = (double **)malloc(sizeof(double*) * n);
	for(int i=0;i<n;i++){
		VN[i] = (double *)malloc(sizeof(double) * dv);
	}
	
	//total LLR VN[i]
	double* VN_total = (double *)malloc(sizeof(double) * n);
	
	//decoded sequence
	int* u_hat = (int *)malloc(sizeof(int) * n);
	
	double *y = (double*)malloc(sizeof(double) * n);
	
	//**********************************************
	
	
	
	//SNR
	const int SNR_L = 1;
	double *SNR_dB = (double *)malloc(sizeof(double) * SNR_L);
	/*
	SNR_dB[0] = 0;
	SNR_dB[1] = 0.4;
	
	SNR_dB[2] = 0.8;
	
	SNR_dB[3] = 1.2;
	
	SNR_dB[4] = 1.6;
	SNR_dB[5] = 2;
	*/
	SNR_dB[0] = 4;
	
	
	//**********************************************

	
	//sigal;
	
	//假設全為 0
	int *u = (int*)malloc(sizeof(int) * n);	//binary sequence
	int *x = (int*)malloc(sizeof(int) * n);
	
	for(int i=0;i<n;i++){
		u[i] = 0;
		x[i] = 1;		//Eb=1	Eav = R*1
	} 
	
	
	
	//*******************************************************************
	
	int numtime =10;
	int iteration = 50;	
	
	double bias = -1;	// use bias let bit shift to error region 
	
	double *FER = (double*)malloc(sizeof(double) * SNR_L);
	for(int i=0;i<SNR_L;i++)
		FER[i]=0;
	
	
	double *FER_cy = (double*)malloc(sizeof(double) * cycle6);
	for(int i=0;i<cycle6;i++)
		FER_cy[i]=0;

	
	
	for(int q=0;q<SNR_L;q++){
			
		double sigma = sqrt((1/(2*R))*pow(10,-(SNR_dB[q]/10)));	//sigma 
		
		
		printf("sigma: %f\n",sigma);
		
		
			
			double frameerror=0;
			
			
			for(int num=0;num<numtime;num++){
				
				
				
				printf("num: %d\n",num);
				
				for(int cy=0;cy<cycle6;cy++){
					
				
					//noise
					double* noise = (double *)malloc(sizeof(double) * n);
					double U ,V ;
					
					
					int cycle_i=0;		//go through cycle idex 
					
					for(int i=0;i<n;i++){
						U = (double) rand() / (double)(RAND_MAX);	//uniform (0~1) 0<U<1
						while(U==0||U==1)
							U = (double) rand() / (double)(RAND_MAX);	
						
						
						V = (double) rand() / (double)(RAND_MAX);
						while(V==0||V==1)
							V = (double) rand() / (double)(RAND_MAX);	
						
						noise[i] = sqrt(-2*log(U))*cos(2*pi*V);
						
						//************************************************** 
						//add bias to cycle bit
						
						if(cycle_i<3 &&cycle_idex[cy][cycle_i]==i){
							
							y[i] = x[i] + sigma*noise[i] + bias;
							cycle_i++;
						}
						else
							y[i] = x[i] + sigma*noise[i];
						
						
						
					} 
					
					//initialization
					for(int i=0;i<n;i++){
						Fn[i] = 2*y[i]/(pow(sigma,2));	
						for(int j=0;j<col[i];j++){	
							
							VN[i][j] = 2*y[i]/(pow(sigma,2));	
							
						}	
						
					}
					
					//iterative decoding
					int iter=0;
					
					for(iter=0;iter<iteration;iter++){
						
						//CN update	
						for(int j=0;j<m;j++){	
							for(int i=0;i<row[j];i++){
								tau[j][i]=1;	
							}
						}
					
						
						for(int j=0;j<m;j++){				//go through all CN	
							for(int i=0;i<row[j];i++){				//相連之 VN 
								//if(CN_set[j][i]==-1){
								//	continue;
								//}
								
									//printf("CN:%d to VN:%d\n",j,CN_set[j][i]);
									for(int np=0 ; np<row[j] ; np++){			//n'
										if(CN_set[j][np]>=0&&CN_set[j][i]!=CN_set[j][np]){	//n != n'
											
											//printf("VN:%d to CN:%d\n",CN_set[j][np],j); //N(m) set
											for(int f=0;f<col[CN_set[j][np]];f++){
												//找到VN 中之index 
												if(VN_set[CN_set[j][np]][f]==j){
													
													//printf("%d %d\n",CN_set[j][np],f);
													tau[j][i] *=tanh(VN[CN_set[j][np]][f]/2);	
													
												}
												
											}
													
										}		
									}
								
								//計算完tau 
								//CN[j][i] = log((1.0+tau[j][i])/(1.0-tau[j][i]));
								if(tau[j][i]==1)
									CN[j][i] = 19.07;
								else if(tau[j][i]==-1)
									CN[j][i] = -19.07;
								else
									CN[j][i] = 2*atanh(tau[j][i]);
								//printf("\n");
								
							}
						}
						
						
						//VN update
			
						for(int i=0;i<n;i++){ 				//go through all VN	
							for(int j=0;j<col[i];j++){			//相連之 CN 
								
									VN[i][j] = Fn[i];
										
									//printf("VN:%d to CN:%d\n",i,VN_set[i][j]);
									for(int mp=0 ; mp<col[i] ; mp++){			//m'
										if(VN_set[i][mp]>=0&&VN_set[i][j]!=VN_set[i][mp]){	//m != m'
											
											//printf("from CN:%d to VN:%d\n",VN_set[i][mp],i);
											for(int p=0;p<row[VN_set[i][mp]];p++){
												//找到 CN 中之index 
												
												if(CN_set[VN_set[i][mp]][p]==i){
													//printf("%d %d\n",VN_set[i][mp],p);
													VN[i][j] += CN[VN_set[i][mp]][p];		
												}
												
											}
													
										}		
									}
									//printf("\n");
								
									
							}
							
						}
						
						
						
						
						//total LLR
						//decode
							
						for(int i=0;i<n;i++){ 				//go through all VN	
							VN_total[i] =  Fn[i]; 			
							for(int j=0;j<col[i];j++){	
								//if(VN_set[i][j]==-1)
								//	continue;				
								for(int m=0;m<row[VN_set[i][j]];m++){
									if(CN_set[VN_set[i][j]][m]==i){		//找到與VN相連之 CN  idex 
										//printf("VN %d CN %d to %d\n",i,VN_set[i][j],CN_set[VN_set[i][j]][m]);
										VN_total[i] += CN[VN_set[i][j]][m];
										
									}
								}
			
							}
							//printf("VN_toatl %f\n",VN_total[i]);
							
							if(VN_total[i]>=0)
								u_hat[i] = 0;
							else
								u_hat[i] = 1;
						}
						
						
						
						
						// symdrome  s
						int* s = (int *)malloc(sizeof(int) * m );
						bool iszerovector = true;
						
						for(int j=0;j<m;j++){
							s[j] =0;
							for(int i=0;i<row[j];i++){
								if(CN_set[j][i]>=0&&u_hat[CN_set[j][i]]==1)
									s[j] += 1;
							}
							
							s[j] %=2;
							
							if(s[j]!=0){
								iszerovector = false;
								break;
							}	
						}
						
						if(iszerovector){
							break;
						}
						
					}
					
					
					
					
					
					
					
					
					for(int i=0;i<n;i++){
						if(u[i]!=u_hat[i]){
							
							// weight function W
							double W = 0;
							double power = 0;
							int cyc_i=0;
							for(int i=0;i<n;i++){
								
								if(cycle_i<3 &&cycle_idex[cy][cycle_i]==i){
									
									power += bias * ( bias/2 - y[i] + 1);
									//printf("i: %d power: %f \n",i,power);
									cyc_i++;
								}
							}
							
							
								
							W = exp((1/(sigma))*power);
							//W = exp((1/(sigma*sigma))*power);	//correct
							//printf("W : %E \n",W);
							
							// frameerror add W
							frameerror+= W;
							break;
						}
							
					}
				
				}
			} 
			
			
			FER[q] = ((double)frameerror)/((double)numtime * cycle6);	//FER 為全部 VN 的 IS estimation 相加起來 ? 
			

		
		printf("final FER: %E\n",FER[q]);
	}

	
	
	
	
	
	// Record the end time
    time_t end = clock();

    double diff = end - start; // ms
    printf(" %f  sec", diff / CLOCKS_PER_SEC );
    
	
	/*
	//寫入檔案 CSV
	FILE *fp = fopen("LDPC_IS.csv", "w");
    
    //避免開啟失敗 
    if (fp == NULL) {
        fprintf(stderr, "fopen() failed.\n");
        exit(EXIT_FAILURE);
    }
    
    
    for(int i=0;i<2;i++){
    	//printf("%d %d\n",q++,H[i][0]);
		for(int j=0;j<SNR_L;j++){
			if(i==0)
				fprintf(fp, "%f,",SNR_dB[j]);
			else if(i==1)
				fprintf(fp, "%E,",FER[j]);

		}	
		
		fprintf(fp, "\n");
	}
	
	fclose(fp);
	*/
	
	return 0;
}







