#include <iostream>
#include <windows.h>
#include <cstdlib>
# include <math.h>
# include <time.h>
#include <ctime>
#include <cmath>
#include <stack>
# include <omp.h>
#define N 4
#define paddingx 2
#define paddingy 1
#pragma warning(disable : 4996)
using namespace std;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;
void gotoXY(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}


void Populate(int** arr, int n, int k) {
	system("CLS");
	cout << "	Please enter the values for the matrix";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < k; j++) {
			gotoXY((i+3) * paddingx, (j+1) * paddingy);
			cin >> arr[i][j];
		}
	}
	system("CLS");
}

void PopulateAuto(int** arr, int n, int k) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < k; j++) {
			arr[i][j] = rand() % 10;
		}
	}
	cout << "Matrix populated" << endl;
}

void MatrixAddition() {
	int tid,n,k,l;
	cout << "\nPlease enter the dimensions of the matrices: ";
	cin >> n >> k;
	
	int** a = new int* [n];
	for (int i = 0; i < n; i++)
		a[i] = new int[k];

	int** b = new int* [n];
	for (int i = 0; i < n; i++)
		b[i] = new int[k];

	int** f = new int* [n];
	for (int i = 0; i < n; i++)
		f[i] = new int[k];


	cout << "\n\nPress 0 to Manually fill the matrices..\nPress 1 to have the matrices filled automatically..\n ";
	cin >> l;
	if (!l) {
		Populate(a, n, k);
		Populate(b, n, k);
	}
	else {
		PopulateAuto(a, n, k);
		PopulateAuto(b, n, k);
	}
	cout << "\n\nAddition of matrices A and B\n\n";
	cout << "\nMatrix A: \n" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < k; j++) {
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
	cout << "\nMatrix B: \n" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < k; j++) {
			cout << b[i][j] << " ";
		}
		cout << endl;
	}
	clock_t start, end;
	start = clock();
#pragma omp parallel for num_threads(4)
		for (int i = 0; i < n; i++) {
#pragma omp parallel for
			for (int j = 0; j < k; j++) {
				f[i][j] = a[i][j] + b[i][j];
			}
		}
		end = clock();
		double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
	cout << "\nResultant Matrix: \n" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < k; j++)
		{
			cout << f[i][j] << " ";
		}
		cout << endl;
	}
	cout << "\n\nTime taken by program is : " << fixed << time_taken << endl;

	cin.ignore();
}

void MoveDataBlockLine_A(int** A, int lineNumber)
{
	int tmp[N / 4][N / 4];

	for (int i = 0; i < 1; i++)
		for (int j = 0; j < 1; j++)
			tmp[i][j] = A[i + 1 * lineNumber][j];

	for (int k = 0; k < 3; k++)
	{
		for (int i = 0; i < 1; i++)
			for (int j = 0; j < 1; j++)
				A[i + 1 * lineNumber][j + 1 * k] = A[i + 1 * lineNumber][j + 1 * (k + 1)];
	}

	for (int i = 0; i < 1; i++)
		for (int j = 0; j < 1; j++)
			A[i + 1 * lineNumber][j + 1 * 3] = tmp[i][j];
}

void MoveDataBlockLine_B(int** B, int lineNumber)
{
	int tmp[N / 4][N / 4];

	for (int i = 0; i < 1; i++)
		for (int j = 0; j < 1; j++)
			tmp[i][j] = B[i][j + 1 * lineNumber];

	for (int k = 0; k < 3; k++)
	{
		for (int i = 0; i < 1; i++)
			for (int j = 0; j < 1; j++)
				B[i + 1 * k][j + 1 * lineNumber] = B[i + 1 * (k + 1)][j + 1 * lineNumber];
	}

	for (int i = 0; i < 1; i++)
		for (int j = 0; j < 1; j++)
			B[i + 1 * 3][j + 1 * lineNumber] = tmp[i][j];
}

void MutiplyBlock(int** A, int** B, int** C, int bi, int bj)
{
	
	for (int i = 0; i < 1; i++)
		for (int j = 0; j < 1; j++)
			C[i + 1 *bi][j + 1 * bj] += A[i + 1 * bi][j + 1 * bj] * B[i + 1 * bi][j + 1 * bj];
}

void CannonsTheorum() {
	int l;
	int** A = new int* [N];
	for (int i = 0; i < N; i++)
		A[i] = new int[N];

	int** B = new int* [N];
	for (int i = 0; i < N; i++)
		B[i] = new int[N];

	int** C = new int* [N];
	for (int i = 0; i < N; i++)
		C[i] = new int[N];
	
	cout << "\n\nPress 0 to Manually fill the matrices..\nPress 1 to have the matrices filled automatically..\n ";
	cin >> l;
	if (!l) {
		Populate(A, N, N);
		Populate(B, N, N);
	}
	else {
		PopulateAuto(A, N, N);
		PopulateAuto(B, N, N);
	}
	cout << "\nMatrix A: " << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << A[i][j] << " ";
			C[i][j] = 0;
		}
		cout << endl;
	}

	cout << "\nMatrix B: " << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << B[i][j] << " ";
		}
		cout << endl;
	}
	clock_t start, end;
	start = clock();
	omp_set_num_threads(2);
	if (N % 4 == 0)
	{
#pragma omp parallel shared( A, B, C )  
		{
#pragma omp sections   
			{

#pragma omp section    
				{
					cout << "\n Sections 1, thread number " << omp_get_thread_num();
					MoveDataBlockLine_A(A, 1);
					MoveDataBlockLine_A(A, 2);
					MoveDataBlockLine_A(A, 2);
					MoveDataBlockLine_A(A, 3);
					MoveDataBlockLine_A(A, 3);
					MoveDataBlockLine_A(A, 3);
				}

#pragma omp section  
				{
					cout << "\n Sections 1, thread number " << omp_get_thread_num();
					MoveDataBlockLine_B(B, 1);
					MoveDataBlockLine_B(B, 2);
					MoveDataBlockLine_B(B, 2);
					MoveDataBlockLine_B(B, 3);
					MoveDataBlockLine_B(B, 3);
					MoveDataBlockLine_B(B, 3);
				}
			}
		}
		for (int k = 0; k < 4; k++)
		{
#pragma omp parallel shared( A, B, C )   
			{
#pragma omp sections   
				{
#pragma omp section
					{
						cout << "\n Sections 2, thread number " << omp_get_thread_num();
						for (int i = 0; i < 2; i++)
							for (int j = 0; j < 4; j++)
								MutiplyBlock(A, B, C, i, j);

						MoveDataBlockLine_A(A, 0);
						MoveDataBlockLine_B(B, 0);
						MoveDataBlockLine_A(A, 1);
						MoveDataBlockLine_B(B, 1);
					}

#pragma omp section
					{
						cout << "\n Sections 2, thread number " << omp_get_thread_num();
						for (int i = 2; i < 4; i++)
							for (int j = 0; j < 4; j++)
								MutiplyBlock(A, B, C, i, j);

						MoveDataBlockLine_A(A, 2);
						MoveDataBlockLine_B(B, 2);
						MoveDataBlockLine_A(A, 3);
						MoveDataBlockLine_B(B, 3);
					}
				}
			}
		}
	}
	else
		cout << "\n Error! N % 4 != 0 ! ";
	end = clock();
	double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
	cout << "\n\nResultant Matrix: " << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << C[i][j] << " ";
		}
		cout << endl;
	}
	
	cout << "\n\nTime taken by program is : " << fixed << time_taken<< " sec" <<endl;
}

void matGene(int* A, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			A[i * size + j] = rand() % 15;
		}
	}
}

void vecGene(int* A, int size) {
	for (int i = 0; i < size; i++) {
		A[i] = rand() % 10;
	}
}

void matShow(int* A, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << A[i * size + j] << " ";
		}
		cout << endl;
	}
}

void vecShow(int* A, int size) {
	for (int i = 0; i < size; i++) {
		cout << A[i] << endl;
	}
}

void GuassJordan() {
	int n, l;
	cout << "Please enter the value for n: ";
	cin >> n;
	int* A = new int[n * n + 2];
	int* b = new int[n + 2];
	int* serial_num = new int[n + 2];
	cout << "\n\nPress 0 to Manually fill the Matrix and Vector...\nPress 1 to have the Matrix and Vector automaticlaly filled...";
	cin >> l;
	if (l) {
		matGene(A, n);
		vecGene(b, n);
	}
	else {
		system("CLS");
		cout << "\n\n\nEntering values for Guass-Jordan:\n\nMatrix: \n\n";
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				gotoXY((i+1)*paddingx,(j+7)*paddingy); cin >> A[i * n + j];
			}
		}
		cout << "\n\nEntering values for Vector: \n\n";
		for (int i = 0; i < n; i++) {
			cin >> b[i];
		}
	}
	cout << "\n\nA = " << endl;
	matShow(A, n);
	cout << "\nb = " << endl;
	vecShow(b, n);


	for (int i = 0; i < n; i++) {
		serial_num[i] = -1;
	}

	stack<int> s1;

	int start_time = omp_get_wtime();
	int num_threads = 2;

	for (int j = 0; j < n; j++) {
		int max_coff = 0;
		int max_index;
		for (int i = 0; i < n; i++) {
			if (serial_num[i] == -1 && abs(A[i * n + j]) > abs(max_coff)) {
				max_coff = A[i * n + j];
				max_index = i;
			}
		}
		serial_num[max_index] = j;
		s1.push(max_index);
#pragma omp parallel for num_threads(num_threads)
		for (int i = 0; i < n; i++) {
			if (serial_num[i] == -1) {
				int tmp_coff = A[i * n + j] / A[max_index * n + j];
				A[i * n + j] = 0;
				for (int k = j + 1; k < n; k++) {
					A[i * n + k] -= tmp_coff * A[max_index * n + k];
				}
				b[i] -= tmp_coff * b[max_index];
			}
		}
	}

	int* result = new int[n + 2];

	for (int j = n - 1; j >= 0; j--) {
		int this_index = s1.top();
		s1.pop();
		serial_num[this_index] = -1;
#pragma omp parallel for num_threads(num_threads)
		for (int i = 0; i < n; i++) {
			if (serial_num[i] != -1) {
				int tmp_coff = A[i * n + j] / A[this_index * n + j];
				A[i * n + j] = 0;
				b[i] -= tmp_coff * b[this_index];
			}
		}
		b[this_index] /= A[this_index * n + j];
		A[this_index * n + j] = 1;
		result[j] = b[this_index];
	}

	cout << "\nResultant matrix : \n" << endl;
		matShow(A, n);
	cout << "\nResultant Vector values: \n" << endl;
	vecShow(result, n);

	cout << "\n\n\n\nTime elapsed: " << omp_get_wtime() - start_time << endl;


}

void SimpleMatrixMultiplication() {
	int n1,n2,k1,k2,l;
	int s;
	int thread_num;
	int wtime;
	thread_num = omp_get_max_threads();

	cout << "Please enter the value of the dimensions";
	cout << "\nMatrix A: ";
	cin >> n1>>k1;

	cout << "\nMatrix B: ";
	cin >> n2 >> k2;
	int** a = new int* [n1];
	for (int i = 0; i < n1; i++)
		a[i] = new int[k1];

	int** b = new int* [n2];
	for (int i = 0; i < n2; i++)
		b[i] = new int[k2];

	if (k1 != n2) {
		cout << "Incorrect dimensions!" << endl;
		return;
	}

	int** c = new int* [n1];
	for (int i = 0; i < k2; i++)
		c[i] = new int[k2];

	cout << "\n\nPress 0 to Manually fill the matrices..\nPress 1 to have the matrices filled automatically..\n ";
	cin >> l;

	if (!l) {
		Populate(a, n1, k1);
		Populate(b, n2, k2);
	}
	else {
		cout << "Matrix A: "; PopulateAuto(a, n1, k1);
		cout << "Matrix B: "; PopulateAuto(b, n2, k2);
	}

	cout << "\nProcessors available: " << omp_get_num_procs();
	cout << "\nThreads available: " << thread_num;
	clock_t start, end;


	start = clock();

# pragma omp parallel shared ( a, b, c, n1 ,n2, k1, k2 ) 
	{
# pragma omp for
		for (int i = 0; i < n1; i++)
		{
			for (int j = 0; j < k2; j++)
			{
				c[i][j] = 0.0;
				for (int k = 0; k < k1; k++)
				{
					c[i][j] = c[i][j] + a[i][k] * b[k][j];
				}
			}
		}

	}
	cout << "\nMatrix A: " << endl;

	for (int i = 0; i < n1; i++) {
		for (int j = 0; j < k1; j++) {
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
	cout << "\nMatrix B: " << endl;

	for (int i = 0; i < n2; i++) {
		for (int j = 0; j < k2; j++) {
			cout << b[i][j] << " ";
		}
		cout << endl;
	}
	cout << "\nResultant matrix: " << endl;

	for (int i = 0; i < n1; i++) {

		for (int j = 0; j < k2; j++) {

			cout << c[i][j] << " ";
		}
		cout << endl;
	}
	end = clock();
	double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
	cout << "\n\nTime taken by program is : " << fixed << time_taken << " sec" << endl;
	cout << endl;
	cin.ignore();
}

int main()
{
	int menu_item = 0, run, x = 7;
	bool running = true;
	gotoXY(1, 7); cout << "->";

	while (running)
	{

		gotoXY(0, 2); cout << "   -----------Matrix Calculator------------";
		gotoXY(18, 5); cout << "Main Menu";
		gotoXY(3, 7);  cout << "1) Simple Matrix Multiplication";
		gotoXY(3, 8);  cout << "2) Simple Matrix Addition";
		gotoXY(3, 9);  cout << "3) Matrix Multiplication through Cannon's Theorem";
		gotoXY(3, 10); cout << "4) Guass-Jordan Elimination";
		gotoXY(3, 11); cout << "5) Credits";
		gotoXY(3, 12); cout << "Quit Program";

		system("pause>nul"); // the >nul bit causes it the print no message

		if (GetAsyncKeyState(VK_DOWN) && x != 12) //down button pressed
		{

			gotoXY(1, x); cout << "  ";
			x++;
			gotoXY(1, x); cout << "->";
			menu_item++;
			continue;

		}

		if (GetAsyncKeyState(VK_UP) && x != 7) //up button pressed
		{

			gotoXY(1, x); cout << "  ";
			x--;
			gotoXY(1, x); cout << "->";
			menu_item--;
			continue;
		}

		if (GetAsyncKeyState(VK_RETURN)) { // Enter key pressed

			switch (menu_item) {

			case 0: {

				system("CLS");
				cout << "\n\n\nYou chose Matrix Multiplication...     " << endl;;
				SimpleMatrixMultiplication();
				cin.ignore();
				system("CLS");
				break;
			}


			case 1: {
				system("CLS");
				cout << "\n\n\nYou chose Matrix Addition" << endl;;
				MatrixAddition();
				cin.ignore();
				system("CLS");
				break;
				
			}

			case 2: {
			
				system("CLS");
				cout << "\n\n\nYou chose Cannons theorem...     " << endl;;
				CannonsTheorum();
				cin.ignore();
				cin.ignore();
				system("CLS");
				break;
			}

			case 3: {
				system("CLS");
				cout << "\n\n\nYou chose Guass-Jordan Elimination...     " << endl;
				GuassJordan();
				cin.ignore();
				cin.ignore();
				system("CLS");
				break;
		
			}

			case 4: {
				system("CLS");
				cout << "\n\nTerm project for Parallel and Distributed Computing\n---------------------------------------------------\nTeam Members: \n-)Aneeb Asif        18k-1129\n-)Irza Kamran Khan  18k-1097\n-)Hasan Burney      18k-0278\n\n\n\n\n\n";
				cin.ignore();
				system("CLS");
				break;
			}
			
			case 5: {
				cout << "\n\n\nExiting the Program" << endl;
				return 0;
			}
			}

		}

	}
	return 0;
}

