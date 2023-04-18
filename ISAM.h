//
// Created by juaquin on 18/04/23.
//

#ifndef ISAM_ISAM_H
#define ISAM_ISAM_H

#include <string>
#include <vector>
#include <fstream>

using T = int;
using Record = int;
const long M = 27;
const long N = 8;

struct IndexPage
{
    T keys[M];//sizeof(T) = 10
    long children[M+1];
    int count;
};


struct DataPage
{
    Record records[N];//sizeof(Record) = 60
    int count;
    long next;
};

struct ISAM {
  std::string namefile;
  void add(Record record){
      std::fstream file("index1.dat", std::ios::in | std::ios::out);
      IndexPage page_ind;
      file.read((char*)&page_ind, sizeof(page_ind));
      file.close();
      long pos_fisica = localizar(page_ind, key(record));
      file.open("index2.dat");
      file.seekg(pos_fisica);
      file.read((char*)&page_ind, sizeof(page_ind));
      file.close();
      pos_fisica = localizar(page_ind, key(record));
      file.open("index3.dat");
      file.seekg(pos_fisica);
      file.read((char*)&page_ind, sizeof(page_ind));
      file.close();
      pos_fisica = localizar(page_ind, key(record));
      file.open("data.dat");
      DataPage data_page;
      file.seekg(pos_fisica);
      file.read((char*)&data_page, sizeof(data_page));

      _insert(data_page, record, file, pos_fisica);
  }
  std::vector<Record> search(T key) {
    std::ifstream file("index1.dat");
    IndexPage page_ind;
    file.read((char*)&page_ind, sizeof(page_ind));
    file.close();
    long pos_fisica = localizar(page_ind, key);
    file.open("index2.dat");
    file.seekg(pos_fisica);
    file.read((char*)&page_ind, sizeof(page_ind));
    file.close();
    pos_fisica = localizar(page_ind, key);
    file.open("index3.dat");
    file.seekg(pos_fisica);
    file.read((char*)&page_ind, sizeof(page_ind));
    file.close();
    pos_fisica = localizar(page_ind, key);
    file.open("data.dat");
    DataPage data_page;
    file.seekg(pos_fisica);
    file.read((char*)&data_page, sizeof(data_page));
    file.close();
    return linear_search(data_page.records, data_page.count, key);
  }

private:
    int localizar(IndexPage ind, T key){

    }


    std::vector<Record> linear_search(Record* records, int size, T key){

  }
  void _insert(DataPage page, Record record, std::fstream& file, int parent_pos) {

      while (page.next != -1) {
          parent_pos = page.next;
          file.seekg(page.next);
          file.read(page, sizeof(page));
      }
      if (page.count == N){
          DataPage new_page;
          new_page.records[0] = record;
          new_page.count++;
          file.seekg(0, std::ios::end);
          page.next = file.tellg();
          file.write((char*)&new_page, sizeof(new_page));
      }
      else {
          page.records[page.count] = record;
          page.count++;
      }
      file.seekg(parent_pos);
      file.write(page, sizeof(page));
  }
};

#endif //ISAM_ISAM_H
