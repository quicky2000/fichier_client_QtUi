#ifndef FACTURE_CLIENT_LIST_TABLE_H
#define FACTURE_CLIENT_LIST_TABLE_H

#include "facture_list_table.h"
#include "search_facture_client_item.h"

class facture_client_list_table: public facture_list_table
{
  Q_OBJECT
 public:
  facture_client_list_table(QWidget *parent);
  void update(std::vector<search_facture_client_item> & p_search_facture_item_list);
 private:
  static QStringList get_header_list(void); 
  void set_row_content(uint32_t p_row,const search_facture_client_item & p_item);
};

#endif
