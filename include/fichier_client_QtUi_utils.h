#ifndef _FICHIER_CLIENT_QTUI_UTILS_H_
#define _FICHIER_CLIENT_QTUI_UTILS_H_

#include <string>
#include <QComboBox>
#include <vector>
#include <inttypes.h>

class fichier_client_QtUi_utils
 {
 public:
   static const std::string get_human_date(const std::string & p_iso_date);
   static const std::string get_iso_date(const std::string & p_date);
   static void clear_combo_box_content(QComboBox * p_combo_box);
   static void select_combo_box_content(uint32_t p_value,QComboBox * p_combo_box,const std::vector<uint32_t> & p_content);
   template<class T> static void set_combo_box_named_list(QComboBox * p_combo_box,std::vector<T> & p_current,const std::vector<T> & p_list);
   template<class T> static void select_combo_box_named_content(uint32_t p_id,QComboBox * p_combo_box,const std::vector<T> & p_content);
 };

//------------------------------------------------------------------------------
template<class T> void fichier_client_QtUi_utils::set_combo_box_named_list(QComboBox * p_combo_box,std::vector<T> & p_current,const std::vector<T> & p_list)
{
  clear_combo_box_content(p_combo_box);
  p_current.clear();
  if(p_list.size() > 1)
    {
      p_combo_box->addItem("");
    }
  typename std::vector<T>::const_iterator l_iter = p_list.begin();
  typename std::vector<T>::const_iterator l_iter_end = p_list.end();
  while(l_iter != l_iter_end)
    {
      p_combo_box->addItem(l_iter->get_name().c_str());
      p_current.push_back(*l_iter);
      ++l_iter;
    }
  if(p_combo_box->count())
    {
      p_combo_box->setCurrentIndex(0);
    }  
}

//------------------------------------------------------------------------------
template<class T> void fichier_client_QtUi_utils::select_combo_box_named_content(uint32_t p_id,QComboBox * p_combo_box,const std::vector<T> & p_content)
{
  if(p_content.size()>1)
    {
      typename std::vector<T>::const_iterator l_iter = p_content.begin();
      typename std::vector<T>::const_iterator l_iter_end = p_content.end();
      uint32_t l_index = 1;
      while(l_iter != l_iter_end && l_iter->get_id() != p_id)
	{
	  ++l_iter;
	  ++l_index;
	}  
      assert(l_iter->get_id() == p_id);
      p_combo_box->setCurrentIndex(l_index);
    }
}


#endif
