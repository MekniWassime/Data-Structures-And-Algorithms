typedef struct{
    int prio;
}Element;

typedef struct{
    Element* tab;
    int taille;
}Tas;

//Creation
Tas create(int taille){
    Tas tas;
    tas.tab = (Element*)malloc(sizeof(Elemet)*taille);
    tas.taille = 0;
    return tas;
}
//element i: //parent       (i - 1) div 2
             //fils-gauche  (2 * i) + 1  
             //fils-droit   (2 * i) + 2
//Insertion
void insertion(Tas* tas, Element e){
    tas->tab[tas->taille] = e;
    tas->taille++;
    int i = tas->taille-1;
    int iParent = (i-1)div2;
    while(iParent>=0 && tas->tab[i]->prio > tas->tab[iParent]->prio){
        permute(tas->tab+i,tas->tab+iParent);
        i = iParent;
    }
}
//Supression
Element suppression(Tas* tas){
    Element elem = tas->tab[0];
    tas->tab[0] = tas->tab[tas->taille-1];
    tas->taille--;
    int i = 0;
    int iGauche = (2*i)+1;
    int iDroit;
    while(iGauche < tas->taille){
        iDroit = (2*i)+2;
        if(iDroit>=tas->taille || tas->tab[iGauche]->prio <= tas->tab[iDroit]->prio){
            if(tas->tab[i]>tas->tab[iGauche])
                permute(tas->tab + i, tas->tab + iGauche);
        }else{
            if(tas->tab[i]->prio > tas->tab[iDroit]->prio)
                permute(tas->tab + i, tas->tab + iDroit);
        }
    }
    return elem;
}

permute(Element* e1, Element* e2){
    Element temp = *e1;
    *e1 = *e2;
    *e1 = temp;
}