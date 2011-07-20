#include "city_list_table.h"
#include "simple_table_cell.h"
#include <vector>
#include <assert.h>

using namespace std;

//------------------------------------------------------------------------------
city_list_table::city_list_table(QWidget *parent):
  QTableWidget(0,3,parent)
{
  QStringList l_h_header_list;
  l_h_header_list << tr("Id") << tr("Ville") << tr("Code postal");
  setHorizontalHeaderLabels(l_h_header_list);
  setSelectionBehavior(QAbstractItemView::SelectRows);
  setSelectionMode(QAbstractItemView::SingleSelection);
  setItemPrototype(new simple_table_cell(""));
  setColumnHidden(0,false);
}

//------------------------------------------------------------------------------
uint32_t city_list_table::get_selected_city_id(uint32_t p_row)const
{
  assert(p_row < ((uint32_t)rowCount()));
  return static_cast<simple_table_cell*>(item(p_row,0))->get_id();
}

//------------------------------------------------------------------------------
void city_list_table::set_row_content(uint32_t p_row,const ville & p_city_item)
{
      QString l_id_q;
      l_id_q.setNum(p_city_item.get_id());
      setItem(p_row,0,new simple_table_cell(l_id_q,p_city_item.get_id()));
      setItem(p_row,1,new simple_table_cell(p_city_item.get_name().c_str()));
      setItem(p_row,2,new simple_table_cell(p_city_item.get_postal_code().c_str()));
 }

//------------------------------------------------------------------------------
void city_list_table::update(std::vector<ville> & p_city_list)
{
  clearContents();
  setRowCount(p_city_list.size());
  vector<ville>::const_iterator l_iter = p_city_list.begin();
  vector<ville>::const_iterator l_iter_end = p_city_list.end();
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
