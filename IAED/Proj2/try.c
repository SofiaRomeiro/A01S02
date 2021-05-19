#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "public.h"
#include "private.h"

tree_node_s treeDelete(tree_node_s root) {

	tree_node_s current, toFree;

    //apago quando o irmao e o filho são nulos

	//volto para o pai


    //current é nulo?
    if (current == NULL) {
        // sim !! -> acaba o ciclo;
        return NULL;
    } 

		//nao é nulo!!
    
    // current tem filhos?

    if (current->child != NULL) {
        //sim
        //passa ao filho
        return treeDelete(current->child);
    }

    else {
        //nao !!
                  
        // tem irmaos ?
        if (current->brother != NULL) {
            //sim !!
           
            //passa para o irmao
            return treeDelete(current->brother);

        }
        else {
            //nao !! -> apagar este 

            // regressa ao pai para processar os irmaos do pai

			toFree = current;


            if (current->parent != NULL) {
                //sim!! 
                // passa para o pai e da free no atual
				free(toFree->path);
                free(toFree->value);
                free(toFree);    

                return treeDelete(current->parent);                    

            }
        }
    }
}
