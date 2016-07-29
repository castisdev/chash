#ifndef CHASH_CONSISTENT_HASH_H_
#define CHASH_CONSISTENT_HASH_H_

#include <set>
#include <map>
#include <string>
#include <vector>

#include <boost/crc.hpp>

struct ConsistentHash {
  typedef std::set<boost::crc_32_type::value_type> KeySet;
  typedef std::map<boost::crc_32_type::value_type, std::string> HashKeyMap;

  explicit ConsistentHash(int replicas);
  void Add(const std::string &key, int weight);
  std::string Get(const std::string &key);
  std::vector<std::string> GetItems(const std::string &key);

  int replicas_;
  std::size_t key_count_;

  KeySet keys_;
  HashKeyMap hash_key_map_;
};

#endif /* CHASH_CONSISTENT_HASH_H_ */
