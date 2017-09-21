#ifndef NTREE_H_INCLUDED
#define NTREE_H_INCLUDED
#include <fstream>
#include <sstream>
#define N 10

template <class T>
struct tnode
{
    T data;
    tnode* children[N];            //array of children tnodes
    tnode (const T& newData):data(newData)  //creates a tnode with a specified number of children nodes
    {
        for(int i = 0; i<N; i++)
            children[i] = NULL;
    }

    ~tnode() //deletes all of the children nodes
    {
        for(int i=0; i < N && children[i] ; i++)
            delete children[i];
    }

    tnode* addChild(const T& newData)
    {
        tnode* newNode = new tnode (newData);
        for(int i=0; i<N; i++)
            if(children[i] == NULL)
            {
               children[i] = newNode;
               break;
            }
        return newNode;
    }
};

template <class T>
class Ntree
{
    private:
        tnode<T>* root;
        
    public:
        Ntree():root(NULL){}
        Ntree(const T& data):root(new tnode<T>(data)){}
        ~Ntree()
        {
            delete root;
        }

        tnode<T>* getRoot()
        {
            return root;
        }

        void printTree(tnode<T> *r, std::string& s)
        {
            if(!r)
                return;
                
            s = s + r->data + "\n";
            
            for(int i=0; i < N && r->children[i] ; i++) {
                s = s + "/";
                printTree(r->children[i], s);
            }
                
            s = s + "/" + " ";
        }

        std::string toString()
        {
            std::string s;
            printTree(root, s);
            return s;
        }

        void toFile(tnode<T> *r, std::ofstream& doc)
        {
            if(!r)
                return;
            doc << r->data << " ";
            for(int i=0; i < N && r->children[i]; i++)
                toFile(r->children[i], doc);
            doc << "/" << " "; // marker that notifies that the there are no more childrenren
        }

        void serialize(const std::string& docpath)
        {
            std::ofstream doc;
            doc.open(docpath.c_str(), std::ios::out);
            toFile(root, doc);
            doc.close();
        }

        bool fromFile(tnode<T> *&r, std::ifstream& doc)
        {
            std::string st;
            if(!(doc >> st) || st == "/")
                return 1;
            r = new tnode<T>(st);
            for(int i=0; i < N; i++)
                if(fromFile(r->children[i],doc) == 1)
                    break;
            return 0;
        }

        void deserialize(const std::string& docpath)
        {
            std::ifstream doc;
            doc.open(docpath.c_str(), std::ios::in);
            fromFile(root, doc);
            doc.close();
        }

        bool operator == (const Ntree<T> &right) const
        {
             if(this->root->data == right.root->data)
                return true;
             else
                return false;
        }
};
#endif