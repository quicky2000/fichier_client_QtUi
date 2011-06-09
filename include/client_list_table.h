#ifndef CLIENT_LIST_TABLE_H
#define CLIENT_LIST_TABLE_H

#include "search_client_item.h"

#include <QTableWidget>
#include <vector>

class client_list_table: public QTableWidget
{
  Q_OBJECT
 public:
  client_list_table(QWidget *parent);
  void update(std::vector<search_client_item> & p_client_list);
  uint32_t get_selected_client_id(uint32_t p_row)const;
 private:
  void set_row_content(uint32_t p_row,const search_client_item & p_client_item);
};

#endif
