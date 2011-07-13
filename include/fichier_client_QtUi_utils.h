#ifndef _FICHIER_CLIENT_QTUI_UTILS_H_
#define _FICHIER_CLIENT_QTUI_UTILS_H_

#include <string>
#include <QComboBox>
#include <vector>

class fichier_client_QtUi_utils
 {
 public:
   static const std::string get_human_date(const std::string & p_iso_date);
   static const std::string get_iso_date(const std::string & p_date);
   static void clear_combo_box_content(QComboBox * p_combo_box);
   template<class T> static void set_combo_box_named_list(QComboBox * p_combo_box,std::vector<T> & p_current,const std::vector<T> & p_list);
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
      p_combo_box->addItem(l_iter->getName().c_str());
      p_current.push_back(*l_iter);
      ++l_iter;
    }
  if(p_combo_box->count())
    {
      p_combo_box->setCurrentIndex(0);
    }  
}



#endif
