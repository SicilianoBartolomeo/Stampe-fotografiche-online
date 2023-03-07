/*
 * Gestione_prodotti.h
 *
 *  Created on: 31 lug 2020
 *      Author: Barty
 */

#ifndef GESTIONE_PRODOTTI_H_
#define GESTIONE_PRODOTTI_H_

/**
 * @brief Inserimento Prodotto
 * @brief Permette di inserire e salvare su file i dati di un prodotto
 *
 * @param file_creatore puntatore al file dei prodotti
 *
 */
void inserimento_prodotto(FILE *file_prodotti);

/**
 * @brief Stampa Prodotto
 * @brief Permette di effettuare la stampa dei campi dei prodotti,
 *
 * @param file_creatore puntatore al file dei prodotti
 *
 */
void stampa_prodotti(FILE *file_prodotti);

/**
 * @brief Modifica Prodotto
 * @brief Permette di effettuare la modifica dei campi dei prodotti
 *
 * @param file_creatore puntatore al file dei prodotti
 *
 */
void modifica_prodotto(FILE *file_prodotti);

/**
 * @brief Cancella Prodotto
 * @brief Permette di effettuare la cancellazione dei campi dei prodotti
 *
 * @param file_creatore puntatore al file dei prodotti
 *
 */
void cancella_prodotto(FILE *file_prodotti);

/**
 * @brief Ordinamento Prodotti Quantit‡
 * @brief Permette di ordinare e stampare i record
 * presenti nel file prodotti in base alla quantit‡
 * dei prodotti
 *
 * @param file_creatore puntatore al file dei prodotti
 *
 */
void ordinamento_prodotti_quantita(FILE *file_prodotti);

/**
 * @brief Ordinamento Prodotti Prezzo
 * @brief Permette di ordinare e stampare i record
 * presenti nel file prodotti in base al prezzo per pezzo
 *
 * @param file_creatore puntatore al file dei prodotti
 *
 */
void ordinamento_prodotti_prezzo(FILE *file_prodotti);

/**
 * @brief Ordinamento Prodotti Spedizione
 * @brief Permette di ordinare e stampare i record
 * presenti nel file prodotti in base al costo di spedizione
 *
 * @param file_creatore puntatore al file dei prodotti
 *
 */
void ordinamento_prodotti_spedizione(FILE *file_prodotti);

/**
 * @brief Ordinamento Prodotti Valutazione
 * @brief Permette di ordinare e stampare i record
 * presenti nel file prodotti in base alla valutazione
 *
 * @param file_creatore puntatore al file dei prodotti
 *
 */
void ordinamento_prodotti_valutazione(FILE *file_prodotti);

#endif /* GESTIONE_PRODOTTI_H_ */
