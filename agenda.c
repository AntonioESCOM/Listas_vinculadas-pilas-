//Programa que gestiona un directorio 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nodo{
	char nombre[100];
	char direccion[100];
	char numero [12];
	struct nodo *ptrsig;
};

int menu(){
  int i;
  printf("Que quiere hacer? \n 1. Guardar datos \n 2. Buscar numero \n 3. Eliminar número\n 4. Imprimir contenido\n 5.Salir\n ");
  scanf("%d", &i);
  return i;
}
struct nodo* crearNodo(char *ptrname, char*ptrdir, char*ptrnum){
	struct nodo*ptrN;
	ptrN=(struct nodo*)malloc(sizeof(struct nodo));
	strcpy(ptrN->nombre,ptrname);
	strcpy(ptrN->direccion,ptrdir);
	strcpy(ptrN->numero,ptrnum);
	ptrN->ptrsig=NULL;
	return ptrN;
}
int comp_2ele (struct nodo*ptrvar, struct nodo*ptrNew,int n){
	if(ptrNew->nombre[n] > ptrvar->ptrsig->nombre[n]){
		return 1;
	}
	else if(ptrNew->nombre[n] == ptrvar->ptrsig->nombre[n]){
		comp_2ele(ptrvar,ptrNew,n+1);
	}
	else
		return 0;
}
int comp_3ele (struct nodo*ptrvar, struct nodo*ptrNew,int n){
	if(ptrvar->nombre[n] > ptrNew->nombre[n]){
		return 1;
	}
	else if(ptrNew->nombre[n] == ptrvar->nombre[n]){
		comp_3ele(ptrvar,ptrNew,n+1);
	}
	else
		return 0;
}




void meter(struct nodo*ptrRef, char *ptrname, char*ptrdir, char*ptrnum){
	struct nodo *ptrNew,*ptrAv,*ptrRet;
	ptrNew=crearNodo(ptrname,ptrdir,ptrnum);
	if(ptrRef->ptrsig == NULL){
		ptrRef->ptrsig=ptrNew;
	}
	else if((ptrRef->ptrsig)->ptrsig== NULL){ //Hay 2 elementos en la lista
		if(comp_2ele(ptrRef,ptrNew,0) == 0 ){
			ptrNew->ptrsig=ptrRef->ptrsig;
			ptrRef->ptrsig=ptrNew;
		}
		else{
			ptrRef->ptrsig->ptrsig = ptrNew;
		}
	}
	
	else{											//Hay más de 2 elementos
		ptrRet=ptrRef;
		ptrAv=ptrRef->ptrsig;
		while(ptrRet->ptrsig != NULL){
			if(strcmp(ptrAv->nombre,ptrNew->nombre) == 0 ||strcmp(ptrAv->numero,ptrNew->numero) == 0){
				printf("El nombre o numero estan repetidos, por favor ingresa nuevamente el contacto!!\n");
				free(ptrNew);
				return;
			}		

			else if(comp_3ele(ptrAv,ptrNew,0) &&(comp_3ele(ptrRet,ptrNew,0)==0 || ptrRet ==ptrRef)){
				ptrNew->ptrsig=ptrAv;
				ptrRet->ptrsig=ptrNew;
				return;
			}
			ptrAv=ptrAv->ptrsig;
			ptrRet=ptrRet->ptrsig;
			
		}
			ptrRet->ptrsig=ptrNew;
	}
	return;
}


void impCont (struct nodo* ptrRef){
 	struct nodo* ptrRec;
	ptrRec=ptrRef->ptrsig;
	while(ptrRec!=NULL){
		printf("Nombre %s\n",ptrRec->nombre);
		printf("Direccion: %s\n",ptrRec->direccion);
		printf("El numero es %s\n\n",ptrRec->numero);
		ptrRec=ptrRec->ptrsig;
	}
	return;
}

int searchNum (struct nodo* ptrRef, char* numsearch){
	struct nodo* ptrSea;
	int bool =0;
	ptrSea=ptrRef->ptrsig;
	while(ptrSea!=NULL){
		if( strcmp(ptrSea->numero,numsearch) == 0){
			bool= 1;
		}
		ptrSea=ptrSea->ptrsig;
	}
	return bool;
}

void delnum (struct nodo* ptrRef, char* numsearch,char* numsave){
	struct nodo *ptrBas,*ptrRec,*ptrRet;
	ptrBas=ptrRef->ptrsig;
	if(ptrRef->ptrsig == NULL){
		printf("La estructura esta vacia\n");
		return;
	}
	else if(ptrBas->ptrsig == NULL){
		if(strcmp(ptrBas->numero,numsearch)){
			ptrRef->ptrsig=NULL;
			strcpy(ptrBas->numero,numsave);
			free(ptrBas);
			printf("El dato %s fue eliminado de la estructura\n",numsearch);
			return;
		}
		else{
			printf("El dato no se encuentra en la estrucutra\n");
			return;
		}
	}
	else{
		ptrRec=ptrRef->ptrsig;
		ptrRet=ptrRef;
		if(searchNum(ptrRef,numsearch)){
			while(ptrRec!=NULL){
				if(strcmp(ptrRec->numero,numsearch) == 0){
					ptrRet->ptrsig=ptrRec->ptrsig;
					ptrBas=ptrRec;
					strcpy(ptrBas->numero,numsave);
					free(ptrBas);
					printf("El dato %d fue eliminado de la estructura\n",numsearch);
					return;
				}
				ptrRec=ptrRec->ptrsig;
				ptrRet=ptrRet->ptrsig;
			}
		}
		else{ 
			printf("No se elimina ni a putazos\n");
			return;
		}
	}
	return;
}

int main(){
	char minum[12];
	char midatoSea[12];
	char miname[100];
	char midireccion[100];
	char minumsave[12];
	struct nodo *miptrRef;
	miptrRef=crearNodo("NULL","NULL","1000");
	for(;;){
		switch(menu()){
			case 1:
					printf("Ingresa el nombre\n");
					fflush(stdin);
					gets(miname);
					fflush(stdin);
					printf("Ingresa la direccion\n");
					fflush(stdin);
					gets(midireccion);
					fflush(stdin);
					printf("Ingresa el numero\n");
					fflush(stdin);
					gets(minum);
					fflush(stdin);
					meter(miptrRef,miname,midireccion,minum);
				break;
			case 2:
				printf("Ingresa el numero que deseas buscar\n");
				fflush(stdin);
				gets(midatoSea);
				fflush(stdin);
				if(searchNum(miptrRef,midatoSea) == 0)
					printf("No se encontro\n");
				else{
					printf("%s esta en la estructura\n",midatoSea);
				}
				break;
			case 3: 
				printf("Ingresa el numero que deseas eliminar \n");
				fflush(stdin);
				gets(midatoSea);
				fflush(stdin);
				delnum (miptrRef,midatoSea,minumsave);
			break;
			case 4:
				impCont(miptrRef);
			break;
			
			case 5:
				exit(0);
			break;
		}
	}
	return 0;
}