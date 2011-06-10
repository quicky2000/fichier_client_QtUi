#ifndef FACTURE_STATUS_LIST_TABLE_H
#define FACTURE_STATUS_LIST_TABLE_H

#include "facture_status.h"
#include <QTableWidget>
#include <vector>

class facture_status_list_table: public QTableWidget
{
  Q_OBJECT
 public:
  facture_status_list_table(QWidget *parent);
  void update(std::vector<facture_status> & p_client_list);
  uint32_t get_selected_facture_status_id(uint32_t p_row)const;
 private:
  void set_row_content(uint32_t p_row,const facture_status & p_facture_status_item);
};

#endif
