#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>
#include<fcntl.h>
#include <io.h>
#define ESC 27
struct Produkt
{
    char nazwa[25];
    int identyfikator;
    char typ[25];
    char producent[25];
    double cenaNetto;
    double VAT;
    double cenaBrutto;
};
void gotoxy(short x, short y);
FILE *fp1,*fp2;

char *tryb1,*tryb2;
char menu (void);
void dopiszStrukture(int id);
void sortuj();
void gotoxy(short x, short y);
void utworzBaze (void);
void usunBaze(void );
void przegladBazy();
void sortowanieBazy();
void drukujStrukt( struct Produkt st);
struct Produkt wczytajStrukt(void);
void drukujStatus(void);
void modyfikacjaBazy(int id, struct Produkt st);

char nazwaBazy[11];

int main(int argc, char *argv[])
{
    struct Produkt produkty[5]=
    {
        {"Gitara elektryczna", 1, "Stratocaster", "Fender", 4347.50, 23},
        {"Gitara elektryczna", 3, "Les Paul", "Gibson", 3999.99, 23},
        {"Gitara akustyczna", 2, "Dreadnought", "Yamaha", 1200.00, 23},
        {"Gitara basowa", 5, "Precision", "Squier", 1549.95, 23},
        {"Wzmacniacz gitarowy", 4, "Twin Reverb", "Fender", 7199.00, 23}
    };
    for(int i=0; i<5; i++)
    {
        double vat=1+produkty[i].VAT/100;
        produkty[i].cenaBrutto=produkty[i].cenaNetto*vat;
    }

    fp1=fopen("baza23.dat", "w+b");
    fwrite(&produkty,sizeof(struct Produkt),5,fp1);
    fclose(fp1);
    menu();
    getchar();
    return 0;
}

void utworzBaze (void)
{
    char nazwa[5];
    int i,licz=0,ok,ok1=1,ok2=1,ok3=1;
    int x=20,y=20;
    system("cls");
    gotoxy(x,y);
    printf(" Metoda utworzBaze");
    getchar();
    do
    {
        printf("\n Podaj nazwe bazy format XXXXdd.dat:");
        fflush(stdin);
        scanf("%11s",nazwaBazy);
        ok1=1,ok2=1,ok3=1;
        for(int i=0; i<4; i++)
        {
            if(isalpha(nazwaBazy[i])==0)
                ok1=0;
        }
        for(int i=4; i<6; i++)
        {
            if(isdigit(nazwaBazy[i])==0)
                ok2=0;
        }

        strcpy(nazwa, nazwaBazy+6);

        if(strcmp(nazwa, ".dat")!=0)
            ok3=0;

        ok=ok1*ok2*ok3;

        if(!ok)
        {
            printf("\n nazwa bazy nie jest prawidlowa");
        }


    }
    while(ok==0);
    fp1=fopen(nazwaBazy,"r+b");
    if(fp1!=NULL)
    {
        printf("\n Plik %s juz istnieje!", nazwaBazy);
        getchar();
        exit(1);
    }
    fclose(fp1);


    fp1=fopen(nazwaBazy,"w+b");
    if(fp1==NULL)
    {
        printf("\n Plik %s nie zostal utworzony", nazwa);
        getchar();
        exit(1);
    }
    dopiszStrukture(0);
    przegladBazy();
}
void otworzBaze (void)
{
    char nazwa[5];
    int i,licz=0,ok,ok1=1,ok2=1,ok3=1;
    int x=20,y=20;
    system("cls");
    gotoxy(x,y);
    printf(" Metoda otworzBaze");
    getchar();
    do
    {
        printf("\n Podaj nazwe bazy format XXXXdd.dat:");
        fflush(stdin);
        scanf("%11s",nazwaBazy);
        ok1=1,ok2=1,ok3=1;
        for(int i=0; i<4; i++)
        {
            if(isalpha(nazwaBazy[i])==0)
                ok1=0;
        }
        for(int i=4; i<6; i++)
        {
            if(isdigit(nazwaBazy[i])==0)
                ok2=0;
        }

        strcpy(nazwa, nazwaBazy+6);

        if(strcmp(nazwa, ".dat")!=0)
            ok3=0;

        ok=ok1*ok2*ok3;

        if(!ok)
        {
            printf("\n nazwa bazy nie jest prawidlowa");
        }


    }
    while(ok==0);
    fp1=fopen(nazwaBazy,"r+b");
    if(fp1==NULL)
    {
        printf("\n Plik %s nie istnieje!", nazwaBazy);

        getchar();
        exit(1);
    }
    przegladBazy();
}
void usunBaze(void )
{
    char nazwa[5];
    int i,licz=0,ok,ok1=0,ok2=0,ok3=0;
    int x=20,y=20,wynik;
    system("cls");
    gotoxy(x,y);
    do
    {
        printf("\n Podaj nazwe bazy format XXXXdd.dat:");
        fflush(stdin);
        scanf("%11s",nazwaBazy);
        ok1=1,ok2=1,ok3=1;
        for(int i=0; i<4; i++)
        {
            if(isalpha(nazwaBazy[i])==0)
                ok1=0;
        }
        for(int i=4; i<6; i++)
        {
            if(isdigit(nazwaBazy[i])==0)
                ok2=0;
        }

        strcpy(nazwa, nazwaBazy+6);

        if(strcmp(nazwa, ".dat")!=0)
            ok3=0;

        ok=ok1*ok2*ok3;
        if(!ok)
        {
            printf("\n nazwa bazy nie jest prawidlowa");
        }


    }
    while(ok==0);
    gotoxy(x,22);
    fp1=fopen(nazwaBazy,"rb");
    if(fp1==NULL)
        printf("\n Plik %s nie moze byc usuniety", nazwaBazy);
    else
    {
        fclose(fp1);
        wynik=remove(nazwaBazy);
        if (wynik)
            printf(" Plik nie zostal usuniety");
        else
            printf(" Plik zostal usuniety");
    }
    getchar();
    return ;
}
char menu (void)
{
    char ch;
    int x,y;
    x=20;
    y=8;
    gotoxy(x,y);
    printf("============================");
    gotoxy(x,y+1);
    printf("1.Otworz baze danych");
    gotoxy(x,y+2);
    printf("2.Utworz nowa baze");
    gotoxy(x,y+3);
    printf("3. Usun baze");
    gotoxy(x,y+4);
    printf("4.Zakoncz program");
    gotoxy(x,y+5);
    printf(" Wybierz opcje :");
    fflush(stdin);
    do
    {
        fflush(stdin);
        ch=getch();
    }
    while ( ch!='1' && ch!='2'&& ch!='3'&& ch!='4');
    switch(ch)
    {
    case '1':
        gotoxy(20,18);
        printf(" Wybrano opcja 1 - Enter");
        getchar();
        otworzBaze();
        break;
    case '2':
        gotoxy(20,18);
        printf(" Wybrano opcja 2 - Enter ");
        utworzBaze();
        break;
    case '3':
        gotoxy(20,18);
        printf(" Wybrano opcja 3 - Enter ");
        usunBaze();
        break;
    case '4':
        gotoxy(20,18);
        printf(" Wybrano opcja 4 - Enter ");
        getchar();
        exit(0);
    }

}
void gotoxy(short x, short y)
{
    COORD pos = {x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void przegladBazy(void)
{
    struct Produkt st;
    int x=1,y=24;
    int id=0;
    int iloscBajtow,iloscElementow;
    fseek(fp1,0,SEEK_END);
    iloscBajtow=ftell(fp1);
    iloscElementow=iloscBajtow/sizeof(struct Produkt);
    fseek(fp1,0,SEEK_SET);
    getchar();
    char ch;
    system("cls");
    gotoxy(x,y);
    drukujStatus();

    while (1)
    {
        fseek(fp1,0,SEEK_END);
        iloscBajtow=ftell(fp1);
        iloscElementow=iloscBajtow/sizeof(struct Produkt);
        fseek(fp1,0,SEEK_SET);

        if(id<0)
            id=0;
        if(id>iloscElementow-1)
            id=iloscElementow-1;

        fseek(fp1,id*sizeof(struct Produkt),SEEK_SET);
        fread(&st,sizeof(struct Produkt),1,fp1);
        drukujStrukt(st);
        drukujStatus();

        do
        {
            fflush(stdin);
            ch=toupper(getch());
        }
        while ( ch!='Y' && ch!='D' && ch!='B'&& ch!='G'&& ch!='H'&&ch!='R'&& ch!='M'\
                &&ch!='S'&&ch!=ESC);
        //Y-up B-down G-Home H-End R-read M-modify S-sort D-del ESC-exit
        switch(ch)
        {
        case 'D':
            gotoxy(20,18);
            printf(" Wybrano opcja D - Enter");
            getchar();
            usuwanieStrukturyZbazy();
            fflush(stdin);
            drukujStatus();
            break;

        case 'Y':
            gotoxy(20,18);
            printf(" Wybrano opcja Y - Enter");
            id++;
            getchar();
            fflush(stdin);
            drukujStatus();
            break;
        case 'B':
            gotoxy(20,18);
            printf(" Wybrano opcja B - Enter ");
            id--;
            getchar();
            drukujStatus();
            break;
        case 'G':
            gotoxy(20,18);
            printf(" Wybrano opcja G - Enter ");
            id=0;
            getchar();
            drukujStatus();
            break;
        case 'H':
            gotoxy(20,18);
            printf(" Wybrano opcja H - Enter ");
            id=iloscElementow-1;
            getchar();
            drukujStatus();
            break;
        case 'R':
            gotoxy(20,18);
            printf(" Wybrano opcja R - Enter ");
            getchar();
            fseek(fp1,id*sizeof(struct Produkt),SEEK_SET);
            fread(&st,sizeof(struct Produkt),1,fp1);
            drukujStrukt(st);
            drukujStatus();
            break;
        case 'M':
            gotoxy(20,18);
            printf(" Wybrano opcja M - Enter ");
            modyfikacjaBazy(id,st);
            getchar();
            break;
        case 'S':
            gotoxy(20,18);
            printf(" Wybrano opcja S - Enter ");
            sortuj();
            break;
        case 'U':
            gotoxy(20,18);
            printf(" Wybrano opcja D - Enter ");
            dopiszStrukture(id);
            break;
        case ESC:
            gotoxy(20,18);
            printf(" Wybrano opcja ESC - Enter ");
            getchar();
            exit(0);
            break;
        }
    }
    return ;
}
void sortowanieBazy(void)
{
    int x=20,y=20;
    system("cls");
    gotoxy(x,y);
    printf(" Metoda sortujBaze");
    getchar();
    return ;
}
void drukujStrukt( struct Produkt st)
{
    int x=20,y=8;
    system("cls");
    gotoxy(x,y);
    printf("Nazwa:%s", st.nazwa);
    gotoxy(x,y+1);
    printf("Identyfikator:%d", st.identyfikator);
    gotoxy(x,y+2);
    printf("Typ :%s", st.typ);
    gotoxy(x,y+3);
    printf("Producent:%s", st.producent);
    gotoxy(x,y+4);
    printf("Cena netto:%.2f",st.cenaNetto);
    gotoxy(x,y+5);
    printf("VAT:%.2f",st.VAT);
    gotoxy(x,y+6);
    printf("Cena brutto:%.2f",st.cenaBrutto);
}
struct Produkt wczytajStrukt(void)
{
    struct Produkt st;
    int k;
    fflush(stdin);
    int x=20,y=8;
    system("cls");
    gotoxy(x,y);
    fflush(stdin);
    printf("Nazwa:");
    do
    {
        k=scanf("%s", &st.nazwa);

        if(!k)
            printf("Niepoprawny format!\n");

        fflush(stdin);
    }
    while(!k);

    gotoxy(x,y+1);
    printf("Identyfikator:");
    do
    {
        k=scanf("%d", &st.identyfikator);
        if(!k)
            printf("Niepoprawny format!\n");
        fflush(stdin);
    }
    while(!k);
    fflush(stdin);
    gotoxy(x,y+2);
    printf("Producent:");
    do
    {
        k=scanf("%s", &st.producent);
        if(!k)
            printf("Niepoprawny format!\n");
        fflush(stdin);
    }
    while(!k);
    fflush(stdin);
    gotoxy(x,y+3);
    printf("Typ:");
    do
    {
        k=scanf("%s", &st.typ);
        if(!k)
            printf("Niepoprawny format!\n");
        fflush(stdin);
    }
    while(!k);
    fflush(stdin);
    gotoxy(x,y+4);
    printf("Cena netto:");
    do
    {
        k=scanf("%lf", &st.cenaNetto);
        if(!k)
            printf("Niepoprawny format!\n");
        fflush(stdin);
    }
    while(!k);
    gotoxy(x,y+5);
    printf("VAT:");
    do
    {
        k=scanf("%lf", &st.VAT);
        if(!k)
            printf("Niepoprawny format!\n");
        fflush(stdin);
    }
    while(!k);
    st.cenaBrutto=st.cenaNetto*(1+st.VAT/100.0);
    return st;
}
void drukujStatus(void)
{
    gotoxy(1,24);
    printf(" Y-up B-down G-Home H-End R-read M-modify S-sort D-del ESC-exit");

}
void modyfikacjaBazy(int id, struct Produkt st)
{
    gotoxy(20,18);
    printf("Jakie pole chcesz zmienic?\n");
    printf(" (nazwa/identyfikator/typ/producent/netto/vat/brutto) ");


    char typ[20];
    scanf("%s", typ);
    for(int i=0; i<20; i++)
        typ[i]=tolower(typ[i]);

    if(strcmp(typ,"nazwa")==0)
    {
        printf("Podaj nazwe: ");
        int k;
        do
        {
            k=scanf("%s", &st.nazwa);
            if(!k)
                printf("Niepoprawny format!\n");
            fflush(stdin);
        }
        while(!k);
    }
    else if(strcmp(typ,"identyfikator")==0)
    {
        printf("Podaj identyfikator: ");
        int k;
        do
        {
            k=scanf("%d", &st.identyfikator);
            if(!k)
                printf("Niepoprawny format!\n");
            fflush(stdin);
        }
        while(!k);

    }
    else if(strcmp(typ,"typ")==0)
    {
        printf("Podaj typ: ");
        int k;
        do
        {
            k=scanf("%s", &st.typ);
            if(!k)
                printf("Niepoprawny format!\n");
            fflush(stdin);
        }
        while(!k);

    }
    else if(strcmp(typ,"producent")==0)
    {
        printf("Podaj producenta: ");
        int k;
        do
        {
            k=scanf("%s", &st.producent);
            if(!k)
                printf("Niepoprawny format!\n");
            fflush(stdin);
        }
        while(!k);

    }
    else if(strcmp(typ,"netto")==0)
    {
        printf("Podaj cene netto: ");
        int k;
        do
        {
            k=scanf("%lf", &st.cenaNetto);
            if(!k)
                printf("Niepoprawny format!\n");
            fflush(stdin);
        }
        while(!k);

    }
    else if(strcmp(typ,"brutto")==0)
    {
        printf("Podaj cene brutto: ");
        int k;
        do
        {
            k=scanf("%lf", &st.cenaBrutto);
            if(!k)
                printf("Niepoprawny format!\n");
            fflush(stdin);
        }
        while(!k);

    }
    else if(strcmp(typ,"vat")==0)
    {
        printf("Podaj vat: ");
        int k;
        do
        {
            k=scanf("%lf", &st.VAT);
            if(!k)
                printf("Niepoprawny format!\n");
            fflush(stdin);
        }
        while(!k);

    }
    else
    {
        printf("Niepoprawna nazwa pola!");
        getchar();
        return 0;
    }
    fseek(fp1,id*sizeof(struct Produkt),SEEK_SET);
    fwrite(&st,sizeof(struct Produkt), 1, fp1);

}

void dopiszStrukture(int id)
{
    struct Produkt st;
    st=wczytajStrukt();
    fseek(fp1,sizeof(struct Produkt),SEEK_END);
    fseek(fp1,-1*sizeof(struct Produkt),SEEK_CUR);
    fwrite(&st,sizeof(struct Produkt), 1, fp1);

}

void sortuj()
{
    int x=20,y=20;
    system("cls");
    gotoxy(x,y);
    printf(" Metoda sortujBaze");
    gotoxy(20,18);
    printf("Wedlug ktorego pola chcesz sortowac: \n");
    printf(" (nazwa/identyfikator/typ/producent/netto/vat/brutto) ");
    char typ[20];
    scanf("%s", typ);
    for(int i=0; i<20; i++)
        typ[i]=tolower(typ[i]);
    int kont=0;
    struct Produkt st1,st2;
    fseek(fp1,0,SEEK_END);
    int iloscBajtow=ftell(fp1);
    int iloscElementow=iloscBajtow/sizeof(struct Produkt);
    fseek(fp1,0,SEEK_SET);
    fflush(stdin);

    if(strcmp(typ,"nazwa")==0)
    {
        for(int i=0; i<iloscElementow-1; i++)
        {
            fseek(fp1,i*sizeof(struct Produkt),SEEK_SET);
            fread(&st1,sizeof(struct Produkt),1,fp1);
            for(int j=i; j<iloscElementow; j++)
            {
                fseek(fp1,j*sizeof(struct Produkt),SEEK_SET);
                fread(&st2,sizeof(struct Produkt),1,fp1);

                if(strcmp(st1.nazwa,st2.nazwa)>0)
                {
                    fseek(fp1,i*sizeof(struct Produkt),SEEK_SET);
                    fwrite(&st2,sizeof(struct Produkt),1,fp1);
                    fseek(fp1,j*sizeof(struct Produkt),SEEK_SET);
                    fwrite(&st1,sizeof(struct Produkt),1,fp1);
                    st1=st2;
                }
            }
        }
    }

    else if(strcmp(typ,"identyfikator")==0)
    {
        for(int i=0; i<iloscElementow-1; i++)
        {
            fseek(fp1,i*sizeof(struct Produkt),SEEK_SET);
            fread(&st1,sizeof(struct Produkt),1,fp1);
            for(int j=i; j<iloscElementow; j++)
            {
                fseek(fp1,j*sizeof(struct Produkt),SEEK_SET);
                fread(&st2,sizeof(struct Produkt),1,fp1);

                if(st1.identyfikator>st2.identyfikator)
                {
                    fseek(fp1,i*sizeof(struct Produkt),SEEK_SET);
                    fwrite(&st2,sizeof(struct Produkt),1,fp1);
                    fseek(fp1,j*sizeof(struct Produkt),SEEK_SET);
                    fwrite(&st1,sizeof(struct Produkt),1,fp1);
                    st1=st2;
                }
            }
        }
    }
    else if(strcmp(typ,"typ")==0)
    {
        for(int i=0; i<iloscElementow-1; i++)
        {
            fseek(fp1,i*sizeof(struct Produkt),SEEK_SET);
            fread(&st1,sizeof(struct Produkt),1,fp1);
            for(int j=i; j<iloscElementow; j++)
            {
                fseek(fp1,j*sizeof(struct Produkt),SEEK_SET);
                fread(&st2,sizeof(struct Produkt),1,fp1);

                if(strcmp(st1.typ,st2.typ)>0)
                {
                    fseek(fp1,i*sizeof(struct Produkt),SEEK_SET);
                    fwrite(&st2,sizeof(struct Produkt),1,fp1);
                    fseek(fp1,j*sizeof(struct Produkt),SEEK_SET);
                    fwrite(&st1,sizeof(struct Produkt),1,fp1);
                    st1=st2;
                }
            }
        }
    }
    else if(strcmp(typ,"producent")==0)
    {
        for(int i=0; i<iloscElementow-1; i++)
        {
            fseek(fp1,i*sizeof(struct Produkt),SEEK_SET);
            fread(&st1,sizeof(struct Produkt),1,fp1);
            for(int j=i; j<iloscElementow; j++)
            {
                fseek(fp1,j*sizeof(struct Produkt),SEEK_SET);
                fread(&st2,sizeof(struct Produkt),1,fp1);

                if(strcmp(st1.producent,st2.producent)>0)
                {
                    fseek(fp1,i*sizeof(struct Produkt),SEEK_SET);
                    fwrite(&st2,sizeof(struct Produkt),1,fp1);
                    fseek(fp1,j*sizeof(struct Produkt),SEEK_SET);
                    fwrite(&st1,sizeof(struct Produkt),1,fp1);
                    st1=st2;
                }
            }
        }
    }
    else if(strcmp(typ,"netto")==0)
    {
        for(int i=0; i<iloscElementow-1; i++)
        {
            fseek(fp1,i*sizeof(struct Produkt),SEEK_SET);
            fread(&st1,sizeof(struct Produkt),1,fp1);
            for(int j=i; j<iloscElementow; j++)
            {
                fseek(fp1,j*sizeof(struct Produkt),SEEK_SET);
                fread(&st2,sizeof(struct Produkt),1,fp1);

                if(st1.cenaNetto>st2.cenaNetto)
                {
                    fseek(fp1,i*sizeof(struct Produkt),SEEK_SET);
                    fwrite(&st2,sizeof(struct Produkt),1,fp1);
                    fseek(fp1,j*sizeof(struct Produkt),SEEK_SET);
                    fwrite(&st1,sizeof(struct Produkt),1,fp1);
                    st1=st2;
                }
            }
        }
    }
    else if(strcmp(typ,"brutto")==0)
    {
        for(int i=0; i<iloscElementow-1; i++)
        {
            fseek(fp1,i*sizeof(struct Produkt),SEEK_SET);
            fread(&st1,sizeof(struct Produkt),1,fp1);
            for(int j=i; j<iloscElementow; j++)
            {
                fseek(fp1,j*sizeof(struct Produkt),SEEK_SET);
                fread(&st2,sizeof(struct Produkt),1,fp1);

                if(st1.cenaBrutto>st2.cenaBrutto)
                {
                    fseek(fp1,i*sizeof(struct Produkt),SEEK_SET);
                    fwrite(&st2,sizeof(struct Produkt),1,fp1);
                    fseek(fp1,j*sizeof(struct Produkt),SEEK_SET);
                    fwrite(&st1,sizeof(struct Produkt),1,fp1);
                    st1=st2;
                }
            }
        }
    }
    else if(strcmp(typ,"vat")==0)
    {
        for(int i=0; i<iloscElementow-1; i++)
        {
            fseek(fp1,i*sizeof(struct Produkt),SEEK_SET);
            fread(&st1,sizeof(struct Produkt),1,fp1);
            for(int j=i; j<iloscElementow; j++)
            {
                fseek(fp1,j*sizeof(struct Produkt),SEEK_SET);
                fread(&st2,sizeof(struct Produkt),1,fp1);

                if(st1.VAT>st2.VAT)
                {
                    fseek(fp1,i*sizeof(struct Produkt),SEEK_SET);
                    fwrite(&st2,sizeof(struct Produkt),1,fp1);
                    fseek(fp1,j*sizeof(struct Produkt),SEEK_SET);
                    fwrite(&st1,sizeof(struct Produkt),1,fp1);
                    st1=st2;
                }
            }
        }
    }
    else
    {
        printf("\n\nNiepoprawna nazwa pola!");
        getchar();
        getchar();
        return 0;
    }

    getchar();

}

void usuwanieStrukturyZbazy(void)
{
    struct Produkt bufs;
    fpos_t nrRek;
    int aktPozycjaWskaznikaPliku;
    int rozmiarPlikBajty;
    fgetpos(fp1, &nrRek);

    fseek (fp1,-1*sizeof( struct Produkt),SEEK_END);
    fread(&bufs,sizeof( struct Produkt),1,fp1);
    fsetpos(fp1, &nrRek);
    fseek(fp1, -sizeof( struct Produkt),SEEK_CUR);
    aktPozycjaWskaznikaPliku=ftell(fp1)/sizeof( struct Produkt);


    fwrite(&bufs,sizeof(struct Produkt),1,fp1);

    fseek(fp1,0,SEEK_END);
    rozmiarPlikBajty=ftell(fp1);

    fclose(fp1);
    int handle;
    handle=open(nazwaBazy, O_RDWR);
    if (handle!=-1)
    {
        chsize(handle, rozmiarPlikBajty-sizeof(struct Produkt));
    }
    else
        printf("\n Plik nie zostal otwarty");
    close(handle);

    fp1=fopen(nazwaBazy,"r+b");
    getchar();
}
