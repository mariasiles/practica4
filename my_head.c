#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
// Creem una funció que imprimeix les primeres 'numeroLinies' linies de l'arxiu identificat per 'arxiu'.
int my_head(int arxiu, int numeroLinies){
	//Imprimeix un encapçalament indicant la quantitat de línies a mostrar.
	printf("Contingut de les primeres %d linies:\n",numeroLinies);
	// Itera sobre el nombre de línies especificat.
	for (int i=0; i<numeroLinies;i++){
		char c;
		 // Llegeix un caràcter de l'arxiu.
		int numLlegits=read(arxiu, &c, 1);
		 // Llegeix l'arxiu caràcter per caràcter fins trobar un salt de línia o arribar al final de l'arxiu.
                while (numLlegits > 0 && c !='\n'){
			// Imprimeix el caràcter llegit.
			printf("%c",c);
			// Llegeix el següent caràcter.
			numLlegits=read(arxiu,&c,1);
		}
		// Imprimeix un salt de línia al final de cada línia llegida.
		printf("\n");
	}
}

int main(){
	// Declaració de variables.
	char nom_arxiu[50];
	int numeroLinies;
	int f;
	// Sol·licita a l'usuari el nom de l'arxiu.
	printf("Introdueix el nom de l'arxiu: ");
	scanf("%s",nom_arxiu);
	// Intenta obrir l'arxiu en mode lectura.
	if((f=open(nom_arxiu, O_RDONLY))<0){
		 perror("Error en el open");// Imprimeix un missatge d'error si l'arxiu no es pot obrir.
		 return 1;
						        }
	// Sol·licita a l'usuari el nombre de línies a mostrar.
	printf("Introdueix el número de linies a mostrar: ");
	scanf("%d",&numeroLinies);
	// Verifica que el nombre de línies sigui vàlid.
	if (numeroLinies<=0){
		printf("Error número de línies incorrecte\n");
		return 1;
	}
	// Crida la funció 'my_head' per mostrar les primeres línies de l'arxiu.
	my_head(f,numeroLinies);
	// Tanca l'arxiu després de la seva utilització.
	close(f);
	return 0;
}





