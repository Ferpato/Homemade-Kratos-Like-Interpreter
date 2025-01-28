#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QCoreApplication>
#include <iostream>
#include <string.h>
#include <fstream>
#include <stack>
#include <list>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <algorithm>

static std::stack<int> pila;

static std::stack<QString> pilaTipo;
static std::stack<int> pilaOP;

static std::stack<QString> pilaCuadruplosOpe;
static std::stack<int> pilaCuadruplosSignos;
static std::stack<int> pilaCuadruplosSaltos;
int fila=0;



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);

}
std::string filename2;
MainWindow::~MainWindow()
{
    delete ui;
}
static int M[20][33] = {{1,	2,	3,	506,	506,	107,	108,	105,	106,	128,	15,	17,	19,	124,	123,	121,	122,	119,	120,	13,	12,	11,	10,	9,	14,	129,	130,	2,	1,	0,	0,	0,	506},
                        {1,	2,	2,	100,	2,	100,	100,	100,	100,	100,	100,	100,	100,	100,	100,	100,	100,	100,	100,	100,	100,	100,	100,	100,	100,	100,	100,	2,	1,	100,	100,	100,	100},
                        {2,	2,	2,	101,	2,	101,	101,	101,	101,	101,	101,	101,	101,	101,	101,	101,	101,	101,	101,	101,	101,	101,	101,	101,	101,	101,	101,	2,	2,	101,	101,	101,	101},
                        {102,	102,	3,	4,	102,	102,	102,	102,	102,	102,	102,	102,	102,	102,	102,	102,	102,	102,	102,	102,	102,	102,	102,	102,	102,	102,	102,	6,	6,	102,	102,	102,	102},
                        {500,	500,	5,	500,	500,	500,	500,	500,	500,	500,	500,	500,	500,	500,	500,	500,	500,	500,	500,	500,	500,	500,	500,	500,	500,	500,	500,	500,	500,	500,	500,	500,	500},
                        {103,	103,	5,	103,	103,	103,	103,	103,	103,	103,	103,	103,	103,	103,	103,	103,	103,	103,	103,	103,	103,	103,	103,	103,	103,	103,	103,	6,	6,	103,	103,	103,	103},
                        {501,	501,	8,	501,	501,	501,	501,	7,	7,	501,	501,	501,	501,	501,	501,	501,	501,	501,	501,	501,	501,	501,	501,	501,	501,	501,	501,	501,	501,	501,	501,	501,	501},
                        {502,	502,	8,	502,	502,	502,	502,	502,	502,	502,	502,	502,	502,	502,	502,	502,	502,	502,	502,	502,	502,	502,	502,	502,	502,	502,	502,	502,	502,	502,	502,	502,	502},
                        {104,	104,	8,	104,	104,	104,	104,	104,	104,	104,	104,	104,	104,	104,	104,	104,	104,	104,	104,	104,	104,	104,	104,	104,	104,	104,	104,	104,	104,	104,	104,	104,	104},
                        {109,	109,	109,	109,	109,	109,	109,	109,	109,	109,	109,	109,	109,	109,	109,	109,	109,	109,	109,	109,	109,	109,	109,	110,	109,	109,	109,	109,	109,	109,	109,	109,	109},
                        {111,	111,	111,	111,	111,	111,	111,	111,	111,	111,	111,	111,	111,	111,	111,	111,	111,	111,	111,	111,	111,	111,	111,	112,	111,	111,	111,	111,	111,	111,	111,	111,	111},
                        {113,	113,	113,	113,	113,	113,	113,	113,	113,	113,	113,	113,	113,	113,	113,	113,	113,	113,	113,	113,	113,	113,	113,	114,	113,	113,	113,	113,	113,	113,	113,	113,	113},
                        {116,	116,	116,	116,	116,	116,	116,	116,	116,	116,	116,	116,	116,	116,	116,	116,	116,	116,	116,	116,	116,	116,	116,	115,	116,	116,	116,	116,	116,	116,	116,	116,	116},
                        {503,	503,	503,	503,	503,	503,	503,	503,	503,	503,	503,	503,	503,	503,	503,	503,	503,	503,	503,	117,	503,	503,	503,	503,	503,	503,	503,	503,	503,	503,	503,	503,	503},
                        {504,	504,	504,	504,	504,	504,	504,	504,	504,	504,	504,	504,	504,	504,	504,	504,	504,	504,	504,	504,	504,	504,	504,	504,	118,	504,	504,	504,	504,	504,	504,	504,	504},
                        {16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	505,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16},
                        {507,	507,	507,	507,	507,	507,	507,	507,	507,	507,	125,	507,	507,	507,	507,	507,	507,	507,	507,	507,	507,	507,	507,	507,	507,	507,	507,	507,	507,	507,	507,	507,	507},
                        {17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	18,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17},
                        {126,	126,	126,	126,	126,	126,	126,	126,	126,	126,	126,	17,	126,	126,	126,	126,	126,	126,	126,	126,	126,	126,	126,	126,	126,	126,	126,	126,	126,	126,	126,	126,	126},
                        {19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	127,	19,	19}};

static QString TE[6][4] ={{"E","E","B","X"},
                          {"R","R","B","X"},
                          {"X","X","B","X"},
                          {"X","X","B","X"},
                          {"X","X","B","X"},
                          {"N","N","B","X"},};

static QString TR[6][4] ={{"R","R","B","X"},
                          {"R","R","B","X"},
                          {"X","X","B","X"},
                          {"X","X","B","X"},
                          {"X","X","B","X"},
                          {"N","N","B","X"},};

static QString TB[6][4] ={{"X","X","B","X"},
                          {"X","X","B","X"},
                          {"X","X","B","B"},
                          {"X","X","B","X"},
                          {"X","X","B","X"},
                          {"X","X","B","X"},};

static QString TC[6][4] ={{"X","X","B","X"},
                          {"X","X","B","X"},
                          {"X","X","B","X"},
                          {"X","X","B","X"},
                          {"X","X","B","X"},
                          {"X","X","B","X"},};

static QString TS[6][4] ={{"X","X","B","X"},
                          {"X","X","B","X"},
                          {"X","X","B","X"},
                          {"X","X","B","X"},
                          {"X","X","B","X"},
                          {"X","X","B","X"},};


static QString TN[6][4] ={{"N","N","B","X"},
                          {"N","N","B","X"},
                          {"X","X","B","X"},
                          {"X","X","B","X"},
                          {"X","X","B","X"},
                          {"N","N","B","X"},};
static QString operpila="";
static QString openpila="";
static QString Error= "";
static QString token="";
static QString cadenas="";
static QString contenidoMostrado="";
static QString Codigo2="";

static QString CuadruploSignos="";
static QString CuadruploOper="";
static QString CuadruploSaltos="";
static QString RellenarS= "";



static QString UltimoId="";

int Resultados=1;
std::list<std::string> Op1C;
std::list<std::string>::iterator Op1CI;
std::list<std::string> Op2C;
std::list<std::string>::iterator Op2CI;
std::list<std::string> ResultadoC;
std::list<std::string>::iterator ResultadoCI;
std::list<std::string> OperadorC;
std::list<std::string>::iterator OperadorCI;
static QString Ultimocar="";
int poscuadruplo=1;

std::list<std::string> NombreV;
std::list<std::string>::iterator Iterador1;
std::list<std::string> TipoV;
std::list<std::string>::iterator Iterador2;
int contadorV=0;
int contadorV2=0;
QString tipopila="";

void MainWindow::setTextErrores(QString p)
{
    MainWindow::ui->errores->setText(p);
}
bool Definicion=false;

static int Tamano=10;
bool si=false;
static int TokenN;
   QString cadenasTMP ="";
QString Palabras[28] = {"lib","class","int","float","char","string","bool"
     ,"if","else","elseif","do","dowhile","enddo","endif","endwhile","while","input","output","def"
    ,"as","array","endclass","private","public","protected","main","end"};
void Token(int e){

    switch (e){
    case 100:
        si=false;
        for(int i=0;i<27;i++){
            if(cadenasTMP==Palabras[i]){
                si=true;
                switch(i){
                case 0:
                    TokenN=1031; //lib
                break;
                case 1:
                    TokenN=1032; //class
                    break;
                case 2:
                    TokenN=1033; //int
                    while(contadorV2<contadorV){
                    TipoV.push_back("E");
                        contadorV2++;
                    }
                    break;
                case 3:
                    TokenN=1034; //float o real
                    while(contadorV2<contadorV){
                        TipoV.push_back("R");
                        contadorV2++;
                    }
                    break;
                case 4:
                    TokenN=1035;//char
                    while(contadorV2<contadorV){
                        TipoV.push_back("C");
                        contadorV2++;
                    }
                    break;
                case 5:
                    TokenN=1036; //String
                    while(contadorV2<contadorV){
                        TipoV.push_back("S");
                        contadorV2++;
                    }
                    break;
                case 6:
                    TokenN=1037; //bool
                    while(contadorV2<contadorV){
                        TipoV.push_back("B");
                        contadorV2++;
                    }
                    break;
                case 7:
                    TokenN=1038; //if
                    break;
                case 8:
                    TokenN=1039; // else
                    break;
                case 9:
                    TokenN=1040; //elseif
                    break;
                case 10:
                    TokenN=1041; //do
                    break;
                case 11:
                    TokenN=1042; //dowhile
                    break;
                case 12:
                    TokenN=1043;//endo
                    break;
                case 13:
                    TokenN=1044;//endif
                    break;
                case 14:
                    TokenN=1045;//endwhile
                    break;
                case 15:
                    TokenN=1046; //while
                    break;
                case 16:
                    TokenN=1047;//input
                    break;
                case 17:
                    TokenN=1048; //output
                    break;
                case 18:
                    TokenN=1049; //def
                    Definicion=true;
                    break;
                case 19:
                    TokenN=1050; //as
                    break;
                case 20:
                    TokenN=1051; //array
                    break;
                case 21:
                    TokenN=1052; //endclass
                    break;
                case 22:
                    TokenN=1053; //rpivate
                    break;
                case 23:
                    TokenN=1054; //public
                    break;
                case 24:
                    TokenN=1055; //protected
                    break;
                case 25:
                    Definicion=false;
                    TokenN=1056; //main
                    break;
                case 26:
                    TokenN=1057; //end
                    break;
                }
            }
        }
        if(si){
            token=token+cadenas+" Palabras reservadas\n";
            break;
        }
        else{
            token=token+cadenas+" Identificador\n";
            // std::cout<<cadenas.toStdString()<<std::endl;
            UltimoId=cadenas;
            Ultimocar=cadenas;
            tipopila="Id";
            if(Definicion){
                bool valido=true;
                Iterador1=NombreV.begin();
                while(Iterador1!=NombreV.end()){
                    if(cadenas.toStdString()==*Iterador1){
                            Error=Error+"80000 VARIABLE "+cadenas+" REPETIDA \n";
                        valido=false;
                    }
                    Iterador1++;
                }

                if(valido){
                NombreV.push_back(cadenas.toStdString());
                  contadorV++;
                }
            }
             TokenN=1001;
            break;
        }



        token=token+cadenas+" Palabras reservadas\n";
        break;
    case 101:
        token=token+cadenas+" Identificador\n";
        // std::cout<<cadenas.toStdString()<<std::endl;
          UltimoId=cadenas;
         Ultimocar=cadenas;
        tipopila="Id";
        if(Definicion){
            bool valido=true;
            Iterador1=NombreV.begin();
            while(Iterador1!=NombreV.end()){
                if(cadenas.toStdString()==*Iterador1){
                    Error=Error+"80000 VARIABLE "+cadenas+" REPETIDA \n";
                    valido=false;
                }
                Iterador1++;
            }

            if(valido){
                NombreV.push_back(cadenas.toStdString());
                contadorV++;
            }
        }
        TokenN=1001;
        break;
    case 102:
        token=token+cadenas+" Enteros\n";
        UltimoId=cadenas;
         Ultimocar=cadenas;
        tipopila="E";
        TokenN=1002;
        break;
    case 103:
        token=token+cadenas+" Reales\n";
          tipopila="R";
          UltimoId=cadenas;
           Ultimocar=cadenas;
        TokenN=1003;
        break;
    case 104:
        token=token+cadenas+" Constante notacion cientifica\n";
          tipopila="N";
        UltimoId=cadenas;
           Ultimocar=cadenas;
        TokenN=1004;
        break;
    case 105:
        token=token+cadenas+" Suma\n";
        TokenN=1005;
        break;
    case 106:
        token=token+cadenas+" Resta\n";
        TokenN=1006;
        break;
    case 107:
        token=token+cadenas+" Multiplicacion\n";
        TokenN=1007;
        break;
    case 108:
        token=token+cadenas+" division\n";
        TokenN=1008;
        break;
    case 109:
        token=token+cadenas+" Asigna\n";
        TokenN=1009;
        break;
    case 110:
        token=token+cadenas+" Igual\n";
        TokenN=1010;
        break;
    case 111:
        token=token+cadenas+" Menor\n";
        TokenN=1011;
        break;
    case 112:
        token=token+cadenas+" Menor Igual\n";
        TokenN=1012;
        break;
    case 113:
        token=token+cadenas+" Mayor\n";
        TokenN=1013;
        break;
    case 114:
        token=token+cadenas+" Mayor igual \n";
        TokenN=1014;
        break;
    case 115:
        token=token+cadenas+" Diferente \n";
        TokenN=1015;
        break;
    case 116:
        token=token+cadenas+" not\n";
        TokenN=1016;
        break;
    case 117:
        token=token+cadenas+" And \n";
        TokenN=1017;
        break;
    case 118:
        token=token+cadenas+" Or\n";
        TokenN=1018;
        break;
    case 119:
        token=token+cadenas+" Parentesis que abre\n";
        TokenN=1019;
        break;
    case 120:
        token=token+cadenas+" Parentesis que cierra\n";
        TokenN=1020;
        break;
    case 121:
        token=token+cadenas+" Corchete que abre\n";
        TokenN=1021;
        break;
    case 122:
        token=token+cadenas+" Corchete que cierra\n";
        TokenN=1022;
        break;
    case 123:
        token=token+cadenas+" Punto y coma\n";
        TokenN=1023;
        break;
    case 124:
        token=token+cadenas+" Coma\n";
        TokenN=1024;
        break;
    case 125:
        token=token+cadenas+" Cte caracter\n";
        tipopila="C";
        UltimoId=cadenas;
        TokenN=1025;
        break;
    case 126:
        token=token+cadenas+" Cte String\n";
        tipopila="S";
        UltimoId=cadenas;
        TokenN=1026;
        break;
    case 127:
        token=token+cadenas+" Comentario de linea\n";
        TokenN=1027;
        break;
    case 128:
        token=token+cadenas+" modulus \n";
        TokenN=1028;
        break;
    case 129:
        token=token+cadenas+" Llave que abre\n";
        TokenN=1029;
        break;
    case 130:
        token=token+cadenas+" Llave que cierra\n";
        TokenN=1030;
        break;
    }
    cadenas="";
}

static void error(int e){


    switch(e){
     case 500:
 Error=Error+" 500: Ese elemento no es reconocido por el lenguaje \n";
         TokenN=500;
        break;
     case 501:
 Error=Error+"501: Valor flotante espera digitos \n";
         TokenN=501;
        break;
     case 502:
        Error=Error+"502: Para la not. Cient. Esperaba digito, + o - \n";
         TokenN=502;
        break;
     case 503:
    Error=Error+"503: Para la not. Cient. Esperaba digito \n";
         TokenN=503;
        break;
     case 504:
         Error=Error+"504: Se esperaba otro caracter de | \n";
         TokenN=504;
         break;
     case 505:
         Error=Error+"505: El caracter debe tener contenido \n";
         TokenN=505;
         break;
     case 506:
         Error=Error+"506: No se reconoce ese caracter \n";
         TokenN=506;
         break;
     case 507:
         Error=Error+"507: Char solo puede tener un caracter \n";
         TokenN=507;
         break;
     case 508:
         Error=Error+"508 No cerro la comilla de comentario antes de que terminara el archivo \n";
         TokenN=508;
         break;
    }

}
int relaciona(char c){
    if(c>='a' && c<='d'){
        return 0;
    }
    if(c>='f' && c<='z'){
        return 0;
    }
    else{
        if(c>='A' && c<='D' || (c>='F' && c<='Z') ){
        return 1;
    }
    else{
        if(c>='0' && c<='9'){
            return 2;
    }
    }
    }
    switch (c){
    case '.': return 3;
    case '_': return 4;
    case '*': return 5;
    case '/': return 6;
    case '+': return 7;
    case '-':return 8;
    case '%':return 9;
    case 39 :return 10; //Apostrof2 '
    case '"' :return 11; // "
    case '#':return 12;
    case ',':return 13;
    case ';':return 14;
    case '[':return 15;
    case ']':return 16;
    case '(':return 17;
    case ')':return 18;
    case '&':return 19;
    case '!':return 20;
    case '>':return 21;
    case '<':return 22;
    case '=':return 23;
    case '|':return 24;
    case '{':return 25;
    case '}':return 26;
    case 'E':return 27;
    case 'e':return 28;
    case '\t':return 29;
    case '\n':return 30;
    case ' ':return 31;

    }
   // cadenas.chop(1);

    return 32;

}

char* leer(){
    std::ifstream archivo(filename2);

    // Verifica si el archivo se abrió correctamente
    if (!archivo) {
        std::cout << "No se pudo abrir el archivo." << std::endl;
        return "";

    }

    // Obtiene la longitud del archivo
    archivo.seekg(0, std::ios::end);
    int longitud = archivo.tellg();
    archivo.seekg(0, std::ios::beg);

    // Crea un buffer para almacenar el contenido del archivo
    char *contenido = new char[longitud+1]; // +1 para el carácter nulo al final
    contenido[longitud] = '\0'; // Asegura que el buffer finalice con un carácter nulo

    // Lee el contenido del archivo y lo almacena en el buffer
    archivo.read(contenido, longitud);

    // Cierra el archivo
    archivo.close();

    // Imprime el contenido del archivo

    //std::cout << contenido << std::endl;
    return contenido;
}
 int cont;
int col;
// Error="";
 //token="";
 //cadenas ="";

int Analiza(){
    static char *cadena;
    QByteArray ba = Codigo2.toLatin1 ();

cadena =ba.data ();



    int edo=0;
    //col=0;
    char car=' ';
  // cont=0;

    //cont=0;



    Tamano=strlen(cadena);
    if(cont>=strlen(cadena)){
        return 1058;

    }
    while(cont<=strlen(cadena)){
        edo=0;

        while(edo<=19){
            car=cadena[cont];

            col=relaciona(car);
            edo=M[edo][col];
            if(edo==1){
                cadenasTMP=cadenasTMP+car;
            }

            //std::cout<<cadenasTMP.toStdString() <<std::endl;


            if(edo<=19 && car!=EOF){
                cont++;

                    if(car=='\t' || car=='\n' || car==' '){
                      if(edo==15 || edo==17){
                         cadenas=cadenas+car;
                        }
                    }
                    else{
                       cadenas=cadenas+car;
                    }


            }
        }
        if(edo==100 || edo==101 || edo==102 || edo==103 || edo==104 || edo==109 || edo==111 || edo==113 || edo==116 || edo==126 ){
            cont--;
        }
        else{
            cadenas=cadenas+car;
        }
        if(edo>=100 && edo<=130){

            Token(edo);
             cadenasTMP="";

        }
        else{
            if(car=='\0'){

            }else{
            Error=Error+car;
            error(edo);
            cadenas="";
            }
        }
        if(edo==508){
            error(edo);
        }

        cont++;

            return TokenN;


    }

}


static int MP[38][58] = {{600,	600,	600,	600,	600,	600,	600,	600,	600,	600,	600,	600,	600,	600,	600,	600,	600,	600,	600,	600,	600,	600,	600,	600,	600,	600,	600,	600,	600,	600,	0,	0,	600,	600,	600,	600,	600,	600,	600,	600,	600,	600,	600,	600,	600,	600,	600,	600,	600,	600,	600,	600,	600,	600,	600,	600,	600,	700},
                         {601,	601,	601,	601,	601,	601,	601,	601,	601,	601,	601,	601,	601,	601,	601,	601,	601,	601,	601,	601,	601,	601,	601,	601,	601,	601,	601,	601,	601,	601,	1,	2,	601,	601,	601,	601,	601,	601,	601,	601,	601,	601,	601,	601,	601,	601,	601,	601,	601,	601,	601,	601,	601,	601,	601,	601,	601,	700},
                         {602,	602,	602,	602,	602,	602,	602,	602,	602,	602,	602,	602,	602,	602,	602,	602,	602,	602,	602,	602,	602,	602,	602,	602,	602,	602,	602,	602,	602,	602,	602,	602,	602,	602,	602,	602,	602,	602,	602,	602,	602,	602,	602,	602,	602,	602,	602,	602,	3,	602,	602,	602,	602,	602,	602,	4,	602,	700},
                         {604,	604,	604,	604,	604,	604,	604,	604,	604,	604,	604,	604,	604,	604,	604,	604,	604,	604,	604,	604,	604,	604,	604,	604,	604,	604,	604,	604,	604,	604,	604,	604,	603,	603,	603,	603,	603,	604,	604,	604,	604,	604,	604,	604,	604,	604,	604,	604,	604,	604,	604,	604,	6,	5,	7,	604,	604,	700},
                         {605,	605,	605,	605,	605,	605,	605,	605,	605,	605,	605,	605,	605,	605,	605,	605,	605,	605,	605,	9,	605,	605,	605,	8,	605,	605,	605,	605,	605,	605,	605,	605,	605,	605,	605,	605,	605,	605,	605,	605,	605,	605,	605,	605,	605,	605,	605,	605,	605,	9,	605,	605,	605,	605,	605,	605,	605,	700},
                         {606,	606,	606,	606,	606,	606,	606,	606,	606,	606,	606,	606,	606,	606,	606,	606,	606,	606,	606,	606,	606,	606,	606,	606,	606,	606,	606,	606,	606,	606,	606,	606,	11,	11,	11,	11,	11,	606,	606,	606,	606,	606,	606,	606,	606,	606,	606,	606,	606,	606,	10,	606,	606,	606,	606,	606,	606,	700},
                         {607,	608,	608,	608,	607,	607,	607,	607,	607,	607,	607,	607,	607,	607,	607,	607,	607,	607,	607,	607,	12,	607,	607,	607,	607,	607,	607,	607,	607,	607,	607,	607,	607,	607,	607,	607,	607,	607,	607,	607,	607,	607,	607,	607,	607,	607,	607,	607,	607,	607,	607,	607,	607,	607,	607,	607,	607,	700},
                         {609,	609,	609,	609,	609,	609,	609,	609,	609,	609,	609,	609,	609,	609,	609,	609,	609,	609,	609,	609,	609,	14,	609,	13,	609,	609,	609,	609,	609,	609,	609,	609,	609,	609,	609,	609,	609,	609,	609,	609,	609,	609,	609,	609,	609,	609,	609,	609,	609,	609,	609,	609,	609,	609,	609,	609,	609,	700},
                         {610,	610,	610,	610,	610,	610,	610,	610,	610,	610,	610,	610,	610,	610,	610,	610,	610,	610,	610,	610,	610,	610,	610,	610,	610,	610,	610,	610,	610,	610,	610,	610,	15,	16,	17,	19,	18,	610,	610,	610,	610,	610,	610,	610,	610,	610,	610,	610,	610,	610,	610,	611,	611,	611,	610,	610,	610,	700},
                         {612,	612,	612,	612,	612,	612,	612,	612,	612,	612,	612,	612,	612,	612,	612,	612,	612,	612,	612,	612,	612,	612,	612,	612,	612,	612,	612,	612,	612,	612,	612,	612,	612,	612,	612,	612,	612,	612,	612,	612,	612,	612,	612,	612,	612,	612,	612,	612,	612,	612,	612,	612,	612,	612,	612,	20,	612,	700},
                         {21,	613,	613,	613,	613,	613,	613,	613,	613,	613,	613,	613,	613,	613,	613,	613,	613,	613,	613,	613,	613,	613,	613,	613,	613,	613,	613,	613,	613,	613,	613,	613,	613,	613,	613,	613,	613,	24,	27,	27,	26,	27,	613,	27,	27,	25,	22,	23,	613,	613,	613,	613,	613,	613,	613,	613,	27,	700},
                         {28,	614,	614,	614,	614,	614,	614,	614,	614,	614,	614,	614,	614,	614,	614,	614,	614,	614,	614,	614,	614,	614,	614,	614,	614,	614,	614,	614,	614,	614,	614,	614,	614,	614,	614,	614,	614,	28,	29,	29,	28,	29,	614,	29,	29,	28,	28,	28,	614,	614,	614,	614,	614,	614,	614,	614,	29,	700},
                         {30,	615,	615,	615,	615,	615,	615,	615,	615,	615,	615,	615,	615,	615,	615,	615,	615,	615,	615,	615,	615,	615,	615,	615,	615,	615,	615,	615,	615,	615,	615,	615,	615,	615,	615,	615,	615,	615,	615,	615,	615,	615,	615,	615,	615,	615,	615,	615,	615,	615,	615,	615,	615,	615,	615,	615,	615,	700},
                         {31,	616,	616,	616,	616,	616,	616,	616,	617,	617,	616,	616,	616,	616,	616,	616,	616,	616,	616,	616,	616,	616,	616,	616,	616,	616,	616,	616,	616,	616,	616,	616,	616,	616,	616,	616,	616,	616,	616,	616,	616,	616,	616,	616,	616,	616,	616,	616,	616,	616,	616,	616,	616,	616,	616,	616,	616,	700},
                         {618,	618,	618,	618,	33,	33,	33,	33,	33,	33,	33,	33,	33,	33,	33,	618,	33,	33,	618,	33,	32,	33,	33,	33,	618,	618,	618,	618,	618,	618,	618,	618,	618,	618,	618,	618,	618,	618,	618,	618,	618,	618,	618,	618,	618,	618,	618,	618,	618,	618,	618,	618,	618,	618,	618,	618,	618,	700},
                         {619,	619,	619,	619,	619,	619,	619,	619,	619,	619,	619,	619,	619,	619,	619,	619,	619,	619,	619,	35,	619,	35,	620,	34,	619,	619,	619,	619,	619,	620,	619,	619,	619,	619,	619,	619,	619,	619,	619,	619,	619,	619,	620,	620,	620,	619,	619,	619,	619,	619,	619,	620,	619,	619,	619,	619,	620,	700},
                         {36,	36,	36,	36,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	36,	621,	621,	36,	621,	621,	621,	621,	621,	36,	36,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	700},
                         {623,	623,	623,	623,	623,	623,	623,	623,	623,	623,	623,	623,	623,	623,	623,	623,	623,	37,	623,	38,	623,	38,	38,	38,	623,	623,	623,	623,	623,	623,	623,	623,	623,	623,	623,	623,	623,	623,	623,	623,	623,	623,	622,	622,	622,	623,	623,	623,	623,	623,	623,	623,	623,	623,	623,	623,	622,	700},
                         {39,	39,	39,	39,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	39,	621,	621,	39,	621,	621,	621,	621,	621,	39,	39,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	700},
                         {624,	624,	624,	624,	624,	624,	624,	624,	624,	624,	624,	624,	624,	624,	624,	624,	40,	41,	624,	41,	624,	41,	41,	41,	624,	624,	624,	624,	624,	624,	624,	624,	624,	624,	624,	624,	624,	624,	624,	624,	624,	624,	624,	624,	624,	624,	624,	624,	624,	624,	624,	624,	624,	624,	624,	624,	624,	700},
                         {43,	43,	43,	43,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	43,	621,	621,	43,	621,	621,	621,	621,	621,	43,	43,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	621,	700},
                         {44,	44,	44,	44,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	44,	625,	625,	625,	625,	625,	44,	44,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	700},
                         {626,	626,	626,	626,	626,	626,	626,	626,	626,	45,	45,	45,	45,	45,	45,	626,	46,	46,	626,	46,	626,	46,	46,	46,	626,	626,	626,	626,	626,	626,	626,	626,	626,	626,	626,	626,	626,	626,	626,	626,	626,	626,	622,	622,	622,	626,	626,	626,	626,	626,	626,	626,	626,	626,	626,	626,	622,	700},
                         {47,	47,	47,	47,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	47,	625,	625,	625,	625,	625,	47,	47,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	625,	700},
                         {627,	627,	627,	627,	48,	49,	627,	627,	627,	50,	50,	50,	50,	50,	50,	627,	50,	50,	627,	50,	627,	50,	50,	50,	627,	627,	627,	627,	627,	627,	627,	627,	627,	627,	627,	627,	627,	627,	627,	627,	627,	627,	627,	627,	627,	627,	627,	627,	627,	627,	627,	627,	627,	627,	627,	627,	627,	700},
                         {629,	629,	629,	629,	629,	629,	629,	629,	628,	51,	53,	54,	55,	56,	52,	629,	629,	629,	629,	629,	629,	629,	629,	629,	629,	629,	629,	629,	629,	629,	629,	629,	629,	629,	629,	629,	629,	629,	629,	629,	629,	629,	629,	629,	629,	629,	629,	629,	629,	629,	629,	629,	629,	629,	629,	629,	629,	700},
                         {57,	57,	57,	57,	630,	630,	630,	630,	630,	630,	630,	630,	630,	630,	630,	630,	630,	630,	57,	630,	630,	631,	631,	630,	57,	57,	630,	630,	630,	630,	630,	630,	630,	630,	630,	630,	630,	630,	630,	630,	630,	630,	631,	631,	631,	630,	630,	630,	630,	630,	630,	630,	630,	630,	630,	630,	631,	700},
                         {632,	632,	632,	632,	61,	61,	58,	59,	632,	61,	61,	61,	61,	61,	61,	632,	61,	61,	632,	61,	632,	61,	61,	61,	632,	632,	632,	60,	632,	632,	632,	632,	632,	632,	632,	632,	632,	632,	632,	632,	632,	632,	632,	632,	632,	632,	632,	632,	632,	632,	632,	632,	632,	632,	632,	632,	632,	700},
                         {68,	62,	63,	64,	633,	633,	633,	633,	633,	633,	633,	633,	633,	633,	633,	633,	633,	633,	67,	633,	633,	633,	633,	633,	65,	66,	633,	633,	633,	633,	633,	633,	633,	633,	633,	633,	633,	633,	633,	633,	633,	633,	633,	633,	633,	633,	633,	633,	633,	633,	633,	633,	633,	633,	633,	633,	633,	700},
                         {634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	69,	634,	634,	634,	634,	634,	634,	634,	634,	634,	700},
                         {634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	70,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	700},
                         {634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	71,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	634,	700},
                         {73,	635,	635,	635,	635,	635,	635,	635,	635,	635,	635,	635,	635,	635,	635,	635,	635,	635,	635,	635,	635,	635,	635,	635,	635,	635,	635,	635,	635,	635,	635,	635,	635,	635,	635,	635,	635,	73,	73,	72,	73,	73,	635,	73,	73,	73,	73,	73,	635,	635,	635,	635,	635,	635,	635,	635,	73,	700},
                         {636,	636,	636,	636,	636,	636,	636,	636,	636,	636,	636,	636,	636,	636,	636,	636,	636,	636,	636,	636,	636,	636,	636,	636,	636,	636,	636,	636,	636,	636,	636,	636,	636,	636,	636,	636,	636,	636,	74,	636,	636,	636,	636,	75,	636,	636,	636,	636,	636,	636,	636,	636,	636,	636,	636,	636,	636,	700},
                         {637,	637,	637,	637,	637,	637,	637,	637,	637,	637,	637,	637,	637,	637,	637,	637,	637,	637,	637,	637,	637,	637,	637,	637,	637,	637,	637,	637,	637,	637,	637,	637,	637,	637,	637,	637,	637,	637,	637,	637,	637,	637,	637,	637,	637,	76,	637,	637,	637,	637,	637,	637,	637,	637,	637,	637,	637,	700},
                         {638,	638,	638,	638,	638,	638,	638,	638,	638,	638,	638,	638,	638,	638,	638,	638,	638,	638,	638,	638,	638,	638,	638,	638,	638,	638,	638,	638,	638,	638,	638,	638,	638,	638,	638,	638,	638,	638,	638,	638,	77,	638,	638,	638,	638,	638,	638,	638,	638,	638,	638,	638,	638,	638,	638,	638,	638,	700},
                         {639,	639,	639,	639,	639,	639,	639,	639,	639,	639,	639,	639,	639,	639,	639,	639,	639,	639,	639,	79,	639,	639,	639,	78,	639,	639,	639,	639,	639,	639,	639,	639,	639,	639,	639,	639,	639,	639,	639,	639,	639,	639,	639,	639,	639,	639,	639,	639,	639,	639,	639,	639,	639,	639,	639,	639,	639,	700},
                         {640,	640,	640,	640,	640,	640,	640,	640,	640,	640,	640,	640,	640,	640,	640,	640,	640,	640,	640,	81,	640,	640,	640,	80,	640,	640,	640,	640,	640,	640,	640,	640,	640,	640,	640,	640,	640,	640,	640,	640,	640,	640,	640,	640,	640,	640,	640,	640,	640,	640,	640,	640,	640,	640,	640,	640,	640,	700}


};

char* erroresP(int n){
    switch(n){
     case 600:
        return "ERROR 600  El programa debe iniciar definiendo clase o una librería.";
    break;
     case 601:
         return "ERROR 601 Despues de definir la librería debe definir otra o definir una clase.";
         break;
     case 602:
         return "ERROR 602 El programa no continuo con el metodo main o una definicion de variables";
         break;
     case 603:
         return "'ERROR 603  Al declarar el tipo de una variable no puede usar el mismo que el de un dato (int,float,char, etc.) .";
         break;
     case 604:
         return "ERROR 604  La declaracion debe venir seguida de un tipo (public, private, protected)";
         break;
     case 605:
         return "ERROR 605 Se eseperaba la definicion de un identificador";
         break;
     case 606:
         return "ERROR 606  Se esperaba un tipo de dato (int, float, char, etc. ) o la definicion de un array.";
         break;
     case 607:
         return "ERROR 607 Al usar un array debe venir seguido de [ para defiinir las dimensiones";
         break;
     case 608:
         return "ERROR 608 Debe inidicar el tamaño del array entre los corchetes.";
         break;
     case 609:
         return "ERROR 609  Se esperaba el cierre de la dimension del array con ].";
         break;
     case 610:
         return "ERROR 610 Al declarar una variable debe venir con el tipo de esta (int, bool, char, etc.)";
         break;
     case 611:
         return "ERROR 611 El tipo de  dato de la variable no puede ser de tipo de declaracion (public, private, protected)";
         break;
     case 612:
         return "'ERROR 612  El programa debe continuar con la declaracion del metodo main.";
         break;
     case 613:
         return "ERROR 613  Se esperaba la declaración de un estatuto";
         break;
     case 614:
         return "ERROR 614 Se esperaba la terminacion del estatuto o la declaracion de otro.";
         break;
     case 615:
         return "ERROR 615  Para asignar un estatuto debe usarse un identificador.";
         break;
     case 616:
         return "ERROR 616  La asignacion estaba esperando un identificador.";
         break;
     case 617:
         return "ERROR 617  La asignacion debe tener un identificador antes de usar =";
         break;
     case 618:
         return "ERROR 618  La asignacion debe continuar con = o un [";
         break;
     case 619:
         return "ERROR 619 Debe cerrar el final de la dimension de la asignacion con []";
         break;
     case 620:
         return "ERROR 620  El final de la asignacion de la dimension solo puede indicarse con ) o ]  ";
         break;
     case 621:
         return "ERROR 621  Ina expresion debe empezar con ! Un identificador un parentesis.";
         break;
     case 622:
         return "ERROR 622 Una expresion debe terminar con ; ) o ]";
         break;
     case 623:
         return "ERROR 623  La expresion solo puede continuar con , con || o con su finalización.  ";
         break;
     case 624:
         return "ERROR 624  La expresion solo puede continuar con &&, con ||, con , o con su finalización.   ";
         break;
     case 625:
         return "ERROR 625 Una expresion debe empezar con un idenificador o un ( .";
         break;
     case 626:
         return "ERROR 626 Una expresion debe ir seguida de un operador relacionar o una finalizacion de la expresion.";
         break;
     case 627:
         return "ERROR 627  La expresion solo puede continuar con un operador lógico, con , o con su finalización.";
         break;
     case 628:
         return "ERROR 628  Deben venir dos operadores = para la evaluación ";
         break;
     case 629:
         return "ERROR 629  Se esperaba un operador relacional (<  > ==";
         break;
     case 630:
         return "ERROR 630  Se esperaba unacontsante, un identificador o   ";
         break;
     case 631:
         return "ERROR 631  La constante o identificador finalizan con ) dentro de un estatuto";
         break;
     case 632:
         return "ERROR 632  Se esperaba un operador, un cierre con ), con ] o una ,   ";
         break;
     case 633:
         return "ERROR 633  Se esperaba una Cconstante o un operador";
         break;
     case 634:
         return "ERROR 634 Se esperaba un estatuto";
         break;
     case 635:
         return "ERROR 635 Se esperaba un elseif o declaraion de un estatuto.  ";
         break;
     case 636:
         return "ERROR 636 El  if debe cerrar con endif o continuar con un else";
         break;
     case 637:
         return "'ERROR 637 Se esperaba la declaracon de while";
         break;
     case 638:
         return "ERROR 638 Se esperaba la declaracion de do.";
         break;
     case 700:
         return "ERROR 700 Se llego al final del archivo inesperadamente.";
         break;
     default:
         return "Algo salio mal en el analizador sintactico revise el cuadro de erroes";
         break;

}
}


int NextToken=0;
int x;
int NT;

//Conversion a producciones
void producciones(int n){

//POP EN LAS QUE NO SEAN VACIO
    switch(n){
    case 0:
         pila.pop();
        pila.push(1052);

        pila.push(9);

        pila.push(2);

        pila.push(1001);

        pila.push(1032);

        pila.push(1);

    break;
    case 1:
         pila.pop();
        pila.push(1);
        pila.push(1023);
        pila.push(1001);
        pila.push(1031);
        break;
    case 2:
        pila.pop();
        break;
    case 3:
         pila.pop();
        pila.push(2);
        pila.push(1023);
        pila.push(8);
        pila.push(5);
        pila.push(1050);
        pila.push(4);
        pila.push(1001);
        pila.push(3);
        pila.push(1049);
        break;
    case 4:
        pila.pop();
        break;
    case 5:
         pila.pop();
        pila.push(1054);
        break;
    case 6:
         pila.pop();
        pila.push(1053);
        break;
    case 7:
         pila.pop();
        pila.push(1055);
        break;
    case 8:
         pila.pop();
        pila.push(4);
        pila.push(1001);
        pila.push(1024);
        break;
    case 9:
        pila.pop();
        break;
    case 10:
         pila.pop();
        pila.push(6);
        pila.push(1051);
        break;
    case 11:
        pila.pop();
        break;
    case 12:
         pila.pop();
        pila.push(1022);
        pila.push(7);
        pila.push(1002);
        pila.push(1021);
        break;
    case 13:
         pila.pop();
        pila.push(7);
        pila.push(1002);
        pila.push(1024);
        break;
    case 14:
        pila.pop();
        break;
    case 15:
         pila.pop();
       pila.push(1033);
        break;
    case 16:
         pila.pop();
        pila.push(1034);
        break;
    case 17:
         pila.pop();
        pila.push(1035);
        break;
    case 18:
         pila.pop();
        pila.push(1037);
        break;
    case 19:
         pila.pop();
        pila.push(1036);
        break;
    case 20:
         pila.pop();
        pila.push(1057);
        pila.push(10);
        pila.push(1020);
        pila.push(1019);
        pila.push(1056);
        break;
    case 21:
         pila.pop();
        pila.push(11);
        pila.push(1023);
        pila.push(12);
        break;
    case 22:
         pila.pop();
        pila.push(11);
        pila.push(1023);
        pila.push(30);
        break;
    case 23:
         pila.pop();
        pila.push(11);
        pila.push(1023);
        pila.push(29);
        break;
    case 24:
         pila.pop();
        pila.push(11);
        pila.push(31);
        break;
    case 25:
         pila.pop();
        pila.push(11);
        pila.push(34);
        break;
    case 26:
         pila.pop();
        pila.push(11);
        pila.push(35);
        break;
    case 27:

        pila.pop();
        break;
    case 28:
         pila.pop();
        pila.push(10);
        break;
    case 29:
        pila.pop();

        break;
    case 30:
         pila.pop();
        pila.push(2104);
        pila.push(2009);
        pila.push(16);
      //  pila.push(2001);//Accion
        pila.push(1009);
        pila.push(2002); //Accion 2
         pila.push(2102); //Accion 102
        pila.push(13);
      //   pila.push(2101);//Accion 101
        pila.push(2001);//Accion 1
        break;
    case 31:
         pila.pop();
        pila.push(14);
        pila.push(1001);
        pila.push(2101);//Accion 101
        pila.push(2001);//Accion 1

        break;
    case 32:
         pila.pop();
        pila.push(1022);
        pila.push(15);
        pila.push(16);
        pila.push(1021);
        break;
    case 33:
        pila.pop();
        break;
    case 34:
         pila.pop();
        pila.push(15);
        pila.push(16);
        pila.push(1024);
        break;
    case 35:
        pila.pop();
        break;
    case 36:
         pila.pop();
        pila.push(17);
        pila.push(18);
        break;
    case 37:
         pila.pop();
        pila.push(16);
        pila.push(1018);
         pila.push(2006);//ACCION 6
         pila.push(2102); //Accion 102
          pila.push(2103); //Accion 103
         pila.push(2004); //ACCION 4
        break;
    case 38:
        pila.pop();
         pila.push(2004); //ACCION 4
         pila.push(2103); //Accion 103
        break;
    case 39:
         pila.pop();
        pila.push(19);
        pila.push(20);
        break;
    case 40:
         pila.pop();
        pila.push(18);
        pila.push(1017);
        pila.push(2005); //Accion 5
         pila.push(2102); //Accion 102
         pila.push(2103); //Accion 103
        pila.push(2003); //Accion 3
        break;
    case 41:
        pila.pop();
         pila.push(2103); //Accion 103
        pila.push(2003);
        break;
    case 42:
         pila.pop();
        pila.push(21);
        pila.push(1016);
        break;
    case 43:
         pila.pop();
        pila.push(21);
        break;
    case 44:
         pila.pop();
        pila.push(22);
        pila.push(23);
        break;
    case 45:
         pila.pop();
        pila.push(23);
        pila.push(25);
        break;
    case 46:
        pila.pop();
        break;
    case 47:
         pila.pop();
        pila.push(24);
        pila.push(26);
        break;
    case 48:
        pila.pop();
        pila.push(23);
        pila.push(1005);
         pila.push(2006);//ACCION 6
         pila.push(2102); //Accion 102
          pila.push(2103); //Accion 103
        pila.push(2004); //ACCION 4
        break;
    case 49:
        pila.pop();
        pila.push(23);
        pila.push(1006);
        pila.push(2006);//ACCION 6
         pila.push(2102); //Accion 102
         pila.push(2103); //Accion 103
         pila.push(2004); //ACCION 4
        break;
    case 50:
        pila.pop();
         pila.push(2004); //ACCION 4
         pila.push(2103); //Accion 103
        break;
    case 51:
        pila.pop();
         pila.push(1010);
         pila.push(2102); //Accion 102
        break;
    case 52:
        pila.pop();
        pila.push(1015);
         pila.push(2102); //Accion 102
        break;
    case 53:
        pila.pop();
        pila.push(1011);
         pila.push(2102); //Accion 102
        break;
    case 54:
        pila.pop();
        pila.push(1012);
         pila.push(2102); //Accion 102
        break;
    case 55:
        pila.pop();
        pila.push(1013);
         pila.push(2102); //Accion 102
        break;
    case 56:
        pila.pop();
        pila.push(1014);
         pila.push(2102); //Accion 102
        break;
    case 57:
        pila.pop();
        pila.push(27);
         pila.push(28);
        break;
    case 58:
        pila.pop();
        pila.push(26);
        pila.push(1007);
        pila.push(2005); //Accion 5
        pila.push(2102); //Accion 102
        pila.push(2103); //Accion 103
        pila.push(2003); //Accion 3
        break;
    case 59:
        pila.pop();
        pila.push(26);
        pila.push(1008);
        pila.push(2005);//Accion 5
         pila.push(2102); //Accion 102
         pila.push(2103); //Accion 103
        pila.push(2003);//Accion 3
        break;
    case 60:
        pila.pop();
        pila.push(26);
        pila.push(1028);
        pila.push(2005);//Accion 5
         pila.push(2102); //Accion 102
         pila.push(2103); //Accion 103
        pila.push(2003);//Accion 3
        break;
    case 61:
        pila.pop();
        pila.push(2003);//Accion 3
         pila.push(2103); //Accion 103
        break;
    case 62:
        pila.pop();
        pila.push(1002);
         pila.push(2001);//Accion 1
                pila.push(2101);//Accion 101

        break;
    case 63:
        pila.pop();
        pila.push(1003);
           pila.push(2001);//Accion
                pila.push(2101);//Accion 101

        break;
    case 64:
        pila.pop();
        pila.push(1004);
           pila.push(2001);//Accion
                 pila.push(2101);//Accion 101

        break;
    case 65:
        pila.pop();
        pila.push(1025);
           pila.push(2001);//Accion
                 pila.push(2101);//Accion 101

        break;
    case 66:
        pila.pop();
        pila.push(1026);
           pila.push(2001);//Accion
            pila.push(2101);//Accion 101

        break;
    case 67:
        pila.pop();
        pila.push(1020);
         pila.push(2008);
        pila.push(16);
        pila.push(1019);
        pila.push(2007);
        break;
    case 68:
        pila.pop();
        pila.push(13);
           pila.push(2001);//Accion
        break;
    case 69:
        pila.pop();
         pila.push(2129); //Accion 128
        pila.push(2100); //ACCION 100
        pila.push(1020);
        pila.push(36);
        pila.push(16);
        pila.push(1019);
        pila.push(2128); //Accion 128
        pila.push(2099); //Accion 99
        pila.push(1048);
        break;
    case 70:
        pila.pop();
          pila.push(2131); //Accion 131
        pila.push(1020);
         pila.push(37);
          pila.push(2101); //Accion 101
         pila.push(1001);
         pila.push(1019);
          pila.push(1047);
          pila.push(2130); //Accion 130
        break;
    case 71:
        pila.pop();
        pila.push(1044);
           pila.push(2110); //Accion 110
         pila.push(2109); //Accion 109
        pila.push(33);
        pila.push(32);
        pila.push(10);
          pila.push(2100); //ACCION 100
         pila.push(2107); //ACCION 106
          pila.push(2106); //ACCION 106
        pila.push(1020);
         pila.push(16);
          pila.push(2105); //Accion 105
          pila.push(2099); //Accion 99
         pila.push(1019);
          pila.push(1038);
        break;
      case 72:
        pila.pop();

        pila.push(32);
               pila.push(2109); //ACCION 100
        pila.push(10);
          pila.push(2100); //ACCION 100
               pila.push(2107); //ACCION 107
                 pila.push(2106); //ACCION 106
        pila.push(1020);
        pila.push(16);
        pila.push(1019);
           pila.push(2099); //Accion 99
               pila.push(2108); //ACCION 108
                  pila.push(2105); //ACCION 105
        pila.push(1040);
        break;
      case 73:
          pila.pop();
          break;
      case 74:
          pila.pop();
          pila.push(10);
           pila.push(2108); //Accion 108
           pila.push(1039);
          break;
      case 75:
          pila.pop();

          break;
      case 76:
          pila.pop();
          pila.push(1045);
           pila.push(2126); //ACCION 126
          pila.push(10);
          pila.push(2100); //ACCION 100
            pila.push(2107); //Accion 107
             pila.push(2106); //Accion 106
          pila.push(1020);
          pila.push(16);
          pila.push(1019);
          pila.push(2125); //Accion 125
            pila.push(2099); //Accion 99
         pila.push(1046);
          break;
      case 77:
          pila.pop();
          pila.push(1043);
           pila.push(2100); //ACCION 100
          pila.push(2127); //Accion 127
          pila.push(2106); //Accion 106
          pila.push(1020);
          pila.push(16);
          pila.push(1019);
              pila.push(2099); //Accion 99
          pila.push(1042);
          pila.push(10);
            pila.push(2125); //Accion 125
          pila.push(1041);
          break;
      case 78:
          pila.pop();
          pila.push(36);
          pila.push(16);
          pila.push(1024);
          break;
      case 79:
          pila.pop();
          break;
      case 80:
          pila.pop();
          pila.push(4);
          pila.push(1001);
          pila.push(1024);
          break;
      case 81:
          pila.pop();
          break;

    }
}
int Convertir(QString tipoA){
    if(tipoA=="E"){
        return 0;
    }
    if(tipoA=="R"){
        return 1;
    }
    if(tipoA=="B"){
        return 2;
    }
    if(tipoA=="C"){
        return 3;
    }
    if(tipoA=="S"){
        return 4;
    }
    if(tipoA=="N"){
        return 5;
    }
    return 2;//null
}
void TablaTipos(){
    int OP;
    QString signo;
    //+ y -
    if(pilaOP.top()==1005 || pilaOP.top()==1006){
        OP=0;
        switch (pilaOP.top()){

        case 1005:
            signo ="+";
        break;
        case 1006:
            signo ="-";
            break;
        }
    }
    // * / %
    if(pilaOP.top()==1007 || pilaOP.top()==1008 || pilaOP.top()==1028){
        OP=1;

        switch (pilaOP.top()){

        case 1007:
            signo ="*";
            break;
        case 1008:
            signo ="/";
            break;
        case 1028:
            signo ="%";
            break;

        }
    }
    //== !=  <  <=  >  >=
    if(pilaOP.top()==1010 || pilaOP.top()==1011 || pilaOP.top()==1012 || pilaOP.top()==1013 || pilaOP.top()==1014 || pilaOP.top()==1015 || pilaOP.top()==1016){
        OP=2;
        switch (pilaOP.top()){

        case 1010:
            signo ="==";
            break;
        case 1011:
            signo ="<";
            break;
        case 1012:
            signo ="<=";
            break;
        case 1013:
            signo =">";
            break;
        case 1014:
            signo =">=";
            break;
        case 1015:
            signo ="!=";
            break;
        case 1016:
            signo ="!";
            break;
        }
    }
    if(pilaOP.top()==1017 || pilaOP.top()==1018){
        OP=3;
        switch (pilaOP.top()){

        case 1017:
            signo ="&&";
            break;
        case 1018:
            signo ="||";
            break;


        }
    }
    pilaOP.pop();
    int Oper2=Convertir(pilaTipo.top());
    QString ET2=pilaTipo.top();
    pilaTipo.pop();
    int Oper1=Convertir(pilaTipo.top());
      QString ET1=pilaTipo.top();
    pilaTipo.pop();
    switch (Oper1){
        case 0:
            if(TE[Oper2][OP]=="X"){
                Error=Error+"8002 Error entre tipos  "+ET1+" "+signo+" "+ET2+" \n";
                pilaTipo.push("E");
            }else{
                pilaTipo.push(TE[Oper2][OP]);
                  std::cout<<TE[Oper2][OP].toStdString()<<std::endl;
                //Error=Error+" hice operacion "+QString::number(Oper1)+" "+QString::number(OP)+" "+QString::number(Oper2)+" Resultado un"+ TE[Oper2][OP]+"\n";

            }
        break;
        case 1:
            if(TR[Oper2][OP]=="X"){
                Error=Error+"8002 Error entre tipos  "+ET1+" "+signo+" "+ET2+" \n";
                pilaTipo.push("E");
            }else{
                pilaTipo.push(TR[Oper2][OP]);
                   std::cout<<TR[Oper2][OP].toStdString()<<std::endl;
                 //   Error=Error+" hice operacion "+QString::number(Oper1)+" "+QString::number(OP)+" "+QString::number(Oper2)+" Resultado un"+ TE[Oper2][OP]+"\n";

            }
        break;
        case 2:
            if(TB[Oper2][OP]=="X"){
                Error=Error+"8002 Error entre tipos  "+ET1+" "+signo+" "+ET2+" \n";
                pilaTipo.push("E");
            }else{
                pilaTipo.push(TB[Oper2][OP]);
                   std::cout<<TB[Oper2][OP].toStdString()<<std::endl;
                   //  Error=Error+" hice operacion "+QString::number(Oper1)+" "+QString::number(OP)+" "+QString::number(Oper2)+" Resultado un"+ TE[Oper2][OP]+"\n";
            }
        break;
        case 3:
            if(TC[Oper2][OP]=="X"){
                Error=Error+"8002 Error entre tipos  "+ET1+" "+signo+" "+ET2+" \n";
                pilaTipo.push("E");
            }else{
                pilaTipo.push(TC[Oper2][OP]);
                   std::cout<<TC[Oper2][OP].toStdString()<<std::endl;
                   // Error=Error+" hice operacion "+QString::number(Oper1)+" "+QString::number(OP)+" "+QString::number(Oper2)+" \n";

            }
        break;
        case 4:
            if(TS[Oper2][OP]=="X"){
                Error=Error+"8002 Error entre tipos  "+ET1+" "+signo+" "+ET2+" \n";
                pilaTipo.push("E");
            }else{
                pilaTipo.push(TS[Oper2][OP]);
                   std::cout<<TS[Oper2][OP].toStdString()<<std::endl;
                    Error=Error+" hice operacion "+QString::number(Oper1)+" "+QString::number(OP)+" "+QString::number(Oper2)+" \n";

            }
        break;
        case 5:
            if(TN[Oper2][OP]=="X"){
                Error=Error+"8002 Error entre tipos  "+ET1+" "+signo+" "+ET2+" \n";
                pilaTipo.push("E");
            }else{
                pilaTipo.push(TN[Oper2][OP]);
                   std::cout<<TN[Oper2][OP].toStdString()<<std::endl;
                    Error=Error+" hice operacion "+QString::number(Oper1)+" "+QString::number(OP)+" "+QString::number(Oper2)+" \n";

            }
        break;

    }


}
QString Signo=" ";
void convertirSignos(int b){
    if(b==1010){
        //CuadruploSignos=CuadruploSignos+"==";
        Signo="==";
    }
    if(b==1011){
       Signo="<";
    }
    if(b==1012){
        Signo="<=";
    }
    if(b==1013){
        Signo=">";
    }
    if(b==1014){
       Signo=">=";
    }
    if(b==1015){
        Signo="!=";
    }
    if(b==1005){
        Signo="+";
    }
    if(b==1006){
        Signo="-";
    }
    if(b==1018){
        Signo="||";
    }
    if(b==1007){
        Signo="*";
    }
    if(b==1008){
        Signo="/";
    }
    if(b==1028){
        Signo="%";
    }
    if(b==1017){
        Signo="&&";
    }
    if(b==1009){
        Signo="=";
    }
}

void Rellenar(int posicion, std::string valor){ //Recibe posicion y valor
    ResultadoCI=ResultadoC.begin();
    for(int ik=1;ik<(posicion);ik++){ //Busca hasta encontrar posicion de resultados
        ResultadoCI++;
    }
//Una vez en posicion
    *ResultadoCI=valor; //Reemplazo valor
    RellenarS=RellenarS+" ("+QString::number(posicion)+","+QString::fromStdString(valor)+")"; //imprimo en los rellenar

}

bool unico=false;
bool acciones=true;
void Acciones(int A){
    switch(A){
        case 2001: //Push la pila
        pila.pop();

            if(tipopila=="E"){
                //std::cout<<"Meti un Entero"<<std::endl;
                pilaTipo.push("E");
                 openpila=openpila+" "+"E";
            }else{
            if(tipopila=="R"){
                // std::cout<<"Meti un Real"<<std::endl;
                   pilaTipo.push("R");
                 openpila=openpila+" "+"R";
            }else{
            if(tipopila=="N"){
              //   std::cout<<"Meti un Notacion Cientifica"<<std::endl;
                   pilaTipo.push("N");
                  openpila=openpila+" "+"N";
            }else{
                if(tipopila=="S"){
                       // std::cout<<"Meti un String"<<std::endl;
             openpila=openpila+" "+"S";
                       pilaTipo.push("S");
                }else{
                    if(tipopila=="C"){
                         //  std::cout<<"Meti un Char"<<std::endl;
                     openpila=openpila+" "+"C";
                           pilaTipo.push("C");
                    }
                    else{
                        Iterador1=NombreV.begin();
                        Iterador2=TipoV.begin();
                        int co=1;
                        while(*Iterador1 != UltimoId.toStdString()){
                            if(co>=NombreV.size()){
                                NombreV.push_back(UltimoId.toStdString());
                                contadorV++;
                                TipoV.push_back("E");
                                contadorV2++;
                                Error=Error+"8001 VARIABLE "+UltimoId+" NO DEFINIDA \n";
                                Iterador2++;
                                Iterador1++;
                              openpila=openpila+" "+"E";
                                break;



                            }
                            Iterador1++;
                            Iterador2++;
                            co++;
                        }
                        pilaTipo.push(QString::fromStdString(*Iterador2));
                        openpila=openpila+" "+QString::fromStdString(*Iterador2);
                      //  std::cout<<*Iterador2+" en "<<std::endl;

                    }
                }

            }
            }

            }


           // std::cout<<UltimoId.toStdString()<<std::endl;
        break;
        case 2002:
            pila.pop();
            pilaOP.push(NextToken);
             // std::cout<<"Meti un"<<std::endl;
           // std::cout<<"="<<std::endl;
             operpila=operpila+" "+"=";

        break;
        case 2003:
            pila.pop();
            //Si en el tope hay un * / % &&
            if(pilaOP.top()==1007 || pilaOP.top()==1008 || pilaOP.top()==1017 || pilaOP.top()==1028){
                TablaTipos();
            }
        break;
        case 2004:
            pila.pop();
            //Si en el tope hay un + - ||
            if(pilaOP.top()==1005 || pilaOP.top()==1006 || pilaOP.top()==1018){
                TablaTipos();
            }
        break;
        case 2005:
            pila.pop();
            pilaOP.push(NextToken);
              //   std::cout<<"Meti un"<<std::endl;
            //  std::cout<<NextToken<<std::endl;
            switch (NextToken){
            case 1007:
                  operpila=operpila+" "+"*";
                break;
            case 1008:
                operpila=operpila+" "+"/";
                break;
            case 1017:
                operpila=operpila+" "+"&&";
                break;
            case 1028:
                operpila=operpila+" "+"%";
                break;
            }

        break;
        case 2006:
            pila.pop();
            pilaOP.push(NextToken);
           // std::cout<<"Meti un"<<std::endl;
           // std::cout<<NextToken<<std::endl;
            switch (NextToken){
            case 1005:
                operpila=operpila+" "+"+";
                break;
            case 1006:
                operpila=operpila+" "+"-";
                break;
            case 1018:
                operpila=operpila+" "+"||";
                break;
            }
        break;
        case 2007:
             pila.pop();
            pilaOP.push(1099);
             // std::cout<<"Meti una MFF"<<std::endl;
             operpila=operpila+" "+"MFF";
        break;
        case 2008:
             pila.pop();
            pilaOP.pop();
       // std::cout<<"Saque una MFF"<<std::endl;
        break;
        case 2009:
            pila.pop();
            if(pilaOP.top()==1009){
                pilaOP.pop();
                QString Resultado = pilaTipo.top();
                pilaTipo.pop();
                 QString Asignacion = pilaTipo.top();
                pilaTipo.pop();
                 if(Resultado!=Asignacion){
                      Error=Error+"8003 Error entre tipos al asignar "+Asignacion+" = "+Resultado+" \n";
                }

            }
        break;
        case 2099:
            pila.pop();
            acciones =false; //desactiva las acciones
        break;
        case 2100:
            pila.pop();
            acciones =true; //Activa las acciones
            break;

        //CUADRUPLOS
        case 2101:        //Accion 101 Almacena el caracter en la pila de operandos


            pila.pop();
            pilaCuadruplosOpe.push(Ultimocar);              //Almacena en la pila de operandos
            CuadruploOper=CuadruploOper+Ultimocar+" ";      //Concatena para mostrarlo

        break;
        case 2102:            //Accion 102 Almacena el caracter en la pila de operadores

            pila.pop();
            convertirSignos(NextToken);             //Convierte el int a string
            CuadruploSignos=CuadruploSignos+Signo+" "; //Lo concatena para mostrar
             operpila=operpila+Signo;                     //Lo concatena para imprimirlo en la pila
            pilaCuadruplosSignos.push(NextToken); // < == > != <= >= * / % +  Lo mete en la pila de operadores


            break;
        case 2103:          //Accion 103
            // Si es && * /  %
            pila.pop();
            if(NextToken==1007 || NextToken ==1008 ||  NextToken ==1028 || NextToken ==10017 ){ //Revisa si sigue signo
                if(pilaCuadruplosSignos.top() ==1007 || pilaCuadruplosSignos.top() ==1008 || pilaCuadruplosSignos.top() ==1028 || pilaCuadruplosSignos.top() ==1017){ //Revisa si es uno de alta priorida
                    if(pilaCuadruplosSignos.top() == 1005 || pilaCuadruplosSignos.top() == 1006 || pilaCuadruplosSignos.top() == 1007 || pilaCuadruplosSignos.top() == 1008 || pilaCuadruplosSignos.top() == 1017 || pilaCuadruplosSignos.top() == 1018){

                        Op2C.push_back(pilaCuadruplosOpe.top().toStdString()); // //Op2
                        pilaCuadruplosOpe.pop();
                        Op1C.push_back(pilaCuadruplosOpe.top().toStdString()); //Op1
                        pilaCuadruplosOpe.pop();

                        convertirSignos(pilaCuadruplosSignos.top());
                        OperadorC.push_back(Signo.toStdString()); //Operador
                        pilaCuadruplosSignos.pop();


                        ResultadoC.push_back(("RN"+QString::number(Resultados).toStdString()));
                        pilaCuadruplosOpe.push("RN"+QString::number(Resultados)); //Resultados
                        CuadruploOper=CuadruploOper+"RN"+QString::number(Resultados)+" ";
                        Resultados++;

                        poscuadruplo++;
                    }
                }
            }
            else{
                if(pilaCuadruplosSignos.top() == 1005 || pilaCuadruplosSignos.top() == 1006 || pilaCuadruplosSignos.top() == 1007 || pilaCuadruplosSignos.top() == 1008 || pilaCuadruplosSignos.top() == 1017 || pilaCuadruplosSignos.top() == 1018){

                    Op2C.push_back(pilaCuadruplosOpe.top().toStdString()); // //Op2
                    pilaCuadruplosOpe.pop();
                    Op1C.push_back(pilaCuadruplosOpe.top().toStdString()); //Op1
                    pilaCuadruplosOpe.pop();

                    convertirSignos(pilaCuadruplosSignos.top());
                    OperadorC.push_back(Signo.toStdString()); //Operador
                    pilaCuadruplosSignos.pop();


                    ResultadoC.push_back(("RN"+QString::number(Resultados).toStdString()));
                    pilaCuadruplosOpe.push("RN"+QString::number(Resultados)); //Resultados
                    CuadruploOper=CuadruploOper+"RN"+QString::number(Resultados)+" ";
                    Resultados++;

                    poscuadruplo++;
                }
            }



            break;
        case 2104:             //Acccion 104 genero cuadruplo de asignacion
            pila.pop();

            ResultadoC.push_back(pilaCuadruplosOpe.top().toStdString()); //Res
            pilaCuadruplosOpe.pop();

            Op2C.push_back("null"); // //Op2

            Op1C.push_back(pilaCuadruplosOpe.top().toStdString()); //Op1 =
            pilaCuadruplosOpe.pop();

            convertirSignos(pilaCuadruplosSignos.top());
            OperadorC.push_back(Signo.toStdString()); //Operador
            pilaCuadruplosSignos.pop();

            poscuadruplo++;
            break;
        case 2105:             //Accion 105 Mete MFF
            pila.pop();
            pilaCuadruplosSignos.push(10000); //MFF
            CuadruploSignos=CuadruploSignos+"MFF ";
            break;
        case 2106:             //Accion 106 Cuadruplo incondicional
            pila.pop();

            Op2C.push_back(pilaCuadruplosOpe.top().toStdString()); // //Op2
            pilaCuadruplosOpe.pop();
            Op1C.push_back(pilaCuadruplosOpe.top().toStdString()); //Op1
            pilaCuadruplosOpe.pop();

            convertirSignos(pilaCuadruplosSignos.top());
            OperadorC.push_back(Signo.toStdString()); //Operador
            pilaCuadruplosSignos.pop();


            ResultadoC.push_back(("RN"+QString::number(Resultados).toStdString()));
            pilaCuadruplosOpe.push("RN"+QString::number(Resultados)); //Resultados
            CuadruploOper=CuadruploOper+"RN"+QString::number(Resultados)+" ";
            Resultados++;

            poscuadruplo++;

            break;

        case 2107: // Salto en falso
            pila.pop();

            Op2C.push_back(" "); // //Op2

            Op1C.push_back(pilaCuadruplosOpe.top().toStdString()); //Op1
            pilaCuadruplosOpe.pop();


            OperadorC.push_back("SF"); //Operador



            ResultadoC.push_back(" "); //Res

            pilaCuadruplosSaltos.push(poscuadruplo); //Saltos
            CuadruploSaltos=CuadruploSaltos+QString::number(poscuadruplo)+" ";

            poscuadruplo++;
            break;
        case 2108: // Salto incondicional
            pila.pop();

             OperadorC.push_back("SI"); //Operador
             Op2C.push_back(" "); // //Op2
             Op1C.push_back(" "); // //Op1
              ResultadoC.push_back(" "); //Res

             Rellenar( pilaCuadruplosSaltos.top(),std::to_string(poscuadruplo+1));
              pilaCuadruplosSaltos.pop();

             pilaCuadruplosSaltos.push(poscuadruplo); //Saltos
             CuadruploSaltos=CuadruploSaltos+QString::number(poscuadruplo)+" ";




             poscuadruplo++;

            break;
        case 2109: //rellenar
            pila.pop();
            Rellenar( pilaCuadruplosSaltos.top(),std::to_string(poscuadruplo));
             pilaCuadruplosSaltos.pop();
        break;
        case 2110:
            pila.pop();
            if(pilaCuadruplosSignos.top()==10000){
            pilaCuadruplosSignos.pop();
               // std::cout<<"SAQUE MFF"<<std::endl;
            }

        break;
        //Casos de while
        case 2125:
            pila.pop();
             pilaCuadruplosSignos.push(9999999); // Herramienta especial ;)
            pilaCuadruplosSaltos.push(poscuadruplo); //Saltos
            CuadruploSaltos=CuadruploSaltos+QString::number(poscuadruplo)+" ";

        break;
        case 2126:
            pila.pop();


            Rellenar( pilaCuadruplosSaltos.top(),std::to_string(poscuadruplo+1));
            pilaCuadruplosSaltos.pop();


            OperadorC.push_back("SI"); //Operador
            Op2C.push_back(" "); // //Op2
            Op1C.push_back(" "); // //Op1
            ResultadoC.push_back(std::to_string((pilaCuadruplosSaltos.top()))); //Res
            pilaCuadruplosSaltos.pop();



            poscuadruplo++;
            pilaCuadruplosSignos.pop(); //Saco herramienta especial
            break;
           //CASOS DO WHILE
        case 2127:
            pila.pop();

            Op2C.push_back(" "); // //Op2

            Op1C.push_back(pilaCuadruplosOpe.top().toStdString()); //Op1
            pilaCuadruplosOpe.pop();


            OperadorC.push_back("SV"); //Operador



            ResultadoC.push_back(std::to_string(pilaCuadruplosSaltos.top())); //Res

            pilaCuadruplosSaltos.pop();
            pilaCuadruplosSignos.pop();

            poscuadruplo++;
            break;
        //Caso output
        case 2128:
            pila.pop();
         pilaCuadruplosSignos.push(9999999); // Herramienta especial ;)
               CuadruploSignos=CuadruploSignos+"Output ";
        break;
        case 2129:
            pila.pop();


            OperadorC.push_back("Output"); //Operador
            Op2C.push_back(" "); // //Op2
            Op1C.push_back(" "); // //Op1
            ResultadoC.push_back((pilaCuadruplosOpe.top()).toStdString()); //Res
            pilaCuadruplosOpe.pop();
            pilaCuadruplosSignos.pop();


            poscuadruplo++;


        break;
        case 2130:
            pila.pop();
            pilaCuadruplosSignos.push(9999999); // Herramienta especial ;)
            CuadruploSignos=CuadruploSignos+"Input ";
        break;
        case 2131:
            pila.pop();


            OperadorC.push_back("Input"); //Operador
            Op2C.push_back(" "); // //Op2
            Op1C.push_back(" "); // //Op1
            ResultadoC.push_back((pilaCuadruplosOpe.top()).toStdString()); //Res
            pilaCuadruplosOpe.pop();
             pilaCuadruplosSignos.pop();



            poscuadruplo++;
        break;

    }

}

char* Sintactico(){
    Error="";
    token="";
    cadenas="";
    pila.push(1058); //Signo de $
    pila.push(0);    // Produccion inicial
      NextToken=Analiza();
    while(!pila.empty()){
        //NextToken=Analiza(); //Dame token
        if(pila.top()>1000){
            if(pila.top()==NextToken && NextToken==1058){
                pila.pop();

                //Iterador1=NombreV.begin();
                //Iterador2=TipoV.begin();
               // for(Iterador1;Iterador1!= NombreV.end();Iterador1++){
                  //  std::cout<<*Iterador1<<std::endl;
                   // std::cout<<*Iterador2<<std::endl;
                 //   Iterador2++;
               // }


            return "El archivo es valido";
            }
            else{
              //  std::cout<<pila.top()<<std::endl;
               // std::cout<<NextToken<<std::endl;
                if(pila.top()>2000){ // ACCIONES
                   // std::cout<<"Voy a hacer accion"<<std::endl;
                    if(acciones){
                      Acciones(pila.top());
                   }
                    else{
                        if(pila.top()==2100 || pila.top()==2001 ){
                         Acciones(pila.top());
                        }else{

                            if(pila.top()>2100){
                               // std::cout<<"Voy a hacer accion de cuadruplo"<<std::endl;
                                 Acciones(pila.top());
                            }
                            else{
                                //  std::cout<<pila.top()<<std::endl;
                                pila.pop();
                            }



                        }
                    }

                }
                else{
                if(pila.top()==NextToken){
                    pila.pop();
                    NextToken=Analiza();
                 //   std::cout<<"Token valido"<<std::endl;
                   //  std::cout<<"Nuevo token"<<std::endl;
                    //  std::cout<<NextToken<<std::endl;

                }
                else{
                   return "El archivo NO es valido";
                }
                }
            }

        }
    else{

          //  std::cout<<pila.top()<<std::endl;
             NT= NextToken-1001;

            //  std::cout<<NT<<std::endl;
           // std::cout<<MP[pila.top()][NT]<<std::endl;
               x=MP[pila.top()][NT];
        if((MP[pila.top()][NT])<82){


            producciones(x);
            }
        else{
           return erroresP(x);
        }

    }
    }





}


void MainWindow::on_pushButton_clicked()
{

}


void MainWindow::on_pushButton_2_clicked()
{

}


void MainWindow::on_Analizar_clicked()
{
    Codigo2 = ui->codigo->toPlainText();
    if (Codigo2==""){
        QMessageBox::information(this,tr("Porfavor ponga algo en el codigo"),"Por favor escriba en el codigo o seleccione un archivo con el boton de"
                                                                             " abrir antes de intentar analizarlo");
        }
    else{
        RellenarS="";
        openpila="";
            operpila="";
        CuadruploSignos="";
        CuadruploSaltos="";
        CuadruploOper="";
        poscuadruplo=1;
        Resultados=1;
        Error="";
       token="";
        cont=0;
       Tamano=10;
        fila=0;
    col=0;
       contadorV=0;
    contadorV2=0;
       TipoV.clear();
    NombreV.clear();
       Op2C.clear();
        Op1C.clear();
        OperadorC.clear();
            ResultadoC.clear();
    ui->errores->setText("");
     ui->tokens->setText("");
    ui->TxtPila->setText("");
    ui->TxtPilaOp->setText("");
     ui->TxtPilaCuadruplosSignos->setText("");
    ui->TxtPilaCuadruplosSaltos->setText("");
    ui->TxtPilaCuadruplosOP->setText("");
    ui->txtPilaRellenar->setText("");



    std::cout<<Sintactico()<<std::endl;

//std::cout<<Analiza()<<std::endl;
    ui->errores->setText(Error);
    ui->tokens->setText(token);
      ui->TxtPila->setText(openpila);
       ui->TxtPilaOp->setText(operpila);
      ui->TxtPilaCuadruplosSignos->setText(CuadruploSignos);
       ui->TxtPilaCuadruplosSaltos->setText(CuadruploSaltos);
      ui->TxtPilaCuadruplosOP->setText(CuadruploOper);
       ui->tablaCuadruplos->horizontalHeader()->sectionResizeMode(QHeaderView::ResizeMode::Stretch);
           ui->txtPilaRellenar->setText(RellenarS);
          ui->tablaCuadruplos->setRowCount(poscuadruplo);


          Op2CI=Op2C.begin();
            Op1CI=Op1C.begin();
          OperadorCI=OperadorC.begin();
          ResultadoCI=ResultadoC.begin();
          fila=0;

       for(int numeros=1;numeros<poscuadruplo;numeros++){
              ui->tablaCuadruplos->setItem(fila,0,new QTableWidgetItem(QString::number(numeros)));
           ui->tablaCuadruplos->setItem(fila,1,new QTableWidgetItem(QString(QString::fromStdString(*OperadorCI))));
          ui->tablaCuadruplos->setItem(fila,2,new QTableWidgetItem(QString(QString::fromStdString( *Op1CI))));
           ui->tablaCuadruplos->setItem(fila,3,new QTableWidgetItem(QString(QString::fromStdString(*Op2CI))));
          ui->tablaCuadruplos->setItem(fila,4,new QTableWidgetItem(QString(QString::fromStdString(*ResultadoCI))));
          Op2CI++;
          Op1CI++;
           OperadorCI++;
          ResultadoCI++;
           fila++;


       }

        }
}


void MainWindow::on_Abrir_clicked()
{

    QString filename = QFileDialog::getOpenFileName(
        this,tr("Abre archivo"),
        "C://",
        "Archivos kCod (*.kcod);;Archivos txt (*.txt)"

        );
   // QMessageBox::information(this,tr("Nombre del arhivo"),filename);
    filename2 = filename.toStdString();
    ui->codigo->setText(leer());
    ui->errores->setText("");
    ui->tokens->setText("");
    ui->TxtPila->setText("");
    ui->TxtPilaOp->setText("");
    ui->txtPilaRellenar->setText("");

    ui->TxtPilaCuadruplosSignos->setText("");
    ui->TxtPilaCuadruplosSaltos->setText("");
    ui->TxtPilaCuadruplosOP->setText("");
      ui->tablaCuadruplos->setRowCount(0);
    Error="";
    token="";
    cont=0;
    Tamano=10;
    col=0;
    openpila="";
    operpila="";
    CuadruploSignos="";
    CuadruploSaltos="";
    CuadruploOper="";
    poscuadruplo=1;
    Resultados=1;
    RellenarS="";

}


void MainWindow::on_Limpiar_clicked()
{
    filename2="";
    ui->errores->setText("");
    ui->tokens->setText("");
    ui->codigo->setText("");
    ui->TxtPila->setText("");
    ui->TxtPilaOp->setText("");
    ui->TxtPilaCuadruplosSignos->setText("");
    ui->TxtPilaCuadruplosSaltos->setText("");
    ui->TxtPilaCuadruplosOP->setText("");
     ui->tablaCuadruplos->setRowCount(0);
    ui->txtPilaRellenar->setText("");
    Error="";
    token="";
    cont=0;
    Tamano=10;    col=0;
    openpila="";
    operpila="";
    CuadruploSignos="";
    CuadruploSaltos="";
    CuadruploOper="";
    poscuadruplo=1;
    Resultados=1;
    fila=0;
    RellenarS="";


}


void MainWindow::on_Guardar_clicked()
{

    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    "C://",
                                                    QFileDialog::ShowDirsOnly
                                                        | QFileDialog::DontResolveSymlinks);

 QString archivo = QInputDialog::getText(0,"Introoduzca el nombre del archivo",QString::fromStdString(filename2));

      QFile file(dir+"/"+archivo+".kcod");
      if(file.open(QIODevice::Truncate | QIODevice::ReadWrite)){
          QTextStream stream(&file);
          stream << ui->codigo->toPlainText();

      }

      file.close();
       QMessageBox::information(this,tr("Guardado exitoso "),"Se guardo "+archivo+".kcod en "+dir);
}

