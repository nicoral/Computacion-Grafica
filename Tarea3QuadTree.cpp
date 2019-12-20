#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>
#include <utility>
#include <stdlib.h> 
#include <time.h>   
#include <queue>
#include <iomanip>

using namespace cv;
using namespace std;
typedef vector<vector<int>> Matriz;
Matriz ini(int n, int nn)// Inicializacion de una Matriz
{
	Matriz B;
	vector<int> aux;
	int val = 0;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < nn; j++)
		{
			aux.push_back(val);
		}
		B.push_back(aux);
		aux.clear();
	}
	return B;
}
Matriz llenar(int n, int nn)// FUNCION PARA LLENAR LA MATRIZ
{
	Matriz B;
	vector<int> aux;
	int val;
	srand(time(NULL));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < nn; j++)
		{
			//cin >> val;
			val = rand() % 10 + 1;
			aux.push_back(val);
		}
		B.push_back(aux);
		aux.clear();
	}
	return B;
}
void mostrar(Matriz& A)
{
	int n = A.size();
	int nn = A[0].size();
	cout << "----------------------------" << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < nn; j++)
		{
			cout << " " << A[i][j];
		}
		cout << endl;
	}
	cout << "----------------------------" << endl;
}
struct node
{
	int valor;
	node* uno;
	node* dos;
	node* tres;
	node* cuatro;
	node(int v, node* a, node* b, node* c, node* d)
	{
		this->valor = v;
		this->uno = a;
		this->dos = b;
		this->tres = c;
		this->cuatro = d;
	}
	node(int v)
	{
		this->valor = v;
		this->uno = NULL;
		this->dos = NULL;
		this->tres = NULL;
		this->cuatro = NULL;
	}
	node()
	{
		this->uno = NULL;
		this->dos = NULL;
		this->tres = NULL;
		this->cuatro = NULL;
	}
};


Matriz subMatriz(Matriz& A, int arri, int izq,int abj , int der)// Se le envia una matriz y te devuelve su 
{                                   									// subMatriz dependiendo de posiciones
	Matriz B;
	int dim1 = abj-arri, dim2 = der-izq ;
	B = ini(dim1,dim2);
	int x = arri, y = izq;
	for (int i = 0; i < dim1; i++)
	{
		for (int j = 0; j < dim2; j++)
		{
			B[i][j] = A[x][y];
			y++;
		}
		x = x + 1;
		y = izq;
	}
	return B;
}
int MatrizIgual(Matriz& A)//BUSCA ALGUN VALOR DISTINTO EN LA MATRIZ 
{
	int au = A[0][0];
	for (int i = 0; i < A.size(); i++)
	{
		for (int j = 0; j < A[0].size(); j++)
		{
			if (A[i][j] != au)
				return -1;
		}
	}
	return au;
}
void imprimirQuad(node* raiz) //IMPRIME EL ARBOL POR NIVELES
{
	queue<node*> cola;
	cola.push(raiz);
	int n;
	while (!cola.empty())
	{
		n = cola.size();
		for (int i = 0; i < n; i++)
		{
			if (cola.front()->uno != NULL)
			{
				cola.push(cola.front()->uno);
			}
			if (cola.front()->dos != NULL)
			{
				cola.push(cola.front()->dos);
			}
			if (cola.front()->tres != NULL)
			{
				cola.push(cola.front()->tres);
			}
			if (cola.front()->cuatro != NULL)
			{
				cola.push(cola.front()->cuatro);
			}
			cout << " " << cola.front()->valor << " ";
			cola.pop();
		}
		cout << endl << endl;
	}
}
void QuadTree(Matriz& A, node* raiz)//FUNCION RECURSIVA QUE RECIVE UNA MATRIZ Y UN 
{                                                                  // NODO E IRA CREANDO EL ARBOL HASTA ENCONTRAR
	int dim1 = A.size();
	
	if (dim1 > 0)
	{
		int dim2 = A[0].size();                        // UNA MATRIZ DE DATOS IGUALES O SEA DE 2X2
		int n = MatrizIgual(A);
		if (n == -1)
		{
			raiz->valor = -1;

			if (dim1 == 1 || dim2 == 1)
			{
				if (dim1 == 1 && dim2 == 1)
				{
					raiz->uno = new node(A[0][0]);
					return;
				}
				else if (dim1 == 1 && dim2 > 1)
				{
					Matriz B = subMatriz(A, 0, 0, dim1, dim2 / 2);

					Matriz D = subMatriz(A, 0, dim2 / 2, dim1, dim2);
					raiz->uno = new node();
					raiz->tres = new node();
					QuadTree(B, raiz->uno);
					QuadTree(D, raiz->tres);
				}
				else if (dim2 == 1 && dim1 > 1)
				{
					
					Matriz B = subMatriz(A, 0, 0, dim1 / 2, dim2);
					Matriz C = subMatriz(A, dim1 / 2, 0, dim1, dim2);
					
					raiz->uno = new node();
					raiz->dos = new node();
					QuadTree(B, raiz->uno);
					QuadTree(C, raiz->dos);
				}
			}
			else if (dim1 == 2 && dim2 == 2)
			{
				raiz->uno = new node(A[0][0]);
				raiz->dos = new node(A[0][1]);
				raiz->tres = new node(A[1][0]);
				raiz->cuatro = new node(A[1][1]);
				return;
			}
			else
			{
				Matriz B = subMatriz(A, 0, 0, dim1 / 2, dim2 / 2);

				Matriz C = subMatriz(A, 0, dim2 / 2, dim1 / 2, dim2);

				Matriz D = subMatriz(A, dim1 / 2, 0, dim1, dim2 / 2);

				Matriz E = subMatriz(A, dim1 / 2, dim2 / 2, dim1, dim2);
				raiz->uno = new node();
				raiz->dos = new node();
				raiz->tres = new node();
				raiz->cuatro = new node();
				QuadTree(B, raiz->uno);
				QuadTree(C, raiz->dos);
				QuadTree(D, raiz->tres);
				QuadTree(E, raiz->cuatro);
			}
		}
		else
		{
			raiz->valor = n;
			return;
		}
	}
}
void imprimir(Mat m, Matriz& A) 
{
	vector<int> aux;
	for (int j = 0; j < m.rows; j++) 
	{
		for (int i = 0; i < m.cols; i++) 
		{
			int pixel = m.at<uchar>(j, i);
			aux.push_back(pixel);
		}
		A.push_back(aux);
		aux.clear();
	}
}

int main()
{
	Matriz A;
	//A = llenar(25,14);
	//mostrar(A);
	
	Mat imagen = imread("Prueba.jpg");
	
	imshow("Prueba", imagen);
	imprimir(imagen,A);
	waitKey(0);
	
	node* raiz = new node();
	QuadTree(A, raiz);
	imprimirQuad(raiz);
	return 0;
}