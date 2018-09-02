#pragma once
#include<iostream>
#include<fstream>
using namespace std;

class Node;
class Element;
struct TiXmlAttribute
{
	char *name = NULL;
	int value;
	TiXmlAttribute *nextElement = NULL;
};

class Tinyxml
{
public:
	enum Model
	{
		in,
		out
	};
	Tinyxml(const char *filename, Model mod);
	~Tinyxml();
	
	enum Rela
	{
		brother,
		child
	};
	Node *open(const char *filename);
	void close();
	
	void Write(Node *node);
	void seek(const char *name, Node *parentNode);
	//void buildNode(const char *name, Rela realtion);
	Node *buildNode(const char *name, Node *&parentNode);
	void PRINT(Node *node);
	Node *RootNode();
	Node *seekBro(Node *node);
private:
	void write(Node *node, int num = 0);
	Node * root;
	Node * nextNode;
	fstream *fin;
	fstream *fout;
};

class Node
{
public:
	Node();
	Node(const char *str, Node *parent = NULL);
	~Node() {}
	
	void buildNode(const char *str,Node *parent=NULL,int val=0,Node *L=NULL,Node *R=NULL);
	char *name();
	int value();
	void Setvalue(int val);
	void insertChild(Node *child);
	void insertBrother(Node *bro);
	void linkParent(Node *parent);
	
	void cutChild(Node *child);
	void cutBrother(Node *bro);
	Node *NextSiblingNode();
	Node *FirstChildNode();
	Node *GetParent();
	void BulidElement(const char *ele);
	void PrintElements();
	TiXmlAttribute *FirstAttribute();
	bool operator==(Node &n1);
	Node &operator=(Node *n1);
private:
	void SetParent(Node *parent);
	char *Name;
	int Value;
	Node *L_Child;//子节点
	Node *R_Child;//兄弟节点
	Node *Parent;//父节点
	Element *elements;
};



class Element
{
	
public:
	Element(const char *ele);
	~Element() {}
	
	void read(const char *ele);
	void write(fstream fout);
	void build(int num);
	void Print();
	TiXmlAttribute *FirstAttribute();
private:
	TiXmlAttribute * head;
	int Num;
};

