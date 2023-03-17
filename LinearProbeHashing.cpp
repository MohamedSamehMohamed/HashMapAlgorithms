#include<bits/stdc++.h>
using namespace std;
class Map{
  struct data{
    int key;
    bool wasDeleted;
    string value;
    data(){
      key = -1;
      wasDeleted = 0;
    }
  };
  vector<data> _map;
  void extend(){
    vector<string> values;
    for (int i = 0; i < _map.size(); i++)
      values.push_back(_map[i].value);
    _map = vector<data>(_map.size() * 2);
    for (int i = 0; i < values.size(); i++){
      add(values[i]);
    }
  }
  public:
    Map(){
      _map = vector<data>(10);
    }  
    Map(int size){
      if (size <= 0) size = 10;
      _map = vector<data>(size);
    }
    int hash(string str){
      int curSize = _map.size();
      int hashValue = 0;
      for (int i = 0; i < str.size(); i++){
        hashValue = (hashValue * 26 + int(str[i])) % curSize;
      }  
      return hashValue;
    }
    void add(string str){
      int curSize = _map.size();
      int hashValue = hash(str);
      int toPut = hashValue;
      bool noFreeSpace = 0;
      while (_map[toPut].key != -1){
        toPut = (toPut + 1) % curSize;
        if (toPut == hashValue){
          noFreeSpace = 1;
          break;
        }
      }
      if (noFreeSpace){
        extend();
        add(str);
        return;
      }
      _map[toPut].key = toPut;
      _map[toPut].value = str;
    }
    void remove(string str){
      int hashValue = hash(str);
      int curSize = _map.size();
      int toDelete = hashValue;
      while (_map[toDelete].key != hashValue && 
      (_map[toDelete].key != -1 || _map[toDelete].wasDeleted == 1)){
        toDelete = (toDelete + 1) % curSize;
        if (toDelete == hashValue){
          // value is not exist 
          return;
        }
      }
      _map[toDelete].key = -1;
      _map[toDelete].wasDeleted = 1; 
    }
    bool find(string str){
      int hashValue = hash(str);
      int curSize = _map.size();
      int index = hashValue;
      while (_map[index].key != hashValue && 
      (_map[index].key != -1 || _map[index].wasDeleted == 1)){
        index = (index + 1) % curSize;
        if (index == hashValue){
          // value not exist 
          return 0;
        }
      }
      return _map[index].key == hashValue;
    }
};
char randomChar(){
  string list = "abc!@#$%^&*()_+defghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  random_shuffle(list.begin(), list.end());
  return list[rand() % (int)list.size()];
}
void test(){
  Map hashMap = Map();
  vector<string> values;
  for (int i = 0; i < 30; i++){
    string cur = "";
    for (int j = 0; j < 5 + rand() % 10; j++){
      cur += randomChar();
    }
    values.push_back(cur);
    hashMap.add(cur);
  }
  for (int i = 0; i < values.size(); i++){
    cout << values[i] <<" is exist: ";
    cout << hashMap.find(values[i]) << " \n";
    hashMap.remove(values[i]);
    cout << values[i] <<" is exist: ";
    cout << hashMap.find(values[i]) << " \n";
  }
}
int main(){
  test();
  
}