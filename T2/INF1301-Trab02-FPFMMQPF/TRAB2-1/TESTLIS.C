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
*           fpf - Felipe Pessoa de Freitas
*           mmq - Matheus de Mello Queiroz
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*	  8		  fpf	01/out/2016	Altera��o das fun��es para acompanhar as altera��es do m�dulo lista
*	  7		  fpf	24/set/2016	Incluido teste da LIS_AlterarElemento
*     6       mmq   23/set/2016 adaptar para a utilizacao na aplicacao "Juiz de Xadrez"
*     5       mmq   11/set/2016 alterar a fun��o LIS_ProcuraValor
*     4       avs   01/fev/2006 criar linguagem script simb�lica
*     3       avs   08/dez/2004 uniformiza��o dos exemplos
*     2       avs   07/jul/2003 unifica��o de todos os m�dulos em um s� projeto
*     1       avs   16/abr/2003 in�cio desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "Lista.h"


static const char CRIAR_LISTA_CMD         [ ] = "=criarLista"        ;
static const char OBTER_ID_LISTA_CMD      [ ] = "=obterIdLista"      ;
static const char INSERIR_NO_CMD          [ ] = "=inserirNo"         ;
static const char OBTER_NO_CMD            [ ] = "=obterNo"           ;
static const char EXCLUIR_NO_CMD          [ ] = "=excluirNoCorrente" ;
static const char IR_PROX_CMD             [ ] = "=irProx"            ;
static const char IR_ANT_CMD              [ ] = "=irAnt"             ;
static const char ALTERAR_NO_CMD		  [ ] = "=alterarNoCorrente" ;
static const char DESTRUIR_LISTA_CMD      [ ] = "=destroiLista"      ;
static const char ANDAR_INICIO_CMD		  [ ] = "=andarInicio"		 ;


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define NULO     0
#define NAO_NULO 1

#define DIM_VT_LISTA   10
#define DIM_ID_LISTA   5

#define DIM_VALOR     100

LIS_tppLista   vtListas[ DIM_VT_LISTA ] ;

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

static void DestruirValor( void * pValor ) ;

static int  ValidarInxLista( int inxLista , int Modo ) ;

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
*     =criarLista                   inxLista  string   CondRetEsp
*     =obterIdLista                 inxLista  string  
*     =inserirNo                    inxLista  char     CondRetEsp  
*     =obterNo                      inxLista  char     CondRetPonteiro
*     =excluirNoCorrente            inxLista
*     =irProx                       inxLista           CondRetEsp
*     =irAnt                        inxLista           CondRetEsp
*	  =alterarNoCorrente			inxLista  char	   CondRetEsp
*     =destroiLista                 inxLista           CondRetEsp
*	  =andarInicio					inxLista           CondRetEsp
*
***********************************************************************/

TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{

	int inxLista   = -1 ,
		numLidos   = -1 ,
		CondRetEsp = -1  ;

	TST_tpCondRet CondRet ;
	TST_tpCondRet CondRetAux;

	char IdListaDado[DIM_VALOR];
	char StringIdLista[ DIM_ID_LISTA ] ;
	char * pIdLista;

	char   CharDado ;
	char * pDado ;

	int ValEsp = -1 ;
	
	int numElem = -1 ;
	

	/* LIS  &Criar lista */

		if ( strcmp( ComandoTeste , CRIAR_LISTA_CMD ) == 0 )
		{

			numLidos = LER_LerParametros( "isi" ,
				&inxLista, IdListaDado, &CondRetEsp);

			if (   ( numLidos != 3 )
				|| ( ! ValidarInxLista( inxLista , VAZIO ) ) 
				|| (strlen(IdListaDado) > DIM_ID_LISTA - 1))
			{
				return TST_CondRetParm ;
			} /* if */

			strcpy(StringIdLista, IdListaDado);

			CondRet = LIS_CriarLista(StringIdLista, DestruirValor, 
					&vtListas[inxLista]);

			return TST_CompararInt( CondRetEsp , CondRet ,
					"Condicao de retorno errada ao criar lista." ) ;

		} /* fim ativa: LIS  &Criar lista */

	/* LIS  &Destruir lista */

		else if ( strcmp( ComandoTeste , DESTRUIR_LISTA_CMD ) == 0 )
		{

			numLidos = LER_LerParametros( "ii" ,
					&inxLista, &CondRetEsp ) ;

			if (   ( numLidos != 2 )
				|| ( ! ValidarInxLista( inxLista , NAO_VAZIO ) ) )
			{
				return TST_CondRetParm ;
			} /* if */

			LIS_DestruirLista( vtListas[ inxLista ] ) ;

			vtListas[ inxLista ] = NULL ;

			return TST_CondRetOK ;

		} /* fim ativa: LIS  &Destruir lista */

	/* LIS  &Obter refer�ncia para o identificador da lista */

		else if ( strcmp( ComandoTeste , OBTER_ID_LISTA_CMD ) == 0 )
		{

			numLidos = LER_LerParametros( "is" ,
				&inxLista, IdListaDado);

			if (   ( numLidos != 2 )
				|| ( ! ValidarInxLista( inxLista , NAO_VAZIO ) ) 
				|| (strlen(IdListaDado) > DIM_ID_LISTA - 1))
			{
				return TST_CondRetParm ;
			} /* if */

			strcpy(StringIdLista, IdListaDado);

			pIdLista = NULL;
			CondRet = LIS_ObterId(vtListas[inxLista], &pIdLista);
			if ( pIdLista == NULL )
			{
				return TST_CompararPonteiroNulo( NAO_NULO , pIdLista ,
						"Indice da lista deveria existir." ) ;
			} /* if */

			return TST_CompararString( StringIdLista , pIdLista ,
					"Valor do indice da lista errado." ) ;

		} /* fim ativa: LIS  &Obter refer�ncia para o identificador da lista */

	/* Testar inserir elemento */

		else if ( strcmp( ComandoTeste , INSERIR_NO_CMD ) == 0 )
		{

			numLidos = LER_LerParametros( "ici" ,
					&inxLista , &CharDado , &CondRetEsp ) ;

			if (   ( numLidos != 3 )
				|| ( ! ValidarInxLista( inxLista , NAO_VAZIO ) ) )
			{
				return TST_CondRetParm ;
			} /* if */

			pDado = ( char * ) malloc( sizeof( char ) ) ;
			if ( pDado == NULL )
			{
				return TST_CondRetMemoria ;
			} /* if */

			*pDado = CharDado;

			CondRet = LIS_InserirElemento( vtListas[ inxLista ] , pDado ) ;

			if ( CondRet != LIS_CondRetOK )
			{
				free( pDado ) ;
			} /* if */

			return TST_CompararInt( CondRetEsp , CondRet ,
					"Condicao de retorno errada ao inserir no." ) ;

		} /* fim ativa: Testar inserir elemento */

	/* LIS  &Excluir elemento */

		else if ( strcmp( ComandoTeste , EXCLUIR_NO_CMD ) == 0 )
		{

			numLidos = LER_LerParametros( "i" ,
					&inxLista ) ;

			if (   ( numLidos != 1 )
				|| ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
			{
				return TST_CondRetParm ;
			} /* if */

			CondRet = LIS_ExcluirElemento( vtListas[ inxLista ] );

			return TST_CompararInt( LIS_CondRetOK, CondRet,
					"A lista est� vazia." );

		} /* fim ativa: LIS  &Excluir elemento */

	/* LIS  &Obter refer�ncia para o valor contido no elemento */

		else if ( strcmp( ComandoTeste , OBTER_NO_CMD ) == 0 )
		{

			numLidos = LER_LerParametros( "ici" ,
					&inxLista , &CharDado , &CondRetEsp ) ;

			if (   ( numLidos != 3 )
				|| ( ! ValidarInxLista( inxLista , NAO_VAZIO ) ) )
			{
				return TST_CondRetParm ;
			} /* if */

			pDado = NULL;
			CondRet = LIS_ObterElemento(vtListas[inxLista], &pDado);
			CondRetAux = TST_CompararInt(CondRetEsp, CondRet,
				"Condicao de retorno errada ao obter no.");

			if (CondRetAux != TST_CondOK)
			{
				return CondRetAux;
			} /* if */

			if (CondRet == LIS_CondRetListaVazia)
			{
				return TST_CondRetOK;
			}

			if (pDado == NULL)
			{
				return TST_CompararPonteiroNulo(NAO_NULO, pDado,
					"Valor deveria existir.");
			}

			return TST_CompararChar(CharDado, *pDado,
				"Valor no N� errado.");

		} /* fim ativa: LIS  &Obter refer�ncia para o valor contido no elemento */

	/* LIS  &Ir para o proximo elemento */

		else if ( strcmp( ComandoTeste , IR_PROX_CMD ) == 0 )
		{

			numLidos = LER_LerParametros( "ii" , 
					&inxLista , &CondRetEsp ) ;

			if (   ( numLidos != 2 )
				|| ( ! ValidarInxLista( inxLista , NAO_VAZIO ) ) )
			{
				return TST_CondRetParm ;
			} /* if */

			return TST_CompararInt( CondRetEsp , LIS_IrProxElemento( vtListas[ inxLista ] ) ,
					"Condicao de retorno errada ao ir para o proximo n�." ) ;

		} /* fim ativa: LIS  &Ir para o proximo elemento */

	/* LIS  &Ir para o proximo elemento */

		else if ( strcmp( ComandoTeste , IR_ANT_CMD ) == 0 )
		{

			numLidos = LER_LerParametros( "ii" , 
				&inxLista , &CondRetEsp ) ;

			if (    ( numLidos != 2 )
				|| ( ! ValidarInxLista( inxLista , NAO_VAZIO ) ) )
			{
				return TST_CondRetParm ;
			} /* if */

			return TST_CompararInt( CondRetEsp , LIS_IrAntElemento( vtListas[ inxLista ] ) ,
				"Condicao de retorno errada ao ir para o proximo n�." ) ;

		} /* fim ativa: LIS  &Ir para o proximo elemento */

	/* LIS  &Alterar o valor contido no elemento */

		else if (strcmp(ComandoTeste, ALTERAR_NO_CMD) == 0)
		{

			numLidos = LER_LerParametros("ici",
				&inxLista, &CharDado, &CondRetEsp);

			if ((numLidos != 3)
				|| (!ValidarInxLista(inxLista, NAO_VAZIO)))
			{
				return TST_CondRetParm;
			} /* if */

			pDado = (char *)malloc(sizeof(char));

			if (pDado == NULL)
			{
				return TST_CondRetMemoria;
			} /* if */

			*pDado = CharDado;

			CondRet = LIS_AlterarElemento(vtListas[inxLista],pDado);

			return TST_CompararInt(CondRetEsp, CondRet,
				"Condicao de retorno errada ao alterar n� corrente.");

		} /* fim ativa: LIS  &Alterar o valor contido no elemento */

	/* LIS  &Andar inicio */

		else if (strcmp(ComandoTeste, ANDAR_INICIO_CMD) == 0)
		{

			numLidos = LER_LerParametros("ii",
				&inxLista, &CondRetEsp);

			if ((numLidos != 2)
				|| (!ValidarInxLista(inxLista, NAO_VAZIO)))
			{
				return TST_CondRetParm;
			} /* if */

			CondRet = LIS_AndarInicio(vtListas[inxLista]);

			return TST_CompararInt(CondRetEsp, CondRet,
				"Condicao de retorno errada ao alterar n� corrente.");

		} /* fim ativa: LIS  &Andar inicio */


	return TST_CondRetNaoConhec ;

} /* Fim fun��o: TLIS &Testar lista */


/*****  C�digo das fun��es encapsuladas no m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TLIS -Destruir valor
*
***********************************************************************/

void DestruirValor( void * pValor )
{

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
		if ( vtListas[ inxLista ] != NULL )
		{
			return FALSE ;
		} /* if */
	} else
	{
		if ( vtListas[ inxLista ] == NULL )
		{
			return FALSE ;
		} /* if */
	} /* if */

	return TRUE ;

} /* Fim fun��o: TLIS -Validar indice de lista */

/********** Fim do m�dulo de implementa��o: TLIS Teste lista de s�mbolos **********/

