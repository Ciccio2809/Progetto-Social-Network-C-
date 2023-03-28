#include "amici.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

lista_utenti*  trovapers (lista_utenti *lista, char username[]){
    lista_utenti* r= lista; //precedente
    while(r!=NULL){
        if((strcmp(r->username, username))==0) {
              //  puts("L'utente è registrato al social! \n");
                return r;
        }
        else {
            r=r->next;
        }
    }
    printf("Utente non registrato! \n\n");
    return NULL;
}

void aggiuntaLettura(lista_amici ** head, char username[]){
	struct nodo_amici* tmp1 = (struct nodo_amici*) 
malloc(sizeof(struct nodo_amici));
    strcpy(tmp1->username, username);
    tmp1 ->next = *head;
    *head = tmp1;
}


int aggiungi_amico (struct utente **lista,  char username[], struct utente ** head) {//registrazione
    int trovato;
    lista_utenti* s= *lista; 
    if(trovapers(*head,username) != NULL){
    	struct nodo_amici* tmp1 = (struct nodo_amici*) 
malloc(sizeof(struct nodo_amici));
    	strcpy(tmp1->username, username);
    	tmp1 ->next = s->amici;
    	s->amici = tmp1;
    	*lista = s; 
    	return 0;
	}
	return 1;
}
    

void visualizza_amici (lista_amici* lista){
    struct nodo_amici* r = lista;
    if(r == NULL){
    	printf( " Non hai ancora aggiunto nessun amico \n");
	}
    while(r!=NULL){
            printf("%s \n", r->username);
            r=r->next;
        }
    printf("\n\n\n");
}

int countAmici (lista_amici *lista){
	lista_amici * tmp = lista;
	int i = 0;
	while(tmp != NULL){
		i++;
		tmp = tmp->next;
	}
	return i;
}


int rimuovi_amico (struct utente **listaut, lista_amici** listaam, char username[]){
    struct utente* trovato;
    trovato=trovapers(*listaut, username);
    if(trovato!=NULL){//cancella un elemento dalla lista
        //restituisce 0 se tutto va a buon fine, 1 in caso contrario
            //due puntatori di appoggio
            lista_amici* r= *listaam; //precedente
            lista_amici* q= *listaam; //successivo
            //cerco l'elemento (al più arrivo alla fine della lista)
            while ((q!= NULL) && (strcmp(q->username, username)!=0)){
                    //r raggiunge q
                    r = q;
                    //q va avanti di uno
                    q = q->next;
            }
            //se sono arrivato alla fine della lista l'elemento non c'è
            if (q == NULL)
                    return 1;
            //se sono ancora in testa alla lista devo spostare la testa
            if (q==*listaam)
                    (*listaam) = (*listaam)->next;
            //se sono in una posizione intermedia il precedente deve puntare al successivo di q
            //nota: q punta all'elemento che voglio cancellare
            else
                    r->next = q->next;
            //dealloco l'elemento
            free(q);
            //tutto e' andato a buon fine
            return 0;
        }
    else return 1;
    }


void info_amici (struct utente **listaut, lista_amici *listaam, char username[]){
    
    lista_amici* r= listaam; //precedente
    while(r!=NULL){
        if((strcmp(r->username, username))==0) {
            lista_utenti* s= *listaut; //precedente
            while(s!=NULL){
                if((strcmp(s->username, username))==0) {
                    printf("le informazioni su %s sono: \n", s->username);
                    printf("%s \t", s->nome);
                    printf("%s \t", s->cognome);
                    printf(" '%s' \t", s->username);
                    printf("%s \n\n\n", s->ddn);
                    return;
                }
                else s=s->next;
            }
        }
        else r=r->next;

    }
    printf("Utente non registrato! \n\n\n");

}
