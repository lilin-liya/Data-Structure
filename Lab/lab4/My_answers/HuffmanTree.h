#ifndef _huffmantree_h
#define _huffmantree_h

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <bitset>

using namespace std;

/*This is the file for HuffmanTree class and some functions I used*/

#define UINT unsigned int 

//HuffmanNode
class HuffmanNode
{
  public:
    UINT ch;              //the char at each node,here use unsigned int instead of char
    int frequency;        //the frequency of each char
    HuffmanNode *left;    //left child
    HuffmanNode *right;   //right child
    HuffmanNode *parent;  //parent

    HuffmanNode(UINT c,int f, HuffmanNode *l = NULL, HuffmanNode *r = NULL, HuffmanNode *p = NULL):
            ch(c),frequency(f),left(l),right(r),parent(p) {}
};

//HuffmanTree 
class HuffmanTree 
{
  private:
    HuffmanNode *root;            //the tree's root 
    HuffmanNode *copy_root;       //also the tree's root ,just for the GetoriginChar() function;
    vector<HuffmanNode*> forest;  //the tree forest
  public:
    HuffmanTree(vector<pair<UINT,int> > all_chars); 
    ~HuffmanTree();
    map<UINT,string> huffmancode; //this map stores the unique chars and their huffmancode
    vector<UINT> chars_get;       //this vec stores all chars in the inputfile
    HuffmanNode* get_root();      //return root
    void resort_forest();         //after each merge ,need to sort the forest vec again
    void createTree();            
    void SetHuffmanCode(HuffmanNode* root,char* result,int deep);   //set huffmancode
    void GetoriginChar(HuffmanNode* root,string& str,int deep);     //get char from huffmancode
};

HuffmanTree::HuffmanTree(vector<pair<UINT,int> > all_chars)
{
  //init the forest
  for (int i = 0; i < all_chars.size(); ++i)
  {  
      HuffmanNode* temp_root = new HuffmanNode(all_chars[i].first,all_chars[i].second);
      forest.push_back(temp_root);
  } 
  createTree();
}

HuffmanNode* HuffmanTree::get_root()
{
  return root;
}

//resort the forest,since the forest is sorted from small to big before,
//so,just need to deal with the last element in the forest
void HuffmanTree::resort_forest()
{
  int count = forest.size();

  if (count == 1)
  {
    return;
  }

  HuffmanNode* temp = forest[count-1];
  //if the merged fre is smaller than any fre in the forest
  if (temp->frequency < forest[0]->frequency)
  {
    for (int j = count-1; j > 0; --j)
    {
      forest[j] = forest[j-1];
    }
    forest[0] = temp;
    return;
  }
  //if the merged fre is biger than any fre in the forest
  if (temp->frequency > forest[count-2]->frequency)
  {
    return;
  }
  //if the merged fre equals some fre in the forest
  for (int i = 0; i < count-1; ++i)
  {
    if (forest[i]->frequency == temp->frequency)
    {
      for (int j = count-1; j > i; --j)
      {
        forest[j] = forest[j-1];
      }
      forest[i] = temp;
      return;
    }
  }
  //if the merged fre is smaller than some fre and biger than another fre in the forest
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
      return;
    }
  }
}

void HuffmanTree::createTree()
{
  HuffmanNode* left;
  HuffmanNode* right;
  HuffmanNode* parent;

  //continue untill the forest only has one tree
  while(forest.size() > 1)
  {
    //we can get left,right,because the forest is sorted
    left = forest[0];
    right = forest[1];

    //for every merged node,I use 32(space) as its char
    parent = new HuffmanNode(32,(left->frequency + right->frequency), left, right, NULL);
    left->parent = parent;
    right->parent = parent;
    forest.erase(forest.begin());
    forest.erase(forest.begin());
    forest.push_back(parent);
    resort_forest();
  }
  //set root and copy_root
  root = parent;
  copy_root = root;
}

void HuffmanTree::SetHuffmanCode(HuffmanNode* root,char* result,int deep)
{
  //every time arrive at a node,get the char and its huffmancode
  if(root->left == NULL && root->right == NULL)
  {
      string temp = "";
      for (int i = 0; i < deep; ++i)
      {
        temp += result[i];
      }
      huffmancode.insert(pair<UINT,string>(root->ch,temp));
      return;
  }
  //left is '0'
  result[deep] = '0';
  if(root->left != NULL)
  {
      SetHuffmanCode(root->left,result, deep + 1);
  }
  //right is '1'
  result[deep] = '1';
  if(root->right != NULL)
  {
      SetHuffmanCode(root->right,result, deep + 1);
  }
}

void HuffmanTree::GetoriginChar(HuffmanNode* root,string& str,int deep)
{
  //when str is empty,return
  if (str.length() == 0)
  {
    return;
  }
  //every time arrive at a node,get the char from its huffmancode
  if (root->left == NULL && root->right == NULL)
  {

    chars_get.push_back(root->ch);
    //set the current node as the root of the tree
    root = copy_root;
    //erase the chars we just searched before
    //so the str can become shorter and shorter
    for (int i = 0; i < deep; ++i)
    {
      str.erase(str.begin());
    }
    GetoriginChar(root,str,0);
    return;
  }
  //if meet '0',go left
  if (str[deep] == '0' && root->left != NULL)
  {
    GetoriginChar(root->left,str,deep+1);
  }
  //if meet '1',go right
  if (str[deep] == '1' && root->right != NULL)
  {
    GetoriginChar(root->right,str,deep+1);
  }
}

HuffmanTree::~HuffmanTree()
{
  huffmancode.clear();
  forest.clear();
  chars_get.clear();
}

//The following two functions are to sort a map by value
int cmp(const pair<UINT,int>& x, const pair<UINT,int>& y)  
{  
  return x.second < y.second;  
}  
   
void sortMapByValue(const map<UINT,int>& tMap, vector<pair<UINT,int> >& tVector)  
{  
  for (map<UINT,int>::const_iterator curr = tMap.begin(); curr != tMap.end(); curr++)  
  {  
    tVector.push_back(pair<UINT,int>(curr->first, curr->second));  
  }
   
  sort(tVector.begin(), tVector.end(), cmp);  
}  

//compress function
void compress(string inputFilename, string outputFilename) 
{
  string result_str = "";           //all chars in the inputfile turn into 0/1 strings
  map<UINT,int> test;               //this map is to count each unique char's frequency,
                                    //UINT is the char,int is the frequency
  vector<pair<UINT,int> > vec;      //vec is for the map sorted by value
  map<UINT,string>::iterator its;
  map<UINT,int>::iterator itc;

  ifstream ifs(inputFilename.c_str(), ios::in | ios::binary);
  ofstream ofs(outputFilename.c_str(), ios::out | ios::binary);
  char c;
  int char_nums = 0;    //get the num of chars in the inputfile,so we can malloc reasonable space
  while (ifs.get(c)) 
  {
    test[c]++;          //get the chars from the file
    char_nums++;
  }
  ifs.close();

  char* result = (char *)malloc(4 * char_nums);

  sortMapByValue(test,vec);   //sort map by value,so the HuffmanTree can get a sorted vec as input

  HuffmanTree huffmantree(vec);

  //in case the inputfile is empty
  if (vec.size() > 0)
  {
    huffmantree.SetHuffmanCode(huffmantree.get_root(),result,0);
  }

  //now read inputfile again to get each char's HuffmanCode,add to result_str
  ifs.open(inputFilename.c_str(), ios::in | ios::binary);
  while (ifs.get(c)) 
  {
    result_str += huffmantree.huffmancode[c];
  }
  ifs.close();

  unsigned char outbyte;      //every time up to 8 bits,turn to outbyte and write into outputfile
  unsigned char lackbits = 0; //since at most time,(the total bits % 8 != 0 ),
                              //so we need to add some 0 at the end of the result_str
                              //lackbits is how many 0 we add at the end

  //write result_str_len into outputfile
  int result_str_len = result_str.length();
  ofs.write((char *)&result_str_len,sizeof(int));

  //write how many unique chars into outputfile
  int unique_char_nums = test.size();
  ofs.write((char *)&unique_char_nums,sizeof(int));

  unsigned char temp_char;
  int temp_char_fre;

  //write unique chars into outputfile
  for (int i = 0; i < vec.size(); i++)
  {
    temp_char = vec[i].first;
    ofs.write((char *)&temp_char,sizeof(unsigned char));
  }
  //write the frequency of each unique char into outputfile
  for (int i = 0; i < vec.size(); i++)
  {
    temp_char_fre = vec[i].second;
    ofs.write((char *)&temp_char_fre,sizeof(int));
  } 

  //deal with result_str,and write it into outputfile
  if (result_str.length() % 8 == 0)
  {
    for (int i = 0; i < result_str.length(); i += 8)
    {
       outbyte='\0';
       for (int j = 0; j < 8; ++j)
       {
          outbyte = outbyte << 1;
          if (result_str[j+i] == '1')
             outbyte |= 1;
       }
       lackbits = 0;
       ofs.write((char *)&outbyte,sizeof(unsigned char));
    }
  }
  else
  {
    lackbits =  8 - (result_str.length() - ((result_str.length() / 8) * 8));
    for (int i = 0; i < lackbits; ++i)
    {
      result_str += "0";
    }
    for (int i = 0; i < result_str.length(); i += 8)
    {
       outbyte='\0';
       for (int j = 0; j < 8; ++j)
       {
          outbyte = outbyte << 1;
          if (result_str[j+i] == '1')
             outbyte |= 1;
       }
       ofs.write((char *)&outbyte,sizeof(unsigned char));
    }
  }
  //at last ,write lackbits into outputfile
  ofs.write((char *)&lackbits,sizeof(unsigned char));
  ofs.close();
}

//decompress function
void decompress(string inputFilename, string outputFilename) 
{
  ifstream ifs(inputFilename.c_str(), ios::in | ios::binary);
  ofstream ofs(outputFilename.c_str(), ios::out | ios::binary);

  int int_num;               //to read int from inputfile
  unsigned char temp_num;    //to read unsigned char from inputfile
  UINT result_str_len;      
  UINT unique_char_nums;
  UINT temp_char;
  UINT temp_char_fre;
  vector<UINT> char_vec;
  vector<UINT> char_fre_vec;

  //first read the result_str_len
  ifs.read((char*)&int_num, sizeof(int));
  result_str_len = int_num;

  //then read the unique_char_nums
  ifs.read((char*)&int_num, sizeof(int));
  unique_char_nums = int_num;

  //then according to the unique_char_nums,read the unique chars and their frequency
  for (int i = 0; i < unique_char_nums*8; i += 8)
  {
    ifs.read((char*)&temp_num, sizeof(unsigned char));
    temp_char = temp_num;
    char_vec.push_back(temp_char);
  }
  for (int i = 0; i < unique_char_nums*8; i += 8)
  {
    ifs.read((char*)&int_num, sizeof(int));
    temp_char_fre = int_num;
    char_fre_vec.push_back(temp_char_fre);
  }

  //now,create a vec like the vec in the compress part
  vector<pair<UINT,int> > vec; 
  for (int i = 0; i < unique_char_nums; ++i)
  {
    vec.push_back(pair<UINT,int>(char_vec[i],char_fre_vec[i]));
  }

  HuffmanTree huffmantree(vec);

  //here according to the result_str_len,read the result_str
  string result_str = "";
  for (int i = 0; i < result_str_len; i+=8)
  {
    ifs.read((char*)&temp_num, sizeof(unsigned char));
    UINT each_char = temp_num;
    //use bitset to simplify read
    bitset<8> bitvec(each_char);
    result_str += bitvec.to_string();
  }

  //at last,read lackbits
  ifs.read((char*)&temp_num, sizeof(unsigned char));
  UINT lackbits = temp_num;
  //according to lackbits,get the original result_str without adding anything
  for (int i = 0; i < lackbits; ++i)
  {
    result_str.erase(result_str.end()-1);
  }

  //now,can get the char according to the HuffmanCode in result_str
  huffmantree.GetoriginChar(huffmantree.get_root(),result_str,0);
  for (int i = 0; i < huffmantree.chars_get.size(); ++i)
  {
    char c = huffmantree.chars_get[i];
    //write into the outputfile
    ofs.put(c);
  }

  ifs.close();
  ofs.close();
}

void usage(string prog) 
{
  cerr << "Usage: " << endl
      << "    " << prog << "[-d] input_file output_file" << endl;
  exit(2);
}

#endif