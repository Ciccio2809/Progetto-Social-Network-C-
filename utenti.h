#ifndef utenti_h
#define utenti_h

#include "amici.h"

struct utente {                //definisco nodo della lista
    char nome[20];                //informazioni del nodo
    char cognome[20];
    char username[20];
    char password[20];
    char ddn[20];
    struct nodo_amici* amici;
    struct utente* next;      //puntatore al prossimo nodo
};

typedef struct utente lista_utenti;


//registrazione => inserimento ordinato per cognome in lista
int registrazione(lista_utenti **lista, struct utente c, struct nodo_amici *  p);

//login => ricerca in lista, se il return è 1 allora è abilitato l'accesso
lista_utenti* provalogin (lista_utenti *lista);

//stampa lista persone registrate => stampa della lista
void stampa_utenti (lista_utenti* lista);

//cerca se esiste questa persona nel social => ricerca in lista, se il return è 1 allora la persona è registrata, altrimenti return 0
int ricerca_pers (lista_utenti *lista, char nome[], char cognome[]);


//modifica password => modifica della password di un utente
int modifica_password(lista_utenti* lista,struct utente c, char nuova_password[]);

void rimozione_liste(struct nodo_amici **listaam, char username[20]);

//eliminazione account => cancellazione dalla lista
int elimina_account (char username[20], lista_utenti ** head);


#endif /* utenti_h */

