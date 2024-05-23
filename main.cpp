#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <algorithm>

using namespace std;

class TableMaker {
  public:
  using Row = vector<string>;
  vector<Row> table;

  void addRow(const Row &row) {
    table.push_back(row);
  }

  void sortByColumn(int columnIndex, bool ascending = true) {
    if (ascending) {
      sort(table.begin(), table.end(), [columnIndex](const Row &a, const Row & b) {
        return a[columnIndex] < b[columnIndex];
      });
    } else {
      sort(table.begin(), table.end(), [columnIndex](const Row &a, const Row &b) {
        return a[columnIndex] > b[columnIndex];
      });
    }
  }

  void printBorder(vector<size_t> columnWidth, ostream &output) {
    for (int i = 0; i < columnWidth.size(); i++) {
      output << "+" << string(columnWidth[i] + 2, '-');
    }
    output << "+" << endl;
  }

  void printTabel(ostream &output, bool header = false) {
    vector<size_t> columnWidth(table[1].size(), 0);

    for (const auto &row : table) {
      for (int i = 0; i < row.size(); i++) {
        columnWidth[i] = max(columnWidth[i], row[i].size());
      }
    }

    printBorder(columnWidth, output);

    auto rowIndex = table.begin();
    for (const auto &row : table) {
      for (int i = 0; i < row.size(); i++) {
        output << "| " << setw(columnWidth[i] + 1) << left << row[i];
      }
      output << "|" << endl;
      if (header && rowIndex == table.begin()) {
        printBorder(columnWidth, output);
      }
      rowIndex++;
    }
    printBorder(columnWidth, output);
  }
};

int main() {
  TableMaker tm;

  tm.table = {
    {"John", "Doe", "30"},
    {"Jane", "Smith", "25"},
    {"Alice", "Brown", "28"},
  };

  tm.printTabel(cout, true);
  return 0;
}