//Nohl Egan 250964782

#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>

struct account{
	char type[8];
	int balance;
	int depositFee;
	int withdrawFee;
	int transferFee;
	int numTransactions;
	int transactionLimit;
	int transactionFee;
	int overdraftFee;
	int overdrafts;
	bool overdraftProtection;
};

struct transaction{
	char type;
	int amount;
	int sender;
	int receiver;
};

struct account bankAccount[999];
struct transaction transList[999];

void  *transaction(void *x);
pthread_mutex_t lock;
int transactionsCompleted = 0;

void  *transaction(void *x){
	pthread_mutex_lock(&lock);
	int transNum = transactionsCompleted;
	char type = transList[transNum].type;
	int amount = transList[transNum].amount;
	int sender = transList[transNum].sender;
	int receiver = transList[transNum].receiver;
	
	if(type == 'd'){
		bankAccount[receiver].balance += amount - bankAccount[receiver].depositFee;
		if(bankAccount[receiver].numTransactions >= bankAccount[receiver].transactionLimit){
			bankAccount[receiver].balance -= bankAccount[receiver].transactionFee;
		}
		bankAccount[receiver].numTransactions++;
	}

	else if(type == 'w'){
		int original = bankAccount[sender].balance;
		bankAccount[sender].balance -= amount + bankAccount[sender].withdrawFee;
		if(bankAccount[sender].numTransactions >= bankAccount[sender].transactionLimit){
			bankAccount[sender].balance -= bankAccount[sender].transactionFee;
		}
		if (bankAccount[sender].balance < -5000){
			bankAccount[sender].balance = original;
			bankAccount[sender].numTransactions--;
		}	
		else if(bankAccount[sender].balance < 0){
			if(bankAccount[sender].overdraftProtection){
				if(bankAccount[sender].balance < 0 && original >= 0){
					bankAccount[sender].balance -= bankAccount[sender].overdraftFee;			
					bankAccount[sender].overdrafts++;
				}
				if(bankAccount[sender].balance <= -500 && original > -500){
					bankAccount[sender].balance -= bankAccount[sender].overdraftFee;			
					bankAccount[sender].overdrafts++;
				}
				if(bankAccount[sender].balance <= -1000 && original > -1000){
					bankAccount[sender].balance -= bankAccount[sender].overdraftFee;			
					bankAccount[sender].overdrafts++;
				}
				if(bankAccount[sender].balance <= -1500 && original > -1500){
					bankAccount[sender].balance -= bankAccount[sender].overdraftFee;			
					bankAccount[sender].overdrafts++;
				}
				if(bankAccount[sender].balance <= -2000 && original > -2000){
					bankAccount[sender].balance -= bankAccount[sender].overdraftFee;			
					bankAccount[sender].overdrafts++;
				}
				if(bankAccount[sender].balance <= -2500 && original > -2500){
					bankAccount[sender].balance -= bankAccount[sender].overdraftFee;			
					bankAccount[sender].overdrafts++;
				}
				if(bankAccount[sender].balance <= -3000 && original > -3000){
					bankAccount[sender].balance -= bankAccount[sender].overdraftFee;			
					bankAccount[sender].overdrafts++;
				}
				if(bankAccount[sender].balance <= -3500 && original > -3500){
					bankAccount[sender].balance -= bankAccount[sender].overdraftFee;			
					bankAccount[sender].overdrafts++;
				}
				if(bankAccount[sender].balance <= -4000 && original > -4000){
					bankAccount[sender].balance -= bankAccount[sender].overdraftFee;			
					bankAccount[sender].overdrafts++;
				}
				if(bankAccount[sender].balance <= -4500 && original > -4500){
					bankAccount[sender].balance -= bankAccount[sender].overdraftFee;			
					bankAccount[sender].overdrafts++;
				}
				if(bankAccount[sender].balance < -5000){
					bankAccount[sender].balance = original;
					bankAccount[sender].numTransactions--;
				}
			}
			else{
				bankAccount[sender].balance = original;
				bankAccount[sender].numTransactions--;
			}
		}
		bankAccount[sender].numTransactions++;
	}
	
	else if(type == 't'){
		bool withdrawn = true;
		int original = bankAccount[sender].balance;
		bankAccount[sender].balance -= amount + bankAccount[sender].transferFee;
		if(bankAccount[sender].numTransactions >= bankAccount[sender].transactionLimit){
			bankAccount[sender].balance -= bankAccount[sender].transactionFee;
		}
		if (bankAccount[sender].balance < -5000){
			bankAccount[sender].balance = original;
			bankAccount[sender].numTransactions--;
			withdrawn = false;
		}	
		else if(bankAccount[sender].balance < 0){
			if(bankAccount[sender].overdraftProtection){
				if(bankAccount[sender].balance < 0 && original >= 0){
					bankAccount[sender].balance -= bankAccount[sender].overdraftFee;			
					bankAccount[sender].overdrafts++;
				}				
				if(bankAccount[sender].balance <= -500 && original > -500){
					bankAccount[sender].balance -= bankAccount[sender].overdraftFee;			
					bankAccount[sender].overdrafts++;
				}
				if(bankAccount[sender].balance <= -1000 && original > -1000){
					bankAccount[sender].balance -= bankAccount[sender].overdraftFee;			
					bankAccount[sender].overdrafts++;
				}
				if(bankAccount[sender].balance <= -1500 && original > -1500){
					bankAccount[sender].balance -= bankAccount[sender].overdraftFee;			
					bankAccount[sender].overdrafts++;
				}
				if(bankAccount[sender].balance <= -2000 && original > -2000){
					bankAccount[sender].balance -= bankAccount[sender].overdraftFee;			
					bankAccount[sender].overdrafts++;
				}
				if(bankAccount[sender].balance <= -2500 && original > -2500){
					bankAccount[sender].balance -= bankAccount[sender].overdraftFee;			
					bankAccount[sender].overdrafts++;
				}
				if(bankAccount[sender].balance <= -3000 && original > -3000){
					bankAccount[sender].balance -= bankAccount[sender].overdraftFee;			
					bankAccount[sender].overdrafts++;
				}
				if(bankAccount[sender].balance <= -3500 && original > -3500){
					bankAccount[sender].balance -= bankAccount[sender].overdraftFee;			
					bankAccount[sender].overdrafts++;
				}
				if(bankAccount[sender].balance <= -4000 && original > -4000){
					bankAccount[sender].balance -= bankAccount[sender].overdraftFee;			
					bankAccount[sender].overdrafts++;
				}
				if(bankAccount[sender].balance <= -4500 && original > -4500){
					bankAccount[sender].balance -= bankAccount[sender].overdraftFee;			
					bankAccount[sender].overdrafts++;
				}
				if(bankAccount[sender].balance < -5000){
					bankAccount[sender].balance = original;
					bankAccount[sender].numTransactions--;
					withdrawn = false;
				}
			}
			else{
				bankAccount[sender].balance = original;
				bankAccount[sender].numTransactions--;
			}
		}
		
		bankAccount[sender].numTransactions++;

		if(withdrawn){
			bankAccount[receiver].balance += amount - bankAccount[receiver].transferFee;
			if(bankAccount[receiver].numTransactions >= bankAccount[receiver].transactionLimit){
				bankAccount[receiver].balance -= bankAccount[receiver].transactionFee;
			}
			bankAccount[receiver].numTransactions++;
		}
	}
	transactionsCompleted++;
	pthread_mutex_unlock(&lock);
}

int main(){
	FILE *inputFile, *outputFile;
	inputFile = fopen("assignment_3_input_file.txt", "r");
	outputFile = fopen("assignment_3_output_file.txt", "w");
	char input[999];
	int i = 0, numAccounts = 0;
	while(fscanf(inputFile, "%c", &input[i]) != EOF){
		if(input[i] == 'a'){
			if(input[i-1] == '\n'){
				numAccounts++;
			}
			else if(i == 0){
				numAccounts++;
			}
		}
		i++;
	}
	input[i] = '\0';
	i = 0;
	fclose(inputFile);

	for(int temp = 0; temp < numAccounts; temp++){
		bankAccount[temp].numTransactions = 0;
		bankAccount[temp].balance = 0;
		bankAccount[temp].overdrafts = 0;
	}
	int accountNum = 0;
	int transNum = 0;
	while(input[i] != '\0'){
		if(input[i] == 'a' && isdigit(input[i+1]) && accountNum != numAccounts){
			i++;
			while(input[i] != '\n'){
				if(input[i] == 't' && input[i+1] == 'y'){
					i += 3;
					while(input[i] != 'b' && input[i] != 'p'){
						i++;
					}
					int x = 0;
					while(input[i] != ' '){
						bankAccount[accountNum].type[x] = input[i];
						x++;
						i++;
					}
				}

				else if(input[i] == 'd' && input[i+1] == ' '){
					while(!isdigit(input[i])){
						i++;
					}
					char deposit[999];
					int x = 0;
					while(isdigit(input[i])){
						deposit[x] = input[i];
						x++;
						i++;
					}
					deposit[x] = '\0';
					bankAccount[accountNum].depositFee = atoi(deposit);
					while(x != 0){
						deposit[x] = '\0';
						x--;
					}
				}

				else if(input[i] == 'w' && input[i+1] == ' '){
					while(!isdigit(input[i])){
						i++;
					}
					char withdraw[999];
					int x = 0;
					while(isdigit(input[i])){
						withdraw[x] = input[i];
						x++;
						i++;
					}
					withdraw[x] = '\0';
					bankAccount[accountNum].withdrawFee = atoi(withdraw);
					while(x != 0){
						withdraw[x] = '\0';
						x--;
					}
				}

				else if(input[i] == 't' && input[i+1] == ' '){
					while(!isdigit(input[i])){
						i++;
					}
					char transfer[999];
					int x = 0;
					while(isdigit(input[i])){
						transfer[x] = input[i];
						x++;
						i++;
					}
					transfer[x] = '\0';
					bankAccount[accountNum].transferFee = atoi(transfer);
					while(x != 0){
						transfer[x] = '\0';
						x--;
					}
				}

				else if(input[i] == 't' && input[i+1] == 'r'){
					while(!isdigit(input[i])){
						i++;
					}
					char transLimit[999];
					char transFee[999];
					int x = 0;
					while(isdigit(input[i])){
						transLimit[x] = input[i];
						x++;
						i++;
					}	
					bankAccount[accountNum].transactionLimit = atoi(transLimit);
					while(x != 0){
						transLimit[x] = '\0';
						x--;
					}

					while(!isdigit(input[i])){
						i++;
					}
					while(isdigit(input[i])){
						transFee[x] = input[i];
						x++;
						i++;
					}	
					transFee[x] = '\0';
					bankAccount[accountNum].transactionFee = atoi(transFee);
					while(x != 0){
						transFee[x] = '\0';
						x--;
					}
				}
				
				else if(input[i] == 'o' && input[i+1] == 'v'){
					while(input[i] != 'Y' && input[i] != 'N'){
						i++;
					}
					if(input[i] == 'N'){
						bankAccount[accountNum].overdraftProtection = false;
						bankAccount[accountNum].overdraftFee = 0;
					}
					else if(input[i] == 'Y'){
						bankAccount[accountNum].overdraftProtection = true;
						while(!isdigit(input[i])){
							i++;
						}
						char over[999];
						int x = 0;
						while(isdigit(input[i])){
							over[x] = input[i];
							x++;
							i++;
						}
						over[x] = '\0';
						bankAccount[accountNum].overdraftFee = atoi(over);
						while(x != 0){
							over[x] = '\0';
							x--;
						}
					}
				}
				
				else{
					i++;
				}
			}
			accountNum++;
		}
		
		else if(input[i] == 'd' && input[i+1] == 'e'){
			i++;
			while(input[i] != '\n'){
				if(input[i] == 'd'){
					transList[transNum].type = 'd';
					while(input[i] != 'a'){
						i++;
					}
					i++;
					char dep[999];
					int x = 0;
					while(input[i] != ' '){
						dep[x] = input[i];
						i++;
						x++;
					}
					dep[x] = '\0';
					transList[transNum].receiver = atoi(dep) - 1;
					while(x != 0){
						dep[x] = '\0';
						x--;
					}
					while(!isdigit(input[i])){
						i++;
					}
					while(isdigit(input[i])){
						dep[x] = input[i];
						i++;
						x++;
					}
					dep[x] = '\0';
					transList[transNum].amount = atoi(dep);
					while(x != 0){
						dep[x] = '\0';
						x--;
					}
					transNum++;
				}
	
				else{
					i++;
				}
			}
		}

		else if(input[i] == 'c' && isdigit(input[i+1])){
			i++;
			while(input[i] != '\n'){
				if(input[i] == 'd'){
					transList[transNum].type = 'd';
					while(input[i] != 'a'){
						i++;
					}
					i++;
					char dep[999];
					int x = 0;
					while(input[i] != ' '){
						dep[x] = input[i];
						i++;
						x++;
					}
					dep[x] = '\0';
					transList[transNum].receiver = atoi(dep) - 1;
					while(x != 0){
						dep[x] = '\0';
						x--;
					}
					while(!isdigit(input[i])){
						i++;
					}
					while(isdigit(input[i])){
						dep[x] = input[i];
						i++;
						x++;
					}
					dep[x] = '\0';
					transList[transNum].amount = atoi(dep);
					while(x != 0){
						dep[x] = '\0';
						x--;
					}
					transNum++;
				}
				
				else if(input[i] == 'w'){
					transList[transNum].type = 'w';
					while(input[i] != 'a'){
						i++;
					}
					i++;
					char with[999];
					int x = 0;
					while(input[i] != ' '){
						with[x] = input[i];
						i++;
						x++;
					}
					with[x] = '\0';
					transList[transNum].sender = atoi(with) - 1;
					while(x != 0){
						with[x] = '\0';
						x--;
					}
					while(!isdigit(input[i])){
						i++;
					}
					while(isdigit(input[i])){
						with[x] = input[i];
						i++;
						x++;
					}
					with[x] = '\0';
					transList[transNum].amount = atoi(with);
					while(x != 0){
						with[x] = '\0';
						x--;
					}
					transNum++;
				}
				
				else if(input[i] == 't'){
					transList[transNum].type = 't';
					while(input[i] != 'a'){
						i++;
					}
					i++;
					char trans[999];
					int x = 0;
					while(input[i] != ' '){
						trans[x] = input[i];
						i++;
						x++;
					}
					trans[x] = '\0';
					transList[transNum].sender = atoi(trans) - 1;
					while(x != 0){
						trans[x] = '\0';
						x--;
					}
					while(input[i] != 'a'){
						i++;
					}
					i++;
					while(input[i] != ' '){
						trans[x] = input[i];
						i++;
						x++;
					}
					trans[x] = '\0';
					transList[transNum].receiver = atoi(trans) - 1;
					while(x != 0){
						trans[x] = '\0';
						x--;
					}
					while(!isdigit(input[i])){
						i++;
					}
					while(isdigit(input[i])){
						trans[x] = input[i];
						i++;
						x++;
					}
					trans[x] = '\0';
					transList[transNum].amount = atoi(trans);
					while(x != 0){
						trans[x] = '\0';
						x--;
					}
					transNum++;
				}
				else{
					i++;
				}
			}
		}
		
		i++;
	}
	
	int err_thread;
	pthread_t threads[transNum];
	for(int x = 0; x < transNum; x++){
		err_thread = pthread_create(&threads[x], NULL, &transaction, &threads[x]); 

		if (err_thread != 0){
			printf("\n Error creating thread %d", x);
		}
	}
	
	for (int x = 0; x < transNum; x++){
		pthread_join(threads[x], NULL);
	}

	for (int x = 0; x < numAccounts; x++){
		printf("a%d type %.8s %d\n", x+1, bankAccount[x].type, bankAccount[x].balance);
		fprintf(outputFile, "a%d type %.8s %d\n", x+1, bankAccount[x].type, bankAccount[x].balance);
	}

	pthread_mutex_destroy(&lock); 

	
	
	fclose(outputFile);
}
