typedef struct Noeud{
    int val;
    Noeud* fg;
    Noeud* fd;
    int balance;
};

typedef Noeud* AVL;

/*            x            y
  droite>>   / \          / \
            y   a        b   x
           / \              / \
          b   c            c   a
*/
AVL rotationDroite(AVL x){
    AVL y = x->fg;
    x->fg = y->fd;
    y->fd = x;
    int bx = x->balance, by = y->balance;
    x->balance = bx - 1 - max(0,by);
    if(bx>=0)
        y->balance = by - 1;
    else
        y->balance = bx - 2 + min(0,by);
    return y;
}
/*            x                y
             / \  <<gauche    / \
            a   y            x   c
               / \          / \
              b   c        a   b 
*/
AVL rotationGauche(AVL x){
    AVL y = x->fd;
    x->fd = y->fg;
    y->fg = x;
    int bx = x->balance, by = y->balance;
    x->balance = bx + 1 - min(0,by);
    if(bx>=0)
        y->balance = by - 1;
    else
        y->balance = bx + 2 + max(0,by);
    return y;
}

//             x   
//    <<gauche  \
//               y    
//              /  droite>>
//             c
AVL rotationDroiteGauche(AVL x){
    x->fd = rotationDroite(x->fd);
    return rotationGauche(x);
}
//             x   
//            /  droite>>   
//           y 
//  <<gauche  \     
//             b    
AVL rotationGaucheDroite(AVL x){
    x->fg = rotationGauche(x->fg);
    return rotationDroite(x);
}

// balance = hGauche - hDroite
AVL requilibrer(AVL x){
    if(x->balance>1){             //hGauche > hDroite
        if(x->fg->balance>=0)            //meme signe
            x = rotationDroite(x);       
        else                             //sinon
            x = rotationGaucheDroite(x); 
    }else if (x->balance<-1){     //hDroite > hGauche
        if(x->fd->balance<=0)            //meme signe
            x = rotationGauche(x);       
        else                             //sinon
            x = rotationDroiteGauche(x); 
    }
}

AVL inserer(AVL root, AVL elem, bool* change){
    if(root == nullptr){
        *change = true;
        return elem;
    }
    if(root->val <= elem->val){
        root->fd = inserer(root->fd, elem, change);
        if(*change)
            root->balance--;
    }else{
        root->fg = inserer(root->fg, elem, change);
        if(*change)
            root->balance++;
    }
    if(*change){
        requilibrer(root);
        if(root->balance == 0)
            *change = false;
        return root;
    }
}

AVL supprimer(AVL root, AVL elem, bool* change){
    if(root == nullptr)
        return nullptr;
    
    if(root->val < elem->val){
        root->fd = supprimer(root->fd, elem, change);
        if(*change){
            root->balance++;
            requilibrer(root);
            if(root->balance==0)
                change=false;
        }
    }else if (root->val > elem->val){
        root->fg = supprimer(root->fg, elem, change);
        if(*change){
            requilibrer(root);
            root->balance--;
            if(root->balance==0)
                change=false;
        }
    }
    else{ //root->val == elem->val
        if(root->fg == nullptr && root->fd == nullptr){
            return nullptr;
        }else if(root->fg != nullptr && root->fd != nullptr){
            root->fd = suppMin(root->fd, &elem, change);
            root->val = elem->val;
            if(*change){
                root->balance--;
                if(root->balance == 0)
                    *change = false;
            }
        }
        else if (root->fg != nullptr){
            *change == true;
            return root->fg->fg;    
        }else //(root->fd != nullptr){
            *change == true;
            return root->fd->fd;
    }
}

AVL suppMin(AVL root, AVL* elem, bool* change){
    if(root->fg == nullptr){
        (*elem)->val = root->val;
        return root->fd;
            
    }else{
        root->fg = suppMin(root->fg, elem, change);
        if(*change){
        root->balance ++;
        requilibrer(root);
        }
    }
    if(root->balance != 0){
        *change = false;
    }
    return root;
}

AVL insertRootIterative(AVL oldRoot, AVL elem){
    
}

int min(int x, int y){ return (x<=y)?x:y;}
int max(int x, int y){ return (x>=y)?x:y;}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AVL supprimerV2(AVL root, AVL elem, bool* change){
    if(root == nullptr)
        return nullptr;

    if(root->val > elem->val){
        root->fg = supprimer(root->fg, elem, change);
        if(*change){
            root->balance--;
            root = requilibrer(root);
        }
    }else if(root->val > elem->val){
        root->fd = supprimer(root->fd, elem, change);
        if(*change){
            root->balance++;
            root = requilibrer(root);
        }
    }else{
        if(root->fg == nullptr){
            *change = true;
            return root->fd;
        }
        if(root->fd == nullptr){
            *change = true;
            return root->fg;
        }
        root->fd = suppMinV2(root->fd, &elem, change);
        root->val = elem->val;
        if(*change){
            root->balance++;
            root = requilibrer(root);
        }
    }
    if(root->balance==0)
        *change = false;
    return root;
}

AVL suppMinV2(AVL root, AVL* elem, bool* change){
    if(root->fg == nullptr){
        (*elem)->val = root->val;
        *change == true;
        return root->fd;
    }else{
        root->fg = suppMinV2(root->fg, elem, change);
        if(*change){
            root->balance--;
            root = requilibrer(root);
        }
        if(root->balance==0)
            *change = false;
        return root;
    }
}
