#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

/*Based on my test,my remove function costs about 50s to remove 50k data,
so,I think,the remove function should be right.
even though the time maybe a little longer when it comes to 200k data. 
*/

#include <iostream>        // For NULL
using namespace std;

// Red-black tree class
//
// CONSTRUCTION: with negative infinity object also
//               used to signal failed finds
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x (unimplemented)
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// bool isEmpty( )        --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class RedBlackTree
{
  public:
    /**
     * Construct the tree.
     * negInf is a value less than or equal to all others.
     */
    explicit RedBlackTree( const Comparable & negInf )
    {
        nullNode    = new RedBlackNode;
        nullNode->left = nullNode->right = nullNode;
        header      = new RedBlackNode( negInf );
        header->left = header->right = nullNode;
    }

    RedBlackTree( const RedBlackTree & rhs )
    {
        nullNode    = new RedBlackNode;
        nullNode->left = nullNode->right = nullNode;
        header      = new RedBlackNode( rhs.header->element );
        header->left = header->right = nullNode;
        *this = rhs;
    }

    ~RedBlackTree( )
    {
        makeEmpty( );
        delete nullNode;
        delete header;
    }

    const Comparable & findMin( ) const
    {
      if( isEmpty( ) ) {}
	  

        RedBlackNode *itr = header->right;

        while( itr->left != nullNode )
            itr = itr->left;

        return itr->element;
    }

    const Comparable & findMax( ) const
    {
      if( isEmpty( ) ){}

        RedBlackNode *itr = header->right;

        while( itr->right != nullNode )
            itr = itr->right;

        return itr->element;
    }

    bool contains( const Comparable & x ) const
    {
        nullNode->element = x;
        RedBlackNode *curr = header->right;

        for( ; ; )
        {
            if( x < curr->element )
                curr = curr->left;
            else if( curr->element < x )
                curr = curr->right;
            else
                return curr != nullNode;
        }
    }

    bool isEmpty( ) const
    {
        return header->right == nullNode;
    }

    void printTree( ) const
    {
        if( header->right == nullNode )
            cout << "Empty tree" << endl;
        else
            printTree( header->right );
    }

    void makeEmpty( )
    {
        reclaimMemory( header->right );
        header->right = nullNode;
    }

    /**
     * Insert item x into the tree. Does nothing if x already prsent.
     */
    void insert( const Comparable & x )
    {
        current = parent = grand = header;
        nullNode->element = x;

        while( current->element != x )
        {
            great = grand; grand = parent; parent = current;
            current = x < current->element ?  current->left : current->right;

                // Check if two red children; fix if so
            if( current->left->color == RED && current->right->color == RED )
                handleReorient( x );
        }

            // Insertion fails if already present
        if( current != nullNode )
            return;
        current = new RedBlackNode( x, nullNode, nullNode );

            // Attach to parent
        if( x < parent->element )
            parent->left = current;
        else
            parent->right = current;
        handleReorient( x );
    }

    //here is my remove code
    void remove( const Comparable & x )
    {
        //since I add parent in struct RedBlackNode,
        //so I need to set every node's parent here
        setParent(header);
        //find(x) is to find the delete node
        RedBlackNode* delete_point = find(x);
        //if delete node doesn't exist,just return  
        if(delete_point == nullNode)  
            return;  
        //if delete node has two childs
        if(delete_point->left != nullNode && delete_point->right != nullNode)  
        {  
            RedBlackNode* successor = InOrderSuccessor(delete_point);    
            delete_point->element = successor->element;  
            delete_point = successor;  
        }  
        RedBlackNode* delete_point_child;  
        if(delete_point->right != nullNode)  
        {  
            delete_point_child = delete_point->right;  
        }  
        else if(delete_point->left != nullNode)  
        {  
            delete_point_child = delete_point->left;  
        }  
        else  
        {  
            delete_point_child = nullNode;  
        }  
        delete_point_child->parent = delete_point->parent;

        //if delete root node
        if(delete_point->parent == nullNode)  
        {  
            header = delete_point_child;  
            nullNode->parent = header;  
            nullNode->left = header;  
            nullNode->right = header;  
        }  
        else if(delete_point == delete_point->parent->right)  
        {  
            delete_point->parent->right = delete_point_child;  
        }  
        else  
        {  
            delete_point->parent->left = delete_point_child;  
        }
        //need to fix up at last  
        if(delete_point->color == BLACK && !(delete_point_child == nullNode && 
                                        delete_point_child->parent == nullNode))  
        {  
            DeleteFixUp(delete_point_child);  
        }  
        //delete delete_point;
        return; 
    }

    enum { RED, BLACK };

    const RedBlackTree & operator=( const RedBlackTree & rhs )
    {
        if( this != &rhs )
        {
            makeEmpty( );
            header->right = clone( rhs.header->right );
        }

        return *this;
    }

  private:
    struct RedBlackNode
    {
        Comparable    element;
        RedBlackNode *left;
        RedBlackNode *right;
        RedBlackNode *parent;       //parent is the current node's parent
        int           color;

        RedBlackNode( const Comparable & theElement = Comparable( ),
                            RedBlackNode *lt = NULL, RedBlackNode *rt = NULL,
                            int c = BLACK )
          : element( theElement ), left( lt ), right( rt ), color( c ),parent(NULL) { }
    };

    RedBlackNode *header;   // The tree header (contains negInf)
    RedBlackNode *nullNode;

        // Used in insert routine and its helpers (logically static)
    RedBlackNode *current;
    RedBlackNode *parent;
    RedBlackNode *grand;
    RedBlackNode *great;

        // Usual recursive stuff
    void reclaimMemory( RedBlackNode *t )
    {
        if( t != t->left )
        {
            reclaimMemory( t->left );
            reclaimMemory( t->right );
            delete t;
        }
    }

    void printTree( RedBlackNode *t ) const
    {
        if( t != t->left )
        {
            printTree( t->left );
            cout << t->element << endl;
            printTree( t->right );
        }
    }

    RedBlackNode * clone( RedBlackNode * t ) const
    {
        if( t == t->left )  // Cannot test against nullNode!!!
            return nullNode;
        else
            return new RedBlackNode( t->element, clone( t->left ),
                                     clone( t->right ), t->color );
    }

        // Red-black tree manipulations
    /**
     * Internal routine that is called during an insertion if a node has two red
     * children. Performs flip and rotatons. item is the item being inserted.
     */
    void handleReorient( const Comparable & item )
    {
            // Do the color flip
        current->color = RED;
        current->left->color = BLACK;
        current->right->color = BLACK;

        if( parent->color == RED )   // Have to rotate
        {
            grand->color = RED;
            if( item < grand->element != item < parent->element )
                parent = rotate( item, grand );  // Start dbl rotate
            current = rotate( item, great );
            current->color = BLACK;
        }
        header->right->color = BLACK; // Make root black
    }

    /**
     * Internal routine that performs a single or double rotation.
     * Because the result is attached to the parent, there are four cases.
     * Called by handleReorient.
     * item is the item in handleReorient.
     * theParent is the parent of the root of the rotated subtree.
     * Return the root of the rotated subtree.
     */
    RedBlackNode * rotate( const Comparable & item, RedBlackNode *theParent )
    {
        if( item < theParent->element )
        {
            item < theParent->left->element ?
                rotateWithLeftChild( theParent->left )  :  // LL
                rotateWithRightChild( theParent->left ) ;  // LR
            return theParent->left;
        }
        else
        {
            item < theParent->right->element ?
                rotateWithLeftChild( theParent->right ) :  // RL
                rotateWithRightChild( theParent->right );  // RR
            return theParent->right;
        }
    }

    void rotateWithLeftChild( RedBlackNode * & k2 )
    {
        RedBlackNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2 = k1;
    }

    void rotateWithRightChild( RedBlackNode * & k1 )
    {
        RedBlackNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1 = k2;
    }

    //private funcs for delete part
    RedBlackNode* find( const Comparable & x ) const
    {  
        RedBlackNode* index = header;  
        while(index != nullNode)  
        {  
            if(x < index->element)     
            {  
                index  = index->left;  //smaller than current,go left  
            }  
            else if(x > index->element)  
            {  
                index = index->right;  //biger than current,go right  
            }  
            else  
            {  
                break;  
            }  
        }  
        return index;  
    }

    void setParent(RedBlackNode* x) 
    {    
        if (x == nullNode)
            return;
        x->left->parent = x;
        x->right->parent = x;
        setParent(x->left);
        setParent(x->right);
    }  

    //since add parent in the RedBlackNode,the two rotate func need to be rewrote
    //left rotate
    void rotate_left(RedBlackNode* node)  
    {  
        if(node == nullNode || node->right == nullNode)  
        {  
            return;     //can't rotate  
        }  
        RedBlackNode* lower_right = node->right;  
        lower_right->parent = node->parent;  
        node->right=lower_right->left;  
        if(lower_right->left != nullNode)  
        {  
            lower_right->left->parent = node;  
        }  
        if(node->parent == nullNode) //rotate node is root  
        {  
            header = lower_right;  
            nullNode->left = header;  
            nullNode->right= header;  
            //m_nullNode->parent = m_root;  
        }  
        else  
        {  
            if(node == node->parent->left)  
            {  
                node->parent->left = lower_right;  
            }  
            else  
            {  
                node->parent->right = lower_right;  
            }  
        }  
        node->parent = lower_right;  
        lower_right->left = node;  
    }  
      
    //right rotate 
    void rotate_right(RedBlackNode* node)  
    {  
        if(node == nullNode || node->left == nullNode)  
        {  
            return;     //can't rotate  
        }  
        RedBlackNode* lower_left = node->left;  
        node->left = lower_left->right;  
        lower_left->parent = node->parent;  
        if(lower_left->right != nullNode)  
        {  
            lower_left->right->parent = node;  
        }  
        if(node->parent == nullNode) //node is root  
        {  
            header = lower_left;  
            nullNode->left = header;  
            nullNode->right = header;  
            //m_nullNode->parent = m_root;  
        }  
        else  
        {  
            if(node==node->parent->right)  
            {  
                node->parent->right = lower_left;  
            }  
            else  
            {  
                node->parent->left = lower_left;  
            }  
        }  
        node->parent = lower_left;  
        lower_left->right = node;  
    }  

    //if the delete node has two childs,then need to find the success node
    RedBlackNode* InOrderSuccessor(RedBlackNode* node)  
    {  
        if(node == nullNode)       //null node has no successor  
        {  
            return nullNode;  
        }  
        RedBlackNode* result = node->right;   //get node's right node  
        while(result != nullNode)        //try to find node's right subtree's left most node  
        {  
            if(result->left != nullNode)       
            {  
                result = result->left;  
            }  
            else  
            {  
                break;  
            }  
        }                              //after while loop result==null or result's left child is null  
        if(result == nullNode)  
        {  
            RedBlackNode* index = node->parent;  
            result = node;  
            while(index != nullNode && result == index->right)  
            {  
                result = index;  
                index = index->parent;  
            }  
            result = index;         //first parent's left or null  
        }  
        return result;  
    }  

    //get the sibling of the node n
    RedBlackNode* get_sibling(RedBlackNode* n)
    {
        if (n == n->parent->left)
            return n->parent->right;
        else
            return n->parent->left;
    }

    //here is six cases for delete
    //case1: n is the root
    void delete_case1(RedBlackNode* n)
    {
        if (n->parent != NULL)
            delete_case2(n);
    }

    //case2: n's sibling s is RED
    void delete_case2(RedBlackNode* n)
    {
        RedBlackNode*s = get_sibling(n);
 
        if (s->color == RED) 
        {
            n->parent->color = RED;
            s->color = BLACK;
            if (n == n->parent->left)
                rotate_left(n->parent);
            else
                rotate_right(n->parent);
        }
        delete_case3(n);
    }

    //case3: n's sibling s is BLACK,
    //s'two childs are BLACK,
    //n's parent p is BLACK
    void delete_case3(RedBlackNode* n)
    {
        RedBlackNode*s = get_sibling(n);
 
        if ((n->parent->color == BLACK) &&
            (s->color == BLACK) &&
            (s->left->color == BLACK) &&
            (s->right->color == BLACK)) 
        {
            s->color = RED;
            delete_case1(n->parent);
        } 
        else
            delete_case4(n);
    }

    //case4: n's sibling s is BLACK,
    //s'two childs are BLACK,
    //n's parent p is RED
    void delete_case4(RedBlackNode* n)
    {
        RedBlackNode*s = get_sibling(n);
        if ((n->parent->color == RED) &&
            (s->color == BLACK) &&
            (s->left->color == BLACK) &&
            (s->right->color == BLACK)) 
        {
            s->color = RED;
            n->parent->color = BLACK;
        } 
        else
            delete_case5(n);
    }

    //case5: n's sibling s is BLACK,
    //s'left child is RED,
    //s'right child is BLACK,
    //n is its parent's left child
    void delete_case5(RedBlackNode* n)
    {
        RedBlackNode*s = get_sibling(n);
        if  (s->color == BLACK)
        {
            if ((n == n->parent->left) &&
                (s->right->color == BLACK) &&
                (s->left->color == RED)) 
            {
                s->left->color = BLACK;
                rotate_right(s);
            } 
            else if ((n == n->parent->right) &&
                    (s->left->color == BLACK) &&
                    (s->right->color == RED)) 
            {
                s->color = RED;
                s->right->color = BLACK;
                rotate_left(s);
            }
        }
        delete_case6(n);
    }

    //case6: n's sibling s is BLACK,
    //s'right child is RED,
    //n is its parent's left child
    void delete_case6(RedBlackNode* n)
    {
        RedBlackNode*s = get_sibling(n);
 
        s->color = n->parent->color;
        n->parent->color = BLACK;
 
        if (n == n->parent->left) 
        {
            s->right->color = BLACK;
            rotate_left(n->parent);
        } 
        else 
        {
            s->left->color = BLACK;
            rotate_right(n->parent);
        }
    }

    //a whole function for delete fix up
    void DeleteFixUp(RedBlackNode* n)
    {
        delete_case1(n);
    }
};

#endif
