//int D_Add(Tree *tree){
//    Node* node = (Node *) malloc(sizeof(Node));
//    int key;
//    Info *info = getInfo(&key);
//
//
//    if (info == NULL) return 0;
//
//    InfoSpace *infoSpace = (InfoSpace *) malloc(sizeof(InfoSpace));
//    infoSpace->current = info;
//    infoSpace->next = NULL;
//    node->key = key;
//    node->infospace = infoSpace;
//
//
//
//    if(tree->root == NULL){
//        node->infospace->rel = 0;
//        node->parent = NULL;
//        node->left = NULL;
//        node->right = NULL;
//        tree->root = node;
//    }
//    else{
//        Node *ptr = tree->root;
//        Node *par = NULL;
//        while(ptr != NULL){
//            par = ptr;
//            if(node->key < ptr->key){
//                ptr = ptr->left;
//            }
//            else{
//                ptr = ptr->right;
//            }
//        }
//
//        Node *n1 = NULL;
//        n1 = find(tree->root, &key);
//        if(n1 != NULL){
//            printf("inf = %d\n", n1->key);
//            node->infospace->rel = n1->infospace->rel +1;
//            node->infospace->next = n1->infospace;
//            n1->infospace = node->infospace;
//            free(node);
//            return 1;
//        }
//
//
//
//        if(node->key < par->key){
//            par->left = node;
//            node->infospace->rel = 0;
//            node->parent = par;
//            node->left = NULL;
//            node->right = NULL;
//        }
//        else if(node->key > par->key){
//            par->right = node;
//            node->infospace->rel = 0;
//            node->parent = par;
//            node->left = NULL;
//            node->right = NULL;
//        }
//
//    }
//    return 1;
//}
