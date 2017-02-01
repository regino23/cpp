#include<iostream>
#include<ctime>
using namespace std;

class DoubleMatrix
{
private:
	int row = 0;
	int col = 0;
	double** arr = nullptr;

public:
	DoubleMatrix() = default;

	DoubleMatrix(int row_, int col_)
		:row(row_), col(col_), arr(new double*[row])
	{
		for (int i = 0; i < row; ++i)
			arr[i] = new double[col];
	}

	DoubleMatrix(const DoubleMatrix & obj)
		:DoubleMatrix(obj.row, obj.col)
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; ++j)
				arr[i][j] = obj.arr[i][j];
		}
	}

	DoubleMatrix(DoubleMatrix && obj)
		:arr(obj.arr), row(obj.row), col(obj.col)
	{
		obj.arr = nullptr;
		obj.row = 0;
		obj.col = 0;
	}

	const DoubleMatrix& operator=(const DoubleMatrix & obj)
	{
		if (this != &obj)
		{
			if (arr != nullptr)
			{
				for (int i = 0; i < row; i++)
					delete[] arr[i];
				delete[] arr;
			}
			arr = new double*[obj.row];
			for (int i = 0; i < obj.row; ++i)
				arr[i] = new double[obj.col];
			col = obj.col;
			row = obj.row;
			for (int i = 0; i < row; ++i)
			{
				for (int j = 0; j < col; ++j)
					arr[i][j] = obj.arr[i][j];
			}
		}
		return *this;
	}

	DoubleMatrix& random(int ran, int from = 0)
	{
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
				arr[i][j] = rand() % ran + from;
		}
		return *this;
	}

	DoubleMatrix operator + (const DoubleMatrix & obj)
	{
		DoubleMatrix sum(row, col);
		if (col == obj.col && row == obj.row)
		{
			for (int i = 0; i < row; ++i)
			{
				for (int j = 0; j < col; ++j)
					sum.arr[i][j] = obj.arr[i][j] + arr[i][j];
			}
			return sum;
		}
		else
			cout << "Different sizes of matrices. Returned first matrix." << endl;
		return *this;
	}

	void operator += (const DoubleMatrix & obj)
	{
		if (col == obj.col && row == obj.row)
		{
			*this = *this + obj;
		}
		else
			cout << "Different sizes of matrices." << endl;
	}

	DoubleMatrix operator - (const DoubleMatrix & obj)
	{
		DoubleMatrix sum(row, col);
		if (col == obj.col && row == obj.row)
		{
			for (int i = 0; i < row; ++i)
			{
				for (int j = 0; j < col; ++j)
					sum.arr[i][j] = arr[i][j] - obj.arr[i][j];
			}
			return sum;
		}
		else
			cout << "Different sizes of matrices. Returned first matrix." << endl;
		return *this;
	}

	void operator -= (const DoubleMatrix & obj)
	{
		if (col == obj.col && row == obj.row)
			*this = *this - obj;
		else
			cout << "Different sizes of matrices." << endl;
	}

	DoubleMatrix operator*(const DoubleMatrix& obj)
	{
		DoubleMatrix compos(row, obj.col);
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < obj.col; ++j)
				compos.arr[i][j] = 0;
		}
		if (col == obj.row)
		{
			for (int i = 0; i < row; ++i)
			{
				for (int j = 0; j < obj.col; ++j)
				{
					for (int n = 0; n < col; ++n)
						compos.arr[i][j] += arr[i][n] * obj.arr[n][j];
				}
			}
			return compos;
		}

		else
			cout << "Different sizes of matrices. Returned initial matrix." << endl;
		return *this;
	}

	DoubleMatrix& operator*=(const DoubleMatrix& obj)
	{
		*this = *this * obj;
		return *this;
	}

	DoubleMatrix& operator*=(double nom)
	{
		*this = *this * nom;
		return *this;
	}

	DoubleMatrix operator*(double nomber)
	{
		DoubleMatrix compos(row, col);
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				compos.arr[i][j] = arr[i][j] * nomber;
			}
		}
		return compos;
	}

	DoubleMatrix operator/(double nomber)
	{
		if (nomber == 0){
			cout << "Can not devide by 0. Returned initial matrix." << endl;
			return *this;
		}
		else
			return *this * (1 / nomber);
	}


	DoubleMatrix operator/(DoubleMatrix& obj)
	{
		if(!this->is_square())
		{
			cout << "Can not be devided. Returned initial matrix." << endl;
			return *this;
		}
		else
			return *this * obj.reverse();
	}

	DoubleMatrix& operator/=(double nom)
	{
		*this = *this / nom;
		return *this;
	}

	DoubleMatrix& operator/=(DoubleMatrix& obj)
	{
		*this = *this / obj;
		return *this;
	}

	bool operator==(const DoubleMatrix& obj)
	{
		if (obj.col != col || obj.row != row)
			return false;
		else
		{
			for (int i = 0; i < row; ++i)
			{
				for (int j = 0; j < col; ++j)
				if (obj.arr[i][j] != arr[i][j])
					return false;
			}
		}
		return true;
	}

	bool operator!=(const DoubleMatrix& obj)
	{
		return !(*this == obj);
	}

	bool is_square()
	{
		return col == row;
	}

	bool is_null()
	{
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
			if (arr[i][j] != 0)
				return false;
		}
		return true;
	}

	bool is_diagonal()
	{
		if (this->is_square())
		{
			for (int i = 0; i < row; ++i)
			{
				for (int j = 0; j < col; ++j)
				if (arr[i][j] != 0 && i != j)
					return false;
			}
			return true;
		}
		return false;
	}

	bool is_unit()
	{
		if (this->is_square())
		{
			for (int i = 0; i < row; ++i)
			{
				if (arr[i][i] != 1)
					return false;
				for (int j = 0; j < col; ++j)
				{
					if (arr[i][j] != 0 && i != j)
						return false;
				}
			}
			return true;
		}
		return false;
	}

	bool is_symmetric()
	{
		if (this->is_square())
		{
			for (int i = 0; i < row; ++i)
			{
				for (int j = i + 1; j < col; ++j)
				{
					if (arr[i][j] != arr[j][i])
						return false;
				}
			}
			return true;
		}
		return false;
	}

	bool is_up_triang()
	{
		if (this->is_square())
		{
			for (int i = 0; i < row; ++i)
			{
				for (int j = 0; j < i; ++j)
				{
					if (arr[i][j] != 0)
						return false;
				}
			}
			return true;
		}
		return false;
	}

	bool is_low_triang()
	{
		if (this->is_square())
		{
			for (int i = 0; i < row; ++i)
			{
				for (int j = i + 1; j < col; ++j)
				{
					if (arr[i][j] != 0)
						return false;
				}
			}
			return true;
		}
		return false;
	}

	DoubleMatrix transpose()
	{
		DoubleMatrix tranM(col, row);
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
				tranM.arr[j][i] = arr[i][j];
		}
		return tranM;
	}

	DoubleMatrix power(int power)
	{
		DoubleMatrix powM = *this;
		if (this->is_square()){
			if (power == 0){
				for (int i = 0; i < row; ++i)
				{
					for (int j = 0; j < col; ++col)
					{
						if (i == j)
							arr[i][j] = 1;
						else
							arr[i][j] = 0;
					}
				}
			}
			else 
			for (int i = 1; i < power; ++i)
				powM *= *this;
		}
		else
			std::cout << "Matrix size are not equal!" << std::endl;

		return powM;
	}

	DoubleMatrix reverse() 
	{
		DoubleMatrix cofM(row - 1, col - 1);
		DoubleMatrix powM(row, col);
		double cof = 0, det = this->determinant();
		if (this->is_square() && det != 0)
		{
			for (int i = 0; i < col*col; ++i)
			{
				for (int j = 0; j < col - 1; ++j)
				{
					for (int k = 0; k < row - 1; ++k)
					{
						if (i % col <= j && i / row <= k)
							cofM.arr[k][j] = arr[k + 1][j + 1];
						if (i % col > j && i / row <= k)
							cofM.arr[k][j] = arr[k + 1][j];
						if (i % col <= j && i / row > k)
							cofM.arr[k][j] = arr[k][j + 1];
						if (i % col > j && i / row > k)
							cofM.arr[k][j] = arr[k][j];
					}
				}
				powM.arr[i / row][i % col] = cofM.determinant()*pow(-1, i % col + i / row);
			}
			powM.transpose();
			powM *= (1 / det);
		}
		else
		{
			cout << "Does not exist reverse matrix. Return original matrix." << endl;
			return *this;
		}
		return powM;
	}

	double determinant()
	{
		double det = 0;
		if (this->is_square())
		{
			if (col == 1)
				det = arr[0][0];
			else if (col == 2)
				det = arr[0][0] * arr[1][1] - arr[1][0] * arr[0][1];
			else
			{
				DoubleMatrix minor(col - 1, col - 1);
				for (int i = 0; i < col; ++i)
				{
					for (int j = 0; j < col - 1; ++j)
					{
						for (int k = 0; k < row - 1; ++k)
						{
							if (j >= i)
								minor.arr[k][j] = arr[k + 1][j + 1];
							else
								minor.arr[k][j] = arr[k + 1][j];
						}
					}
					det += pow(-1, i) * arr[0][i] * minor.determinant();
				}
			}
		}
		else
			cout << "Matrix is not square. Return 0;" << endl;
		return det;
	}

	double norm_square()
	{
		double norm = 0;
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
				norm += pow(arr[i][j], 2);
		}
		norm = sqrt(norm);
		return norm;
	}

	double norm_row()
	{
		double norm = 0, sumRow = 0;
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
				sumRow += abs(arr[i][j]);
			if (norm < sumRow)
			{
				norm = sumRow;
				sumRow = 0;
			}
		}
		return norm;
	}

	double norm_col()
	{
		double norm = 0, sumCol = 0;
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
				sumCol += abs(arr[j][i]);
			if (norm < sumCol)
			{
				norm = sumCol;
				sumCol = 0;
			}
		}
		return norm;
	}

	~DoubleMatrix()
	{
		for (int i = 0; i < row; ++i)
			delete[] arr[i];
		delete[] arr;
	}

	friend ostream& operator<<(ostream& os, const DoubleMatrix& obj);
	friend istream& operator>>(istream& is, const DoubleMatrix& obj);
};

ostream& operator<<(ostream& os, const DoubleMatrix& obj)
{
	for (int i = 0; i < obj.row; ++i)
	{
		for (int j = 0; j < obj.col; ++j)
			os << obj.arr[i][j] << "  ";
		os << endl;
	}
	return os;
}

istream& operator >> (istream& is, const DoubleMatrix& obj)
{
	for (int i = 0; i < obj.row; ++i)
	{
		for (int j = 0; j < obj.col; ++j)
			is >> obj.arr[i][j];
	}
	return is;
}

void typeM(DoubleMatrix& obj)
{
	cout << boolalpha << "Square matrix = " << obj.is_square() << endl;
	cout << boolalpha << "Diagonal matrix = " << obj.is_diagonal() << endl;
	cout << boolalpha << "Zero matrix = " << obj.is_null() << endl;
	cout << boolalpha << "Unit matrix = " << obj.is_unit() << endl;
	cout << boolalpha << "Symmetric matrix = " << obj.is_symmetric() << endl;
	cout << boolalpha << "Low triangular matrix = " << obj.is_low_triang() << endl;
	cout << boolalpha << "Top triangular matrix = " << obj.is_up_triang() << endl;
}

void menu()
{
	int col, row, var;
	cout << "Enter the quantity of rows and columns in the first matrix. " << endl; 
	cin >> row >> col;
	DoubleMatrix mat1(row, col);
	cout << "Enter the quantity of rows and columns in the second matrix. " << endl;
	cin >> row >> col;
	DoubleMatrix mat2(row, col);

	cout << "1. Create two matrices randomly." << endl;
	cout << "2. Create two matrices manually." << endl;
	cin >> var;
	do
	{
		switch (var)
		{
		case 1:
		{
				  mat1.random(100);
				  mat2.random(100);
				  break;
		}
		case 2:
		{
				  cout << "Enter values of the first matrix. " << endl;
				  cin >> mat1;
				  cout << "Enter values of the second matrix. " << endl;
				  cin >> mat2;
				  break;
		}
		default: cout << "Option missing." << endl;
		}
	}	while (var != 1 && var != 2);
	bool con = true;
	while (con)
	{
		cout << "Matrix 1:" << endl;
		cout << mat1 << endl;
		cout << "Matrix 2:" << endl;
		cout << mat2 << std::endl;
		cout << "Select the operation:" << endl;
		cout << "1. + " << endl;
		cout << "2. - " << endl;
		cout << "3. += " << endl;
		cout << "4. -= " << endl;
		cout << "5. * " << endl;
		cout << "6. * the number" << endl;
		cout << "7. *= " << endl;
		cout << "8. *= the number" << endl;
		cout << "9. / " << endl;
		cout << "10. / the number" << endl;
		cout << "11. /= " << endl;
		cout << "12. /= the number" << endl;
		cout << "13. == " << endl;
		cout << "14. != " << endl;
		cout << "15. Inverse matrix " << endl;
		cout << "16. Transposed matrix " << endl;
		cout << "17. Power matrix " << endl;
		cout << "18. Determinant" << endl;
		cout << "19. Norms of matrix " << endl;
		cout << "20. Check the type of matrix " << endl;
		cout << "21. Exit program " << endl;
		cin >> var;
		switch (var)
		{
		case 1:
		{
				  cout << "Result:" << endl;
				  cout << mat1 + mat2;
				  break;
		}
		case 2:
		{
				  cout << "Result:" << endl;
				  cout << mat1 - mat2;
				  break;
		}
		case 3:
		{
				  cout << "Result:" << endl;
				  mat1 += mat2;
				  cout << mat1 << endl;
				  break;
		}
		case 4:
		{
				  cout << "Result:" << endl;
				  mat1 -= mat2;
				  cout << mat1 << endl;
				  break;
		}
		case 5:
		{
				  cout << "Result:" << endl;
				  cout << mat1 * mat2;
				  break;
		}
		case 6:
		{
				  double num;
				  cout << "Enter number:" << endl;
				  cin >> num;
				  cout << "Result:" << endl;
				  cout << mat1 * num;
				  break;
		}
		case 7:
		{
				  cout << "Result:" << endl;
				  mat1 *= mat2;
				  cout << mat1;
				  break;
		}
		case 8:
		{
				  double num;
				  cout << "Enter number:" << endl;
				  cin >> num;
				  cout << "Result:" << endl;
				  mat1 *= num;
				  cout << mat1;
				  break;
		}
		case 9:
		{
				  cout << "Result:" << endl;
				  cout << mat1 / mat2;
				  break;
		}
		case 10:
		{
				  double num;
				  cout << "Enter number:" << endl;
				  cin >> num;
				  cout << "Result:" << endl;
				  cout << mat1 / num;
				  break;
		}
		case 11:
		{
				  cout << "Result:" << endl;
				  mat1 /= mat2;
				  cout << mat1;
				  break;
		}
		case 12:
		{
				  double num;
				  cout << "Enter number:" << endl;
				  cin >> num;
				  cout << "Result:" << endl;
				  mat1 /= num;
				  cout << mat1;
				  break;
		}
		case 13:
		{
				  cout << "Result:" << endl;
				  cout << (mat1 == mat2);
				  break;
		}
		case 14:
		{
				   cout << "Result:" << endl;
				   cout << (mat1 != mat2);
				   break;
		}
		case 15:
		{
				   int var;
				   cout << "1. Inverse first matrix." << endl;
				   cout << "2. Inverse second matrix." << endl;
				   cin >> var;
				   switch (var)
				   {
				   case 1: cout << "Result:" << endl; cout << mat1.reverse(); break;
				   case 2: cout << "Result:" << endl; cout << mat1.reverse(); break;
				   default: cout << "Option missing." << endl;
				   }
				   break;
		}
		case 16:
		{
				   int var;
				   cout << "1. Transpose first matrix." << endl;
				   cout << "2. Transpose second matrix." << endl;
				   cin >> var;
				   switch (var)
				   {
				   case 1: cout << "Result:" << endl; cout << mat1.transpose(); break;
				   case 2: cout << "Result:" << endl; cout << mat1.transpose(); break;
				   default: cout << "Option missing." << endl;
				   }
				   break;
		}
		case 17:
		{
				   int var, pow;
				   cout << "1. Power first matrix." << endl;
				   cout << "2. Power second matrix." << endl;
				   cin >> var;
				   cout << "Enter the power:" << endl;
				   cin >> pow;
				   switch (var)
				   {
				   case 1: cout << "Result:" << endl; cout << mat1.power(pow); break;
				   case 2: cout << "Result:" << endl; cout << mat1.power(pow); break;
				   default: cout << "Option missing." << endl;
				   }
				   break;
		}
		case 18:
		{
				   int var;
				   cout << "1. Find determinant of the first matrix." << endl;
				   cout << "2. Find determinant of the second matrix." << endl;
				   cin >> var;
				   switch (var)
				   {
				   case 1: cout << "Result:" << endl; cout << mat1.determinant(); break;
				   case 2: cout << "Result:" << endl; cout << mat1.determinant(); break;
				   default: cout << "Option missing." << endl;
				   }
				   break;
		}
		case 19:
		{
				   int var;
				   cout << "1. Find norms of the first matrix." << endl;
				   cout << "2. Find norms of the second matrix." << endl;
				   cin >> var;
				   switch (var)
				   {
				   case 1:
				   {
							 cout << "Norm by rows:" << endl; cout << mat1.norm_row();
							 cout << "Norm by columns:" << endl; cout << mat1.norm_col();
							 cout << "The Euclidean norm: " << endl; cout << mat1.norm_square();
							 break;
				   }
				   case 2:
				   {
							 cout << "Norm by rows:" << endl; cout << mat2.norm_row();
							 cout << "Norm by columns:" << endl; cout << mat2.norm_col();
							 cout << "The Euclidean norm: " << endl; cout << mat2.norm_square();
							 break;
				   }
				   default: cout << "Option missing." << endl;
				   }
				   break;
		}
		case 20:
		{
				   int var;
				   cout << "1. First matrix." << endl;
				   cout << "2. Second matrix." << endl;
				   cin >> var;
				   switch (var)
				   {
				   case 1: cout << "Result for the first matrix:" << endl; typeM(mat1); break;   
				   case 2: cout << "Result for the second matrix:" << endl; typeM(mat2); break;
				   default: cout << "Option missing." << endl;
				   } 
				   break;
		}
		default: {con = false; break; }
		}
		cout << "Continue?" << endl;
		cout << "1. Yes" << endl;
		cout << "2. No" << endl;
		cin >> var;
		switch (var)
		{
		case 1: system("cls"); break;
		default: exit(1);
		}
	}
}

int main()
{
	srand(time(NULL));
	menu();

	return 0;
}