#include "client_list_table.h"
#include "simple_table_cell.h"
#include <vector>
#include <assert.h>

using namespace std;

client_list_table::client_list_table(QWidget *parent):
  QTableWidget(0,5,parent)
{
  QStringList l_h_header_list;
  l_h_header_list << tr("Id") << tr("Nom") << tr("Prenom") << tr("Address") << tr("Ville") ;
  setHorizontalHeaderLabels(l_h_header_list);
  setSelectionBehavior(QAbstractItemView::SelectRows);
  setSelectionMode(QAbstractItemView::SingleSelection);
  setItemPrototype(new simple_table_cell(""));
  setColumnHidden(0,true);
}

uint32_t client_list_table::get_selected_client_id(uint32_t p_row)const
{
  assert(p_row < ((uint32_t)rowCount()));
  return static_cast<simple_table_cell*>(item(p_row,0))->get_id();
}

void client_list_table::set_row_content(uint32_t p_row,const search_client_item & p_client_item)
{
      QString l_id_q;
      l_id_q.setNum(p_client_item.get_id());
      setItem(p_row,0,new simple_table_cell(l_id_q,p_client_item.get_id()));
      setItem(p_row,1,new simple_table_cell(p_client_item.get_name().c_str()));
      setItem(p_row,2,new simple_table_cell(p_client_item.get_first_name().c_str()));
      setItem(p_row,3,new simple_table_cell(p_client_item.get_address().c_str()));
      setItem(p_row,4,new simple_table_cell(p_client_item.get_city().c_str()));
 }

void client_list_table::update(std::vector<search_client_item> & p_client_list)
{
  clearContents();
  setRowCount(p_client_list.size());
  vector<search_client_item>::const_iterator l_iter = p_client_list.begin();
  vector<search_client_item>::const_iterator l_iter_end = p_client_list.end();
  uint32_t l_row = 0;
  while(l_iter != l_iter_end)
    {
      set_row_content(l_row,*l_iter);
      ++l_row;
      ++l_iter;
    }
  resizeColumnsToContents();
}

//EOF
