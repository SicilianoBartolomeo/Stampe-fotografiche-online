 /*
 * Gestione_ordini.c
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

void inserimento_ordine(FILE *file_ordini){
	ordine ord = {0,0,0,0,"",0,""};
	char controllo[10] = "";
	short int flag = 0, stato = 0;

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
                ord.codice_prodotto = atoi(controllo);
                flag = 0;
            }
          }while(flag != 0);

       if(ord.codice_prodotto != -1){

      //programmazione difensiva-controllo codice cliente
           do{
               flag = 0;
               puts("\tCODICE CLIENTE (max 2 cifre)   --> " );
               scanf("%s",controllo);

               if((isdigit(controllo[0]) == 0) && (isdigit(controllo[1]) == 0)){
                   puts("Codice errato!! Il valore inserito e' alfanumerico, sono validi solo numeri \n\n");
                   flag = 1;
                   }
                   else{
                        ord.codice_cliente = atoi(controllo);
                       }
                     }while(flag != 0);

	        		  puts("\tPREZZO   --> " );
	        		  scanf("%f", &ord.prezzo);

                //programmazione difensiva-controllo sullo  stato
                do{
                   flag = 0;
                   puts("\tSTATO  --> ");
                   puts("\t(1) COMPLETATO");
                   puts("\t(2) SPEDITO");
                   puts("\t(3) IN STAMPA");
                   puts("\t(4) ANNULLATO");
                   scanf("%s" ,controllo);

                   if(controllo[0] == 0){
                       puts("Codice errato!! Il valore inserito e' alfanumerico, sono validi solo numeri \n\n");
                       flag = 1;
                     }
                      else{
                           stato = atoi(controllo);

                        switch(stato){
                        case 1:
                               strcpy(ord.stato, "completato");
                        break;
                        case 2:
                               strcpy(ord.stato, "spedito");
                        break;
                        case 3:
                               strcpy(ord.stato, "in stampa");
                        break;
                        case 4:
                        	   strcpy(ord.stato, "annullato");
                        break;
                        default:
                        	flag = 1;
                        	puts("Errore. Lo stato deve essere compreso tra 1 e 4!");
                        break;
                      }
                  }
                }while(flag != 0);

                puts("\tQUANTITA' ORDINATA   ---> ");
                scanf("%hd" ,&ord.quantita);

                puts("\tVALUTAZIONE   ---> ");
                scanf("%hd" ,&ord.valutazione);

                puts("\tCOMMENTI   ---> ");
	   	        svuotaInput();
	   	        fgets(ord.commenti,LUNGHEZZA_30,stdin);

              //il puntatore si sposta in base al codice prodotto e salva le informazionii su file
	           fseek(file_ordini,(ord.codice_prodotto-1)*sizeof(ordine), SEEK_SET);
	   	   	   fwrite(&ord, sizeof(ord), 1, file_ordini);
              }
	          }while (ord.codice_prodotto != -1);


           puts("***************Inserimento Terminato******************\n\n");
}

void stampa_ordini(FILE *file_ordini){
	ordine ord = {0,0,0,0,"",0,""};

	rewind(file_ordini);
	while (!feof(file_ordini)){
		fread(&ord, sizeof(ordine), 1, file_ordini);
		if (!feof(file_ordini))
				printf(" Codice prodotto   Codice cliente  Prezzo in € \t Stato \t\tValutazione-/5 \t Quantita' \t Commenti\n\n");

                printf("\t%-10hd    %-10hd   %-10.2f   %-10s \t  %-10hd \t  %-10hd   %-10s    \n\n",
				ord.codice_prodotto,
				ord.codice_cliente,
				ord.prezzo,
				ord.stato,
				ord.valutazione,
				ord.quantita,
				ord.commenti);
	}

	 puts("\t\t\t\t***************File Terminato******************\n\n");
}

void Realizzazione_ordine(FILE *file_prodotti, FILE *file_clienti, FILE *file_ordini){
	ordine ord = {0,0,0,0,"",0,""};
	prodotto prod = {0,"",0,0,0,"",0,""};
	cliente cli = {0,0};
    short int scelta = 0, flag = 0, i = 0;
    char controllo[LUNGHEZZA_10] = "";

	puts("**********************************************************************");
	puts("**********BENVENUTO NELLA MODALITA' REALIZZAZIONE ORDINE**************");
	puts("**********************************************************************");
	puts("* Il cliente inserisce il proprio codice, la categoria, la quantita' *");
	puts("* del prodotto da acquistare e se vuole puo' lasciare una valutazione*");
	puts("* e un commento.                                                     *");
	puts("*                                                                    *");
	puts("* Il programma calcola il costo totale in base alle informazioni.    *");
	puts("**********************************************************************");
    //programmazione difensiva-controllo che il codice sia un numero
	do{
        puts("\n\n\tCODICE CLIENTE   --> " );
        scanf("%s",controllo);

      if( (isdigit(controllo[0]) == 0) && (isdigit(controllo[1]) == 0) ){
          puts("Codice errato!! Il valore inserito e' alfanumerico, sono validi solo numeri \n\n");
          flag = 1;
      }
      else{
          ord.codice_cliente = atoi(controllo);
          //pongo uguali le due variabili per aggiornare i file in seguito
          cli.codice_cliente = ord.codice_cliente;
          flag = 0;
      }
    }while(flag != 0);

     /*funzione che in base alla categoria inserita restituisce il codice di un prodotto
       con maggiore quantita' appartenente a quella categoria*/
       ord.codice_prodotto = Ricerca_categoria(file_prodotti);
       //pongo uguali le variabili per aggiornare i file in seguito
       prod.codice_prodotto = ord.codice_prodotto;
       cli.codice_prodotto = ord.codice_prodotto;

	   fseek(file_prodotti,(prod.codice_prodotto-1)*sizeof(prodotto), SEEK_SET);
	   fread(&prod, sizeof(prodotto), 1, file_prodotti);

    //programmazione difensiva-controllo che la quantit‚Ä° sia un numero
     do{
         puts("\n\n\tQUANTITA'   --> " );
         scanf("%s",controllo);

         if( isdigit(controllo[0]) == 0 ){
             puts("Codice errato!! Il valore inserito e' alfanumerico, sono validi solo numeri \n\n");
             flag = 1;
         }
         else{
             ord.quantita = atoi(controllo);
             flag = 0;
         }
       }while(flag != 0);

     /*calcolo del costo totale dell'ordine in base alla quantita' inserita,
     al prezzo di spedizione e al prezzo per pezzo*/
     ord.prezzo = (ord.quantita * prod.prezzo_pezzo) + prod.spedizione;

	   do{
		   puts("Vuoi lasciare un commento e una recensione?");
		   puts("\t(1) SI");
		   puts("\t(0) NO");
		   scanf("%s",controllo);
           //programmazione difensiva-controllo sulla valutazione
		    if( isdigit(controllo[0]) == 0 ){
		             puts("Codice errato!! Il valore inserito e' alfanumerico, sono validi solo numeri \n\n");
		             flag = 1;
		         }
		          else{
		                scelta = atoi(controllo);
		                flag = 0;
		                if(scelta == 0 || scelta == 1){
		                if(scelta == 1){
		                do{
		                   puts("\n\n\tVALUTAZIONE (da 1 a 5)   --> ");
		 	   	           scanf("%s" ,controllo);

		                    if(isdigit(controllo[0]) == 0){
		                      		puts("codice errato!! Il valore inserito e' alfanumerico, sono validi solo numeri \n\n");
		                       		flag = 1;
		       		   	        	}
	         		   	        	else{
		                	    		 flag = 0;
		                		    	 ord.valutazione = atoi(controllo);
		                		    	 prod.valutazione = ord.valutazione;

		                		   	      if( ord.valutazione <1 || ord.valutazione > 5){
		                		   	      			puts("Errore! La scelta deve essere compresa tra 1 e 5\n\n");
		                		   	       			flag = 1;
		                		          }
		                		    }
		       	   	        }while(flag != 0);

			   	        puts("\n\n\tCOMMENTI   --> ");
			   	        svuotaInput();
			   	        fgets(prod.commenti,LUNGHEZZA_30,stdin);
			   	        //programmazione difensiva-prima lettera maiuscola le restanti minuscole
			   	 	    ord.commenti[0] = toupper(prod.commenti[0]);
			   	 	    prod.commenti[0] = ord.commenti[0];
			   	 	    for(i = 1; i < LUNGHEZZA_30; i++){
			   	 		    ord.commenti[i] = tolower(prod.commenti[i]);
			   	 		    prod.commenti[i] = ord.commenti[i];
			   	 	    }
		              }
		          }
		                else{
		                	flag = 1;
		                	puts("ERRORE! La scelta inserita non e' compresa tra 0 e 1");
		                }
		            }
	   }while(flag != 0);

	   strcpy(ord.stato,"in gestione");

	   puts("*******************************************************************************");
	   printf("Il cliente codice: %hd  ha ordinato il prodotto codice: %hd" ,ord.codice_cliente,ord.codice_prodotto);
	   printf("\nCopie ordinate: %hd \t Importo totale: %.2f € \n" ,ord.quantita,ord.prezzo);
	   puts("*******************************************************************************");

	   puts("\n\n\n\t************************ORDINE COMPLETATO************************");
	   puts("\t*************IL LABORATORIO GESTIRA' IL VOSTRO ORDINE************\n\n");

	   //aggiorno le informazioni sui file
	   fseek(file_ordini,(ord.codice_prodotto-1)*sizeof(ordine), SEEK_SET);
	   fwrite(&ord, sizeof(ord), 1, file_ordini);

	   fseek(file_prodotti,(prod.codice_prodotto-1)*sizeof(prodotto), SEEK_SET);
	   fwrite(&prod, sizeof(prodotto), 1, file_prodotti);

	   fseek(file_clienti,(cli.codice_cliente-1)*sizeof(cliente), SEEK_SET);
	   fwrite(&cli, sizeof(cliente), 1, file_clienti);
}

void Gestione_ordini(FILE *file_prodotti, FILE* file_ordini){
	ordine ord = {0,0,0,0,"",0,""};
	prodotto prod = {0,"",0,0,0,"",0,""};
	char stato[LUNGHEZZA_20] = "in gestione";
	short int flag = 0, opzione = 0;
	char controllo[LUNGHEZZA_10] = "";

	puts("\t********************************************************************");
	puts("\t*************BENVENUTO NELLA MODALITA' GESTIONE ORDINI**************");
	puts("\t********************************************************************");
	puts("\t* Se la quantita' del prodotto ordinato e' sufficiente in magazzino*");
	puts("\t*  il sistema mandera' tale ordine in spedizione;                  *");
	puts("\t*                                                                  *");
	puts("\t*  Altrimenti l' utente puo' scegliere di:                         *");
	puts("\t*       -mandare in stampa le copie mancanti                       *");
	puts("\t*       -eventualmente annullare l'ordine                          *");
	puts("\t********************************************************************\n");
	//procedura che stampa gli ordini il cui stato e' "in gestione"
	stampa_ordini_gestione(file_ordini);

	rewind(file_ordini);
	while(!feof(file_ordini)){
		fread(&ord, sizeof(ordine), 1, file_ordini);
		if(!feof(file_ordini)){
            //ricerca deglli ordini il cui stato √ã "in gestione"
			if( (strcmp(ord.stato,stato)) == 0){
				prod.codice_prodotto = ord.codice_prodotto;
				fseek(file_prodotti,(prod.codice_prodotto-1)*sizeof(prodotto), SEEK_SET);
				fread(&prod, sizeof(prodotto), 1, file_prodotti);

				if(ord.quantita <= prod.quantita){
					printf("\n\t\t************L'ordine codice: %hd e' stato spedito************",ord.codice_prodotto);
					strcpy(ord.stato,"spedito");
					//aggiorno la quantit‚Ä° dei prodotti in base a quella ordinata
					prod.quantita = prod.quantita - ord.quantita;
				}
				else{
					printf("\n\n\tERRORE! La quantita' del prodotto codide: %d in magazzino non e' sufficiente",prod.codice_prodotto);

					do{
					   flag = 0;
					   puts("\n\nScegli l'operazione da effettuare: ");
					   puts("\t(1) Mandare in stampa");
					   puts("\t(0) Annullare l'ordine");
					   scanf("%s" ,controllo);

		               if(controllo[0] == 0){
		                   puts("Codice errato!! Il valore inserito e' alfanumerico, sono validi solo numeri \n\n");
		                   flag = 1;
		                 }
		               else{
		            	   opzione = atoi(controllo);
		            	   switch (opzione){
		            	   case (1):
		            			   puts("\t\t***********L'ORDINE E' STATO MANDATO IN STAMPA************");
		            	           strcpy(ord.stato,"in stampa");
		          				   prod.quantita = prod.quantita - ord.quantita;
		            	   break;
		            	   case (0):
		            			   puts("\t\t*************L'ORDINE E' STATO ANNULLATO*****************");
		            	           strcpy(ord.stato,"annullato");
		            	   break;
		            	   default:
	                    	      puts("Codice errato!! La risposta inserita non e' compresa tra 0 e 1  \n\n");
	                    	      flag = 1;
		            	   }
		               }
					}while(flag != 0);
				}

				//aggiorno le modifiche sui file
				 fseek(file_ordini,(ord.codice_prodotto-1)*sizeof(ordine), SEEK_SET);
			     fwrite(&ord, sizeof(ord), 1, file_ordini);

			     fseek(file_prodotti,(prod.codice_prodotto-1)*sizeof(prodotto), SEEK_SET);
			     fwrite(&prod, sizeof(prodotto), 1, file_prodotti);
			}
		}
	}
}

void stampa_ordini_gestione(FILE *file_ordini){
	ordine ord = {0,0,0,0,"",0,""};
	char stato[LUNGHEZZA_20] = "in gestione";

	puts("*****************************ORDINI DA GESTIRE*****************************");
	rewind(file_ordini);
	while(!feof(file_ordini)){
		fread(&ord, sizeof(ordine), 1, file_ordini);
		if(!feof(file_ordini)){
			//ricerca  e stampa i record degli ordini il cui stato e' "in gestione"
			if( (strcmp(ord.stato,stato)) == 0){
				printf("\n\nCodice prodotto: %hd\tCodice cliente: %hd",ord.codice_prodotto,ord.codice_cliente);
				printf("\tCosto totale: %.2f\tValutazione: %hd\tCommenti: %s",ord.prezzo,ord.valutazione,ord.commenti);
				printf("\tQuantita' ordinata: %hd" ,ord.quantita);
			}
		}
	}
}

short int Ricerca_categoria(FILE *file_prodotti){
	  prodotto prod = {0,"",0,0,0,"",0,""};
	  char controllo[LUNGHEZZA_10] = "";
	  char categoria[LUNGHEZZA_20] = "";
	  short int codice[MAX_RECORD] = {0};
	  short int quantita[MAX_RECORD] = {0};
	  short int scelta = 0, flag = 0, i = 0, codice_max = 0, pos = -1;

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
	               scelta = atoi(controllo);

	                       switch(scelta){
	                       case 1:
	                              strcpy(categoria, "fotolibri");
	                       break;
	                       case 2:
	                              strcpy(categoria, "stampe su tela");
	                       break;
	                       case 3:
	                              strcpy(categoria, "stampe foto");
	                       break;
	                       case 4:
	                    	      strcpy(categoria, "calendari");
	                       break;
	                       default:
	                    	      puts("Codice errato!! La risposta inserita non e' compresa tra 1 e 4  \n\n");
	                     }

	  rewind(file_prodotti);
	  while( (i<MAX_RECORD) && (pos < 0) ){
		      while (!feof(file_prodotti) ){
			         fread(&prod, sizeof(prodotto), 1, file_prodotti);
			         if (!feof(file_prodotti) )
                    //ricerca i prodotti su file in base alla categoria inserita
	                if(strcmp(categoria, prod.categoria) == 0 ){

	                //ricerca i prodotti con maggior quantit‚
	                if(prod.quantita>=quantita[i] && prod.codice_prodotto!=codice[i]
	                && prod.codice_prodotto!=codice[i-1] && prod.codice_prodotto!=codice[i-9]){
	                   quantita[i]=prod.quantita;
	                   codice[i]=prod.codice_prodotto;
	                   pos=i;
	               }
	             }
	           }
		      i++;
	         }
	       }
	     }while(flag != 0);

	   codice_max = codice [pos];
	   return codice_max;
}

void Ricerca_codice_prodotto(FILE *file_ordini){
      ordine ord = {0,0,0,0,"",0,""};
	  char controllo[LUNGHEZZA_10] = "";
	  short int flag = 0;

      do{
          puts("\n\n\tCODICE PRODOTTO   --> " );
          scanf("%s",controllo);

          if( (isdigit(controllo[0]) == 0) && (isdigit(controllo[1]) == 0) ){
              puts("Codice errato!! Il valore inserito e' alfanumerico, sono validi solo numeri \n\n");
              flag = 1;
          }
          else{
              ord.codice_prodotto = atoi(controllo);
              flag = 0;
          }

       //sposta il puntatore in base al codice da cercare e ne stampa le informazioni
	   fseek(file_ordini,(ord.codice_prodotto-1)*sizeof(ordine), SEEK_SET);
	   fread(&ord, sizeof(ordine), 1, file_ordini);

	   if(ord.codice_cliente != 0){
		    puts("**********************************************************************************************************************************");
			printf(" Codice prodotto: %hd\tCodice cliente: %hd",ord.codice_prodotto,ord.codice_cliente);
			printf("\tCosto totale: %.2f €\tValutazione: %hd / 5\tCommenti: %s",ord.prezzo,ord.valutazione,ord.commenti);
			printf("\tStato: %s\tQuantita' acquistata: %hd \n " ,ord.stato,ord.quantita);
			puts("**********************************************************************************************************************************");
	   }
	   else{
		   puts("ERRORE! Non ci sono ordini aventi questo codice prodotto");
		   flag = 1;
	   }
      }while(flag != 0);
}

void Ricerca_codice_cliente(FILE *file_ordini){
    ordine ord = {0,0,0,0,"",0,""};

    do{
    	//ricerca del codice prodotto in base al codice cliente inserito e ne stampa le informazioni
    	ord.codice_prodotto = RicercaCodiceCliente(file_ordini);
    	if(ord.codice_prodotto != 0){
    	    fseek(file_ordini,(ord.codice_prodotto-1)*sizeof(ordine), SEEK_SET);
    	    fread(&ord, sizeof(ordine), 1, file_ordini);

    	    puts("**********************************************************************************************************************************");
    	    printf("Codice prodotto: %hd\tCodice cliente: %hd",ord.codice_prodotto,ord.codice_cliente);
    	  	printf("\tCosto totale: %.2f €\tValutazione: %hd / 5\tCommenti: %s",ord.prezzo,ord.valutazione,ord.commenti);
    	  	printf("\tStato: %s\tQuantita' acquistata: %hd \n" ,ord.stato,ord.quantita);
    	  	puts("**********************************************************************************************************************************");
    	}
    	else{
    		puts("ERRORE! Il codice cliente inserito non appartiene a nessun ordine");
    	}
    }while(ord.codice_prodotto == 0);
}

short int RicercaCodiceCliente(FILE *file_ordini){
      ordine ord = {0,0,0,0,"",0,""};
	  char controllo[LUNGHEZZA_10] = "";
	  short int flag = 0, i = 0, codice_cliente = 0, codice_prodotto = 0;

	  do{
		  flag = 0;
          puts("\n\n\tCODICE CLIENTE   --> " );
          scanf("%s",controllo);

          if( (isdigit(controllo[0]) == 0) && (isdigit(controllo[1]) == 0) ){
              puts("Codice errato!! Il valore inserito e' alfanumerico, sono validi solo numeri \n\n");
              flag = 1;
          }
          else{
        	  codice_cliente = atoi(controllo);
        	  rewind(file_ordini);
             //ricerca lineare con sentinella
        	  while( (i<MAX_RECORD) && codice_prodotto == 0){
        		      while (!feof(file_ordini) ){
        			         fread(&ord, sizeof(ordine), 1, file_ordini);
        			         if (!feof(file_ordini) ){

        	                if( codice_cliente == ord.codice_cliente ){
        	                	codice_prodotto = ord.codice_prodotto;
        	             }
        	         }
                 }
        		i++;
   	         }
          }
	  }while(flag != 0);
	  return codice_prodotto;
}

void ordinamento_ordini_valutazione(FILE *file_ordini){
    ordine ord = {0,0,0,0,"",0,""};
    short int i = 0;
    short int codice[MAX_RECORD] = {0};
    short int valutazione[MAX_RECORD] = {0};

    //il codice e la quantita' vengono spostati su un vettore di appoggio per effettuare l'ordinamento
    rewind(file_ordini);
    while(!feof(file_ordini)){
    	fread(&ord, sizeof(ordine), 1, file_ordini);
    	if(!feof(file_ordini)){
    		codice[i] = ord.codice_prodotto;
    		valutazione[i] = ord.valutazione;
    		i++;
    	}
    }
    quick_sort(valutazione,codice, 0 ,MAX_RECORD-1);
    for(i=0;i<MAX_RECORD;i++){
    	//controllo per evitare di stampare record vuoti
    	if(valutazione[i] != 0){
    		ord.codice_prodotto = codice[i];

    		fseek(file_ordini,(ord.codice_prodotto-1)*sizeof(ordine), SEEK_SET);
    		fread(&ord, sizeof(ordine), 1, file_ordini);

			printf("%-10s   %-10s   %-10s   %-10s   %-10s   %-10s   %-10s  \n\n",
			"Codice prodotto",
			"Codice cliente",
			"Prezzo in €",
			"Stato",
			"VALUTAZIONE -/5",
			"Quantita'",
			"Commenti");

            printf("\t%-10hd    %-10hd   %-10.2f   %-10s \t  %-10hd \t  %-10hd   %-10s    \n\n",
			ord.codice_prodotto,
			ord.codice_cliente,
			ord.prezzo,
			ord.stato,
			ord.valutazione,
			ord.quantita,
			ord.commenti);
    	}
    }
}

void ordinamento_ordini_quantita(FILE *file_ordini){
    ordine ord = {0,0,0,0,"",0,""};
    short int i = 0;
    short int codice[MAX_RECORD] = {0};
    short int quantita[MAX_RECORD] = {0};

    //il codice e la quantit‚ vengono spostati su un vettore di appoggio per effettuare l'ordinamento
    rewind(file_ordini);
    while(!feof(file_ordini)){
    	fread(&ord, sizeof(ordine), 1, file_ordini);
    	if(!feof(file_ordini)){
    		codice[i] = ord.codice_prodotto;
    		quantita[i] = ord.quantita;
    		i++;
    	}
    }
    quick_sort(quantita,codice, 0 ,MAX_RECORD-1);
    for(i=0;i<MAX_RECORD;i++){
    	//controllo per evitare di stampare record vuoti
    	if(quantita[i] != 0){
    		ord.codice_prodotto = codice[i];

    		fseek(file_ordini,(ord.codice_prodotto-1)*sizeof(ordine), SEEK_SET);
    		fread(&ord, sizeof(ordine), 1, file_ordini);

			printf("%-10s   %-10s   %-10s   %-10s   %-10s   %-10s   %-10s  \n\n",
			"Codice prodotto",
			"Codice cliente",
			"Prezzo in €",
			"Stato",
			"Valutazione -/5",
			"QUANTITA'",
			"Commenti");

            printf("\t%-10hd    %-10hd   %-10.2f   %-10s \t  %-10hd \t  %-10hd   %-10s    \n\n",
			ord.codice_prodotto,
			ord.codice_cliente,
			ord.prezzo,
			ord.stato,
			ord.valutazione,
			ord.quantita,
			ord.commenti);
    }
  }
}

void ordinamento_ordini_prezzo(FILE *file_ordini){
    ordine ord = {0,0,0,0,"",0,""};
    short int i = 0;
    short int codice[MAX_RECORD] = {0};
    float prezzo[MAX_RECORD] = {0};

    //il codice e la quantit‚Ä° vengono spostati su un vettore di appoggio per effettuare l'ordinamento
    rewind(file_ordini);
    while(!feof(file_ordini)){
    	fread(&ord, sizeof(ordine), 1, file_ordini);
    	if(!feof(file_ordini)){
    		codice[i] = ord.codice_prodotto;
    		prezzo[i] = ord.prezzo;
    		i++;
    	}
    }
    quick_sort_float(prezzo,codice, 0 ,MAX_RECORD-1);
    for(i=0;i<MAX_RECORD;i++){
    	//controllo per evitare di stampare record vuoti
    	if(prezzo[i] != 0){
    		ord.codice_prodotto = codice[i];

    		fseek(file_ordini,(ord.codice_prodotto-1)*sizeof(ordine), SEEK_SET);
    		fread(&ord, sizeof(ordine), 1, file_ordini);

			printf("%-10s   %-10s   %-10s   %-10s   %-10s   %-10s   %-10s  \n\n",
			"Codice prodotto",
			"Codice cliente",
			"PREZZO in €",
			"Stato",
			"Valutazione -/5",
			"Quantita'",
			"Commenti");

            printf("\t%-10hd    %-10hd   %-10.2f   %-10s \t  %-10hd \t  %-10hd   %-10s    \n\n",
			ord.codice_prodotto,
			ord.codice_cliente,
			ord.prezzo,
			ord.stato,
			ord.valutazione,
			ord.quantita,
			ord.commenti);
    	}
    }
}

void quick_sort(short int v[], short int s[], int l, int r){
	int i = 0;

	if(r > l){
		i = partizione(v, s, l, r);

		// richiama il quick sort ricorsivamente sulle partizioni
		quick_sort(v, s, l, i - 1);
		quick_sort(v, s, i + 1, r);
	}
}

int partizione( short int v[], short int s[], int l, int r){
    int x = 0, i = 0, j = 0, temp = 0, p = 0;

	p = (l + r) / 2;

	x = v[p];
	i = l-1;
	j = r + 1;

	while (i < j) {

		while(v[ --j ] > x);
		while(v[ ++i ] < x);
		if (i < j) {
			temp = v[i];
			v[i] = v[j];
			v[j] = temp;

			temp = 0;

			temp = s[i];
			s[i] = s[j];
			s[j] = temp;
		}
	}
	return j;
}

void quick_sort_float(float v[], short int s[], int l, int r){
	int i = 0;

	if(r >= l){
		i = partizione_float(v, s, l, r);

		// richiama il quick sort ricorsivamente sulle partizioni
		quick_sort_float(v, s, l, i - 1);
		quick_sort_float(v, s, i + 1, r);
	}
}

int partizione_float( float v[], short int s[], int l, int r){
    int x = 0, i = 0, j = 0, temp = 0, p = 0;

	p = (l + r) / 2;

	x = v[p];
	i = l-1;
	j = r + 1;

	while (i < j) {

		while(v[ --j ] > x);
		while(v[ ++i ] < x);
		if (i < j) {
			temp = v[i];
			v[i] = v[j];
			v[j] = temp;

			temp = 0;

			temp = s[i];
			s[i] = s[j];
			s[j] = temp;
		}
	}
	return j;
}

