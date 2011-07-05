#include "facture_reason_list_table.h"
#include "simple_table_cell.h"
#include <vector>
#include <assert.h>

using namespace std;

//------------------------------------------------------------------------------
facture_reason_list_table::facture_reason_list_table(QWidget *parent):
  QTableWidget(0,2,parent)
{
  QStringList l_h_header_list;
  l_h_header_list << tr("Id") << tr("Status") ;
  setHorizontalHeaderLabels(l_h_header_list);
  setSelectionBehavior(QAbstractItemView::SelectRows);
  setSelectionMode(QAbstractItemView::SingleSelection);
  setItemPrototype(new simple_table_cell(""));
  setColumnHidden(0,false);
}

//------------------------------------------------------------------------------
uint32_t facture_reason_list_table::get_selected_facture_reason_id(uint32_t p_row)const
{
  assert(p_row < ((uint32_t)rowCount()));
  return static_cast<simple_table_cell*>(item(p_row,0))->get_id();
}

//------------------------------------------------------------------------------
void facture_reason_list_table::set_row_content(uint32_t p_row,const facture_reason & p_facture_reason_item)
{
      QString l_id_q;
      l_id_q.setNum(p_facture_reason_item.get_id());
      setItem(p_row,0,new simple_table_cell(l_id_q,p_facture_reason_item.get_id()));
      setItem(p_row,1,new simple_table_cell(p_facture_reason_item.getName().c_str()));
 }

//------------------------------------------------------------------------------
void facture_reason_list_table::update(std::vector<facture_reason> & p_facture_reason_list)
{
  clearContents();
  setRowCount(p_facture_reason_list.size());
  vector<facture_reason>::const_iterator l_iter = p_facture_reason_list.begin();
  vector<facture_reason>::const_iterator l_iter_end = p_facture_reason_list.end();
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
