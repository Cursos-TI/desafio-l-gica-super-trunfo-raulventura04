#include <stdio.h>  
#include <stdlib.h>  
#include <time.h>  
#include <string.h>  

typedef struct {  
    char estado[50];  
    char codigo[20];  
    char nome[50];  
    int populacao;  
    float area;  
    float pib;  
    int pontos_turisticos;  
} Carta;  

float densidade_populacional(Carta carta) {  
    return carta.populacao / carta.area;  
}  

void cadastrar_carta(Carta *carta) {  
    printf("Digite o estado: ");  
    scanf("%s", carta->estado);  
    
    printf("Digite o codigo da carta: ");  
    scanf("%s", carta->codigo);  
    
    printf("Digite o nome da cidade: ");  
    scanf("%s", carta->nome);  
    
    printf("Digite a populacao: ");  
    scanf("%d", &carta->populacao);  
    
    printf("Digite a area (em km²): ");  
    scanf("%f", &carta->area);  
    
    printf("Digite o PIB (em milhoes de dolares): ");  
    scanf("%f", &carta->pib);  
    
    printf("Digite o numero de pontos turisticos: ");  
    scanf("%d", &carta->pontos_turisticos);  
}  

void gerar_carta_maquina(Carta *carta) {  
    const char *nomes[] = {"Cidade A", "Cidade B", "Cidade C", "Cidade D", "Cidade E"};  
    const char *estados[] = {"Estado 1", "Estado 2", "Estado 3", "Estado 4", "Estado 5"};  
    int index = rand() % 5;  

    strcpy(carta->nome, nomes[index]);  
    strcpy(carta->estado, estados[index]);  
    strcpy(carta->codigo, "MAQ123");  
    
    carta->populacao = rand() % 1000000 + 100000;  
    carta->area = (float)(rand() % 10000 + 1);  
    carta->pib = (float)(rand() % 50000 + 1000);  
    carta->pontos_turisticos = rand() % 10;  
}  

void menu_atributos() {  
    printf("Escolha os atributos para comparação:\n");  
    printf("1. População\n");  
    printf("2. Área\n");  
    printf("3. PIB\n");  
    printf("4. Pontos turísticos\n");  
    printf("5. Densidade populacional\n");  
}  

float obter_valor(Carta carta, int atributo) {  
    switch (atributo) {  
        case 1: return (float)carta.populacao;   
        case 2: return carta.area;   
        case 3: return carta.pib;   
        case 4: return (float)carta.pontos_turisticos;   
        case 5: return densidade_populacional(carta);   
        default: return 0;  
    }  
}  

int comparar_cartas(Carta carta1, Carta carta2, int atributo1, int atributo2) {  
    float valor1_a = obter_valor(carta1, atributo1);  
    float valor1_b = obter_valor(carta1, atributo2);  
    float valor2_a = obter_valor(carta2, atributo1);  
    float valor2_b = obter_valor(carta2, atributo2);  
    
    float soma1 = valor1_a + valor1_b;  
    float soma2 = valor2_a + valor2_b;  

    if (atributo1 == 5 || atributo2 == 5) {  
        return (valor1_a < valor2_a ? 1 : (valor1_a > valor2_a ? 2 : 0));  
    }  

    return (soma1 > soma2 ? 1 : (soma1 < soma2 ? 2 : 0));  
}  

void exibir_resultados(int resultado, Carta carta1, Carta carta2) {  
    if (resultado == 0) {  
        printf("Empate! Nenhuma cidade venceu.\n");  
    } else if (resultado == 1) {  
        printf("A cidade %s venceu!\n", carta1.nome);  
    } else {  
        printf("A cidade %s venceu!\n", carta2.nome);  
    }  
}  

void exibir_carta(Carta carta) {  
    printf("\n=== Detalhes da Carta ===\n");  
    printf("Estado: %s\n", carta.estado);  
    printf("Código: %s\n", carta.codigo);  
    printf("Nome da Cidade: %s\n", carta.nome);  
    printf("População: %d\n", carta.populacao);  
    printf("Área: %.2f km²\n", carta.area);  
    printf("PIB: %.2f milhões de dólares\n", carta.pib);  
    printf("Pontos Turísticos: %d\n", carta.pontos_turisticos);  
}  

void menu() {  
    printf("\n=== MENU DE COMPARACAO ===\n");  
    printf("1. Player contra Player\n");  
    printf("2. Player contra a máquina\n");  
    printf("0. Sair\n");  
}  

int main() {  
    srand(time(NULL));  
    Carta carta1, carta2, carta_maquina;  
    
    int opcao;  
    do {  
        menu();  
        printf("Escolha uma opcao: ");  
        scanf("%d", &opcao);  

        if (opcao == 1) {  
            printf("Cadastro da primeira carta...\n");  
            cadastrar_carta(&carta1);  
            printf("Cadastro da segunda carta...\n");  
            cadastrar_carta(&carta2);  

            menu_atributos();  
            int atributo1, atributo2;  
            printf("Escolha o primeiro atributo (1-5): ");  
            scanf("%d", &atributo1);  
            printf("Escolha o segundo atributo (1-5): ");  
            scanf("%d", &atributo2);  
            
            if (atributo1 < 1 || atributo1 > 5 || atributo2 < 1 || atributo2 > 5) {  
                printf("Atributos inválidos! Tente novamente.\n");  
                continue;  
            }  

            int resultado = comparar_cartas(carta1, carta2, atributo1, atributo2);  
            exibir_resultados(resultado, carta1, carta2);  
        
        } else if (opcao == 2) {  
            printf("Cadastro da carta do jogador...\n");  
            cadastrar_carta(&carta1);  
            
            gerar_carta_maquina(&carta_maquina);  
            printf("A carta da máquina foi gerada!\n");  
            exibir_carta(carta_maquina); // Exibir a carta da máquina  

            menu_atributos();  
            int atributo1, atributo2;  
            printf("Escolha o primeiro atributo (1-5): ");  
            scanf("%d", &atributo1);  
            printf("Escolha o segundo atributo (1-5): ");  
            scanf("%d", &atributo2);  
            
            if (atributo1 < 1 || atributo1 > 5 || atributo2 < 1 || atributo2 > 5) {  
                printf("Atributos inválidos! Tente novamente.\n");  
                continue;  
            }  

            int resultado = comparar_cartas(carta1, carta_maquina, atributo1, atributo2);  
            exibir_resultados(resultado, carta1, carta_maquina);  
        }  

    } while (opcao != 0);  

    printf("Programa encerrado.\n");  
    return 0;  
}
