#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define TAILLE_MAX 1000

typedef struct Produit Produit;
struct Produit{
    char codeP[7],designation[20];
    double pAchat;
    double pVente;
};

struct listNode{
    Produit data;
    struct listNode *suivant,*precedent;
};


typedef struct listNode ListNode;
typedef ListNode *ListNodePtr;

void insert(ListNodePtr *tete,Produit *p);
void delete(ListNodePtr *tete);
void printList(ListNodePtr courant);
int listVide(ListNodePtr listPtr);
void rechercherProduit(ListNodePtr *tete,char *code);
void enregistrerDansFichier(ListNodePtr *tete);
void chargerInfos(ListNodePtr *listPtr);
void afficherProduit(Produit *p);
void mappingProduit(char *ch,Produit *p);
void supprimerProduit(ListNodePtr *tete,char *code);
void delBr(char *ch);
void menu(void);

void main(char *args,int argc){
    ListNodePtr listPtr = NULL;
    ListNodePtr tete =NULL;
    int choix;
    Produit value;
    char code[7];
    menu();
    scanf("%d",&choix);
    do{
        switch (choix){
            case 1:
                system("cls");
                printf("\tAjouter Un Produit Au Debut \n");
                printf("\tSaisir Code Produit --->  ");
                scanf("%s",&value.codeP);
                printf("\tSaisir Designation Produit --->  ");
                scanf("%s",&value.designation);
                printf("\tSaisir Prix D'Achat --->  ");
                scanf("%lf",&value.pAchat);
                printf("\tSaisir Prix De Vente --->  ");
                scanf("%lf",&value.pVente);
                insert(&listPtr,&value);
                break;
            case 2:
                system("cls");
                printf("\tAjouter Un Produit A La Fin . Veuillez Implementer Cette Fonction \n");
                //insertEnd(&tete,value);
                system("pause");
                break;
            case 3:
                system("cls");
                printf("\tAfficher Les Produits \n");
                printList(listPtr);
                break;
            case 4:
                system("cls");
                printf("\tRechercher Un Produit \n");
                printf("\tSaisir Le Code Produit --> ");
                scanf("%s",&code);
                rechercherProduit(&listPtr,code);
                system("pause");
                break;
            case 5:
                system("cls");
                printf("\tSupprimer Un Produit \n");
                printf("\tSaisir Le Code Produit --> ");
                scanf("%s",&code);
                //rechercherProduit(&listPtr,code);
                supprimerProduit(&listPtr,code);
                system("pause");
                break;
            case 6:
                system("cls");
                printf("\tEnregistrement Des Produits Dans Un Fichier \n");
                enregistrerDansFichier(&listPtr);
                system("pause");
                break;
            case 7:
                chargerInfos(&listPtr);
                break;
            default:
                system("cls");
                printf("\tChoix Invalide  \n\n");
                system("pause");
                break;
        }
        menu();
        scanf("%d",&choix);
    }while(choix!=8 && choix<8 && choix>0);
    system("cls");
    printf("........Fin D'execution.......\n\n");
    system("pause");

}

void menu(void){
    system("cls");
    printf("\n");
    printf("\t+-------------------------------+\n");
    printf("\t|  \tEntrer Votre Choix      |\n");
    printf("\t+-------------------------------+\n\n");
    printf("   1. Ajouter Un Produit Au Debut \n");
    printf("   2. Ajouter Un Produit A La Fin \n");
    printf("   3. Afficher Les Produits De La Liste \n");
    printf("   4. Rechercher Un Produit Dans La Liste  \n");
    printf("   5. Supprimer Un Produit De La Liste  \n");
    printf("   6. Enregistrer La Liste Dans Un Fichier \n");
    printf("   7. Charger Les Produits Dans La Liste \n");
    printf("   8. Quitter Le Programme \n");
    printf("\n");
    printf("   ---> ");
}
void insert(ListNodePtr *tete,Produit *p){
    ListNodePtr nouveau;
    nouveau = malloc(sizeof(ListNode));

    if(nouveau != NULL){
        nouveau->data.pAchat = p->pAchat;
        nouveau->data.pVente = p->pVente;
        strcpy(nouveau->data.codeP,p->codeP);
        strcpy(nouveau->data.designation,p->designation);
        nouveau->suivant = *tete;
        *tete = nouveau;
    }
    else{
        printf("\tEchec Insertion...Pas De Memoire Disponible\n\n");
    }
}
void printList(ListNodePtr courant){
     system("cls");
    if(courant==NULL){
        printf("\tLa Liste Est Vide\n\n");
    }
    else{
        printf("\tVoici Le Contenu De La Liste : \n\n");
        while(courant != NULL){
            afficherProduit(&courant->data);
            courant = courant->suivant;
        }
    }
    system("pause");
}

int listVide(ListNodePtr listPtr){
    return listPtr==NULL;
}
void rechercherProduit(ListNodePtr *tete,char *code){
    ListNodePtr courant = *tete;

    while(courant->suivant!=NULL && strcmp(courant->data.codeP,code)!=0){
        courant = courant->suivant;
    }
    system("cls");
    if(strcmp(courant->data.codeP,code)==0){
        printf("\tLes Details Du Produit \n");
        printf("\t----------------------\n\n");
        afficherProduit(&courant->data);
    }
    else
        printf("\tCe Produit n'exste Pas Dans La liste..... Veuillez Renseigner Un Bon Code SVP ..!\n\n");
}
void enregistrerDansFichier(ListNodePtr *tete){

    ListNodePtr courant = *tete;
    FILE* fichier = NULL;
    fichier = fopen("produits.txt","a");

    if(fichier!=NULL){
        
        while(courant!=NULL){
            fprintf(fichier,"%s|%s|%f|%f\n",courant->data.codeP,courant->data.designation,courant->data.pAchat,courant->data.pVente);
            courant = courant->suivant;
        }
        printf("\tProduits Enregistres Avec Succes....\n\n");
        fclose(fichier);
    }
    else
        printf("\tAjout Impossible...Echec Ouverture Fichier\n\n");
}
void chargerInfos(ListNodePtr *listPtr){
    FILE* fichier = NULL;
    char chaine[TAILLE_MAX] = "";
    Produit p;
    system("cls");
    fichier = fopen("produits.txt","r");
    if(fichier!=NULL){
        while(fgets(chaine,TAILLE_MAX,fichier)!=NULL){
            mappingProduit(chaine,&p);
            insert(listPtr,&p);
            //insert(listPtr,tcode);
            //fgets(chaine,TAILLE_MAX,fichier);
        }
        fclose(fichier);
        printf("\n\tChargement Reussi Avec Succes....Consulter La Liste..!\n\n");
    }
    else
        printf("\tChargement Impossible...Echec Ouverture Fichier\n\n");
    system("pause");
}
void afficherProduit(Produit *p){

    printf("\tCode Produit            ---> %s\n",p->codeP);
    printf("\tDesignation Produit     ---> %s\n",p->designation);
    printf("\tPrix D'Achat            ---> %f\n",p->pAchat);
    printf("\tPrix De Vente           ---> %f\n",p->pVente);
    printf("\n");
}
void supprimerProduit(ListNodePtr *tete,char *code){
    ListNodePtr precedent;
    ListNodePtr courant;
    ListNodePtr temp;
    if(strcmp(code,(*tete)->data.codeP)==0){
        temp = *tete;
        *tete = (*tete)->suivant;
        free(temp);
        printf("\n\tProduit Supprime Avec Succes....\n\n");
    }
    else{
        precedent = *tete;
        courant = (*tete)->suivant;

        while(courant!=NULL && strcmp(courant->data.codeP,code)!=0){
            precedent = courant;
            courant = courant->suivant;
        }
        if(courant!=NULL){
            temp = courant;
            precedent->suivant = courant->suivant;
            free(temp);
            printf("\n\tProduit Supprime Avec Succes....\n\n");
        }
    }
}
void mappingProduit(char *ch,Produit *p){

    char ch1[17]="",tab[3][20];
    delBr(ch);
    int taille = strlen(ch);
    int j=0,i=0,k=0;   
    
    for(j=0;j<taille;j++){
        if(ch[j]!='|'){
            ch1[k] = ch[j];
            k++;
        }
        else{
            ch1[k] = 0;
            strcpy(tab[i],ch1);
            k=0;
            i++;
        }
    } 
    
    double pa = strtod(tab[2],NULL);
    double pv = strtod(tab[3],NULL);

    strcpy(p->codeP,tab[0]);
    strcpy(p->designation,tab[1]);
    p->pAchat = pa;
    p->pVente = pv;
}
void delBr(char *ch){
    int i=0;
    for(i=0;i<strlen(ch);i++){
        if(ch[i]=='\n')
        ch[i]=0;
    }
}