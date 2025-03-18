#include<stdio.h>
#include<ctype.h>
#include<stdarg.h>
#include<string.h>
#include<conio2.h>

void newClearScr(int LI, int CI, int LF, int CF)
{
    int i;
    int j;
    for (i = LI; i <= LF; i++)
    {
        for (j = CI; j <= CF; j++)
        {
            gotoxy(j, i);
            printf("%c", 32);
        }
    }
}

void limpandoArea(char regiao[])
{
    if (strcmp(regiao, "topo") == 0){
        newClearScr(3, 3, 3, 70);
//        textbackground(15);
	}
    else if (strcmp(regiao, "alerta") == 0)
        newClearScr(23, 3, 23, 78);
    else if (strcmp(regiao, "subMenu") == 0)
    {
        newClearScr(23, 3, 23, 78);
        newClearScr(8, 3, 20, 26);
        newClearScr(6, 29, 20, 78);
    }
    else if (strcmp(regiao, "rightside") == 0)
        newClearScr(6, 29, 20, 78);
}

char *conv(unsigned int numero, int base)
{
    static char Rep[] = "0123456789ABCDEF";
    static char buffer[50];
    char *ptr;

    ptr = &buffer[49];
    *ptr = '\0';

    do
    {
        *--ptr = Rep[numero % base];
        numero /= base;
    } while (numero != 0);
    return ptr;
}

void consolePrintf(char *consolePos, char *cor, int _i, char *str, ...)
{
    unsigned int i;
    char *transc;
    char *s;

    va_list arg;
    va_start(arg, str);
    if (strcmp(cor, "preto") == 0)
        textcolor(0);
    else if (strcmp(cor, "azul") == 0)
        textcolor(1);
    else if (strcmp(cor, "verde") == 0)
        textcolor(2);
    else if (strcmp(cor, "ciano") == 0)
        textcolor(3);
    else if (strcmp(cor, "vermelho") == 0)
        textcolor(4);
    else if (strcmp(cor, "rosa") == 0)
        textcolor(5);
    else if (strcmp(cor, "marrom") == 0)
        textcolor(6);
    else if (strcmp(cor, "branco") == 0)
        textcolor(7);
    else if (strcmp(cor, "cinza_claro") == 0)
        textcolor(8);
    else if (strcmp(cor, "azul_claro") == 0)
        textcolor(9);
    else if (strcmp(cor, "verde_claro") == 0)
        textcolor(10);
    else if (strcmp(cor, "ciano_claro") == 0)
        textcolor(11);
    else if (strcmp(cor, "vermelho_claro") == 0)
        textcolor(12);
    else if (strcmp(cor, "rosa_claro") == 0)
        textcolor(13);
    else if (strcmp(cor, "amarelo") == 0)
        textcolor(14);
    else if (strcmp(cor, "branco") == 0)
        textcolor(15);
    else
        textcolor(15);

    limpandoArea(consolePos);

    if (strcmp(consolePos, "topo") == 0)
    {
        int mid = (strlen(str) / 2);
        gotoxy(40 - mid, 3);
    }
    else if (strcmp(consolePos, "alerta") == 0)
        gotoxy(3, 23);
    else if (strcmp(consolePos, "esquerda") == 0)
        gotoxy(4, 9);
    else if (strcmp(consolePos, "direita") == 0)
        gotoxy(30, 7);
    else if (strcmp(consolePos, "subMenu") == 0)
//        gotoxy(3, 33);
        gotoxy(4, 23);

    gotoxy(wherex(), wherey() + _i);

    for (transc = str; *transc != '\0';)
    {
        while (*transc != '%' && *transc != '\0')
        {
            putchar(*transc);
            transc++;
        }
        if (*transc == '%')
            transc++;
        switch (*transc)
        {
        case 'd':
            i = va_arg(arg, int);
            if (i < 0)
            {
                i = -1;
                putchar('-');
            }
            fputs(conv(i, 10), stdout);
            transc++;
            break;
        case 's':
            s = va_arg(arg, char *);
            fputs(s, stdout);
            transc++;
            break;
        case 'f':
            i = va_arg(arg, double);
            if (i < 0)
            {
                i = -1;
                putchar('-');
            }
            fputs(conv(i, 10), stdout);
            transc++;
            break;
        }
    }
    textcolor(15);
    va_end(arg);
}

void Moldura(int CI, int LI, int CF, int LF, int CorT, int CorF)
{
    int i;
    textcolor(CorT);
    textbackground(CorF);
    gotoxy(CI, LI);
    printf("%c", 201);
    gotoxy(CI, LF);
    printf("%c", 200);
    gotoxy(CF, LI);
    printf("%c", 187);
    gotoxy(CF, LF);
    printf("%c", 188);
    for (i = CI + 1; i < CF; i++)
    {
        gotoxy(i, LI);
        printf("%c", 205);
        gotoxy(i, LF);
        printf("%c", 205);
    }
    for (i = LI + 1; i < LF; i++)
    {
        gotoxy(CI, i);
        printf("%c", 186);
        gotoxy(CF, i);
        printf("%c", 186);
    }

    textcolor(7);
    textbackground(0);
}

void application(void)
{
    Moldura(1, 1, 80, 25, 14, 0); //borda_fora
    Moldura(2, 2, 79, 4, 15, 5); //titulo_menu
    Moldura(2, 5, 27, 21, 15, 3); //esquerda_menu
    Moldura(2, 22, 79, 24, 15, 1); //esquerda_submenu_alert
    Moldura(28, 5, 79, 21, 15, 11); //direita
}

