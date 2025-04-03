#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
typedef struct etudiant* list;
typedef struct etudiant{
    long matricule;
    char nom[40];
    char prenom[40];
    int groupe;
    list suivent;
}etudiant;
list l = NULL; 

int nbr_etudiant = 0;

typedef struct noeud {
    etudiant* etudiant;
    struct noeud* gauche;
    struct noeud* droite;
} noeud;
noeud* arbre = NULL;//racine de l'arbre



int afficher_ou_non(){
    char choi;
    printf("Voulez-vous afficher le resultat ? \n");
    test:
    printf("pour -oui- Tapez -O- \npour -non- Tapez -N-");
    printf("\n\n~~Votre choix :");
    scanf("%c",&choi);
    getchar();
    system("cls");
    if(choi == 'O' || choi == 'o'){
        printf("le nombre total des etudiants :%d \n\n",nbr_etudiant);
        printf("****la liste des etudiants \n" );
        return 1;
    }
    if(choi != 'O' && choi != 'o' && choi != 'N' && choi != 'n'){
	    printf("Incorrect choix!!  Entrez une lettre entre -O- ou -N-\n");
        goto test;
    }
    return 0;
}

noeud *creerNoeud(etudiant *etud){
    noeud *nouveauNoeud = (noeud *)malloc(sizeof(noeud));
    if (nouveauNoeud == NULL){
        perror("Erreur d'allocation memoire");
        exit(EXIT_FAILURE);
    }
    nouveauNoeud->etudiant = etud;
    nouveauNoeud->gauche = NULL;
    nouveauNoeud->droite = NULL;
    return nouveauNoeud;
}

noeud *ajouterEtudiantCroissant(noeud *racine, etudiant *etud){
    if (racine == NULL) return creerNoeud(etud);

    noeud *noeudCourant = racine;
    while (noeudCourant != NULL){
        if (etud->matricule > noeudCourant->etudiant->matricule){
            if (noeudCourant->gauche == NULL){
                noeudCourant->gauche = creerNoeud(etud);
                break;
            }
            else noeudCourant = noeudCourant->gauche;
        }
        else{
            if (noeudCourant->droite == NULL){
                noeudCourant->droite = creerNoeud(etud);
                break;
            }
            else noeudCourant = noeudCourant->droite;
        }
    }
    return racine;
}

void chargerInfoArbre() {
    nbr_etudiant = 0;
    FILE* file = fopen("Fichier_Test.txt", "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }
    clock_t debut,fin;
    debut = clock();
    etudiant* etud;
    while ((etud = malloc(sizeof(etudiant))) != NULL && !feof(file)) {
        fscanf(file, "Matricule: %lu Nom: %[^Prénom] Prénom: %[^Groupe] Groupe: %d\n",&etud->matricule, etud->nom, etud->prenom, &etud->groupe);
        nbr_etudiant++;
        arbre = ajouterEtudiantCroissant(arbre, etud);
    }
    fin = clock();
    double temps_ecoule = ((double)(fin - debut)) / CLOCKS_PER_SEC;
    FILE* file2 = fopen("temps.csv", "a+");
    fprintf(file2, "allocation,/,arbre,%lf\n",temps_ecoule);
    fclose(file2);
    fclose(file);
    return;
}

void afficherArbreCroissant(noeud* racine) {
    if (racine != NULL) {
        afficherArbreCroissant(racine->gauche);
        printf("Matricule: %lu Nom: %s Prenom: %sGroupe: %d\n" ,racine->etudiant->matricule ,racine->etudiant->nom ,racine->etudiant->prenom, racine->etudiant->groupe);
        afficherArbreCroissant(racine->droite);
    }
    return;
}

// sisir dans la structure de donne Tableau
etudiant* charger_info_tableau(etudiant* liste_etudiant){
    nbr_etudiant = 0;
    clock_t debut,fin;
    debut = clock();
    FILE* file = fopen("Fichier_Test.txt", "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier\n");
        exit(EXIT_FAILURE);
    }

    liste_etudiant = malloc(sizeof(etudiant));
    while( fscanf(file, "Matricule: %lu Nom: %[^Prénom] Prénom: %[^Groupe] Groupe: %d\n",&liste_etudiant[nbr_etudiant].matricule ,liste_etudiant[nbr_etudiant].nom ,liste_etudiant[nbr_etudiant].prenom ,&liste_etudiant[nbr_etudiant].groupe) == 4 ){
        nbr_etudiant++;
        liste_etudiant = (etudiant*)realloc(liste_etudiant, (nbr_etudiant + 1) * sizeof(etudiant));
    }
    fclose(file);
    fin = clock();
    double temps_ecoule = ((double)(fin - debut)) / CLOCKS_PER_SEC;
    FILE* file2 = fopen("temps.csv", "a+");
    fprintf(file2, "allocation,/,tableau,%lf\n",temps_ecoule);
    fclose(file2);
    return liste_etudiant;
}
// des fonctions de trie pour le tableau de hachage
double trie_bulle(etudiant tab[], int taille) {
    clock_t debut , fin;
    debut = clock();
    etudiant temp;
    int nbr_swape = 0;

    for (int i = 0; i < taille - 1; i++) {
        for (int j = 0; j < taille - 1 - i; j++) {
            if (tab[j].matricule < tab[j + 1].matricule) {
                // l'echage des elemnts qui n'on pas le mem ordre
                temp = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = temp;
                nbr_swape++;
            }
        }
        if(nbr_swape == 0){
            fin = clock();
            double temps_ecoule = 0;
            return (temps_ecoule = ((double)(fin - debut)) / CLOCKS_PER_SEC);
        }
        nbr_swape = 0;
    }
    fin = clock();
    double temps_ecoule = 0;
    return (temps_ecoule = ((double)(fin - debut)) / CLOCKS_PER_SEC);
}
double trie_selection(etudiant tab[], int taille) {
    clock_t debut , fin;
    debut = clock();
    int i, j, min_index;
    etudiant temp;

    for (i = 0; i < taille - 1; i++) {
        min_index = i;
        for (j = i + 1; j < taille; j++) {
            if (tab[j].matricule > tab[min_index].matricule) {
                min_index = j;
            }
        }
        // Swap the le minimum avec l'elemnet de l'indice i
        temp = tab[i];
        tab[i] = tab[min_index];
        tab[min_index] = temp;
    }
    fin = clock();
    double temps_ecoule = 0;
    return temps_ecoule = ((double)(fin - debut)) / CLOCKS_PER_SEC;
}
double trie_insertion(etudiant tab[], int taille) {
    int i, j;
    etudiant temp;
    clock_t debut , fin;
    debut = clock();

    for (i = 1; i < taille; i++) {
        temp = tab[i];
        j = i - 1;

        // Move elements that are greater than key to one position ahead of their current position
        while (j >= 0 && tab[j].matricule < temp.matricule) {
            tab[j + 1] = tab[j];
            j = j - 1;
        }
        tab[j + 1] = temp;
    }
    fin = clock();
    double temps_ecoule = 0;
    return temps_ecoule = ((double)(fin - debut)) / CLOCKS_PER_SEC;
}
// debut des fonctions de trie par fusion pour les table de hachage
void fusionner(etudiant tab[], int debut, int milieu, int fin) {
    int n1 = milieu - debut + 1;
    int n2 = fin - milieu;

    // Creation de tableaux temporaires
    etudiant* temp1 = malloc(n1 * sizeof(etudiant));
    if(temp1 == NULL){
        printf("Erreur d'alocation memoire");
        exit(EXIT_FAILURE);
    }
    etudiant *temp2 = malloc(n2 * sizeof(etudiant));
    if(temp2 == NULL){
        printf("Erreur d'alocation memoire");
        exit(EXIT_FAILURE);
    }
    // Copie des donnees dans les tableaux temporaires
    for (int i = 0; i < n1; i++) {
        temp1[i] = tab[debut + i];
    }
    for (int j = 0; j < n2; j++) {
        temp2[j] = tab[milieu + 1 + j];
    }
    // Fusion des tableaux temporaires dans le tableau principal
    int i = 0, j = 0, k = debut;
    while (i < n1 && j < n2) {
        if (temp1[i].matricule >= temp2[j].matricule) {
            tab[k] = temp1[i];
            i++;
        } else {
            tab[k] = temp2[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        tab[k] = temp1[i];
        i++;
        k++;
    }
    while (j < n2) {
        tab[k] = temp2[j];
        j++;
        k++;
    }
    free(temp1);
    free(temp2);
    return;
}
double trie_fusion(etudiant tab[], int debut, int fin) {
    clock_t debutt,fini;
    debutt = clock();
    if (debut < fin) {
        int milieu = debut + (fin - debut) / 2;
        trie_fusion(tab, debut, milieu);
        trie_fusion(tab, milieu + 1, fin);
        fusionner(tab, debut, milieu, fin);
    }
    fini = clock();
    double temps_ecoule = 0;
    return temps_ecoule = ((double)(fini - debutt)) / CLOCKS_PER_SEC;
}

int partitionner(etudiant tab[], int debut, int fin) {
    float pivot = tab[fin].matricule;
    int i = debut - 1;
    for (int j = debut; j <= fin - 1; j++) {
        if (tab[j].matricule >= pivot) {
            i++;
            etudiant temp = tab[i];
            tab[i] = tab[j];
            tab[j] = temp;
        }
    }
    etudiant temp = tab[i + 1];
    tab[i + 1] = tab[fin];
    tab[fin] = temp;
    return i + 1;
}
double trie_rapide(etudiant tab[], int debut, int fin) {
    clock_t debutt,fini;
    debutt = clock();
    if (debut < fin) {
        // Trouver l'index du pivot apres partitionnement
        int pivotIndex = partitionner(tab, debut, fin);
        trie_rapide(tab, debut, pivotIndex - 1);
        trie_rapide(tab, pivotIndex + 1, fin);
    }
    fini = clock();
    double temps_ecoule = 0;
    return temps_ecoule = ((double)(fini - debutt)) / CLOCKS_PER_SEC;
}

void afficher_resultats(etudiant tab[], int taille){
    for (int j = 0; j < taille; j++) {
        if (tab[j].nom[0] != '\0') printf("Matricule: %lu Nom: %s Prenom: %sGroupe: %d\n", tab[j].matricule ,tab[j].nom ,tab[j].prenom ,tab[j].groupe);
        else printf("Case vide\n");
    }
    return;
}
void menu_de_tri_etudiants(etudiant tab_ha[], int taille) {
    int choix;
    double temps = 0;
    FILE* file2 = fopen("temps.csv", "a+");
    printf("Donnez-moi l'algorithme de tri que vous voulez utiliser\n");
    test5:
    printf("1. Trie par Selection\n");
    printf("2. Trie a Bulle\n");
    printf("3. Trie par Insertion\n");
    printf("4. Trie par Fusion\n");
    printf("5. Trie Rapide\n");
    printf("\nVotre choix : ");
    scanf("%d", &choix);
    getchar();
    system("cls");
    switch (choix) {
        case 1:
            temps = trie_selection(tab_ha, taille);
            fprintf(file2, "trie,selection,tableau d'hachage,%lf\n",temps);
        break;
        case 2:
            temps = trie_bulle(tab_ha, taille);
            fprintf(file2, "trie,bulle,tableau d'hachage,%lf\n",temps);
        break;
        case 3:
            temps = trie_insertion(tab_ha, taille);
            fprintf(file2, "trie,insertion,tableau d'hachage,%lf\n",temps);
        break;
        case 4:
            temps = trie_fusion(tab_ha, 0, taille - 1);
            fprintf(file2, "trie,fusion,tableau d'hachage,%lf\n",temps);
        break;
        case 5:
            temps = trie_rapide(tab_ha, 0, taille - 1);
            fprintf(file2, "trie,rapide,tableau d'hachage,%lf\n",temps);
        break;
        default:
            printf("Choix incorrect, veuillez choisir un nombre entre 1 et 5\n");
            goto test5;
        break;

        fclose(file2);
        return;
    }
    system("cls");
    printf("Votre donnees ont ete trie en ordre decroisant \n");
    if (afficher_ou_non()) afficher_resultats(tab_ha, taille);
    return;
}
// fin des procedures utilise pour le hachage !!
// debut de systeme de hachage
int fonction_hash_1(long nombre) {
    int somme = 0;
    while (nombre > 0) {
        int chiffre = nombre % 10;
        chiffre *= 2;
        somme += chiffre;
        nombre /= 10;
    }
    return somme % 100;
}
void charger_info_tableau_hachage() {
    clock_t debut;
    etudiant *tab_ha = (etudiant*)calloc(100, sizeof(etudiant)); // Initialise tous les champs � z�ro (case vide) en utilisant la m�thode de hachage statique
    nbr_etudiant = 0; // Pour la cr�ation dynamique
    debut = clock();
    clock_t fin;

    FILE *file = fopen("Fichier_Test.txt", "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier\n");
        exit(EXIT_FAILURE);
    }
    etudiant* liste_etudiant = NULL;

    while (!feof(file)) {
        liste_etudiant = (etudiant*)realloc(liste_etudiant, (nbr_etudiant + 1) * sizeof(etudiant));
        if (fscanf(file, "Matricule: %lu Nom: %[^Prénom] Prénom: %[^Groupe] Groupe: %d\n", &liste_etudiant[nbr_etudiant].matricule, liste_etudiant[nbr_etudiant].nom, liste_etudiant[nbr_etudiant].prenom, &liste_etudiant[nbr_etudiant].groupe) == 4) {
            int k = fonction_hash_1(liste_etudiant[nbr_etudiant].matricule);
            if (k >= 0 && k < 100) {
                if (tab_ha[k].nom[0] == '\0') {
                    strcpy(tab_ha[k].nom, liste_etudiant[nbr_etudiant].nom);
                    strcpy(tab_ha[k].prenom, liste_etudiant[nbr_etudiant].prenom);
                    tab_ha[k].matricule = liste_etudiant[nbr_etudiant].matricule;
                    tab_ha[k].groupe = liste_etudiant[nbr_etudiant].groupe;
                } else {
                    int case_initial = k;
                    while (tab_ha[k].nom[0] != '\0') {
                        k = (k + 1) % 100;
                        if (k == case_initial) {
                            printf("Erreur : Impossible d'inserer l'etudiant, toutes les cases sont occupees.\n");
                            break;
                        }
                    }
                    if (k != case_initial) {
                        strcpy(tab_ha[k].nom, liste_etudiant[nbr_etudiant].nom);
                        strcpy(tab_ha[k].prenom, liste_etudiant[nbr_etudiant].prenom);
                        tab_ha[k].matricule = liste_etudiant[nbr_etudiant].matricule;
                        tab_ha[k].groupe = liste_etudiant[nbr_etudiant].groupe;
                    }
                }
                nbr_etudiant++;
            }
        }
    }
    fin = clock();
    char choi;
    system("cls");
    printf("Votre donnes ont ete bien sauvgardez dans le table d'hachage \n");
    if(afficher_ou_non()) afficher_resultats(tab_ha, 100);


    double temps_ecoule = ((double)(fin - debut)) / CLOCKS_PER_SEC;
    fclose(file);

    FILE* file2 = fopen("temps.csv", "a+");
    fprintf(file2, "allocation par hachage,linear,tableau d'hachage,%lf\n",temps_ecoule);
    fclose(file2);
    menu_de_tri_etudiants(tab_ha, 100);
    free(liste_etudiant);
    free(tab_ha);
    return;
}
// debut de systeme de hachage double
int fonction_hash_2(long matricule) {
    int somme = 0;
    while (matricule > 0) {
        int chiffre = matricule % 10;
        chiffre *= 3;
        somme += chiffre;
        matricule /= 10;
    }
    somme = somme + 80;
    somme = (int)somme/13;
    return somme % 100;
}

void charger_info_tableau_hachage_double() {    ///////
    clock_t debut, fin;
    etudiant tab_ha[100] = {0};  // Initialise tous les champs à zéro (case vide) en utilisant la méthode de hachage statique
    int n = 0; // Pour la création dynamique
    FILE *file;
    etudiant* liste_etudiant = NULL;

    debut = clock();
    file = fopen("Fichier_Test.txt", "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier\n");
        exit(EXIT_FAILURE);
    }
    for (nbr_etudiant =  0 ; !feof(file) ; nbr_etudiant++) {
        n++;
        liste_etudiant = (etudiant*)realloc(liste_etudiant, n * sizeof(etudiant));
        fscanf(file, "Matricule: %lu Nom: %[^Prénom] Prénom: %[^Groupe] Groupe: %d\n", &liste_etudiant[nbr_etudiant].matricule, liste_etudiant[nbr_etudiant].nom, liste_etudiant[nbr_etudiant].prenom, &liste_etudiant[nbr_etudiant].groupe);
        int k = fonction_hash_1(liste_etudiant[nbr_etudiant].matricule);
        int j = 0;
        if (k >= 0 && k < 100) {
            if (tab_ha[k].nom[0] == '\0') {
                strcpy(tab_ha[k].nom, liste_etudiant[nbr_etudiant].nom);
                strcpy(tab_ha[k].prenom, liste_etudiant[nbr_etudiant].prenom);
                tab_ha[k].matricule = liste_etudiant[nbr_etudiant].matricule;
                tab_ha[k].groupe = liste_etudiant[nbr_etudiant].groupe;
            }
            else {
                // Vérifier si la case est déjà occupée par un autre nom
                while (tab_ha[k].nom[0] != '\0') {
                    k = (k + 1) % 100;
                    j++;
                    if (j >= 100) {
                        // La premier fonction n'a pas trouvé de case
                        k = fonction_hash_2(liste_etudiant[nbr_etudiant].matricule);
                        j = 0;
                    }
                }
                // On a trouvé une case disponible
                if (k < 0) {// La case de la table de hachage est déjà occupée par un autre nom
                    continue;
                }
                else {
                    strcpy(tab_ha[k].nom, liste_etudiant[nbr_etudiant].nom);
                    strcpy(tab_ha[k].prenom, liste_etudiant[nbr_etudiant].prenom);
                    tab_ha[k].matricule = liste_etudiant[nbr_etudiant].matricule;
                    tab_ha[k].groupe = liste_etudiant[nbr_etudiant].groupe;
                }
            }
        }
    }
    fin = clock();
    char choi;
    system("cls");
    printf("Votre donnes ont ete bien sauvgardez dans le table d'hachage \n");
    if(afficher_ou_non()) afficher_resultats(tab_ha, 100);

    fclose(file);
    printf("\n");
    double temps_ecoule = ((double)(fin - debut)) / CLOCKS_PER_SEC;
    FILE* file2 = fopen("temps.csv", "a+");
    fprintf(file2, "allocation par hachage,double,tableau d'hachage,%lf\n",temps_ecoule);
    fclose(file2);
    menu_de_tri_etudiants(tab_ha, 100);
    return;
}


void free_liste(){
    while(l != NULL){
        list tmp = l;
        l=l->suivent;
        free(tmp);
    }
    return;
}

// fin de systeme de hchage double
void charger_info_liste(){  // sisir dans la structure de donne List
    nbr_etudiant = 0;
    clock_t debut,fin;
    debut = clock();
    FILE* file = fopen("Fichier_Test.txt", "r");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }
    while(!feof(file)){
        list q = malloc(sizeof(etudiant));
        if(q == NULL){
            printf("Erreur d'alocation memoire");
            free_liste();
            exit(EXIT_FAILURE);
        }
        fscanf(file, "Matricule: %lu Nom: %[^Prénom] Prénom: %[^Groupe] Groupe: %d\n",&q->matricule ,q->nom ,q->prenom ,&q->groupe);
        nbr_etudiant++;
        q->suivent = l;
        l = q;
    }
    fclose(file);
    fin = clock();
    double temps_ecoule = ((double)(fin - debut)) / CLOCKS_PER_SEC ;
    FILE* file2 = fopen("temps.csv", "a+");
    fprintf(file2, "allocation,/,liste,%lf\n",temps_ecoule);
    fclose(file2);
    return;
}

void swap_list(list p ,list q){
    etudiant swp;
    strcpy(swp.nom , p->nom);
    strcpy(swp.prenom , p->prenom);
    swp.groupe = p->groupe;
    swp.matricule = p->matricule;

    strcpy(p->nom , q->nom);
    strcpy(p->prenom , q->prenom);
    p->groupe = q->groupe;
    p->matricule = q->matricule;

    strcpy(q->nom , swp.nom);
    strcpy(q->prenom , swp.prenom);
    q->groupe = swp.groupe;
    q->matricule = swp.matricule;
    return;
}

void trie_selection_list(){
    clock_t debut = clock();
    clock_t fin;
    list fin_list = NULL;
    list tmp;
    list min = l;
    for(list p = l; p->suivent != NULL; p = p->suivent){
        for(tmp = l; tmp->suivent != fin_list; tmp = tmp->suivent){
            if(min->matricule > tmp->suivent->matricule) min = tmp->suivent;
        }
        swap_list(min , tmp);
        fin_list = tmp;
        min = l;
    }
    fin = clock();
    double temps_ecoule = ((double)(fin - debut)) / CLOCKS_PER_SEC;
    FILE* file2 = fopen("temps.csv", "a+");
    fprintf(file2, "trie,selection,liste,%lf\n",temps_ecoule);
    fclose(file2);
    return;
}

void trie_bulle_list(){
    clock_t debut = clock();
    clock_t fin;
    list fin_list = NULL;
    list tmp;
    for(list q = l; q->suivent != NULL; q = q->suivent){
        for(tmp = l; tmp->suivent != fin_list; tmp = tmp->suivent){
            if(tmp->matricule < tmp->suivent->matricule) swap_list(tmp ,tmp->suivent);
        }
        fin_list = tmp;
    }
    fin = clock();
    double temps_ecoule = ((double)(fin - debut)) / CLOCKS_PER_SEC;
    FILE* file2 = fopen("temps.csv", "a+");
    fprintf(file2, "trie,bulle,liste,%lf\n",temps_ecoule);
    fclose(file2);
    return;
}

void trie_insertion_list() {
    clock_t debut = clock();
    clock_t fin;
    if (l == NULL || l->suivent == NULL) return;
    list triee = NULL;
    while (l != NULL) {
        list courant = l;
        l = l->suivent; // Avancer dans la liste non triee
        if (triee == NULL || courant->matricule >= triee->matricule) {
            // Inserer au debut de la liste triee
            courant->suivent = triee;
            triee = courant;
        } else {
            // Rechercher l'emplacement d'insertion dans la liste triee
            list tmp = triee;
            while (tmp->suivent != NULL && tmp->suivent->matricule > courant->matricule) {
                tmp = tmp->suivent;
            }
            // Inserer dans la liste triee
            courant->suivent = tmp->suivent;
            tmp->suivent = courant;
        }
    }
    // Mettre a jour la liste d'origine avec la liste triee
    l = triee;
    fin = clock();
    double temps_ecoule = ((double)(fin - debut)) / CLOCKS_PER_SEC;
    FILE* file2 = fopen("temps.csv", "a+");
    fprintf(file2, "trie,insertion,liste,%lf\n",temps_ecoule);
    fclose(file2);
    return;
}

list milieu(list tete){
    list slow = tete;
    list fast = tete->suivent;
    while (fast != NULL && fast->suivent != NULL){
        slow = slow->suivent;
        fast = fast->suivent->suivent;
    }
    return slow;
}

list fusionner2(list l1 , list l2){
    list q = malloc(sizeof(etudiant));
    if(q == NULL){
        perror("Erreur d'alocation memoire");
        free_liste(l);
        exit(EXIT_FAILURE);
    }
    list tmp = q;

    while(l1 != NULL && l2 != NULL){
        if(l1->matricule > l2->matricule){
            tmp->suivent = l1;
            l1 = l1->suivent;
        }
        else{
            tmp->suivent = l2;
            l2 = l2->suivent;
        }
        tmp = tmp->suivent;
    }
    if(l1 == NULL) tmp->suivent = l2;
    else tmp->suivent = l1;
    return q->suivent;
}


list trie_fusion_list(list tete){
    if(tete == NULL || tete->suivent == NULL) return tete;

    list g = tete;
    list d = milieu(tete);

    list tmp = d;
    d = d->suivent;
    tmp->suivent = NULL;

    g =  trie_fusion_list(g);
    d =  trie_fusion_list(d);
    return fusionner2(g , d);
}

list partition(list debut, list fin) {

    list pivot = debut;
    for (list q = debut ; q != NULL && q != fin ; q = q->suivent) {
        if (q->matricule > fin->matricule) {
            pivot = debut;
            swap_list(debut , q);
            debut = debut->suivent;
        }
    }
    swap_list(debut , fin);
    return pivot;
}

void trie_rapide_list(list debut, list fin) {
    if(debut == fin) return;
    list pivot = partition(debut, fin);
    if (pivot != NULL && pivot->suivent != NULL) trie_rapide_list(pivot->suivent, fin);
    if (pivot != NULL && debut != pivot) trie_rapide_list(debut, pivot);
    return;
}

void afichage_liste(){
    for(list tmp = l ; tmp != NULL ; tmp = tmp->suivent)
        printf("Matricule: %lu Nom: %s Prenom: %sGroupe: %d\n", tmp->matricule, tmp->nom, tmp->prenom, tmp->groupe);
    return;
}


int main(){
    etudiant *liste_etudiant = NULL;
    int choix;
    list fin ;
    double temps = 0;
    clock_t debut1, fin1;

    FILE* file2 = fopen("temps.csv", "w");
    fprintf(file2, "OPERATION,TYPE D'OPERATION,STRUCTURE DE DONNEE,TEMPS\n");
    fclose(file2);

    system("cls");
    printf("Salut!!  Bienvenu dans notre application...\n\n");
    printf("Je vais vous giuder Quelle structure de donne voulez vous choisir : ");
    while(1){
    test1:
    printf("\nTapez -1- pour modialiser votre Structure de donne avec un Tableau");
    printf("\nTapez -2- pour modialiser votre Structure de donne avec une Liste Chaine");
    printf("\nTapez -3- pour modialiser votre Structure de donne avec une Arbre");
    printf("\nTapez -4- pour chargez votre donnees par le hachgae");
    printf("\n\n~~Votre choix :");
    scanf("%d",&choix);
    getchar();
    system("cls");
    switch(choix){
    case 01: // Appel a la fonction pour charger les informations dons un tableau
        liste_etudiant = charger_info_tableau(liste_etudiant);

        system("cls");
        printf("Votre donnes ont ete bien sauvgardez dans le tableau \n");
        if (afficher_ou_non()) afficher_resultats(liste_etudiant,nbr_etudiant - 1);

        printf("\n\nDonnez mois maintenat la method de trie que vous voulez utiliser : \n");
        test2:
        printf("Tapez -1- pour utiliser le Trie par Selection\n");
        printf("Tapez -2- pour utiliser le Trie a Bulle\n");
        printf("Tapez -3- pour utiliser le Trie par insertion\n");
        printf("Tapez -4- pour utiliser le Trie par fusion\n");
        printf("Tapez -5- pour utiliser le Trie rapide\n");
        printf("\n~~Votre choix : ");
        scanf("%d",&choix);
        getchar();
        system("cls");
        switch(choix){
            case 1:
                temps = trie_selection(liste_etudiant,nbr_etudiant - 1);
                file2 = fopen("temps.csv", "a+");
                fprintf(file2, "trie,selection,tableau,%lf\n",temps);
                fclose(file2);
            break;
            case 2:
                temps = trie_bulle(liste_etudiant,nbr_etudiant - 1);
                file2 = fopen("temps.csv", "a+");
                fprintf(file2, "trie,bulle,tableau,%lf\n",temps);
                fclose(file2);
            break;
            case 3:
                temps = trie_insertion(liste_etudiant,nbr_etudiant - 1);
                file2 = fopen("temps.csv", "a+");
                fprintf(file2, "trie,insertion,tableau,%lf\n",temps);
                fclose(file2);
            break;
            case 4:
                temps = trie_fusion(liste_etudiant,0,nbr_etudiant - 2);
                file2 = fopen("temps.csv", "a+");
                fprintf(file2, "trie,fusion,tableau,%lf\n",temps);
                fclose(file2);
            break;
            case 5:
                temps = trie_rapide(liste_etudiant,0,nbr_etudiant - 2);
                file2 = fopen("temps.csv", "a+");
                fprintf(file2, "trie,rapide,tableau,%lf\n",temps);
                fclose(file2);
            break;
            default:
                printf("choix incorect!! entrer un numero entre 1 et 5\n");
                goto test2;
            break;
        }
        system("cls");
        printf("Votre donnees ont ete trie en ordre decroisant \n");
        if (afficher_ou_non()) afficher_resultats(liste_etudiant,nbr_etudiant - 1);

    break;

    case 2:  // Appel a la fonction pour charger les informations dons une Liste Chaine
        charger_info_liste();

        system("cls");
        printf("Votre donnes ont ete bien sauvgardez dans la Liste Chaine \n");
        if (afficher_ou_non()) afichage_liste();

        printf("\n\nDonnez mois maintenat la method de trie que vous voulez utiliser : \n");
        test3:
        printf("Tapez -1- pour utiliser le Trie par Selection\n");
        printf("Tapez -2- pour utiliser le Trie a Bulle\n");
        printf("Tapez -3- pour utiliser le Trie par insertion\n");
        printf("Tapez -4- pour utiliser le Trie par fusion\n");
        printf("Tapez -5- pour utiliser le Trie rapide\n");
        printf("\n~~Votre choix :");
        scanf("%d",&choix);
        getchar();
        system("cls");
        switch(choix){
            case 1:
                trie_selection_list();
            break;
            case 2:
                trie_bulle_list();
            break;
            case 3:
                trie_insertion_list();
            break;
            case 4:
                debut1 = clock();
                l = trie_fusion_list(l);
                fin1 = clock();
                temps = ((double)(fin1 - debut1)) / CLOCKS_PER_SEC;
                file2 = fopen("temps.csv", "a+");
                fprintf(file2, "trie,fusion,liste,%lf\n",temps);
                fclose(file2);

            break;
            case 5:
                fin = l;
                debut1 = clock();
                while(fin != NULL && fin->suivent != NULL) fin = fin->suivent;
                trie_rapide_list(l , fin);
                fin1 = clock();
                temps = ((double)(fin1 - debut1)) / CLOCKS_PER_SEC;
                file2 = fopen("temps.csv", "a+");
                fprintf(file2, "trie,rapide,liste,%lf\n",temps);
                fclose(file2);
            break;
            default:
                printf("choix incorect!! entrer un numero entre 1 et 5\n");
                goto test3;
            break;
        }
        system("cls");
        printf("Votre donnees ont ete trie en ordre decroisant \n");
        if (afficher_ou_non()) afichage_liste();

        free_liste();
    break;

    case 3:  // Appel a la fonction pour charger les informations dans une Arbre
        chargerInfoArbre();

        system("cls");
        printf("Votre donnes ont ete bien sauvgardez dans l'arbre binaire de recherche \n");
        if (afficher_ou_non()) afficherArbreCroissant(arbre);

    break;
    case 4:
        printf("Donnez mois la methode de hachage que vous voulez utiliser !!\n");
        test4:
        printf("Tapez -1- pour utiliser le hachage linieaire\n");
        printf("Tapez -2- pour utiliser le hachage double\n");
        printf("\n~~Votre choix :");
        scanf("%d",&choix);
        getchar();
        system("cls");
        switch(choix){
            case 1:
                charger_info_tableau_hachage();
            break;
            case 2:
                charger_info_tableau_hachage_double(liste_etudiant);
            break;
            default:
                printf("choix incorect!! entrer un numero entre 1 et 2\n");
                goto test4;
            break;
        }

    break;
    default:
        printf("choix incorect!! entrer un numero entre 1 et 4");
        goto test1;
    break;
    }


    char choi;
    printf("\n\nVoulez-vous continue ? \n");
    testt:
    printf("pour continue Tapez -O- \npour quiter Tapez -N-\n~~Votre choix :");
    scanf("%c",&choi);
    getchar();
    if(choi == 'N' || choi == 'n'){
	    system("cls");
        printf("merci d'utiliser notre application. \nMission Complete ....");
        return 0;
    }
	if(choi != 'O' && choi != 'o' && choi != 'N' && choi != 'n'){
    	printf("Incorrect choix!!  Entrez une lettre entre -O- ou -N-\n\n~~Votre choix :");
        goto testt;
	}
    system("cls");
    }
}
