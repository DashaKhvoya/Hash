#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <vector>

#include <algorithm>
#include <cmath>

using std::vector;
using std::list;

const size_t prime_numb = 9999901;
const size_t arg_1 = 20;
const size_t arg_2 =50;

struct HashTable {
  vector<list<size_t> > array;
};

size_t Hash(size_t table_size, const size_t key) {
  size_t hash_result = (key * arg_1 + arg_2) % prime_numb;
  hash_result %= table_size;
  return hash_result;
}

void ReallocTable(HashTable* table) {
  size_t new_capacity = 2 * table -> array.capacity();
  HashTable copy_table = {};
  list<size_t> list = {};

  for (size_t i = 0; i < new_capacity; i++) {
    copy_table.array.push_back(list);
  }

  for (size_t i = 0; i < table -> array.capacity(); i++) {
    for (auto j = table -> array[i].begin(); j != table -> array[i].end(); j = next(j)) {
      size_t pos = Hash(new_capacity, *j);
      copy_table.array[i].push_front(*j);
    }
  }

  table = &copy_table;
}

bool FindTable(const size_t key, HashTable* table) {
  size_t pos = Hash(table -> array.capacity(), key);

  for (auto i = table -> array[pos].begin(); i != table -> array[pos].end(); i = next(i)) {
    if (*i == pos) {
      return true;
    }
  }

  return false;
}

void RemoveTable(const size_t key, HashTable* table) {
  size_t pos = Hash(table -> array.capacity(), key);

  for (auto i = table -> array[pos].begin(); i != table -> array[pos].end(); i = next(i)) {
    if (*i == pos) {
      table -> array[pos].erase(i);
      break;
    }
  }
}

void AddTable(const size_t key, HashTable* table) {
  size_t pos = Hash(table -> array.capacity(), key);
  if (table -> array[pos].size() > 50) {
    ReallocTable(table);
  }

  if (FindTable(key, table) == true) {
    return;
  }

  table -> array[pos].push_front(key);
}

int main() {
  size_t numb = 0;
  scanf("%lu", &numb);
  HashTable table = {};

  for (size_t i = 0; i < numb; i++) {
    char op;
    size_t key = 0;
    scanf("%c%lu", &op, &key);

    if (op == '+') {
      AddTable(key, &table);
    } else if (op == '-') {
      RemoveTable(key, &table);
    } else {
      if (FindTable(key, &table) == true) {
        printf("YES\n");
      } else {
        printf("NO\n");
      }
    }
  }

  return 0;
}
