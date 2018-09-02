#include "stdafx.h"
#include "tinyxml.h"
#include"Mystring.h"




Tinyxml::Tinyxml(const char * filename, Model mod)
{
	cout << "sussceeful create class Tinyxml" << endl;
	root = new Node();
	if (mod == in)
	{
		cout << "sussceeful select mod" << endl;
		fin = new fstream(filename, ios::in);
	}
	else if (mod == out)
		fout = new fstream(filename, ios::out);
	else
		cout << "文件打开错误" << endl;
}

Tinyxml::~Tinyxml()
{
	if(fin||fout)
		close();
}

Node * Tinyxml::open(const char *filename)
{
	//int count = 0;
	//fstream fin(filename,ios::in);
	/*
	char *content = NULL;
	char *p = new char;
	char *ptm = NULL;
	copy(p, " ");
	//copy(content, filename);

	char *str = new char[100];
	cout << "copying...." << endl;
	while (!fin->eof())
	{
		
		*fin >> str;
		//cout << "----------------------------------"<<endl << str << endl;
		
		append(content, p);
		append(content, str);
		//content = append(content, p);
		//content = append(content, str);
		//cout << "---------------" << p << "---------------------" << endl;
		//cout << "****************"<<ptm << "**************" << endl;
		//cout << "----------------" << content << "---------------" << endl;
		//delete p;
		//cout << "successful append !!!!!!!!!!" << endl;
	}
	*/
	cout << "-------------successful open --------------------" << endl;
	int count = 0;
	char *s1 = new char[100];
	while (!fin->eof())
	{
		*fin >> s1;
		count++;
	}
		
	fin->clear();
	fin->seekg(ios::beg);
	
	int *room=new int [count + 1];
	int *head = room;
	char *s = new char[100];
	int sum = 0;
	while (!fin->eof())
	{
		*fin >> s;
		*head = len(s)+1;
		sum += *head;
		head++;
	}
	fin->clear();
	fin->seekg(ios::beg);

	char **str = new char *[count + 1];
	int n = 0;
	for (int i = 0; i < count; i++)
		str[i] = new char[room[i]+1];
		
	while (!fin->eof())
	{
		*fin >> str[n];
		n++;
	}
	close();
	char *content = NULL;
	append(content, str, room, count, sum);
	
	//cout << content << endl;
	cout << "successful copy!!!!!!!!!!" << endl;
	delete str;
	delete s;
	delete room;
	delete s1;
	//cout << "successful delete!!!!!!!!!!" << endl;
	seek(content, root);
	cout << "successful seek!!!!!!!!!!" << endl;
	/*
	for (int i = m; i >= 0; i--)
	{
		if (str[i + 1] == '/'&&str[i] == '<')
		{
			char *name;
			copy(name, str, i + 2,'>');
			buildNode(name,child);
		}

		if (str[i + 1] == '>'&&str[i] == '/')
		{
			char *name;
			copy(name, str, i + 2, '>',-1);
			buildNode(name,child);
		}
	}
*/
	return root;
}

void Tinyxml::close()
{
	if (fin)
	{
		fin->close();
		delete fin;
		fin = NULL;
	}
		
	if (fout)
	{
		fout->close();
		if (fout != NULL)
		{
			delete fout;
			fout = NULL;
		}
		
	}
		
}

void Tinyxml::write(Node * node, int num )
{
	//fstream fout(filename, ios::out);////////////////////
	if (node)
	{
		for (int i = 0; i < num; i++)
			*fout << " " << " ";
		if (node->FirstChildNode())
		{
			
			*fout << "< " << node->name() << " "  << " >" << endl;
			write(node->FirstChildNode(),num+1);
			*fout << "<\\ " << node->name() << " >" << endl;
			write(node->NextSiblingNode(), num);
			
		}
		else
		{
			*fout << "< " << node->name() << " "<< "/>" << endl;
			write(node->NextSiblingNode(), num);

		}
	}
	
	
}



void Tinyxml::Write(Node * node)
{
	write(node);
}

void Tinyxml::seek(const char * str, Node *parentNode)
{
	int m = len(str);
	
	for (int i = m; i >= 0; i--)
	{
		if (str[i + 1] == '/'&&str[i] == '<')
		{
			//cout << "-----------------successful seek '</'-------------" << endl;
			char *name=NULL;
			copy(name, str, i + 2, '>');
			//cout << "-----------------successful copy Node's regional name -------------" << name <<"----"<< endl;
			slipSpace(name);

			//cout << "-----------------successful copy Node's name -------------" << name << "----" << endl;
			Node *node = buildNode(name, parentNode);
			//cout << "the new node's name :" << node->name() << endl;
			//cout << "-----------------successful build Node -------------" << endl;
			for (int j = i; j >= 0; j--)
			{
				if (compare(name, str, j))
				{
					//cout << "-------------successful compare ----------------" << endl;
					char *str1 = NULL;
					copy(str1, str, j+1, i-j-2);
					char *elements = NULL;
					copy(elements, str1, 0, '>');
					//cout << "-------------successful copy node's elements ----------------" << elements << endl;
					node->BulidElement(elements);
					
					//cout << "-------------successful copy compare content ----------------" << str1<<endl;
					seek(str1, node);

					i = j;
					break;
				}
			}
		}
		else if (str[i + 1] == '>'&&str[i] == '/')
		{
			
			for (int j = i; j >= 0; j--)
			{
				if (str[j] == '<')
				{
					char *name = NULL;
					copy(name, str, j + 1, ' ');
					slipSpace(name);
					Node *node = buildNode(name, parentNode);
					//cout << "the new node's name :" << node->name() << endl;
					i = j + len(name) + 2;
					char *elements = NULL;
					copy(elements, str, i, '/');
					//cout << "-------------successful copy node's elements ----------------" << elements << endl;
					node->BulidElement(elements);
					
					break;
				}
			}
			
		}
	}
	//cout << "----------------delete the str of " << parentNode->name() << endl;
	if (!compare(parentNode->name(), "rootNode", 7))/////////////////
	{
		delete str;
	}
		
}

Node * Tinyxml::buildNode(const char * name, Node *&parentNode)
{
	if (!parentNode)
		parentNode = new Node();
	Node *child = new Node(name);//val ????????
	parentNode->insertChild(child);
	return child;
}

void Tinyxml::PRINT(Node *node)
{
	//cout << "-------------------  " << node << "  -------------------"<<endl;
	if (node)
	{
		if (!node->GetParent()&&node->value()!=9)
		{
			node->Setvalue(9);
			node = seekBro(node);
		}
	
		//cout << "----------------begin to print the tree---------------" << endl << endl;
		cout << "name: " << node->name() << "  " << node->value();
		
		if (node->GetParent())
			cout << "  parent name: " << node->GetParent()->name();
		cout << endl ;
		node->PrintElements();
		cout << endl ;
		//cout << "----------------successful---------------" << endl << endl;
		//cout << "----------------begin to print the child---------------" << node->name() << endl << endl;
		PRINT(node->FirstChildNode());
		//cout << "---------------- successful print the child---------------" << node->name() << endl << endl;
		//cout << "----------------begin to print the brother---------------" << node->name() << endl << endl;

		PRINT(node->GetParent());
		//cout << "---------------- successful print the brother---------------" << node->name() << endl << endl;

		


	}
}

Node * Tinyxml::RootNode()
{
	return root->FirstChildNode();
}

Node * Tinyxml::seekBro(Node * node)
{
	//Node *bro = NULL;
	while (node->NextSiblingNode())
		node = node->NextSiblingNode();
	//if (!bro)
		//bro = node;
	return node;
}




Node::Node()
{
	buildNode("rootNode", 0);
	elements = NULL;
}

Node::Node(const char *str, Node *parent)
{
	buildNode(str, parent);
	elements = NULL;
}

void Node::buildNode(const char *name, Node *parent, int val, Node *L, Node *R)
{
	
		int i = 0;
		copy(Name, name);
		Value = val;
		R_Child = R;
		L_Child = L;
		Parent = parent;
}

char * Node::name()
{
	return Name;
}

int Node::value()
{
	return Value;
}

void Node::Setvalue(int val)
{
	Value = val;
}

void Node::insertChild(Node *child)
{
	if (L_Child) 
	{
		L_Child->insertBrother(child);
	}
	else 
	{
		//L_Child = new Node;
		//*L_Child = *child;//重载“=”
		L_Child = child;
		//L_Child->SetParent(this);
	}

}

void Node::insertBrother(Node *bro)
{
	if (R_Child)
	{
		R_Child->insertBrother(bro);
	}
	else
	{
		//R_Child = new Node;
		//*R_Child = *bro;//重载“=”
		R_Child = bro;
		R_Child->SetParent(this);
	}
}

void Node::linkParent(Node *parent)
{
	if (Parent)
	{
		Parent->cutChild(this);
	}
	parent->insertChild(this);
}

void Node::SetParent(Node * parent)
{
	Parent = parent;
}

void Node::cutChild(Node * child)
{
	if (*L_Child == *child)//重载“==”
	{
		L_Child = NULL;
	}
	else
	{
		L_Child->cutBrother(child);
	}
}

void Node::cutBrother(Node * bro)
{
	if (*R_Child == *bro)//
	{
		R_Child = R_Child->NextSiblingNode();//
	}
	else
	{
		R_Child->cutBrother(bro);
	}
}

Node * Node::NextSiblingNode()
{
	return R_Child;
}

Node * Node::FirstChildNode()
{
	return L_Child;
}

Node * Node::GetParent()
{
	return Parent;
}

void Node::BulidElement(const char * ele)
{
	elements = new Element(ele);
}

void Node::PrintElements()
{
	if (elements)
		elements->Print();
}

TiXmlAttribute * Node::FirstAttribute()
{
	return elements->FirstAttribute();
}



bool Node::operator==(Node &n1)
{

	//重载==，对比字符串
	return (compare(this->name(), n1.name()) && (this->value() == n1.value())); //&& 
		//(this->value() == n1->value()) && (this->value() == n1->value()) && (this->value() == n1->value());
}

Node & Node::operator=(Node * n1)
{
	this->buildNode(n1->name(), n1->Parent, n1->value(), n1->NextSiblingNode(), n1->FirstChildNode());
	return *this;
	// TODO: 在此处插入 return 语句
}

Element::Element(const char * ele)
{
	//cout << "------------build elements ----------------" << endl;
	Num = 0;
	for (int i = 0; i <= len(ele); i++)
	{
		if (ele[i] == '=')
			Num++;
	}
	//cout << "---------totally " << Num << " elements---------" << endl << endl;
	build(Num);
	read(ele);
	//cout << "----------successful read elements--------" << endl << endl;
}

void Element::read(const char * ele)
{
	TiXmlAttribute *elements = head;
	for (int i = 0; i <= len(ele); i++)
	{
		if (ele[i] == '=' &&elements != NULL)
		{
			//cout << "-------------copy elements' name--------------" ;
			copy(elements->name, ele, i - 1, ' ', -1);
			char *val = NULL;
			copy(val, ele, i + 2, '\"');
			elements->value = Toint(val);
			elements = elements->nextElement;
			//cout << "--------- " << " -sssssssssssssss--------" << endl << endl;
			delete val;
			//cout << "--------- " << " -sssssssssssssss--------" << endl << endl;
		}
	}
	
}

void Element::write(fstream fout)
{
	for (TiXmlAttribute *elements = head; 
		elements!=NULL;
		elements=elements->nextElement)
	{
		fout << elements->name << "=\"" << elements->value << "\" ";
	}
}

void Element::build(int num)
{
	if (num)
	{
		head = new TiXmlAttribute;
		TiXmlAttribute *p = head;
		for (int i = 0; i < num - 1; i++)
		{
			p->nextElement = new TiXmlAttribute;
			p = p->nextElement;
		}
		p = NULL;
	}
	else
		head = NULL;


}

void Element::Print()
{
	for (TiXmlAttribute *elements = FirstAttribute();
		elements != NULL;
		elements = elements->nextElement)
	{
		cout << elements->name << "=\"" << elements->value << "\" " << endl;
	}
}

TiXmlAttribute * Element::FirstAttribute()
{
	return head;
}

