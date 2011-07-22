#include "list_table_coherency_report.h"
#include "simple_table_cell.h"
#include <assert.h>

//------------------------------------------------------------------------------
list_table_coherency_report::list_table_coherency_report(QWidget *parent):
  QTableWidget(0,4,parent)
{
  QStringList l_h_header_list;
  l_h_header_list << tr("Niveau") << tr("Type") << tr("Id") << tr("Message");
  setHorizontalHeaderLabels(l_h_header_list);
  setSelectionBehavior(QAbstractItemView::SelectRows);
  setSelectionMode(QAbstractItemView::SingleSelection);
  setItemPrototype(new simple_table_cell(""));
}

//------------------------------------------------------------------------------
uint32_t list_table_coherency_report::get_selected_item_id(void)const
{
  assert(!this->selectedRanges().empty());
  return static_cast<simple_table_cell*>(item(this->currentRow(),0))->get_id();
}

//------------------------------------------------------------------------------
void list_table_coherency_report::update(std::vector<coherency_report_item> & p_list)
{
  clearContents();
  setRowCount(p_list.size());
  std::vector<coherency_report_item>::const_iterator l_iter = p_list.begin();
  std::vector<coherency_report_item>::const_iterator l_iter_end = p_list.end();
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
void list_table_coherency_report::set_row_content(uint32_t p_row,const coherency_report_item & p_item)
{
  QString l_id_q;
  l_id_q.setNum(p_item.get_id());
  setItem(p_row,0,new simple_table_cell(coherency_report_item::to_string(p_item.get_report_level()).c_str()));
  setItem(p_row,1,new simple_table_cell(p_item.get_table_name().c_str()));
  setItem(p_row,2,new simple_table_cell(l_id_q,p_item.get_id()));
  setItem(p_row,1,new simple_table_cell(p_item.get_message().c_str()));
}

//EOF
