#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "amici.h"
#include "utenti.h"




int menu_modifiche(lista_utenti** listaut, lista_utenti ** head){
    int selez, check;
    struct utente c={"prova"};
    char nuova_password[20];
    do{
	    printf("Menu modifiche \n Digita 1 per modificare la password \n Digita 2 per eliminare il tuo account \n Digita 5 per tornare indietro \n\n\n\n ");
	    scanf("%d", &selez);
	    switch(selez){
	        case 1:
	            printf("inserisci username: ");
	            scanf("%s", c.username);
	            printf("inserisci password: ");
	            scanf("%s", c.password);
	            printf("inserisci nuova password: ");
	            scanf("%s", nuova_password);
	            modifica_password(*listaut, c, nuova_password);
	            break;
	        case 2:
	            printf("ATTENZIONE! LA SEGUENTE COMPILAZIONE ELIMINERA' IL SUO ACCOUNT. DIGITARE 1 PER CONTINUARE, 2 PER USCIRE: ");
	            scanf("%d", &check);
	            if(check==1)
	            	elimina_account((*listaut)->username, head);
	            return 1;
    	}
    } while(selez<5);
    return 0;
}



void menu_utente(lista_utenti* lista,lista_utenti* head){
    int selez;
    char nome[20];
    char cognome[20];
    do{
	    printf("Menu utenti \n Digita 1 per visualizzare le persone presenti sul social network \n Digita 2 per cercare se una persona e' registrata \n Digita 5 per tornare indietro \n");
	    scanf("%d", &selez);
	    switch(selez){
	         case 1:
	             stampa_utenti(head);
	             break;
	         case 2:
	             printf("inserisci nome: ");
	             scanf("%s", nome);
	             
	             printf("inserisci cognome: ");
	             scanf("%s", cognome);
	             ricerca_pers(head, nome, cognome);
	             break;
	         case 5:
	             return;
	    }
    }while(selez<5);
}

void menu_amicizie(lista_utenti** listaut, lista_utenti ** head){
    int selez;
    char username[20], trovaptr[20];
    do{
    	printf("Menu amicizie \n Digita 1 per aggiungere un amico \n Digita 2 per eliminare un amico \n Digita 3 per trovare le informazioni di un amico");
	printf(" \n Digita 4 per visualizzare la lista dei tuoi amici \n Digita 5 per tornare indietro \n\n\n\n\n ");
    	scanf("%d", &selez);
	    switch(selez){
	        case 1:
	            printf("Inserisci l'username: ");
	            scanf("%s", username);
	            if(((aggiungi_amico(listaut, username, head))==0))
	               printf("Amico aggiunto con successo! \n\n");
	            break;
	       case 2:
	            printf("inserisci l'username: ");
	            scanf("%s", username);
	            lista_amici * tmp = (*listaut)->amici;
	            rimuovi_amico(head, &tmp, username);
	            (*listaut)->amici = tmp;
	            break;
	        case 3:
	            printf("inserisci l'username: ");
	            scanf("%s", username);
	            info_amici(head, (*listaut)->amici, username);
	            break;
	        case 4:
	            visualizza_amici((*listaut)->amici);
	            break;
	        case 5:
	        	printf("Uscita...\n");
	            break;
	    }
    }while(selez != 5);
}
    

void menuprinc(lista_utenti **listaut,lista_utenti **head){
	int mod;
    int selez;
    printf("Benvenuto %s, cosa vuoi fare? \n\n",(*listaut)->nome );
    do{
	    printf(" Digita 1 per il menu amicizie \n Digita 2 per il menu utenti \n Digita 3 per il menu modifiche \n Digita 4 per uscire dall'account \n\n\n");
	    scanf("%d", &selez);
	    switch(selez){
	        case 1:
	            menu_amicizie(listaut,head);
	            break;
	        case 2:
	            menu_utente(*listaut,*head);
	            break;
	        case 3:
	            mod = menu_modifiche(listaut, head);
	            if(mod == 1){
	            	return;
				}
	            break;
	        case 4:
	            return;
	    }
    } while(selez!=5);
}

lista_utenti *letturaS(){//Lettura da file utenti.
	FILE *f = fopen("utenti.txt","r");
    lista_utenti dato;
    lista_utenti *head;
    int count;
    char username[20];
    head=NULL;
    int j = 0;
	if(f==NULL){
		printf("ERRORE forse il file utenti.txt non esiste\n");
		exit(1);
	}else{
		while(fscanf(f,"%s - %s - %s - %s - %s - %d",&(dato.nome),&(dato.cognome),&(dato.username),&(dato.password),&(dato.ddn),&count)!= EOF){
            lista_amici * p = NULL;
            if(count!=0){ 
                for(j = 0;j<count;j++){
                    fscanf(f,"%s\n",&username);
                    aggiuntaLettura(&p,username);
                }
            }
            dato.amici = p;
            registrazione(&head,dato,p); 
    	}
	}
	return head;
}
void salvaSocial(lista_utenti* head){
    FILE * output;
    int zero=0;
    if(output=fopen("utenti.txt" ,"w")){
        printf("\t\tSalvataggio utenti in corso \n");
        while(head!=NULL){  
            fprintf(output,"%s - ",head->nome);
            fprintf(output,"%s - ",head->cognome);
            fprintf(output,"%s - ",head->username);
            fprintf(output,"%s - ",head->password);
            fprintf(output,"%s - ",head->ddn);
            lista_amici * p = head->amici;
            if(p!=NULL){
                int count = countAmici(p); 
                fprintf(output,"%d\n",count);
                while(p!=NULL){
                    fprintf(output,"%s\n",p->username);
                    p=p->next;
                }
            }else{
                fprintf(output,"%d\n",zero);
                printf("\t\t Salvataggio... \n ");
            }
            head=head->next;
        }
    }else{
         printf("\n\nERRORE nella scrittura del file utenti.txt , controllare i permessi\n\n");
         return;
    }	
    printf("\t\tSalvataggio utenti completato \n");
    fclose(output);
}

    


int main(void){
	
    lista_utenti *head=letturaS(); //UTENTI HEAD

    lista_utenti *utente = NULL;
    struct utente c;
	int scelta = 0;

    do{
	    printf("Benvenuto nel social network! Se vuoi fare il login digita 1, se vuoi registrarti premi 2, Digita 5 per uscire dal programma \n");
	    scanf("%d", &scelta);
	    switch(scelta){
	    	
	            case 1:
	                utente = provalogin(head);
	            	break;
	            	
	            case 2:
		            printf("Benvenuto nella fase di registrazione! \n");
		            printf("Inserisci il tuo nome: ");
		            scanf("%s", c.nome);
		            printf("Inserisci il tuo cognome: ");
		            scanf("%s", c.cognome);
		            printf("Scegli un username: ");
		            scanf("%s", c.username);
		            printf("Inserire una password: ");
		            scanf("%s", c.password);
		            printf("Inserisci la tua data di nascita (formato GG/MM/AAAA diviso dagli slash): ");
		            scanf("%s", c.ddn);
		            
		            registrazione(&head, c, NULL);
		        
		            printf("\n Adesso effettua il Login! \n");
		            utente = provalogin(head);
	            	break;            		
	    }
	    
	    if(utente!=NULL){
	    	menuprinc(&utente,&head);
		}
	    utente = NULL;
    }while(scelta!=5);
    salvaSocial(head);
	return 0;
}
