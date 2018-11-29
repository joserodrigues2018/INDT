/* Prova Pratica INDT C++/Qt
    Descrição: Interpretar um arquivo Xml e criar uma estrutura de decisão
               para ler um arquivo de bits
    Desenvolvedor: Rodrigues
    Data: 26/11/2018
*/

/*
Solução em C++ Console para Linux
Ambiente utilizado:
    Linux: Ubuntu 17
    IDE: Code Blocks
*/
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <cstring>

using namespace std;

//Prototipo das Funções
int LerFileXml(char* nomefile);
string TratarTexto(string text);
void EstruturaDecisao(string *vtlinhasXml);
void SplitString(string strFull, string *vetor_split);
void LerFileBin(const char* nomearq,int pos_cmp,int valor_cmp);

/*
 * registros campos xml
 */
 /*
class campoxml {
private:
    string  nome,tam,descricao,condicao;
};
*/
string *vtlinhasXml;

int main()
{
    char nomefile[]="xml_test.xml";
    LerFileXml(nomefile);
    //LerFileBin(nomefile,1,1);
	return 0;
}

void LerFileBin(const char* nomearq,int pos_cmp,int valor_cmp)
{
	ifstream arq;
	cout << "Abrindo arquivo binario...\n"<<nomearq << endl;

	arq.open(nomearq,ios::in);

    do
	{
	    string   regvalor;
		string linha_texto;
        string bin_valor;

		arq >> linha_texto;

        regvalor=linha_texto;
        bin_valor=regvalor.substr(0,1);;

		if(!arq.fail()) {
			cout << linha_texto << "\t" << endl;
		}

    	// Aplicar a leitura dos bits para apresentar o conjunto de bits
        if(atoi(bin_valor.c_str()) == valor_cmp)
        {
            cout << "Condição Verdadeira\n"<<endl;
            cout << "Conjunto de Bits\n "<<regvalor<<endl;
        }
        else{
            cout << "Condição Falsa\n"<<endl;
        }

	} while(arq.good());

		if(arq.bad() || !arq.eof()) {
		cout << "Erro fatal!" << endl;
		exit(1);
	}

	cout << "Fechando o arquivo binario..." << endl;

	arq.close();

}

string TratarTexto(string text)
{
  string::iterator it;
  string::iterator ot;
  string only = "abcdefghijklmnopqrstuvxwyz=$0123456789";
  size_t found = text.find_first_not_of(only);

  while (found!=string::npos)
  {
      it = text.begin()+found;

      text.erase (it);

     found = text.find_first_not_of(only);
  }

  return (text);
}
void SplitString(string strFull, string *ret_split)
{
    string parte_string;
    string str_parte;

    int ind_posicao=0;
    int ind_ultposicao=0;
    int ind_split = 0;
    int tam_str= 0;

    strFull = TratarTexto(strFull);

    size_t tam = strlen(strFull.c_str());

    while ((int)tam>ind_posicao){

        str_parte=strFull.substr(ind_posicao,1);

        ind_posicao++;

        if(str_parte == "="){

                if(ind_split == 0){

                    tam_str = strlen(strFull.substr(ind_split,ind_posicao-1).c_str());
                    ret_split[ind_split] = parte_string=strFull.substr(ind_split,tam_str);
                    ind_split++;
                }
                else{
                    tam_str = strlen(strFull.substr(ind_ultposicao,((ind_posicao-ind_ultposicao)-1)).c_str());
                    ret_split[ind_split] = parte_string=strFull.substr(ind_ultposicao,tam_str);
                    ind_split++;
                }

                ind_ultposicao = ind_posicao;
        }
        else if((int)tam == ind_posicao){
                tam_str = strlen(strFull.substr(ind_ultposicao,((ind_posicao-ind_ultposicao))).c_str());
                ret_split[ind_split] = parte_string=strFull.substr(ind_ultposicao,tam_str);
        }
        else{
        }
    }
}

int LerFileXml(char* filename)
{
    int ct = 0;
	ifstream arq;
    string vtlinhasXml[50];

	cout << "Abrindo arquivo..." << endl;

	arq.open(filename,ios::in);

	if (!arq.is_open())
		return (0);

	string cabecalho;
	getline(arq,cabecalho);

	cout << cabecalho << endl;

	do
	{
	    string   recvalor;
		string linha_texto;
		arq >> linha_texto;

        recvalor=linha_texto;
        vtlinhasXml[ct]=recvalor;

        ct++;

		if(!arq.fail()) {
			cout << linha_texto << "\t" << endl;
		}

	} while(arq.good());

		if(arq.bad() || !arq.eof()) {
		cout << "Erro fatal!" << endl;
		exit(1);
	}

	cout << "Fechando o arquivo..." << endl;

	arq.close();

    EstruturaDecisao(vtlinhasXml);

	return 0;
}

void EstruturaDecisao(string *vtlinhasXml)
{
    string ret_split[3];
    size_t sztam;
    string posicao;
    string valor_bit;

    cout<<"\nEstrutura de Decisão..."<< endl;

	for ( int i=0; i<20; i++)
    {
       string str_codicao="conditions";

       //cout<< vtlinhasXml[i] << endl;

       if(str_codicao == vtlinhasXml[i].substr(0,strlen(str_codicao.c_str())))
       {
            SplitString(vtlinhasXml[i],ret_split);

            for(int l=0; l<3 ; l++)
            {
                cout << ret_split[l] << endl;
            }


            sztam = strlen(ret_split[1].c_str());
            posicao = ret_split[1].substr((int)sztam-1,1);
            valor_bit = ret_split[2];

            //vetor/poteiro com o nome dos arquivos binarios
            //const char *filesbin[] = {"agenda.xml","bits_file0.bf","bits_file1.bf"};
            const char* vetor_arq[] = {"bits_file0.bf","bits_file1.bf"};

            for(int f=0; f<(int)sizeof(vetor_arq); f++)
            {
                LerFileBin(vetor_arq[f],atoi(posicao.c_str()),atoi(valor_bit.c_str()));
            }
       }
    }

}
