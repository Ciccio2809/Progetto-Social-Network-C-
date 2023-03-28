#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utenti.h"

int registrazione (lista_utenti **lista, struct utente c, struct nodo_amici * amici) {//registrazione
    lista_utenti* r= *lista; //precedente
    lista_utenti* q= *lista; //successivo
    lista_utenti* p=(lista_utenti*)malloc(sizeof(lista_utenti)); //alloco nuovo nodo
    if (p==NULL) return 1; //se non alloco il nodo allora restituisco 1
    strcpy(p->nome, c.nome); //inseriamo il nuovo dato
    strcpy(p->cognome, c.cognome);
    strcpy(p->username, c.username);
    strcpy(p->password, c.password);
    strcpy(p->ddn, c.ddn);
    p->amici=amici;

    if(q==NULL){
        p->next=*lista;
        *lista=p;
        return 0;
    }
    while((q!=NULL)&&(strcmp(q->cognome, p->cognome)<0)){
        r=q;
        q=q->next;
    }
    if(q==*lista){
        p->next= *lista;
        *lista=p;
    }
    else{
        r->next=p;
        p->next=q;
    }
    return 0; //se tutto è andato correttamente resistuisco 0
    }

lista_utenti* provalogin(lista_utenti *lista){
    char username[20], password[20];
    lista_utenti* r= lista; //precedente
    printf("Inserisci il tuo username: ");
    scanf("%s", username);
    printf("Inserisci la tua password: ");
    scanf("%s", password);
    while(r!=NULL){
        if((strcmp(r->username, username))==0) {
            if(strcmp(r->password, password)==0){
                puts("Login effettuato! \n\n");
                return r;
            }
            else{
                printf("Password Errata! \n\n");
                return NULL;
            }
        }
        else {
            r=r->next;
        }
    }
    printf("Utente non registrato! \n\n ");
    return NULL;
}

void stampa_utenti(lista_utenti* lista){
    printf("\n Le persone registrate al Social Network sono: \n");
    lista_utenti* r= lista;
    while(r!=NULL){
        printf("%s ", r->nome);
        printf("%s ", r->cognome);
        printf(" '%s' \n", r->username);
        r=r->next;
    }
    printf("\n\n\n");
}




int ricerca_pers (lista_utenti *lista, char nome[], char cognome[]){
    lista_utenti* r= lista;
    while(r!=NULL){
        if((strcmp(r->nome, nome))==0 && (strcmp(r->cognome, cognome)==0)) 
{
                puts("L'utente è registrato al social! \n\n");
                return 0;
        }
        else {
            r=r->next;
        }
    }
    printf("Utente non registrato! \n\n");
    return 1;
}




int modifica_password(lista_utenti* lista, struct utente c, char nuova_password[]){
    lista_utenti* r= lista;
    while(r!=NULL){
        if((strcmp(r->username, c.username))==0) {
            if(strcmp(r->password, c.password)==0){
                strcpy(r->password, nuova_password);
                printf("Password modificata con successo! \n\n\n ");
                return 0;
            }
            else{
                printf("Password Errata! \n\n");
                return 2;
            }
        }
        else {
            r=r->next;
        }
    }
    printf("Username errato! \n\n");
    return 1;
};

void rimozione_liste(struct nodo_amici **listaam, char username[20]){
		
        lista_amici* s= *listaam;
        lista_amici* q= *listaam;
        while ((q!= NULL) && (strcmp(q->username, username)!=0)){
                s = q;
                q = q->next;
        }
        if (q == NULL)
        	return;
        if (q==*listaam)
                (*listaam)=(*listaam)->next;
        else{s->next=q->next;}
        free(q);
}
      
int elimina_account (char username[20], lista_utenti ** head){
    lista_utenti* r= *head;
    lista_utenti* q= *head;
    lista_utenti* tmp = *head;
    while (tmp!=NULL){
    	struct nodo_amici * tmpAmici = tmp->amici;
    	if(tmpAmici != NULL){
			rimozione_liste(&tmpAmici,username);
	    	tmp->amici = tmpAmici;
		}
		tmp = tmp->next;
	}
    while ((q != NULL) && (q->username != username)){
                r = q;
                q = q->next;
    }
    if (q == NULL)
            return 1;
    if (q==*head)
            (*head) = (*head)->next;
    else
            r->next = q->next;
    free(q);
    
    return 0;
}
