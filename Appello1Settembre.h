/*
 * Appello1Settembre.h
 *
 *  Created on: 25 lug 2020
 *      Author: Barty
 */

/**
 *
 * @mainpage
 * @authors Siciliano Bartolomeo Roberto, Pagliara Giacomo
 *
 * Questo programma effettua la gestione tra prodotti, clienti e ordini di un laboratorio fotografico.
 *
 * All'interno di questo progetto i dati vengono inseriti, stampati, modificati ed eliminati.
 *
 * Inoltre ci sono altre funzioni:
 * 1. realizzazione di un ordine da parte di un cliente
 * 2. gestione degli ordini da parte del laboraorio
 * 3. ricerca dei prodotti e degli ordini
 * 4. ordinamento dei prodotti e degli ordini
 *
 * La prima deve permettere di far completare un ordine a un cliente che inserendo i campi restituisce il costo totale;
 *
 * La seconda deve permettere a un laboratorio di gestire un ordine in base alla quantit‡ richiesta e a quella a disposizione;
 *
 * La terza deve essere in grado di stampare le informazione dei prodotti e degli ordini inserendo codice cliente o prodotto;
 *
 * La quarta deve permettere du stampare le informazione dei prodotti e degli ordini in base al prezzo, alla quantit‡ o alla valutazione.
 *
 */

#ifndef APPELLO1SETTEMBRE_H_
#define APPELLO1SETTEMBRE_H_

/**
 * @brief indica la scelta massima che si puo' fare nel menu principale
 */
#define MAX_SCELTA_MENU 3

/**
 * @brief indica la scelta massima che si puo' fare nel menu amministratore di laboratorio
 */
#define MAX_SCELTA_MENU_LAB 7

/**
 * @brief indica la scelta massima che si puo' fare nel menu aggiunta-modifica-cancellazione ordini
 */
#define SCELTA_MENU_PRECEDENTE 4
/**
 * @brief indica la scelta massima che si puo' fare nel menu RICERCA
 */
#define SCELTA_MENU_RICERCA 5

/**
 * @brief indica il numero massimo di record presenti in un file
 */
#define MAX_RECORD 30

/**
 * @brief indica la lunghezza 10 per le stringhe
 */
#define LUNGHEZZA_10 10

/**
 * @brief indica la lunghezza 20 per le stringhe
 */
#define LUNGHEZZA_20 20

/**
 * @brief indica la lunghezza 30 per le stringhe
 */
#define LUNGHEZZA_30 30




typedef struct{

	/** intero > 0
	 *
	 * indica il codice del prodotto ordinato
	 **/
	short int codice_prodotto;


	/** intero > 0
	 *
	 * indica il codice del cliente che ha effettuato l'ordine
	 **/
	short int codice_cliente;

	/** intero > 0
	 *
	 * indica il prezzo dell'ordine
	 **/
	float prezzo;

	/** intero >= 0
	 *
	 * indica la quantit‡ di prodotti che il cliente  vuole ordinare
	 **/
	short int quantita;

	/** char di lunghezza 20
	 *
	 * indica lo stato dell ordine (in stampa, spedito, in gestionr, annullato)
	 **/
	char stato[LUNGHEZZA_20];

	/** intero che va da 1 a 5
	 *
     * indica la valutazione del prodotto ordinato
	 **/
	short int valutazione;

	/** char di lunghezza 30
	 *
     * indica i commenti lasciati dall'utente
	 **/
	char commenti [LUNGHEZZA_30];
}ordine;

typedef struct{

	/** intero > 0
	 *
	 * indica il codice identificativo del prodotto
	 **/
	short int codice_prodotto;

	/** stringa di char
	 *
	 * indica la categoria del prodotto (fotolibri, stampe su tela, stampe foto, calendario)
	 **/
	char categoria[LUNGHEZZA_20];

	/** intero >= 0 indica quantit‡ disponibile,
	 * < 0 indica quantit‡ da stampare
	 *
	 * indica la quantit‡ di prodotti
	 **/
	short int quantita;

	/** float > 0
	 *
	 * indica il costo di ogni pezzo
	 **/
	float prezzo_pezzo;

	/** float > 0
	 *
     * indica il costo della spedizione
	 **/
	float spedizione;

	/** char di lunghezza 30
	 *
     * indica una breve descrizione del prodotto
	 **/
	char descrizione [LUNGHEZZA_30];

	/** intero che va da 1 a 5
	 *
     * indica la valutazione del prodotto ordinato
	 **/
	short int valutazione;

	/** char di lunghezza 30
	 *
     * indica i commenti lasciati dall'utente
	 **/
	char commenti [LUNGHEZZA_30];
}prodotto;

typedef struct{

	/** intero > 0
	 *
	 * indica il codice del cliente
	 **/
	short int codice_cliente;


	/** intero > 0
	 *
	 * indica il codice del prodotto ordinato dal cliente
	 **/
	short int codice_prodotto;
}cliente;




/**
 * @brief Menu Principale
 * @brief Ci sono 3 scelte da poter effettuare nel menu principale
 *
 * @param file_prodotti puntatore al file dei prodotti
 * @param file_clienti puntatore al file dei clienti
 * @param file_ordini puntatore al file degli ordini
 */
void menu_principale(FILE *file_prodotti, FILE *file_clienti, FILE *file_ordini);


/**
 * @brief Menu Laboratorio
 * @brief Ci sono 8 scelte da poter effettuare nel menu laboratorio
 *
 * @param file_prodotti puntatore al file dei prodotti
 * @param file_clienti puntatore al file dei clienti
 * @param file_ordini puntatore al file degli ordini
 */
void menu_laboratorio(FILE *file_prodotti, FILE *file_clienti, FILE *file_ordini);

/**
 * @brief Menu Cliente
 * @brief Ci sono 4 scelte da poter effettuare nel menu cliente
 *
 * @param file_prodotti puntatore al file dei prodotti
 * @param file_clienti puntatore al file dei clienti
 * @param file_ordini puntatore al file degli ordini
 */
void menu_cliente(FILE *file_prodotti, FILE *file_clienti, FILE *file_ordini);

/**
 * @brief Menu Ordinamento Prodotti
 * @brief Ci sono 5 scelte da poter effettuare nel menu ordinamento prodotti
 *
 * @param file_prodotti puntatore al file dei prodotti
 */
void Menu_ordinamento_prodotti(FILE *file_prodotti);

/**
 * @brief Menu Ordinamento Ordinamento
 * @brief Ci sono 4 scelte da poter effettuare nel menu ordinamento ordini
 *
 * @param file_prodotti puntatore al file degli ordini
 */
void Menu_ordinamento_ordini(FILE *file_ordini);

/**
 * @brief Menu Gestione Ordinamento
 * @brief Ci sono 3 scelte da poter effettuare nel menu ordinamento ordini
 *
 * @param file_prodotti puntatore al file dei prodotti
 * @param file_clienti puntatore al file dei clienti
 * @param file_prodotti puntatore al file degli ordini
 */
void Menu_gestione_ordini(FILE *file_prodotti,FILE *file_clienti, FILE *file_ordini);

/**
 * @brief Menu Cliente
 * @brief Ci sono 6 scelte da poter effettuare nel menu laboratorio
 *
 * @param file_prodotti puntatore al file dei prodotti
 * @param file_clienti puntatore al file dei clienti
 * @param file_ordini puntatore al file degli ordini
 */
void Menu_statistiche(FILE *file_prodotti, FILE *file_clienti, FILE *file_ordini);


/**
 * @brief Aggiunta Modifica Cancellazione Prodotti
 * @brief Ci sono 4 scelte da poter effettuare nel menu
 *
 * @param file_ordini puntatore al file degli ordini
 */
void Aggiunta_modifica_cancellazione_prodotti(FILE *file_ordini);

/**
 * @brief Aggiunta Modifica Cancellazione Clienti
 * @brief Ci sono 4 scelte da poter effettuare nel menu
 *
 * @param file_clienti puntatore al file dei clienti
 */
void Aggiunta_modifica_cancellazione_clienti(FILE *file_clienti);

/**
 * @brief Menu Ricerca Ordini
 * @brief Ci sono 4 scelte da poter effettuare nel menu
 * in base alla scelta ci sar‡ una procedura diversa di ricerca
 *
 * @param file_ordini puntatore al file degli ordini
 */
void Menu_ricerca_ordini(FILE *file_ordini);

/**
 * @brief Svuota Input
 * @brief Serve per svuotare il buffer
 *
 */
void svuotaInput();


#endif /* APPELLO1SETTEMBRE_H_ */
