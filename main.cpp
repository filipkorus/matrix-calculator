#include "matrix.h"

int main() {
	srand(time(0)); // seed for random number generator

	Matrix A(3, 3, true), B(3, 3, true);
	int operation;

	enum actions {
		ADDITION = 1,
		SUBTRACTION,
		MULTIPLICATION,
		SCALAR_MULTIPLICATION,
		EXPONENTIATION,
		GET_VALUE_BY_INDEXES,
		SWAP_ROWS,
		SWAP_COLS,
		EXIT
	};

	std::cout << "A =\n" << A << "\nB =\n" << B << "\n";

	while (true) {
		std::cout << "_____________________________________________________________\n"
						 "Ktora operacje chcesz wykonac?\n"
						 "(1) A + B\n"
						 "(2) A - B\n"
						 "(3) A * B\n"
						 "(4) n * A\n"
						 "(5) A^n\n"
						 "(6) wypisz liczbe z macierzy A lub B na podstawie indeksu\n"
						 "(7) zamien wiersze macierzy A lub B\n"
						 "(8) zamien kolumny macierzy A lub B\n"
						 "(9) wyjscie z programu\n"
						 "Podaj numer operacji: ";

		std::cin >> operation;

		int n, row, col, r1, r2, c1, c2;
		char matrix;

		switch (operation) {
			case ADDITION:
				std::cout << "\nA + B =\n" << A + B << "\n";
				break;
			case SUBTRACTION:
				std::cout << "\nA - B =\n" << A - B << "\n";
				break;
			case MULTIPLICATION:
				std::cout << "\nA * B =\n" << A * B << "\n";
				break;
			case SCALAR_MULTIPLICATION:
				std::cout << "Podaj n: ";
				std::cin >> n;
				std::cout << "\nn * A =\n" << A * n << "\n";
				break;
			case EXPONENTIATION:
				std::cout << "Podaj n: ";
				std::cin >> n;
				std::cout << "\nA ^ n =\n" << (A ^ n) << "\n";
				break;
			case GET_VALUE_BY_INDEXES:
				std::cout << "Podaj ktora macierz wybierasz (A/B): ";
				std::cin >> matrix;
				std::cout << "Podaj wspolrzedna wiersza (pierwszy wiersz ma indeks 0): ";
				std::cin >> row;
				std::cout << "Podaj wspolrzedna kolumny (pierwsza kolumna ma indeks 0): ";
				std::cin >> col;
				std::cout << "\n A[" << row << "][" << col << "] = ";
				 std::cout << (toupper(matrix) == 'A' ? A.getFromPosition(row, col) : B.getFromPosition(row, col)) << "\n";
				break;
			case SWAP_ROWS:
				std::cout << "Podaj ktora macierz wybierasz (A/B): ";
				std::cin >> matrix;
				std::cout << "Ktore wiersze chcesz zamienic?\n"
								 "Podaj indeks pierwszego z nich (pierwszy wiersz ma indeks 0): ";
				std::cin >> r1;
				std::cout << "Podaj indeks drugiego z nich (pierwszy wiersz ma indeks 0): ";
				std::cin >> r2;
				std::cout << "\n" << char(toupper(matrix)) << " (zamienione wiersze " << r1 << " -> " << r2 << ") =\n";
				 std::cout << (toupper(matrix) == 'A' ? A.swapRows(r1, r2) : B.swapRows(r1, r2)) << "\n";
				break;
			case SWAP_COLS:
				std::cout << "Podaj ktora macierz wybierasz (A/B): ";
				std::cin >> matrix;
				std::cout << "Ktore kolumny chcesz zamienic?\n"
				             "Podaj indeks pierwszej z nich (pierwsza kolumna ma indeks 0): ";
				std::cin >> c1;
				std::cout << "Podaj indeks drugiej z nich (pierwsza kolumna ma indeks 0): ";
				std::cin >> c2;
				std::cout << "\n" << char(toupper(matrix)) << " (zamienione kolumny " << c1 << " -> " << c2 << ") =\n";
				 std::cout << (toupper(matrix) == 'A' ? A.swapCols(c1, c2) : B.swapCols(c1, c2)) << "\n";
				break;
			case EXIT:
				std::cout << "wyjscie z programu...\n";
				exit(0);
			default:
				std::cout << "nieprawidlowa operacja...\n";
		}
	}
}
