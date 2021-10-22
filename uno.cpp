///UNO
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<cstring>
#include<time.h>
#include<windows.h>
#define random(x) rand() %x
#define randomize srand ((unsigned)time(NULL))
using namespace std;
//variabili programma
//struct per carte
struct carta
{
    int colore;
    int numero;
    carta *succ;
};
typedef carta *tipocarta;
tipocarta mazzo=NULL;
tipocarta scarti=NULL;

//char per salvare il nome
typedef char *nome;

//lista per i giocatori con i dati
struct gioc
{
    tipocarta maz;
    nome nom;
    int cont;
    gioc *succ;
};
typedef gioc* tipogioc;
tipogioc listagioc=NULL;

//carte rimaste
int nrimaste=36;
int nscarti=0;
//numero dei giocatori
int ngioc;
//bool per la vittoria
bool vittoria=false;
bool stop=false;

//SOTTOPROGRAMMI
//GENERALI
//funzione per generare casualmente un numero compreso tra 1 e max
int caso(int max)
{
    return(random(max)+1);
}

//setcolor per cambiare il colore del testo e dello sfondo del testo
void setcolor(unsigned short color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
}

//Void per inserimento in coda di un nodo carta
void coda(tipocarta &c, tipocarta &ncarta)
{
    if(c==NULL)
    {
        c=ncarta;
        ncarta->succ=NULL;
    }
    else
    {
        tipocarta app=c;
        while(app->succ!=NULL)
        {
            app=app->succ;
        }
        app->succ=ncarta;
        ncarta->succ=NULL;
    }
}

//CREAZIONE MAZZO
//void per salvare i dati di una carta in un nodo carta
void salvacarta(tipocarta &c, int col, int num)
{
    tipocarta app;
    app=new carta;
    app->colore=col;
    app->numero=num;
    coda(c,app);
}

//void per caricare il mazzo in modo ordinato con tutte le carte
void caricamazzo(tipocarta &mazzo)
{
    tipocarta app;
    //rosso
    for(int i=1;i<=8;i++)
    {
        salvacarta(mazzo,192,i);
    }
    //blu
    for(int i=1;i<=8;i++)
    {
        salvacarta(mazzo,144,i);
    }
    //giallo
    for(int i=1;i<=8;i++)
    {
        salvacarta(mazzo,224,i);
    }
    //verde
    for(int i=1;i<=8;i++)
    {
        salvacarta(mazzo,160,i);
    }
    //jolly X4
    salvacarta(mazzo,0,9);
    salvacarta(mazzo,0,9);
    salvacarta(mazzo,0,9);
    salvacarta(mazzo,0,9);
}

//VISUALIZZAZIONE
//procedura per cancellare cio' che c'e' sullo schermo dopo che l'utente ha premuto un pulsante
void canc()
{
    system("pause");
    system("cls");
}

//procedura per mandare a video una riga di dato colore e lunghezza
void visriga(int col, int l)
{
    setcolor(col);
    for(int i=0; i<l; i++) cout<<" ";
}

//procedura che determina come visualizzare i bordi superiore e inferiore di una carta
void riga1(int col)
{
    visriga(col, 14);
}

//procedura che determina come visualizzare la seconda e la penultima riga di una carta
void riga2(int col)
{
    visriga(col, 3);
    visriga(240, 8);
    visriga(col, 3);
}

//procedura che determina come visualizzare la seconda e la penultima riga del retro di una carta
void riga2_retro()
{
    visriga(0, 3);
    visriga(192, 8);
    visriga(0, 3);
}

//procedura che contiene tutti i modelli del centro delle carte (suddiviso per righe) e permette di visualizzarli correttamente
void bancacarte(int riga, int num)
{
    if(num==1)
    {
        if(riga==2)
        {
            visriga(240, 2);
            visriga(0, 3);
            visriga(240,3);
        }
        if(riga>=3 && riga<=6)
        {
            visriga(240, 3);
            visriga(0, 2);
            visriga(240,3);
        }
    }
    if(num==2)
    {
        if(riga==2 || riga==4 || riga==6)
        {
            visriga(240, 1);
            visriga(0, 6);
            visriga(240, 1);
        }
        if(riga==3)
        {
            visriga(240, 5);
            visriga(0, 2);
            visriga(240, 1);
        }
        if(riga==5)
        {
            visriga(240, 1);
            visriga(0, 2);
            visriga(240, 5);
        }
    }
    if(num==3)
    {
        if(riga==2 || riga==4 || riga==6)
        {
            visriga(240, 1);
            visriga(0, 6);
            visriga(240, 1);
        }
        if(riga==3 || riga==5)
        {
            visriga(240, 5);
            visriga(0, 2);
            visriga(240, 1);
        }
    }
    if(num==4)
    {
        if(riga==2 || riga==3)
        {
            visriga(240, 1);
            visriga(0, 2);
            visriga(240, 2);
            visriga(0, 2);
            visriga(240, 1);
        }
        if(riga==4)
        {
            visriga(240, 1);
            visriga(0, 6);
            visriga(240, 1);
        }
        if(riga==5 || riga==6)
        {
            visriga(240, 5);
            visriga(0, 2);
            visriga(240, 1);
        }
    }
    if(num==5)
    {
        if(riga==2 || riga==4 || riga==6)
        {
            visriga(240, 1);
            visriga(0, 6);
            visriga(240, 1);
        }
        if(riga==3)
        {
            visriga(240, 1);
            visriga(0, 2);
            visriga(240, 5);
        }
        if(riga==5)
        {
            visriga(240, 5);
            visriga(0, 2);
            visriga(240, 1);
        }
    }
    if(num==6)
    {
        if(riga==2 || riga==4 || riga==6)
        {
            visriga(240, 1);
            visriga(0, 6);
            visriga(240, 1);
        }
        if(riga==3)
        {
            visriga(240, 1);
            visriga(0, 2);
            visriga(240, 5);
        }
        if(riga==5)
        {
            visriga(240, 1);
            visriga(0, 2);
            visriga(240, 2);
            visriga(0, 2);
            visriga(240, 1);
        }
    }
    if(num==7)
    {
        if(riga==2)
        {
            visriga(240, 1);
            visriga(0, 6);
            visriga(240, 1);
        }
        if(riga>=3 && riga<=6)
        {
            visriga(240, 5);
            visriga(0, 2);
            visriga(240, 1);
        }
    }
    //pesca
    if(num==8)
    {
        if(riga==2 || riga==4)
        {
            visriga(240, 1);
            visriga(0, 5);
            visriga(240, 2);
        }
        if(riga==3)
        {
            visriga(240, 1);
            visriga(0, 2);
            visriga(240, 2);
            visriga(0, 2);
            visriga(240, 1);
        }
        if(riga==5 || riga==6)
        {
            visriga(240, 1);
            visriga(0, 2);
            visriga(240, 5);
        }
    }
    //jolly
    if(num==9)
    {
        if(riga==2 || riga==3)
        {
            visriga(192, 3);
            visriga(240, 2);
            visriga(144, 3);
        }
        if(riga==4)
        {
            visriga(240, 8);
        }
        if(riga==5 || riga==6)
        {
            visriga(224, 3);
            visriga(240, 2);
            visriga(160, 3);
        }
    }
    //retro intero carta
    if(num==10)
    {
        if(riga==2)
        {
            visriga(192, 7);
            visriga(224, 3);
        }
        if(riga==3)
        {
            visriga(192, 3);
            visriga(96, 2);
            visriga(192, 1);
            visriga(96, 1);
            visriga(224, 1);
            visriga(192, 1);
            visriga(224, 1);
        }
        if(riga==4)
        {
            visriga(224, 1);
            visriga(192, 1);
            visriga(224, 1);
            visriga(96, 4);
            visriga(224, 3);
        }
        if(riga==5)
        {
            visriga(224, 1);
            visriga(192, 1);
            visriga(224, 1);
            visriga(96, 1);
            visriga(192, 1);
            visriga(96, 2);
            visriga(192, 3);
        }
        if(riga==6)
        {
            visriga(224, 3);
            visriga(192, 7);
        }
    }
}

//procedura che permette di visualizzare una determinata riga di una carta di dato numero e colore
void viscarta(int riga, int num, int col)
{
    //serve per mandare a video una riga dello stasso colore dello sfondo se una pila e' piu' bassa dell'altra
    if(riga<0) visriga(112, 14);
    else
    {
        //serve per mandare a video il bianco sotto la prima carta di una pila
        if(riga>8) visriga(240, 14);
        else
        {
            //bordo superiore e inferiore
            if(riga==0 || riga==8) riga1(col);
            else
            {
                //bordo superiore e inferiore "interni"
                if(riga==1 || riga==7)
                {
                    if(num==10) riga2_retro();
                    else riga2(col);
                }
                else
                {
                    //bordo sinistra
                    visriga(col, 2);
                    if(num!=10) visriga(240, 1);
                    //area interna alla carta
                    bancacarte(riga, num);
                    //bordo destra
                    if(num!=10) visriga(240, 1);
                    visriga(col, 2);
                }
            }
        }
    }
}

//procedura che permette di mandare a video un dato mazzo, raggruppando le carte in righe da 5 carte ciascuna
void visualmazzo(tipocarta mazzo)
{
    int riga, i;
    tipocarta temp1=mazzo, temp2;
    //ciclo per mandare a video tutte le carte
    while(temp1!=NULL)
    {
        riga=0;
        //ciclo per mandare a video tutte le righe di una serie da 5 di carte
        while(temp1!=NULL && riga<9)
        {
            visriga(112, 1);
            i=0;
            temp2=temp1;
            //ciclo per mandare a video 5 carte per riga (o meno se non ce ne sono abbastanza)
            while(temp1!=NULL && i<5)   //basta modificare i<x per cambiare il numero di carte visualizzate per ogni riga
            {
                viscarta(riga, temp1->numero, temp1->colore);
                if(i!=4)visriga(112, 2);
                i++;
                temp1=temp1->succ;
            }
            cout<<endl;
            riga++;
            if(riga!=9)temp1=temp2;
        }
        cout<<endl;
    }
    setcolor(112);
}

//procedura che manda a video il nome di un giocatore e il relativo mazzo
void visualgioc(tipogioc gioc)
{
    cout<<gioc->nom<<":"<<endl<<endl;
    visualmazzo(gioc->maz);
}

//funzione che serve per inizializzare in modo corretto le righe di una pila per fare in modo che la base sia alla stessa riga (la riga maggiore e' inizializzata a 0, la minore di un numero negativo tale che arrivi a 0 quando deve cominciare a visualizzare la carta). Serve anche per determinare quante righe bianche visualizzare (in base al valore ritornato)
int mas(int &n1, int &n2)
{
    int app;
    if(n1>=n2)
    {
        app=n1;
        n2=n2-n1;
        n1=0;
        return app;
    }
    else
    {
        app=n2;
        n1=n1-n2;
        n2=0;
        return app;
    }
}

//procedura che manda a video le carte impilate del mazzo(la prima e' girata) e degli scarti. E' anche resa (un po' alla buona) l'altezza delle due pile di carte
void visualpile(tipocarta mazzo, tipocarta scarti, int nrimaste, int nscarti)
{
    //prima mazzo, poi scarti
    //in questo modo ogni livello bianco contiene 6 carte
    int rig1=nrimaste/6, rig2=nscarti/6;
    int mass=mas(rig1, rig2);
    //ciclo per mandare a video le righe delle pile (carta superiore e bianco per le carte sottostanti)
    for(int i=0; i<9+mass; i++)
    {
        cout<<"  ";
        viscarta(rig1, 10, 0);
        visriga(112, 4);
        viscarta(rig2, scarti->numero, scarti->colore);
        rig1++;
        rig2++;
        cout<<endl;
        setcolor(112);
    }
    cout<<endl<<endl;
}

//procedura che manda a video i primi 4 spazi di una riga di una carta (serve per creare l'effetto sovrapposizione nelle carte nelle carte avversari)
void visretroparz(int riga)
{
    if(riga==0 || riga==8)
    {
        visriga(0, 4);
    }
    if(riga==1 || riga==7)
    {
        visriga(0, 4);
    }
    if(riga==2 || riga==3)
    {
        visriga(0, 2);
        visriga(192, 2);
    }
    if(riga==4 || riga==5)
    {
        visriga(0, 2);
        visriga(224, 1);
        visriga(192, 1);
    }
    if(riga==6)
    {
        visriga(0, 2);
        visriga(224, 2);
    }
}

//funzione che ritorna il colore del nome di un giocatore in base alla sua posizione nella listagioc
int coloregioc(int i)
{
    if(i==1) return 207;
    if(i==2) return 159;
    if(i==3) return 239;
    if(i==4) return 175;
    if(i==5) return 223;
}

//procedura che manda a video le carte degli avversari, girate e sovrapposte, nel giusto numero
void visualavversari(tipogioc listagioc, int codgioc, int ngioc)
{
    tipogioc app=listagioc;
    cout<<"CARTE AVVERSARI:"<<endl;
    //ciclo per mandare a video le carte di tutti i giocatori
    for(int i=1; i<=ngioc; i++)
    {
        //per evitare che visualizzi anche le carte del giocatore corrente
        if(i!=codgioc)
        {
            setcolor(coloregioc(i));
            cout<<app->nom<<":"<<endl;
            setcolor(112);
            //ciclo per visualizzare le righe delle carte
            for(int rig=0; rig<9; rig++)
            {
                cout<<"  ";
                //ciclo per visualizzare parzialmente tutte le carte meno una di un avversario
                for(int car=0; car<(app->cont)-1; car++) visretroparz(rig);
                //visualizzazione retro carta intero
                viscarta(rig, 10, 0);
                setcolor(112);
                cout<<endl;
            }
            cout<<endl;
        }
        app=app->succ;
    }
    cout<<endl;
}

//DISTRIBUZIONE CARTE
//procedura che ritorna l'indirizzo di una carta data la sua posizione all'interno del mazzo (come se fosse l'indice di un vettore)
//non servono i controlli per il non trovato perche' la casuale generera' sempre un indice che nel mazzo esiste
tipocarta ricseq_pos(tipocarta &mazzo, int pos)
{
    if(mazzo==NULL) return NULL;
    tipocarta temp=mazzo;
    for(int i=0; i<pos; i++) temp=temp->succ;
    return temp;
}

//procedura che estrae da un mazzo una carta data la sua posizione all'interno del mazzo (parte da 0)
tipocarta estrai_pos(tipocarta &mazzo, int pos)
{
    tipocarta trov=ricseq_pos(mazzo, pos);
    if(trov!=NULL)
    {
        tipocarta temp=mazzo;
        if(trov==mazzo) mazzo=mazzo->succ;
        else
        {
            while(temp->succ!=trov) temp=temp->succ;
            temp->succ=trov->succ;
        }
    }
    return trov;
}

//procedura che riporta il colore di tutti i jolly a nero
void azzerajolly(tipocarta &mazzo)
{
    //non serve il controllo per il mazzo vuoto perche'non puo' mai esserlo
    tipocarta app=mazzo;
    while(app!=NULL)
    {
        if(app->numero==9) app->colore=0;
        app=app->succ;
    }
}

//procedura che mette le carte degli scarti, tranne la prima, nel mazzo e aggiorna i relativi contatori
void mescola(tipocarta &mazzo, tipocarta &scarti, int &nscarti, int &nrimaste)
{
    mazzo=scarti->succ;
    scarti->succ=NULL;
    nrimaste=nscarti-1;
    nscarti=1;
    azzerajolly(mazzo);
}

//procedura che pesca casualmente una carta dal mazzo principale e la assegna (in coda) al mazzo di un dato giocatore
void pesca(tipocarta &mazzo, tipocarta &gioc, int &nrim, int &cont, int pos, tipocarta &scarti, int &nscarti)
{
    tipocarta pes=estrai_pos(mazzo, pos);
    //in realta' questo cout non servira'
    if(pes==NULL) cout<<"Il mazzo e' vuoto"<<endl;
    else
    {
        coda(gioc, pes);
        nrim--;
        cont++;
    }
    if(nrim==0)
    {
        mescola(mazzo,scarti,nscarti,nrim);
    }
}

//procedura che crea il mazzo iniziale (costituito da 5 carte) per un dato giocatore
void caricagioc(tipocarta &mazzo, tipocarta &gioc, int &nrim, int &cont, tipocarta &scarti, int &nscarti)
{
    for(int i=0; i<5; i++) pesca(mazzo, gioc, nrim, cont, caso(nrim)-1,scarti,nscarti);
}

//procedura che inserisce la prima carta nel mazzo degli scarti controllando che sia un numero (e non un jolly o una pesca)
void primascarti(tipocarta &mazzo, tipocarta &scarti, int &nrimaste, int &nscarti)
{
    int pos;
    tipocarta app;
    //cicloper controllare che non si estragga una carta speciale
    do
    {
        pos=caso(nrimaste)-1;
        app=ricseq_pos(mazzo, pos);
    }while(app->numero>7);
    pesca(mazzo, scarti, nrimaste, nscarti, pos,scarti, nscarti);
}

//INSERIMENTO GIOCATORI
//void per chiedere in quanti giocano
void giocatori(int &n)
{
    do{
        cout<<"In quanti giocatori giocate? (Tra 2 e 5)"<<endl;
        cin>>n;
      }while(n<2 || n>5);

}

//funzione che ritorna false se un nome e' gia' stato inserito, true in caso contrario
bool ctrlnome(tipogioc listagioc, nome n)
{
    tipogioc temp=listagioc;
    while(temp!=NULL)
    {
        if(strcmpi(temp->nom, n)==0) return false;
        temp=temp->succ;
    }
    return true;
}

//void per dare i nomi ai giocatori
void nomi(nome &n)
{
    fflush(stdin);
    gets(n);
}

//funzione che ritorna l'indirizzo del terminatore di una data stringa
nome cercatermstr(nome n)
{
    nome temp=n;
    while(strcmp(temp, "\0")!=0) temp=temp+1;
    return temp;
}

//funzione che ritorna l'indirizzo di una stringa contenente il nome di un nuovo giocatore con i controlli per evitare ripetizioni
nome chiedinome(int i)
{
    int col;
    bool ctrl;
    nome n=new char, c;
    do
    {

        cout<<"Inserisci nome "<<i<<"o giocatore: ";
        col=coloregioc(i);
        setcolor(col);
        nomi(n);
        ctrl=ctrlnome(listagioc, n);
        setcolor(112);
        if(ctrl==false)
        {
            cout<<"Nome gia' inserito. Inserisci cognome: ";
            setcolor(col);
            //cerca il terminatore di stringa del nome e salvane l'indirizzo in c
            c=cercatermstr(n);
            //nella cella di indirizzo trovato metti uno spazio (per lasciare uno spazio tra nome e cognome)
            *c=' ';
            //punta alla cella successiva
            c++;
            //salva la stringa a partire dalla cella attuale (quella dopo lo spazio dopo il nome)
            nomi(c);
            //in questo modo si sono fuse le due stringhe: n conterra' sia nome che cognome perche' c'e' un solo terminatore di stringa, quello dopo il cognome
            ctrl=ctrlnome(listagioc, n);
            setcolor(112);
            if(ctrl==false) cout<<"Tu e un altro giocatore siete omonimi. Inserire un nuovo nome."<<endl;
        }
    }while(ctrl==false);
    cout<<endl;
    return n;
}

//procedura che inserisce in coda un nodo contenente i dati di un nuovo giocatore
void inscoda_gioc(tipogioc &listagioc, tipogioc &ngioc)
{
    if(listagioc==NULL)
    {
        listagioc=ngioc;
        ngioc->succ=NULL;
    }
    else
    {
        tipogioc app=listagioc;
        while(app->succ!=NULL)
        {
            app=app->succ;
        }
        app->succ=ngioc;
        ngioc->succ=NULL;
    }
}

//procedura che crea tanti giocatori quanti sono quelli inseriti dall'utente e li carica con i relativi dati
void creagioc(tipogioc &listagioc, int numgioc, int &nrim, tipocarta &scarti, int &nscarti)
{
    tipogioc ngioc;
    for(int i=0; i<numgioc; i++)
    {
        ngioc=new gioc;
        ngioc->cont=0;
        ngioc->nom=chiedinome(i+1);
        ngioc->maz=NULL;
        caricagioc(mazzo, ngioc->maz, nrim, ngioc->cont,scarti,nscarti);
        inscoda_gioc(listagioc, ngioc);
    }
}

//funzione che dato l'indice di un giocatore (parte da 1) ritorna l'indirizzo del nodo che gli corrisponde
tipogioc cercagioc(tipogioc listagioc, int n)
{
    tipogioc temp=listagioc;
    for(int i=1; i<n; i++) temp=temp->succ;
    return temp;
}

//procedura che manda a video tutti i mazzi dei giocatori (solo fase sviluppo)
void vismazzi(tipogioc listagioc, int ngioc)
{
    tipogioc temp=listagioc;
    for(int i=0; i<ngioc; i++)
    {
        visualgioc(temp);
        cout<<endl<<endl;
        temp=temp->succ;
    }
}

//GIOCO
//procedura che manda a video un trattino colorato
void trattocol()
{
    setcolor(121);
    cout<<" - ";
    setcolor(112);
}
//Void che manda a video le regole del gioco
void regole()
{
    setcolor(31);
    cout<<"BENVENUTI"<<endl;
    setcolor(119);
    system("pause");
    setcolor(121);
    cout<<"REGOLE:"<<endl;
    trattocol();
    cout<<"Si puo' giocare in 2, o in 3, o in 4, o in 5;"<<endl;
    trattocol();
    cout<<"Ogni giocatore ha 5 carte in mano;";
    trattocol();
    cout<<endl<<"Viene scoperta una carta, che formera' la pila degli scarti;"<<endl;
    trattocol();
    cout<<"Quando e' il turno del giocatore stabilito, esso deve selezionare una carta da scartare. Essa deve essere dello stesso seme della carta scartata dal giocatore precedente, oppure deve essere dello stesso numero, oppure puoi giocare la carta 'jolly' che ti permette anche di cambiare colore; se non hai nessuna di queste carte, peschi una carta dal mazzo e se essa e' compatibile con quella scartata dall'avversario, puoi scartarla, altrimenti salti il turno e passa al giocatore successivo;"<<endl;
    trattocol();
    cout<<"Se un giocatore gioca la carta 'P', il giocatore successivo pesca due carte e salta il turno;";

    setcolor(113);
    cout<<endl<<endl<<"!!!";
    setcolor(112);
    cout<<" Il giocatore che finisce le carte per primo vince. ";
    setcolor(113);
    cout<<"!!!"<<endl<<endl;
    setcolor(112);

    system("pause");
    system("cls");
}

//void che modifica il colore del jolly
void colorejolly(tipocarta &carta)
{
    char *colore;
    colore=new char;
    do{
        cout<<"Quale colore vuoi scegliere per il jolly (rosso, verde, blu, giallo) ?"<<endl;
        fflush(stdin);
        gets(colore);
      }while(strcmpi(colore,"rosso")!=0 && strcmpi(colore,"giallo")!=0 && strcmpi(colore,"blu")!=0 && strcmpi(colore,"verde")!=0);
    if(strcmpi(colore,"rosso")==0)
    {
        carta->colore=192;
    }
    if(strcmpi(colore,"blu")==0)
    {
        carta->colore=144;
    }
    if(strcmpi(colore,"verde")==0)
    {
        carta->colore=160;
    }
    if(strcmpi(colore,"giallo")==0)
    {
        carta->colore=224;
    }
}

//funzione che serve per controllare se la carta può essere scrtata o meno
bool controllascarto(int posizione, tipocarta mazzogioc, tipocarta scarti, bool &stop)
{
    //se true può scartare la carta
    //se false non può scartarla
    tipocarta cercato=ricseq_pos(mazzogioc,posizione);
    switch(cercato->numero)
    {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:{
                if(cercato->numero==scarti->numero || cercato->colore==scarti->colore){return true;}
                else{return false;}
                break;
               }
        case 8:{
                //il giocatore dopo si ferma
                if(cercato->numero==scarti->numero || cercato->colore==scarti->colore)
                {
                    stop=true;
                    return true;
                }
                else{return false;}
                break;
               }
        case 9:{
                colorejolly(cercato);
                return true;
                break;
               }
    }
}

//funzione che data una posizione sotto forma di stringa, ritorna il numero corrispondente (fino a 20 per sicurezza)
int traducipos(char *strpos)
{
    if(strcmp(strpos, "1")==0) return 1;
    if(strcmp(strpos, "2")==0) return 2;
    if(strcmp(strpos, "3")==0) return 3;
    if(strcmp(strpos, "4")==0) return 4;
    if(strcmp(strpos, "5")==0) return 5;
    if(strcmp(strpos, "6")==0) return 6;
    if(strcmp(strpos, "7")==0) return 7;
    if(strcmp(strpos, "8")==0) return 8;
    if(strcmp(strpos, "9")==0) return 9;
    if(strcmp(strpos, "10")==0) return 10;
    if(strcmp(strpos, "11")==0) return 11;
    if(strcmp(strpos, "12")==0) return 12;
    if(strcmp(strpos, "13")==0) return 13;
    if(strcmp(strpos, "14")==0) return 14;
    if(strcmp(strpos, "15")==0) return 15;
    if(strcmp(strpos, "16")==0) return 16;
    if(strcmp(strpos, "17")==0) return 17;
    if(strcmp(strpos, "18")==0) return 18;
    if(strcmp(strpos, "19")==0) return 19;
    if(strcmp(strpos, "20")==0) return 20;
    return 0;
}

//chiedere all'utente cosa vuole scartare
void chiedi(int &posizione, tipogioc gioc,tipocarta scarti, bool &stop)
{
    char *strpos;
    strpos=new char;
    //serve per controllare se ha delle carte da scartare o se deve pescare
    bool controllo;
    do{
        do{
            cout<<"Quale posizione occupa la carta che vuoi scartare"<<endl;
            fflush(stdin);
            gets(strpos);
            posizione=traducipos(strpos);
        }while(posizione<1 || posizione>gioc->cont);
        posizione--;
        controllo=controllascarto(posizione,gioc->maz,scarti,stop);
        if(controllo==false){cout<<"Non puoi scartare la carta scelta"<<endl;}
        if(posizione>=gioc->cont){cout<<"Questa posizione non esiste perche' non hai quel numero di carte"<<endl;}
      }while(controllo==false);

}

//void per mandare la carta scelta dall'utente nel mazzo degli scarti
void testa(tipocarta &scarti, tipocarta &carta)
{
    carta->succ=scarti;
    scarti=carta;
}

//funzione che controlla se l'utente può scartare le carte
bool controllopossibilitascartare(tipogioc gioc,tipocarta scarti)
{
    int cont=0;
    tipocarta app=gioc->maz;
    for(int i=0;i<gioc->cont;i++)
    {
        if(app->numero==scarti->numero || app->colore==scarti->colore || app->numero==9)
        {
            cont++;
        }
        app=app->succ;
    }
    if(cont>0) return true;
    else return false;
}

//void per i turni dei giocatori
void turno(tipocarta &mazzo, tipocarta &scarti, tipogioc listagioc, bool &vittoria, bool &stop, int &nrimaste, int &nscarti, int codgioc)
{
    int posizione;
    tipogioc gioc=cercagioc(listagioc, codgioc);
    cout<<"E' il turno di ";
    setcolor(coloregioc(codgioc));
    cout<<gioc->nom<<endl;
    setcolor(112);
    cout<<endl;
    visualavversari(listagioc, codgioc, ngioc);
    visualpile(mazzo, scarti, nrimaste, nscarti);

    //se e' stata scartata una pesca
    if(stop==true)
    {
        stop=false;
        pesca(mazzo, gioc->maz, nrimaste, gioc->cont, caso(nrimaste)-1,scarti,nscarti);
        pesca(mazzo, gioc->maz, nrimaste, gioc->cont, caso(nrimaste)-1,scarti,nscarti);
        setcolor(124);
        cout<<"Ti sono state aggiunte due carte e salti il turno"<<endl;
        setcolor(112);
        cout<<"Il tuo mazzo e':"<<endl;
        visualmazzo(gioc->maz);
    }
    else
    {
        cout<<"Il tuo mazzo e':"<<endl;
        visualmazzo(gioc->maz);
        //se il giocatore ha almenouna carta da scartare
        if(controllopossibilitascartare(gioc,scarti)==true)
        {
            chiedi(posizione,gioc,scarti,stop);
            tipocarta estrai=estrai_pos(gioc->maz,posizione);
            testa(scarti,estrai);
            gioc->cont--;
            nscarti++;
        }
        else{
                setcolor(121);
                cout<<"Ora pescherai una carta perche' le tue carte non possono essere scartate"<<endl<<endl;
                setcolor(112);
                system("pause");
                //gli faccio pescare le carte
                pesca(mazzo, gioc->maz, nrimaste, gioc->cont, caso(nrimaste)-1,scarti,nscarti);
                cout<<"Ora il tuo mazzo e'"<<endl;
                visualmazzo(gioc->maz);
                //se la carta pescata puo' essere scartata
                if(controllascarto(gioc->cont-1,gioc->maz,scarti,stop)==true)
                {
                    setcolor(122);
                    cout<<"La carta pescata e' stata scartata"<<endl<<endl;
                    setcolor(112);
                    tipocarta estrai=estrai_pos(gioc->maz,gioc->cont-1);
                    testa(scarti,estrai);
                    gioc->cont--;
                    nscarti++;
                }
                else{
                        setcolor(124);
                        cout<<"La carta pescata NON puo' essere scartata"<<endl<<endl;
                        setcolor(112);
                    }
            }
    }
    system("pause");
    system("cls");
    if(gioc->cont==0) vittoria=true;
    else
    {
        //Ora dico che il turno è andato avanti
        cout<<"Ora e' il turno di ";
        if(gioc->succ!=NULL)
        {
            setcolor(coloregioc(codgioc+1));
            cout<<gioc->succ->nom<<endl<<endl;

        }
        else
        {
            setcolor(coloregioc(1));
            cout<<listagioc->nom<<endl<<endl;
        }
        setcolor(112);
    }
    system("pause");
    system("cls");
}

//procedura che ritorna l'indirizo del nodo del giocatore che ha vinto
tipogioc cercavinc(tipogioc listagioc, tipogioc &vinc, int &pos)
{
    int i=1;
    tipogioc app=listagioc;
    while(app->cont!=0)
    {
        app=app->succ;
        i++;
    }
    pos=i;
    vinc=app;
}

void mesvit(int c);
//procedura che manda a video i messaggi di vittoria specifici per un giocatore
void messaggivittoria(tipogioc listagioc)
{
    tipogioc vinc;
    int posvinc;
    int col;
    cercavinc(listagioc, vinc, posvinc);
    cout<<"COMPLIMENTI, ";
    col=coloregioc(posvinc);
    setcolor(col);
    cout<<vinc->nom;
    setcolor(112);
    cout<<"!!!"<<endl<<endl;
    mesvit(col);
    setcolor(112);
    cout<<endl<<"Grazie per aver giocato!"<<endl;
    setcolor(119);
}

//void per fare passare i turni con i controlli in caso di vittoria
void gioco(tipocarta mazzo, tipocarta scarti, tipogioc listagioc, int &nrimaste, int &nscarti, bool &stop)
{
    do{
        //turno del primo giocatore
        turno(mazzo,scarti,listagioc, vittoria, stop, nrimaste, nscarti, 1);
        if(vittoria==false)
        {
            //turno del secondo giocatore
            turno(mazzo,scarti,listagioc, vittoria, stop, nrimaste, nscarti, 2);
            if(vittoria==false && ngioc>2)
            {
                //turno del terzo giocatore
                turno(mazzo,scarti,listagioc, vittoria, stop, nrimaste, nscarti, 3);
                if(vittoria==false && ngioc>3)
                {
                    //turno del quarto giocatore
                    turno(mazzo,scarti,listagioc, vittoria, stop, nrimaste, nscarti, 4);
                    if(vittoria==false && ngioc>4)
                    {
                        //turno del quinto giocatore
                        turno(mazzo,scarti,listagioc, vittoria, stop, nrimaste, nscarti, 5);
                    }
                }
            }
        }
    }while(vittoria==false);
    messaggivittoria(listagioc);
}

//procedura che manda a video una riga piu' scura del normale dato colore e lunghezza
void visriga2(int col, int n)
{
    char let=178;
    setcolor(col);
    for(int i=0; i<n; i++) cout<<let;
}

//procedura che manda a video una riga di stanga (true con l'ombra, false senza)
void i(bool om)
{
    if(om==true) visriga2(112, 1);
    visriga(0, 2);
    visriga(128, 2);
    visriga(0, 2);
}

//procedura che manda a video una riga di u
void u(bool nr)
{
    visriga(176, 3);
    i(true);
    visriga(176, 9);
    i(true);
    visriga(176, 2);
    visriga2(112, 1);
    visriga(0, 2);
    visriga(128, 2);
    if(nr==true) visriga(0, 2);
}

//procedura che manda a video una riga del pezzo obliquo della n
void n()
{
    visriga2(112, 2);
    visriga(0, 1);
    visriga(128, 2);
    visriga(0, 1);
}

//procedura che manda a video una riga del pezzo centrale della O dati due colori
void c(int col1, int col2)
{
    visriga(240, 1);
    visriga(col1, 3);
    visriga(240, 2);
    visriga(col2, 3);
    visriga(240, 1);
}

//procedura che manda a video il titolo del gioco
void titolo()
{
    visriga(176, 79);
    cout<<endl;
    visriga(176, 79);
    cout<<endl;
    visriga(176, 4);
    visriga(0, 6);
    visriga(176, 10);
    visriga(0, 6);
    visriga(176, 3);
    visriga(0, 7);
    visriga(176, 9);
    visriga(0, 6);
    visriga(176, 3);
    visriga(0, 22);
    visriga(176, 3);
    cout<<endl;
    u(false);
    visriga(128, 2);
    visriga(0, 2);
    visriga(176, 7);
    i(true);
    visriga(176, 2);
    visriga2(112, 1);
    visriga(0, 2);
    visriga(128, 18);
    visriga(0, 2);
    visriga(176, 3);
    cout<<endl;
    u(false);
    visriga(128, 4);
    visriga(0, 1);
    visriga(176, 6);
    i(true);
    visriga(176, 2);
    i(true);
    visriga(0, 10);
    i(false);
    visriga(176, 3);
    cout<<endl;
    u(true);
    visriga(0, 1);
    visriga(128, 2);
    visriga(0, 1);
    visriga(176, 5);
    i(true);
    visriga(176, 2);
    i(true);
    visriga(240, 10);
    i(false);
    visriga(176, 3);
    cout<<endl;
    u(true);
    visriga2(112, 1);
    visriga(0, 1);
    visriga(128, 2);
    visriga(0, 1);
    visriga(176, 4);
    i(true);
    visriga(176, 2);
    i(true);
    c(192, 144);
    i(false);
    visriga(176, 3);
    cout<<endl;
    u(true);
    n();
    visriga(176, 3);
    i(true);
    visriga(176, 2);
    i(true);
    c(192, 144);
    i(false);
    visriga(176, 3);
    cout<<endl;
    u(true);
    visriga(176, 1);
    n();
    visriga(176, 2);
    i(true);
    visriga(176, 2);
    i(true);
    visriga(240, 10);
    i(false);
    visriga(176, 3);
    cout<<endl;
    u(true);
    visriga(176, 2);
    n();
    visriga(176, 1);
    i(true);
    visriga(176, 2);
    i(true);
    c(224, 160);
    i(false);
    visriga(176, 3);
    cout<<endl;
    u(true);
    visriga(176, 3);
    n();
    i(true);
    visriga(176, 2);
    i(true);
    c(224, 160);
    i(false);
    visriga(176, 3);
    cout<<endl;
    u(true);
    visriga(176, 4);
    n();
    i(false);
    visriga(176, 2);
    i(true);
    visriga(240, 10);
    i(false);
    visriga(176, 3);
    cout<<endl;
    visriga(176, 3);
    visriga2(112, 1);
    visriga(0, 2);
    visriga(128, 2);
    visriga(0, 14);
    visriga(128, 2);
    visriga(0, 2);
    visriga(176, 2);
    i(true);
    visriga(176, 5);
    visriga2(112, 2);
    visriga(0, 1);
    visriga(128, 6);
    visriga(0, 2);
    visriga(176, 2);
    i(true);
    visriga(0, 10);
    i(false);
    visriga(176, 3);
    cout<<endl;
    visriga(176, 3);
    visriga2(112, 1);
    visriga(0, 2);
    visriga(128, 18);
    visriga(0, 2);
    visriga(176, 2);
    i(true);
    visriga(176, 6);
    visriga2(112, 2);
    visriga(0, 2);
    visriga(128, 4);
    visriga(0, 2);
    visriga(176, 2);
    visriga2(112, 1);
    visriga(0, 2);
    visriga(128, 18);
    visriga(0, 2);
    visriga(176, 3);
    cout<<endl;
    visriga(176, 3);
    visriga2(112, 1);
    visriga(0, 22);
    visriga(176, 2);
    visriga2(112, 1);
    visriga(0, 6);
    visriga(176, 7);
    visriga2(112, 2);
    visriga(0, 7);
    visriga(176, 2);
    visriga2(112, 1);
    visriga(0, 22);
    visriga(176, 3);
    cout<<endl;
    visriga(176, 3);
    visriga2(112, 22);
    visriga(176, 3);
    visriga2(112, 6);
    visriga(176, 9);
    visriga2(112, 7);
    visriga(176, 3);
    visriga2(112, 22);
    visriga(176, 4);
    cout<<endl;
    visriga(176, 79);
    cout<<endl;
    visriga(176, 79);
    cout<<endl;
    setcolor(112);
}

//procedura che manda a video il messaggio "Hai vinto" dato un colore della scritta
void mesvit(int c)
{
    //1
    //h
    visriga(112, 2);
    visriga(c, 2);
    visriga(112, 2);
    visriga(c, 2);
    visriga(112, 1);
    //a
    visriga(c, 6);
    visriga(112, 1);
    //i
    visriga(c, 2);
    visriga(112, 4);
    //v
    visriga(c, 2);
    visriga(112, 3);
    visriga(c, 2);
    visriga(112, 1);
    //i
    visriga(c, 2);
    visriga(112, 1);
    //n
    visriga(c, 3);
    visriga(112, 3);
    visriga(c, 2);
    visriga(112, 1);
    //t
    visriga(c, 6);
    visriga(112, 1);
    //o
    visriga(c, 6);
    visriga(112, 1);
    //!
    visriga(c, 2);
    cout<<endl;

    //2
    //h
    visriga(112, 2);
    visriga(c, 2);
    visriga(112, 2);
    visriga(c, 2);
    visriga(112, 1);
    //a
    visriga(c, 2);
    visriga(112, 2);
    visriga(c, 2);
    visriga(112, 1);
    //i
    visriga(c, 2);
    visriga(112, 4);
    //v
    visriga(c, 2);
    visriga(112, 3);
    visriga(c, 2);
    visriga(112, 1);
    //i
    visriga(c, 2);
    visriga(112, 1);
    //n
    visriga(c, 4);
    visriga(112, 2);
    visriga(c, 2);
    visriga(112, 3);
    //t
    visriga(c, 2);
    visriga(112, 3);
    //o
    visriga(c, 2);
    visriga(112, 2);
    visriga(c, 2);
    visriga(112, 1);
    //!
    visriga(c, 2);
    cout<<endl;

    //3
    //h
    visriga(112, 2);
    visriga(c, 6);
    visriga(112, 1);
    //a
    visriga(c, 6);
    visriga(112, 1);
    //i
    visriga(c, 2);
    visriga(112, 4);
    //v
    visriga(c, 2);
    visriga(112, 3);
    visriga(c, 2);
    visriga(112, 1);
    //i
    visriga(c, 2);
    visriga(112, 1);
    //n
    visriga(c, 2);
    visriga(112, 1);
    visriga(c, 2);
    visriga(112, 1);
    visriga(c, 2);
    visriga(112, 3);
    //t
    visriga(c, 2);
    visriga(112, 3);
    //o
    visriga(c, 2);
    visriga(112, 2);
    visriga(c, 2);
    visriga(112, 1);
    //!
    visriga(c, 2);
    cout<<endl;

    //4
    //h
    visriga(112, 2);
    visriga(c, 2);
    visriga(112, 2);
    visriga(c, 2);
    visriga(112, 1);
    //a
    visriga(c, 2);
    visriga(112, 2);
    visriga(c, 2);
    visriga(112, 1);
    //i
    visriga(c, 2);
    visriga(112, 5);
    //v
    visriga(c, 2);
    visriga(112, 1);
    visriga(c, 2);
    visriga(112, 2);
    //i
    visriga(c, 2);
    visriga(112, 1);
    //n
    visriga(c, 2);
    visriga(112, 2);
    visriga(c, 4);
    visriga(112, 3);
    //t
    visriga(c, 2);
    visriga(112, 3);
    //o
    visriga(c, 2);
    visriga(112, 2);
    visriga(c, 2);
    visriga(112, 1);
    //!
    cout<<endl;

    //5
    //h
    visriga(112, 2);
    visriga(c, 2);
    visriga(112, 2);
    visriga(c, 2);
    visriga(112, 1);
    //a
    visriga(c, 2);
    visriga(112, 2);
    visriga(c, 2);
    visriga(112, 1);
    //i
    visriga(c, 2);
    visriga(112, 6);
    //v
    visriga(c, 3);
    visriga(112, 3);
    //i
    visriga(c, 2);
    visriga(112, 1);
    //n
    visriga(c, 2);
    visriga(112, 3);
    visriga(c, 3);
    visriga(112, 3);
    //t
    visriga(c, 2);
    visriga(112, 3);
    //o
    visriga(c, 6);
    visriga(112, 1);
    //!
    visriga(c, 2);
    cout<<endl;
    setcolor(112);
}

//int main
int main()
{
    randomize;
    system("color 70");
    cout<<"Prima di cominciare, espandi la finestra per una migliore esperienza di gioco"<<endl;
    system("pause");
    system("cls");
    titolo();
    cout<<endl;

    //mando a video le regole
    regole();

    //creo e carico i mazzo
    caricamazzo(mazzo);

    //mettere la prima carta negli scarti
    primascarti(mazzo, scarti, nrimaste, nscarti);

    //creo e do' il nome ai giocatori
    giocatori(ngioc);
    creagioc(listagioc, ngioc, nrimaste,scarti,nscarti);
    cout<<"I mazzi sono stati creati"<<endl;
    cout<<"Ora iniziano i turni dei giocatori"<<endl<<endl;
    system("pause");
    system("cls");

    //Iniziano i turni
    gioco(mazzo,scarti,listagioc, nrimaste, nscarti, stop);
    system("pause");
}
