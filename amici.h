#ifndef amici_h
#define amici_h

#include "utenti.h"
struct utente;


 struct nodo_amici{
  char username[20];
  struct nodo_amici* next;
};
  
typedef struct nodo_amici lista_amici;

  //aggiungi amico => inserimento ordinato per cognome in lista
    int aggiungi_amico (struct utente **listaut, char username[], struct utente ** head);

    void aggiuntaLettura(lista_amici ** head, char username[]);

  //rimuovi amico => eliminazione dalla lista
    int rimuovi_amico (struct utente **listaut, lista_amici** lista, char username[]);
  
  //visualizza lista amici =>stampa della lista
    void visualizza_amici (lista_amici *lista);
  
  //cerca informazioni amici => ricerca in lista e stampa di una voce
    void info_amici (struct utente **listaut, lista_amici *listaam, char username[]);

    int countAmici (lista_amici *lista);


#endif /* amici_h */
