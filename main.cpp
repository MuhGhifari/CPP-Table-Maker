#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <algorithm>

using namespace std;

class TableMaker {
  protected:
  void printBorder(vector<size_t> columnWidth, ostream &output) {
    for (int i = 0; i < columnWidth.size(); i++) {
      output << "+" << string(columnWidth[i] + 2, '-');
    }
    output << "+" << endl;
  }

  public:
  using Row = vector<string>;
  vector<Row> table;

  void addRow(const Row &row) {
    table.push_back(row);
  }

  void sortByColumn(int columnIndex, bool hasHeader = false, bool ascending = true) {
    if (columnIndex < 1 || columnIndex > table[1].size()) {
      cerr << "[\x1b[31mERROR\x1b[0m] : tidak ada indeks kolom ke-" << columnIndex << " untuk diurut" << endl;
      return;
    }

    auto startingIndex = hasHeader ? table.begin() + 1 : table.begin();
    int column = columnIndex - 1;

    if (ascending) {
      sort(startingIndex, table.end(), [column](const Row &a, const Row & b) {
        return a[column] < b[column];
      });
    } else {
      sort(startingIndex, table.end(), [column](const Row &a, const Row &b) {
        return a[column] > b[column];
      });
    }
  }

  void printTabel(ostream &output, bool hasHeader = false) {
    if (table.empty()) return;

    vector<size_t> columnWidth(table[1].size(), 0);

    for (const auto &row : table) {
      for (int i = 0; i < row.size(); i++) {
        columnWidth[i] = max(columnWidth[i], row[i].size());
      }
    }

    printBorder(columnWidth, output);

    auto rowIndex = table.begin();
    for (const auto &row : table) {
      for (int i = 0; i < columnWidth.size(); i++) {
        output << "| " << setw(columnWidth[i] + 1) << left << row[i];
      }
      output << "|" << endl;
      if (hasHeader && rowIndex == table.begin()) {
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
    {"NPM", "Nama", "Role"},
    {"065123020", "Muhammad Ghifari", "Programmer"},
    {"065123026", "Revieta Ramadhani K.", "PPT"},
    {"065123021", "Muhammad Bimo N.R.", "Makalah"},
    {"065123004", "Rizha Aditya", "Flowchart"},
    {"065123023", "Muhammad Ziran", "Tester"},
  };

  tm.sortByColumn(1, true, true);
  tm.printTabel(cout, true);
  return 0;
}