typedef struct noued{
    noued * fils[2*m];
    int cles[2*m-1];
    int nombre;
}
typedef struct noued * BTree;
//creation
BTree create(int m){
    Btree tree;
    tree = (BTree)malloc(sizeof(BTree));
    tree.nombre = 0;
    for(int i = 0; i < 2*m; i++){
        b->fils[i] = nullptr;
    }   
    return b;
}
//recherche
BTree search(BTree tree, int cle){
    if(tree == nullptr)
        return nullptr;
    int i = 0;
    while(i<tree->nombre-1 && tree->cles[i] < cle)
        i++;
    if(tree->cles[i] == cle){
        return tree;
    }else if(tree->cles[i] > cle){
        return search(tree->fils[i], cle);
    }else{//if(tree->cles[i] < cle)
        return search(tree->fils[i+1], cle);
    }
}

//eclatement
//    m = 3         nbrCles = 5  nbrPtrs = 6
//                        [p0 c0 p1 c1 p2 c2 p3 .. .. .. ..]
//              p1 => [p0 v0 p1 v1 p2 v2 p3 v3 p4 v4 p5]
//              ====> [p0 v0 p1 v1 p2] .. v2 .. x2 => [p3 v3 p4 v4 p5]
//                        [p0 c0 p1 v2 x2 c1 p2 c2 p3 .. ..]

void eclaterFils(BTree root, indice){
    BTree newTree = create(m);
    Btree filsTree = root->fils[indice];
    for(int i = 0; i < m-1; i++)   //j=i+m => j = m; j < 2*m-1 (nbr cles)
        newTree->cles[i] = filsTree->cles[i+m];
    if(filsTree->fils[0]!=null)
        for(int i = 0; i < m; i++) //j=i+m => j = m; j < 2*m (nbr pointeurs/fils)
            newTree->fils[i] = filsTree->fils[i+m];
    filsTree->nombre = m-1; //m = position of median so we r taking keys before the median
    newTree->nombre = m-1;  //nbr cles - m = 2*m-1 - m = m-1
    for(int i = root->nombre; i > indice; i--) //indice=1 nombre=4 [c0, c1, c2, c3, ..] => [c0, c1, c1, c2, c3] => [c0, median, c1 , c2, c3]
        root->cles[i] = root->cles[i-1];       //                indice=1^   nombre=4^   indice=1^   nombre=4^          ^cles[indice]=median
    for(int i = root->nombre+1; i > indice + 1; i--) //            [p0, p1, p2, p3, p4, ..] => [p0, p1, newTree, p2, p3, p4]
        root->fils[i] = root->fils[i-1];             //            indice+1=2^ nombre+1=5^              ^fils[indice+1]=newTree        
    root->nombre = root->nombre + 1;                 //  result => [p0, c0, p1, median, newTree, c1, p2, c2, p3, c3, p4]
    root->cles[indice] = filsTree->cles[m]; //median
    root->fils[indice+1] = newTree;
}

void inserer-incomplet(Btree root, int cle){
    if(root->fils[0] == nullptr){
        int i = root->nombre-1;
        while(i => 0 && cle < root->cles[i]){
            root->cles[i+1] = root->cles[i];
            i--;
        }
        root->cles[i+1] = cle;
        root->nombre = root->nombre + 1;
    }else{
        int i = 0;
        while(i < root->nombre && cle > root->cles[i])
            i++;
        if(root->fils[i]->nombre == m*2-1){ //saturée
            eclaterFils(root, i);
            if(cle > root->cles[i])  //cle > median
                i++;
        }
        inserer-incomplet(root->fils[i], cle);
    }
}

BTree inserer(Btree root, int cle){
    if(root->nombre == 2*m-1){ //saturée
        BTree newTree = create(m);
        newTree->fils[0] = root;
        eclaterFils(newTree, 0);
        inserer-incomplet(newTree, cle);
        return newTree;
    }                          //else
    inserer-incomplet(root, cle);
    return root;
}

/************************ Supprimer **************************/
//takes from left and puts in right
BTree emprunt-gauche(BTree root, int indice){
    BTree tGauche = root->fils[indice-1];
    BTree tDroite = root->fils[indice];
    //add key from root to right and get the soon to be orphan child from the left
    for(int i = tDroite->nombre; i > 0; i--){
        tDroite->cles[i] = tDroite->cles[i-1];
        tDroite->fils[i+1] = tDroite->fils[i];
    }
    tDroite->fils[1] = tDroite->fils[0];
    tDroite->cles[0] = root->cles[indice-1];
    tDroite->fils[0] = tGauche->fils[tGauche->nombre];
    tDroite->nombre = tDroite->nombre + 1;
    //change the key in root with the rightmost cles from left
    root->cles[index-1] = tGauche->cles[tGauche->nombre-1];
    //remove the rightmost key from left which will make the rightmost child an orphan
    tGauche->nombre = tGauche->nombre - 1;
}
//takes from right and puts in left
void emprunt-droite(BTree root, int indice){
    BTree tGauche = root->fils[indice];
    BTree tDroite = root->fils[indice+1];
    //add key from root to left and get the soon to be orphan child from the right
    tGauche->cles[tGauche->nombre] = root->cles[indice];
    tGauche->fils[tGauche->nombre + 1] = tDroite->fils[0];
    tGauche->nombre = tGauche->nombre + 1;
    //change the key in root with the leftmost cles from right
    root->cles[index] = tDroite->cles[0];
    //remove the leftmost key from right which will make the lefttmost child an orphan
    for(int i = 0; i < tDroite->nombre-1; i++){  //we don't need to set the last key as it will be removed when we decrease nombre
        tDroite->cles[i] = tDroite->cles[i+1];
        tDroite->fils[i] = tDroite->fils[i+1]; 
    }   
    tDroite->fils[tDroite->nombre - 1] = tDroite->fils[tDroite->nombre];
    tDroite->nombre = tDroite->nombre - 1;
}

//move right elements to left
void fusion-droite(BTree root, int indice){
    BTree tGauche = root->fils[indice-1];
    BTree tDroite = root->fils[indice];
    //add key from root to left
    tGuache->cles[tGauche->nombre] = root->cles[indice-1];
    //add keys and children from right to left
    for(int i = 0; i < tGauche->nombre; i++){
        tGauche->cles[tGauche->nombre + i + 1] = tDroite->cles[i];
        tGauche->cles[tGauche->nombre + i + 1] = tDroite->fils[i];
    }
    tGauche->cles[tGauche->nombre + tDroite->nombre] = tDroite->fils[tDroite->nombre];
    tGauche->nombre = 2*m-1;
    free(tDroite);
    //remove key and child from root
    for(int i = indice-1; i < root->nombre-1; i++){ //we don't need to set the last key as it will be removed when we decrease nombre
        root->cles[i] = root->cles[i+1];
        root->fils[i] = root->fils[i+1];
    }
    root->fils[root->nombre-1] = root->fils[root->nombre];
    root->nombre = root->nombre - 1;
}

int supp-pred(BTree root){
    if(root->fils[0]==null){
        root->nombre = root->nombre - 1;
        return root->cles[root->nombre];
    }
    if(root->fils[root->nombre]->nombre < m){
        if(root->fils[root->nombre-1]->nombre < m)
            fussion-gauche(root, root->nombre);
        else
            emprunt-gauche(root, root->nombre);
    }
    return supp-pred(root->fils[root->nombre]);
}

BTree supprimer(BTree root, int cle){
    if(root->nombre == 1 && root->fils[0] != nullptr && root->fils[0]->nombre < m && root->fils[1]->nombre < m){
        fussion-droite(root,0);
        BTree temp = root->fils[0];
        free(root);
        return supprimer-interne(temp, cle);
    }
    return supprimer-interne(root, cle);
}


BTree supprimer-interne(BTree root, int cle){
    int i = 0;
    if(root->fils[0] == nullptr){     //root is a leaf
        while(i < root->nombre-1 && cle > root->cles[i])
            i++;                          //i points to the key 
        if(cle == root->cles[i])
            for(int j = i; j < root->number-1; j++)
                root->cles[i] = root->cles[i+1];
        root->nombre = root->nombre - 1;
        if(root->nombre == 0){
            free(root);
            root = nullptr
        }
    }else{                            //root is not a leaf
        while(i < root->nombre && cle > root->cles[i])
            i++;                  
        if(i < root->nombre && cle == root->cles[i]){ // cle exists in root
            if(root->fils[i]->nombre >= m){
                root->cles[i] = supp-pred(root->fils[i]);
            }else if(root->fils[i+1]->nombre >= m){
                root->cles[i+1] = supp-succ(root->fils[i+1]);
            }else{
                fussion-droite(root,i);
                root = supprimer-interne(root, cle);
            }
        }else{                                       // cle doesn't exist in root
            if(root->fils[i]->nombre >= m){          // no need to restructure the tree   
                root->fils[i] = supprimer-interne(root->fils[i], cle);
            }else{                                   // need to restructure tree
                if(i == 0){                          // there are no left child
                    if(root->fils[1]->nombre >= m){
                        emprunt-droite(root, 0);
                        root->fils[0] = supprimer-interne(root->fils[0], cle);
                    }else{
                        fussion-droite(root, 0);
                        root->fils[0] = supprimer-interne(root->fils[0], cle);
                    }
                }else{// (i > 0)                     // there is a left child 
                    if(root->fils[i-1]->nombre >= m){
                        emprunt-gauche(root, i);
                        root->fils[i+1] = supprimer-interne(root->fils[i+1], cle);
                    }else{
                        fussion-gauche(root, i);
                        root->fils[i-1] = supprimer-interne(root->fils[i-1], cle);
                    }
                }
            }
        }
    }
    return root;
}