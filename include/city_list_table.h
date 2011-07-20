#ifndef CITY_LIST_TABLE_H
#define CITY_LIST_TABLE_H

#include "ville.h"
#include <QTableWidget>
#include <vector>

class city_list_table: public QTableWidget
{
  Q_OBJECT
 public:
  city_list_table(QWidget *parent);
  void update(std::vector<ville> & p_client_list);
  uint32_t get_selected_city_id(uint32_t p_row)const;
 private:
  void set_row_content(uint32_t p_row,const ville & p_city_item);
};

#endif
