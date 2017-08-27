#include<stdio.h>
#include<string.h>
#include<math.h>
#include"interface.h"


int sizeConversor(char textSize[]);

int main(){

	int numberOfOperations, sizeDiskNum, sizeArqNum, j = 0;
	char operation[8], arqName[11], sizeArq[7], sizeDisk[7];
	DISK *drive = NULL;



	while(1){
		scanf("%d", &numberOfOperations);
		if(numberOfOperations == 0){
			break;
		}
		scanf("%s", sizeDisk);
		sizeDiskNum = sizeConversor(sizeDisk);
		diskInitializer(&drive, sizeDiskNum);

		for(j = 0; j < numberOfOperations; j++){
			scanf("%s", operation);

			if(strcmp(operation, "insere") == 0){
				scanf("%s", arqName);
				scanf("%s", sizeArq);
				sizeArqNum = sizeConversor(sizeArq);
				if(drive->error == 0)
					ArchiveInsertion(drive, arqName, sizeArqNum);
			}else if(strcmp(operation, "remove") == 0){
				scanf("%s", arqName);
				if(drive->error == 0)
					ArchiveRemover(drive, arqName);
			}else if(strcmp(operation, "otimiza") == 0){
				if(drive->error == 0)
					otimize(drive);
			}else{
				printf("Operacao Inexistente, digite uma operacao valida.\n");
				printf("Tente: insere <nome> <tamanho>, remove <nome> ou otimiza\n");
				j--;
			}

		}

		if(drive->error == 0)
			EstimateUsage(drive);
		else if(drive->error == 1)
			printf("ERRO: disco cheio\n");

	}

	freeTheDisk(&drive);
	return 0;
}

int sizeConversor(char textSize[]){

	int size = strlen(textSize);
	int power = 0, coeficient = 0, j = 1 ,i = 0;

	for (i = size; i >= 0; i--){
		if(textSize[i] == 'b')
			continue;
		else if(textSize[i] > 64 && textSize[i] < 91){

			if(textSize[i] == 'M')
				power = 10;
			if(textSize[i] == 'G')
				power = 20;

		}else if(textSize[i] > 47 && textSize[i] < 58){

			coeficient = coeficient + (textSize[i] - '0')*j;
			j*=10;

		}

	}
		size = coeficient*pow(2,power);

	return size;
}
