#pragma once
typedef   unsigned   char   *POINTER;
typedef   unsigned   short   int   UINT2;
typedef   unsigned   long   int   UINT4;
typedef   struct
{
	UINT4   state[4];
	UINT4   count[2];
	unsigned   char   buffer[64];
}   MD5_CTX;


#define   S11   7  
#define   S12   12  
#define   S13   17  
#define   S14   22  
#define   S21   5  
#define   S22   9  
#define   S23   14  
#define   S24   20  
#define   S31   4  
#define   S32   11  
#define   S33   16  
#define   S34   23  
#define   S41   6  
#define   S42   10  
#define   S43   15  
#define   S44   21  

void   MD5Init(MD5_CTX   *);
void   MD5Update(MD5_CTX   *, unsigned   char   *, unsigned   int);
void   MD5Final(unsigned   char[16], MD5_CTX   *);
void MD5Digest(unsigned   char   *pszInput, unsigned   long   nInputSize, unsigned   char   *pszOutPut);