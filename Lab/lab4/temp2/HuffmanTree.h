#ifndef _huffmantree_h
#define _huffmantree_h

#include <map>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

#define UINT unsigned int 

class HuffmanNode
{
  public:
    UINT ch;
    int frequency;
    HuffmanNode *left;
    HuffmanNode *right;
    HuffmanNode *parent;

    HuffmanNode(UINT c,int f, HuffmanNode *l = NULL, HuffmanNode *r = NULL, HuffmanNode *p = NULL):
            ch(c),frequency(f),left(l),right(r),parent(p) {}
};

class HuffmanTree 
{
  private:
    HuffmanNode *root;
    vector<HuffmanNode*> forest;
  public:
    HuffmanTree(vector<pair<UINT,int> > all_chars); 
    ~HuffmanTree();
    map<UINT,string> huffmancode;
    HuffmanNode* get_root();
    void resort_forest();
    void createTree();
    void SetHuffmanCode(HuffmanNode* root,char* result,int deep);
};

HuffmanTree::HuffmanTree(vector<pair<UINT,int> > all_chars)
{
  //cout<<"----------"<<endl;
  for (int i = 0; i < all_chars.size(); ++i)
  {  
      HuffmanNode* temp_root = new HuffmanNode(all_chars[i].first,all_chars[i].second);
      forest.push_back(temp_root);
  } 
  //cout<<"----------"<<endl; 
  //resort_forest();
  // cout<<"----------"<<endl;
  // for (int i = 0; i < forest.size(); ++i)
  // {
  //   cout<<forest[i]->ch<<": "<<forest[i]->frequency<<endl;
  // }
  createTree();
}

HuffmanNode* HuffmanTree::get_root()
{
  return root;
}

void HuffmanTree::resort_forest()
{
  int count = forest.size();

  if (count == 1)
  {
    return;
  }

  HuffmanNode* temp = forest[count-1];
  if (temp->frequency < forest[0]->frequency)
  {
    for (int j = count-1; j > 0; --j)
    {
      forest[j] = forest[j-1];
    }
    forest[0] = temp;
    for (int i = 0; i < forest.size(); ++i)
    {
      cout<<forest[i]->frequency<<" ";
    }
    cout<<endl;
    return;
  }
  if (temp->frequency > forest[count-2]->frequency)
  {
    for (int i = 0; i < forest.size(); ++i)
    {
      cout<<forest[i]->frequency<<" ";
    }
    cout<<endl;
    return;
  }
  for (int i = 0; i < count-1; ++i)
  {
    if (forest[i]->frequency == temp->frequency)
    {
      for (int j = count-1; j > i; --j)
      {
        forest[j] = forest[j-1];
      }
      forest[i] = temp;
      for (int i = 0; i < forest.size(); ++i)
      {
        cout<<forest[i]->frequency<<" ";
      }
      cout<<endl;
      return;
    }
  }
  for (int i = 0; i < count-2; ++i)
  {
    if (forest[i]->frequency < temp->frequency &&
        forest[i+1]->frequency > temp->frequency)
    {
      for (int j = count-1; j > i+1; --j)
      {
        forest[j] = forest[j-1];
      }
      forest[i+1] = temp;
      for (int i = 0; i < forest.size(); ++i)
      {
        cout<<forest[i]->frequency<<" ";
      }
      cout<<endl;
      return;
    }
  }
}

void HuffmanTree::createTree()
{
  HuffmanNode* left;
  HuffmanNode* right;
  HuffmanNode* parent;

  //cout<<"----------"<<endl;
  while(forest.size() != 1)
  {
    left = forest[0];
    right = forest[1];

    parent = new HuffmanNode(32,(left->frequency + right->frequency), left, right, NULL);
    left->parent = parent;
    right->parent = parent;
    forest.erase(forest.begin());
    forest.erase(forest.begin());
    forest.push_back(parent);
    //cout<<"----------"<<endl;
    resort_forest();
  }
  root = parent;
}

void HuffmanTree::SetHuffmanCode(HuffmanNode* root,char* result,int deep)
{
  //cout<<root->left->ch<<": "<<root->left->frequency<<endl;
  //cout<<root->right->ch<<": "<<root->right->frequency<<endl;
  if(root->left == NULL && root->right == NULL)
  {
    //cout<<"------"<<endl;
      string temp = "";
      for (int i = 0; i < deep; ++i)
      {
        temp += result[i];
      }
      cout<<temp<<endl;
      huffmancode[root->ch] = temp;
      if (root->parent->left->left == NULL && root->parent->left->right == NULL
          && root->parent->right->left == NULL && root->parent->right->right == NULL)
      {
        return;
      }
  }
  //cout<<"------"<<endl;
  result[deep] = '0';
  if(root->left != NULL)
  {
      //cout<<"root->left != NULL"<<endl;
      SetHuffmanCode(root->left,result, deep + 1);
      //SetHuffmanCode(root->right,result, deep + 1);
  }
  // else
  //   cout<<"root->left == NULL"<<endl;
  result[deep] = '1';
  if(root->right != NULL)
  {
      //cout<<"root->right != NULL"<<endl;
      //SetHuffmanCode(root->left,result, deep + 1);
      SetHuffmanCode(root->right,result, deep + 1);
  }
  // else
  //   cout<<"root->left == NULL"<<endl;
}

HuffmanTree::~HuffmanTree()
{
  cout<<"hello"<<endl;
  huffmancode.clear();
  forest.clear();
  delete root;
}

#endif