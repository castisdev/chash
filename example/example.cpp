#include "consistent_hash.h"

#include <vector>
#include <string>
#include <iostream>

#include <uuid/uuid.h>

void print(std::vector<std::string> v) {
  std::cout << "[";
  for (std::vector<std::string>::const_iterator i = v.begin(); i != v.end();
      ++i) {
    std::cout << *i << " ";
  }
  std::cout << "]\n";
}

int main(int argc, char* argv[]) {
  ConsistentHash hash_low(5);

  hash_low.Add("low1", 1);
  hash_low.Add("low2", 1);
  hash_low.Add("low3", 1);

  std::cout << "select single key\n";
  for (int i = 0; i < 10; ++i) {
    uuid_t uuid;
    uuid_generate_random(uuid);
    char str[256];
    uuid_unparse(uuid, str);
    std::string key = str;
    key += ".mpg";
    std::cout << "key = " << key << ", selected = " << hash_low.Get(key);
    std::cout << "\n";
  }

  ConsistentHash hash_middle(5);

  hash_middle.Add("middle1", 1);
  hash_middle.Add("middle2", 1);
  hash_middle.Add("middle3", 1);
  hash_middle.Add("middle4", 1);
  hash_middle.Add("middle5", 1);

  std::cout << "\nselect ordered keys\n";
  for (int i = 0; i < 10; ++i) {
    uuid_t uuid;
    uuid_generate_random(uuid);
    char str[256];
    uuid_unparse(uuid, str);
    std::string key = str;
    key += ".mpg";
    std::cout << "key = " << key << ", selected = ";
    print(hash_middle.GetItems(key));
  }

  return 0;
}
