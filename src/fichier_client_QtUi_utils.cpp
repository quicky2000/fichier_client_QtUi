
#include "fichier_client_QtUi_utils.h"
#include <assert.h>

//------------------------------------------------------------------------------
const std::string fichier_client_QtUi_utils::get_human_date(const std::string & p_iso_date)
{
  assert(p_iso_date.length()==10 || p_iso_date.length()==0);
  std::string l_result;
  if(p_iso_date.length())
    {
      l_result = p_iso_date.substr(8,2)+"/"+p_iso_date.substr(5,2)+"/"+p_iso_date.substr(0,4);
    }  
  return l_result;
}

//------------------------------------------------------------------------------
const std::string fichier_client_QtUi_utils::get_iso_date(const std::string & p_date)
{
  assert(p_date.length()==10);
  return p_date.substr(6,4)+"-"+p_date.substr(3,2)+"-"+p_date.substr(0,2);
 
}

//------------------------------------------------------------------------------
void fichier_client_QtUi_utils::clear_combo_box_content(QComboBox * p_combo_box)
{
  assert(p_combo_box);
  while(p_combo_box->count())
    {
      p_combo_box->removeItem(0);
    }
}

//------------------------------------------------------------------------------
void fichier_client_QtUi_utils::select_combo_box_content(uint32_t p_value,QComboBox * p_combo_box,const std::vector<uint32_t> & p_content)
{
  assert(p_combo_box);
    if(p_content.size()>1)
    {
      std::vector<uint32_t>::const_iterator l_iter = p_content.begin();
      std::vector<uint32_t>::const_iterator l_iter_end = p_content.end();
      uint32_t l_index = 1;
      while(l_iter != l_iter_end && *l_iter != p_value)
	{
	  ++l_iter;
	  ++l_index;
	}  
      assert(*l_iter == p_value);
      p_combo_box->setCurrentIndex(l_index);
    }

}

//EOF 
