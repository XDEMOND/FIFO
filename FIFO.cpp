//@XDEMOND
#include <iostream.h>
#include <conio.h>
#include <stdlib.h>

#define Memoria 	1024
#define MarcoPag 	64
#define LinpPag	100
#define N			10
#define so			128

void crear_MMT(void);
void imprime_MMT(void);
void crear_JT(void);
void imprime_JT(void);
void crear_PMT(void);
void imprime_PMT(void);
void asigna_SO(void);
void asigna_FIFO(void);

struct MMT
{
	int nbloque;
   int locini;
   int edoMMT;
   struct MMT *sig;
};

struct JT
{
	int tarea;
   int captarea;
   int locPMT;
   int numpag;
   int secuencia[];
   struct JT *sig;
};

struct PMT
{
	int pagina;
   int locmarco;
   int edoPMT;
   int mod;
   int ref;
   struct PMT *sig;
};

MMT *iM, *fM, *nuevoM, *auxM;
JT *iJ, *fJ, *nuevoJ, *auxJ;
PMT *iP[N], *fP[N], *nuevoP[N], *auxP[N], *aux2P[N];

void main()
{
	iM = NULL;
   fM = NULL;
   iJ = NULL;
   fJ = NULL;
   iP[N] = NULL;
   fP[N] = NULL;

   system("cls");
   crear_MMT();
   imprime_MMT();

   crear_JT();
   imprime_JT();

   crear_PMT();
   imprime_PMT();
   asigna_SO();
   imprime_MMT();
   asigna_FIFO();
   system("pause");
}

void crear_MMT(void)
{
	int i=0, Marcos=0;

   Marcos = (Memoria/MarcoPag);
   cout<<"Marcos: "<<Marcos<<endl;

   do
   {
   	if(iM==NULL)
      {
      	iM = (MMT *)malloc(sizeof(MMT));
         iM->nbloque = i;
         iM->locini = (i*MarcoPag);
         iM->edoMMT = 0;

         iM->sig = NULL;
         fM = iM;
      }
      else
      {
         nuevoM = (MMT *)malloc(sizeof(MMT));
         nuevoM->nbloque = i;
         nuevoM->locini = (i*MarcoPag);
         nuevoM->edoMMT = 0;

         fM->sig = nuevoM;
         fM = nuevoM;
      }
      i++;
   }while(i<Marcos);
   fM->sig=NULL;
}

void crear_JT(void)
{
	int i=1, j=5,s=1;
   int modulo=0, divisor=0;

   do
   {
   	if(iJ==NULL)
      {
      	iJ = (JT *)malloc(sizeof(JT));
         iJ->tarea = i;
         iJ->captarea = 400+rand()%600;
         iJ->locPMT =0;
         modulo = (iJ->captarea%LinpPag);
         divisor = (iJ->captarea/LinpPag);
         if(modulo =! 0)
         {
         	divisor++;
         }
         iJ->numpag = divisor;

         iJ->sig=NULL;
         fJ = iJ;
      }
      else
      {
      	nuevoJ = (JT *)malloc(sizeof(JT));
         nuevoJ->tarea = i;
         nuevoJ->captarea = 400+rand()%600;
         nuevoJ->locPMT = j;
         modulo = (nuevoJ->captarea%LinpPag);
         divisor = (nuevoJ->captarea/LinpPag);
         if(modulo =! 0)
         {
         	divisor++;
         }
         nuevoJ->numpag = divisor;

         fJ->sig = nuevoJ;
         fJ = nuevoJ;
      }
      i++;
   }while(i<=N);
}

void crear_PMT(void)
{
	int i=1, j;
   auxJ = iJ;

   do
   {
   	for(j=0;j<auxJ->numpag;j++)
      {
      	if(iP[i]==NULL)
         {
         	iP[i]=(PMT *)malloc(sizeof(PMT));
            iP[i]->pagina = j;
            iP[i]->locmarco =0;
            iP[i]->edoPMT = 0;
            iP[i]->mod = 0;
            iP[i]->ref = 0;
            iP[i]->sig = NULL;
            fP[i] = iP[i];
      	}
         else
         {
         	nuevoP[i]=(PMT *)malloc(sizeof(PMT));
            nuevoP[i]->pagina = j;
            nuevoP[i]->locmarco = 0;
            nuevoP[i]->edoPMT = 0;
            nuevoP[i]->mod = 0;
            nuevoP[i]->ref = 0;
            nuevoP[i]->sig = NULL;
            fP[i]->sig = nuevoP[i];
            fP[i] = nuevoP[i];
         }
      }
      i++;
      auxJ = auxJ->sig;
   }while(i<=N);
}

void imprime_MMT(void)
{
	auxM = iM;

   cout<<" -- MMT -- "<<endl;
   cout<<"NoMarco\tLoc ini\t\tEstado\n";
   while(auxM!=NULL)
   {
   	cout<<auxM->nbloque<<"\t"<<auxM->locini<<"KB\t\t"<<auxM->edoMMT<<endl;
      auxM = auxM->sig;
   }
}


void imprime_JT(void)
{
   auxJ = iJ;
   int s;

	cout<<"\n -- JT --"<<endl;
   cout<<"Tarea\tNoLineas\tlocPMT\tNumPaginas\n";
   while(auxJ!=NULL)
   {
   	cout<<"J"<<auxJ->tarea<<"\t"<<auxJ->captarea<<"\t\t"<<auxJ->locPMT<<"\t\t"<<auxJ->numpag<<endl;
      auxJ = auxJ->sig;
   }
}

void imprime_PMT(void)
{
	int i=1, j;
	auxJ = iJ;


   cout<<"\n -- PMT --"<<endl;

   do
   {
   	auxP[i] = iP[i];
   	cout<<"\nTabla J"<<i<<endl;
      cout<<"Pagina\tMarco\tEdo\tMod\tRef\n";
      while(auxP[i]!=NULL)
      {
      	cout<<"P"<<auxP[i]->pagina<<"\t"<<auxP[i]->locmarco<<"\t"<<auxP[i]->edoPMT<<"\t"<<auxP[i]->mod<<"\t"<<auxP[i]->ref<<endl;
         auxP[i] = auxP[i]->sig;
      }
      i++;
      auxJ = auxJ->sig;
      getch();
   }while(i<=N);
}

void asigna_SO(void)
{
	auxM = iM;
   int totalM=0;

   cout<<" -- Asigna SO --"<<endl;

	while(auxM!=NULL)
   {
   	if(auxM->edoMMT!=1)
      {
      	totalM = totalM + auxM->locini;
      	if(totalM > so)
         {
         	goto exit;
         }
         auxM->edoMMT = 1;

      }
      auxM = auxM->sig;
   }
   exit:
}

void asigna_FIFO(void)
{
	auxM = iM;
	auxJ = iJ;
   auxP[N]=iP[N];


	int s,p=1;
   int espacio=3,e=0, nump;
	int n;
	while(auxJ!=NULL)
   {
   	n= auxJ->numpag;
   	cout<<"Tarea J"<<auxJ->tarea;
   	cout<<"\nNumeros de pagina"<<n<<"\n";
   	auxJ->secuencia[n];

   	for(int i=0;i<n;i++)
   	{
   		auxJ->secuencia[i] = rand()%10;
      	cout<<" "<<auxJ->secuencia[i];
   	}
      auxJ = auxJ->sig;
   }

	int sec[]={0,rand()%10,rand()%10,rand()%10,rand()%10,rand()%10,rand()%10,rand()%10,rand()%10};
   cout<<"\nSECUENCIA"<<endl;
   for(s=0;s<8;s++)
   {
   	cout<<" "<<sec[s];
   }
   cout<<endl;
   s=0;
}


