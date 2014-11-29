#include <stdio.h>  
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;  

//preorder[0] is the root
//find preorder[0] in inorder
//then the left of preorder[0] in inorder is the left tree
//the right of preorder[0] in inorder is the right child tree
//then recursive

struct Binary_Tree 
{  
    int data;                   //node
    Binary_Tree *lchild;        //left child
    Binary_Tree *rchild;        //right child
}; 

//here to create a node whose data is ele
Binary_Tree *create_node(int ele) 
{  
    Binary_Tree *nd = new Binary_Tree;  
    nd->data = ele;  
    nd->lchild = NULL;  
    nd->rchild = NULL;  
    return nd;  
}

int find_ele(vector<int> vec, int begin, int end, int num) 
{  
    if (end < begin || begin < 0 || end >= vec.size())  
        return -1;  
    for (int i = begin; i <= end; i++) 
    {  
        if (vec[i] == num)  
            return i;  
    }  
    return -1;  
}

//here to use recursive to get root
Binary_Tree* get_root(vector<int> preorder, int p1, int p2, vector<int> inorder, int i1, int i2) 
{  
    if (p2 < p1 || p1 < 0 || p2 >= preorder.size() || 
    	i2 < i1 || i1 < 0 || i2 >= inorder.size())
    {  
        return NULL;  
    } 
    int node_data = preorder[p1]; 
    int pos = find_ele(inorder, i1, i2, node_data);  
    if (pos < 0) 
    {  
        return NULL;  
    }  
    Binary_Tree *nd = create_node(node_data);  
    nd->lchild = get_root(preorder, p1 + 1, p1 + pos - i1, inorder, i1, pos - 1);  
    nd->rchild = get_root(preorder, p1 + pos - i1 + 1, p2, inorder, pos + 1, i2);  
    return nd;  
}

//create a tree
Binary_Tree* create_tree(vector<int> preorder, vector<int> inorder) 
{   
    return get_root(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1);  
}

//postorder is in the result vector
void printpostorder(Binary_Tree* tree,vector<int>& result) 
{  
    if (tree == NULL)
    {
        return;  
    }
    printpostorder(tree->lchild,result);  
    printpostorder(tree->rchild,result);  
    result.push_back(tree->data);
    return;
}  
  
int main(int argc, char** argv) 
{  
    //ensure the input order is correct
    if (argc != 3)
    {
        cout<<"Please enter correct input and output filename."<<endl;
    }
    else
    {
        string input = argv[1];     //get input file
        string output = argv[2];    //get output file

        int num;
        int test_nums;              //the number of all test cases
        int current_nodes;          //the current case's nodes
        int judge = 1;    
        vector<int> all_case_nums;  //this vec saves all ints in the input file
        vector<int> preorder;       //preorder
        vector<int> inorder;        //inorder
        vector<int> result;         //result

        ifstream ist;
        ofstream ost;

        ist.open(input.c_str());
        ost.open(output.c_str());

        //if there is sth wrong when opening the input file,then cout this and quit
        if (!ist)
        {
            cout<<"No such input file,please check!"<<endl;
        }

        //run the program when everything is right
        else
        {
            while(ist >> num)
                all_case_nums.push_back(num);

            ist.close();

            test_nums = all_case_nums[0];

            while(judge < all_case_nums.size())
            {
                //before each test case starts,clear the preorder,inorder,result vector
                preorder.clear();
                inorder.clear();
                result.clear();
                current_nodes = all_case_nums[judge];
                for (int i = 0; i < current_nodes; ++i)
                {
                    judge++;
                    preorder.push_back(all_case_nums[judge]);
                }
                for (int i = 0; i < current_nodes; ++i)
                {
                    judge++;
                    inorder.push_back(all_case_nums[judge]);
                }

                //use pre and in order to create binary tree
                Binary_Tree* tree = create_tree(preorder, inorder);   
                //save its postorder into vector result
                printpostorder(tree,result);

                for (int i = 0; i < current_nodes; ++i)
                {
                    ost<<result[i]<<" ";
                }
                ost<<endl;

                judge++;
            }
            ost.close();
            cout<<"All answers were wrote into "<<output<<endl;
            cout<<"Please open it and check."<<endl;
        }
    }
    return 0;  
} 