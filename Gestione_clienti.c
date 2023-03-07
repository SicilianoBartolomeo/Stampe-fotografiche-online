/*
 * Gestione_clienti.c
 *
 *  Created on: 25 ago 2020
 *      Author: Barty
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "Appello1Settembre.h"


void inserimento_cliente(FILE *file_clienti){

	cliente cli = {0,0};
	char controllo[10] = "";
	short int flag = 0;

	do{
	        	  puts("Inserire i dati del cliente (-1 nel codice per terminare) -->");
	  	          do{
	  	              puts("\n\n\tCODICE CLIENTE   --> " );
	  	              scanf("%s",controllo);
                   //programmazione difensiva-controllo che il codice non sia un carattere
	  	            if( (isdigit(controllo[0]) == 0) && (isdigit(controllo[1]) == 0) ){
	  	                puts("Codice errato!! Il valore inserito e' alfanumerico, sono validi solo numeri \n\n");
	  	                flag = 1;
	  	            }
	  	            else{
	  	            	//conversione in intero di una stringa
	  	                cli.codice_cliente = atoi(controllo);
	  	                flag = 0;
	  	            }
	  	          }while(flag != 0);

	        	  if (cli.codice_cliente != -1){
	      	        do{
	      	            puts("\n\n\tCODICE PRODOTTO   --> " );
	      	            scanf("%s",controllo);
	      	          //programmazione difensiva-controllo che il codice non sia un carattere
	      	            if( (isdigit(controllo[0]) == 0) && (isdigit(controllo[1]) == 0) ){
	      	                puts("Codice errato!! Il valore inserito e' alfanumerico, sono validi solo numeri \n\n");
	      	                flag = 1;
	      	            }
	      	            else{
	      	                cli.codice_prodotto = atoi(controllo);
	      	                flag = 0;
	      	            }
	      	          }while(flag != 0);

	      	        //sposto il puntatore in base al codice cliente inserito e salvo le informazioni
	        		  fseek(file_clienti,(cli.codice_cliente-1)*sizeof(cliente), SEEK_SET);
	        		  fwrite(&cli, sizeof(cliente), 1, file_clienti);
	        	  }
	          }while (cli.codice_cliente!=-1);

           printf("***************Inserimento Terminato******************\n\n");
}

void stampa_clienti(FILE *file_clienti){
	cliente cli = {0,0};

	rewind(file_clienti);

	puts("I dati memorizzati nel file clienti sono i seguenti \n");
	puts("Codice cliente       Codice prodotto acquistato");

	while (!feof(file_clienti)){
		fread(&cli, sizeof(cliente), 1, file_clienti);
		if (!feof(file_clienti))

			printf("      %hd                %hd", cli.codice_cliente, cli.codice_prodotto);
		    puts("\n\n");
	}

	 puts("***************File Terminato******************\n\n");

}

void modifica_cliente(FILE *file_clienti){
	cliente cli = {0,0};
	char controllo[10] = "";
	short int flag = 0;

	do {
		puts("Inserire il codice del cliente che vuoi modificare (-1 nel codice per terminare) -->");

          do{
              puts("\n\n\tCODICE CLIENTE   --> " );
              scanf("%s",controllo);
              //programmazione difensiva-controllo che il codice non sia un carattere
            if( (isdigit(controllo[0]) == 0) && (isdigit(controllo[1]) == 0) ){
                puts("Codice errato!! Il valore inserito e' alfanumerico, sono validi solo numeri \n\n");
                flag = 1;
            }
            else{
                cli.codice_cliente = atoi(controllo);
                flag = 0;
            }
          }while(flag != 0);

		if (cli.codice_cliente != -1){
		//sposto il puntatore in base al codice inserito e leggo il record corrispondente
			fseek(file_clienti,(cli.codice_cliente-1)*sizeof(cliente), SEEK_SET);
			//questa fread e' necessaria per controllare che il record esista e sia avvalorato
			fread(&cli, sizeof(cliente), 1, file_clienti);

			if (!feof(file_clienti)){
      	        do{
      	            puts("\n\n\tCODICE PRODOTTO   --> " );
      	            scanf("%s",controllo);
      	          //programmazione difensiva-controllo che il codice non sia un carattere
      	            if( (isdigit(controllo[0]) == 0) && (isdigit(controllo[1]) == 0) ){
      	                puts("Codice errato!! Il valore inserito e' alfanumerico, sono validi solo numeri \n\n");
      	                flag = 1;
      	            }
      	            else{
      	                cli.codice_prodotto = atoi(controllo);
      	                flag = 0;
      	            }
      	          }while(flag != 0);

      	      //questa fseek e' necessaria perchË dopo la fread il puntatore si e' spostato
				fseek(file_clienti,(cli.codice_cliente-1)*sizeof(cliente), SEEK_SET);
				fwrite(&cli, sizeof(cliente), 1, file_clienti);
			}
			else
				puts("Codice non trovato!");
		}
	}while (cli.codice_cliente != -1);
}

void cancella_cliente(FILE *file_clienti){

	cliente cli, cli_reset ={0,0};
	int codice;
	char controllo[10] = "";
	short int flag = 0;

	do {
		puts("Inserire il codice del cliente che vuoi cancellare (-1 nel codice per terminare) -->");

        do{
            puts("\n\n\tCODICE CLIENTE   --> " );
            scanf("%s",controllo);

          if( (isdigit(controllo[0]) == 0) && (isdigit(controllo[1]) == 0) ){
              puts("Codice errato!! Il valore inserito e' alfanumerico, sono validi solo numeri \n\n");
              flag = 1;
          }
          else{
              cli.codice_cliente = atoi(controllo);
              flag = 0;
          }
        }while(flag != 0);

		if (cli.codice_cliente != -1){

			fseek(file_clienti,(cli.codice_cliente-1)*sizeof(cliente), SEEK_SET);
			fread(&cli, sizeof(cliente), 1, file_clienti); //questa fread Ë necessaria per controllare che il record esista e sia avvalorato

			if (!feof(file_clienti)){
				codice = cli.codice_cliente; //mi conservo il codice prima di sovrascriverlo
				cli = cli_reset;

				fseek(file_clienti,(codice-1)*sizeof(cliente), SEEK_SET); //questa fseek Ë necessaria perchË dopo la fread il puntatore si Ë spostato
				fwrite(&cli, sizeof(cliente), 1, file_clienti);
				puts("Record cancellato");
			}
			else
				puts("Codice non trovato!");
		}
	}while (cli.codice_cliente != -1);
}

