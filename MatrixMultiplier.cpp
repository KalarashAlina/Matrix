#include <iostream>
#include <cstdlib>  // Äëÿ rand()
#include <ctime>    // Äëÿ srand(time(0))
#include <chrono>
#include <vector>
#include <iomanip>
#include <Windows.h>

using namespace std;
using namespace chrono;

const int MATRIX_SIZE = 10;  // Renamed to avoid conflict with Windows.h

// Ôóíêö³ÿ äëÿ çàïîâíåííÿ ìàòðèö³ âèïàäêîâèìè ÷èñëàìè (0-9)
void fillMatrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
  for (int i = 0; i < MATRIX_SIZE; i++) {
    for (int j = 0; j < MATRIX_SIZE; j++) {
      matrix[i][j] = rand() % 10;
    }
  }
}

// Ôóíêö³ÿ äëÿ âèâîäó ìàòðèö³
void printMatrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
  for (int i = 0; i < MATRIX_SIZE; i++) {
    for (int j = 0; j < MATRIX_SIZE; j++) {
      cout << matrix[i][j] << "\t";
    }
    cout << "\n";
  }
}

void printTimeMatrix(const vector<vector<long long>>& timeMatrix) {
  cout << "\n×àñ âèêîíàííÿ äëÿ êîæíîãî åëåìåíòà (íàíîñåêóíäè):\n";
  for (const auto& row : timeMatrix) {
    for (long long t : row) {
      cout << setw(12) << t << " ";
    }
    cout << endl;
  }
}

int main() {
  setlocale(LC_ALL, "Ukrainian");
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
  srand(time(0)); // ²í³ö³àë³çàö³ÿ ãåíåðàòîðà âèïàäêîâèõ ÷èñåë

  int A[MATRIX_SIZE][MATRIX_SIZE], B[MATRIX_SIZE][MATRIX_SIZE], C[MATRIX_SIZE][MATRIX_SIZE];

  fillMatrix(A);
  fillMatrix(B);

  cout << "Matrix A:\n";
  printMatrix(A);

  cout << "\nMatrix B:\n";
  printMatrix(B);

  vector<vector<long long>> timeMatrix(MATRIX_SIZE, vector<long long>(MATRIX_SIZE));

  // Ïî÷àòîê âèì³ðþâàííÿ çàãàëüíîãî ÷àñó
  auto totalStart = high_resolution_clock::now();

  for (int i = 0; i < MATRIX_SIZE; i++) {
    for (int j = 0; j < MATRIX_SIZE; j++) {
      auto start = high_resolution_clock::now(); // Ïî÷àòîê âèì³ðþâàííÿ äëÿ îêðåìîãî åëåìåíòà

      C[i][j] = 0;
      for (int k = 0; k < MATRIX_SIZE; k++) {
        C[i][j] += A[i][k] * B[k][j];
      }

      auto stop = high_resolution_clock::now(); // Ê³íåöü âèì³ðþâàííÿ äëÿ îêðåìîãî åëåìåíòà
      timeMatrix[i][j] = duration_cast<nanoseconds>(stop - start).count();
    }
  }

  // Ê³íåöü âèì³ðþâàííÿ çàãàëüíîãî ÷àñó
  auto totalStop = high_resolution_clock::now();
  long long totalTime = duration_cast<nanoseconds>(totalStop - totalStart).count();

  cout << "\nResult (A * B):\n";
  printMatrix(C);
  printTimeMatrix(timeMatrix);

  // Âèâåäåííÿ çàãàëüíîãî ÷àñó
  cout << "\nÇàãàëüíèé ÷àñ âèêîíàííÿ ìíîæåííÿ ìàòðèöü: " << totalTime << " íàíîñåêóíä\n";

  return 0;
}
