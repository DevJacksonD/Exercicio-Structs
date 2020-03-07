#include<stdio.h>
#include<stdlib.h>

// Estrutura definida
typedef struct
{
	unsigned short Id;
	char Name[32];
	unsigned char Age;
}Person_t;
//
Person_t *people; 
int NumberPeople; // Variavel para definir quantidade de pessoas.
// função para preencher estrura
int writePeople(Person_t *people){
    int i, auxInput = 0;
    for( i=0; i<NumberPeople; i++) { // preenche cada posiçao do vetor de estrutura
        printf(" Digite o numero do Id: ");
        scanf("%d", &auxInput);
        fflush(stdin); // limpa lixo de memória
        people[i].Age = auxInput;
        while(verifyId(auxInput) == 1){ // ao receber 1 da função que verifica se o Id ja existe, entra no loop, ate que o Id seja diferente
            printf("Este Id ja existe, digite outro:");
            scanf("%d",&auxInput);
            fflush(stdin);
        }
        people[i].Id = auxInput; // a estrura recebe o valor da variavel auxiliar
        printf(" Digite o nome: ");
        scanf("%s", &people[i].Name);
        fflush(stdin);
        people[i].Age = checkbugsAge();// chama a função para verificar idade digitada
    }
}
//
// Função para imprimir estrutura
int readPeople(Person_t *people){
    int i;
    for(i=0; i<NumberPeople; i++) { // realiza a varredura do vetor ate o numero de pessoas desejado, preenchendo cada posição
        printf("\n # Lendo Pessoa #%d" ,i+1);
        printf(" \n ID: %d ", people[i].Id);
        printf(" \n Nome: %s ", people[i].Name);
        printf(" \n Idade: %d ", people[i].Age);
        
    }

}
// função para verificar se numero de pessoas é valido, apresenta erro ao digitar caracter diferente de número
int checkbugsNumberPeople(){
    int aux = 0; 
    printf("Entre com o numero de pessoas:");
    scanf("%d",&NumberPeople);
    fflush(stdin);  
    aux = NumberPeople; // variavel auxiliar recebe o numero de pessoas desejado
    while(aux == 0){ // caso seja um caracter ele retorna zero, e entra no loop.
        printf("Numero invalido\n");
        printf("Entre com o numero de pessoas:");
        scanf("%d",&NumberPeople);
        fflush(stdin);
        aux = NumberPeople;   
    }
    return 0;  
}
//
// Função que verifica se Id ja existe, caso exista pede para inserir outro
int verifyId(int auxId){

    int i;
    for(i=0;i<NumberPeople;i++){
        if(auxId == people[i].Id){ // verifica se o valor de Id digitado ja existe na estrutura, retornando 1 se ja existir.
            return 1;
        }

    }
    return 0;
}
// Função que verifica se Idade digitada é um numero e se é maior que 1.
int checkbugsAge(){
   int verifyAge = 0,auxAge = 0;
        printf(" Digite a Idade: ");
        scanf("%d", &auxAge);
        fflush(stdin);
         verifyAge = auxAge; 
    while(verifyAge == 0|| verifyAge < 1){ //caso não seja numero ou seja menor que 1, entra no loop
        printf("Idade invalido\n");
        printf("Entre com uma nova idade:");
        scanf("%d",&auxAge);
        fflush(stdin);
        verifyAge = auxAge;   
    }
    return verifyAge;   
}
//
// Função que ordena estrura pela idade de forma decrescente
// usado codigo como exemplo - https://pt.wikipedia.org/wiki/Quicksort -
void quicksort(int values[], int began, int end)
{
     
	int i=0, j=0, pivo=0, aux=0 , k=0;
    char auxName[32];
    char auxidp;
    for(k = 0; k <NumberPeople; k++){
        values[k] = people[k].Age;
    }
	i = began;
	j = end-1;
	pivo = values[(began + end) / 2];
	while(i <= j)
	{
		while(values[i] < pivo && i < end)
		{
			i++;
		}
		while(values[j] > pivo && j > began)
		{
			j--;
		}
		if(i <= j)
		{
			aux = values[i];   
            strcpy(auxName, people[i].Name);
            auxidp = people[i].Id;
			values[i] = values[j];
            people[i].Id = people[j].Id;
            strcpy(people[i].Name,people[j].Name);
            people[i].Age = people[j].Age;
			values[j] = aux;
            people[j].Id = auxidp;
            strcpy(people[j].Name, auxName);
            people[j].Age = aux;
			i++;
			j--;
		}
	}
	if(j > began)
		quicksort(values, began, j+1);
	if(i < end)
		quicksort(values, i, end);
}
//
// Função que imprime a estrutura de forma ordenada
int readQuicksort(Person_t *people){
    int j;
    printf("\n# Relacao de pessoas ordenadas");
    for(j=NumberPeople-1; j>=0; j--) {
        printf(" \n ID: %d ", people[j].Id);
        printf(" \n Nome: %s ", people[j].Name);
        printf(" \n Idade: %d ", people[j].Age);
    }
}

int main(void) {
    
    int values[NumberPeople - 1];// vetor auxiliar utilizado na função quick sort
    people = (Person_t*) malloc(NumberPeople*sizeof(Person_t)); // aloca memoria dinamicamente
    checkbugsNumberPeople();//chama função para verificar o numero de pessoas
    writePeople(people);//chama função para preencher a  estrutura
    readPeople(people);// chama função para imprimir a estrutura
    quicksort(values, 0, NumberPeople);// chama função para ordenação
    readQuicksort(people);// chama função para imprimir estrutura ordenada
    free(people);// libera memória

}