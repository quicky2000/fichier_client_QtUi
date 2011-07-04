#ifndef _FICHIER_CLIENT_QTUI_UTILS_H_
#define _FICHIER_CLIENT_QTUI_UTILS_H_

#include <string>

class fichier_client_QtUi_utils
 {
 public:
   static const std::string get_human_date(const std::string & p_iso_date);
   static const std::string get_iso_date(const std::string & p_date);
 };

#endif
