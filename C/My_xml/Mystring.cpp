#include "stdafx.h"
#include "Mystring.h"


Mystring::Mystring()
{
}


Mystring::~Mystring()
{
}

bool compare(char * s1, char * s2)
{
	bool n1 = 1;
	if (len(s1) == len(s2))
	{
		for (int i = 0; i <= len(s1); i++)
		{
			if (s1[i] != s2[i])
				n1 = 0;
		}
	}
	else
		n1 = 0;
	return n1;
}

bool compare(char * s1, const char * s2)
{
	bool n1 = 1;
	if (len(s1) == len(s2))
	{
		for (int i = 0; i <= len(s1); i++)
		{
			if (s1[i] != s2[i])
				n1 = 0;
		}
	}
	else
		n1 = 0;
	return n1;
}

bool compare(char * s1, const char * s2, int pos)
{
	bool n1 = 1;
	int length = len(s1);
	if (pos - length < 0)
		return 0;
	for (int i = 0; i <= length; i++)
	{
		if (s1[i] != s2[pos + i - length])
			n1 = 0;
		
	}
	return n1;
}

void append(char *&s1, char * s2)
{
	int n = len(s1) + len(s2)+3;
	//cout << "appending......" << endl;
	//cout << "------------- totall append " << n << "chars --------------" << endl;
	char *s = new char[n];
	for (int i = 0; i < n; i++)
	{
		
		if (i <= len(s1))
			s[i] = s1[i];
		else
			s[i] = s2[i-len(s1)-1];
	}
	
	delete s1;
	s1 = s;
}

void append(char *&content, char ** str, int *room, int count, int sum)
{
	char *s1 = new char[sum + count + 1];
	int n = 0;
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < room[i]; j++)
		{
			s1[n] = str[i][j];
			n++;
		}
		s1[n] = ' ';
		n++;
	}
	//cout << "----------------------------------------------" << n << "---------------" <<sum+1+count<<endl;
	s1[sum + count + 1] = '\0';
	content = s1;
}

void copy(char *& s1, const char *s2)
{
	if(s1)
		delete s1;
	s1 = new char[len(s2) + 1];
	for (int i = 0; i <= len(s2)+1; i++)
		s1[i] = s2[i];
}

void copy(char *& s1, const char * s2, int pos, int length, int dirt)
{
	if(s1)
		delete s1;
	s1 = new char[length + 2];
	if (pos<0 || pos>len(s2) || pos + length > len(s2)) {
		std::cout << "copy ÖØÔØº¯Êý ³ö´í" << std::endl;
		length = -1;
	}
	else
	{
		for (int i = 0; i <=length; i++)
			{
				s1[i] = s2[pos + i];
			}
			s1[length + 1] = '\0';
	}
	
}

void copy(char *& s1, const char * s2, int pos, char split, int dirt)
{
	if (s1)
		delete s1;
	int length =0;
	for (int i = pos; ; i+=dirt)
	{
		if (s2[i] == split||i<0||i>len(s2))
			break;
		length++;
	}
	s1 = new char[length+1];
	if (dirt > 0)
	{
		for (int i = pos; i < pos + length; i++)
		{
			s1[i- pos] = s2[i];
		}
				
	}
	else
	{
		for (int i = pos - length + 1; i <= pos; i++)
		{
			s1[i- (pos - length + 1)] = s2[i];
		}
			
	}
	s1[length] = '\0';
}

int len(char * str)
{
	if (!str)
	{
		cout << "wrong!!!!!!!!" << endl;
		return -1;
	}
	int i=0;
	while (1)
	{
		if (str[i] == '\0')
			break;
		i++;
	}
	return i-1;
}

int len(const char * str)
{
	if (!str)
	{
		cout << "wrong!!!!!!!!" << endl;
		return -1;
	}
	int i = 0;
	while (1)
	{
		if (str[i] == '\0')
			break;
		i++;
	}
	return i - 1;
}

int Toint(const char * str)
{
	int sum = 0;
	int length = len(str);
	if (str[0] == '-')
	{
		for (int i = length; i > 0; i--)
		{
			sum += (str[i] - 48)*pow(10, length - i);
		}
		sum = -sum;
	}
	else if (str[0] >= 48 && str[0] < 58)
	{
		for (int i = length; i >= 0; i--)
		{
			sum += (str[i] - 48)*pow(10, length - i);
		}
	}
	else
		cout << "wrong!!!!!" << endl;
	return sum;
}

void slipSpace(char *& str)
{
	char *s1 = NULL;
	int length = len(str);

	if (str[0] == ' '&&str[length] == ' ')
	{
		copy(s1, str, 1, length - 2);
	}
	else if (str[0] == ' ')
	{
		copy(s1, str, 1, length-1);
	}
	else if (str[length] == ' ')
	{
		copy(s1, str, 0, length-1);
	}
	else
		s1 = str;
	str = s1;
}

int pow(int x, int y)
{
	int sum = 1;
	for (int i = 0; i < y; i++)
	{
		sum *= x;
	}
	return sum;
}

