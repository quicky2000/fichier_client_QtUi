#ifndef _CITY_WIDGET_H_
#define _CITY_WIDGET_H_

#include <QWidget>
#include "ville.h"

class fichier_client;
class QLineEdit;
class QPushButton;
class postal_code_widget;
class city_list_table;

class city_widget:public QWidget
{
  Q_OBJECT
 public:
  city_widget(fichier_client & p_fichier_client,QWidget * p_parent = NULL);
  void set_enable(bool p_enabled);

    // Interactions with city information
  void clear_city_information(void);
  void set_name(const std::string & p_name);  
  const std::string get_name(void)const;
  void set_postal_code(const std::string & p_postal_code);  
  const std::string get_postal_code(void)const;
  bool is_postal_code_complete(void)const;

  // Interactions with city list
  bool is_city_selection_empty(void)const;
  uint32_t get_selected_city_id(void)const;
  void set_city_list(std::vector<ville> & p_list);
  void set_city_list_enabled(bool p_enable);

  // Interactions with city actions
  void set_create_city_enabled(bool p_enable);
  void set_delete_city_enabled(bool p_enable);
  void set_modify_city_enabled(bool p_enable);
  void set_modify_action_name(const std::string & p_name);

  private slots:

  // City information related events handler
  void treat_criteria_modification_event(void);

  // City list related events handler
  void treat_city_selected_event(void);
  void treat_city_selection_changed_event(void);

  // City action related events handler
  void treat_create_event(void);
  void treat_modify_event(void);
  void treat_delete_event(void);

 private:
  // City information fields
  postal_code_widget * m_postal_code_field;
  QLineEdit * m_name_field;
  // City information list
  city_list_table * m_city_list_table;
  // City information actions
  QPushButton * m_create_button;
  QPushButton * m_modify_button;
  QPushButton * m_delete_button;

  fichier_client & m_fichier_client;
  
};

#endif /* _CITY_WIDGET_H_ */
//EOF
