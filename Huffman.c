#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define Nodo struct nodo
#define Arbol struct arbol

Arbol{
	int letra,fr;
	Arbol*izq;
	Arbol*der;
};

Nodo{
	Arbol*raiz;
	Nodo*siguiente;
	Nodo*anterior;
};
int buscador(int dato);
Arbol*desencolar();
void insertarCola(int dato);
void insertarOrden(Arbol*dato);
Nodo*nuevoNodo(Arbol*dato);
int convertir(int bin);
void recur();
Arbol*nuevoArbol(int dato,int n);
void ordenar();
void inorden(FILE*hola,Arbol*r,int n);
int colaVacia();
void lineas(FILE*Leer,int num);
void imprimir(char*binario);

Nodo*inicio=NULL;
Nodo*final=NULL;
int con=0,con1=0;
char cad[100];

void imprimir(char*binario){
	FILE*encritador=fopen("error.txt","ab");
	int len=strlen(binario);
	printf("Binario: ");
	puts(binario);
	printf("\n|----------------------------------------------------------------------------------------------------------------------|\n");
	printf("\nEl archivo contine %i Bits\n",len);
	printf("\n|----------------------------------------------------------------------------------------------------------------------|\n");
	int bytes=len/8,sb=len%8,num,aux,j,i;
	char byte[8],sll[7];
	printf("Frase Encriptado: ");
	for(i=1;i<=bytes+1;i++){
		aux=0;
		if(i<bytes+1){
			for(j=8*(i-1);j<8*i;j++){
				byte[aux]=binario[j];
				aux++;
			}
			num=convertir(atoi(byte));
			printf("%c",num);
			fprintf(encritador,"%c",num);
		}else if(sb!=0){
			for(j=8*(i-1);j<(8*(i-1))+sb;j++){
				sll[aux]=binario[j];
				aux++;
			}
			num=convertir(atoi(sll));
			printf("%c",num);
			fprintf(encritador,"%c",num);
		}
	}
	printf("\n|----------------------------------------------------------------------------------------------------------------------|\n");
	fclose(encritador);
}

int convertir(int bin){
	int c=1,d=0,p;
	while(bin>0)
	{
		p=0;
		p=c*(bin%10);
		d+=p;
		c*=2;
		bin/=10;
	}
	return d;
}

void recur(){
	int n;
	if(inicio==final)
		return;
	Arbol*nuevo1=desencolar();
	Arbol*nuevo2=desencolar();
	n=nuevo1->fr+nuevo2->fr;
	Arbol*arbolito=nuevoArbol(46,n);
	arbolito->izq=nuevo1;
	arbolito->der=nuevo2;
	insertarOrden(arbolito);
	recur();
	
}

void insertarOrden(Arbol*dato){
	Nodo*nuevo=nuevoNodo(dato);
	Nodo*aux=inicio,*ant=NULL;
	while(aux!=NULL){
		if(aux->raiz->fr==nuevo->raiz->fr){
			if(aux==inicio){
				nuevo->siguiente=inicio;
				inicio->anterior=nuevo;
				inicio=nuevo;
			}else{
				ant->siguiente=nuevo;
				nuevo->anterior=ant;
				nuevo->siguiente=aux;
				aux->anterior=nuevo;
			}
			return;
		}
		ant=aux;
		aux=aux->siguiente;
	}
	if(inicio==NULL && final==NULL){
		inicio=nuevo;
		final=nuevo;
	}else{
		final->siguiente=nuevo;
		nuevo->anterior=final;
		final=nuevo;
	}
}

Arbol*desencolar(){
	Nodo*aux;
	if(colaVacia()){
		return NULL;
	}else{
		aux=inicio;
		inicio=inicio->siguiente;
		aux->siguiente=NULL;
		if(inicio!=NULL){
			inicio->anterior=NULL;
		}else{
			final=NULL;
		}
	}
	Arbol*resultado=aux->raiz;
	free(aux);
	return resultado;
}

void insertarCola(int dato){
	con++;
	if(buscador(dato)==1){
		return;	
	}
	Arbol*arbolito=nuevoArbol(dato,1);
	Nodo*nuevo=nuevoNodo(arbolito);
	if(inicio==NULL && final==NULL){
		inicio=nuevo;
		final=nuevo;
	}else{
		final->siguiente=nuevo;
		nuevo->anterior=final;
		final=nuevo;
	}
}

Arbol*nuevoArbol(int dato,int n){
	Arbol*nuevo=(Arbol*)malloc(sizeof(Arbol));
	nuevo->letra=dato;
	nuevo->fr=n;
	nuevo->izq=NULL;
	nuevo->der=NULL;
	return nuevo;
}

Nodo*nuevoNodo(Arbol*dato){
	Nodo*nuevo=(Nodo*)malloc(sizeof(Nodo));
	nuevo->raiz=dato;
	nuevo->siguiente=NULL;
	nuevo->anterior=NULL;
	return nuevo;
}

int buscador(int dato){
	Nodo*aux=inicio;
	while(aux!=NULL){
		if(aux->raiz->letra==dato){
			aux->raiz->fr++;
			return 1;
		}
		aux=aux->siguiente;
	}
	return 0;
}

void ordenar(){
	if(inicio!=NULL){
		Nodo*piv=inicio;
		Nodo*apiv=NULL;
		Nodo*aux=inicio->siguiente;
		Nodo*max=inicio;
		Nodo*ant=inicio;
		while(piv!=NULL){
			while(aux!=NULL){
				if(aux->raiz->fr<max->raiz->fr){
					ant->siguiente=aux->siguiente;
					if(ant->siguiente==NULL)
						final=ant;
					aux->siguiente=piv;
					if(piv==inicio){
						inicio=aux;
					}else{
						apiv->siguiente=aux;
					}
					max=aux;
					piv=aux;
					aux=ant->siguiente;
				}else{
					aux=aux->siguiente;
					ant=ant->siguiente;
				}
			}
			apiv=piv;
			piv=piv->siguiente;
			max=max->siguiente;
			if(piv==NULL){
				aux=NULL;
			}else{
				aux=piv->siguiente;
			}
			ant=piv;
		}
	}
}

void inorden(FILE*hola,Arbol*r,int n){
	if(r!=NULL){
		inorden(hola,r->izq,n*10);
		if(r->letra!=46){
			if(hola==NULL){
				perror("Error en el cargado del archivo");
				return;
			}
			fprintf(hola,"%c %i\n",r->letra,n);
		}
		inorden(hola,r->der,n*10+1);
	}
	con1=0;
}

int colaVacia(){
	if(inicio==NULL && final==NULL){
		return 1;
	}else{
		return 0;
	}
}

void lineas(FILE*Leer,int num){
	int conta=num-1;
	fseek(Leer, 0, SEEK_SET);
	prueba:     
		if (conta>0)  
	{ 
			while (fgetc(Leer) != '\n');
			conta--;
			goto prueba;
	}
}
int main(){
	int len,i,j;
	char codigo[100],*binario=NULL;
	FILE*texto1 = fopen("Karimnot.txt","r");
	printf("El texto que esta en el archivo es:\n");
	while(!feof(texto1)){
		printf("%c",getc(texto1));
	}
	printf("\n|----------------------------------------------------------------------------------------------------------------------|\n");
	FILE*texto = fopen("Karimnot.txt","rb");
	if(texto==NULL){
		return 0;
	}
	while(!feof(texto)){
		char caracter=fgetc(texto);
		if(caracter==-1)
			break;
		insertarCola(caracter);
	}
	fclose(texto);
	ordenar();
	recur();
	FILE*hola=fopen("error.txt","wb");
	inorden(hola,inicio->raiz,7);
	fclose(hola);
	
	FILE*Leer = fopen("error.txt","rb"); 
	FILE*Palabra = fopen("Karimnot.txt","rb"); 
	if(Leer==NULL || Palabra==NULL){
		printf("Error en el archivo\n");
		return 0;
	}
	while(!feof(Palabra)){
		char caracter=fgetc(Palabra);
		if(caracter==-1)
			break;
		for(i=0;i<con;i++){
			lineas(Leer,i+1);
			char c=fgetc(Leer);
			if(caracter==c){
				fseek(Leer,2, SEEK_CUR);
				fscanf(Leer," %s",&codigo);
				len=strlen(codigo);
				if(binario==NULL){
					binario=malloc((len+1)*sizeof(char));   
					
					
					for(j=0;j<(len+1);j++){
						binario[j]=0;
					}
					
					
				}else{
					binario=realloc(binario,(strlen(binario)+len+1)*sizeof(char));
				}
				strcat(binario,codigo);
				goto cont;
			}
		}
		cont:
			rewind(Leer);
	}
	fclose(Palabra);
	fclose(Leer);
	imprimir(binario);
}
