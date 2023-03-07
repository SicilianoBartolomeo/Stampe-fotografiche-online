/*
 * Gestione_prodotti.c
 *
 *  Created on: 25 ago 2020
 *      Author: Barty
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "Appello1Settembre.h"
#include "Gestione_ordini.h"

void inserimento_prodotto(FILE *file_prodotti){
	prodotto prod = {0,"",0,0,0,"",0,""};
	char controllo[10] = "";
	short int flag = 0, categoria = 0, i=0;

	do{

	        puts("Inserire i dati dell' ordine (-1 nel codice prodotto per terminare) -->");

	        //programmazione difensiva-controllo che il codice prodotto sia un numero
	        do{
	            puts("\n\n\tCODICE PRODOTTO   --> " );
	            scanf("%s",controllo);

	            if( (isdigit(controllo[0]) == 0) && (isdigit(controllo[1]) == 0) ){
	                puts("Codice errato!! Il valore inserito e' alfanumerico, sono validi solo numeri \n\n");
	                flag = 1;
	            }
	            else{
	                prod.codice_prodotto = atoi(controllo);
	                flag = 0;
	            }
	          }while(flag != 0);

	       if(prod.codice_prodotto != -1){

               //programmazione difensiva-controllo categoria
               do{
                  flag = 0;
                  puts("\tCATEGORIA  --> ");
                  puts("\t(1) FOTOLIBRI");
                  puts("\t(2) STAMPE SU TELA");
                  puts("\t(3) STAMPE FOTO");
                  puts("\t(4) CALENDARI");
                  scanf("%s" ,controllo);

                  if(controllo[0] == 0){
                      puts("Codice errato!! Il valore inserito e' alfanumerico, sono validi solo numeri \n\n");
                      flag = 1;
                    }
                     else{
                          categoria = atoi(controllo);

                       switch(categoria){
                       case 1:
                              strcpy(prod.categoria, "fotolibri");
                       break;
                       case 2:
                              strcpy(prod.categoria, "stampe su tela");
                       break;
                       case 3:
                              strcpy(prod.categoria, "stampe foto");
                       break;
                       case 4:
                    	      strcpy(prod.categoria, "calendari");
                       break;
                       default:
                    	      puts("Codice errato!! La risposta inserita non e' compresa tra 1 e 4  \n\n");
                    	      flag = 1;
                     }
                   }
                 }while(flag != 0);

              //programmazione difensiva-controllo che la quantit‚Ä° sia un numero
   	        do{
   	            puts("\n\n\tQUANTITA'   --> " );
   	            scanf("%s",controllo);

   	            if( isdigit(controllo[0]) == 0 ){
   	                puts("Codice errato!! Il valore inserito e' alfanumerico, sono validi solo numeri \n\n");
   	                flag = 1;
   	            }
   	            else{
   	                prod.quantita = atoi(controllo);
   	                flag = 0;
   	            }
   	          }while(flag != 0);

   	        puts("\n\n\tPREZZO   --> ");
   	        scanf("%f" ,&prod.prezzo_pezzo);

   	        puts("\n\n\tSPESE DI SPEDIZIONE   --> ");
   	        scanf("%f" ,&prod.spedizione);

   	        puts("\n\n\tDESCRIZIONE   --> ");
   	        svuotaInput();
   	        fgets(prod.descrizione,LUNGHEZZA_30,stdin);
   	        //programmazione difensiva-prima lettera maiuscola le restanti minuscole

   	 	    prod.descrizione[0] = toupper(prod.descrizione[0]);
   	 	    for(i = 1; i < LUNGHEZZA_30; i++){
   	 		    prod.descrizione[i] = tolower(prod.descrizione[i]);
   	 	    }

   	        do{
   	        	puts("\n\n\tVALUTAZIONE (da 1 a 5)   --> ");
   	        	scanf("%s" ,controllo);

   	        	if(isdigit(controllo[0]) == 0){
   	        		puts("codice errato!! Il valore inserito e' alfanumerico, sono validi solo numeri \n\n");
   	        		flag = 1;
   	        	}
   	        	else{
   	        		flag = 0;
   	        		prod.valutazione = atoi(controllo);

   	        		if( prod.valutazione <1 || prod.valutazione > 5){
   	        			puts("Errore! La scelta deve essere compresa tra 1 e 5\n\n");
   	        			flag = 1;
   	        		}
   	        	}
   	        }while(flag != 0);

   	        puts("\n\n\tCOMMENTI   --> ");
   	        svuotaInput();
   	        fgets(prod.commenti,LUNGHEZZA_30,stdin);
   	        //programmazione difensiva-prima lettera maiuscola le restanti minuscole
   	 	    prod.commenti[0] = toupper(prod.commenti[0]);
   	 	    for(i = 1; i < LUNGHEZZA_30; i++){
   	 		    prod.commenti[i] = tolower(prod.commenti[i]);
   	 	    }
                //sposto il puntatore in base al codice prodotto e salvo su file
		        fseek(file_prodotti,(prod.codice_prodotto-1)*sizeof(prodotto), SEEK_SET);
       		    fwrite(&prod, sizeof(prod), 1, file_prodotti);
	       }
	 }while (prod.codice_prodotto != -1);


	           puts("***************Inserimento Terminato******************\n\n");
}

void stampa_prodotti(FILE *file_prodotti){
	prodotto prod = {0,"",0,0,0,"",0,""};

	rewind(file_prodotti);

	puts("I dati memorizzati nel file prodotti sono i seguenti \n");

	while (!feof(file_prodotti)){
		fread(&prod, sizeof(prodotto), 1, file_prodotti);
		if (!feof(file_prodotti))
            puts("\n");
            puts("******************************************************************************************");
      		printf("%-10s   %-10s\t   %-15s   %-13s   %-10s   %-10s\n\n",
						"Codice",
						"Categoria",
						"Quantita'",
						"Prezzo in €",
						"Spedizione in €",
						"Valutazione -/5");

            printf("%-10hd   %-10s\t    %-15hd   %-10.2f   %-15.2f   %-10hd  ",
						prod.codice_prodotto,
						prod.categoria,
						prod.quantita,
						prod.prezzo_pezzo,
						prod.spedizione,
						prod.valutazione );

            printf("\n\nDescrizione:%s \nCommenti:%s " ,prod.descrizione,prod.commenti);
            puts("******************************************************************************************");
            puts("\n");

	}
	 puts("\t\t\t\t***************File Terminato******************\n\n");
}

void modifica_prodotto(FILE *file_prodotti) {
	prodotto prod = {0,"",0,0,0,"",0,""};
	char controllo[10] = "";
	short int flag = 0, categoria = 0, i = 0;

	do {
		printf("Inserire il codice del prodotto che vuoi modificare (-1 nel codice per terminare) -->");
		do{
		printf("\n\n\tCODICE   --> " );
        scanf("%s",controllo);

        if( (isdigit(controllo[0]) == 0) && (isdigit(controllo[1]) == 0) ){
            puts("Codice errato!! Il valore inserito e' alfanumerico, sono validi solo numeri \n\n");
            flag = 1;
        }
        else{
            prod.codice_prodotto = atoi(controllo);
            flag = 0;
        }
      }while(flag != 0);

		if (prod.codice_prodotto != -1){
			fseek(file_prodotti,(prod.codice_prodotto-1)*sizeof(prodotto), SEEK_SET);
			//questa fread e' necessaria per controllare che il record esista e sia avvalorato
			fread(&prod, sizeof(prodotto), 1, file_prodotti);

			if (!feof(file_prodotti)){
	               //programmazione difensiva-controllo categoria
	               do{
	                  flag = 0;
	                  puts("\tCATEGORIA  --> ");
	                  puts("\t(1) FOTOLIBRI");
	                  puts("\t(2) STAMPE SU TELA");
	                  puts("\t(3) STAMPE FOTO");
	                  puts("\t(4) CALENDARI");
	                  scanf("%s" ,controllo);

	                  if(controllo[0] == 0){
	                      puts("Codice errato!! Il valore inserito e' alfanumerico, sono validi solo numeri \n\n");
	                      flag = 1;
	                    }
	                     else{
	                          categoria = atoi(controllo);

	                       switch(categoria){
	                       case 1:
	                              strcpy(prod.categoria, "fotolibri");
	                       break;
	                       case 2:
	                              strcpy(prod.categoria, "stampe su tela");
	                       break;
	                       case 3:
	                              strcpy(prod.categoria, "stampe foto");
	                       break;
	                       case 4:
	                    	      strcpy(prod.categoria, "calendari");
	                       break;
	                       default:
	                    	      puts("Codice errato!! La risposta inserita non e' compresa tra 1 e 4  \n\n");
	                    	      flag = 1;
	                     }
	                   }
	                 }while(flag != 0);

	              //programmazione difensiva-controllo che la quantit‚Ä° sia un numero
	   	        do{
	   	            puts("\n\n\tQUANTITA'   --> " );
	   	            scanf("%s",controllo);

	   	            if( isdigit(controllo[0]) == 0 ){
	   	                puts("Codice errato!! Il valore inserito e' alfanumerico, sono validi solo numeri \n\n");
	   	                flag = 1;
	   	            }
	   	            else{
	   	                prod.quantita = atoi(controllo);
	   	                flag = 0;
	   	            }
	   	          }while(flag != 0);

	   	        puts("\n\n\tPREZZO   --> ");
	   	        scanf("%f" ,&prod.prezzo_pezzo);

	   	        puts("\n\n\tSPESE DI SPEDIZIONE   --> ");
	   	        scanf("%f" ,&prod.spedizione);

	   	        puts("\n\n\tDESCRIZIONE   --> ");
	   	        svuotaInput();
	   	        fgets(prod.descrizione,LUNGHEZZA_30,stdin);
	   	        //programmazione difensiva-prima lettera maiuscola le restanti minuscole
	   	 	    prod.descrizione[0] = toupper(prod.descrizione[0]);
	   	 	    for(i = 1; i < LUNGHEZZA_30; i++){
	   	 		    prod.descrizione[i] = tolower(prod.descrizione[i]);
	   	 	    }

	   	        do{
	   	        	puts("\n\n\tVALUTAZIONE (da 1 a 5)   --> ");
	   	        	scanf("%s" ,controllo);

	   	        	if(isdigit(controllo[0]) == 0){
	   	        		puts("codice errato!! Il valore inserito e' alfanumerico, sono validi solo numeri \n\n");
	   	        		flag = 1;
	   	        	}
	   	        	else{
	   	        		flag = 0;
	   	        		prod.valutazione = atoi(controllo);

	   	        		if( prod.valutazione <1 || prod.valutazione > 5){
	   	        			puts("Errore! La scelta deve essere compresa tra 1 e 5\n\n");
	   	        			flag = 1;
	   	        		}
	   	        	}
	   	        }while(flag != 0);

	   	        puts("\n\n\tCOMMENTI   --> ");
	   	        svuotaInput();
	   	        fgets(prod.commenti,LUNGHEZZA_30,stdin);
	   	        //programmazione difensiva-prima lettera maiuscola le restanti minuscole
	   	 	    prod.commenti[0] = toupper(prod.commenti[0]);
	   	 	    for(i = 1; i < LUNGHEZZA_30; i++){
	   	 		    prod.commenti[i] = tolower(prod.commenti[i]);
	   	 	    }

	   	 	   //questa fseek e' necessaria perch√ã dopo la fread il puntatore si √ã spostato
				fseek(file_prodotti,(prod.codice_prodotto-1)*sizeof(prodotto), SEEK_SET);
				fwrite(&prod, sizeof(prodotto), 1, file_prodotti);
			}
			else
				puts("Codice non trovato!");
		}
	}while (prod.codice_prodotto != -1);
}

void cancella_prodotto(FILE *file_prodotti){
	prodotto prod, prod_reset ={0,"",0,0,0,"",0,""};
	int codice = 0;
	char controllo[10] = "";
	short int flag = 0;

	do {
		puts("Inserire il codice del prodotto che vuoi cancellare (-1 nel codice per terminare) -->");
        do{
            puts("\n\n\tCODICE PRODOTTO   --> " );
            scanf("%s",controllo);

            if( (isdigit(controllo[0]) == 0) && (isdigit(controllo[1]) == 0) ){
                puts("Codice errato!! Il valore inserito e' alfanumerico, sono validi solo numeri \n\n");
                flag = 1;
            }
            else{
                prod.codice_prodotto = atoi(controllo);
                flag = 0;
            }
          }while(flag != 0);
		if (prod.codice_prodotto != -1){
			fseek(file_prodotti,(prod.codice_prodotto-1)*sizeof(prodotto), SEEK_SET);
			 //questa fread e' necessaria per controllare che il record esista e sia avvalorato
			fread(&prod, sizeof(prodotto), 1, file_prodotti);

			if (!feof(file_prodotti)){
				//mi conservo il codice prima di sovrascriverlo
				codice = prod.codice_prodotto;
				prod = prod_reset;

				//questa fseek e' necessaria perch√ã dopo la fread il puntatore si e' spostato
				fseek(file_prodotti,(codice-1)*sizeof(prodotto), SEEK_SET);
				fwrite(&prod, sizeof(prodotto), 1, file_prodotti);
				puts("Record cancellato");
			}
			else
				puts("Codice non trovato!");
		}
	}while (prod.codice_prodotto!=-1);
}

void ordinamento_prodotti_quantita(FILE *file_prodotti){
  	prodotto prod = {0,"",0,0,0,"",0,""};
    short int i = 0;
    short int codice[MAX_RECORD] = {0};
    short int quantita[MAX_RECORD] = {0};

    //il codice e la quantita' vengono spostati su un vettore di appoggio per effettuare l'ordinamento
    rewind(file_prodotti);
    while(!feof(file_prodotti)){
    	fread(&prod, sizeof(prodotto), 1, file_prodotti);
    	if(!feof(file_prodotti)){
    		codice[i] = prod.codice_prodotto;
    		quantita[i] = prod.quantita;
    		i++;
    	}
    }
    quick_sort(quantita,codice, 0 ,MAX_RECORD-1);
    for(i=0;i<MAX_RECORD;i++){
    	//controllo per evitare di stampare record vuoti
    	if(quantita[i] != 0){
    		prod.codice_prodotto = codice[i];

    		fseek(file_prodotti,(prod.codice_prodotto-1)*sizeof(prodotto), SEEK_SET);
    		fread(&prod, sizeof(prodotto), 1, file_prodotti);

    		puts("\n");
            puts("******************************************************************************************");
      		printf("%-10s   %-10s\t   %-15s   %-13s   %-10s   %-10s\n\n",
						"Codice",
						"Categoria",
						"QUANTITA'",
						"Prezzo in €",
						"Spedizione in €",
						"Valutazione -/5");

            printf("%-10hd   %-10s\t    %-15hd   %-10.2f   %-15.2f   %-10hd  ",
						prod.codice_prodotto,
						prod.categoria,
						prod.quantita,
						prod.prezzo_pezzo,
						prod.spedizione,
						prod.valutazione );

            printf("\n\nDescrizione:%s \nCommenti:%s " ,prod.descrizione,prod.commenti);
            puts("******************************************************************************************");
            puts("\n");
    	}
    }
}

void ordinamento_prodotti_prezzo(FILE *file_prodotti){
  	prodotto prod = {0,"",0,0,0,"",0,""};
    short int i = 0;
    short int codice[MAX_RECORD] = {0};
    float prezzo[MAX_RECORD] = {0};

    //il codice e il prezzo vengono spostati su un vettore di appoggio per effettuare l'ordinamento
    rewind(file_prodotti);
    while(!feof(file_prodotti)){
    	fread(&prod, sizeof(prodotto), 1, file_prodotti);
    	if(!feof(file_prodotti)){
    		codice[i] = prod.codice_prodotto;
    		prezzo[i] = prod.prezzo_pezzo;
    		i++;
    	}
    }
    quick_sort_float(prezzo,codice, 0 ,MAX_RECORD-1);
    for(i=0;i<MAX_RECORD;i++){
    	//controllo per evitare di stampare record vuoti
    	if(prezzo[i] != 0){
    		prod.codice_prodotto = codice[i];

    		fseek(file_prodotti,(prod.codice_prodotto-1)*sizeof(prodotto), SEEK_SET);
    		fread(&prod, sizeof(prodotto), 1, file_prodotti);

            puts("\n******************************************************************************************");
      		printf("%-10s   %-10s\t   %-15s   %-13s   %-10s   %-10s\n\n",
						"Codice",
						"Categoria",
						"Quantita'",
						"PREZZO in €",
						"Spedizione in €",
						"Valutazione -/5");

            printf("%-10hd   %-10s\t    %-15hd   %-10.2f   %-15.2f   %-10hd  ",
						prod.codice_prodotto,
						prod.categoria,
						prod.quantita,
						prod.prezzo_pezzo,
						prod.spedizione,
						prod.valutazione );

            printf("\n\nDescrizione:%s \nCommenti:%s " ,prod.descrizione,prod.commenti);
            puts("******************************************************************************************\n");
    	}
    }
}

void ordinamento_prodotti_spedizione(FILE *file_prodotti){
  	prodotto prod = {0,"",0,0,0,"",0,""};
    short int i = 0;
    short int codice[MAX_RECORD] = {0};
    float spedizione[MAX_RECORD] = {0};

    //il codice e la spedizione vengono spostati su un vettore di appoggio per effettuare l'ordinamento
    rewind(file_prodotti);
    while(!feof(file_prodotti)){
    	fread(&prod, sizeof(prodotto), 1, file_prodotti);
    	if(!feof(file_prodotti)){
    		codice[i] = prod.codice_prodotto;
    		spedizione[i] = prod.spedizione;
    		i++;
    	}
    }
    quick_sort_float(spedizione,codice, 0 ,MAX_RECORD-1);
    for(i=0;i<MAX_RECORD;i++){
    	//controllo per evitare di stampare record vuoti
    	if(spedizione[i] != 0){
    		prod.codice_prodotto = codice[i];

    		fseek(file_prodotti,(prod.codice_prodotto-1)*sizeof(prodotto), SEEK_SET);
    		fread(&prod, sizeof(prodotto), 1, file_prodotti);

            puts("\n******************************************************************************************");
      		printf("%-10s   %-10s\t   %-15s   %-13s   %-10s   %-10s\n\n",
						"Codice",
						"Categoria",
						"Quantita'",
						"Prezzo in €",
						"SPEDIZIONE in €",
						"Valutazione -/5");

            printf("%-10hd   %-10s\t    %-15hd   %-10.2f   %-15.2f   %-10hd  ",
						prod.codice_prodotto,
						prod.categoria,
						prod.quantita,
						prod.prezzo_pezzo,
						prod.spedizione,
						prod.valutazione );

            printf("\n\nDescrizione:%s \nCommenti:%s " ,prod.descrizione,prod.commenti);
            puts("******************************************************************************************\n");
    	}
    }
}

void ordinamento_prodotti_valutazione(FILE *file_prodotti){
  	prodotto prod = {0,"",0,0,0,"",0,""};
    short int i = 0;
    short int codice[MAX_RECORD] = {0};
    short int valutazione[MAX_RECORD] = {0};

    //il codice e la valutazione vengono spostati su un vettore di appoggio per effettuare l'ordinamento
    rewind(file_prodotti);
    while(!feof(file_prodotti)){
    	fread(&prod, sizeof(prodotto), 1, file_prodotti);
    	if(!feof(file_prodotti)){
    		codice[i] = prod.codice_prodotto;
    		valutazione[i] = prod.valutazione;
    		i++;
    	}
    }
    quick_sort(valutazione,codice, 0 ,MAX_RECORD-1);
    for(i=0;i<MAX_RECORD;i++){
    	//controllo per evitare di stampare record vuoti
    	if(valutazione[i] != 0){
    		prod.codice_prodotto = codice[i];

    		fseek(file_prodotti,(prod.codice_prodotto-1)*sizeof(prodotto), SEEK_SET);
    		fread(&prod, sizeof(prodotto), 1, file_prodotti);

            puts("\n******************************************************************************************");
      		printf("%-10s   %-10s\t   %-15s   %-13s   %-10s   %-10s\n\n",
						"Codice",
						"Categoria",
						"Quantita'",
						"Prezzo in €",
						"Spedizione in €",
						"VALUTAZIONE -/5");

            printf("%-10hd   %-10s\t    %-15hd   %-10.2f   %-15.2f   %-10hd  ",
						prod.codice_prodotto,
						prod.categoria,
						prod.quantita,
						prod.prezzo_pezzo,
						prod.spedizione,
						prod.valutazione );

            printf("\n\nDescrizione:%s \nCommenti:%s " ,prod.descrizione,prod.commenti);
            puts("******************************************************************************************\n");
    	}
    }
}

