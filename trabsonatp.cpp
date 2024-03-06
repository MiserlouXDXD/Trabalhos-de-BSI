#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<conio2.h>
#include<ctype.h>


struct tpjogo
{
	int cod;
  	char desc[100], status;
};

struct tppart
{
	int codp;
  	char nome[100], status;
};

struct tpcamp
{
      int codcamp, codjogo, ano;
      char titulo[100],resp [100], descrcamp[500], status;
};

struct control
{
      int codcamp, codpart;
      char nick[100], status;
};

//declaracao de funcoes
int busca_exaust_jogo (FILE * ptr, int cod);
int busca_exaust_part (FILE * ptr, int codp);
int busca_exaust_camp (FILE * ptr, int codcamp);
int busca_exaust_control (FILE * ptr, int codcamp, int codpart);
int busca_exaust_rel1 (FILE * ptr, char nome[50]);
int busca_exaust (FILE * ptr, int code, int code2);

//int busca_exaustsent_camp (FILE * ptr, int codcamp);
int busca_binaria_part(FILE * ptr, int codp);
int busca_seqindex_jogo (FILE * ptr, int cod);

void alterar_camp();
void alterar_jogo();
void alterar_part();

void reljogo(void);
void relpart(void);
void relcamp(void);
void relatorio1 (void);

void bubblesort_jogo (void);
void bubblesort_part (void);
void bubblesort_camp(void);
void bubblesort_control (void);
void insercao_direta_jogo(void);
void ordenacao_direta_part(void);
void bubblesort_part_nome(FILE * ptr);

int  PosMaior (FILE * ptr, int TL);

void exclusao_logi_jogo(void);
void exclusao_logi_part(void);
void exclusao_logi_controle(void);
void exclusao_logi_camp (void);

void consulta_jogo(void);
void consulta_part(void);
void consulta_camp(void);
void consulta_control(void);

void inicializar(void);
void exclusao_fisica(void);
void exclusaofisica_camp (void);

void moldura();
void apagar(int &y);
void pi(int &y);
void inserir(void);

//menus
char menu (void)
{
	int y = 3;
	apagar(y);
	pi(y); printf("* * * MENU * * * ");
	pi(y); printf("[A] p/ cadastrar");
	pi(y); printf("[B] p/ relatorio");
	pi(y); printf("[C] p/ alterar");
	pi(y); printf("[D] p/ excluir");
	pi(y); printf("[E] p/ consultar");
	pi(y); printf("[ESC] p/ sair");
		
	return toupper(getch());
}

char menucad (void)
{
	int y = 3;
	apagar(y);
	pi(y); printf("* * * CADASTROS * * *");
	pi(y); printf("[A] p/ cadastrar jogo");
	pi(y); printf("[B] p/ cadastrar participante");
	pi(y); printf("[C] p/ cadastrar uma competicao");
	pi(y); printf("[D] p/ cadastrar controle");
	
	
	return toupper(getch());
	
}

char menurel (void)
{
	int y = 3;
	apagar(y);
	pi(y); printf("* * * RELATORIOS * * *");
	pi(y); printf("[A] p/ ver relatorio dos jogos cadastrados");
	pi(y); printf("[B] p/ ver relatorio dos participantes cadastrados");
	pi(y); printf("[C] p/ ver relatorio dos campeonatos criados");
	pi(y); printf("[D] p/ ver relatorio do controle");
	pi(y); printf("[E] p/ ver relatorio 1");
	pi(y); printf("[F] p/ ver relatorio 2");
	
	return toupper(getch());
}

char menualt (void)
{
	int y = 3;
	apagar(y);
	pi(y); printf("* * * ALTERACAO * * *");
	pi(y); printf("[A] p/ alterar jogo");
	pi(y); printf("[B] p/ alterar participantes");
	pi(y); printf("[C] p/ alterar campeonatos");
	pi(y); printf("[D] p/ alterar controle");
	
	return toupper(getch());
}

char menuexcl (void)
{
	int y = 3;
	apagar(y);
	pi(y); printf("* * * EXCLUSAO * * *");
	pi(y); printf("[A] p/ excluir jogo");
	pi(y); printf("[B] p/ exluir participante");
	pi(y); printf("[C] p/ excluir campeonato");
	pi(y); printf("[D] p/ excluir controle");
	
	return toupper(getch());
}

char menuconsul (void)
{
	int y = 3;
	apagar(y);
	pi(y); printf("* * * CONSULTAR * * *");
	pi(y); printf("[A] p/ consultar jogo");
	pi(y); printf("[B] p/ consultar participante");
	pi(y); printf("[C] p/ consultar campeonato");
	pi(y); printf("[D] p/ consultar controle");
	
	return toupper(getch());
}

// cadastros
void cadjogo ()
{
	int y = 3;
	FILE * ptr = fopen("jogo.dat","ab+");
	
	tpjogo reg;
	
	int pos;
	
	apagar(y);
	pi(y); printf("* * * Cadastro de Jogo * * *");
	pi(y); printf("Digite o codigo ou '0' p/ sair: ");
	scanf("%d", &reg.cod);
	
	while(reg.cod != 0)
	{	
		pos = busca_seqindex_jogo(ptr, reg.cod);
		//pi(y); printf("%d", pos);
		if(pos == -1)
		{
			apagar(y);
			pi(y); printf("* * * Cadastro de Jogo * * *");
			pi(y); printf("Digite o nome do jogo: ");
			fflush(stdin);
			gets(reg.desc);
			reg.status = 'A';	
			fseek(ptr, 0, 2);	
			fwrite(&reg,sizeof(tpjogo),1,ptr);
			
			fclose(ptr);
			
			insercao_direta_jogo();
			
			ptr = fopen ("jogo.dat","ab+");
		}
		else
		{
			apagar(y);
			pi(y); printf("* * * Cadastro de Jogo * * *");
			pi(y); printf("Codigo de jogo ja cadastrado!!");
			getch();
		}
		
		apagar(y);
		pi(y); printf("* * * Cadastro de Jogo * * *");
		pi(y); printf("Digite o codigo ou '0' p/ sair: ");
		fflush(stdin);
		scanf("%d", &reg.cod);	
			
	}
	//bubblesort_jogo();
	fclose(ptr);		
		
}

void cadpart ()
{
	int y = 3;
	FILE * ptr = fopen("jogadores.dat","ab+");
	
	tppart reg;
	
	int pos;
	
	apagar(y);
	pi(y); printf(" * * * Cadastro de participante * * *");
	pi(y); printf("Digite o codigo do participante: ");
	scanf("%d", &reg.codp);
	
	while(reg.codp != 0)
	{
		pos = busca_binaria_part(ptr, reg.codp);
		
		if (pos == -1)
		{
			
			apagar(y);
			//pi(y); printf("%d", pos);
			pi(y); printf(" * * * Cadastro de participante * * *");
			pi(y); printf("Digite o nome do participante: ");
			fflush(stdin);
			gets(reg.nome);
			reg.status = 'A';
			fseek(ptr, 0, 2);
			fwrite(&reg, sizeof(tppart),1,ptr);
			fclose(ptr);
			ordenacao_direta_part();
			ptr = fopen("jogadores.dat", "ab+"); 
			
		}
		else
		{
			apagar(y);
			pi(y); printf(" * * * Cadastro de participante * * *");
			pi(y); printf("Codigo ja cadastrado!!!");
			getch();
		
		}
		apagar(y);
		pi(y); printf(" * * * Cadastro de participante * * *");
		pi(y); printf("Digite o codigo do participante: ");
		scanf("%d", &reg.codp);
	}
	//bubblesort_part();
	fclose(ptr);
//ordenacao_direta_part();
}

void cadcamp (void)
{
	int y = 3;
	FILE * ptrcamp = fopen ("camp.dat","ab+");
	FILE * ptrjogo = fopen("jogo.dat","rb");
	
	tpcamp regcamp;
	tpjogo regjogo;
	int pos;
	
	apagar(y);
	pi(y); printf(" * * * CADASTRO DE COMPETICAO * * *");
	pi(y); printf("Digite o codigo do campeonato: ");
	scanf("%d", &regcamp.codcamp);
	
	while(regcamp.codcamp != 0)
	{
		pos = busca_exaust_camp(ptrcamp, regcamp.codcamp);
		
		if(pos == -1)
		{
			apagar(y);
			pi(y); printf(" * * * CADASTRO DE COMPETICAO * * *");
			pi(y); printf("Digite o Codigo do Jogo:");
			scanf("%d", &regcamp.codjogo);
										
			if(busca_exaust_jogo(ptrjogo, regcamp.codjogo) > -1)
			{
				
				apagar(y);
				pi(y); printf(" * * * CADASTRO DE COMPETICAO * * *");
				pi(y); printf("Digite o Titulo do Campeonato: ");
				fflush(stdin);
				gets(regcamp.titulo);
				pi(y); printf("Nome do Responsavel: ");
				fflush(stdin);
				gets(regcamp.resp);
				pi(y); printf("Ano da Disputa: ");
				scanf("%d", &regcamp.ano);
				pi(y); printf("Descricao: ");
				fflush(stdin);
				gets(regcamp.descrcamp);
				regcamp.status = 'A';
				
				fseek(ptrcamp, 0, 2);
				fwrite(&regcamp, sizeof(tpcamp),1,ptrcamp);
			
			}
			else
			{
				apagar(y);
				pi(y); printf(" * * * CADASTRO DE COMPETICAO * * *");
				pi(y); printf("Jogo Nao encontrado!!!");
				getch();
			}
		}
		else
		{
			apagar(y);
			pi(y); printf(" * * * CADASTRO DE COMPETICAO * * *");
			pi(y); printf("Codigo ja cadastrado!!");
			getch();
		}
		apagar(y);
		pi(y); printf(" * * * CADASTRO DE COMPETICAO * * *");
		pi(y); printf("Digite o codigo do campeonato: ");
		scanf("%d", &regcamp.codcamp);
	}

	fclose(ptrcamp);
	fclose(ptrjogo);
	bubblesort_camp();	
}


void cadcontrole (void)
{
	int y = 3;
	FILE * ptrcamp = fopen ("camp.dat","rb");
	FILE * ptrcontrol = fopen("control.dat", "ab+");
	FILE * ptrpart = fopen("jogadores.dat", "rb");
	
	//tpcamp regcamp;
	//tppart regpart;
	control regcontrol;
	int pos;
	
	apagar(y);
	pi(y); printf(" * * * CONTROLE DE PARTICIPANTES * * *");
	pi(y); printf("Digite o codigo do campeonato: ");
	scanf("%d", &regcontrol.codcamp);
	
	while(regcontrol.codcamp != 0)
	{
		pos = busca_exaust_camp(ptrcamp, regcontrol.codcamp);
		if(pos > -1)
		{
			apagar(y);
			pi(y); printf(" * * * CONTROLE DE PARTICIPANTES * * *");
			pi(y); printf("Digite o Codigo do Participante:");
			scanf("%d", &regcontrol.codpart);
										
			if(busca_exaust_part(ptrpart, regcontrol.codpart) > -1)
			{
				pos = busca_exaust_control(ptrcontrol, regcontrol.codcamp, regcontrol.codpart);
				
				do
				{
				
					if(pos == -1)
					{
						apagar(y);
						pi(y); printf(" * * * CONTROLE DE PARTICIPANTES * * *");
						pi(y); printf("Digite o Nick: ");
						fflush(stdin);
						gets(regcontrol.nick);
						if(strlen(regcontrol.nick) > 0) 
						{
							regcontrol.status = 'A';
							fseek(ptrcontrol, 0, 2);
							fwrite(&regcontrol, sizeof(control),1,ptrcontrol);
						}
						else
						{
							apagar(y);
							pi(y); printf(" * * * CONTROLE DE PARTICIPANTES * * *");
							pi(y); printf("Por favor insira um nick valido!!!");
							getch();
						}
					}
					else
					{
						apagar(y);
						pi(y); printf(" * * * CONTROLE DE PARTICIPANTES * * *");
						pi(y); printf("Jogador ja cadastrado!!!");
						getch();	
					}
				}while(strlen(regcontrol.nick) == 0);
			}
			else
			{
				apagar(y);
				pi(y); printf(" * * * CONTROLE DE PARTICIPANTES * * *");
				pi(y); printf("Jogador nao encontrado!!!");
				getch();
			}
		}
		else
		{
			apagar(y);
			pi(y); printf(" * * * CONTROLE DE PARTICIPANTES * * *");
			pi(y); printf("Campeonato nao encontrado!!");
			getch();
		}
		apagar(y);
		pi(y); printf(" * * * CONTROLE DE PARTICIPANTES * * *");
		pi(y); printf("Digite o codigo do campeonato: ");
		scanf("%d", &regcontrol.codcamp);
	}	
	
	bubblesort_control();
	fclose(ptrcontrol);
	fclose(ptrcamp);
	fclose(ptrpart);
}
// Buscas
//busca exaustiva
int busca_exaust_jogo (FILE * ptr, int cod)
{
	tpjogo reg;
	
	fseek(ptr, 0 ,0);
	fread(&reg, sizeof(tpjogo), 1, ptr);
	
	while(!feof(ptr) && (reg.cod != cod || reg.status != 'A'))
		fread(&reg, sizeof(tpjogo), 1, ptr);
	
	if(reg.cod == cod && reg.status =='A')
		return ftell(ptr) - sizeof(tpjogo);
	else 
		return -1;
}

int busca_exaust_camp (FILE * ptr, int codcamp)
{
	tpcamp reg;
	fseek(ptr, 0, 0);
	fread(&reg, sizeof(tpcamp), 1, ptr);
	
	while(!feof(ptr) && (reg.codcamp != codcamp || reg.status != 'A'))
		fread(&reg, sizeof(tpcamp), 1, ptr);

	if (reg.codcamp == codcamp && reg.status == 'A')
		return ftell(ptr) - sizeof(tpcamp);
	else
	
	
		return -1;
	
}
//buscas para o relatorio 1-----------------------------
int busca_exaust_rel1 (FILE * ptr, char nome[50])
{
	tppart reg;
	fseek(ptr, 0, 0);
	fread(&reg, sizeof(tppart), 1, ptr);
	
	while(!feof(ptr) && stricmp(nome,reg.nome)!=0)
		fread(&reg, sizeof(tppart), 1, ptr);

	if (stricmp(nome,reg.nome)==0)
		return ftell(ptr) - sizeof(tppart);
	else
		return -1;
	
}
//int busca_exaust (FILE * ptr, int code, int code2)
//{
//	control reg;
//	fseek(ptr, 0, 0);
//	fread(&reg, sizeof(control), 1, ptr);
//	
//	while(!feof(ptr) && (reg.codpart != code || reg.codcamp != code2 || reg.status != 'A'))
//		fread(&reg, sizeof(control), 1, ptr);

//	if (reg.codpart == code && reg.codcamp == code2)
//		return ftell(ptr) - sizeof(control);
//	else
//		return -1;
//	
//}
//------------------------------------------------------
int busca_exaust_part (FILE * ptr, int codp)
{
	tppart reg;
	  
	fseek(ptr, 0 ,0);
	fread(&reg, sizeof(tppart), 1, ptr);  
	
	while(!feof(ptr) && (reg.codp != codp || reg.status != 'A'))
		fread(&reg, sizeof(tppart), 1, ptr);
	
	if(reg.codp == codp && reg.status =='A')
		return ftell(ptr) - sizeof(tppart);
	else 
		return -1;
}

int busca_exaust_control (FILE * ptr, int codcamp, int codpart)
{
	control reg;
	
	fseek(ptr, 0 ,0);
	fread(&reg, sizeof(control), 1, ptr);
	
	while(!feof(ptr) && (reg.codcamp != codcamp || reg.codpart != codpart || reg.status != 'A'))
		fread(&reg, sizeof(control), 1, ptr);
	
	if(reg.codcamp == codcamp && reg.codpart == codpart && reg.status == 'A')
		return ftell(ptr) - sizeof(control);
	else 
		return -1;
}

//busca com sentinela
//int busca_exaustsent_camp (FILE * ptr, int codcamp)
//{
//	FILE * samba = fopen("camp.dat", "rb+");
//	
//	tpcamp reg;
//	
//	reg.codcamp = codcamp;
//	reg.ano = 0;
//	reg.codjogo = 0; 
//	strcpy(reg.descrcamp, "a");
//	strcpy(reg.resp, "a");
//	strcpy(reg.titulo, "a");
//	reg.status = 'I';
//	
//	fseek(samba, 0, 2);
//	fwrite(&reg, sizeof(tpcamp), 1, samba);
//	
//	fclose(samba);
//	
//	fseek(ptr, 0 ,0);
//	fread(&reg,sizeof(tpcamp),1,ptr);
//	while(reg.codcamp != codcamp)
//		fread(&reg, sizeof(tpcamp), 1, ptr);
//	if(reg.codjogo != 0 && reg.status == 'A')
//	{
//		
//		return ftell(ptr) - sizeof(tpcamp);
//	}
//	else
//		return -1;
//	
//}

//busca binaria
int busca_binaria_part(FILE * ptr, int codp)
{
	int y = 3;
	int inicio=0, fim, meio;                  
	
	tppart reg;

	fseek(ptr, 0, 2);
	fim = ftell(ptr) / sizeof(tppart)-1;
	
	meio = fim/2;
	
  	fseek(ptr, meio*sizeof(tppart), 0);
	fread(&reg, sizeof(tppart), 1, ptr);
	
	while(inicio < fim && (reg.status != 'A' || codp != reg.codp))
	{
		pi(y); printf("%d", reg.codp);
		if(codp < reg.codp)
			fim = meio-1;
		else
			inicio = meio+1;
			
		meio = (inicio+fim)/2;
		fseek(ptr, meio*sizeof(tppart), 0);
		fread(&reg, sizeof(tppart), 1, ptr);
	}	
	if(reg.codp == codp && reg.status == 'A')
		return meio*sizeof(tppart);
	else
		return -1;
	
	
}
//busca sequencial indexada
int busca_seqindex_jogo (FILE * ptr, int cod)
{
	tpjogo reg;

	fseek(ptr, 0, 0);
	fread(&reg, sizeof(tpjogo), 1, ptr);
	while(!feof(ptr) && (reg.cod != cod || reg.status != 'A'))
		fread(&reg, sizeof(tpjogo), 1, ptr);

	if(reg.cod == cod && reg.status == 'A')
		return ftell(ptr) - sizeof(tpjogo);
	else
		return -1;

}
 
//exclusao
void exclusao_logi_jogo()
{
	int y = 3;
	char op;
	int pos, i, j;
	tpjogo regjogo;
	tpcamp regcamp;
	control regcontrol;
	
	FILE *ptrjogo = fopen("jogo.dat","rb+");
	FILE *ptrcamp = fopen("camp.dat","rb+");
	FILE *ptrcontrol = fopen("control.dat", "rb+");
	
	if(ptrjogo == NULL && ptrcamp == NULL && ptrcontrol == NULL)
	{
		pi(y); printf("ERRO DE ABERTURA DE ARQUIVO");
	}
	else
	{
		
		apagar(y);
		pi(y); printf(" * * * Excluir Jogo * * *");
		pi(y); printf("Codigo do Jogo:");
		scanf("%d", &regjogo.cod);
				
		while(regjogo.cod !=0)
		{
			pos = busca_exaust_jogo(ptrjogo,regjogo.cod);
		
			if(pos == -1)
			{
				apagar(y);
				pi(y); printf(" * * * Excluir Jogo * * *");
				pi(y); printf("Nao encontrado");
				getch();
			}
			else
			{
				fseek(ptrjogo, pos, 0);
				fread(&regjogo, sizeof(tpjogo), 1, ptrjogo);
				
				apagar(y);
				pi(y); printf(" * * * Excluir Jogo * * *");
				pi(y); printf("DESEJA REALMENTE EXCLUIR?");
				pi(y); printf("S/N");
				op = toupper(getch());
				if(op == 'S')
				{
					 regjogo.status = 'I';
					 
					 fseek(ptrjogo, pos, 0);
					 fwrite(&regjogo, sizeof(tpjogo), 1, ptrjogo);
					
					 fseek(ptrcamp, 0, 0);
					 fread(&regcamp, sizeof(tpcamp), 1, ptrcamp);
					 i=0;
					 while(!feof(ptrcamp))
					 {
					 	if(regcamp.codjogo == regjogo.cod)
					 	{
					 	
						 	regcamp.status = 'I';
						 	fseek(ptrcamp,i*sizeof(tpcamp), 0);
						 	fwrite(&regcamp, sizeof(tpcamp), 1, ptrcamp);
						 	j=0;
						 	fseek(ptrcontrol, j*sizeof(control), 0);
							fread(&regcontrol, sizeof(control), 1, ptrcontrol);
						 	while(!feof(ptrcontrol))
						 	{
						 		
						 		if(regcontrol.codcamp == regcamp.codcamp)
						 		{
						 			
						 			regcontrol.status = 'I';
								 	fseek(ptrcontrol,j*sizeof(control), 0);
								 	fwrite(&regcontrol, sizeof(control), 1, ptrcontrol);
						 		}
						 		j++;
						 		fseek(ptrcontrol, j*sizeof(control), 0);
								fread(&regcontrol, sizeof(control), 1, ptrcontrol);
						 	}
						}
						i++;
						fseek(ptrcamp, i*sizeof(tpcamp), 0);
						fread(&regcamp, sizeof(tpcamp), 1, ptrcamp);
					 }
					 
					apagar(y);
					pi(y); printf(" * * * Excluir Jogo * * *");
					pi(y); printf("Jogo Excluido");
					getch(); 				
				}
						
				
			}
			apagar(y);
			pi(y); printf(" * * * Excluir Jogo * * *");
			pi(y); printf("Codigo do Jogo:");
			scanf("%d", &regjogo.cod);
		}
		fclose(ptrjogo);
		fclose(ptrcamp);
	}
}

void exclusao_logi_part(void)
{
	int y = 3;
	char op;
	int pos, i;
	tppart reg;
	control regcontrol;
	
	FILE *ptr = fopen("jogadores.dat","rb+");
	FILE *ptrcontrol = fopen("control.dat", "rb+");
	
	if(ptr == NULL && ptrcontrol == NULL)
	{
	
		pi(y); printf("ERRO DE ABERTURA DE ARQUIVO");
	
	}
	else
	{
	
		apagar(y);
		pi(y); printf(" * * * Excluir Participante * * *");
		pi(y); printf("Codigo do Participante:");
		scanf("%d", &reg.codp);
				
		while(reg.codp != 0)
		{
			pos = busca_exaust_part(ptr,reg.codp);
			if(pos == -1)
			{
				pi(y); printf(" * * * Excluir Participante * * *");
				pi(y); printf("Nao encontrado");
				getch();
			}
			else
			{
				fseek(ptr, pos, 0);
				fread(&reg, sizeof(tppart), 1, ptr);
				pi(y); printf(" * * * Excluir Participante * * *");
				pi(y); printf("DESEJA REALMENTE EXCLUIR?");
				pi(y); printf("S/N");
				op = toupper(getch());
				if(op == 'S')
				{
					apagar(y);
					reg.status = 'I';
					fseek(ptr, pos, 0);
					fwrite(&reg, sizeof(tppart), 1, ptr);
					
					i=0;
				 	fseek(ptrcontrol, i*sizeof(control), 0);
					fread(&regcontrol, sizeof(control), 1, ptrcontrol);
				 	while(!feof(ptrcontrol))
				 	{
				 		
				 		if(regcontrol.codpart == reg.codp)
				 		{
				 			
				 			regcontrol.status = 'I';
						 	fseek(ptrcontrol,i*sizeof(control), 0);
						 	fwrite(&regcontrol, sizeof(control), 1, ptrcontrol);
				 		}
				 		i++;
				 		fseek(ptrcontrol, i*sizeof(control), 0);
						fread(&regcontrol, sizeof(control), 1, ptrcontrol);
				 	}
				 	apagar(y);
				 	pi(y); printf(" * * * Excluir Participante * * *");
					pi(y); printf("Participante Excluido");
					getch();
						
				}
				
			}
			apagar(y);
			pi(y); printf(" * * * Excluir Participante * * *");
			pi(y); printf("Codigo do Participante:");
			scanf("%d", &reg.codp);
		}
		fclose(ptrcontrol);
		fclose(ptr);
	}
		
}

void exclusao_logi_controle(void)
{
	int y = 3;

	FILE * ptr = fopen("control.dat", "rb+");
	FILE * ptrcamp = fopen("camp.dat", "rb");
	FILE * ptrpart = fopen("jogadores.dat", "rb");

	control regcontrol;
	tpcamp regcamp;
	tppart regpart;
	int pos;
	char op;
	
	apagar(y);
	pi(y); printf(" * * * Excluir Controle * * *");
	pi(y); printf("Digite o codigo do campeonato: ");
	scanf("%d", &regcontrol.codcamp);
	
	while(regcontrol.codcamp != 0)
	{
		apagar(y);
		pi(y); printf(" * * * Excluir Controle * * *");
		pi(y); printf("Digite o Codigo do Participante: ");
		scanf("%d", &regcontrol.codpart);
		
		pos=busca_exaust_control(ptr, regcontrol.codcamp, regcontrol.codpart);
											
		if(pos > -1)
		{
			fseek(ptr, pos, 0);
			fread(&regcontrol, sizeof(control), 1, ptr);
			
			apagar(y);
			pi(y); printf(" * * * Excluir Controle * * *");
			pi(y); printf("DESEJA REALMENTE EXCLUIR?");
			pi(y); printf("S/N");
			op = toupper(getch());
			if(op == 'S')
			{
				apagar(y);
				regcontrol.status = 'I';
				fseek(ptr, pos, 0);
				fwrite(&regcontrol, sizeof(control),1,ptr);
													
			}
		}
		else
		{
			apagar(y);
			pi(y); printf(" * * * Excluir Controle * * *");
			pi(y); printf("Participante nao encontrado!!!");
			getch();
		}
		
		apagar(y);
		pi(y); printf(" * * * Excluir Controle * * *");
		pi(y); printf("Digite o codigo do campeonato: ");
		scanf("%d", &regcontrol.codcamp);
		
	}
				
	fclose(ptr);
	
}

void exclusao_logi_camp (void)
{
	int y = 3;
	char op;
	int pos, i;
	tpcamp regcamp;
	control regcontrol;
	
	FILE *ptrcamp = fopen("camp.dat","rb+");
	FILE *ptrcontrol = fopen("control.dat", "rb+");
	
	if(ptrcamp == NULL && ptrcontrol == NULL)
	{
		apagar(y);
		pi(y); printf(" * * * EXCLUIR COMPETICAO * * *");
		pi(y); printf("ERRO DE ABERTURA DE ARQUIVO");
	}
	else
	{
	
		apagar(y);
		pi(y); printf(" * * * EXCLUIR COMPETICAO * * *");
		pi(y); printf("Codigo do Campeonato:");
		scanf("%d", &regcamp.codcamp);
				
		while(regcamp.codcamp != 0)
		{
			pos = busca_exaust_camp(ptrcamp,regcamp.codcamp);
			if(pos == -1)
			{
				pi(y); printf(" * * * EXCLUIR COMPETICAO * * *");
				pi(y); printf("Nao encontrado");
				getch();
			}
			else
			{
				fseek(ptrcamp, pos, 0);
				fread(&regcamp, sizeof(tpcamp), 1, ptrcamp);
				pi(y); printf(" * * * EXCLUIR COMPETICAO * * *");
				pi(y); printf("DESEJA REALMENTE EXCLUIR?");
				pi(y); printf("S/N");
				op = toupper(getch());
				if(op == 'S')
				{
					apagar(y);
					regcamp.status = 'I';
					fseek(ptrcamp, pos, 0);
					fwrite(&regcamp, sizeof(tpcamp), 1, ptrcamp);
					
					i=0;
				 	fseek(ptrcontrol, i*sizeof(control), 0);
					fread(&regcontrol, sizeof(control), 1, ptrcontrol);
				 	while(!feof(ptrcontrol))
				 	{
				 		
				 		if(regcontrol.codcamp == regcamp.codcamp)
				 		{
				 			
				 			regcontrol.status = 'I';
						 	fseek(ptrcontrol,i*sizeof(control), 0);
						 	fwrite(&regcontrol, sizeof(control), 1, ptrcontrol);
				 		}
				 		i++;
				 		fseek(ptrcontrol, i*sizeof(control), 0);
						fread(&regcontrol, sizeof(control), 1, ptrcontrol);
				 	}
				 	apagar(y);
				 	pi(y); printf(" * * * EXCLUIR COMPETICAO * * *");
					pi(y); printf("Competicao Excluida");
					getch();
						
				}
				
			}
			
			apagar(y);
			pi(y); printf(" * * * EXCLUIR COMPETICAO * * *");
			pi(y); printf("Codigo do Campeonato:");
			scanf("%d", &regcamp.codcamp);
		
			
		}
	
		fclose(ptrcontrol);
		fclose(ptrcamp);
	}
	
	
}
void exclusao_fisica(void)
{
	FILE * ptrjogo = fopen("jogo.dat", "rb");
	FILE * ptrcamp = fopen("camp.dat", "rb");
	FILE * ptrcontrol = fopen("control.dat", "rb");
	FILE * ptrpart = fopen("jogadores.dat", "rb");
	
	FILE * ptraux1 = fopen("aux1.dat", "wb+");
	FILE * ptraux2 = fopen("aux2.dat", "wb+");
	FILE * ptraux3 = fopen("aux3.dat", "wb+");
	FILE * ptraux4 = fopen("aux4.dat", "wb+");
	
	tpcamp regcamp;
	tpjogo regjogo;
	tppart regpart;
	control regcontrol;
	
	fseek(ptrjogo, 0, 0);
	fread(&regjogo, sizeof(tpjogo), 0, ptrjogo);
	
	while(!feof(ptrjogo))
	{
		if(regjogo.status == 'A')
		{
			fseek(ptraux1, 0, 2);
			fwrite(&regjogo, sizeof(tpjogo), 1, ptraux1);
		}
		fread(&regjogo, sizeof(tpjogo), 1, ptrjogo);
			
	}
	
	
	fseek(ptrcamp, 0, 0);
	fread(&regcamp, sizeof(tpcamp), 0, ptrcamp);
	while(!feof(ptrcamp))
	{
		if(regcamp.status == 'A')
		{
			fseek(ptraux2, 0, 2);
			fwrite(&regcamp, sizeof(tpcamp), 1, ptraux2);
		}
		fread(&regcamp, sizeof(tpcamp), 1, ptrcamp);
			
	}
	
	fseek(ptrcontrol, 0, 0);
	fread(&regcontrol, sizeof(control), 0, ptrcontrol);
	while(!feof(ptrcontrol))
	{
		if(regcontrol.status == 'A')
		{
			fseek(ptraux3, 0, 2);
			fwrite(&regcontrol, sizeof(control), 1, ptraux3);
		}
		fread(&regcontrol, sizeof(control), 1, ptrcontrol);
			
	}
	
	fseek(ptrpart, 0, 0);
	fread(&regpart, sizeof(tppart), 0, ptrpart);
	while(!feof(ptrpart))
	{
		if(regpart.status == 'A')
		{
			fseek(ptraux4, 0, 2);
			fwrite(&regpart, sizeof(tppart), 1, ptraux4);
		}
		fread(&regpart, sizeof(tppart), 1, ptrpart);
			
	}
	
	
				
	fclose(ptrjogo);
	fclose(ptrcamp);
	fclose(ptrcontrol);
	fclose(ptrpart);
	remove("jogo.dat");
	remove("camp.dat");
	remove("control.dat");
	remove("jogadores.dat");
	
	fclose(ptraux1);
	fclose(ptraux2);
	fclose(ptraux3);
	fclose(ptraux4);
	rename("aux1.dat", "jogo.dat");
	rename("aux2.dat", "camp.dat");
	rename("aux3.dat", "control.dat");
	rename("aux4.dat", "jogadores.dat");
}

//exclusao fisica camp
void exclusaofisica_camp (void)
{
	FILE * ptrcamp = fopen("camp.dat", "rb");
	FILE * ptrauxcamp = fopen("aux.dat", "wb");

	tpcamp regcamp;
	
	fseek(ptrcamp, 0, 0);
	fread(&regcamp, sizeof(tpcamp), 0, ptrcamp);
	while(!feof(ptrcamp))
	{
		if(regcamp.status == 'A')
		{
			fseek(ptrauxcamp, 0, 2);
			fwrite(&regcamp, sizeof(tpcamp), 1, ptrauxcamp);
		}
		fread(&regcamp, sizeof(tpcamp), 1, ptrcamp);
			
	}
		
	fclose(ptrcamp);
	remove("camp.dat");
	fclose(ptrauxcamp);
	rename("aux.dat", "camp.dat");
			
}
//alteracao
void alterar_jogo (void)
{
	int y = 3;

	char op;
	int pos;
	tpjogo reg;
	
	FILE *ptr = fopen("jogo.dat","rb+");
	
	apagar(y);
	pi(y); printf("Codigo do Jogo:");
	scanf("%d", &reg.cod);
	while(reg.cod != 0)
	{
		
		pos = busca_exaust_jogo(ptr,reg.cod);
		fseek(ptr, pos, 0);
		fread(&reg, sizeof(tpjogo), 1, ptr);
		if(pos == -1)
		{
			pi(y); printf("Nao encontrado");
			getch();
		}
		else
		{
			pi(y); printf("DESEJA REALMENTE ALTERAR?");
			pi(y); printf("S/N");
			op = toupper(getch());
			if(op == 'S')
			{
				apagar(y);
				pi(y); printf("Descricao atual: %s", reg.desc);
				pi(y); printf("Descricao: ");
				fflush(stdin);
				gets(reg.desc);
			}
			fseek(ptr, pos, 0);
			fwrite(&reg, sizeof(tpjogo), 1, ptr);
		}
		apagar(y);
		pi(y); printf("Codigo do Jogo:");
		scanf("%d", &reg.cod);
	}
	fclose(ptr);
}

void alterar_camp (void)
{
	int y = 3;
	char op;
	int pos, aux;
	tpcamp regcamp;
	tpjogo regjogo;
	
	
	FILE *ptrcamp = fopen("camp.dat","rb+");
	FILE *ptrjogo = fopen("jogo.dat","rb");
	
	apagar(y);
	pi(y); printf("***ALTERAR CAMPEONATO***");
	pi(y); printf("Codigo do Campeonato:");
	scanf("%d", &regcamp.codcamp);
	pos = busca_exaust_camp(ptrcamp,regcamp.codcamp);
	if(pos == -1)
	{
		apagar(y);
		pi(y); printf("***ALTERAR CAMPEONATO***");
		pi(y); printf("Nao encontrado!");
		getch();
	}
	else
	{
		fseek(ptrcamp, pos, 0);
		fread(&regcamp, sizeof(tpcamp), 1, ptrcamp);
		pi(y); printf("DESEJA REALMENTE ALTERAR? ");
		pi(y); printf("S/N");
		op = toupper(getch());
		if(op == 'S')
		{
			do
			{
				apagar(y);
				pi(y); printf("***ALTERAR CAMPEONATO***");
				pi(y); printf("[A] Codigo do Tipo de Jogo");
				pi(y); printf("[B] Descricao");
				pi(y); printf("[C] Responsavel");
				pi(y); printf("[D] Titulo");
				op = toupper(getch());
				
				
				switch(op)
				{
					case 'A':
							apagar(y);
							pos = busca_exaust_jogo(ptrjogo, regcamp.codjogo);
							fseek(ptrjogo, pos, 0);
							fread(&regjogo, sizeof(tpjogo), 1, ptrjogo);
							pi(y); printf("***ALTERAR CAMPEONATO***");
							pi(y); printf("Jogo Atual: %s", regjogo.desc);
							pi(y); printf("  Codigo do tipo de Jogo: ");
							scanf("%d", &regcamp.codjogo);
							if(busca_exaust_jogo(ptrjogo, regcamp.codjogo) > -1)
							{
								apagar(y);
								pi(y); printf("***ALTERAR CAMPEONATO***");
								pi(y); printf("Alteracao concluida");
							}
							else
							{
								apagar(y);
								pi(y); printf("***ALTERAR CAMPEONATO***");
								pi(y); printf("Jogo nao existente");
							}
							
							getch();
							break;	
				
					case 'B':
							apagar(y);
							pi(y); printf("***ALTERAR CAMPEONATO***");
							pi(y); printf("  Descricao: ");
							fflush(stdin);
							gets(regcamp.descrcamp);
							break;
							
					case 'C':
							apagar(y);
							pi(y); printf("***ALTERAR CAMPEONATO***");
							pi(y); printf("  Responsavel: ");
							fflush(stdin);
							gets(regcamp.resp);
							break;
							
					case 'D':
							apagar(y);
							pi(y); printf("***ALTERAR CAMPEONATO***");
							pi(y); printf("  Titulo: ");
							fflush(stdin);
							gets(regcamp.titulo);
							break;
						
				}
				
			}while(op != 27);
				
		}
		fseek(ptrcamp, pos, 0);
		fwrite(&regcamp, sizeof(tpcamp), 1, ptrcamp);
		fclose(ptrcamp);
	}
}

void alterar_controle (void)
{
	int y = 3;
	FILE * ptrcamp = fopen ("camp.dat","rb");
	FILE * ptrcontrol = fopen("control.dat", "rb+");
	FILE * ptrpart = fopen("jogadores.dat", "rb");
	
	tpcamp regcamp;
	tppart regpart;
	control regcontrol;
	int pos;
	
	apagar(y);
	pi(y); printf(" * * * ALTERAR CONTROLE * * *");
	pi(y); printf("Digite o codigo do campeonato: ");
	scanf("%d", &regcontrol.codcamp);
	
	while(regcontrol.codcamp != 0)
	{
		pos = busca_exaust_camp(ptrcamp, regcontrol.codcamp);
		if(pos > -1)
		{
			
			apagar(y);
			pi(y); printf(" * * * ALTERAR CONTROLE * * *");
			pi(y); printf("Digite o Codigo do Participante: ");
			scanf("%d", &regcontrol.codpart);
										
			if(busca_exaust_part(ptrpart, regcontrol.codpart) > -1)
			{
				pos = busca_exaust_control(ptrcontrol, regcontrol.codcamp, regcontrol.codpart);
				
				if(pos > -1)
				{
					fread(&regcontrol, sizeof(control), 1, ptrcontrol);
					apagar(y);
					pi(y); printf(" * * * ALTERAR CONTROLE * * *");
					pi(y); printf("Digite o Nick: ");
					fflush(stdin);
					gets(regcontrol.nick);
					fseek(ptrcontrol, 0, 0);
					fwrite(&regcontrol, sizeof(control),1,ptrcontrol);
					apagar(y);
					pi(y); printf(" * * * ALTERAR CONTROLE * * *");
					pi(y); printf("Nick Alterado!");
					getch();
				}
				else
				{
					apagar(y);
					pi(y); printf(" * * * ALTERAR CONTROLE * * *");
					pi(y); printf("Jogador nao cadastrado!!!");
					getch();	
				}
			}
			else
			{
				apagar(y);
				pi(y); printf(" * * * ALTERAR CONTROLE * * *");
				pi(y); printf("Jogador nao encontrado!!!");
				getch();
			}
		}
		else
		{
			apagar(y);
			pi(y); printf(" * * * ALTERAR CONTROLE * * *");
			pi(y); printf("Campeonato nao encontrado!!");
			getch();
		}
		apagar(y);
		pi(y); printf(" * * * ALTERAR CONTROLE * * *");
		pi(y); printf("Digite o codigo do campeonato: ");
		scanf("%d", &regcontrol.codcamp);
	}	
	fclose(ptrcontrol);
	fclose(ptrcamp);
	fclose(ptrpart);
}

void alterar_part (void)
{
	int y = 3;
	char op;
	int pos;
	tpjogo reg;
	
	FILE *ptr = fopen("jogadores.dat","rb+");
	
	apagar(y);
	pi(y); printf("Codigo do Participante:");
	scanf("%d", &reg.cod);
	pos = busca_exaust_part(ptr,reg.cod);
	fseek(ptr, pos, 0);
	fread(&reg, sizeof(tppart), 1, ptr);
	if(pos == -1)
	{
		pi(y); printf("Nao encontrado");
		getch();
	}
	else
	{
		pi(y); printf("DESEJA REALMENTE ALTERAR?");
		pi(y); printf("S/N");
		op = toupper(getch());
		if(op == 'S')
		{
			apagar(y);
			pi(y); printf("Descricao atual: %s", reg.desc);
			pi(y); printf("Descricao: ");
			fflush(stdin);
			gets(reg.desc);
				
		
				
		}
		fseek(ptr, pos, 0);
		fwrite(&reg, sizeof(tppart), 1, ptr);
		fclose(ptr);
	}
}

//ordenacoes
//bubble sort
void bubblesort_jogo (void)
{
	int d = 3;
	FILE * ptr = fopen ("jogo.dat","rb+");
	
	int qtd, x, y;
	tpjogo rega, regb;
	
	if (ptr == NULL)
	{
		pi(d); printf("Erro ao abrir um arquivo!!");
	}
	else
	{
		fseek(ptr,0,2);
		qtd = ftell(ptr)/sizeof(tpjogo);
		for(x=0; x < qtd-1 ; x++)
			for(y = x+1; y<qtd; y++)
			{
				fseek(ptr, x*sizeof(tpjogo),0);
				fread(&rega,sizeof(tpjogo),1,ptr);
				
				fseek(ptr, y*sizeof(tpjogo),0);
				fread(&regb, sizeof(tpjogo),1,ptr);
				
				if(rega.cod > regb.cod)
				{
					fseek(ptr, x*sizeof(tpjogo),0);
					fwrite(&regb, sizeof(tpjogo),1,ptr);
					
					fseek(ptr, y*sizeof(tpjogo),0);
					fwrite(&rega, sizeof(tpjogo),1,ptr);
					
				}
			}

		
		fclose(ptr);
		apagar(d);
		
	}
}

void bubblesort_part (void)
{
	FILE * ptr = fopen("jogadores.dat","rb+");
	
	int x,y,qtd, d=3;
	tppart reg1, reg2;
	
	if(ptr ==NULL)
	{
		pi(d); printf("ERRO AO ABRIR O ARQUIVO");
	}
	else
	{
		fseek(ptr,0,2);
		qtd = ftell(ptr)/sizeof(tpjogo);

		
		for(x=0; x < qtd-1 ; x++)
			for(y = x+1; y<qtd; y++)
			{
				fseek(ptr, x*sizeof(tppart),0);
				fread(&reg1,sizeof(tppart),1,ptr);
				
				fseek(ptr, y*sizeof(tppart),0);
				fread(&reg2, sizeof(tppart),1,ptr);
				
				if(reg1.codp > reg2.codp)
				{
					fseek(ptr, x*sizeof(tppart),0);
					fwrite(&reg2, sizeof(tppart),1,ptr);
					
					fseek(ptr, y*sizeof(tppart),0);
					fwrite(&reg1, sizeof(tppart),1,ptr);
					
				}
			}

		fclose(ptr);
		
			
			
	}
}

void bubblesort_camp(void)
{
	FILE * ptr = fopen ("camp.dat","rb+");
	
	int x,y,qtd,d=3;
	tpcamp reg1, reg2;
	
	if(ptr == NULL)
	{
		pi(d); printf("ERRO AO ABRIR O ARQUIVO");
	}
	else
	{
		fseek(ptr,0,2);
		qtd = ftell(ptr)/sizeof(tpcamp);
	
		for (x = 0; x < qtd -1;x++)
			for(y = x+1; y<qtd; y++)
			{
				fseek(ptr, x*sizeof(tpcamp),0);
				fread(&reg1,sizeof(tpcamp),1,ptr);
				
				fseek(ptr, y*sizeof(tpcamp),0);
				fread(&reg2, sizeof(tpcamp),1,ptr);
				
				if(reg1.codcamp > reg2.codcamp)
				{
					fseek(ptr, x*sizeof(tpcamp),0);
					fwrite(&reg2, sizeof(tpcamp),1,ptr);
					
					fseek(ptr, y*sizeof(tpcamp),0);
					fwrite(&reg1, sizeof(tpcamp),1,ptr);
					
				}
			}
	}
}

void bubblesort_part_nome(FILE * ptr)
{
		
	int x,y,qtd,d=3;
	tppart reg1, reg2;
	
	if(ptr == NULL)
	{
		pi(d); printf("ERRO AO ABRIR O ARQUIVO");
	}
	else
	{
		fseek(ptr,0,2);
		qtd = ftell(ptr)/sizeof(tppart);
		
		
		for(x=0; x < qtd-1 ; x++)
			for(y = x+1; y<qtd; y++)
			{
				fseek(ptr, x*sizeof(tppart),0);
				fread(&reg1,sizeof(tppart),1,ptr);
				
				fseek(ptr, y*sizeof(tppart),0);
				fread(&reg2, sizeof(tppart),1,ptr);
				
				if(stricmp(reg1.nome,reg2.nome) > 0)
				{
					fseek(ptr, x*sizeof(tppart),0);
					fwrite(&reg2, sizeof(tppart),1,ptr);
					
					fseek(ptr, y*sizeof(tppart),0);
					fwrite(&reg1, sizeof(tppart),1,ptr);
					
				}
			}
			
		
	}
}

void bubblesort_control (void)
{
	FILE * ptr = fopen ("control.dat","rb+");
	
	int x,y,qtd,d=3;
	control reg1, reg2;
	
	if(ptr == NULL)
	{
		pi(y); printf("ERRO AO ABRIR O ARQUIVO");
	}
	else
	{
		fseek(ptr,0,2);
		qtd = ftell(ptr)/sizeof(control);

		for(y = x+1; y<qtd; y++)
			for(y = x+1; y<qtd; y++)
			{
				fseek(ptr, x*sizeof(control),0);
				fread(&reg1,sizeof(control),1,ptr);
				
				fseek(ptr, y*sizeof(control),0);
				fread(&reg2, sizeof(control),1,ptr);
				
				if(reg1.codcamp > reg2.codcamp)
				{
					fseek(ptr, x*sizeof(control),0);
					fwrite(&reg2, sizeof(control),1,ptr);
					
					fseek(ptr, y*sizeof(control),0);
					fwrite(&reg1, sizeof(control),1,ptr);
					
				}
			}


	}
	
}
//insercao direta
void insercao_direta_jogo(void)
{
	FILE* ptr = fopen("jogo.dat", "rb+");

	tpjogo reg, reg2;
	int i;

	fseek(ptr, 0, 2);
	i = ftell(ptr) / sizeof(tpjogo)-1;
	if(i >0)
	{
		fseek(ptr,(i-1)*sizeof(tpjogo),0);
		fread(&reg,sizeof(tpjogo),1,ptr);
		fread(&reg2,sizeof(tpjogo),1,ptr);
	
		if(reg.cod > reg2.cod)
		{
			fseek(ptr,(i-1)*sizeof(tpjogo),0);
			fwrite(&reg2,sizeof(tpjogo),1,ptr);
			fseek(ptr,i*sizeof(tpjogo),0);
			fwrite(&reg,sizeof(tpjogo),1,ptr);
		}
		i--;
	}
	
	while(i > 0 && reg.cod > reg2.cod)
	{
		fseek(ptr,(i-1)*sizeof(tpjogo),0);
		fread(&reg,sizeof(tpjogo),1,ptr);
		fread(&reg2,sizeof(tpjogo),1,ptr);
		if(reg.cod > reg2.cod)
		{
			fseek(ptr,(i-1)*sizeof(tpjogo),0);
			fwrite(&reg2,sizeof(tpjogo),1,ptr);
			fseek(ptr,i*sizeof(tpjogo),0);
			fwrite(&reg,sizeof(tpjogo),1,ptr);
		}
		i--;
	}
	fclose(ptr);
}
//ordenação direta (selection sort)
int  PosMaior (FILE * ptr, int TL)
{
	int posMaior,maior,i=0;
	tpjogo reg;
	
	fseek(ptr,0,0);
	posMaior = 0;
	maior = 0;
	
	fread(&reg,sizeof(tpjogo),1,ptr);
	
	while(i<TL)
	{
		if(maior < reg.cod)
		{
			maior = reg.cod;
			posMaior = ftell(ptr)/sizeof(tpjogo) - 1;
		}
		fread(&reg, sizeof(tpjogo),1,ptr);
		i++;
	}
	 return posMaior;
}
void ordenacao_direta_part(void)
{
	FILE * ptr = fopen("jogadores.dat","rb+");
	tpjogo reg,maior;
	int posMaior1, tl, i=0;
	
	fseek(ptr,0,2);
	tl=ftell(ptr)/sizeof(tpjogo);
	
	while(i<tl)
	{
		posMaior1 = PosMaior (ptr,tl);
		if(posMaior1 < tl)
		{
			//
			fseek(ptr,posMaior1*sizeof(tpjogo),0);
			fread(&maior,sizeof(tpjogo),1,ptr);
			//
			fseek(ptr,(tl-1)*sizeof(tpjogo),0);
			fread(&reg,sizeof(tpjogo),1,ptr);
			
			fseek(ptr,posMaior1*sizeof(tpjogo),0);
			fwrite(&reg,sizeof(tpjogo),1,ptr);
			
			fseek(ptr,(tl-1)*sizeof(tpjogo),0);
			fwrite(&maior,sizeof(tpjogo),1,ptr);
		}
		tl--;
	}
	fclose(ptr);
}
//relatorios
void reljogo(void)
{
	int y = 3;
	FILE * ptr = fopen("jogo.dat", "rb");
	
	tpjogo reg;
	
	if (ptr == NULL){
		
		apagar(y);
		pi(y); printf("ERRO AO ABRIR O ARQUIVO");
	}
	else
	{
		apagar(y);
		pi(y); printf("* * * CONTEUDO DO JOGO * * *");
		fread(&reg, sizeof(tpjogo), 1,ptr);
		
		while(!feof(ptr))
		{
			if(reg.status == 'A')
			{
				pi(y); printf("codigo: %d",reg.cod);
				pi(y); printf("nome : %s",reg.desc);
				
			}
			fread(&reg, sizeof(tpjogo), 1, ptr);
		}
		fclose(ptr);
	}
	getch();
}

void relpart(void)
{
	FILE * ptr = fopen("jogadores.dat","rb");
	int y = 3;
	
	tppart reg;
	
	if (ptr == NULL)
	{
		pi(y); printf("ERRO AO ABRIR O ARQUIVO");
	}
	else
		{
			apagar(y);
			pi(y); printf("* * * CONTEUDO DOS PARTICIPANTES * * *");
			fread(&reg, sizeof(tppart),1,ptr);
			
			while (!feof(ptr))
			{
				if(reg.status == 'A')
				{
					pi(y); printf("codigo: %d",reg.codp);
					pi(y); printf("nome: %s: ",reg.nome);
				}
				fread(&reg, sizeof(tppart), 1,ptr);
			}
			fclose(ptr);
		}
	getch();
}

void relcontrol(void)
{
	FILE * ptr = fopen("control.dat", "rb");
	int y = 3;
	control reg;
	
	if (ptr == NULL){
		apagar(y);
		pi(y); printf("ERRO AO ABRIR O ARQUIVO");
	}
	else
	{
		apagar(y);
		pi(y); printf("* * * CONTEUDO DO CONTROLE * * *");
		fread(&reg, sizeof(control), 1,ptr);
		
		while(!feof(ptr))
		{
			if(reg.status == 'A')
			{
				pi(y); printf("codigo do camp: %d",reg.codcamp);
				pi(y); printf("codigo do participante: %d",reg.codpart);
				pi(y); printf("nick: %s",reg.nick);
			}
			fread(&reg, sizeof(control), 1, ptr);
		}
		fclose(ptr);
	}
	getch();
}

void relcamp (void)
{
	FILE * ptr = fopen("camp.dat", "rb");
		int y = 3;
		tpcamp reg;
		
		if (ptr == NULL){
			
			apagar(y);
			pi(y); printf("ERRO AO ABRIR O ARQUIVO");
		}
		else
		{
			apagar(y);
			pi(y); printf("* * * CONTEUDO DO CAMPEONATO * * *");
			fread(&reg, sizeof(tpcamp), 1,ptr);
			
			while(!feof(ptr))
			{
				if(reg.status == 'A')	
				{

					pi(y); printf("codigo do camp: %d ",reg.codcamp);
					pi(y); printf("titulo: %s",reg.titulo);
					pi(y); printf("resp: %s",reg.resp);
					pi(y); printf("ano: %d",reg.ano);
					pi(y); printf("descricao: %d",reg.descrcamp);
				}
					
				fread(&reg, sizeof(tpcamp), 1, ptr);
			}
			fclose(ptr);
		}
		getch();
}
//relatorios especificos
void relatorio1 (void)
{
	FILE * ptrcamp = fopen("camp.dat","rb");
	FILE * ptrjogo = fopen("jogo.dat","rb");
	FILE * ptrpart = fopen("jogadores.dat","rb");
	FILE * ptrcontrol = fopen("control.dat","rb");
	int y = 3;
	
	tppart regpart;
	tpcamp regcamp;
	tpjogo regjogo;
	control regcontrol;

	int pos, cont, soma =0;

	char nome[50];

	apagar(y);
	pi(y); printf("* * * RELATORIO DE COMPETIDOR * * *");
	pi(y); printf("Digite o nome do jogador: ");
	fflush(stdin);
	gets(nome);
	
	pos =  busca_exaust_rel1(ptrpart, nome);

	if(pos != -1)
	{
		apagar(y);
		fseek(ptrpart,pos,0);
		fread(&regpart,sizeof(tppart),1,ptrpart);
		pi(y); printf("Jogador selecionado: %s",regpart.nome);
		pi(y); printf("---------------------------------------------------------------------");

		fseek(ptrjogo,0,0);
		fread(&regjogo,sizeof(tpjogo),1,ptrjogo);
		while(!feof(ptrjogo))
		{
			cont = 0;
			fseek(ptrcamp,0,0);
			fread(&regcamp,sizeof(tpcamp),1,ptrcamp);
			while(!feof(ptrcamp))
			{
				if(regjogo.cod == regcamp.codjogo)
				{
					pos = busca_exaust_control(ptrcontrol,regcamp.codcamp,regpart.codp);

					if(pos != -1)
					{
						fseek(ptrcontrol,pos,0);
						fread(&regcontrol,sizeof(control),1,ptrcontrol);

						if(cont == 0)
						{
							pi(y); printf("-> Tipo de jogo: %s",regjogo.desc);
							
						}

						pi(y); printf("%s - Responsavel: %s(%d) - Nick: %s",regcamp.titulo,regcamp.resp,regcamp.ano,regcontrol.nick);
						cont++;
					}
				}	
				fread(&regcamp, sizeof(tpcamp),1,ptrcamp);
			}
			if(cont > 0)
			{
				pi(y); printf("total de campeonatos: %d",cont);
				pi(y); printf("-------------------------------------------------------------------------");
			}
			soma+=cont;

			fread(&regjogo, sizeof(tpjogo),1,ptrjogo);
		}
		pi(y); printf("Total de Campeonatos do Participante: %d",soma);
		getch();
	}
	else
	{
		apagar(y);
		pi(y); printf("* * * RELATORIO DE CAMPEONATOS * * *");
		pi(y); printf("Jogador nao encontrado");
		getch();
	}

fclose(ptrjogo);
fclose(ptrpart);
fclose(ptrcamp);
fclose(ptrcontrol);
}

void relatorio2(void)
{
	FILE * ptrjogo = fopen("jogo.dat", "rb");
	FILE * ptrpart = fopen("jogadores.dat", "rb+");
	FILE * ptrcamp = fopen("camp.dat", "rb");
	FILE * ptrcontrol = fopen("control.dat", "rb");
	int y = 3;
	tpjogo regjogo;
	tppart regpart;
	tpcamp	regcamp;
	control regcontrol;
	
	int pos, auxcod;
	
	apagar(y);
	pi(y); printf("* * * RELATORIO DE CAMPEONATO * * *");
	pi(y); printf("Digite o codigo do campeonato: ");
	scanf("%d", &auxcod);
	
	while(auxcod != 0)
	{
		pos = busca_exaust_camp(ptrcamp, auxcod);
		
		if(pos > -1)
		{
			fseek(ptrcamp, pos, 0);
			fread(&regcamp, sizeof(tpcamp), 1, ptrcamp);
			pi(y); printf("%s", regcamp.titulo);
			
			pos = busca_seqindex_jogo(ptrjogo, regcamp.codjogo);
			fseek(ptrjogo, pos, 0);	
			fread(&regjogo, sizeof(tpjogo), 1, ptrjogo);
			pi(y); printf("Responsavel: %s - %d - %s",regcamp.resp, regcamp.ano, regjogo.desc);
			pi(y); printf("");
			pi(y); printf("Descricao:");
			pi(y); printf("");
			pi(y); printf("%s", regcamp.descrcamp);
			pi(y); printf("");
			pi(y); printf("Participantes:");
			pi(y); printf("");
			bubblesort_part_nome(ptrpart);
			fseek(ptrpart, 0 , 0);
			fread(&regpart, sizeof(tppart), 1, ptrpart);
			while(!feof(ptrpart))
			{
				pos = busca_exaust_control(ptrcontrol, regcamp.codcamp, regpart.codp);
				
				if(pos > -1)
				{
					pi(y); printf("-%s", regpart.nome);
					pi(y); printf("");
					
				}
				fread(&regpart, sizeof(tppart),1 , ptrpart);
			}
			getch();	
			
		}
	
		apagar(y);
		pi(y); printf("* * * RELATORIO DE CAMPEONATO * * *");
		pi(y); printf("Digite o codigo do campeonato: ");
		scanf("%d", &auxcod);	
	}
	
	fclose(ptrjogo);
	fclose(ptrpart);
	fclose(ptrcamp);
	fclose(ptrcontrol);
}

//consultar
void consulta_jogo(void)
{
	tpjogo reg;
	int pos;
	int y = 3;
	FILE * ptr = fopen("jogo.dat","rb");
	apagar(y);
	pi(y); printf("* * * CONSULTAR JOGOS * * *");
	
	if(ptr == NULL)
	{
		pi(y); printf("ERRO DE ABERTURA");
	}
	else
	{	
		pi(y); printf("Digite o codigo ou [0] p/sair: ");
		scanf("%d", &reg.cod);
		
		while (reg.cod != 0)
		{
			pos = busca_exaust_jogo(ptr, reg.cod);
			
			if(pos == -1)
			{
			
				apagar(y);
				pi(y); printf("* * * CONSULTAR JOGOS * * *");
				pi(y); printf("NOME NAO CADASTRADO");
				getch();
			}
			else
			{
				apagar(y);
				pi(y); printf("* * * CONSULTAR JOGOS * * *");
				pi(y); printf("* * * DETALHES * * *");
	            fseek(ptr, pos, 0);
	            fread(&reg, sizeof(tpjogo),1,ptr);
	            pi(y); printf("codigo do jogo: %d",reg.cod);
	            pi(y); printf("nome do jogo: %s",reg.desc);
	            pi(y); printf("status do jogo: %c",reg.status);
	            getch();
            }
            apagar(y);
            pi(y); printf("* * * CONSULTAR JOGOS * * *");
            pi(y); printf("Digite o codigo ou [0] p/sair: ");
            scanf("%d", &reg.cod);
		}	
		fclose(ptr);
	}
}

void consulta_part(void)
{
	tppart reg;
	int pos;
	int y = 3;
	FILE * ptr = fopen("jogadores.dat","rb");
	apagar(y);
	pi(y); printf("* * * CONSULTAR PARTICIPANTES * * *");
	
	if(ptr == NULL)
	{
		pi(y); printf("ERRO DE ABERTURA");
	}
	else
	{	
		pi(y); printf("Digite o codigo: ");
		scanf("%d", &reg.codp);
		
		while (reg.codp != 0)
		{
			pos = busca_exaust_part(ptr, reg.codp);
			
			if(pos == -1)
			{
			
				apagar(y);
				pi(y); printf("* * * CONSULTAR PARTICIPANTES * * *");
				pi(y); printf("NOME NAO CADASTRADO");
			}
			else
			{ 
				apagar(y);
				pi(y); printf("* * * CONSULTAR PARTICIPANTES * * *");
				pi(y); printf("* * * DETALHES * * *");
			    fseek(ptr, pos, 0);
			    fread(&reg, sizeof(tppart),1,ptr);
			    pi(y); printf("codigo do participante: %d",reg.codp);
			    pi(y); printf("nome do participante: %s",reg.nome);
			    //pi(y); printf("status do participante: %c",reg.status);
			    getch();
			}
			apagar(y);
			pi(y); printf("* * * CONSULTAR PARTICIPANTES * * *");
            pi(y); printf("Digite o codigo ou [0] p/sair: ");
            scanf("%d", &reg.codp);
		}
		
		fclose(ptr);
	}
}

void consulta_camp(void)
{
	tpcamp reg;
	int pos;
	int y = 3;
	FILE * ptr = fopen("camp.dat","rb");
	
	apagar(y);
	pi(y); printf("* * * CONSULTAR CAMPEONATOS * * *");
	
	if(ptr == NULL)
	{
		apagar(y);
		pi(y); printf("ERRO DE ABERTURA");
	}
	else
	{	
		apagar(y);
		pi(y); printf("* * * CONSULTAR CAMPEONATOS * * *");
		pi(y); printf("Digite o codigo: ");
		scanf("%d", &reg.codcamp);
		
		while (reg.codcamp != 0)
		{
			pos = busca_exaust_camp(ptr, reg.codcamp);
//			fclose(ptr);
//			exclusaofisica_camp();
//			ptr = fopen("camp.dat", "rb");
						
			if(pos == -1)
			{
				pi(y); printf("NOME NAO CADASTRADO");}
			else
			{
				apagar(y);
				pi(y); printf("* * * CONSULTAR CAMPEONATOS * * *");
				pi(y); printf("* * * DETALHES * * *");
				fseek(ptr, pos, 0);
				fread(&reg, sizeof(tpcamp),1,ptr);
				pi(y); printf("codigo do camp: %d",reg.codcamp);
				pi(y); printf("descricao do camp: %s",reg.descrcamp);
				pi(y); printf("titulo do camp: %s",reg.titulo);
				pi(y); printf("responsavel do camp: %s",reg.resp);
				pi(y); printf("ano do campeonato: %d",reg.ano);
				pi(y); printf("codigo do jogo: %d", reg.codjogo);     
				getch();
            }
            pi(y); printf("* * * CONSULTAR CAMPEONATOS * * *");
            pi(y); printf("Digite o codigo ou [0] p/sair: ");
            scanf("%d", &reg.codcamp);
		}
		
		fclose(ptr);
	}

}

void consulta_control(void)
{
	FILE * ptrcontrol = fopen("control.dat", "rb");
	int y = 3;
	control regcontrol;

	int pos;
		
	apagar(y);
	pi(y); printf("* * * CONSULTAR CONTROLE * * *");
	
	if(ptrcontrol == NULL)
		{
		pi(y); printf("ERRO DE ABERTURA");}
	else
	{	
		apagar(y);
		pi(y); printf("* * * CONSULTAR CONTROLE * * *");
		pi(y); printf("Digite o codigo do campeonato: ");
		scanf("%d", &regcontrol.codcamp);
		
		while (regcontrol.codcamp != 0)
		{
			apagar(y);
			pi(y); printf("* * * CONSULTAR CONTROLE * * *");
			pi(y); printf("Digite o codigo do participante: ");
			scanf("%d", &regcontrol.codpart);
			
			pos = busca_exaust_control(ptrcontrol, regcontrol.codcamp, regcontrol.codpart);
			
			if(pos == -1)
			{
				apagar(y);
				pi(y); printf("* * * CONSULTAR CONTROLE * * *");
				pi(y); printf("NOME NAO CADASTRADO");
			}
			else
			{
				  apagar(y);
				  pi(y); printf("* * * CONSULTAR CONTROLE * * *");
		          pi(y); printf("* * * DETALHES * * *");
		          fseek(ptrcontrol, pos, 0);
		          fread(&regcontrol, sizeof(control),1,ptrcontrol);
		          pi(y); printf("codigo do campeonato: %d",regcontrol.codcamp);
		          pi(y); printf("codigo do participante: %d",regcontrol.codpart);
		          pi(y); printf("nick do jogador: %s",regcontrol.nick);
		          getch();
            }
            pi(y); printf("* * * CONSULTAR CONTROLE * * *");
            pi(y); printf("Digite o codigo do campeonato ou [0] p/sair: ");
            scanf("%d", &regcontrol.codcamp);
		}
		fclose(ptrcontrol);
	}
}


int main (void)
{
	char op;
	int y=5;
	FILE * ptr;
	moldura();
	apagar(y);
	op = menu();
	inicializar();
	
	
	do
	{
		switch(op)
		{
			case 'A':
			fflush(stdin); 
			op = menucad(); 
			
	 		switch(op)
			{
				
				case 'A':
				cadjogo();
				break;
				
				case 'B':
				cadpart();
				break;
				
				case 'C':
				cadcamp();
				break;
				
				case 'D':
				cadcontrole();
				break;
			}
			break;	
		 		
			case 'B':
			fflush(stdin);
			op = menurel();
			
			switch(op)
			{
				case 'A':
				reljogo();
				break;
				
				case 'B':
				relpart();
				break;
				
				case 'C':
				relcamp();
				break;
				
				case 'D':
				relcontrol();
				break;
				
				case 'E':
				relatorio1();
				break;
				
				case 'F':
				relatorio2();
				break;
			}
			break;
			
			case 'C':
			fflush(stdin);	
			op = menualt();

			switch(op)
			{
				case 'A':
				alterar_jogo();
				break;
				
				case 'B':
				alterar_part();
				break;
								
				case 'C':
				alterar_camp();
				break;
				
				case 'D':
				alterar_controle();
				break;
			}
			break;
			
			case 'D':
			fflush(stdin);
			op = menuexcl();
			
			switch(op)
			{
				case 'A':
				exclusao_logi_jogo();
				break;
	
				case 'B':
				exclusao_logi_part();
				break;
				
				case 'C':
				exclusao_logi_camp();
				break;
				
				case 'D':	
				exclusao_logi_controle();
				break;
					
			}
			break;
			
			case 'E':
			fflush(stdin);
			op = menuconsul();
			
			switch(op)
			{
				case 'A':
				consulta_jogo();
				break;
				
				case 'B':
				consulta_part();
				break;
				
				case 'C':
				consulta_camp();
				break;
				
				case 'D':
				consulta_control();
				break;
			}
			break;
			
			case 'F':
				inserir();
				break;
		}
		op = menu(); 
	}while(op != 27);
	
	exclusao_fisica();
	return 0;
}

void inicializar()
{
	FILE * ptrjogo = fopen("jogo.dat", "ab+");
	FILE * ptrcontrol = fopen("control.dat", "ab+");
	FILE * ptrpart = fopen("jogadores.dat", "ab+");
	FILE * ptrcamp = fopen("camp.dat", "ab+");
	
	fclose(ptrjogo);
	fclose(ptrpart);
	fclose(ptrcamp);
	fclose(ptrcontrol);
	
}

void moldura(void)
{
	int i;
	textcolor(15);
	for(i=4;i<4+113;i++)
	{
		gotoxy(i,2); printf("%c",205);
		gotoxy(i,2+27); printf("%c",205);
	}
	
	for(i=2;i<2+27;i++)
	{
		gotoxy(4,i); printf("%c",186);
		gotoxy(4+113,i); printf("%c",186);
	}
	
	gotoxy(4,2); printf("%c",201);
	gotoxy(4+113,2); printf("%c",187);
	gotoxy(4,2+27); printf("%c",200);
	gotoxy(4+113,2+27); printf("%c",188);
}

void pi(int &y)
{
	gotoxy(6,y);
	y++;
}

void apagar(int &y)
{
	for(y=3;y<29;y++)
	{
		gotoxy(6,y);
		printf("                                                                                                              ");
	}
	y = 3;
}

void inserir(void)
{
	FILE *ptr = fopen("jogo.dat","wb");
	
	tpjogo regJogo;
	tppart regPart;
	tpcamp regCamp;
	control regCont;
	
	regJogo.cod = 1;
	strcpy(regJogo.desc, "League of Legends");
	regJogo.status = 'A';
	fwrite(&regJogo,sizeof(tpjogo),1,ptr);
	regJogo.cod = 2;
	strcpy(regJogo.desc, "Fortnite");
	regJogo.status = 'A';
	fwrite(&regJogo,sizeof(tpjogo),1,ptr);
	regJogo.cod = 3;
	strcpy(regJogo.desc, "Mortal Kombat");
	regJogo.status = 'A';
	fwrite(&regJogo,sizeof(tpjogo),1,ptr);
	regJogo.cod = 4;
	strcpy(regJogo.desc, "CS:GO");
	regJogo.status = 'A';
	fwrite(&regJogo,sizeof(tpjogo),1,ptr);
	
	fclose(ptr);
	ptr = fopen("jogadores.dat","wb");
	
	regPart.codp = 1;
	strcpy(regPart.nome, "Marcelo “coldzera” David");
	regPart.status = 'A';
	fwrite(&regPart,sizeof(tppart),1,ptr);
	regPart.codp = 2;
	strcpy(regPart.nome, "Olof “olofmeister” Kajbjer");
	regPart.status = 'A';
	fwrite(&regPart,sizeof(tppart),1,ptr);
	regPart.codp = 3;
	strcpy(regPart.nome, "Ladislav “GuardiaN” Kovács");
	regPart.status = 'A';
	fwrite(&regPart,sizeof(tppart),1,ptr);
	regPart.codp = 4;
	strcpy(regPart.nome, "Nicolai “dev1ce” Reedtz");
	regPart.status = 'A';
	fwrite(&regPart,sizeof(tppart),1,ptr);
	regPart.codp = 5;
	strcpy(regPart.nome, "Santorin");
	regPart.status = 'A';
	fwrite(&regPart,sizeof(tppart),1,ptr);
	regPart.codp = 6;
	strcpy(regPart.nome, "SGD Sty1eee");
	regPart.status = 'A';
	fwrite(&regPart,sizeof(tppart),1,ptr);
	regPart.codp = 7;
	strcpy(regPart.nome, "Solokill3hk");
	regPart.status = 'A';
	fwrite(&regPart,sizeof(tppart),1,ptr);
	regPart.codp = 8;
	strcpy(regPart.nome, "JUGKlNG");
	regPart.status = 'A';
	fwrite(&regPart,sizeof(tppart),1,ptr);
	regPart.codp = 9;
	strcpy(regPart.nome, "Kyle Giersdorf (Bugha)");
	regPart.status = 'A';
	fwrite(&regPart,sizeof(tppart),1,ptr);
	
	fclose(ptr);
	ptr = fopen("camp.dat","wb");
	
	regCamp.codcamp = 1;
	strcpy(regCamp.titulo,"Mundial de LoL");
	strcpy(regCamp.resp,"Riot Games");
	regCamp.ano = 2019;
	regCamp.codjogo = 1;
	strcpy(regCamp.descrcamp, "O torneio mais importante do MOBA da Riot Games...");
	regCamp.status = 'A';
	fwrite(&regCamp,sizeof(tpcamp),1,ptr);
	
	regCamp.codcamp = 2;
	strcpy(regCamp.titulo,"Copa do mundo de Fortnite");
	strcpy(regCamp.resp,"Epic Games");
	regCamp.ano = 2019;
	regCamp.codjogo = 2;
	strcpy(regCamp.descrcamp, "A jornada para a Fortnite World Cup comeca com dez qualificatorias semanais...");
	regCamp.status = 'A';
	fwrite(&regCamp,sizeof(tpcamp),1,ptr);
	
	regCamp.codcamp = 3;
	strcpy(regCamp.titulo,"Campeonato Brasileiro de CS:GO");
	strcpy(regCamp.resp,"Valve");
	regCamp.ano = 2020;
	regCamp.codjogo = 4;
	strcpy(regCamp.descrcamp, "Uma nova competicao de Counter-Strike: Global Offensive foi anunciada no Brasil...");
	regCamp.status = 'A';
	fwrite(&regCamp,sizeof(tpcamp),1,ptr);
	
	fclose(ptr);
	ptr = fopen("control.dat","wb");
	
	regCont.codcamp = 3;
	regCont.codpart = 2;
	strcpy(regCont.nick,"SG BOOTCAMP");
	regCont.status = 'A';
	fwrite(&regCont,sizeof(control),1,ptr);
	
	regCont.codcamp = 3;
	regCont.codpart = 1;
	strcpy(regCont.nick,"PERAQTOCOSTA");
	regCont.status = 'A';
	fwrite(&regCont,sizeof(control),1,ptr);
	
	regCont.codcamp = 1;
	regCont.codpart = 1;
	strcpy(regCont.nick,"KT ROLSTER");
	regCont.status = 'A';
	fwrite(&regCont,sizeof(control),1,ptr);
	
	regCont.codcamp = 1;
	regCont.codpart = 2;
	strcpy(regCont.nick,"FREECS");
	regCont.status = 'A';
	fwrite(&regCont,sizeof(control),1,ptr);
	
	regCont.codcamp = 3;
	regCont.codpart = 4;
	strcpy(regCont.nick,"INSTANTK");
	regCont.status = 'A';
	fwrite(&regCont,sizeof(control),1,ptr);
	
	regCont.codcamp = 1;
	regCont.codpart = 9;
	strcpy(regCont.nick,"ROYAL NEVER");
	regCont.status = 'A';
	fwrite(&regCont,sizeof(control),1,ptr);
	
	regCont.codcamp = 1;
	regCont.codpart = 3;
	strcpy(regCont.nick,"GEN.G");
	regCont.status = 'A';
	fwrite(&regCont,sizeof(control),1,ptr);
	
	regCont.codcamp = 3;
	regCont.codpart = 5;
	strcpy(regCont.nick,"NASDH");
	regCont.status = 'A';
	fwrite(&regCont,sizeof(control),1,ptr);
	
	regCont.codcamp = 2;
	regCont.codpart = 6;
	strcpy(regCont.nick,"BUGHA");
	regCont.status = 'A';
	fwrite(&regCont,sizeof(control),1,ptr);
	
	regCont.codcamp = 1;
	regCont.codpart = 8;
	strcpy(regCont.nick,"ROOKIE");
	regCont.status = 'A';
	fwrite(&regCont,sizeof(control),1,ptr);
	
	regCont.codcamp = 2;
	regCont.codpart = 7;
	strcpy(regCont.nick,"NYHROX");
	regCont.status = 'A';
	fwrite(&regCont,sizeof(control),1,ptr);
	
	fclose(ptr);
}
