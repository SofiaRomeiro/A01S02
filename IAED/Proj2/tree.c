#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "private.h"
#include "public.h"


tree_node_s treeConstructor(){
    tree_node_s new_tree = (tree_node_s)malloc(sizeof(struct tree_node));    
    new_tree->path = (char *)malloc(sizeof(char)*strlen(ROOT)+1);
    strcpy(new_tree->path, ROOT);
    new_tree->value = NULL;
    new_tree->brother = NULL;
    new_tree->child = NULL;
    new_tree->parent = NULL;
    return new_tree;
}

tree_node_s newTreeNode(char path[], char value[], tree_node_s parent){
    tree_node_s new_node = (tree_node_s) malloc(sizeof(struct tree_node)); 
    new_node->child = NULL;
    new_node->brother = NULL;
    new_node->parent = parent;
    new_node->path = (char *) malloc(sizeof(char) * (strlen(path)+1));
    strcpy(new_node->path, path);
    if (value != NULL) {
        new_node->value = (char *) malloc(sizeof(char) * (strlen(value)+1));
        strcpy(new_node->value, value);
         return new_node;
    } 
    new_node->value = NULL;   
    return new_node;
}

tree_node_s treeCompletlyDestructor(tree_node_s node) {
    tree_node_s aux;

    /* se ja é nulo , ver se todos os componentes sao nulos*/

    if (node == NULL) {
        return NULL;
    }

    /* se nao tem filhos nem irmao, pode apagar */
    /*if (node->child == NULL && node->brother == NULL) {
        free(node->path);
        free(node->value);
        free(node);
    }*/

    /* tem filhos ? */
    if (node->child != NULL) {
        /* sim! passa aos filhos */
        return treeCompletlyDestructor(node->child);

    }
    else {
        /* não! tem irmaos? */
        if (node->brother != NULL) {
            /* sim! ligar o pai ao irmao, e apagar o respetivo node (APAGA AQUI) */
            node->parent->child = node->brother;
            aux = node->brother;
            node->brother=NULL;
            node->child=NULL;
            if (node->child == NULL && node->brother == NULL) {
                free(node->path);
                free(node->value);
                free(node);
            }
            return treeCompletlyDestructor(aux);
        } 
        else {
            /* não! tem pai com irmaos?*/
            if (node->parent != NULL) {
                /*sim! dar return ao pai com irmaos (APAGAR AQUI)*/ 
                node->parent->child = NULL;
                aux = node->parent;
                if (node->child == NULL && node->brother == NULL) {
                    free(node->path);
                    free(node->value);
                    free(node);
                }
                return treeCompletlyDestructor(aux);
            }          
             /*nao! procurar o pai com irmaos (APAGAR AQUI) */

        }         
    }
    return NULL;
}


tree_node_s treePartialDestructor(tree_node_s node) {
    tree_node_s aux;


    /* se ja é nulo , ver se todos os componentes sao nulos*/

    if (node == NULL) {
        return NULL;
    }

    /* se nao tem filhos nem irmao, pode apagar */
    /*if (node->child == NULL && node->brother == NULL) {
        free(node->path);
        free(node->value);
        free(node);
    }*/

    /* tem filhos ? */
    if (node->child != NULL) {
        /* sim! passa aos filhos */
        return treePartialDestructor(node->child);

    }
    else {
        /* não! tem irmaos? */
        if (node->brother != NULL) {
            /* sim! ligar o pai ao irmao, e apagar o respetivo node (APAGA AQUI) */
            node->parent->child = node->brother;
            aux = node->brother;
            if (node->child == NULL && node->brother == NULL) {
                free(node->path);
                free(node->value);
                free(node);
            }
            return treePartialDestructor(aux);
        } 
       /* else {
             não! tem pai com irmaos?
            if (node->parent != NULL) {
                sim! dar return ao pai com irmaos (APAGAR AQUI) 
                node->parent->child = NULL;
                aux = node->parent;
                if (node->child == NULL && node->brother == NULL) {
                    printf("[treeDestructor] node will be destroyed! %s\n", node->path);
                    free(node->path);
                    free(node->value);
                    free(node);
                }
                return treeDestructor(aux);
            }          
             nao! procurar o pai com irmaos (APAGAR AQUI) 

        }     */     
    }
    return NULL;
}


void treeAdd(tree_node_s root) {  
    /* guardar o endereço da root sempre, so mexer no parent*/
    tree_node_s current = root;
    char *array;
    int j=0, found=0, size; 
    char c, input[MAX_PATH+1], value[MAX_PATH+1];

   while((c=getchar())!= EOF && c != '\n') {
       
       /* se for igual a espaço/tab e ainda nao tiver começado a ler, continuo */
        if ((c==' ') && !found) {
            continue;
        }

       /* se for igual a uma barra, vejo se o diretorio nao é vazio e adiciono novo node */
        else if (c == '/') {
            if (!strcmp(input, "")) {
                memset(input,'\0',MAX_PATH+1);
                j=0;
            }
            else {
                /* adicionar node */               
                input[j] = '\0';
                current = auxAddTree(current, input);
                memset(input,'\0',MAX_PATH+1);
                j=0;
            }
        }
        /* se for diferente de espaço/tab e diferente de barra,adiciono ao diretorio */
        else if (c != ' ' && c != '\t') {
            found = 1;
            input[j++] = c;
        }
        else if (c == ' ' && found){
            if (strcmp(input, "")) {
               /* adicionar node */ 
                input[j] = '\0';
                current = auxAddTree(current, input);
                j=0;
                break;
            }  
            else {
                break;
            } 
        }
    }
   
    j=0;
    /* quando o dir for NULL, chegámos ao fim, e o value pode ser adicionado ao ultimo child (acabar de ler o value do buffer, aproveitar o valor do i)  */

    while((c=getchar())!= EOF && c!= '\n') {
        input[j++] = c;
    }
    input[j] = '\0';

    

    array = strtok(input, " ");
   
    while( array != NULL ) {     
        strcat(value, array);   
        strcat(value, " ");
        array = strtok(NULL, " ");
    }
    

    size = strlen(value)-1;   
    value[size] = '\0'; 

    current->value = (char *) malloc(sizeof(char)*(strlen(value)+1));  
    strcpy(current->value, value);

    clear(value);
    clear(input);   
}

tree_node_s auxAddTree(tree_node_s parent, char path[]) {

    /*o parent do input sera colocado no campo "parent" do novo filho*/

    /* o filho que vou criar*/
    tree_node_s child;
    /* o irmao, caso nao exista ainda o path, que será o antecessor do novo node a criar com o path*/
    tree_node_s brother;

    /*verificar existem filhos*/

    if (parent->child != NULL) {
        /*existem, logo tenho de saber se o path a criar ja existe nos filhos*/
        
        brother = brotherSearch(parent->child, path); /*procurar o sitio onde esta o path(filho), se nao existir return NULL*/

        if (brother != NULL) {
            /* ja existe o filho, logo será o meu novo pai*/
            return brother;
        }
        else {
        /* nao existe ainda o path a criar, mas ja existem irmaos, logo vou procurar onde posso inserir*/  
            brother = brotherSearch(parent->child, NULL);
            child = newTreeNode(path, NULL, parent);
            brother->brother = child;  /*novo irmao do brother que retornei*/
            return child;
        }
    }
    else {
        /* se nao existirem, tenho de criar uma nova lista de filhos para o atual pai e adicionar o filho criado a primeira posicao*/
        child = newTreeNode(path, NULL, parent);
        parent->child = child;
        return child;
    }

    /*agora, o pai(atual) passa a ser o filho que acabei de criar (return no pai atual)*/
}

tree_node_s brotherSearch(tree_node_s current, char path[]) {
    /*procura a ver se existe algum no com o path igual ao do path(input)*/
    tree_node_s aux = current;
    /* procura a ver se existe algum node(child) com o path que quero criar*/
    if (path == NULL) {
        while (aux->brother != NULL) {
            aux = aux->brother;
        }
        return aux;
    }

    else {
        while (aux != NULL) {
            if (equals(aux->path, path))) {
                return aux;
            }
            aux = aux->brother;
        }
        return NULL;
    }    
   
}


tree_node_s treeSearch(tree_node_s root, char buffer[], list_ext_s extremes, list_node_s head) {
    tree_node_s current = root, aux;   

    /* fim -> o parent é NULL */

    if (current == NULL) { 
        printf("not found\n");       
        return NULL;
    }


    /*encontrou o valor, PARA tudo! */
    if (current->value != NULL && equals(current->value, buffer))) {
        printSearch(extremes);
        destroyList(extremes);
        return NULL;
    } 

    /* tem filhos ? */
        /* sim! passa para o proximo filho*/
    else if (current->child != NULL) {              
        head = insertEnd(extremes, head, current->child);       
        return treeSearch(current->child, buffer, extremes, head);
    }

    /* não! passa para o irmao*/
    else if (current->brother != NULL) {
        
        head = deleteEnd(extremes, head);
        head= insertEnd(extremes, head, current->brother);  
        return treeSearch(current->brother, buffer, extremes, head);
    }

    /*tem irmao e nao tem filhos? */   
    else {
        /* nao! procura um parent que tenha irmaos*/
        if (current->parent->brother == NULL) {
            /*stack = pop(stack);*/         
            
            /*current = findParent(current, stack);*/

            /* ---------------------------------------------*/
            aux = current;
            /* tenho de procurar um pai que tenha irmaos*/
            while (aux->parent != NULL) {
                /*encontrou um parent com irmao -> devolve esse irmao*/
                if (aux->brother != NULL) {
                    head= deleteEnd(extremes, head);
                    head= insertEnd(extremes, head, aux->brother);  
                    return treeSearch(aux->brother, buffer, extremes, head);
                }
                /* chegou à root*/
                else if (equals(aux->path, ROOT))) {
                    head= deleteEnd(extremes,head);
                    return treeSearch(aux, buffer, extremes, head);
                } 
                
                aux = aux->parent;
                head= deleteEnd(extremes, head);
            }
        }
            
        else {        
            head= deleteEnd(extremes, head);
            head= deleteEnd(extremes, head);
            head= insertEnd(extremes,head, current->parent->brother);
            return treeSearch(current->parent->brother, buffer, extremes, head);
        }
    }   
    printf("not found\n");
    return NULL; 
}   

void treeFind(tree_node_s root) {    
    tree_node_s current = root->child, previous;
    char *array, directory[MAX_PATH+1];  

    scanf("%s", directory);

    array = strtok(directory, "/"); 

    while (array != NULL) {

        current = brotherSearch(current, directory);
        /*se existir, passo ao filho como atual*/
        if (current != NULL) {
            previous = current;
            current = current->child;
        }
        else {
            /* se nao existir, lanço erro*/
            printf("not found\n");
            return;
        } 
        
        array = strtok(NULL, "/");
    }
    
    if (current->value == NULL) {
        printf("no data\n");
        return;
    }
    else{
        printf("%s\n", previous->value);
        return;
    }
}


/* TODO tree_print */

list_ext_s treePrint(tree_node_s root, list_ext_s extremes, list_node_s head) {

    tree_node_s current = root;
    list_node_s list = head;

    if (!strcmp(root->path, "/") && root->child==NULL && root->brother==NULL && root->parent==NULL) {
        return NULL;
    }
    
    /*current é nulo?*/
    if (current == NULL) {
        /* sim !! -> acaba o ciclo;*/
        return NULL;
    } 
        /* nao!! -> continua*/

    /* current tem valor?*/
    if (current->value != NULL) {
        /*sim !!
            print da stack
            continua*/
         
        printList(extremes);
        /*nao !!
            passa a frente*/
    }
    
    /* current tem filhos?*/
    

    if (current->child != NULL) {
        /*sim !!
            o que acontece à stack? coloca o proximo filho na stack*/
        list = insertEnd(extremes, list, current->child);
        
        /*passa ao filho*/
        return treePrint(current->child, extremes, list);
    }
   

    else {
        /*nao !!
       
        / tem irmaos ?*/
        if (current->brother != NULL) {
            /*sim !!
                o que acontece à stack? tiro o node atual e coloco o irmao na stack*/
            list = deleteEnd(extremes, list);
            list = insertEnd(extremes, list, current->brother);
            
            /*passa para o irmao*/
            return treePrint(current->brother, extremes, list);

        }
        else {
            /*nao !!
                o pai tem irmaos ?*/
           

            if (current->parent != NULL && current->parent->brother != NULL) {
                 
                /*sim!! 
                    o que acontece à stack? tira o atual e o pai do atual e coloca lá o irmao do pai do atual*/
                list = deleteEnd(extremes, list);                
                list = deleteEnd(extremes, list);
                list = insertEnd(extremes, list, current->parent->brother);
                
                /*passa para o irmao do pai*/
                return treePrint(current->parent->brother, extremes, list);                  

            }

             
            
            else {
            /*nao !!
                procurar o proximo pai que tenha irmaos*/            
                 
                while (current->brother == NULL) {  
                    
                    current = current->parent; 

                    if (current != NULL && !strcmp(current->path, "/")) {                        
                        
                        destroyList(extremes);
                        return NULL;
                    }                      
                    list = deleteEnd(extremes, list);                    
                    
                }               
                list = deleteEnd(extremes, list);   

                if (current->brother == NULL) {
                    destroyList(extremes);
                    return NULL;
                }

                list= insertEnd(extremes, list, current->brother);                
                return treePrint(current->brother, extremes, list);               

            }
        }
    }
    return NULL;
}

/*tree_node_s findParent(tree_node_s current, list_ext_s extremes) {
    tree_node_s aux = current;*/
    /* tenho de procurar um pai que tenha irmaos*/
   /* while (aux->parent != NULL) {*/
        /*encontrou um parent com irmao -> devolve esse irmao*/
      /*  if (aux->brother != NULL) { */
            /*stack = push(aux->brother, stack);*/
       /*     return aux->brother;
        }*/
        /*chegou à root*/
      /*  else if (!strcmp(aux->path, "/")) {
            return aux;
        } 
        
        aux = aux->parent;
        deleteEnd(extremes, head);
    }
    return NULL;
}*/



/* TODO tree_list */

void listRoot(tree_node_s root) {

    int num_of_nodes, i;
    tree_node_s aux = root->child;
    tree_node_s *sortList;

    num_of_nodes = countNodes(aux); 

    printf("[listRoot]nodes: %d\n", num_of_nodes); 

    sortList = malloc(sizeof(struct tree_node) * num_of_nodes);

    for (i=0; i < num_of_nodes && aux != NULL; i++, aux = aux->brother) {
        sortList[i] = aux;
    }

    quicksort(sortList, 0, num_of_nodes-1);

    for (i=0; i < num_of_nodes; i++) {
        printf("%s\n", sortList[i]->path);        
    }
    free(sortList);
}

void treeList(tree_node_s root, int args) {

    tree_node_s aux;
    char path[MAX_PATH+1];
   /*int i=0, found=0, stop_reading=0;
    char c;*/

    if (!args) {
        listRoot(root);
    }

    else {
       /* while ((c=getchar()) != '\n' && c != EOF) {
            if ((c==SPACE) && !found) {
                continue;
            } 
            else if ((c==SPACE) && found) {
                stop_reading=1;
            }
            else if (!stop_reading) {
                path[i++] = c;
                found=1;
            }
           
        }
        path[i] = '\0';*/
        

        fgets(path, 2000, stdin);
        path[strlen(path)-1] = '\0';
        printf("[treeList] |%s|\n", path);
        aux = nodeSearch(root, path);
        if (aux==NULL) {
            printf("not found\n");
            return;
            
        }
        listRoot(aux->parent);
    }
}

tree_node_s nodeSearch(tree_node_s root, char directory[]) {
    
    /* fim -> o parent é NULL*/

    tree_node_s current = root->child; 
    char *array;   

    /* se a len do buffer for 0, return da root */  
    printf("[nodeSearch]directory: |%s|\n", directory);

    array = strtok(directory, "/"); 

    while( array != NULL && !equals(array, ""))) {

        printf("[nodeSearch]array: |%s|\n", array);
        current = brotherSearch(current, array);


        /* se existir, passo ao filho como atual*/
        if (current != NULL) {
            current = current->child;
        } 
        array = strtok(NULL, "/");
    }
    return current;

}


tree_node_s treeDelete(tree_node_s root) {

    tree_node_s aux, finder, parent;
    char directory[200];

    aux = nodeSearch(root, directory);  

    if (aux==NULL) {
        printf("not found\n");
        return NULL;
    }

    if (equals(aux->path, ROOT))) {
        treeCompletlyDestructor(root);
        return NULL;
    }
    else {
        /*se for o primeiro filho dos pais, substituir pelo irmao (se houver) */

        /*se tiver irmaos e nao for o filho direto, procurar o irmao anterior*/
        if (!strcmp(aux->parent->child->path, aux->path)) {
            if (aux->brother != NULL) {
                aux->parent->child = aux->brother;
            }
            else {
                aux->parent->child = NULL;
            }
        }
        else {
            parent = aux->parent;
            finder = parent->child;
            aux->parent = NULL;
            while (strcmp(finder->brother->path, aux->path)) {
                finder = finder->brother;
            }
            finder->brother = aux->brother;
        }
        treePartialDestructor(aux);
        return NULL;       

    }
    return NULL;
}
