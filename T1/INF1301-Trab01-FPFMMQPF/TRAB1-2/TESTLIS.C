/***************************************************************************
*  $MCI M�dulo de implementa��o: TLIS Teste lista de s�mbolos
*
*  Arquivo gerado:              TestLIS.c
*  Letras identificadoras:      TLIS
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs - Arndt Von Staa
*           mmq - Matheus de Mello Queiroz
*			fpf - Felipe Pessoa de Freitas
*			pf  - Pedro Ferreira Alves Pinto
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor		Data        Observa��es
*	  9		  fpf		11/set/2016	fun��es LIS_InserirElementoAntes e LIS_InserirElementoApos removidas dos testes
*     8       mmq		09/set/2016 melhorias na legibilidade do modulo
*	  7		  fpf		08/set/2016	teste das fun��es LIS_ExibirConteudoLista e LIS_InserirElementoOrdenado
*	  6		  fpf		08/set/2016	teste da fun��o LIS_ProcurarValor
*	  5		  fpf/pf	08/set/2016	altera��o na fun��o DestruirValor e adapta��es nos testes para novo tipo
*     4       avs		01/fev/2006 criar linguagem script simb�lica
*     3       avs		08/dez/2004 uniformiza��o dos exemplos
*     2       avs		07/jul/2003 unifica��o de todos os m�dulos em um s� projeto
*     1       avs		16/abr/2003 in�cio desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "Lista.h"


static const char RESET_LISTA_CMD         [ ] = "=resetteste"     ;
static const char CRIAR_LISTA_CMD         [ ] = "=criarlista"     ;
static const char DESTRUIR_LISTA_CMD      [ ] = "=destruirlista"  ;
static const char ESVAZIAR_LISTA_CMD      [ ] = "=esvaziarlista"  ;
static const char INS_ELEM_ANTES_CMD      [ ] = "=inselemantes"   ;
static const char INS_ELEM_APOS_CMD       [ ] = "=inselemapos"    ;
static const char INS_ELEM_ORD_CMD		  [ ] = "=inselemord"	  ;
static const char OBTER_VALOR_CMD         [ ] = "=obtervalorelem" ;
static const char EXC_ELEM_CMD            [ ] = "=excluirelem"    ;
static const char IR_INICIO_CMD           [ ] = "=irinicio"       ;
static const char IR_FIM_CMD              [ ] = "=irfinal"        ;
static const char AVANCAR_ELEM_CMD        [ ] = "=avancarelem"    ;
static const char PROCURAR_VALOR_CMD      [ ] = "=procurarvalor"  ;
static const char EXIBIR_CONTEUDO_CMD     [ ] = "=exibirconteudo" ;


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define NULO     0
#define NAO_NULO 1

#define DIM_VT_LISTA   10
#define DIM_VALOR     100

LIS_tppLista   vtListas[ DIM_VT_LISTA ] ;


/***********************************************************************
*
*  $TC Tipo de dados: LIS Estrutura iniciais-nomes
*
*
***********************************************************************/

typedef struct tagConteudo {

	char * iniciais;
	char * nome;

} tpConteudo;

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

   static void DestruirValor( tpConteudo * pValor ) ;

   static int ValidarInxLista( int inxLista , int Modo ) ;

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TLIS &Testar lista
*
*  $ED Descri��o da fun��o
*     Podem ser criadas at� 10 listas, identificadas pelos �ndices 0 a 10
*
*     Comandos dispon�veis:
*
*     =resetteste
*           - anula o vetor de listas. Provoca vazamento de mem�ria
*     =criarlista                   inxLista
*     =destruirlista                inxLista
*     =esvaziarlista                inxLista
*     =inselemord                   inxLista  string  string  CondRetEsp
*     =obtervalorelem               inxLista  string  string  CondretPonteiro
*     =excluirelem                  inxLista  CondRetEsp
*     =irinicio                     inxLista
*     =irfinal                      inxLista
*     =avancarelem                  inxLista  numElem CondRetEsp
*     =procurarvalor                inxLista  string  string  CondRetEsp
*     =exibirconteudo               inxLista
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int inxLista  = -1 ,
          numLidos   = -1 ,
          CondRetEsp = -1  ;

      TST_tpCondRet CondRet ;

	  tpConteudo * pdado;

      char   StringDado1[  DIM_VALOR ] ;
	  char   StringDado2[  DIM_VALOR ] ;
      char * pDado1 ;
	  char * pDado2 ;

      int ValEsp = -1 ;

      int i ;

      int numElem = -1 ;

      StringDado1[ 0 ] = 0 ;
	  StringDado2[ 0 ] = 0 ;

      /* Efetuar reset de teste de lista */

         if ( strcmp( ComandoTeste , RESET_LISTA_CMD ) == 0 )
         {

            for( i = 0 ; i < DIM_VT_LISTA ; i++ )
            {
               vtListas[ i ] = NULL ;
            } /* for */

            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de lista */

      /* Testar CriarLista */

         else if ( strcmp( ComandoTeste , CRIAR_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                       &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            vtListas[ inxLista ] =
                 LIS_CriarLista( DestruirValor ) ;

			return TST_CompararPonteiroNulo( NAO_NULO , vtListas[ inxLista ] ,
               "Erro em ponteiro de nova lista."  ) ;

         } /* fim ativa: Testar CriarLista */

      /* Testar Esvaziar lista lista */

         else if ( strcmp( ComandoTeste , ESVAZIAR_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                               &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            LIS_EsvaziarLista( vtListas[ inxLista ] ) ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar Esvaziar lista lista */

      /* Testar Destruir lista */

         else if ( strcmp( ComandoTeste , DESTRUIR_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                               &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            LIS_DestruirLista( vtListas[ inxLista ] ) ;
            vtListas[ inxLista ] = NULL ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar Destruir lista */

	  /* Testar inserir elemento ordenado */

		 else if (strcmp(ComandoTeste, INS_ELEM_ORD_CMD) == 0)
		 {

			 numLidos = LER_LerParametros("issi",
				 &inxLista, StringDado1, StringDado2, &CondRetEsp);

			 if ((numLidos != 4)
				 || (!ValidarInxLista(inxLista, NAO_VAZIO)))
			 {
				 return TST_CondRetParm;
			 } /* if */

			 pDado1 = (char *)malloc(strlen(StringDado1) + 1);
			 if (pDado1 == NULL)
			 {
				 return TST_CondRetMemoria;
			 } /* if */

			 strcpy(pDado1, StringDado1);

			 pDado2 = (char *)malloc(strlen(StringDado2) + 1);
			 if (pDado2 == NULL)
			 {
				 return TST_CondRetMemoria;
			 } /* if */

			 strcpy(pDado2, StringDado2);


			 CondRet = LIS_InserirElementoOrdenado(vtListas[inxLista], pDado1, pDado2);

			 if (CondRet != LIS_CondRetOK)
			 {
				 free(pDado1);
			 } /* if */

			 if (CondRet != LIS_CondRetOK)
			 {
				 free(pDado2);
			 } /* if */

			 return TST_CompararInt(CondRetEsp, CondRet,
				 "Condicao de retorno errada ao inserir apos.");

		 } /* fim ativa: Testar inserir elemento ordenado */

      /* Testar excluir simbolo */

         else if ( strcmp( ComandoTeste , EXC_ELEM_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                  &inxLista , &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( CondRetEsp ,
                      LIS_ExcluirElemento( vtListas[ inxLista ] ) ,
                     "Condi��o de retorno errada ao excluir."   ) ;

         } /* fim ativa: Testar excluir simbolo */

      /* Testar obter valor do elemento corrente */

         else if ( strcmp( ComandoTeste , OBTER_VALOR_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "issi" ,
                       &inxLista , StringDado1, StringDado2 , &ValEsp ) ;

            if ( ( numLidos != 4 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            pdado = LIS_ObterValor( vtListas[ inxLista ] ) ;

            if ( ValEsp == 0 )
            {
               return TST_CompararPonteiroNulo( NULO , pdado ,
                         "Valor n�o deveria existir." ) ;
            } /* if */

            if ( pdado == NULL )
            {
				return TST_CompararPonteiroNulo( NAO_NULO , pdado ,
                         "Dado tipo um deveria existir." ) ;
            } /* if */

			if (!TST_CompararString(StringDado1, pdado->iniciais,
				"Valor do elemento errado."))
			{
				return TST_CompararString(StringDado2, pdado->nome,
					"Valor do elemento errado.");
			}

			return TST_CondRetErro;

         } /* fim ativa: Testar obter valor do elemento corrente */

      /* Testar ir para o elemento inicial */

         else if ( strcmp( ComandoTeste , IR_INICIO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" , &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            IrInicioLista( vtListas[ inxLista ] ) ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar ir para o elemento inicial */

      /* LIS  &Ir para o elemento final */

         else if ( strcmp( ComandoTeste , IR_FIM_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" , &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            IrFinalLista( vtListas[ inxLista ] ) ;

            return TST_CondRetOK ;

         } /* fim ativa: LIS  &Ir para o elemento final */

      /* LIS  &Avan�ar elemento */
	  
         else if ( strcmp( ComandoTeste , AVANCAR_ELEM_CMD ) == 0 )
         {
	  
            numLidos = LER_LerParametros( "iii" , &inxLista , &numElem ,
                                &CondRetEsp ) ;
	  
            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */
	  
            return TST_CompararInt( CondRetEsp ,
                      LIS_AvancarElementoCorrente( vtListas[ inxLista ] , numElem ) ,
                      "Condicao de retorno errada ao avancar" ) ;
	  
         } /* fim ativa: LIS  &Avan�ar elemento */
	  
	  /* Testar procurar elemento contendo valor */

		 else if (strcmp(ComandoTeste, PROCURAR_VALOR_CMD) == 0)
		 {
			 numLidos = LER_LerParametros("issi",
				 &inxLista, StringDado1, StringDado2, &CondRetEsp);

			 if ((numLidos != 4)
				 || (!ValidarInxLista(inxLista, NAO_VAZIO)))
			 {
				 return TST_CondRetParm;
			 } /* if */

			 pDado1 = (char *)malloc(strlen(StringDado1) + 1);
			 if (pDado1 == NULL)
			 {
				 return TST_CondRetMemoria;
			 } /* if */

			 strcpy(pDado1, StringDado1);

			 pDado2 = (char *)malloc(strlen(StringDado2) + 1);
			 if (pDado2 == NULL)
			 {
				 return TST_CondRetMemoria;
			 } /* if */

			 strcpy(pDado2, StringDado2);

			 return TST_CompararInt(CondRetEsp,
				 LIS_ProcurarValor(vtListas[inxLista], pDado1,pDado2),
				 "Condicao de retorno errada ao procurar elemento");

		 } /* fim ativa: Testar procurar elemento contendo valor */

	  /* Testar exibir conteudo */

		 else if (strcmp(ComandoTeste, EXIBIR_CONTEUDO_CMD) == 0)
		 {
			 numLidos = LER_LerParametros("i", &inxLista);

			 if ((numLidos != 1)
				 || (!ValidarInxLista(inxLista, NAO_VAZIO)))
			 {
				 return TST_CondRetParm;
			 } /* if */

			 LIS_ExibirConteudoLista(vtListas[inxLista]);

			 return TST_CondRetOK;

		 } /* fim ativa: Testar exibir conteudo */

      return TST_CondRetNaoConhec ;

   } /* Fim fun��o: TLIS &Testar lista */


/*****  C�digo das fun��es encapsuladas no m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TLIS -Destruir valor
*
***********************************************************************/

   void DestruirValor( tpConteudo * pValor )
   {

		free(pValor->iniciais);
		free(pValor->nome);
		free( pValor ) ;

   } /* Fim fun��o: TLIS -Destruir valor */


/***********************************************************************
*
*  $FC Fun��o: TLIS -Validar indice de lista
*
***********************************************************************/

   int ValidarInxLista( int inxLista , int Modo )
   {

      if ( ( inxLista <  0 )
        || ( inxLista >= DIM_VT_LISTA ))
      {
         return FALSE ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
         if ( vtListas[ inxLista ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtListas[ inxLista ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   } /* Fim fun��o: TLIS -Validar indice de lista */

/********** Fim do m�dulo de implementa��o: TLIS Teste lista de s�mbolos **********/

