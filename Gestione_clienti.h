/*
 * Gestione_clienti.h
 *
 *  Created on: 4 ago 2020
 *      Author: Barty
 */

#ifndef GESTIONE_CLIENTI_H_
#define GESTIONE_CLIENTI_H_

/**
 * @brief Inserimento Cliente
 * @brief Permette di inserie salvare su file i dati di un cliente
 *
 * @param file_creatore puntatore al file dei clienti
 *
 */
void inserimento_cliente(FILE *file_clienti);

/**
 * @brief Stampa Clienti
 * @brief Permette di effettuare la stampa dei campi dei clienti,
 *
 * @param file_creatore puntatore al file dei clienti
 *
 */
void stampa_clienti(FILE *file_clienti);

/**
 * @brief Modifica Clienti
 * @brief Permette di effettuare la modifica dei campi dei clienti
 *
 * @param file_creatore puntatore al file dei clienti
 *
 */
void modifica_cliente(FILE *file_clienti);

/**
 * @brief Cancella Clienti
 * @brief Permette di effettuare la cancellazione dei campi dei clienti
 *
 * @param file_creatore puntatore al file dei clienti
 *
 */
void cancella_cliente(FILE *file_clienti);



#endif /* GESTIONE_CLIENTI_H_ */
