#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <locale.h>
#define TAM_ARQ 0xFFFFF
#define OFFSET 0

int Tamanho(char* nome);
void Escolhe_bloco(int seletor);
struct bloco le_bloco(char* nome_do_bloco);
void Inserter(char* texto_traduzido, struct bloco parametros, char* numero_bloco, char* caminho_bin);
void pont_orig(char *nome_do_bloco, struct bloco parametros);
void calcula_ponteiro(unsigned int offset_fim, unsigned int inicio_bloco, char* caminho_bin, char* numero_bloco);
struct ponteiro le_ponteiro(char *nome_ponteiro, char* numero_bloco);

typedef struct bloco{
	unsigned int offset_ini;
	unsigned int offset_fim;
};

typedef struct ponteiro{
	unsigned int pont_texto;
	unsigned int pont_offset;
	unsigned int pont_hard;
};

struct ponteiro le_ponteiro(char *nome_ponteiro, char *numero_bloco){
	FILE *arquivo;
	char s[100];
	int bloco=0;
	struct ponteiro pont;
	char *h;
	char nome_ponteiro_concat[70] = "";
	
	strcpy(nome_ponteiro_concat, "Ponteiros\\Pont_Bloco_");
	strcat(nome_ponteiro_concat, numero_bloco);
	strcat(nome_ponteiro_concat, ".txt"); //Bloco_1.txt
	
//	printf("\nArquivo que está sendo lido: %s\n", nome_ponteiro_concat);
//	getch();
	
	if ((arquivo = fopen(nome_ponteiro_concat, "rt")) == NULL){
	  printf ("Erro na leitura do arquivo!\n\n");
	  exit (0);        
	}
	
	while (fgets(s, 100, arquivo) != NULL){
		
//		printf("\n%s\n", s);
//		getch();
		
		if(strstr(s, nome_ponteiro) != NULL && (h=strstr(s, "Texto=")) != NULL){
			sscanf(s+strlen(h), "%XX", &pont.pont_texto);
//			printf("\nInício do texto original: %.8x\n", pont.pont_texto);
//			getch();
		}	
		if(strstr(s, nome_ponteiro) != NULL && (h=strstr(s, "Offset=")) != NULL){
      		sscanf(s+strlen(h), "%XX", &pont.pont_offset);
//      		printf("\nOffset original do ponteiro: %.8x\n", pont.pont_offset);
//      		getch();
    	}
    	if(strstr(s, nome_ponteiro) != NULL && (h=strstr(s, "Hard=")) != NULL){
      		sscanf(s+strlen(h), "%XX", &pont.pont_hard);
//      		printf("\nValor do ponteiro: %.4x\n", pont.pont_hard);
//      		getch();
      		//break;
    	}
	}
	fclose(arquivo);
	return pont;

}

int Tamanho(char* nome){
	FILE *arq;
	unsigned char s[200];
	int contador, i;
	
	if ((arq = fopen (nome,"r")) == NULL){
	  printf ("Erro na abertura do arquivo de texto!\n\n");
	  exit (0);        
	}
	
	while (fgets(s, 200, arq) != NULL){
		
		if(!strcmp(s, "------------------\n") || !strcmp(s, "------------------")){
		  continue;
		}
		
		for(i=0;i<(int)strlen(s)-1;i++){
			if(s[i] == '{'){
				if(s[i+3] == '}'){
					contador++;
				}
				i=i+3;
				
			}
			else{
			  contador++;
			}    
		}
	
	}
	fclose(arq);
	return contador;
}

struct bloco le_bloco(char *nome_do_bloco){
	FILE *arquivo;
	char s[100];
	int bloco=0;
	struct bloco parametros;
	char *h;
	
	if ((arquivo = fopen("Blocos_Panzer.txt", "rt")) == NULL){
	  printf ("Erro na abertura do arquivo!\n\n");
	  exit (0);        
	}

	//arquivo = fopen("Blocos_Panzer.txt", "rt");
	while (fgets(s, 100, arquivo) != NULL){
		
		if(strstr(s, nome_do_bloco) != NULL && (h=strstr(s, "_Offset_de_inicio=")) != NULL){
			sscanf(s+strlen(h), "%XX", &parametros.offset_ini);	
		}	
		if(strstr(s, nome_do_bloco) != NULL && (h=strstr(s, "_Offset_de_fim=")) != NULL){
      		sscanf(s+strlen(h), "%XX", &parametros.offset_fim);
      		break;
    	}
	}
	
	fclose(arquivo);
	return parametros;
}

void Escolhe_bloco(int seletor){
    int opc, i;
    char nome[50];
    char caminho[100];
    char caminho_trad[100];
    char opc_convertido[2];
    struct bloco parametros;
    char nome_bin[50];
    char caminho_bin[70];

    do{
        system("cls");
        printf("Digite o numero do Script que deseja inserir:\n");
        printf("\t 1. Bloco_1: Abertura\n");
        printf("\t 2. Bloco_2: Intro\n");
        printf("\t 3. Bloco_3: Escolha de fases\n");
        printf("\t 4. Bloco_4: Gustav (Kazan)\n");
        printf("\t 5. Bloco_5: Jingorou\n");
        printf("\t 6. Bloco_6: Senka\n");
        printf("\t 7. Bloco_7: Mudou\n");
        printf("\t 8. Bloco_8: Seleção fases 5\n");
        printf("\t 9. Bloco_9: Farad\n");
        printf("\t 10. Bloco_10: Zwei\n");
        printf("\t 11. Bloco_11: Cont. Fase 5\n");
        printf("\t 12. Bloco_12: Sala dos Chefes finais\n");
        printf("\t 13. Bloco_13: Cont. Chefes finais\n");
        printf("\t 14. Bloco_14: Final do jogo\n");
        printf("\t 15. Sair\n");
        printf("\t 0. Todos\n");
        scanf("%d", &opc);
		
		if(opc == 1){
			strcpy(nome_bin, "DEMO1.BIN");
		}
		if(opc == 2){
			strcpy(nome_bin, "DEMO2.BIN");
		}
		if(opc == 3){
			strcpy(nome_bin, "LOAD_VS.BIN");
		}
		if(opc == 4){
			strcpy(nome_bin, "ST1_3.BIN");
		}
		if(opc == 5){
			strcpy(nome_bin, "ST2_3.BIN");
		}
		if(opc == 6){
			strcpy(nome_bin, "ST3_3.BIN");
		}
		if(opc == 7){
			strcpy(nome_bin, "ST4_3.BIN");
		}
		if(opc == 8){
			strcpy(nome_bin, "ST4_E.BIN");
		}
		if(opc == 9){
			strcpy(nome_bin, "ST5_2.BIN");
		}
		if(opc == 10){
			strcpy(nome_bin, "ST5_3.BIN");
		}
		if(opc == 11){
			strcpy(nome_bin, "ST7_3.BIN");
		}
		if(opc == 12){
			strcpy(nome_bin, "ST8_1.BIN");
		}
		if(opc == 13){
			strcpy(nome_bin, "ST8_3.BIN");
		}
		if(opc == 14){
			strcpy(nome_bin, "STA_0.BIN");
		}
		
		strcat(caminho_bin, nome_bin);
		
		if(opc != 0){
			if(seletor == 222){
	            strcpy(nome, "Bloco_");
				sprintf(opc_convertido, "%d", opc);
				strcat(nome, opc_convertido);
	            strcpy(caminho_trad, "scripts_traduzidos\\");
	            strcat(caminho_trad, nome);
	            strcat(caminho_trad, ".txt");

	            parametros = le_bloco(nome);
	            Inserter(caminho_trad, parametros, opc_convertido, caminho_bin);
	            break;
        	}
	        if(opc == 15){
				break;
			}
		}
		else{
			for(i=1;i<=14;i++){
				if(seletor == 222){
		            strcpy(nome, "Bloco_");
		            if(opc == 0){
		            	opc++;
					}
					strcpy(caminho_bin, "Binarios\\");
					sprintf(opc_convertido, "%d", opc);
					strcat(nome, opc_convertido);
		            strcpy(caminho_trad, "scripts_traduzidos\\");
		            strcat(caminho_trad, nome);
		            strcat(caminho_trad, ".txt");
		            
		            if(opc == 1){
						strcpy(nome_bin, "DEMO1.BIN");
					}
					if(opc == 2){
						strcpy(nome_bin, "DEMO2.BIN");
					}
					if(opc == 3){
						strcpy(nome_bin, "LOAD_VS.BIN");
					}
					if(opc == 4){
						strcpy(nome_bin, "ST1_3.BIN");
					}
					if(opc == 5){
						strcpy(nome_bin, "ST2_3.BIN");
					}
					if(opc == 6){
						strcpy(nome_bin, "ST3_3.BIN");
					}
					if(opc == 7){
						strcpy(nome_bin, "ST4_3.BIN");
					}
					if(opc == 8){
						strcpy(nome_bin, "ST4_E.BIN");
					}
					if(opc == 9){
						strcpy(nome_bin, "ST5_2.BIN");
					}
					if(opc == 10){
						strcpy(nome_bin, "ST5_3.BIN");
					}
					if(opc == 11){
						strcpy(nome_bin, "ST7_3.BIN");
					}
					if(opc == 12){
						strcpy(nome_bin, "ST8_1.BIN");
					}
					if(opc == 13){
						strcpy(nome_bin, "ST8_3.BIN");
					}
					if(opc == 14){
						strcpy(nome_bin, "STA_0.BIN");
					}
					
					strcat(caminho_bin, nome_bin);
					
		            parametros = le_bloco(nome);
		            Inserter(caminho_trad, parametros, opc_convertido, caminho_bin);
		            opc++;
		            strcpy(caminho_bin, "");
        		}
		        if(opc == 15){
					break;
				}
				printf("%s\n", nome);	
			}
			printf("Concluído!\n");
			exit(0);
			//getch();
		}  
	}while(opc != 15);
    strcpy(caminho, "");
    strcpy(caminho_trad, "");
    strcpy(nome, ""); 
}

void Inserter(char* texto_traduzido, struct bloco parametros, char* numero_bloco, char* caminho_bin){
	FILE *arq, *out;
	unsigned char s[200];
	unsigned int c;
	unsigned int offset_fim, offset_fim_add, inicio, fim;
	int i, j, cont, contador, contador_bin, over;
	int left=NULL;
	unsigned char caminho_trad[100] = "";
	//char nome[30] = "KISINDAT_novo.NCB";
	unsigned char tabela[256] = "@@@@@@@@@@@@@@@@"
	                          	"@@@@@@@@@@@@@@@@"
	                          	" !\"#$%&'()*+,-./"
	                          	"0123456789:;<=>?"
	                          	"@ABCDEFGHIJKLMNO"
	                          	"PQRSTUVWXYZ[\\]^_"
	                          	"@abcdefghijklmno"
	                          	"pqrstuvwxyz{@@@@"
	                          	"@@@@@@@@@@@@@@@@"
	                          	"@@@@@@@@@@@@@@@@"
	                          	"@@@@@@@@@@@@@@@@"
	                          	"@@@@@@@@@@º@@@@@"
	                          	"ÀÁÂÃÄ@@Ç@ÉÊËÌÍÎÏ"
	                          	"@ÑÒÓÔÕÖ@@ÙÚÛÜ@@ß"
	                          	"àáâãä@@ç@éê@@í@@"
	                          	"@@@óôõ@@@ùú@@@@@";

		
	strcpy(caminho_trad, texto_traduzido);
	printf("Caminho traduzido: %s\n\n", caminho_trad);
	contador_bin = parametros.offset_fim - parametros.offset_ini;
	contador = Tamanho(caminho_trad);
	
	printf("\nTamanho_bin: %d\nTamanho do texto: %d\n", contador_bin, contador);
	
	if(contador > contador_bin){
		over = contador - contador_bin;
    	printf("O arquivo modificado tem %d caractere(s) a mais. Edite-o.\n", over);
    	getch();
    	exit(0);
	}
	if(contador < contador_bin){
		left = contador_bin - contador;
		printf("\nTamanho aceitável!!\n");
	}

	if ((arq = fopen (caminho_trad,"r")) == NULL){
	  printf ("Erro na abertura do arquivo modificado!\n\n");
	  exit (0);        
	}
	    
	if ((out = fopen (caminho_bin,"r+b")) == NULL){
	  printf ("Erro na criação do arquivo!\n");
	  exit (0);        
	}

	fseek (out, SEEK_SET + parametros.offset_ini, SEEK_SET);

	while (fgets(s, 200, arq) != NULL){
		if(!strcmp(s, "------------------\n") || !strcmp(s, "------------------")){
		  continue;
		}
		for(i=0;i<(int)strlen(s)-1;i++){
			if(s[i] == '{'){
				if(s[i+3] == '}'){
					sscanf(&s[i+1], "%xx", &c);
					fputc(c, out);                        
					i= i+3;
				}
			}
			else{
			  c = s[i];
			  cont = 0;
			  while (tabela[cont] != c) cont++;
			  fputc (cont, out);
			}    
		}
	}
	
	offset_fim = ftell(out);
	
	if(left != NULL){
		offset_fim_add = offset_fim+left;
		for(j=offset_fim;j<=offset_fim_add;j++){
			fputc(0x20, out);
		}
	}
	fclose(arq);
	fclose(out);
	
//	printf("Offset_ini: %.8x\nOffset_fim: %.8x\n", parametros.offset_ini, parametros.offset_fim);
//    getch();
    
    inicio = parametros.offset_ini;
    
	if(strcmp(numero_bloco, "Bloco_9") || strcmp(numero_bloco, "Bloco_10") || strcmp(numero_bloco, "Bloco_14")){
		if(left != NULL){
			calcula_ponteiro(offset_fim_add, inicio, caminho_bin, numero_bloco);	
		}
		else{
			calcula_ponteiro(offset_fim, inicio, caminho_bin, numero_bloco);	
		}
	}
	
	printf("A inserção foi realizada com êxito!\n");
//	getch();

}

void calcula_ponteiro(unsigned int offset_fim, unsigned int inicio_bloco, char* caminho_bin, char* numero_bloco){
	FILE *arquivo;
	unsigned int tam, novo_offset_ini, Byte1, Byte2, resto, novo_ponteiro_soma;
	unsigned char *memoria;
	int cont, i;
	struct ponteiro parametros_pont;
	int num_pont=1;
	char numero_ponteiro[2]; 
	char nome_ponteiro[20];
	
	arquivo = fopen(caminho_bin, "r+b");
    fseek(arquivo, 0, SEEK_END);
    tam = ftell(arquivo);
    fseek(arquivo, 0, SEEK_SET);
    memoria = (unsigned char*) malloc (sizeof(unsigned char)*tam);
    cont = fread (memoria, sizeof(unsigned char), tam, arquivo);
    
    for(i=inicio_bloco;i<=offset_fim-1;i++){
    	
    	if(memoria[i] == 0x00 && memoria[i+1] != 0x00 && memoria[i+1] != 0x20){
			novo_offset_ini = i + 1;
    		
			strcpy(nome_ponteiro, "Pont_");
			sprintf(numero_ponteiro, "%d", num_pont);
			strcat(nome_ponteiro, numero_ponteiro);
			
//			printf("\nPonteiro que está sendo mandado: %s\n", nome_ponteiro);
			
			parametros_pont = le_ponteiro(nome_ponteiro, numero_bloco);
			
//			printf("\nNovo Offset_ini: %.8x\nInício do texto original: %.8x\nOffset original do ponteiro: %.8x\nValor do ponteiro: %.4x\n", novo_offset_ini, parametros_pont.pont_texto, parametros_pont.pont_offset, parametros_pont.pont_hard);
			
			if(novo_offset_ini > parametros_pont.pont_texto){
				resto = novo_offset_ini - parametros_pont.pont_texto;
				novo_ponteiro_soma = parametros_pont.pont_hard + resto;
			}
			if(parametros_pont.pont_texto > novo_offset_ini){
				resto = parametros_pont.pont_texto - novo_offset_ini;
				novo_ponteiro_soma = parametros_pont.pont_hard - resto;
			}
			if(parametros_pont.pont_texto == novo_offset_ini){
				resto = 0;
				novo_ponteiro_soma = parametros_pont.pont_hard + resto;
			}
			
//			printf("\nResto: %d\nResultado: %.8x\n", resto, novo_ponteiro_soma);
		
						
			Byte1 = (unsigned char)(novo_ponteiro_soma & 0x000000FF);
		    Byte2 = (unsigned char)((novo_ponteiro_soma >> 8) & 0x000000FF);
		    
//		    printf("\nByte1: %.2x\n\nByte2: %.2x\nLocal de gravação: %.8x\n", Byte1, Byte2, parametros_pont.pont_offset);
//		    getch();
		    		
		    fseek (arquivo, parametros_pont.pont_offset, SEEK_SET);
		    	
		    fwrite(&Byte1, sizeof(unsigned char), 1, arquivo);
	    	fwrite(&Byte2, sizeof(unsigned char), 1, arquivo);
			
			num_pont++;
			
		}
		
    }
    
    fclose(arquivo);
    free(memoria);
    
}

int main(){
	int opc;
	int i;
	
	setlocale(LC_ALL, "Portuguese");
	
	mkdir("scripts_originais");
	mkdir("scripts_traduzidos");
	
	do{
		system("cls");
		printf("     Escolha uma das opções:\n\n");
		printf("\t1. Inserir textos\n");
		printf("\t9. Sair\n");
		scanf("%d", &opc);
	  
	  	if(opc==1){  	
	  		Escolhe_bloco(222);
	  	}
	  	else if(opc == 9){
	  		exit(1);
	  	}               
	}
	while(opc != 9);
	getch();
}
