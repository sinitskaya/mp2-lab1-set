﻿// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len < -1)
		throw out_of_range("out of range");
	BitLen = len;
	MemLen = (BitLen + sizeof(TELEM)*8-1)/(sizeof(TELEM)*8); 
	pMem = new TELEM[MemLen]; 
	if ( pMem != NULL )
		for ( int i=0; i < MemLen; i++ ) 
			pMem[i] = 0; 
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen=bf.BitLen;
	MemLen=bf.MemLen;
	pMem =new TELEM[MemLen];
	for (int i=0;i<MemLen; i++) 
		pMem[i]=bf.pMem[i];
}

TBitField::~TBitField()
{
	delete []pMem;
	pMem = NULL;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return n >> 5; 
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1 << (n & 31);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0) || (n > BitLen))
		throw out_of_range("Out of range");
	pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ( (n <0) || (n > BitLen) )
		throw out_of_range("Out of range");
	pMem[GetMemIndex(n)] &=~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n < 0) || (n > BitLen)) 
		throw out_of_range("out of range");
	return pMem[GetMemIndex(n)] & GetMemMask(n); 
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this != &bf)
	{
		BitLen = bf.BitLen; 
		MemLen = bf.MemLen; 
		delete []pMem; 
		pMem = new TELEM [MemLen]; 
		for (int i=0;i<MemLen;i++) 
			pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  int flag; 
	if (MemLen == bf.MemLen) 
	{ 
		for (int i=0;i<MemLen;i++)  
			if (pMem[i] != bf.pMem[i]) 
			{ 
				flag = 0; 
				break; 
			}  
		flag = 1; 
	} 
	return flag; 
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  int flag; 
	if (MemLen == bf.MemLen) 
	{ 
		for (int i=0;i<MemLen;i++)
			if (pMem[i] = bf.pMem[i]) 
			{ 
				flag = 0; 
				break; 
			}  
		flag = 1; 
	} 
	return flag;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int a; 
	if (BitLen >= bf.BitLen)
		a = BitLen; 
	else a = bf.BitLen; 
	TBitField x(a); 
	for (int i=0;i<x.MemLen;i++) 
	{ 
		x.pMem[i] = bf.pMem[i] | pMem[i]; 
	} 
	return x; 
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int a; 
	if (BitLen >= bf.BitLen) a = BitLen; 
	else a = bf.BitLen; 
	TBitField x(a); 
	for (int i=0;i<x.MemLen;i++) 
	{ 
		x.pMem[i] = bf.pMem[i] & pMem[i]; 
	} 
	return x; 
}

TBitField TBitField::operator~(void) // отрицание
{
	int len = BitLen;
	TBitField temp(len);
	for ( int i=0; i<MemLen; i++ )
		temp.pMem[i] = ~pMem[i];
	return temp; 
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	for (int i=0; i< bf.MemLen; i++)
		istr >> bf.pMem[i];
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i=0; i<bf.MemLen; i++) 
		ostr << bf.pMem[i];
	return ostr;
}
