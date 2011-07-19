#include "base_list_table.h"
#include "simple_table_cell.h"
#include <assert.h>

//------------------------------------------------------------------------------
base_list_table::base_list_table(const std::string & p_name,QWidget *parent):
  QTableWidget(0,2,parent)
{
  QStringList l_h_header_list;
  l_h_header_list << tr("Id") << p_name.c_str() ;
  setHorizontalHeaderLabels(l_h_header_list);
  setSelectionBehavior(QAbstractItemView::SelectRows);
  setSelectionMode(QAbstractItemView::SingleSelection);
  setItemPrototype(new simple_table_cell(""));
  setColumnHidden(0,false);
}

//------------------------------------------------------------------------------
uint32_t base_list_table::get_selected_item_id(uint32_t p_row)const
{
  assert(p_row < ((uint32_t)rowCount()));
  return static_cast<simple_table_cell*>(item(p_row,0))->get_id();
}

//EOF
