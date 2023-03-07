/*
 * Appello1Settembre.c
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
#include "Gestione_prodotti.h"
#include "Gestione_clienti.h"

int main(){
	FILE *file_prodotti = NULL;
	FILE *file_clienti = NULL;
	FILE *file_ordini = NULL;
	system("pause");

	file_prodotti = fopen("Prodotti.csv","rb+");
	file_clienti = fopen("Clienti.csv","rb+");
	file_ordini = fopen("Ordini.csv","rb+");

	//programmazione difensiva-controllo che i file siano aperti correttamente
	if(file_prodotti == NULL)
		puts("ERRORE! Il file Prodotti.csv non Ë stato aperto correttamente");
	else{
		if(file_clienti == NULL)
			puts("ERRORE! Il file Clienti.csv non Ë stato aperto correttamente");
		else{
			if(file_ordini == NULL)
				puts("ERRORE! Il file Ordini.csv non Ë stato aperto correttamente");
			else{
				puts("\n\n\t*****************************************************************");
				puts("\t*Il programma si occupa della gestione di una piattaforma online*");
				puts("\t*****************************************************************");

				menu_principale(file_prodotti, file_clienti, file_ordini);
			}
		}
	}

	if( (!fclose(file_prodotti)) && (!fclose(file_clienti)) && (!fclose(file_ordini)) ){
		puts("\n\nFile chiusi correttamente");
	}
	else{
		puts("\n\nErrore durante la chiusura dei file");
	}


	return 0;
}

void menu_principale(FILE *file_prodotti, FILE *file_clienti, FILE *file_ordini){
	short int scelta = 0;
	char controllo[10] = "";

	do{
		puts("\n\n\t****************************************************************");
		puts("\t*      SCEGLIERE LA MODALITA' CON CUI ENTRARE NEL PROGRAMMA    *");
		puts("\t****************************************************************");

		puts("\t*\t\t(1) Modalita' amministratore di laboratorio    *");
		puts("\t*\t\t(2) Modalita' cliente                          *");
		puts("\t*\t\t(3) Esci dal programma                         *");
		puts("\t****************************************************************");
		scanf("%s" ,controllo);

		if(isdigit(controllo[0]) == 0){

			printf("Codice errato!! La risposta inserita e' alfanumerica, sono validi solo numeri \n\n");

			scelta = 0;
		}
		else{
			//conversione in intero di scelta
			scelta = atoi(controllo);

			switch (scelta){
			case (1):
					menu_laboratorio(file_prodotti, file_clienti, file_ordini);
			break;
			case (2):
					menu_cliente(file_prodotti, file_clienti, file_ordini);
			break;
			case (3):
					puts("\t**********Grazie per aver usato il nostro programma**********");
			break;
			default:
				puts("Codice errato!! La risposta inserita non Ë compresa tra 1 e 3  \n\n");
				scelta = 0;
			break;
			}
		}

	}while(scelta == 0 || scelta != MAX_SCELTA_MENU);
}

void menu_laboratorio(FILE *file_prodotti, FILE *file_clienti, FILE *file_ordini){
	short int opzione = 0;
	char controllo[10] = "";
	char password_amministratore[12] = "laboratorio";
	char password[12] = "";

		//inserimento password per entrare in modalita' amministratore di laboratorio
		//la password e' "laboratorio"
		puts("\n\n");
		puts("Hai selezionato di accedere come amministratore, inserire la password per visualizzare il menu amministratore\n");
		scanf("%s" ,password);
		if( (strcmp(password,password_amministratore)) == 0){

	puts("****************************************************************");
	puts("****BENVENUTO NELLA MODALITA' AMMINISTRATORE DI LABORATORIO*****");
	puts("****************************************************************");

	do{
		puts("\n\n");
		puts("\tScegli il tipo di operazione che vuoi effettuare:  ");
		puts("\t\t(1) Aggiunta-Modifica-Cancellazioni prodotti");
		puts("\t\t(2) Aggiunta-Modifica-Cancellazione clienti");
		puts("\t\t(3) Gestione ordini e statistiche");
		puts("\t\t(4) Ricerca ordini");
		puts("\t\t(5) Stampa lista ordinata dei prodotti");
		puts("\t\t(6) Stampa lista ordinata degli ordini");
		puts("\t\t(7) Ritorna al menu' iniziale");
		scanf("%s" ,controllo);

		if(isdigit(controllo[0]) == 0){

			printf("Codice errato!! La risposta inserita e' alfanumerica, sono validi solo numeri \n\n");
			opzione = 0;

		}
		else{
			//conversione in intero di scelta
			opzione = atoi(controllo);

					switch (opzione){
					case (1):
		                    Aggiunta_modifica_cancellazione_prodotti(file_prodotti);
					break;
					case (2):
				            Aggiunta_modifica_cancellazione_clienti(file_clienti);
					break;
					case (3):
                            Menu_gestione_ordini(file_prodotti, file_prodotti, file_ordini);
					break;
					case (4):
							Menu_ricerca_ordini(file_ordini);
					break;
					case (5):
							Menu_ordinamento_prodotti(file_prodotti);
					break;
					case (6):
							Menu_ordinamento_ordini(file_ordini);
					break;
					case(7):
					break;
					default:
						    puts("Codice errato!! La risposta inserita non e' compresa tra 1 e 7  \n\n");
							opzione = 0;
					break;
					}
				}
	       }while(opzione == 0 || opzione != MAX_SCELTA_MENU_LAB);
	}
	else{
		puts("ERRORE!!! Password inserita errata!");
	}
}


void menu_cliente(FILE *file_prodotti, FILE *file_clienti, FILE *file_ordini){
	short int opzione = 0;
	char controllo[10] = "";

	puts("****************************************************************");
	puts("***************BENVENUTO NELLA MODALITA' CLIENTE****************");
	puts("****************************************************************");

	do{
		puts("\n\n");
		puts("\tScegli il tipo di operazione che vuoi effettuare:  ");
		puts("\t\t(1) Realizzazione ordini");
		puts("\t\t(2) Ricerca ordini");
		puts("\t\t(3) Ritorna al menu' iniziale");
		scanf("%s" ,controllo);

		if(isdigit(controllo[0]) == 0){

			printf("Codice errato!! La risposta inserita e' alfanumerica, sono validi solo numeri \n\n");
			opzione = 0;

		}
		else{
			//conversione in intero di scelta
			opzione = atoi(controllo);

					switch (opzione){
					case (1):
		                    Realizzazione_ordine(file_prodotti, file_clienti, file_ordini);
		                   stampa_prodotti(file_prodotti);
		                   stampa_ordini(file_ordini);
		                   stampa_clienti(file_clienti);
					break;
					case (2):
				            Menu_ricerca_ordini(file_ordini);
					break;
					case (3):
					break;
					default:
						    puts("Codice errato!! La risposta inserita non e' compresa tra 1 e 3  \n\n");
							opzione = 0;
					break;
					}
				}
	       }while(opzione == 0 || opzione != MAX_SCELTA_MENU);
}


void Aggiunta_modifica_cancellazione_prodotti(FILE *file_prodotti){
	short int opzione = 0;
	char controllo[10] = "";

	do{
		puts("\n\n");
		puts("\tScegli il tipo di operazione che vuoi effettuare:   ");
		puts("\t\t(1) Aggiunta prodotti");
		puts("\t\t(2) Modifica prodotti");
		puts("\t\t(3) Cancellazione prodotti");
		puts("\t\t(4) Ritorna al menu' precedente");
		scanf("%s" ,controllo);

		if(isdigit(controllo[0]) == 0){

			printf("Codice errato!! La risposta inserita e' alfanumerica, sono validi solo numeri \n\n");
			opzione = 0;

		}
		else{
			//conversione in intero di scelta
			opzione = atoi(controllo);

					switch (opzione){
					case (1):
				            puts("\n********************************Inserimento Prodotti***************************************\n");
				            puts("\nVengono inseriti i campi: \n");
				            puts("codice prodotto, categoria, quantita', prezzo per pezzo, costo spedizione, descrizione, valutazione e commenti \n");
			    	        inserimento_prodotto(file_prodotti);
			    	        stampa_prodotti(file_prodotti);
					break;
					case (2):
				            puts("***************************Modifica Prodotti***************************\n");
				            puts("Viene inserito il codice e in base a questo viene modificato il prodotto \n");
				            puts("Se il codice non esiste, viene visualizzato un messaggio d'errore\n");
				            modifica_prodotto(file_prodotti);
				            stampa_prodotti(file_prodotti);
					break;
					case (3):
				            puts("******************************Cancella Prodotti******************************\n");
				            puts("Viene inserito il codice e viene cancellato il record associato\n");
				            puts("Se il codice non esiste, viene visualizzato un messaggio d'errore.\n\n\n");
				            cancella_prodotto(file_prodotti);
				            stampa_prodotti(file_prodotti);
					break;
					case (4):
					break;
					default:
						    puts("Codice errato!! La risposta inserita non e' compresa tra 1 e 4  \n\n");
							opzione = 0;
					break;
					}
				}

	       }while(opzione == 0 || opzione != SCELTA_MENU_PRECEDENTE);

}


void Aggiunta_modifica_cancellazione_clienti(FILE *file_clienti){
	short int opzione = 0;
	char controllo[10] = "";

	do{
		puts("\n\n");
		puts("\tScegli il tipo di operazione che vuoi effettuare:   ");
		puts("\t\t(1) Aggiunta clienti");
		puts("\t\t(2) Modifica clienti");
		puts("\t\t(3) Cancellazione clienti");
		puts("\t\t(4) Ritorna al menu precedente");
		scanf("%s" ,controllo);

		if(isdigit(controllo[0]) == 0){

			printf("Codice errato!! La risposta inserita e' alfanumerica, sono validi solo numeri \n\n");
			opzione = 0;

		}
		else{
			//conversione in intero di scelta
			opzione = atoi(controllo);

					switch (opzione){
					case (1):
				            puts("\n********************************Inserimento Clienti***************************************\n");
				            puts("\nVengono inseriti i campi: \n");
				            puts("codice cliente, codice prodotti ordinati \n");
			    	        inserimento_cliente(file_clienti);
			    	        stampa_clienti(file_clienti);
					break;
					case (2):
				            puts("***************************Modifica Clienti***************************\n");
				            puts("Viene inserito il codice e in base a questo viene modificato il cliente \n");
				            puts("Se il codice non esiste, viene visualizzato un messaggio d'errore\n");
				            modifica_cliente(file_clienti);
				            stampa_clienti(file_clienti);
					break;
					case (3):
				            puts("******************************Cancella Clienti******************************\n");
				            puts("Viene inserito il codice e viene cancellato il record associato\n");
				            puts("Se il codice non esiste, viene visualizzato un messaggio d'errore.\n\n\n");
				            cancella_cliente(file_clienti);
				            stampa_clienti(file_clienti);
					break;
					case (4):
					break;
					default:
					    puts("Codice errato!! La risposta inserita non e' compresa tra 1 e 4  \n\n");
						opzione = 0;
					break;
					}
				}

	       }while(opzione == 0 || opzione != SCELTA_MENU_PRECEDENTE);

}


void Menu_ricerca_ordini(FILE *file_ordini){
	short int opzione = 0;
	char controllo[LUNGHEZZA_10] = "";

	puts("****************************************************************");
	puts("***************BENVENUTO NEL MENU' RICERCA ORDINI***************");
	puts("****************************************************************");

	do{
		puts("\n\n");
		puts("\tScegli il tipo di ricerca che vuoi effettuare:   ");
		puts("\t\t(1) Ricerca per codice prodotto");
		puts("\t\t(2) Ricerca per codice cliente");
		puts("\t\t(3) Stampa tutta la lista degli ordini");
		puts("\t\t(4) Ritorna al menu precedente");
		scanf("%s" ,controllo);

		if(isdigit(controllo[0]) == 0){

			printf("Codice errato!! La risposta inserita e' alfanumerica, sono validi solo numeri \n\n");
			opzione = 0;

		}
		else{
			opzione = atoi(controllo);

			switch (opzione){
			case (1):
					puts("******************************Ricerca per codice prodotto******************************\n");
			        puts("L'utente inserisce il codice prodotto, il sistema stampa i dati relativi a quell'ordine");
			        Ricerca_codice_prodotto(file_ordini);
			break;
			case (2):
					puts("******************************Ricerca per codice cliente******************************\n");
			        puts("L'utente inserisce il codice cliente, il sistema stampa i dati relativi a quell'ordine");
			        Ricerca_codice_cliente(file_ordini);
			break;
			case (3):
					puts("*********************************Lista ordini effettuati*********************************\n");
			        stampa_ordini(file_ordini);
			break;
			case (4):
		    break;
			default:
			       puts("Codice errato!! La risposta inserita non e' compresa tra 1 e 4  \n\n");
				   opzione = 0;
			break;
			}
		}
	}while(opzione == 0 || opzione != SCELTA_MENU_PRECEDENTE);
}


void Menu_ordinamento_prodotti(FILE *file_prodotti){
	short int opzione = 0;
	char controllo[LUNGHEZZA_10] = "";

	puts("****************************************************************");
	puts("************BENVENUTO NEL MENU' ORDINAMENTO PRODOTTI************");
	puts("*******IL PROGRAMMA STAMPA UNA LISTA ORDINATA DEI PRODOTTI******");
	puts("***************IN BASE ALLA SCELTA DELL'UTENTE******************");
	puts("****************************************************************");

	do{
		puts("\n\n");
		puts("\tScegli il tipo di ordinamento che vuoi effettuare:   ");
		puts("\t\t(1) Ordina per valutazione");
		puts("\t\t(2) Ordina per quantita'");
		puts("\t\t(3) Ordina per prezzo per pezzo");
		puts("\t\t(4) Ordina per spese di spedizione");
		puts("\t\t(5) Ritorna al menu precedente");
		scanf("%s" ,controllo);

		if(isdigit(controllo[0]) == 0){

			printf("Codice errato!! La risposta inserita e' alfanumerica, sono validi solo numeri \n\n");
			opzione = 0;

		}
		else{
			opzione = atoi(controllo);

			switch (opzione){
			case (1):
					puts("******************************Ordinamento per valutazione******************************\n");
			        ordinamento_prodotti_valutazione(file_prodotti);
			break;
			case (2):
					puts("********************************Ordinamento per quantita'********************************\n");
			        ordinamento_prodotti_quantita(file_prodotti);
			break;
			case (3):
		            puts("*****************************Ordinamento per prezzo per pezzo*****************************\n");
		            ordinamento_prodotti_prezzo(file_prodotti);
		    break;
			case (4):
					puts("****************************Ordinamento per spese di spedizione****************************\n");
			        ordinamento_prodotti_spedizione(file_prodotti);
			break;
			case (5):
		    break;
			default:
			       puts("Codice errato!! La risposta inserita non e' compresa tra 1 e 5  \n\n");
				   opzione = 0;
			break;
			}
		}
	}while(opzione == 0 || opzione != SCELTA_MENU_RICERCA);
}


void Menu_ordinamento_ordini(FILE *file_ordini){
	short int opzione = 0;
	char controllo[LUNGHEZZA_10] = "";

	puts("****************************************************************");
	puts("************BENVENUTO NEL MENU' ORDINAMENTO ORDINI**************");
	puts("*******IL PROGRAMMA STAMPA UNA LISTA ORDINATA DEGLI ORDINI******");
	puts("***************IN BASE ALLA SCELTA DELL'UTENTE******************");
	puts("****************************************************************");

	do{
		puts("\n\n");
		puts("\tScegli il tipo di ordinamento che vuoi effettuare:   ");
		puts("\t\t(1) Ordina per valutazione");
		puts("\t\t(2) Ordina per quantita'");
		puts("\t\t(3) Ordina per prezzo totale");
		puts("\t\t(4) Ritorna al menu precedente");
		scanf("%s" ,controllo);

		if(isdigit(controllo[0]) == 0){

			printf("Codice errato!! La risposta inserita e' alfanumerica, sono validi solo numeri \n\n");
			opzione = 0;

		}
		else{
			opzione = atoi(controllo);

			switch (opzione){
			case (1):
					puts("******************************Ordinamento per valutazione******************************\n");
			        ordinamento_ordini_valutazione(file_ordini);
			break;
			case (2):
					puts("********************************Ordinamento per quantita'********************************\n");
			        ordinamento_ordini_quantita(file_ordini);
			break;
			case (3):
		            puts("*****************************Ordinamento per prezzo totale*****************************\n");
		            ordinamento_ordini_prezzo(file_ordini);
		    break;
			case (4):
			break;
			default:
			       puts("Codice errato!! La risposta inserita non e' compresa tra 1 e 4  \n\n");
				   opzione = 0;
			break;
			}
		}
	}while(opzione == 0 || opzione != SCELTA_MENU_PRECEDENTE);
}


void Menu_gestione_ordini(FILE *file_prodotti, FILE *file_clienti, FILE *file_ordini){
	short int opzione = 0;
	char controllo[LUNGHEZZA_10] = "";

	do{
		puts("\n\n");
		puts("\tScegli il tipo di operazione che vuoi effettuare:   ");
		puts("\t\t(1) Gestione ordini");
		puts("\t\t(2) Visualizzazione statistiche");
		puts("\t\t(3) Ritorna al menu precedente");
		scanf("%s" ,controllo);

		if(isdigit(controllo[0]) == 0){

			printf("Codice errato!! La risposta inserita e' alfanumerica, sono validi solo numeri \n\n");
			opzione = 0;

		}
		else{
			opzione = atoi(controllo);

			switch (opzione){
			case (1):
					Gestione_ordini(file_prodotti, file_ordini);
			break;
			case (2):
			        Menu_statistiche(file_prodotti, file_clienti, file_ordini);
			break;
			case (3):
		    break;
			default:
			       puts("Codice errato!! La risposta inserita non e' compresa tra 1 e 3  \n\n");
				   opzione = 0;
			break;
			}
		}
	}while(opzione == 0 || opzione != MAX_SCELTA_MENU);
}


void Menu_statistiche(FILE *file_prodotti, FILE *file_clienti, FILE *file_ordini){
	short int opzione = 0;
	char controllo[LUNGHEZZA_10] = "";

	puts("****************************************************************");
	puts("***************BENVENUTO NEL MENU' STATISTICHE******************");
	puts("****************************************************************");

	do{
		puts("\n\n");
		puts("\tScegli il tipo di statistiche da visualizzare:   ");
		puts("\t\t(1) Stampa l' elenco dei prodotti");
		puts("\t\t(2) Stampa l' elenco degli ordini");
		puts("\t\t(3) Stampa l' elenco dei prodotti piu' acquistati");
		puts("\t\t(4) Stampa l' elenco dei prodotti maggiormente valutati");
		puts("\t\t(5) Torna al menu' precedente");
		scanf("%s" ,controllo);

		if(isdigit(controllo[0]) == 0){

			printf("Codice errato!! La risposta inserita e' alfanumerica, sono validi solo numeri \n\n");
			opzione = 0;

		}
		else{
			opzione = atoi(controllo);

			switch (opzione){
			case (1):
					puts("********************************LISTA PRODOTTI********************************\n");
			        stampa_prodotti(file_prodotti);
			break;
			case (2):
		            puts("*****************************LISTA ORDINI*****************************\n");
		            stampa_ordini(file_ordini);
		    break;
			case (3):
		            puts("**************************LISTA PRODOTTI PIU' ACQUISTATI**************************\n");
					ordinamento_ordini_quantita(file_ordini);
			break;
			case (4):
		           puts("*************************LISTA PRODOTTI CON MIGLIOR VALUTAZIONE*************************\n");
					ordinamento_prodotti_valutazione(file_prodotti);
			break;
			case (5):
		    break;
			default:
			       puts("Codice errato!! La risposta inserita non e' compresa tra 1 e 5  \n\n");
				   opzione = 0;
			break;
			}
		}
	}while(opzione == 0 || opzione != SCELTA_MENU_RICERCA);
}


void svuotaInput(){
  while(getchar()!='\n');
}
