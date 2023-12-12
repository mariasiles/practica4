#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
// Funció per moure i canviar el nom dels arxius
int my_mv(char arxiu_origen[], char arxiu_desti[]){
	// Obrir l'arxiu d'origen en mode lectura
	int f;
	if ((f=open(arxiu_origen, O_RDONLY))<0){
		perror("Error en el open");// Tractament d'errors
	        return 1;
	}
	// Crear o obrir l'arxiu de destí en mode escriptura, creant-lo si no existeix
	int desc_destino = open(arxiu_desti, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (desc_destino<0){
		perror("Error al crear l'arxiu destí");// Tractament d'errors
		close(f);
		return 1;
	}
        char c;
        int f2;
	// Llegir l'arxiu d'origen caracter per caràcter
	while ((f2 = read(f, &c, 1)) != 0) {
		 if (f2 == -1) {
			 perror("Error al leer del archivo de origen");// Tractament d'errors
			 close(f);
			 close(desc_destino);
                         return 1;
		 }
	if (write(desc_destino, &c, 1) == -1) {
		perror("Error al escribir en el archivo de destino");// Tractament d'errors
		close(f);
		close(desc_destino);
		return 1;
	}
	}
	// Tancar els arxius després de l'operació de lectura/escriptura
	close(f);
	close(desc_destino);
	// Eliminar l'arxiu d'origen després de la còpia 
	if (unlink(arxiu_origen) != 0) {
		perror("Error en eliminar l'arxiu d'origen");
		return 1;
	}
	return 0;// Operació correcte
	
}



// Funció principal

int main(){
	char arxiu_origen[100];
	char arxiu_desti[100];
	// Demanar a l'usuari el nom de l'arxiu d'origen
	printf("Introdueix el nombre de l'arxiu a moure: ");
        scanf("%s",arxiu_origen);// Guarda l'arxiu origen en la variable arxiu_origen
	// Demanar a l'usuari el nou nom de l'arxiu
        printf("Introdueix el nou nom de l'arxiu: ");
	scanf("%s",arxiu_desti);// Guarda el nom de l'arxiu destí en la variable arxiu_destí

	// Crida a la funció per moure i canviar el nom dels arxius
        if (my_mv(arxiu_origen,arxiu_desti)==0){
		printf("L'arxiu s'ha mogut i renombrat amb èxit\n");
	}
        return 0;// Acaba el programa
}

