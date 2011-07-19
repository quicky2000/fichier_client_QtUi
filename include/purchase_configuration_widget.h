#ifndef _PURCHASE_CONFIGURATION_WIDGET_H_
#define _PURCHASE_CONFIGURATION_WIDGET_H_

#include <QWidget>
#include "named_item_list_table.h"
#include "marque.h"
#include "type_achat.h"

class QPushButton;
class fichier_client;

class purchase_configuration_widget : public QWidget
 {
     Q_OBJECT

 public:
   purchase_configuration_widget(fichier_client & p_fichier_client,QWidget * p_parent = NULL);
   
  // Interactions with brand information
   void clear_brand_information(void);
  void set_brand_name(const std::string & p_name);  
  const std::string get_brand_name(void)const;

  // Interactions with brand list
  bool is_brand_selection_empty(void)const;
  uint32_t get_selected_brand_id(void)const;
  void set_brand_list(std::vector<marque> & p_list);
  void set_brand_list_enabled(bool p_enable);

  // Interactions with brand actions
  void set_create_brand_enabled(bool p_enable);
  void set_delete_brand_enabled(bool p_enable);
  void set_modify_brand_enabled(bool p_enable);
  void set_modify_brand_action_name(const std::string & p_name);

  // Interactions with type information
   void clear_type_information(void);
  void set_type_name(const std::string & p_name);  
  const std::string get_type_name(void)const;

  // Interactions with type list
  bool is_type_selection_empty(void)const;
  uint32_t get_selected_type_id(void)const;
  void set_type_list(std::vector<type_achat> & p_list);
  void set_type_list_enabled(bool p_enable);

  // Interactions with type actions
  void set_create_type_enabled(bool p_enable);
  void set_delete_type_enabled(bool p_enable);
  void set_modify_type_enabled(bool p_enable);
  void set_modify_type_action_name(const std::string & p_name);


  void set_enable(bool p_enable);

  private slots:
  // Brand information related events
  void treat_brand_criteria_modification_event(void);
  // Brand list related events
  void treat_brand_selected_event(void);
  void treat_brand_selection_changed_event(void);
  // Brand actions related events
  void treat_create_brand_event(void);
  void treat_delete_brand_event(void);
  void treat_modify_brand_event(void);
  // Type information related events
  void treat_type_criteria_modification_event(void);
  // Type list related events
  void treat_type_selected_event(void);
  void treat_type_selection_changed_event(void);
  // Type list action events
  void treat_create_type_event(void);
  void treat_delete_type_event(void);
  void treat_modify_type_event(void);

 private:
  QLineEdit * m_brand_name_field;
  named_item_list_table<marque> * m_brand_list_table;
  QPushButton * m_create_brand_button;
  QPushButton * m_delete_brand_button;
  QPushButton * m_modify_brand_button;

  QLineEdit * m_type_name_field;
  named_item_list_table<type_achat> * m_type_list_table;
  QPushButton * m_create_type_button;
  QPushButton * m_delete_type_button;
  QPushButton * m_modify_type_button;

  fichier_client & m_fichier_client;
 };

#endif
