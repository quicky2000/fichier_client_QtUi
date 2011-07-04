
#include "fichier_client_QtUi_utils.h"
#include <assert.h>

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

const std::string fichier_client_QtUi_utils::get_iso_date(const std::string & p_date)
{
  assert(p_date.length()==10);
  return p_date.substr(6,4)+"-"+p_date.substr(3,2)+"-"+p_date.substr(0,2);
 
}

//EOF 
