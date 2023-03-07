/*
 * Gestione_ordini.h
 *
 *  Created on: 28 lug 2020
 *      Author: Barty
 */

#ifndef GESTIONE_ORDINI_H_
#define GESTIONE_ORDINI_H_

/**
 * @brief Inserimento Ordine
 * @brief Permette di effettuare l' insermineto dei campi degli ordini,
 *
 * @param file_creatore puntatore al file dei ordini
 *
 */
void inserimento_ordine(FILE *file_ordini);

/**
 * @brief Stampa Ordini
 * @brief Permette di effettuare la stampa dei campi degli ordini,
 *
 * @param file_creatore puntatore al file dei ordini
 *
 */
void stampa_ordini(FILE *file_ordini);

/**
 * @brief Realizzazione Ordine
 * @brief Permette a un cliente di realizzare un ordine
 *
 * @param file_prodotti puntatore al file dei prodotti
 * @param file_clienti puntatore al file dei clienti
 * @param file_ordini puntatore al file degli ordini
 *
 */
void Realizzazione_ordine(FILE *file_prodotti, FILE* file_clienti, FILE* file_ordini);

/**
 * @brief Realizzazione Ordine
 * @brief Permette al laboratorio di gestiregli ordini
 * effettuati dai clienti
 *
 * @param file_prodotti puntatore al file dei prodotti
 * @param file_ordini puntatore al file degli ordini
 *
 */
void Gestione_ordini(FILE *file_prodotti, FILE* file_ordini);

/**
 * @brief Stampa Ordini
 * @brief Permette di effettuare la stampa dei campi degli ordini
 * il quale stato Ë "in gestione"
 *
 * @param file_creatore puntatore al file dei ordini
 *
 */
void stampa_ordini_gestione(FILE *file_ordini);

/**
 * @brief Ricerca Categoria
 * @brief Funzione che restituisce il codice di un prodotto
 * in base alla categoria inserita, ricercandone quello
 * con quantit‡ maggiore
 *
 * @param file_prodotti puntatore al file dei prodotti
 *
 */
short int Ricerca_categoria(FILE *file_prodotti);

/**
 * @brief Ricerca Codice Prodotto
 * @brief Permette di stampare i dati di un ordine in base
 * al codice prodotto inserito
 *
 * @param file_prodotti puntatore al file ordini
 *
 */
void Ricerca_codice_prodotto(FILE *file_ordini);

/**
 * @brief Ricerca Codice Cliente
 * @brief Permette di stampare i dati di un ordine in base
 * al codice cliente inserito
 *
 * @param file_prodotti puntatore al file degli ordini
 *
 */
void Ricerca_codice_cliente(FILE *file_ordini);

/**
 * @brief Ricerca Categoria
 * @brief Funzione che restituisce il codice di un prodotto
 * in base al codice cliente inserito
 *
 * @param file_prodotti puntatore al file degli ordini
 *
 */
short int RicercaCodiceCliente(FILE *file_ordini);

/**
 * @brief Ordinamento Ordini Quantit‡
 * @brief Permette di ordinare e stampare i record
 * presenti nel file ordini in base alla quantit‡
 * dei prodotti venduta
 *
 * @param file_creatore puntatore al file degli ordini
 *
 */
void ordinamento_ordini_quantita(FILE *file_ordini);

/**
 * @brief Ordinamento Ordini Valutazione
 * @brief Permette di ordinare e stampare i record
 * presenti nel file ordini in base alla valutazione
 * dei clienti
 *
 * @param file_creatore puntatore al file degli ordini
 *
 */
void ordinamento_ordini_valutazione(FILE *file_ordini);

/**
 * @brief Ordinamento Ordini Prezzo
 * @brief Permette di ordinare e stampare i record
 * presenti nel file ordini in base al costo totale
 *
 * @param file_creatore puntatore al file degli ordini
 *
 */
void ordinamento_ordini_prezzo(FILE *file_ordini);

/**
 * @brief Quick Sort
 * @brief Algoritmo di ordinamento Quick Sort
 *
 * @param v vettore su cui verra effettuato l'ordinamento
 * @param s vettore associato al vettore v
 * @param l l = left ultima posizione del vettore
 * @param r r = right prima posizione del vettore
 */
void quick_sort(short int v[], short int s[], int l, int r);

/**
 * @brief Partizione
 * @brief Esegue una partizione del vettore
 *
 * @param v vettore su cui verra effettuato l'ordinamento
 * @param s vettore associato al vettore v
 * @param l l = left ultima posizione del vettore
 * @param r r = right prima posizione del vettore
 * @return j cioe' la partizione del vettore
 */
int partizione(short int v[], short int s[], int l, int r);

/**
 * @brief Quick Sort Float
 * @brief Algoritmo di ordinamento Quick Sort per dati di tipo float
 *
 * @param v vettore su cui verra effettuato l'ordinamento
 * @param s vettore associato al vettore v
 * @param l l = left ultima posizione del vettore
 * @param r r = right prima posizione del vettore
 */
void quick_sort_float(float v[], short int s[], int l, int r);

/**
 * @brief Partizione
 * @brief Esegue una partizione del vettore di tipo float
 *
 * @param v vettore su cui verra effettuato l'ordinamento
 * @param s vettore associato al vettore v
 * @param l l = left ultima posizione del vettore
 * @param r r = right prima posizione del vettore
 * @return j cioe' la partizione del vettore
 */
int partizione_float(float v[], short int s[], int l, int r);

#endif /* GESTIONE_ORDINI_H_ */
