#include "consistent_hash.h"

#include <string>
#include <vector>

#include <boost/crc.hpp>
#include <boost/lexical_cast.hpp>

ConsistentHash::ConsistentHash(int replicas)
    : replicas_(replicas), key_count_(0) {
}

void ConsistentHash::Add(const std::string &key, int weight) {
  for (int i = 0; i < replicas_ * weight; ++i) {
    boost::crc_32_type result;
    std::string current_key = boost::lexical_cast<std::string>(i) + key;
    result.process_bytes(current_key.c_str(), current_key.length());
    boost::crc_32_type::value_type hash = result.checksum();
    keys_.insert(hash);
    hash_key_map_.insert(std::make_pair(hash, key));
  }
  ++key_count_;
}

std::string ConsistentHash::Get(const std::string &key) {
  if (keys_.empty() == true) {
    return "";
  }

  boost::crc_32_type result;
  result.process_bytes(key.c_str(), key.length());
  boost::crc_32_type::value_type hash = result.checksum();

  KeySet::const_iterator spos = keys_.lower_bound(hash);
  if (spos == keys_.end()) {
    spos = keys_.begin();
  }

  HashKeyMap::const_iterator mpos = hash_key_map_.find(*spos);
  if (mpos == hash_key_map_.end()) {
    return "";
  }

  return mpos->second;
}

std::vector<std::string> ConsistentHash::GetItems(const std::string &key) {
  std::vector<std::string> items;

  if (keys_.empty() == true) {
    return items;
  }

  boost::crc_32_type result;
  result.process_bytes(key.c_str(), key.length());
  boost::crc_32_type::value_type hash = result.checksum();

  KeySet::const_iterator spos = keys_.lower_bound(hash);
  if (spos == keys_.end()) {
    spos = keys_.begin();
  }

  std::set<std::string> hit;
  for (KeySet::size_type i = 0; i < keys_.size(); ++i) {
    HashKeyMap::const_iterator mpos = hash_key_map_.find(*spos);
    if (mpos != hash_key_map_.end() && hit.find(mpos->second) == hit.end()) {
      items.push_back(mpos->second);
      hit.insert(mpos->second);
      if (items.size() == key_count_) {
        return items;
      }
    }
    ++spos;
    if (spos == keys_.end()) {
      spos = keys_.begin();
    }
  }
  return items;
}
