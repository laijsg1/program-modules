#pragma once
#include<iostream>
#include<string.h>
using namespace std;
bool compare(char *s1, char *s2);
bool compare(char *s1, const char *s2);
bool compare(char *s1, const char *s2, int pos);
void append(char *&s1, char *s2);
void append(char *&content, char **str, int *room, int count, int sum);
void copy(char *&s1, const char *s2);
void copy(char *&s1, const char *s2, int pos ,int len, int dirt =1);
void copy(char *&s1, const char *s2, int pos, char split,int dirt = 1);
int len(char *str);
int len(const char *str);
int Toint(const char *str);
void slipSpace(char *&str);
int pow(int x, int y);
class Mystring
{
	
public:
	Mystring();
	~Mystring();
	friend bool compare(char *s1, char *s2);
	friend bool compare(char *s1, const char *s2);
	friend bool compare(char *s1, const char *s2, int pos);
	friend void append(char *&s1, char *s2);
	friend void append(char *&content, char **str, int *room, int count, int sum);
	friend void copy(char *&s1, const char *s2);
	friend void copy(char *&s1, const char *s2, int pos, char split, int dirt );
	friend void copy(char *&s1, const char *s2, int pos, int len, int dirt );
	friend int len(char *str);
	friend int len(const char *str);
	friend int Toint(const char *str);
	friend void slipSpace(char *&str);
	friend int pow(int x, int y);
};

