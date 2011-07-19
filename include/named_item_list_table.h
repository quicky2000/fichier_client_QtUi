#ifndef _NAMED_ITEM_LIST_TABLE_H_
#define _NAMED_ITEM_LIST_TABLE_H_

#include "base_list_table.h"
#include "simple_table_cell.h"
#include <vector>

template<typename T>
class named_item_list_table: public base_list_table
{
 public:
  named_item_list_table(const std::string & p_name,QWidget *parent=NULL);
  void update(std::vector<T> & p_list);
 private:
  void set_row_content(uint32_t p_row,const T & p_item);

};

//------------------------------------------------------------------------------
template<typename T>
named_item_list_table<T>::named_item_list_table(const std::string & p_name,QWidget *parent):
  base_list_table(p_name,parent)
{
}

//------------------------------------------------------------------------------
template<typename T>
void named_item_list_table<T>::update(std::vector<T> & p_list)
{
  clearContents();
  setRowCount(p_list.size());
  typename std::vector<T>::const_iterator l_iter = p_list.begin();
  typename std::vector<T>::const_iterator l_iter_end = p_list.end();
  uint32_t l_row = 0;
  while(l_iter != l_iter_end)
    {
      set_row_content(l_row,*l_iter);
      ++l_row;
      ++l_iter;
    }
  resizeColumnsToContents();
}

//------------------------------------------------------------------------------
template<typename T>
void named_item_list_table<T>::set_row_content(uint32_t p_row,const T & p_item)
{
  QString l_id_q;
  l_id_q.setNum(p_item.get_id());
  setItem(p_row,0,new simple_table_cell(l_id_q,p_item.get_id()));
  setItem(p_row,1,new simple_table_cell(p_item.get_name().c_str()));
}

#endif
