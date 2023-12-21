//Метод конечных разностей
#include <iostream> 
#include <cmath>
#include <vector> 

std::vector<std::vector<double>> matrix_A(int n, double h) 
{
	std::vector<std::vector<double>> matrix;
	
	for (int i = 0; i != n; i++)
	{
		std::vector<double> v;
		for (int j = 0; j != n; j++)
		{
			v.push_back(0.0);
		}
		matrix.push_back(v);
	}
	
	for (int i = 0; i != n; i++)
	{
		for (int j = 0; j != n; j++)
		{
			if (i == j){
				matrix[i][j] = 2.0/(h*h);
			} else if (i == j + 1 || i == j - 1){
				 matrix[i][j] = -1.0/(h*h);
			} else {
				matrix[i][j] = 0.0;
			}
		}
	}
	
	matrix[0][0] = 1.0;
	matrix[0][1] = 0.0;
	matrix[10][9] = 0.0;
	matrix[10][10] = 1.0;
	
	std::cout << "Matrix A:" << "\n";
	for(int i = 0; i != n; i++)
		{
			for(int j = 0; j != n; j++)
				{
					std::cout << matrix[i][j] << "\t\t";
				}
			std::cout << "\n";	
		}
	
	return matrix;
}


std::vector<std::vector<double>> inv_matrix_A(int n, std::vector<std::vector<double>> matrix) //нахождение обратной матрицы
{
	std::vector<std::vector<double>> inv_matrix;
	
	for (int i = 0; i != n; i++)//делаем обратную матрицу изначально единичной
		{
			std::vector<double> v;
			for (int j = 0; j != n; j++)
				{
					v.push_back((i == j) ? 1.0 : 0.0); //т.е равно 1, если i == j, иначе равно 0
				}
			inv_matrix.push_back(v);

		}
		
		
	for (int k = 0; k != n; k++)//приводим матрицу к верхнетреугольной
		{
			for (int i = k + 1; i != n; i++)
				{
					double temp = matrix[i][k] / matrix[k][k];
					for (int j = 0; j != n; j++)
						{
							matrix[i][j] -= temp * matrix[k][j];
							inv_matrix[i][j] -= temp * inv_matrix[k][j];
						}
				}
		}
	
		
	for (int k = n - 1; k > 0; k--)//далее зануляем все, что выше главной диагонали
		{
			for (int i = k - 1; i >= 0; i--)
				{
					double temp = matrix[i][k] / matrix[k][k];
					for (int j = 0; j != n; j++)
						{
							matrix[i][j] -= temp * matrix[k][j];
							inv_matrix[i][j] -= temp * inv_matrix[k][j];
						}
				}
		}
		
		
	for (int i = 0; i != n; i++)//делим на элементы главной диагонали
		{
			for (int j = 0; j != n; j++)
				{
					inv_matrix[i][j] /= matrix[i][i];
				}
		}

	std::cout << "Inverse matrix A^-1:" << "\n";
	for(int i = 0; i != n; i++)
		{
			for(int j = 0; j != n; j++)
				{
					std::cout << inv_matrix[i][j] << "\t\t";
				}
			std::cout << "\n";	
		}
		
	std::cout << "\n";	
		
	return inv_matrix;
}


std::vector<double> vector_(int n, double h)
{
	std::vector<double> vec(n);
	vec[0] = 0;	
	for (int i = 1; i != n-1; i++)
	{
		vec[i] = sin(i*h) - (i*h)*(i*h)*(i*h);	
	}
	vec[n-1] = 1;
		
	for(int i = 0; i != n; i++)
		{
			std::cout << "vec[" << i << "]= " << vec[i] << "\n";	
		}
	std::cout << "\n";

	return vec;
}


std::vector<double> vec_u(int n, std::vector<std::vector<double>>& inv_matrix, std::vector<double>& vec)
{
	std::vector<double> u;
	
	for (auto& v: inv_matrix)
	{
		double temp = 0.0;
		for(int j = 0; j != n; j++) 
		{
			temp += v[j] * vec[j];
		}
		u.push_back(temp);
	}
	
	for(int i = 0; i != n; i++)
		{
			std::cout << "u[" << i << "]= " << u[i] << "\n";	
		}
		std::cout << "\n";
		std::cout << "/////////////////////////////////////////////////////////////////////////////////////////////////////////////" << "\n";
		
	return u;
}

//начинаем след шаг итерации
std::vector<double> vector1_(int n, double h, std::vector<double>& u)
{
	std::vector<double> vec1(n);
	vec1[0] = 0;	
	for (int i = 1; i != n-1; i++)
	{
		vec1[i] = sin(i*h) - u[i]*u[i]*u[i];	
	}
	vec1[n-1] = 1;
		
	for(int i = 0; i != n; i++)
		{
			std::cout << "vec1[" << i << "]= " << vec1[i] << "\n";	
		}
	std::cout << "\n";

	return vec1;
}

std::vector<double> vec1_u(int n, std::vector<std::vector<double>>& inv_matrix, std::vector<double>& vec1)
{
	std::vector<double> u1;
	
	for (auto& v: inv_matrix)
	{
		double temp = 0.0;
		for(int j = 0; j != n; j++) 
		{
			temp += v[j] * vec1[j];
		}
		u1.push_back(temp);
	}
	
	for(int i = 0; i != n; i++)
		{
			std::cout << "u1[" << i << "]= " << u1[i] << "\n";	
		}
		std::cout << "\n";
	return u1;
}

double dist (int n, double h, std::vector<double>& u, std::vector<double>& u1)
{
	double sum = 0.0;
	for (int i = 0; i != n; i++)
		{ 
			sum += h*(u1[i]-u[i])*(u1[i]-u[i]);
		}
	return sum;
} 

int main()
{
	int n = 11;
	double h = 0.1;
	
	std::vector<std::vector<double>> matrix = matrix_A(n, h) ;
	std::vector<std::vector<double>> inv_matrix = inv_matrix_A(n, matrix);
	std::vector<double> vec = vector_(n, h);
	std::vector<double> u = vec_u(n, inv_matrix, vec);


	std::vector<double> vec1 = vector1_(n, h, u);
	std::vector<double> u1 = vec1_u(n, inv_matrix, vec1);
	
	//double d = 0.0;
	//d = dist (n, h, u, u1);
	//std::cout << "d = " << d << "\n\n";	
	
	while (dist (n, h, u, u1) >= 1.e-6)
	{
		u = u1;
		//for(int i = 0; i != n; i++)
		//{
		//	std::cout << "u[" << i << "]= " << u[i] << "\n";	
		//}
		//std::cout << "\n";
		
		//for(int i = 0; i != n; i++)
		//{
		//	std::cout << "u1[" << i << "]= " << u1[i] << "\n";	
		//}
		//std::cout << "\n";

		vec1 = vector1_(n, h, u);
		u1 = vec1_u(n, inv_matrix, vec1);	
	}
	
	//d = dist (n, h, u, u1);
	//std::cout << "d = " << d << "\n\n";
	
	return 0;
}
