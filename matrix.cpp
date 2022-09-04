#include "matrix.h"


Matrix::Matrix(int row, int col, bool randomFill) {
	this->w = row;
	this->k = col;
	this->m = new double* [row];
	for (int i = 0; i < row; ++i) {
		this->m[i] = new double [col];
	}

	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			this->m[i][j] = randomFill ? randomDouble(0., 9.99) : 0.;
		}
	}
}

Matrix::Matrix(const Matrix& copy) { // konstruktor kopiujacy - kopiuje macierz "copy" do macierzy "this"
	this->w = copy.w; // "this" to nowy obiekt do ktorego kopiujemy wszystko z obiektu copy
	this->k = copy.k;
	this->m = new double* [this->w]; // deklarujemy nowa macierz
	for (int row = 0; row < this->w; ++row) {
		this->m[row] = new double [this->k]; // dla kazdego wiersza w starej macierzy tworzymy wiersz w nowej macierzy
		std::memcpy(this->m[row], copy.m[row], sizeof(double) * this->k); // i kopiujemy kazdy wiersz
	}
}

Matrix::~Matrix() {
	for (int row = 0; row < this->w; ++row) {
		delete [] this->m[row]; // usuwa kazdy wiersz dynamicznej tablicy na wiersze macierzy
	}
	delete [] this->m; // usuwa dynamiczna tablice na macierz
}

int Matrix::getW() const {
	return this->w;
}

int Matrix::getK() const {
	return this->k;
}

double Matrix::getFromPosition(int w, int k) const {
	if (w >= this->w || k >= this->k || w < 0 || k < 0) {
		throw std::invalid_argument("invalid coordinates!");
	}
	return this->m[w][k];
}

Matrix& Matrix::setAtPosition(int w, int k, double value) {
	if (w >= this->w || k >= this->k || w < 0 || k < 0) {
		throw std::invalid_argument("invalid coordinates!");
	}

	this->m[w][k] = value;

	return *this;
}

bool Matrix::isSameSize(const Matrix &rhs) const {
	return this->w == rhs.w && this->k == rhs.k;
}

bool Matrix::operator==(const Matrix &rhs) const {
	if (!this->isSameSize(rhs)) {
		return false;
	}

	for (int row = 0; row < this->w; ++row) {
		for (int col = 0; col < this->k; ++col) {
			if (this->m[row][col] != rhs.m[row][col]) {
				return false;
			}
		}
	}
	return true;
}

Matrix& Matrix::operator=(const Matrix &rhs) { // podobne do kontruktora kopiujacego
	this->w = rhs.w;
	this->k = rhs.k;

	for (int row = 0; row < this->w; ++row) {
		std::memcpy(this->m[row], rhs.m[row], sizeof(double) * this->k); // kopiowanie kazdego wiersza do nowego obiektu
	}

	return *this;
}

Matrix Matrix::operator+(const Matrix &rhs) const { // przeciazenie operatora
	if (!this->isSameSize(rhs)) {
		throw std::invalid_argument("unable to add matrices with different sizes!");
	}

	Matrix result(this->w, this->k);

	for (int row = 0; row < w; ++row) {
		for (int col = 0; col < k; ++col) {
			result.m[row][col] = this->m[row][col] + rhs.m[row][col];
		}
	}

	return result;
}

Matrix Matrix::operator-(const Matrix &rhs) const {
	if (!this->isSameSize(rhs)) {
		throw std::invalid_argument("unable to subtract matrices with different sizes!");
	}

	Matrix result(this->w, this->k);

	for (int row = 0; row < this->w; ++row) {
		for (int col = 0; col < this->k; ++col) {
			result.m[row][col] = this->m[row][col] - rhs.m[row][col];
		}
	}

	return result;
}

Matrix Matrix::operator*(const Matrix &rhs) const {
	if (this->k != rhs.w) { // macierze mozna przemnozyc <=> liczba kolumn macierzy A jest rowna liczbie wierszy macierzy B
		throw std::invalid_argument("unable to multiplicate matrices");
	}  

	Matrix result(this->w, rhs.k);

   // mnozenie maciezy
	for (int row = 0; row < this->w; row++) {
		for (int col = 0; col < rhs.k; col++) {
			double sum = 0;
			for (int inner = 0; inner < this->k; inner++) {
				sum += this->m[row][inner] * rhs.m[inner][col];
			}
			result.m[row][col] = sum;
		}
	}

	return result;
}

Matrix Matrix::operator*(const double &num) const {
	Matrix result(this->w, this->k);

   // przemnazam kazda liczbe w macierzy razy liczbe num
	for (int row = 0; row < this->w; row++) {
		for (int col = 0; col < this->k; col++) {
			result.m[row][col] = this->m[row][col] * num;
		}
	}

	return result;
}

Matrix Matrix::operator^(const int &n) const {
	if (this->w != this->k) {
		throw std::invalid_argument("unable to raise matrices to power");
	}

	if (n <= 0) {
		throw std::invalid_argument("unable to raise matrix to a non-positive power!");
	}

	Matrix tmp = *this;


	for (int i = 0; i < n - 1; ++i) {
		tmp = tmp * (*this);
	}

	return tmp;
}

Matrix Matrix::swapRows(const int& r1, const int& r2) {
	if (r1 >= this->w || r2 >= this->w || r1 < 0 || r2 < 0) {
		throw std::invalid_argument("invalid rows' numbers!");
	}

	Matrix res = *this;

	std::swap(res.m[r1], res.m[r2]);

	return res;
}

Matrix Matrix::swapCols(const int& c1, const int& c2) {
	if (c1 >= this->k || c2 >= this->k || c1 < 0 || c2 < 0) {
		throw std::invalid_argument("invalid columns' numbers!");
	}

	Matrix res = *this;

	for (int row = 0; row < this->w; ++row) {
		std::swap(res.m[row][c1], res.m[row][c2]);
	}

	return res;
}

Matrix& Matrix::print() {
	std::cout << *this << '\n';
	return *this;
}

std::ostream& operator<<(std::ostream &out, const Matrix &rhs) {
	for (int row = 0; row < rhs.w; ++row) {
		for (int col = 0; col < rhs.k; ++col) {
			out << std::fixed << std::setprecision(2) << rhs.getFromPosition(row, col) << '\t';
		}
		out << '\n';
	}
   
	return out;
}

double Matrix::randomDouble(const double &min, const double &max) {
	double random = double (rand()) / double (RAND_MAX);
	double result = random * (max - min) + min;
	return int(result * 100 + .5) / 100.;
}
