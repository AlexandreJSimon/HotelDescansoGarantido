#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <conio.h>
#include <locale.h>
struct Tfuncionario
{
    int codigo;
    char nome[30];
    int telefone;
    char cargo[15];
    float salario;
    int deleta;
};
typedef struct Tfuncionario funcionario;
int main()
{
    FILE *f;
    char op;
    setlocale(LC_ALL,"portuguese");
    if ((f = fopen("teste.dat", "r+b"))==NULL) // arquivo existe
    {
        printf("Arquivo não exista ... criando arquivo!");
        if((f = fopen("teste.dat", "w+b"))==NULL) //arq não existe
        {
            printf("Erro na criação do arquivo!!");
            exit(1);
        }
        system("pause");
    }

    do
    {
        printf("Escolha:\n");
        printf("a-incluir funcionario\n");
        printf("b-alterar funcionario\n");
        printf("c-listar funcionario\n");
        printf("d-deletar funcionario\n");
        printf("e-sair do sistema\n");
        op=getch();
        switch (op)
        {
        case 'a':
            printf("preenchendo o arquivo...\n");
            inclui_funcionario(f);
            break;
        case 'b':
            printf("alterando o arquivo...\n");
            altera_arquivo(f);
            break;
        case 'c':
            printf("imprmindo o arquivo...\n");
            imprime_arquivo(f);
            system("pause");
            break;
             case 'd':
            printf("deletando o arquivo...\n");
            deleta_arquivo(f);
            system("pause");
            break;
        }
    }
    while (op!='e');
    fclose(f);
    return 0;
}

int localiza_funcionario(FILE *f,int codigo)
{
    int posicao=-1,achou=0;
    funcionario m;
    fseek(f,0,SEEK_SET);
    fread(&m, sizeof(m),1, f);
    while (!feof(f) && !achou)
    {
        printf("%d %d\n",m.codigo,m.deleta);
        posicao++; // semelhante a posicao = posicao +1;
        if (m.codigo==codigo && m.deleta==0)
        {
            achou=1;
        }
        fread(&m, sizeof(m),1, f);
    }
    if (achou)
    {
        return posicao;
    }
    else
    {
        return -1;
    }
}

void inclui_funcionario(FILE *f)
{
    funcionario m;
    int posicao;
//lendo os dados do teclado
    printf("Digite o código do Funcionario...:");
    fflush(stdin);
    scanf("%d",&m.codigo);
    posicao=localiza_funcionario(f,m.codigo);
    if (posicao==-1) //não tnha codigo no arquivo
    {
        printf("Digite o nome do Funcionario...:");
        fflush(stdin);
        gets(m.nome);
        printf("Digite o telefone do Funcionario...:");
        fflush(stdin);
        scanf("%d",&m.telefone);
        printf("Digite o cargo do Funcionario...:");
        fflush(stdin);
        gets(m.cargo);
        printf("Digite o salario do funcionario...:");
        fflush(stdin);
        scanf("%f",&m.salario);
         m.deleta=0;
        fflush(f);
        fseek(f,0,SEEK_END); // posicionado o arquivo no fnal
        fwrite(&m, sizeof(m),1,f); //gravando os dados
        fflush(f);
    }
    else
    {
        printf("Código %d já existe no arquivo. Inclusão não realizada!\n");
    }
}

void altera_arquivo(FILE *f)
{
    int codigo,posicao;
    funcionario m;
    printf("Diga qual o codigo funcionario para alterar:");
    scanf("%d",&codigo);
    posicao=localiza_funcionario(f,codigo);
    if (posicao!=-1)
    {
        fseek(f,sizeof(m)*(posicao),SEEK_SET);
        fread(&m, sizeof(m),1, f);
        printf("Codigo atual:%d - nome atual:%s - telefone atual:%d - cargo atual:%s - salario atual:%.2f\n",m.codigo,m.nome,m.telefone,m.cargo,m.salario);
        printf("Novo nome....:");
        fflush(stdin);
        gets(m.nome);
        printf("Novo telefone....:");
        fflush(stdin);
        scanf("%d",&m.telefone);
        printf("Novo cargo....:");
        fflush(stdin);
        gets(m.cargo);
        printf("Novo salario....:");
        scanf("%f",&m.salario);
        m.deleta=0;
        fflush(f);
        fseek(f,sizeof(m)*(posicao ),SEEK_SET);
        fwrite(&m, sizeof(m),1, f);
        fflush(f);
    }
}

void imprime_arquivo(FILE *f)
{
    funcionario m;
    fseek(f,0,SEEK_SET);
    fread(&m, sizeof(m),1, f);
    while (!feof(f))
    {
        if (m.deleta==0)
        {
        printf("Código....:%d \n",m.codigo);
        printf("Descrição.:%s \n",m.nome);
        printf("Telefone....:%d \n",m.telefone);
        printf("Cargo.:%s \n",m.cargo);
        printf("Salario.....:%.2f\n",m.salario);
        }
        fread(&m, sizeof(m),1, f);
    }

}
void deleta_arquivo(FILE *f)
{
    int codigo,posicao;
    funcionario m;
    printf("Diga qual o codigo funcionario para deletar:");
    scanf("%d",&codigo);
    posicao=localiza_funcionario(f,codigo);
    if (posicao!=-1)
    {
        fseek(f,sizeof(m)*(posicao),SEEK_SET);
        fread(&m, sizeof(m),1, f);
        m.deleta=1;
        fflush(f);
        fseek(f,sizeof(m)*(posicao),SEEK_SET);
        fwrite(&m, sizeof(m),1, f);
        fflush(f);
    }

}

